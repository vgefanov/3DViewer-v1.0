#ifndef MAINSCENE_H
#define MAINSCENE_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "scenesettings.h"

extern "C" {
    #include "cfiles/objfiles.h"
    #include "cfiles/affine.h"
}

class MainScene : public QOpenGLWindow, protected QOpenGLFunctions
{

public:
    MainScene();
    void set_projection_settings();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void screenshot(QString filename);

    model model;
    SceneSettings *sceneSettings;

    float diapason;

private:
    float projection_min;
    float projection_max;
    float projmin_scaled;
    float projmax_scaled;
};

#endif // MAINSCENE_H
