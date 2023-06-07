#include "dynamicanglegroup.h"

Universe1::Video::DynamicAngleGroup::DynamicAngleGroup(const float _angleOffset,
                                                       const Material &_material,
                                                       const std::string &_name,
                                                       std::list<DynamicProperty *> &_allProps,
                                                       std::list<DynamicMaterialGroup *> &_allMaterials)
    : show(true, _name + ".show")
    , showText(true, _name + ".showText")
    , angleOffset(_angleOffset, _name + ".angleOffset")
    , radiusLine(Config::cfg().lineRadius, _name + ".radiusLine")
    , arrowLength(Config::cfg().arrowLength, _name + ".arrowLength")
    , arrowRadius(Config::cfg().arrowRadius, _name + ".arrowRadius")
    , textSize(1.0f, _name + ".textSize")
    , textPosition(_TextMiddle, _name + ".textPosition")
    , textAlign(Qt::AlignHCenter | Qt::AlignBottom, _name + ".textAlign")
    , material(_material, _name + ".material", _allProps, _allMaterials)
{
    _allProps.push_back(&show);
    _allProps.push_back(&showText);
    _allProps.push_back(&angleOffset);
    _allProps.push_back(&radiusLine);
    _allProps.push_back(&arrowLength);
    _allProps.push_back(&arrowRadius);
    _allProps.push_back(&textSize);
    _allProps.push_back(&textPosition);
    _allProps.push_back(&textAlign);
}
