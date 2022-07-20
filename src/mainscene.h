#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

extern "C" {
    #include "cfiles/cfiles.h"
}

class MainScene : public QOpenGLWindow
{

public:
    MainScene();
    ~MainScene() override;

    void initializeGL() override;
    void paintGL() override;

    void updateScene();
    void animateColorsTo(const std::vector<QColor> & toColors);

    std::vector<QColor> m_vertexColors;

private:
    void animate();

    QOpenGLVertexArrayObject  m_vao;
    QOpenGLBuffer             m_vbo;
    QOpenGLBuffer             m_ibo;
    QOpenGLShaderProgram     *m_program;

    std::vector<float>		  m_vertexBufferData;
    std::vector<QColor>		  m_toColors;
    std::vector<QColor>		  m_fromColors;
    unsigned int			  m_frameCount;

    model model;
};

#endif // MAINSCENE_H
