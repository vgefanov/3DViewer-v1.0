#include <iostream>
#include "mainscene.h"

MainScene::MainScene()
{
    // Настройки
    sceneSettings = new SceneSettings();

    model = load_model(sceneSettings->modelName.toLocal8Bit().data());
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
    float diapason = projmax_scaled - projmin_scaled;

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // масштабирование
    //glScalef(sceneSettings->scaleX, sceneSettings->scaleY, sceneSettings->scaleZ);
    // сдвиг
    //glTranslatef(sceneSettings->moveX * diapason, sceneSettings->moveY * diapason, sceneSettings->moveZ);
    // поворот
    //glRotatef(sceneSettings->rotateX, 1, 0, 0);
    //glRotatef(sceneSettings->rotateY, 0, 1, 0);
    //glRotatef(sceneSettings->rotateZ, 0, 0, 1);

    //  проекция
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (sceneSettings->projection == Settings::Projection::Orho) {
        glOrtho(projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled);
    } else {
        glFrustum (projmin_scaled, projmax_scaled, projmin_scaled, projmax_scaled, 8, 100);
        glTranslatef(0.0, 0.0, -10);
    }

    // цвет фона
    glClearColor(sceneSettings->sceneColorR, sceneSettings->sceneColorG, sceneSettings->sceneColorB, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // привязываем вершины
    glVertexPointer(3, GL_FLOAT, 0, model.vertexes);

    glEnableClientState(GL_VERTEX_ARRAY);

    // отрисовываем линии
    glColor3d(sceneSettings->lineColorR, sceneSettings->lineColorG, sceneSettings->lineColorB);
    glLineWidth(sceneSettings->lineWidth);
    glLineStipple(1, sceneSettings->linePattern);
    glEnable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, model.f_num, GL_UNSIGNED_INT, model.faces);
    glDisable(GL_LINE_STIPPLE);

    // отрисовываем вершины
    if (sceneSettings->pointStyle != Settings::PointStyle::None) {
        glColor3d(sceneSettings->vertexColorR, sceneSettings->vertexColorG, sceneSettings->vertexColorB);
        glPointSize(sceneSettings->pointSize);
        if (sceneSettings->pointStyle == Settings::PointStyle::Rounded) {
            glEnable(GL_POINT_SMOOTH);
        }
        glDrawArrays(GL_POINTS, 0, model.v_num / 3);
        if (sceneSettings->pointStyle == Settings::PointStyle::Rounded) {
            glDisable(GL_POINT_SMOOTH);
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}


void MainScene::screenshot(QString filename)
{
    this->grabFramebuffer().save(filename);
}
