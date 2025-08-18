/*!
 * \file src/Items/Sphere/itemirregellipsoid.cpp
 * \brief Dynamic sphere video item
 */

#include "itemirregellipsoid.h"

#include "../../Data3D/data3dmaterialnormal.h"
#include "../../Data3D/data3dtexture.h"

namespace U1 {
namespace Items {

ItemIrregEllipsoid::ItemIrregEllipsoid(const std::string &_name,
                                       const Math::Vec3F &_center,
                                       const Math::Vec3F &_normal,
                                       const Math::Vec3F &_arm,
                                       const float _radius1P,
                                       const float _radius1M,
                                       const float _radius2P,
                                       const float _radius2M,
                                       const float _radius3P,
                                       const float _radius3M,
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
    , radius1P(_name + ".radius1P", _radius1P, 0.0f, std::numeric_limits<float>::max())
    , radius1M(_name + ".radius1M", _radius1M, 0.0f, std::numeric_limits<float>::max())
    , radius2P(_name + ".radius2P", _radius2P, 0.0f, std::numeric_limits<float>::max())
    , radius2M(_name + ".radius2M", _radius2M, 0.0f, std::numeric_limits<float>::max())
    , radius3P(_name + ".radius3P", _radius3P, 0.0f, std::numeric_limits<float>::max())
    , radius3M(_name + ".radius3M", _radius3M, 0.0f, std::numeric_limits<float>::max())
    , quality(_name + ".quality", _quality)
    , show(_name + ".show", QMetaEnum::fromType<Ellipsoid::ShowEllipsoidType>(), _show)
    , materialOuter(_name + ".materialOuter", _materialOuter)
    , materialInner(_name + ".materialInner", _materialInner)
    , textureImage(_name + ".textureImage", _textureImage)
    , showWire(_name + ".showWire", _showWire)
    , radiusWire(_name + ".radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire(_name + ".stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire(_name + ".qualityWire", _qualityWire)
    , materialWire(_name + ".materialWire", _materialWire)
{
    addProperty(&radius1P);
    addProperty(&radius1M);
    addProperty(&radius2P);
    addProperty(&radius2M);
    addProperty(&radius3P);
    addProperty(&radius3M);
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

void ItemIrregEllipsoid::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r1p = radius1P.value(_timeStep);
    if (!Math::isPositive(r1p))
        return;

    const float r1m = radius1M.value(_timeStep);
    if (!Math::isPositive(r1m))
        return;

    const float r2p = radius2P.value(_timeStep);
    if (!Math::isPositive(r2p))
        return;

    const float r2m = radius2M.value(_timeStep);
    if (!Math::isPositive(r2m))
        return;

    const float r3p = radius3P.value(_timeStep);
    if (!Math::isPositive(r3p))
        return;

    const float r3m = radius3M.value(_timeStep);
    if (!Math::isPositive(r3m))
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Ellipsoid::ShowEllipsoidType st = show.valueEnum<Ellipsoid::ShowEllipsoidType>(_timeStep);
    uint8_t a;

    switch (st)
    {
    case Ellipsoid::EllipsoidHidden: break;

    case Ellipsoid::EllipsoidInnerOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
            _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidInn(
                o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
        }
        break;

    case Ellipsoid::EllipsoidOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidInner:
        a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidInn(
                o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidTextureInnerOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
            {
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidInn(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
            }
            else
            {
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoid(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoidInn(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
            }
        }
        break;

    case Ellipsoid::EllipsoidTextureOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoid(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
        }
        break;

    case Ellipsoid::EllipsoidTextureInner:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidInn(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoidInn(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
        }
        break;

    case Ellipsoid::EllipsoidTextureSoccerBall:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(":/socer_ball.png");
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoid(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
        }
        break;

    case Ellipsoid::EllipsoidTextureSoccerEarth:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(":/earth.png");
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
                    o, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::irregEllipsoid(
                    new QOpenGLTexture(img), o, r1p, r1m, r2p, r2m, r3p, r3m, q, a));
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

    _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(o, r2p, r2m, r3p, r3m, rw, q, qw, mw));
    _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
        {o.center, o.normal2, o.normal3, o.normal1}, r3p, r3m, r1p, r1m, rw, q, qw, mw));
    _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
        {o.center, o.normal3, o.normal1, o.normal2}, r1p, r1m, r2p, r2m, rw, q, qw, mw));

    const float sw = stepWire.value(_timeStep);
    if (!Math::isPositive(sw))
        return;

    const float r1p2 = r1p * r1p;
    const float r1m2 = r1m * r1m;
    const float r2p2 = r2p * r2p;
    const float r2m2 = r2m * r2m;
    const float r3p2 = r3p * r3p;
    const float r3m2 = r3m * r3m;

    float x = sw;
    while (Math::isLessNotEqual(x, r1p))
    {
        const float X2 = x * x;
        const float R2P = std::sqrt(r2p2 * (1.0f - X2 / r1p2));
        const float R2M = std::sqrt(r2m2 * (1.0f - X2 / r1p2));
        const float R3P = std::sqrt(r3p2 * (1.0f - X2 / r1p2));
        const float R3M = std::sqrt(r3m2 * (1.0f - X2 / r1p2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center + o.normal1 * x, o.normal1, o.normal2, o.normal3}, R2P, R2M, R3P, R3M, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r1m))
    {
        const float X2 = x * x;
        const float R2P = std::sqrt(r2p2 * (1.0f - X2 / r1m2));
        const float R2M = std::sqrt(r2m2 * (1.0f - X2 / r1m2));
        const float R3P = std::sqrt(r3p2 * (1.0f - X2 / r1m2));
        const float R3M = std::sqrt(r3m2 * (1.0f - X2 / r1m2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center - o.normal1 * x, o.normal1, o.normal2, o.normal3}, R2P, R2M, R3P, R3M, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r2p))
    {
        const float X2 = x * x;
        const float R3P = std::sqrt(r3p2 * (1.0f - X2 / r2p2));
        const float R3M = std::sqrt(r3m2 * (1.0f - X2 / r2p2));
        const float R1P = std::sqrt(r1p2 * (1.0f - X2 / r2p2));
        const float R1M = std::sqrt(r1m2 * (1.0f - X2 / r2p2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center + o.normal2 * x, o.normal2, o.normal3, o.normal1}, R3P, R3M, R1P, R1M, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r2m))
    {
        const float X2 = x * x;
        const float R3P = std::sqrt(r3p2 * (1.0f - X2 / r2m2));
        const float R3M = std::sqrt(r3m2 * (1.0f - X2 / r2m2));
        const float R1P = std::sqrt(r1p2 * (1.0f - X2 / r2m2));
        const float R1M = std::sqrt(r1m2 * (1.0f - X2 / r2m2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center - o.normal2 * x, o.normal2, o.normal3, o.normal1}, R3P, R3M, R1P, R1M, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r3p))
    {
        const float X2 = x * x;
        const float R1P = std::sqrt(r1p2 * (1.0f - X2 / r3p2));
        const float R1M = std::sqrt(r1m2 * (1.0f - X2 / r3p2));
        const float R2P = std::sqrt(r2p2 * (1.0f - X2 / r3p2));
        const float R2M = std::sqrt(r2m2 * (1.0f - X2 / r3p2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center + o.normal3 * x, o.normal3, o.normal1, o.normal2}, R1P, R1M, R2P, R2M, rw, q, qw, mw));
        x += sw;
    }

    x = sw;
    while (Math::isLessNotEqual(x, r3m))
    {
        const float X2 = x * x;
        const float R1P = std::sqrt(r1p2 * (1.0f - X2 / r3m2));
        const float R1M = std::sqrt(r1m2 * (1.0f - X2 / r3m2));
        const float R2P = std::sqrt(r2p2 * (1.0f - X2 / r3m2));
        const float R2M = std::sqrt(r2m2 * (1.0f - X2 / r3m2));
        _data.push_back(OpenGL::Data3DMaterialNormal::pathIrregEllipse(
            {o.center - o.normal3 * x, o.normal3, o.normal1, o.normal2}, R1P, R1M, R2P, R2M, rw, q, qw, mw));
        x += sw;
    }
}

ItemIrregEllipsoidCut::ItemIrregEllipsoidCut(const std::string &_name,
                                             const Math::Vec3F &_center,
                                             const Math::Vec3F &_normal,
                                             const Math::Vec3F &_arm,
                                             const float _radius1P,
                                             const float _radius1M,
                                             const float _radius2P,
                                             const float _radius2M,
                                             const float _radius3P,
                                             const float _radius3M,
                                             const float _angleLonStart,
                                             const float _angleLonEnd,
                                             const float _angleLatStart,
                                             const float _angleLatEnd,
                                             const size_t _quality,
                                             const Ellipsoid::ShowEllipsoidCutType _show,
                                             const Math::MaterialRGB &_materialOuter,
                                             const Math::MaterialRGB &_materialInner,
                                             const uint8_t _alpha,
                                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius1P(_name + ".radius1P", _radius1P, 0.0f, std::numeric_limits<float>::max())
    , radius1M(_name + ".radius1M", _radius1M, 0.0f, std::numeric_limits<float>::max())
    , radius2P(_name + ".radius2P", _radius2P, 0.0f, std::numeric_limits<float>::max())
    , radius2M(_name + ".radius2M", _radius2M, 0.0f, std::numeric_limits<float>::max())
    , radius3P(_name + ".radius3P", _radius3P, 0.0f, std::numeric_limits<float>::max())
    , radius3M(_name + ".radius3M", _radius3M, 0.0f, std::numeric_limits<float>::max())
    , angleLonStart(_name + ".angleLonStart", _angleLonStart)
    , angleLonEnd(_name + ".angleLonEnd", _angleLonEnd)
    , angleLatStart(_name + ".angleLatStart", _angleLatStart, 0.0f, float(M_PI))
    , angleLatEnd(_name + ".angleLatEnd", _angleLatEnd, 0.0f, float(M_PI))
    , quality(_name + ".quality", _quality)
    , show(_name + ".show", QMetaEnum::fromType<Ellipsoid::ShowEllipsoidCutType>(), _show)
    , materialOuter(_name + ".materialOuter", _materialOuter)
    , materialInner(_name + ".materialInner", _materialInner)
{
    addProperty(&radius1P);
    addProperty(&radius1M);
    addProperty(&radius2P);
    addProperty(&radius2M);
    addProperty(&radius3P);
    addProperty(&radius3M);
    addProperty(&angleLonStart);
    addProperty(&angleLonEnd);
    addProperty(&angleLatStart);
    addProperty(&angleLatEnd);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialOuter);
    addProperty(&materialInner);
}

void ItemIrregEllipsoidCut::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);

