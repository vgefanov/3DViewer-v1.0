#include <iostream>
#include "mainscene.h"

MainScene::MainScene()
{
    model = load_model("/Users/farfetch/C8_3DViewer_v1.0-0/src/models/medium/al.obj");
    // размеры проекции
    projection_min = (model.x_min < model.y_min) ? model.x_min : model.y_min;
    if (model.z_min < projection_min) projection_min = model.z_min;
    projection_max = (model.x_max > model.y_max) ? model.x_max : model.y_max;
    if (model.z_max > projection_max) projection_max = model.z_max;
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
    const float projection_scale = 1.1;
    float projmin_scaled = projection_min * projection_scale;
    float projmax_scaled = projection_max * projection_scale;
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glScaled(0.2, 0.2, 0.2);
//    glTranslated(1, 0, 0);
//    glRotated(angle, x, y, z);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // glOrtho(projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled);

    glFrustum (projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled, 8, 100);
    glTranslatef(0.0, 0.0, -10);


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
