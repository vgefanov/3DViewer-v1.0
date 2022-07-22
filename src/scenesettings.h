#ifndef SCENESETTINGS_H
#define SCENESETTINGS_H

#include <QColor>

namespace Settings
{
    enum class Projection { Orho, Frustum };
}

class SceneSettings
{
public:
    SceneSettings();

    float scaleX, scaleY, scaleZ;
    float moveX, moveY, moveZ;
    float rotateX, rotateY, rotateZ;
    Settings::Projection projection;
    float sceneColorR, sceneColorG, sceneColorB;
    float lineColorR, lineColorG, lineColorB;
    int lineWidth;
    unsigned short linePattern;
    float vertexColorR, vertexColorG, vertexColorB;
    int pointSize;
};

#endif // SCENESETTINGS_H
