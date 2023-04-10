#pragma once

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include "enums.h"
#include "Renderer.h"

class QOpenGLContext;
class Shader;
class MainWindow;

/* This inherits from QWindow to get access to the Qt functionality and
 * OpenGL surface. We also inherit from QOpenGLFunctions, to get access
 * to the OpenGL functions. This is the same as using "glad" and "glfw"
 * from general OpenGL tutorials.
*/
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    friend class DebugLogger;
private slots:
    void render();

private:
    void init();            //initialize things we need before rendering

    // Our OpenGL context
    QOpenGLContext* mContext;

    bool mInitialized{false};

    // Timer that drives the gameloop
    QTimer *mRenderTimer;

    // Time variable that reads the calculated FPS
    QElapsedTimer mTimeStart;

    // Points back to MainWindow to be able to put info in StatusBar
    MainWindow* mMainWindow;

    // Helper class to get some clean debug info from OpenGL
    class QOpenGLDebugLogger* mOpenGLDebugLogger;

    // Logger - Output Log in the application
    class Logger* mLogger;

    float FOV{75.f};
    float aspectRatio{16.f/9.f};
    float nearPlane{0.01f};
    float farPlane{1000.f};

    float deltaTime{0.016f};
    qint64 lastFrame{};
    QElapsedTimer* frameTimer;

    // How much the mouse moved since last tick
    float lastMouseX{0.f};
    float lastMouseY{0.f};
    int currentFunc = 1;

    /**
     * \brief Keys that were held the last frame.
     */
    std::vector<Movement> heldKeys;

    /**
     * \brief Takes the input from the last frame and
     * sends into into the engine hierarchy (pawns etc.)
     */
    void processInput();

    // Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate();

    // Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();

    bool bIsPolygonMode = false;
    bool bIsCullMode = false;

protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)
    //
    //    void mousePressEvent(QMouseEvent *event) override{}
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;              //the only one we use now
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

