/*!
 * \file src/Items/Rectangle/itemrectangle.cpp
 * \brief Dynamic rectangle video item
 */

#include "itemrectangle.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"
#include "../../Data3D/data3dmaterialnormal.h"
#include "../../Data3D/data3dtexture.h"

namespace U1 {
namespace Items {

ItemRectangle::ItemRectangle(const std::string &_name,
                             const Math::Vec3F &_center,
                             const Math::Vec3F &_normal,
                             const Math::Vec3F &_arm,
                             const float _radius1,
                             const float _radius2,
                             const Rectangle::ShowRectangleType _show,
                             const Rectangle::ShowRectangleWireType _showWire,
                             const QString &_textureImage,
                             const Math::MaterialRGB &_materialFront,
                             const Math::MaterialRGB &_materialBack,
                             const Math::MaterialRGBA &_material1Front,
                             const Math::MaterialRGBA &_material2Front,
                             const Math::MaterialRGBA &_material3Front,
                             const Math::MaterialRGBA &_material4Front,
                             const Math::MaterialRGBA &_material1Back,
                             const Math::MaterialRGBA &_material2Back,
                             const Math::MaterialRGBA &_material3Back,
                             const Math::MaterialRGBA &_material4Back,
                             const Math::MaterialRGBA &_materialWire,
                             const float _radiusWire,
                             const float _stepWire,
                             const size_t _qualityWire,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius1("radius1", _radius1, 0.0f, std::numeric_limits<float>::max())
    , radius2("radius2", _radius2, 0.0f, std::numeric_limits<float>::max())
    , show("show", QMetaEnum::fromType<Rectangle::ShowRectangleType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , material1Front("material1Front", _material1Front)
    , material2Front("material2Front", _material2Front)
    , material3Front("material3Front", _material3Front)
    , material4Front("material4Front", _material4Front)
    , material1Back("material1Back", _material1Back)
    , material2Back("material2Back", _material2Back)
    , material3Back("material3Back", _material3Back)
    , material4Back("material4Back", _material4Back)
    , textureImage("textureImage", _textureImage)
    , showWire("showWire", QMetaEnum::fromType<Rectangle::ShowRectangleWireType>(), _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&radius1);
    addProperty(&radius2);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&material1Front);
    addProperty(&material2Front);
    addProperty(&material3Front);
    addProperty(&material4Front);
    addProperty(&material1Back);
    addProperty(&material2Back);
    addProperty(&material3Back);
    addProperty(&material4Back);
    addProperty(&textureImage);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

/*!
 * \brief Create rectangle wire-frame 3D data
 * \param _data Output data objects
 * \param _timeStep Time-step
 * \param _showWire Show rectangle wire-frame mode
 * \param _radiusWire Wire radius
 * \param _stepWire Wire-frame matrix step
 * \param _qualityWire Wire circle quality
 * \param _materialWire Wire-frame material
 * \param _orientation Orientation
 * \param _radius1 Rectangle radius 1
 * \param _radius2 Rectangle radius 2
 * \return
 */
static void createRectangleWires(std::list<OpenGL::Data3D *> &_data,
                                 const size_t _timeStep,
                                 const Props::ItemPropertyEnum &_showWire,
                                 const Props::ItemPropertyFloat &_radiusWire,
                                 const Props::ItemPropertyFloat &_stepWire,
                                 const Props::ItemPropertyQuality &_qualityWire,
                                 const Props::ItemPropertyMaterialRGBA &_materialWire,
                                 const Math::OrientF &_orientation,
                                 const float _radius1,
                                 const float _radius2)
{
    switch (_showWire.valueEnum<Rectangle::ShowRectangleWireType>(_timeStep))
    {
    case Rectangle::RectangleWireHidden: break;
    case Rectangle::RectangleWireBorder: {
        const float rw = _radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const Math::MaterialRGBA mw = _materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t q = _qualityWire.value(_timeStep);
                const Math::Vec3F p1 =
                    _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2;
                const Math::Vec3F p2 =
                    _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2;
                const Math::Vec3F p3 =
                    _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2;
                const Math::Vec3F p4 =
                    _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2;
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, rw, rw, q, mw));
            }
        }
    }
    break;

