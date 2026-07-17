#pragma once
#include "../../../../../../MiddleLayer/Math/Vector/Vector3.h"


struct StandardMaterial
{
    Vector3 diffuse = { 0.5f,0.5f, 0.5f };
    Vector3 specular;
    float alpha{};
    float shininess{};
    std::string colorMap;
    std::string specularMap;
    std::string shininessMap;
    std::string normalMap;

};