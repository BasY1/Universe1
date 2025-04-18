/*!
 * \file src/Items/Sphere/itemellipsoid.cpp
 * \brief Dynamic sphere video item
 */

#include "itemellipsoid.h"

#include "../../Data3D/data3dmaterialnormal.h"
#include "../../Data3D/data3dtexture.h"

namespace U1 {
namespace Items {

ItemEllipsoid::ItemEllipsoid(const std::string &_name,
                             const Math::Vec3F &_center,
                             const Math::Vec3F &_normal,
                             const Math::Vec3F &_arm,
                             const float _radius1,
                             const float _radius2,
                             const float _radius3,
                             const size_t _quality,
                             const Ellipsoid::ShowEllipsoidType _show,
                             const bool _showWire,
                             const QString &_textureImage,
                             const Math::MaterialRGB &_materialOuter,
                             const Math::MaterialRGB &_materialInner,
                             const Math::MaterialRGBA &_materialWire,
                             const float _radiusWire,
                             const float _stepWire,
                             const size_t _qualityWire,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius1("radius1", _radius1, 0.0f, std::numeric_limits<float>::max())
    , radius2("radius2", _radius2, 0.0f, std::numeric_limits<float>::max())
    , radius3("radius3", _radius3, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Ellipsoid::ShowEllipsoidType>(), _show)
    , materialOuter("materialOuter", _materialOuter)
    , materialInner("materialInner", _materialInner)
    , textureImage("textureImage", _textureImage)
    , showWire("showWire", _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&radius1);
    addProperty(&radius2);
    addProperty(&radius3);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialOuter);
    addProperty(&materialInner);
    addProperty(&textureImage);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

void ItemEllipsoid::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
        return;

    const float r3 = radius3.value(_timeStep);
    if (!Math::isPositive(r3))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Ellipsoid::ShowEllipsoidType st = show.valueEnum<Ellipsoid::ShowEllipsoidType>(_timeStep);

    switch (st)
    {
    case Ellipsoid::EllipsoidHidden: break;

    case Ellipsoid::EllipsoidInnerOuter:
        _data.push_back(OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
        _data.push_back(
            OpenGL::Data3DMaterialNormal::ellipsoidInn(o, r1, r2, r3, q, materialInner.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidOuter:
        _data.push_back(OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidInner:
        _data.push_back(
            OpenGL::Data3DMaterialNormal::ellipsoidInn(o, r1, r2, r3, q, materialInner.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidTextureInnerOuter: {
        const QImage img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
        {
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoidInn(o, r1, r2, r3, q, materialInner.value(_timeStep), a));
        }
        else
        {
            _data.push_back(OpenGL::Data3DTexture::ellipsoid(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
            _data.push_back(OpenGL::Data3DTexture::ellipsoidInn(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
        }
    }
    break;

    case Ellipsoid::EllipsoidTextureOuter: {
        const QImage img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
        else
            _data.push_back(OpenGL::Data3DTexture::ellipsoid(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
    }
    break;

    case Ellipsoid::EllipsoidTextureInner: {
        const QImage img = QImage(textureImage.value(_timeStep));
        if (img.isNull())
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoidInn(o, r1, r2, r3, q, materialInner.value(_timeStep), a));
        else
            _data.push_back(OpenGL::Data3DTexture::ellipsoidInn(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
    }
    break;

    case Ellipsoid::EllipsoidTextureSoccerBall: {
        const QImage img = QImage(":/socer_ball.png");
        if (img.isNull())
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
        else
            _data.push_back(OpenGL::Data3DTexture::ellipsoid(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
    }
    break;

    case Ellipsoid::EllipsoidTextureSoccerEarth: {
        const QImage img = QImage(":/earth.png");
        if (img.isNull())
            _data.push_back(
                OpenGL::Data3DMaterialNormal::ellipsoid(o, r1, r2, r3, q, materialOuter.value(_timeStep), a));
        else
            _data.push_back(OpenGL::Data3DTexture::ellipsoid(new QOpenGLTexture(img), o, r1, r2, r3, q, a));
    }
    break;
    }

    if (!showWire.value(_timeStep))
        return;

    const float rw = radiusWire.value(_timeStep);
    if (!Math::isPositive(rw))
        return;

    const Math::MaterialRGBA mw = materialWire.value(_timeStep);
    if (mw.alpha == 0U)
        return;

    const size_t qw = qualityWire.value(_timeStep);

    _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(o, r2, r3, rw, q, qw, mw));
    _data.push_back(
        OpenGL::Data3DMaterialNormal::pathEllipse({o.center, o.normal2, o.normal3, o.normal1}, r3, r1, rw, q, qw, mw));
    _data.push_back(
        OpenGL::Data3DMaterialNormal::pathEllipse({o.center, o.normal3, o.normal1, o.normal2}, r1, r2, rw, q, qw, mw));

    const float sw = stepWire.value(_timeStep);
    if (!Math::isPositive(sw))
        return;

    const float r12 = r1 * r1;
    const float r22 = r2 * r2;
    const float r32 = r3 * r3;

    float x = sw;
    while (Math::isLessNotEqual(x, r1))
    {
        const float X2 = x * x;
        const float R2 = std::sqrt(r22 * (1.0f - X2 / r12));
        const float R3 = std::sqrt(r32 * (1.0f - X2 / r12));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center + o.normal1 * x, o.normal1, o.normal2, o.normal3}, R2, R3, rw, q, qw, mw));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center - o.normal1 * x, o.normal1, o.normal2, o.normal3}, R2, R3, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r2))
    {
        const float X2 = x * x;
        const float R1 = std::sqrt(r12 * (1.0f - X2 / r22));
        const float R3 = std::sqrt(r32 * (1.0f - X2 / r22));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center + o.normal2 * x, o.normal2, o.normal3, o.normal1}, R3, R1, rw, q, qw, mw));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center - o.normal2 * x, o.normal2, o.normal3, o.normal1}, R3, R1, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r3))
    {
        const float X2 = x * x;
        const float R1 = std::sqrt(r12 * (1.0f - X2 / r32));
        const float R2 = std::sqrt(r22 * (1.0f - X2 / r32));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center + o.normal3 * x, o.normal3, o.normal1, o.normal2}, R1, R2, rw, q, qw, mw));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathEllipse(
            {o.center - o.normal3 * x, o.normal3, o.normal1, o.normal2}, R1, R2, rw, q, qw, mw));
        x += sw;
    }
}

}  // namespace Items
}  // namespace U1
