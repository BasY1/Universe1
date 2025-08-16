/*!
 * \file src/Items/BodyParts/Hand/itemhand.cpp
 * \brief Dynamic hand video item
 */

#include "itemhand.h"

#include "../../../Data3D/data3dmaterialbase.h"
#include "../../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

void ItemHand::createDataImpl(std::list<OpenGL::Data3D *> &_out, const size_t _timeStep) const
{
    createHand(_out, hand.value(_timeStep, valueOrientation(_timeStep)), alpha.value(_timeStep));
}

/*!
 * \brief Create finger part
 * \param _out Output data
 * \param _center Center point
 * \param _normal Major normal
 * \param _arm Secondary normal
 * \param _length Finger length
 * \param _radius1 Finger radius at begin
 * \param _radius2 Finger radius at end
 * \param _quality Finger circle quality
 * \param _material Material
 * \param _alpha Alpha
 * \param _isLast Flag - last part of finger
 * \return
 */
inline static void createFinger(std::list<OpenGL::Data3D *> &_out,
                                const Math::Vec3F &_center,
                                const Math::Vec3F &_normal,
                                const Math::Vec3F &_arm,
                                const float _length,
                                const float _radius1,
                                const float _radius2,
                                const size_t _quality,
                                const Math::MaterialRGB &_material,
                                const uint8_t _alpha,
                                const bool _isLast)
{
    const Math::Vec3F c1 = _center + _normal * (_radius1 * 2.0f);
    const Math::Vec3F c2 = _center + _normal * (_length - (_isLast ? 1.0f : 2.0f) * _radius2);
    const float lc = _length - 2.0f * _radius1 - (_isLast ? 1.0f : 2.0f) * _radius2;
    _out.push_back(OpenGL::Data3DMaterialNormal::cylinder(
        {c1, _normal, _arm}, lc, _radius1, _radius2, _quality, _material, _alpha));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
        {c1, -_normal, _arm}, 0, 2.0 * M_PI, 0, M_PI_2, _radius1, _quality, _material, _alpha));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
        {c2, _normal, _arm}, 0, 2.0 * M_PI, 0, M_PI_2, _radius2, _quality, _material, _alpha));
}

