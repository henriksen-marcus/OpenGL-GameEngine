#include "TextureScene.h"
#include "Plane.h"

TextureScene::TextureScene()
{
    auto* plane = new Plane(QVector3D(), 5.f, 5.f);
    mActors.push_back(plane);
    mRenderer->Add("plane", plane);
}
