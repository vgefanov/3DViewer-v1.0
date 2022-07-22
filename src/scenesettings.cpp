#include "scenesettings.h"

SceneSettings::SceneSettings()
    : scaleX(1.0), scaleY(1.0), scaleZ(1.0),
      moveX(0.0), moveY(0.0), moveZ(0.0),
      rotateX(0.0), rotateY(0.0), rotateZ(0.0),
      projection(Settings::Projection::Orho),
      sceneColorR(0.0), sceneColorG(0.0), sceneColorB(0.0),
      lineColorR(1.0), lineColorG(1.0), lineColorB(1.0),
      lineWidth(1),
      linePattern(0xffff),
      vertexColorR(0.0), vertexColorG(0.0), vertexColorB(0.0),
      pointSize(1)
{
}
