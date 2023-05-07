#include "renderwindow.h"

#include <iostream>
#include <QDebug>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QStatusBar>
#include <QTimer>
#include <windows.h>
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>
#include <filesystem>

#include "logger.h"
#include "mainwindow.h"
#include "PlayerController.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "../Game/Scenes/TextureScene.h"
#include "World.h"
#include "WorldManager.h"
#include "Vendor/stb_image.h"
#include "DebugLogger.h"
#include "Source/Game/Scenes/Scene1.h"
#include "Source/Game/Scenes/HeightmapScene.h"
#include "Source/Engine/Shader3.h"
#include "Source/Game/Scenes/BarycentricScene.h"
#include "Source/Game/Scenes/CurveScene.h"
#include "Source/Game/Scenes/CubemapScene.h"
#include "Source/Game/Scenes/Eksamen2019Scene.h"

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)
{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);

    // DeltaTime
    frameTimer = new QElapsedTimer();
    frameTimer->start();
}

RenderWindow::~RenderWindow()
{
	delete mRenderTimer;
	delete mContext;
    delete frameTimer;
    delete mOpenGLDebugLogger;
    delete mLogger;
}

// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        mLogger->logText("makeCurrent() failed", LogType::REALERROR);
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    mLogger->logText("The active GPU and API:", LogType::HIGHLIGHT);
    std::string tempString;
    tempString += std::string("  Vendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n" +
            std::string("  Renderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" +
            std::string("  Version: ") + std::string((char*)glGetString(GL_VERSION));
    mLogger->logText(tempString);

    //Start the Qt OpenGL debugger
    //Really helpful when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(128.f/255.f, 200.f/255.f, 0.9f, 1.f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Current program path: " << cwd << std::endl;

    //auto* texScene = new TextureScene();
    //WorldManager::GetInstance().SetWorld(texScene);

    //auto* heightmapscene = new HeightmapScene();
    //WorldManager::GetInstance().SetWorld(heightmapscene);

    /*auto* baryscene = new BarycentricScene();
    WorldManager::GetInstance().SetWorld(baryscene);*/

    /*CurveScene* curveScene = new CurveScene();
    WorldManager::GetInstance().SetWorld(curveScene);*/

    /*auto* cubescene = new CubemapScene();
    WorldManager::GetInstance().SetWorld(cubescene);*/

    auto* eksScene = new Eksamen2019Scene();
    WorldManager::GetInstance().SetWorld(eksScene);

    auto* s1 = new Shader();
    s1->CreateFromFiles("Source/Engine/Shader/vertex.vert", "Source/Engine/Shader/fragment.frag");

    auto* s2 = new Shader();
    s2->CreateFromFiles("Source/Engine/Shader/texturevertshader.vert", "Source/Engine/Shader/texturefragshader.frag");

    auto* s3 = new Shader();
    s3->CreateFromFiles("Source/Engine/Shader/godshader.vert", "Source/Engine/Shader/godshader.frag");

    auto* s4 = new Shader3();
    s4->CreateFromFiles("Source/Engine/Shader/geo.vert", "Source/Engine/Shader/geo.geom", "Source/Engine/Shader/geo.frag");

    auto* s5 = new Shader();
    s5->CreateFromFiles("Source/Engine/Shader/skybox.vert", "Source/Engine/Shader/skybox.frag");

    auto* s6 = new Shader();
    s6->CreateFromFiles("Source/Engine/Shader/billboard.vert", "Source/Engine/Shader/billboard.frag");

    auto& SM = ShaderManager::GetInstance();
    SM.Shaders["plain"] = s1;
    SM.Shaders["texture"] = s2;
    SM.Shaders["god"] = s3;
    SM.Shaders["geo"] = s4;
    SM.Shaders["skybox"] = s5;
    SM.Shaders["billboard"] = s6;
    SM.ActiveShader = s1;

    DebugLogger::GetInstance().SetRenderWindow(this);
    WorldManager::GetInstance().GetWorld()->BeginPlay();
}



void RenderWindow::processInput()
{
    // Remove dupes
    std::sort(heldKeys.begin(), heldKeys.end());

    // Remove duplicates
    auto new_end = std::unique(heldKeys.begin(), heldKeys.end());

    // Resize the vector to remove the duplicates
    heldKeys.resize(std::distance(heldKeys.begin(), new_end));

//    for (auto key : heldKeys)
//    {
//        camera->ProcessKeyboard(key, deltaTime);
//    }
    PlayerController::GetInstance().ProcessKeyboard(heldKeys);
}

void RenderWindow::render()
{
    mContext->makeCurrent(this); // Must be called every frame (every time mContext->swapBuffers is called)
    //initializeOpenGLFunctions(); // Must call this every frame it seems..

    QVector3D col = WorldManager::GetInstance().GetWorld()->GetWorldColor();
    glClearColor(col.x(), col.y(), col.z(), 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate framerate before checkForGLerrors() because that call takes a long time
    // and before swapBuffers(), else it will show the vsync time
    calculateFramerate();
    mTimeStart.restart(); // Restart FPS clock
    //using our expanded OpenGL debugger to check if everything is OK.
    checkForGLerrors();

    processInput();

    // Runs everything
    WorldManager::GetInstance().GetWorld()->Tick(deltaTime);

    /* Qt require us to call this swapBuffers() -function.
     swapInterval is 1 by default which means that swapBuffers() will (hopefully) block
     and wait for vsync. */
    mContext->swapBuffers(this);
}

//This function is called from Qt when window is exposed (shown)
// and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(4);
        mTimeStart.start();
    }
}

