#include <QFileDialog>
#include <QMessageBox>
#include "scenesettings.h"

SceneSettings::SceneSettings()
    : modelName("/Users/farfetch/C8_3DViewer_v1.0-0/src/models/medium/al.obj"),
      visibleModelName(modelName.split("/").last()),
      scaleX(1.0), scaleY(1.0), scaleZ(1.0),
      moveX(0.0), moveY(0.0), moveZ(0.0),
      rotateX(0.0), rotateY(0.0), rotateZ(0.0),
      projection(Settings::Projection::Orho),
      sceneColorR(0.0), sceneColorG(0.0), sceneColorB(0.0),
      lineColorR(1.0), lineColorG(1.0), lineColorB(1.0),
      lineWidth(1),
      linePattern(0xffff),
      vertexColorR(0.0), vertexColorG(0.0), vertexColorB(0.0),
      pointSize(1),
      pointStyle(Settings::PointStyle::None)
{
}


void SceneSettings::save()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save config file", ".", "Config file (*.conf)");
    if (check_file_name(filename)) {
        QFile file(filename);
        QDataStream stream(&file);
        file.open(QIODevice::WriteOnly);
        stream << modelName
               << visibleModelName
               << scaleX << scaleY << scaleZ
               << moveX << moveY << moveZ
               << rotateX << rotateY << rotateZ
               << projection
               << sceneColorR << sceneColorG << sceneColorB
               << lineColorR << lineColorG << lineColorB
               << lineWidth
               << linePattern
               << vertexColorR << vertexColorG << vertexColorB
               << pointSize
               << pointStyle;
        file.close();
    }

}


void SceneSettings::load()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Load config file", ".", "Config file (*.conf)");
    if (check_file_name(filename)) {
        QFile file(filename);
        QDataStream stream(&file);
        file.open(QIODevice::ReadOnly);
        stream >> modelName
               >> visibleModelName
               >> scaleX >> scaleY >> scaleZ
               >> moveX >> moveY >> moveZ
               >> rotateX >> rotateY >> rotateZ
               >> projection
               >> sceneColorR >> sceneColorG >> sceneColorB
               >> lineColorR >> lineColorG >> lineColorB
               >> lineWidth
               >> linePattern
               >> vertexColorR >> vertexColorG >> vertexColorB
               >> pointSize
               >> pointStyle;
        file.close();
    }
}


bool SceneSettings::check_file_name(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(0, "info", file.errorString());
        return false;
    }
    file.close();
    return true;
}