    case Rectangle::RectangleWireFull: {
        float rw = _radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const Math::MaterialRGBA mw = _materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t q = _qualityWire.value(_timeStep);
                const Math::Vec3F p1 =
                    _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2;
                const Math::Vec3F p2 =
                    _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2;
                const Math::Vec3F p3 =
                    _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2;
                const Math::Vec3F p4 =
                    _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2;
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, rw, rw, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, rw, rw, q, mw));

                const float sw = _stepWire.value(_timeStep);
                if (Math::isPositive(sw))
                {
                    rw *= 0.8f;
                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::line(_orientation.center - _orientation.normal2 * _radius1,
                                                           _orientation.center + _orientation.normal2 * _radius1,
                                                           rw,
                                                           rw,
                                                           q,
                                                           mw));

                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::line(_orientation.center - _orientation.normal3 * _radius2,
                                                           _orientation.center + _orientation.normal3 * _radius2,
                                                           rw,
                                                           rw,
                                                           q,
                                                           mw));

                    float x = sw;
                    while (Math::isLessNotEqual(x, _radius1))
                    {
                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center - _orientation.normal2 * x - _orientation.normal3 * _radius2,
                            _orientation.center - _orientation.normal2 * x + _orientation.normal3 * _radius2,
                            rw,
                            rw,
                            q,
                            mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center + _orientation.normal2 * x - _orientation.normal3 * _radius2,
                            _orientation.center + _orientation.normal2 * x + _orientation.normal3 * _radius2,
                            rw,
                            rw,
                            q,
                            mw));

                        x += sw;
                    }

                    x = sw;

                    while (Math::isLessNotEqual(x, _radius2))
                    {
                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * x,
                            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * x,
                            rw,
                            rw,
                            q,
                            mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::line(
                            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * x,
                            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * x,
                            rw,
                            rw,
                            q,
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

void ItemRectangle::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
        return;

    Math::OrientF o = valueOrientation(_timeStep);

    Rectangle::ShowRectangleType st = show.valueEnum<Rectangle::ShowRectangleType>(_timeStep);

    QImage img;
    switch (st)
    {
    case Rectangle::RectangleHidden:
    case Rectangle::RectangleFrontBack:
    case Rectangle::RectangleFront:
    case Rectangle::RectangleBack:
    case Rectangle::RectangleVertexFrontBack:
    case Rectangle::RectangleVertexFront:
    case Rectangle::RectangleVertexBack: break;
    case Rectangle::RectangleTextureFrontBack:
        img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            st = Rectangle::RectangleFrontBack;
        break;
    case Rectangle::RectangleTextureFront:
        img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            st = Rectangle::RectangleFront;
        break;
    case Rectangle::RectangleTextureBack:
        img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            st = Rectangle::RectangleBack;
        break;
    }

    switch (st)
    {
    case Rectangle::RectangleHidden: break;
    case Rectangle::RectangleFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, materialFront.value(_timeStep), a));
            _data.push_back(
                OpenGL::Data3DMaterialBase::rectangle(o.invert12(), r1, r2, materialBack.value(_timeStep), a));
        }
    }
    break;

    case Rectangle::RectangleFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, materialFront.value(_timeStep), a));
    }
    break;

    case Rectangle::RectangleBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(
                OpenGL::Data3DMaterialBase::rectangle(o.invert12(), r1, r2, materialBack.value(_timeStep), a));
    }
    break;

    case Rectangle::RectangleVertexFrontBack: {
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o,
                                                                r1,
                                                                r2,
                                                                material1Front.value(_timeStep),
                                                                material2Front.value(_timeStep),
                                                                material3Front.value(_timeStep),
                                                                material4Front.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o.invert12(),
                                                                r1,
                                                                r2,
                                                                material4Back.value(_timeStep),
                                                                material3Back.value(_timeStep),
                                                                material2Back.value(_timeStep),
                                                                material1Back.value(_timeStep)));
    }
    break;

    case Rectangle::RectangleVertexFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o,
                                                                r1,
                                                                r2,
                                                                material1Front.value(_timeStep),
                                                                material2Front.value(_timeStep),
                                                                material3Front.value(_timeStep),
                                                                material4Front.value(_timeStep)));
        break;

    case Rectangle::RectangleVertexBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o.invert12(),
                                                                r1,
                                                                r2,
                                                                material4Back.value(_timeStep),
                                                                material3Back.value(_timeStep),
                                                                material2Back.value(_timeStep),
                                                                material1Back.value(_timeStep)));
        break;

    case Rectangle::RectangleTextureFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DTexture::rectangle(new QOpenGLTexture(img), o, r1, r2, a));
            _data.push_back(OpenGL::Data3DTexture::rectangleInverted(new QOpenGLTexture(img), o, r1, r2, a));
        }
    }
    break;

    case Rectangle::RectangleTextureFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DTexture::rectangle(new QOpenGLTexture(img), o, r1, r2, a));
    }
    break;
    case Rectangle::RectangleTextureBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DTexture::rectangleInverted(new QOpenGLTexture(img), o, r1, r2, a));
    }
    break;
    }

    createRectangleWires(_data, _timeStep, showWire, radiusWire, stepWire, qualityWire, materialWire, o, r1, r2);
}

