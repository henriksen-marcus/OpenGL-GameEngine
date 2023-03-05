#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>
#include <string>
#include <iostream>

#include "Cube.h"
#include "VisualFunction2D.h"
#include "XYZ.h"
#include "Arrow.h"
#include "VisualFunction3D.h"
#include "VisualPoints.h"
#include "Axis.h"
#include "BaseObject.h"
#include "World.h"
#include "WorldManager.h"
#include "Plane.h"
#include "Quadtree.h"
#include "PlayerController.h"
#include "Scene1.h"
#include "CameraComponent.h"

#include "MathTasks.h"
#include "functions.h"
#include "renderwindow.h"
#include "Shader.h"
#include "mainwindow.h"
#include "logger.h"

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

    //renderer = new Renderer();
}


RenderWindow::~RenderWindow(){}


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
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(128.f/255.f, 200.f/255.f, 0.9f, 1.f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:
    // NB: hardcoded path to files! You have to change this if you change directories for the project.
    // Qt makes a build-folder besides the project folder. That is why we go down one directory
    // (out of the build-folder) and then up into the project folder.
    mShaderProgram = new Shader();
    mShaderProgram->CreateFromFiles("../OpenGLMainQt/vertex.vert", "../OpenGLMainQt/fragment.frag");

    //renderer->Add("xyz", new XYZ(true));
    //renderer->Add("arrow", new Arrow(QVector3D(), 1.f, QVector3D(1.f, 0.f, 1.f)));
    //renderer->Add("cube", new Cube(QVector3D(), 1.f, QVector3D(0.3f, 0.6f, 1.f), GL_LINES, true));

//    auto* a1 = new Actor(QVector3D(0.5f, -0.5f, 0.f));
//    a1->SetCollisionComponent(0.25f);
//    auto* a2 = new Actor(QVector3D(-0.2f, -0.5f, 0.f));
//    a2->SetCollisionComponent(0.3f);
//    auto* a3 = new Actor(QVector3D(0.8f, 0.5f, 0.f));
//    a3->SetCollisionComponent(0.1f);

//    renderer->Add("a1", new Plane(QVector3D(0.5f, -0.5f, 0.f), 0.5f, 0.5f, QVector3D(0.f, 1.f, 0.f), GL_LINES));
//    renderer->Get("a1")->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));


//    renderer->Add("a2", new Plane(QVector3D(-0.2f, -0.5f, 0.f), 0.6f, 0.6f, QVector3D(0.f, 1.f, 0.f), GL_LINES));
//    renderer->Get("a2")->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));


//    renderer->Add("a3", new Plane(QVector3D(0.8f, 0.5f, 0.f), 0.2f, 0.2f, QVector3D(0.f, 1.f, 0.f), GL_LINES));
//    renderer->Get("a3")->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

//    auto* quad = new Quadtree(Boundry2D(QVector2D(0.f, 0.f), 2.f), 0.f);
//    //quad->Subdivide();
////    quad->ne->Subdivide();
////    quad->ne->ne->Subdivide();
////    quad->ne->ne->ne->Subdivide();

//    quad->Insert(a1);
//    quad->Insert(a2);
//    quad->Insert(a3);

//    std::vector<Actor*> found;
//    quad->Query(found, Boundry2D(QVector2D(0.f, 0.f), 0.4f));
//    printf("found: %d\n", found.size());

//    renderer->Add("a4", new Plane(QVector3D(0.f, 0.f, 0.f), 0.8f, 0.8f, QVector3D(0.f, 0.f, 1.f), GL_LINES));
//    renderer->Get("a4")->AddActorLocalRotation(QVector3D(90.f, 0.f, 0.f));

//    quad->Init();
//    renderer->Add("quad", quad);

    scene1 = new Scene1();
    WorldManager::GetInstance().SetWorld(scene1);
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

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{
    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    initializeOpenGLFunctions();    //must call this every frame it seems...

    //clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShaderProgram->UseShader();

    // Calculate framerate before
    // checkForGLerrors() because that call takes a long time
    // and before swapBuffers(), else it will show the vsync time
    calculateFramerate();

    //using our expanded OpenGL debugger to check if everything is OK.
    checkForGLerrors();

    processInput();

    QMatrix4x4 projection;
    projection.perspective(FOV, aspectRatio, nearPlane, farPlane);

    QMatrix4x4 viewMatrix{};
    auto* cam = PlayerController::GetInstance().GetCurrentCamera();
    if (cam)
    {
        viewMatrix = cam->GetViewMatrix();
        //std::cout << "Got camera\n";
    }

    QMatrix4x4 emptyTranslation{};
    glUniformMatrix4fv(mShaderProgram->GetModelLocation(), 1, GL_FALSE, emptyTranslation.constData());
    glUniformMatrix4fv(mShaderProgram->GetProjectionLocation(), 1, GL_FALSE, projection.constData());
    glUniformMatrix4fv(mShaderProgram->GetViewLocation(), 1, GL_FALSE, viewMatrix.constData());

    std::cout << deltaTime << std::endl;

    // Runs everything
    WorldManager::GetInstance().GetWorld()->Tick(deltaTime, mShaderProgram->GetModelLocation());
    //renderer->Get("arrow")->AddActorLocalRotation(QVector3D(0.f, 0.f, 1.f));
    //renderer->Get("xyz")->SetActorRotation(QVector3D(45.f, 1.f, 0.5f));



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
        mRenderTimer->start(16);
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
    //mMainWindow->statusBar()->showMessage(" AAAA");

    if (event->key() == Qt::Key_Escape) mMainWindow->close();  // Shuts down the whole program

    if (event->key() == Qt::Key_W) heldKeys.push_back(Movement::FORWARD);
    if (event->key() == Qt::Key_A) heldKeys.push_back(Movement::LEFT);
    if (event->key() == Qt::Key_S) heldKeys.push_back(Movement::BACKWARD);
    if (event->key() == Qt::Key_D) heldKeys.push_back(Movement::RIGHT);
    if (event->key() == Qt::Key_E) heldKeys.push_back(Movement::UP);
    if (event->key() == Qt::Key_Q) heldKeys.push_back(Movement::DOWN);
}

void RenderWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::FORWARD), heldKeys.end());
    if (event->key() == Qt::Key_A) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::LEFT), heldKeys.end());
    if (event->key() == Qt::Key_S) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::BACKWARD), heldKeys.end());
    if (event->key() == Qt::Key_D) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::RIGHT), heldKeys.end());
    if (event->key() == Qt::Key_E) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::UP), heldKeys.end());
    if (event->key() == Qt::Key_Q) heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(),Movement::DOWN), heldKeys.end());
}

void RenderWindow::wheelEvent(QWheelEvent* event){}
