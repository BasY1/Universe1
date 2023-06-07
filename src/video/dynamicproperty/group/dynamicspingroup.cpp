#include "dynamicspingroup.h"

Universe1::Video::DynamicSpinGroup::DynamicSpinGroup(const Material &_material,
                                                     const std::string &_name,
                                                     std::list<DynamicProperty *> &_allProps,
                                                     std::list<DynamicMaterialGroup *> &_allMaterials)
    : show(true, _name + ".show")
    , showVector(true, _name + ".showVector")
    , showAxis(true, _name + ".showAxis")
    , showArrows(true, _name + ".showArrows")
    , showDots(true, _name + ".showDots")
    , showSphere(true, _name + ".showSphere")
    , showText(true, _name + ".showText")
    , radiusVector(Config::cfg().lineRadiusSpin, _name + ".radiusVector")
    , radiusLineAxis(Config::cfg().lineRadius, _name + ".radiusLineAxis")
    , radiusLineSphere(Config::cfg().lineRadius, _name + ".radiusLineSphere")
    , radiusDots(Config::cfg().lineRadius * 5.0f, _name + ".radiusDots")
    , twistStep(0.2f, _name + ".twistStep")
    , arrowDirOffset(Config::cfg().spinOffsetDir, _name + ".arrowDirOffset")
    , arrowArmOffset(Config::cfg().spinOffsetSide, _name + ".arrowArmOffset")
    , arrowLength(Config::cfg().arrowLength, _name + ".arrowLength")
    , arrowRadius(Config::cfg().arrowRadius, _name + ".arrowRadius")
    , textSize(1.0f, _name + ".textSize")
    , textPosition(_TextAtPointTo, _name + ".textPosition")
    , textAlign(Qt::AlignHCenter | Qt::AlignBottom, _name + ".textAlign")
    , dotsCount(1U, _name + ".dotsCount")
    , multAxis(Config::cfg().lineMultDash, _name + ".multAxis")
    , material(_material, _name + ".material", _allProps, _allMaterials)
{
    _allProps.push_back(&show);
    _allProps.push_back(&showVector);
    _allProps.push_back(&showAxis);
    _allProps.push_back(&showArrows);
    _allProps.push_back(&showDots);
    _allProps.push_back(&showSphere);
    _allProps.push_back(&showText);
    _allProps.push_back(&radiusVector);
    _allProps.push_back(&radiusLineAxis);
    _allProps.push_back(&radiusLineSphere);
    _allProps.push_back(&radiusDots);
    _allProps.push_back(&twistStep);
    _allProps.push_back(&arrowDirOffset);
    _allProps.push_back(&arrowArmOffset);
    _allProps.push_back(&arrowLength);
    _allProps.push_back(&arrowRadius);
    _allProps.push_back(&textSize);
    _allProps.push_back(&textPosition);
    _allProps.push_back(&textAlign);
    _allProps.push_back(&dotsCount);
    _allProps.push_back(&multAxis);
}