ItemRectangleCamera::ItemRectangleCamera(const std::string &_name,
                                         const Math::Vec3F &_center,
                                         const float _radius1,
                                         const float _radius2,
                                         const float _spin,
                                         const Rectangle::ShowRectangleCameraType _show,
                                         const Rectangle::ShowRectangleWireType _showWire,
                                         const QString &_textureImage,
                                         const Math::MaterialRGB &_material,
                                         const Math::MaterialRGBA &_material1,
                                         const Math::MaterialRGBA &_material2,
                                         const Math::MaterialRGBA &_material3,
                                         const Math::MaterialRGBA &_material4,
                                         const Math::MaterialRGBA &_materialWire,
                                         const float _radiusWire,
                                         const float _stepWire,
                                         const size_t _qualityWire,
                                         const uint8_t _alpha,
                                         const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , radius1("radius1", _radius1, 0.0f, std::numeric_limits<float>::max())
    , radius2("radius2", _radius2, 0.0f, std::numeric_limits<float>::max())
    , spin("spin", _spin)
    , show("show", QMetaEnum::fromType<Rectangle::ShowRectangleCameraType>(), _show)
    , material("material", _material)
    , material1("material1", _material1)
    , material2("material2", _material2)
    , material3("material3", _material3)
    , material4("material4", _material4)
    , textureImage("textureImage", _textureImage)
    , showWire("showWire", QMetaEnum::fromType<Rectangle::ShowRectangleWireType>(), _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&center);
    addProperty(&radius1);
    addProperty(&radius2);
    addProperty(&spin);
    addProperty(&show);
    addProperty(&material);
    addProperty(&material1);
    addProperty(&material2);
    addProperty(&material3);
    addProperty(&material4);
    addProperty(&textureImage);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

void ItemRectangleCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                         const Math::CamF &_camera,
                                         const size_t _timeStep) const
{
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
        return;

    const Math::OrientF o(_camera, center.value(_timeStep), spin.value(_timeStep));

    Rectangle::ShowRectangleCameraType st = show.valueEnum<Rectangle::ShowRectangleCameraType>(_timeStep);

    QImage img;
    switch (st)
    {
    case Rectangle::RectangleCameraHidden: break;
    case Rectangle::RectangleCameraSingle: break;
    case Rectangle::RectangleCameraVertex: break;
    case Rectangle::RectangleCameraTexture:
        img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            st = Rectangle::RectangleCameraSingle;
        break;
    }

    switch (st)
    {
    case Rectangle::RectangleCameraHidden: break;

    case Rectangle::RectangleCameraSingle: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, material.value(_timeStep), a));
    }
    break;

    case Rectangle::RectangleCameraVertex:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o,
                                                                r1,
                                                                r2,
                                                                material1.value(_timeStep),
                                                                material2.value(_timeStep),
                                                                material3.value(_timeStep),
                                                                material4.value(_timeStep)));
        break;

    case Rectangle::RectangleCameraTexture: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DTexture::rectangle(new QOpenGLTexture(img), o, r1, r2, a));
    }
    break;
    }

    createRectangleWires(_data, _timeStep, showWire, radiusWire, stepWire, qualityWire, materialWire, o, r1, r2);
}

}  // namespace Items
}  // namespace U1
