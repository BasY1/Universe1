#include "dynamicspingroup.h"

Universe1::Video::DynamicSpinGroup::DynamicSpinGroup(const bool _show,
                                                     const bool _showVector,
                                                     const bool _showAxis,
                                                     const bool _showArrows,
                                                     const bool _showDots,
                                                     const bool _showSphere,
                                                     const bool _showText,
                                                     const float _radiusVector,
                                                     const float _radiusLineAxis,
                                                     const float _radiusLineSphere,
                                                     const float _radiusDots,
                                                     const float _twistStep,
                                                     const float _arrowDirOffset,
                                                     const float _arrowArmOffset,
                                                     const float _arrowLength,
                                                     const float _arrowRadius,
                                                     const float _textSize,
                                                     const TextPosition _textPosition,
                                                     const Qt::Alignment _textAlign,
                                                     const uint _dotsCount,
                                                     const uint _multAxis,
                                                     const Material &_material,
                                                     const std::string &_name,
                                                     std::list<DynamicProperty *> &_allProps,
                                                     std::list<DynamicMaterialGroup *> &_allMaterials)
    : show(_show, _name + ".show")
    , showVector(_showVector, _name + ".showVector")
    , showAxis(_showAxis, _name + ".showAxis")
    , showArrows(_showArrows, _name + ".showArrows")
    , showDots(_showDots, _name + ".showDots")
    , showSphere(_showSphere, _name + ".showSphere")
    , showText(_showText, _name + ".showText")
    , radiusVector(_radiusVector, _name + ".radiusVector")
    , radiusLineAxis(_radiusLineAxis, _name + ".radiusLineAxis")
    , radiusLineSphere(_radiusLineSphere, _name + ".radiusLineSphere")
    , radiusDots(_radiusDots, _name + ".radiusDots")
    , twistStep(_twistStep, _name + ".twistStep")
    , arrowDirOffset(_arrowDirOffset, _name + ".arrowDirOffset")
    , arrowArmOffset(_arrowArmOffset, _name + ".arrowArmOffset")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , textSize(_textSize, _name + ".textSize")
    , textPosition(_textPosition, _name + ".textPosition")
    , textAlign(_textAlign, _name + ".textAlign")
    , dotsCount(_dotsCount, _name + ".dotsCount")
    , multAxis(_multAxis, _name + ".multAxis")
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
