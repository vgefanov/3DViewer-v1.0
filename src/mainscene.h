#ifndef MAINSCENE_H
#define MAINSCENE_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "scenesettings.h"

extern "C" {
    #include "cfiles/objfiles.h"
    #include "cfiles/matrix.h"
}

class MainScene : public QOpenGLWindow, protected QOpenGLFunctions
{

public:
    MainScene();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    model model;
    SceneSettings *sceneSettings;

private:
    float projection_min;
    float projection_max;
};

#endif // MAINSCENE_H
