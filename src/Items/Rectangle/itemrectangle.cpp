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
                             const bool _showWire,
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
    , showWire("showWire", _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
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
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

void ItemRectangle::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    Math::OrientF o = valueOrientation(_timeStep);
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
        return;

    Rectangle::ShowRectangleType st = show.valueEnum<Rectangle::ShowRectangleType>(_timeStep);

    QImage img;
    switch (st)
    {
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
    case Rectangle::RectangleFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, materialFront.value(_timeStep), a));
            o.normal1.invert();
            o.normal2.invert();
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, materialBack.value(_timeStep), a));
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
        {
            o.normal1.invert();
            o.normal2.invert();
            _data.push_back(OpenGL::Data3DMaterialBase::rectangle(o, r1, r2, materialBack.value(_timeStep), a));
        }
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
        o.normal1.invert();
        o.normal2.invert();
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o,
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
        o.normal1.invert();
        o.normal2.invert();
        _data.push_back(OpenGL::Data3DMaterialsAlpha::rectangle(o,
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

    if (showWire.value(_timeStep))
    {
        const float r = radiusWire.value(_timeStep);
        if (Math::isPositive(r))
        {
            const Math::MaterialRGBA mw = materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t q = qualityWire.value(_timeStep);
                const Math::Vec3F p1 = o.center - o.normal2 * r1 + o.normal3 * r2;
                const Math::Vec3F p2 = o.center - o.normal2 * r1 - o.normal3 * r2;
                const Math::Vec3F p3 = o.center + o.normal2 * r1 - o.normal3 * r2;
                const Math::Vec3F p4 = o.center + o.normal2 * r1 + o.normal3 * r2;
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, r, r, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, r, r, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, r, r, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, r, r, q, mw));
            }
        }
    }
}

}  // namespace Items
}  // namespace U1