void ItemHand::createHand(std::list<OpenGL::Data3D *> &_out,
                          const Math::OrientF &o,
                          const bool rh,
                          const float _size,
                          const float _openFingerThumb,
                          const float _openFingerIndex,
                          const float _openFingerMiddle,
                          const float _openFingerRing,
                          const float _openFingerLittle,
                          const size_t _quality,
                          const Math::MaterialRGB &m1,
                          const Math::MaterialRGB &m2,
                          const uint8_t a)
{
    if (!Math::isPositive(_size) || a == 0U)
        return;

    const float a11 = _openFingerThumb * M_PI_2;
    const float a21 = _openFingerIndex * M_PI_2 * 0.9;
    const float a31 = _openFingerMiddle * M_PI_2 * 0.9;
    const float a41 = _openFingerRing * M_PI_2 * 0.95;
    const float a51 = _openFingerLittle * M_PI_2;

    const float a22 = _openFingerIndex * M_PI_2 * 1.1;
    const float a32 = _openFingerMiddle * M_PI_2 * 1.1;
    const float a42 = _openFingerRing * M_PI_2 * 1.05;
    const float a52 = _openFingerLittle * M_PI_2;

    const float a23 = _openFingerIndex * M_PI_2 * 0.9;
    const float a33 = _openFingerMiddle * M_PI_2 * 0.9;
    const float a43 = _openFingerRing * M_PI_2 * 0.95;
    const float a53 = _openFingerLittle * M_PI_2;

    const float rd = _size * 0.02;
    const float rb = _size * 0.07;
    const float r11 = _size * 0.07;
    const float r21 = _size * 0.07;
    const float r31 = _size * 0.07;
    const float r41 = _size * 0.07;
    const float r51 = _size * 0.065;

    const float r12 = _size * 0.065;
    const float r22 = _size * 0.065;
    const float r32 = _size * 0.065;
    const float r42 = _size * 0.065;
    const float r52 = _size * 0.055;

    const float r23 = _size * 0.06;
    const float r33 = _size * 0.06;
    const float r43 = _size * 0.06;
    const float r53 = _size * 0.05;

    const float l11 = _size * 0.35;
    const float l21 = _size * 0.38;
    const float l31 = _size * 0.40;
    const float l41 = _size * 0.38;
    const float l51 = _size * 0.32;

    const float l12 = _size * 0.28;
    const float l22 = _size * 0.32;
    const float l32 = _size * 0.35;
    const float l42 = _size * 0.32;
    const float l52 = _size * 0.28;

    const float l23 = _size * 0.23;
    const float l33 = _size * 0.25;
    const float l43 = _size * 0.23;
    const float l53 = _size * 0.20;

    const float ss = rh ? 1.0f : -1.0f;

    const float ww = r21 + r51 + 2.0f * (r31 + r41) + 3.0f * rd;
    const float hh = _size * 0.6;

    const Math::Vec3F k11 = o.center + o.normal2 * (r11 + r21) - o.normal3 * (_size * 0.5f);
    const Math::Vec3F k21 = o.center;
    const Math::Vec3F k31 = o.center - o.normal2 * (r21 + r31 + rd);
    const Math::Vec3F k41 = k31 - o.normal2 * (r31 + r41 + rd);
    const Math::Vec3F k51 = k41 - o.normal2 * (r41 + r51 + rd);

    const Math::Vec3F arm11 = o.normal2.rotated(o.normal1, a11).normalized();
    const Math::Vec3F arm21 = o.normal3.rotated(o.normal2, ss * a21).normalized();
    const Math::Vec3F arm31 = o.normal3.rotated(o.normal2, ss * a31).normalized();
    const Math::Vec3F arm41 = o.normal3.rotated(o.normal2, ss * a41).normalized();
    const Math::Vec3F arm51 = o.normal3.rotated(o.normal2, ss * a51).normalized();

    const Math::Vec3F k12 = k11 + arm11 * l11;
    const Math::Vec3F k22 = k21 + arm21 * l21;
    const Math::Vec3F k32 = k31 + arm31 * l31;
    const Math::Vec3F k42 = k41 + arm41 * l41;
    const Math::Vec3F k52 = k51 + arm51 * l51;

    const Math::Vec3F arm22 = arm21.rotated(o.normal2, ss * a22).normalized();
    const Math::Vec3F arm32 = arm31.rotated(o.normal2, ss * a32).normalized();
    const Math::Vec3F arm42 = arm41.rotated(o.normal2, ss * a42).normalized();
    const Math::Vec3F arm52 = arm51.rotated(o.normal2, ss * a52).normalized();

    const Math::Vec3F k23 = k22 + arm22 * l22;
    const Math::Vec3F k33 = k32 + arm32 * l32;
    const Math::Vec3F k43 = k42 + arm42 * l42;
    const Math::Vec3F k53 = k52 + arm52 * l52;

    const Math::Vec3F arm23 = arm22.rotated(o.normal2, ss * a23).normalized();
    const Math::Vec3F arm33 = arm32.rotated(o.normal2, ss * a33).normalized();
    const Math::Vec3F arm43 = arm42.rotated(o.normal2, ss * a43).normalized();
    const Math::Vec3F arm53 = arm52.rotated(o.normal2, ss * a53).normalized();

    const Math::Vec3F p0 = o.center - o.normal3 * (rb * 2.0f);
    const Math::Vec3F p1 = p0 - o.normal2 * ww;
    const Math::Vec3F p2 = p1 - o.normal3 * hh;
    const Math::Vec3F p3 = p0 - o.normal3 * hh;
    const Math::Vec3F d = o.normal1 * rb;

    _out.push_back(OpenGL::Data3DMaterialBase::rectangle(p0 + d, p1 + d, p2 + d, p3 + d, m1, a));
    _out.push_back(OpenGL::Data3DMaterialBase::rectangle(p0 - d, p3 - d, p2 - d, p1 - d, m1, a));

    _out.push_back(OpenGL::Data3DMaterialNormal::cylinder({p0, -o.normal2, o.normal1}, ww, rb, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::cylinder({p2, o.normal2, o.normal1}, ww, rb, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::cylinder({p0, -o.normal3, -o.normal1}, hh, rb, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::cylinder({p2, o.normal3, -o.normal1}, hh, rb, rb, _quality, m1, a));

    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({p0, o.normal1, o.normal3}, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({p1, o.normal1, -o.normal2}, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({p2, o.normal1, -o.normal3}, rb, _quality, m1, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({p3, o.normal1, o.normal2}, rb, _quality, m1, a));

    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k11, o.normal1, o.normal2, o.normal3}, r11, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k21, o.normal1, o.normal2, o.normal3}, r21, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k31, o.normal1, o.normal2, o.normal3}, r31, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k41, o.normal1, o.normal2, o.normal3}, r41, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k51, o.normal1, o.normal2, o.normal3}, r51, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k12, o.normal1, o.normal2, o.normal3}, r12, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k22, o.normal1, o.normal2, o.normal3}, r22, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k32, o.normal1, o.normal2, o.normal3}, r32, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k42, o.normal1, o.normal2, o.normal3}, r42, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k52, o.normal1, o.normal2, o.normal3}, r52, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k23, o.normal1, o.normal2, o.normal3}, r23, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k33, o.normal1, o.normal2, o.normal3}, r33, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k43, o.normal1, o.normal2, o.normal3}, r43, _quality, m2, a));
    _out.push_back(OpenGL::Data3DMaterialNormal::sphere({k53, o.normal1, o.normal2, o.normal3}, r53, _quality, m2, a));

    createFinger(_out, k11, arm11, o.normal1, l11, r11, r12, _quality, m1, a, false);
    createFinger(_out, k12, arm11, o.normal1, l12, r12, r12 * 0.9, _quality, m1, a, true);

    createFinger(_out, k21, arm21, o.normal2, l21, r21, r22, _quality, m1, a, false);
    createFinger(_out, k22, arm22, o.normal2, l22, r22, r23, _quality, m1, a, false);
    createFinger(_out, k23, arm23, o.normal2, l23, r23, r23 * 0.9, _quality, m1, a, true);

    createFinger(_out, k31, arm31, o.normal2, l31, r31, r32, _quality, m1, a, false);
    createFinger(_out, k32, arm32, o.normal2, l32, r32, r33, _quality, m1, a, false);
    createFinger(_out, k33, arm33, o.normal2, l33, r33, r33 * 0.9, _quality, m1, a, true);

    createFinger(_out, k41, arm41, o.normal2, l41, r41, r42, _quality, m1, a, false);
    createFinger(_out, k42, arm42, o.normal2, l42, r42, r43, _quality, m1, a, false);
    createFinger(_out, k43, arm43, o.normal2, l43, r43, r43 * 0.9, _quality, m1, a, true);

    createFinger(_out, k51, arm51, o.normal2, l51, r51, r52, _quality, m1, a, false);
    createFinger(_out, k52, arm52, o.normal2, l52, r52, r53, _quality, m1, a, false);
    createFinger(_out, k53, arm53, o.normal2, l53, r53, r53 * 0.9, _quality, m1, a, true);
}

}  // namespace Items
}  // namespace U1
