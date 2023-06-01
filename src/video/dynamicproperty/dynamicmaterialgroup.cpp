#include "dynamicmaterialgroup.h"

Universe1::Video::DynamicMaterialGroup::DynamicMaterialGroup(const QColor _color, const std::string &_name)
    : ambient(_color.darker(), _name + ".ambient")
    , diffuse(_color, _name + ".diffuse")
    , specular(QColor(255, 255, 224), _name + ".specular")
    , shine(32.0f, _name + ".shine")
    , alpha(1.0f, _name + ".alpha")
{
}

Universe1::Video::DynamicMaterialGroup::DynamicMaterialGroup(const Material &_material, const std::string &_name)
    : ambient(_material.ambient, _name + ".ambient")
    , diffuse(_material.diffuse, _name + ".diffuse")
    , specular(_material.specular, _name + ".specular")
    , shine(_material.shine, _name + ".shine")
    , alpha(_material.alpha, _name + ".alpha")
{
}