//The way this function is set up is that we start the clock before doing the draw call,
// and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)
    {
        if (++frameCount > 30)    // once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            // showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }

    qint64 currentFrame = frameTimer->elapsed();
    //frameTimer->restart();
    deltaTime = (currentFrame - lastFrame) * 0.001f;
    lastFrame = currentFrame;
}

//Uses QOpenGLDebugLogger if this is presentf
//Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
        {
            if (!(message.type() == message.OtherType)) // get rid of uninteresting "object ...
                                                        // will use VIDEO memory as the source for
                                                        // buffer object operations"
                // valid error message:
                mLogger->logText(message.message().toStdString(), LogType::REALERROR);
        }
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            mLogger->logText("glGetError returns " + std::to_string(err), LogType::REALERROR);
            switch (err) {
            case 1280:
                mLogger->logText("GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.");
                break;
            case 1281:
                mLogger->logText("GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.");
                break;
            case 1282:
                mLogger->logText("GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.");
                break;
            }
        }
    }
}

//Tries to start the extended OpenGL debugger that comes with Qt
//Usually works on Windows machines, but not on Mac...
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            mLogger->logText("This system can not use QOpenGLDebugLogger, so we revert to glGetError()",
                             LogType::HIGHLIGHT);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            mLogger->logText("This system can log extended OpenGL errors", LogType::HIGHLIGHT);
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                mLogger->logText("Started Qt OpenGL debug logger");
        }
    }
}

void RenderWindow::mouseMoveEvent(QMouseEvent* event)
{
    /* Get the difference from the last mouse position
     * and send it to the camera. Then move cursor back
     * to center of screen to prevent cursor from exiting
     * the window.
    */
    float currentX = event->globalPosition().x();
    float currentY = event->globalPosition().y();

    float deltaX = currentX - mMainWindow->center.x();
    float deltaY = mMainWindow->center.y() - currentY;

    QCursor::setPos(mMainWindow->center);

    PlayerController::GetInstance().ProcessMouse(deltaX, deltaY);
}

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) mMainWindow->close();  // Shuts down the whole program

    if (event->key() == Qt::Key_W) heldKeys.push_back(Movement::FORWARD);
    if (event->key() == Qt::Key_A) heldKeys.push_back(Movement::LEFT);
    if (event->key() == Qt::Key_S) heldKeys.push_back(Movement::BACKWARD);
    if (event->key() == Qt::Key_D) heldKeys.push_back(Movement::RIGHT);
    if (event->key() == Qt::Key_E) heldKeys.push_back(Movement::ROTATE_RIGHT);
    if (event->key() == Qt::Key_Q) heldKeys.push_back(Movement::ROTATE_LEFT);
    if (event->key() == Qt::Key_Shift) heldKeys.push_back(Movement::UP);
    if (event->key() == Qt::Key_Control) heldKeys.push_back(Movement::DOWN);
    if (event->key() == Qt::Key_Space) heldKeys.push_back(Movement::JUMP);

    if (event->key() == Qt::Key_Tab)
    {
	    /*if (mMainWindow->isFullScreen())
	    {
		    mMainWindow->showNormal();
		    mMainWindow->setFixedSize(800, 600);
	    }
	    else
	    {
		    mMainWindow->showFullScreen();
	    }*/
        if (bIsPolygonMode)
        {
	        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			bIsPolygonMode = false;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			bIsPolygonMode = true;
		}
    }

    if (event->key() == Qt::Key_Alt)
    {
	    if (bIsCullMode)
	    {
		    glDisable(GL_CULL_FACE);
            bIsCullMode = false;
	    }
        else
        {
        	glEnable(GL_CULL_FACE);
			bIsCullMode = true;
        }
    }
}

void RenderWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::FORWARD), heldKeys.end());
    if (event->key() == Qt::Key_A) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::LEFT), heldKeys.end());
    if (event->key() == Qt::Key_S) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::BACKWARD), heldKeys.end());
    if (event->key() == Qt::Key_D) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::RIGHT), heldKeys.end());
    if (event->key() == Qt::Key_E) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::ROTATE_RIGHT), heldKeys.end());
    if (event->key() == Qt::Key_Q) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::ROTATE_LEFT), heldKeys.end());
    if (event->key() == Qt::Key_Shift) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::UP), heldKeys.end());
    if (event->key() == Qt::Key_Control) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::DOWN), heldKeys.end());
    if (event->key() == Qt::Key_Space) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::JUMP), heldKeys.end());
}

void RenderWindow::wheelEvent(QWheelEvent* event)
{
	if (event->angleDelta().y() > 0)
	{
		PlayerController::GetInstance().ProcessMouseScroll(1.f);
	}
	else
	{
		PlayerController::GetInstance().ProcessMouseScroll(-1.f);
	}
}
