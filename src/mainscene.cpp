#include <iostream>
#include "mainscene.h"

MainScene::MainScene()
{
    model = load_model("/Users/farfetch/C8_3DViewer_v1.0-0/src/models/medium/al.obj");
}

void MainScene::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void MainScene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainScene::paintGL()
{
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glScaled(0.2, 0.2, 0.2);
//    glTranslated(1, 0, 0);
//    glRotated(angle, x, y, z);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-2, 2, -2, 2, -2, 2);

    glFrustum (-1, 1, -1, 1, 3, 20);
    glTranslatef(0.0, 0.0, -10.0);
//    float fov = 60.0 * M_PI / 180;  // 60 угол в градусах
//    float winHeight = 2;
//    float winWidth = 2;
//    float heapHeight = winHeight / (2 * tan(fov / 2));
//    glFrustum(-winWidth, winWidth, -winHeight, winHeight, heapHeight, heapHeight + 2);


    // цвет фона
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    // привязываем вершины
    glVertexPointer(3, GL_FLOAT, 0, model.vertexes);

    // отрисовываем линии
    glColor3d(0.5f, 0.5f, 0.5f);
    glLineWidth(1);
    glLineStipple(1, 0x00ff);
    glEnable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, model.f_num, GL_UNSIGNED_INT, model.faces);
    glDisable(GL_LINE_STIPPLE);

    // отрисовываем вершины
    glColor3d(1.0f, 1.0f, 1.0f);
    glPointSize(3);
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, model.v_num);
    glDisable(GL_POINT_SMOOTH);

    glDisableClientState(GL_VERTEX_ARRAY);
}
