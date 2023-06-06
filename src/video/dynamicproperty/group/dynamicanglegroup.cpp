#include "dynamicanglegroup.h"

Universe1::Video::DynamicAngleGroup::DynamicAngleGroup(const bool _show,
                                                       const bool _showText,
                                                       const float _angleOffset,
                                                       const float _radiusLine,
                                                       const float _arrowLength,
                                                       const float _arrowRadius,
                                                       const float _textSize,
                                                       const TextPosition _textPosition,
                                                       const Qt::Alignment _textAlign,
                                                       const Material &_material,
                                                       const std::string &_name,
                                                       std::list<DynamicProperty *> &_allProps,
                                                       std::list<DynamicMaterialGroup *> &_allMaterials)
    : show(_show, _name + ".show")
    , showText(_showText, _name + ".showText")
    , angleOffset(_angleOffset, _name + ".angleOffset")
    , radiusLine(_radiusLine, _name + ".radiusLine")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , textSize(_textSize, _name + ".textSize")
    , textPosition(_textPosition, _name + ".textPosition")
    , textAlign(_textAlign, _name + ".textAlign")
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
