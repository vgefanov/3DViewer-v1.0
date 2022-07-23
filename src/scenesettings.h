#ifndef SCENESETTINGS_H
#define SCENESETTINGS_H

#include <QColor>

namespace Settings
{
    enum class Projection { Orho, Frustum };
    enum class PointStyle { None, Rounded, Quad };
}

class SceneSettings
{
public:
    SceneSettings();

    QString modelName;
    QString visibleModelName;
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
    Settings::PointStyle pointStyle;

    void save();
    void load();

private:
    bool check_file_name(QString filename);
};

#endif // SCENESETTINGS_H
