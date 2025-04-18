/*!
 * \file src/Items/Sphere/itemsphere.cpp
 * \brief Dynamic sphere video item
 */

#include "itemsphere.h"

#include "../../Data3D/data3dmaterialnormal.h"
#include "../../Data3D/data3dtexture.h"

namespace U1 {
namespace Items {

ItemSphere::ItemSphere(const std::string &_name,
                       const Math::Vec3F &_center,
                       const Math::Vec3F &_normal,
                       const Math::Vec3F &_arm,
                       const float _radius,
                       const size_t _quality,
                       const Sphere::ShowSphereType _show,
                       const Sphere::ShowSphereWireType _showWire,
                       const QString &_textureImage,
                       const Math::MaterialRGB &_materialOuter,
                       const Math::MaterialRGB &_materialInner,
                       const Math::MaterialRGBA &_materialWire,
                       const float _radiusWire,
                       const float _stepWire,
                       const size_t _qualityWire,
                       const size_t _qualityLatLong,
                       const uint8_t _alpha,
                       const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Sphere::ShowSphereType>(), _show)
    , materialOuter("materialOuter", _materialOuter)
    , materialInner("materialInner", _materialInner)
    , textureImage("textureImage", _textureImage)
    , showWire("showWire", QMetaEnum::fromType<Sphere::ShowSphereWireType>(), _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , stepWire("stepWire", _stepWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , qualityLatLong("qualityLatLong", _qualityLatLong)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialOuter);
    addProperty(&materialInner);
    addProperty(&textureImage);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&stepWire);
    addProperty(&qualityWire);
    addProperty(&qualityLatLong);
    addProperty(&materialWire);
}

/*!
 * \brief Create sphere wire-frame shape
 * \param _data Output data
 * \param _orientation Sphere orientation
 * \param _radiusSphere Sphere radius
 * \param _radiusWire Wire radius
 * \param _angleStep Angle step
 * \param _quality Sphere quality
 * \param _qualityWire Wire circle quality
 * \param _material Wire material
 * \return
 */
static void createSphereWires(std::list<OpenGL::Data3D *> &_data,
                              const Math::OrientF &_orientation,
                              const float _radiusSphere,
                              const float _radiusWire,
                              const float _angleStep,
                              const size_t _quality,
                              const size_t _qualityWire,
                              const Math::MaterialRGBA &_material);

void ItemSphere::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    // const uint8_t a = alpha.value(_timeStep);
    // if (a == 0U)
    //     return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Sphere::ShowSphereType st = show.valueEnum<Sphere::ShowSphereType>(_timeStep);
    uint8_t a;

    switch (st)
    {
    case Sphere::SphereHidden: break;

    case Sphere::SphereInnerOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
            _data.push_back(OpenGL::Data3DMaterialNormal::sphereInn(o, r, q, materialInner.value(_timeStep), a));
        }
        break;

    case Sphere::SphereOuter:
        a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
        break;

    case Sphere::SphereInner:
        a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialNormal::sphereInn(o, r, q, materialInner.value(_timeStep), a));
        break;

    case Sphere::SphereTextureInnerOuter: {
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
            {
                _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
                _data.push_back(OpenGL::Data3DMaterialNormal::sphereInn(o, r, q, materialInner.value(_timeStep), a));
            }
            else
            {
                _data.push_back(OpenGL::Data3DTexture::sphere(new QOpenGLTexture(img), o, r, q, a));
                _data.push_back(OpenGL::Data3DTexture::sphereInn(new QOpenGLTexture(img), o, r, q, a));
            }
        }
    }
    break;

    case Sphere::SphereTextureOuter: {
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::sphere(new QOpenGLTexture(img), o, r, q, a));
        }
    }
    break;

    case Sphere::SphereTextureInner: {
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(textureImage.value(_timeStep));
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::sphereInn(o, r, q, materialInner.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::sphereInn(new QOpenGLTexture(img), o, r, q, a));
        }
    }
    break;

    case Sphere::SphereTextureSoccerBall: {
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(":/socer_ball.png");
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::sphere(new QOpenGLTexture(img), o, r, q, a));
        }
    }
    break;

    case Sphere::SphereTextureSoccerEarth: {
        a = alpha.value(_timeStep);
        if (a > 0U)
        {
            const QImage img = QImage(":/earth.png");
            if (img.isNull())
                _data.push_back(OpenGL::Data3DMaterialNormal::sphere(o, r, q, materialOuter.value(_timeStep), a));
            else
                _data.push_back(OpenGL::Data3DTexture::sphere(new QOpenGLTexture(img), o, r, q, a));
        }
    }
    break;
    }

    switch (showWire.valueEnum<Sphere::ShowSphereWireType>(_timeStep))
    {
    case Sphere::SphereWireHidden: break;
    case Sphere::SphereWireLatLongStep: {
        const float rw = radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const float sw = stepWire.value(_timeStep);
            if (Math::isPositive(sw))
            {
                const Math::MaterialRGBA mw = materialWire.value(_timeStep);
                if (mw.alpha > 0U)
                {
                    const size_t qw = qualityWire.value(_timeStep);
                    const float as = sw / r;
                    createSphereWires(_data, o, r, rw, as, q, qw, mw);
                }
            }
        }
    }
    break;
    case Sphere::SphereWireLatLongFixed: {
        const float rw = radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const Math::MaterialRGBA mw = materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t qw = qualityWire.value(_timeStep);
                const size_t ql = qualityLatLong.value(_timeStep);
                const float as = _2PI / float(Math::circlePointCount(ql));
                createSphereWires(_data, o, r, rw, as, q, qw, mw);
            }
        }
    }
    break;

    case Sphere::SphereWireXYZ: {
        const float rw = radiusWire.value(_timeStep);
        if (Math::isPositive(rw))
        {
            const float sw = stepWire.value(_timeStep);
            if (Math::isPositive(sw))
            {
                const Math::MaterialRGBA mw = materialWire.value(_timeStep);
                if (mw.alpha > 0U)
                {
                    const float r2 = r * r;
                    const size_t qw = qualityWire.value(_timeStep);
                    _data.push_back(OpenGL::Data3DMaterialNormal::torus(o, r, rw, q, qw, mw));
                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::torus({o.center, o.normal2, o.normal3}, r, rw, q, qw, mw));
                    _data.push_back(
                        OpenGL::Data3DMaterialNormal::torus({o.center, o.normal3, o.normal1}, r, rw, q, qw, mw));

                    float x = sw;
                    while (Math::isLessNotEqual(x, r))
                    {
                        const float rr = std::sqrt(r2 - x * x);
                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center + o.normal1 * x, o.normal1, o.normal2}, rr, rw, q, qw, mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center - o.normal1 * x, o.normal1, o.normal2}, rr, rw, q, qw, mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center + o.normal2 * x, o.normal2, o.normal3}, rr, rw, q, qw, mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center - o.normal2 * x, o.normal2, o.normal3}, rr, rw, q, qw, mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center + o.normal3 * x, o.normal3, o.normal1}, rr, rw, q, qw, mw));

                        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                            {o.center - o.normal3 * x, o.normal3, o.normal1}, rr, rw, q, qw, mw));
                        x += sw;
                    }
                }
            }
        }
    }
    break;
    }
}

