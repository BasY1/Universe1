/*!
 * \file src/Items/Circle/itemcircle.cpp
 * \brief Dynamic circle video item
 */

#include "itemcircle.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"
#include "../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

ItemCircle::ItemCircle(const std::string &_name,
                       const Math::Vec3F &_center,
                       const Math::Vec3F &_normal,
                       const Math::Vec3F &_arm,
                       const float _radius,
                       const size_t _quality,
                       const Circle::ShowCircleType _show,
                       const Circle::ShowCircleWireType _showWire,
                       const Math::MaterialRGB &_materialFront,
                       const Math::MaterialRGB &_materialBack,
                       const Math::MaterialRGBA &_materialCenterFront,
                       const Math::MaterialRGBA &_materialBorderFront,
                       const Math::MaterialRGBA &_materialCenterBack,
                       const Math::MaterialRGBA &_materialBorderBack,
                       const Math::MaterialRGBA &_materialWire,
                       const float _radiusWire,
                       const float _stepWire,
                       const size_t _qualityWire,
                       const uint8_t _alpha,
                       const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Circle::ShowCircleType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , materialCenterFront("materialCenterFront", _materialCenterFront)
    , materialBorderFront("materialBorderFront", _materialBorderFront)
    , materialCenterBack("materialCenterBack ", _materialCenterBack)
    , materialBorderBack("materialBorderBack ", _materialBorderBack)
    , showWire("showWire", QMetaEnum::fromType<Circle::ShowCircleWireType>(), _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&materialCenterFront);
    addProperty(&materialBorderFront);
    addProperty(&materialCenterBack);
    addProperty(&materialBorderBack);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

/*!
 * \brief Create circle wire-frame 3D data
 * \param _data Output data objects
 * \param _timeStep Time-step
 * \param _showWire Show circle wire-frame mode
 * \param _radiusWire Wire radius
 * \param _stepWire Wire-frame matrix step
 * \param _qualityWire Wire circle quality
 * \param _materialWire Wire-frame material
 * \param _orientation Orientation
 * \param _radius Circle radius
 * \param _quality Circle quality
 * \return
 */
static void createCircleWires(std::list<OpenGL::Data3D *> &_data,
                              const size_t _timeStep,
                              const Props::ItemPropertyEnum &_showWire,
                              const Props::ItemPropertyFloat &_radiusWire,
                              const Props::ItemPropertyFloat &_stepWire,
                              const Props::ItemPropertyQuality &_qualityWire,
                              const Props::ItemPropertyMaterialRGBA &_materialWire,
                              const Math::OrientF &_orientation,
                              const float _radius,
                              const size_t _quality)
{
    switch (_showWire.valueEnum<Circle::ShowCircleWireType>(_timeStep))
    {
    case Circle::CircleWireHidden: break;

    case Circle::CircleWireBorder: {
        const float rw = _radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const Math::MaterialRGBA mw = _materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t qw = _qualityWire.value(_timeStep);
                _data.push_back(OpenGL::Data3DMaterialNormal::torus(_orientation, _radius, rw, _quality, qw, mw));
            }
        }
    }
    break;

    case Circle::CircleWireFull: {
        float rw = _radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const Math::MaterialRGBA mw = _materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t qw = _qualityWire.value(_timeStep);
                _data.push_back(OpenGL::Data3DMaterialNormal::torus(_orientation, _radius, rw, _quality, qw, mw));

                const float sw = _stepWire.value(_timeStep);
                if (Math::isPositive(sw))
                {
                    rw *= 0.8f;

                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::line(_orientation.center - _orientation.normal2 * _radius,
                                                           _orientation.center + _orientation.normal2 * _radius,
                                                           rw,
                                                           rw,
                                                           qw,
                                                           mw));

                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::line(_orientation.center - _orientation.normal3 * _radius,
                                                           _orientation.center + _orientation.normal3 * _radius,
                                                           rw,
                                                           rw,
                                                           qw,
                                                           mw));

                    const float r2 = _radius * _radius;
                    float x = sw;
                    while (Math::isLessNotEqual(x, _radius))
                    {
                        const float y = std::sqrt(r2 - x * x);

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center + _orientation.normal2 * x + _orientation.normal3 * y,
                            _orientation.center + _orientation.normal2 * x - _orientation.normal3 * y,
                            rw,
                            rw,
                            qw,
                            mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center - _orientation.normal2 * x + _orientation.normal3 * y,
                            _orientation.center - _orientation.normal2 * x - _orientation.normal3 * y,
                            rw,
                            rw,
                            qw,
                            mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center + _orientation.normal2 * y + _orientation.normal3 * x,
                            _orientation.center - _orientation.normal2 * y + _orientation.normal3 * x,
                            rw,
                            rw,
                            qw,
                            mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center + _orientation.normal2 * y - _orientation.normal3 * x,
                            _orientation.center - _orientation.normal2 * y - _orientation.normal3 * x,
                            rw,
                            rw,
                            qw,
                            mw));

                        x += sw;
                    }
                }
            }
        }
    }
    break;
    }
}

