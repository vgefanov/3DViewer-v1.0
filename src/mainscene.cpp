#include <iostream>
#include "mainscene.h"

MainScene::MainScene()
{
    model = load_model("/Users/farfetch/C8_3DViewer_v1.0-0/src/models/small/cube.obj");
}

void MainScene::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void MainScene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainScene::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.5f, 0.5f, 0.5f);
    glLineWidth(20);

    glLineStipple(1, 0x00ff);
    glEnable(GL_LINE_STIPPLE);

    glVertexPointer(3, GL_FLOAT, 0, model.vertexes);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, model.f_num, GL_UNSIGNED_INT, model.faces);
    glDisableClientState(GL_VERTEX_ARRAY);
}