    const float r1p = radius1P.value(_timeStep);
    if (!Math::isPositive(r1p))
        return;

    const float r1m = radius1M.value(_timeStep);
    if (!Math::isPositive(r1m))
        return;

    const float r2p = radius2P.value(_timeStep);
    if (!Math::isPositive(r2p))
        return;

    const float r2m = radius2M.value(_timeStep);
    if (!Math::isPositive(r2m))
        return;

    const float r3p = radius3P.value(_timeStep);
    if (!Math::isPositive(r3p))
        return;

    const float r3m = radius3M.value(_timeStep);
    if (!Math::isPositive(r3m))
        return;

    const float aas = angleLatStart.value(_timeStep);
    const float aae = angleLatEnd.value(_timeStep);
    if (Math::equals(aas, aae))
        return;

    float als = angleLonStart.value(_timeStep);
    float ale = angleLonEnd.value(_timeStep);
    if (Math::equals(als, ale))
        return;

    if (Math::isMoreOrEqual(std::abs(ale - als), _2PI))
    {
        als = 0.0f;
        ale = _2PI;
    }

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Ellipsoid::ShowEllipsoidCutType st = show.valueEnum<Ellipsoid::ShowEllipsoidCutType>(_timeStep);

    switch (st)
    {
    case Ellipsoid::EllipsoidCutInnerOuter:
        _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidArc(
            o, als, ale, aas, aae, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
        _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidArcInn(
            o, als, ale, aas, aae, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidCutOuter:
        _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidArc(
            o, als, ale, aas, aae, r1p, r1m, r2p, r2m, r3p, r3m, q, materialOuter.value(_timeStep), a));
        break;

    case Ellipsoid::EllipsoidCutInner:
        _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoidArcInn(
            o, als, ale, aas, aae, r1p, r1m, r2p, r2m, r3p, r3m, q, materialInner.value(_timeStep), a));
        break;
    }
}

}  // namespace Items
}  // namespace U1
