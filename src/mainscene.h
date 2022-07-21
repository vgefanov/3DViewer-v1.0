#ifndef MAINSCENE_H
#define MAINSCENE_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWindow>
#include <QOpenGLFunctions>

extern "C" {
    #include "cfiles/cfiles.h"
}

class MainScene : public QOpenGLWindow, protected QOpenGLFunctions
{

public:
    MainScene();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    model model;
};

#endif // MAINSCENE_H