static void createSphereWires(std::list<OpenGL::Data3D *> &_data,
                              const Math::OrientF &_orientation,
                              const float _radiusSphere,
                              const float _radiusWire,
                              const float _angleStep,
                              const size_t _quality,
                              const size_t _qualityWire,
                              const Math::MaterialRGBA &_material)
{
    static const float _2PI = float(2.0 * M_PI);
    static const float _PI2 = float(M_PI_2);

    const float rs2 = _radiusSphere * _radiusSphere;
    const float l = float(M_PI) * _radiusSphere;

    float angle = 0.0f;
    while (Math::isLessNotEqual(angle, _2PI))
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
            Math::OrientF(
                _orientation.center, _orientation.normal3.rotated(_orientation.normal1, angle), _orientation.normal1),
            l,
            _radiusSphere,
            _radiusWire,
            _radiusWire,
            _quality,
            _qualityWire,
            _material));

        angle += _angleStep;
    }

    angle = 0.0f;
    while (Math::isLessNotEqual(angle, _PI2))
    {
        const float x = std::sin(angle) * _radiusSphere;
        const float r = std::sqrt(rs2 - x * x);

        _data.push_back(OpenGL::Data3DMaterialNormal::torus(
            Math::OrientF(_orientation.center + _orientation.normal1 * x, _orientation.normal1, _orientation.normal2),
            r,
            _radiusWire,
            _quality,
            _qualityWire,
            _material));

        if (!Math::isNull(angle))
            _data.push_back(OpenGL::Data3DMaterialNormal::torus(
                Math::OrientF(
                    _orientation.center - _orientation.normal1 * x, _orientation.normal1, _orientation.normal2),
                r,
                _radiusWire,
                _quality,
                _qualityWire,
                _material));

        angle += _angleStep;
    }
}

ItemSphereCut::ItemSphereCut(const std::string &_name,
                             const Math::Vec3F &_center,
                             const Math::Vec3F &_normal,
                             const Math::Vec3F &_arm,
                             const float _radius,
                             const float _angleLonStart,
                             const float _angleLonEnd,
                             const float _angleLatStart,
                             const float _angleLatEnd,
                             const size_t _quality,
                             const Sphere::ShowSphereCutType _show,
                             const Math::MaterialRGB &_materialOuter,
                             const Math::MaterialRGB &_materialInner,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , angleLonStart("angleLonStart", _angleLonStart)
    , angleLonEnd("angleLonEnd", _angleLonEnd)
    , angleLatStart("angleLatStart", _angleLatStart, 0.0f, float(M_PI))
    , angleLatEnd("angleLatEnd", _angleLatEnd, 0.0f, float(M_PI))
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Sphere::ShowSphereCutType>(), _show)
    , materialOuter("materialOuter", _materialOuter)
    , materialInner("materialInner", _materialInner)
{
    addProperty(&radius);
    addProperty(&angleLonStart);
    addProperty(&angleLonEnd);
    addProperty(&angleLatStart);
    addProperty(&angleLatEnd);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialOuter);
    addProperty(&materialInner);
}

void ItemSphereCut::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);

    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
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
    const Sphere::ShowSphereCutType st = show.valueEnum<Sphere::ShowSphereCutType>(_timeStep);

    switch (st)
    {
    case Sphere::SphereCutInnerOuter:
        _data.push_back(
            OpenGL::Data3DMaterialNormal::sphereArc(o, als, ale, aas, aae, r, q, materialOuter.value(_timeStep), a));
        _data.push_back(
            OpenGL::Data3DMaterialNormal::sphereArcInn(o, als, ale, aas, aae, r, q, materialInner.value(_timeStep), a));
        break;

    case Sphere::SphereCutOuter:
        _data.push_back(
            OpenGL::Data3DMaterialNormal::sphereArc(o, als, ale, aas, aae, r, q, materialOuter.value(_timeStep), a));
        break;

    case Sphere::SphereCutInner:
        _data.push_back(
            OpenGL::Data3DMaterialNormal::sphereArcInn(o, als, ale, aas, aae, r, q, materialInner.value(_timeStep), a));
        break;
    }
}

}  // namespace Items
}  // namespace U1