void ItemCircle::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);

    const Circle::ShowCircleType st = show.valueEnum<Circle::ShowCircleType>(_timeStep);

    switch (st)
    {
    case Circle::CircleHidden: break;
    case Circle::CircleFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialBase::circle(o, r, q, materialFront.value(_timeStep), a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(o.invert12(), r, q, materialBack.value(_timeStep), a));
        }
    }
    break;
    case Circle::CircleFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::circle(o, r, q, materialFront.value(_timeStep), a));
    }
    break;
    case Circle::CircleBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::circle(o.invert12(), r, q, materialBack.value(_timeStep), a));
    }
    break;

    case Circle::CircleBorderFrontBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circle(
            o, r, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circle(
            o.invert12(), r, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;

    case Circle::CircleBorderFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circle(
            o, r, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        break;

    case Circle::CircleBorderBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circle(
            o.invert12(), r, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;
    }

    createCircleWires(_data, _timeStep, showWire, radiusWire, stepWire, qualityWire, materialWire, o, r, q);
}

ItemCircleCamera::ItemCircleCamera(const std::string &_name,
                                   const Math::Vec3F &_center,
                                   const float _radius,
                                   const size_t _quality,
                                   const Circle::ShowCircleCameraType _show,
                                   const Circle::ShowCircleWireType _showWire,
                                   const Math::MaterialRGB &_material,
                                   const Math::MaterialRGBA &_materialCenter,
                                   const Math::MaterialRGBA &_materialBorder,
                                   const Math::MaterialRGBA &_materialWire,
                                   const float _radiusWire,
                                   const float _stepWire,
                                   const size_t _qualityWire,
                                   const uint8_t _alpha,
                                   const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Circle::ShowCircleCameraType>(), _show)
    , material("material", _material)
    , materialCenter("materialCenter", _materialCenter)
    , materialBorder("materialBorder", _materialBorder)
    , showWire("showWire", QMetaEnum::fromType<Circle::ShowCircleWireType>(), _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&center);
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&material);
    addProperty(&materialCenter);
    addProperty(&materialBorder);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

void ItemCircleCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                      const Math::CamF &_camera,
                                      const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const Math::OrientF o(_camera, center.value(_timeStep));
    const size_t q = quality.value(_timeStep);
    const Circle::ShowCircleCameraType st = show.valueEnum<Circle::ShowCircleCameraType>(_timeStep);

    switch (st)
    {
    case Circle::CircleCameraHidden: break;

    case Circle::CircleCameraSingle: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::circle(o, r, q, material.value(_timeStep), a));
    }
    break;

    case Circle::CircleCameraBorder:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circle(
            o, r, q, materialCenter.value(_timeStep), materialBorder.value(_timeStep)));
        break;
    }

    createCircleWires(_data, _timeStep, showWire, radiusWire, stepWire, qualityWire, materialWire, o, r, q);
}

}  // namespace Items
}  // namespace U1
