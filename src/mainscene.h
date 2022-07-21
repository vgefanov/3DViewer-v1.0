#ifndef MAINSCENE_H
#define MAINSCENE_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWindow>

extern "C" {
    #include "cfiles/cfiles.h"
}

class MainScene : public QOpenGLWindow
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
