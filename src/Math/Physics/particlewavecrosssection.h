/*!
 * \file src/Math/Physics/particlewavecrosssection.h
 * \brief 3D Sphere cross-section tools
 */

#ifndef PHYSICS_PARTICLEWAVECROSSSECTION_H
#define PHYSICS_PARTICLEWAVECROSSSECTION_H

#include "../vec3.h"

namespace U1 {
namespace Math {

/*!
 * \brief Cross-section type
 * \details Information about wave's sphere against particle's sphere
 */
enum ParticleWaveCrossSectionType : int
{
    CROSS_INVALID = 0,        //!< Invalid cross-section
    CROSS_WAVE_MISS_BEFORE,   //!< Wave is before particle (Wave needs to grow to hit particle)
    CROSS_WAVE_TOUCH_BEFORE,  //!< Wave sphere touch particle's border (Growing wave will cross particle)
    CROSS_WAVE_CROSSES,       //!< Wave sphere cross particle's sphere
    CROSS_WAVE_TOUCH_AFTER,   //!< Wave sphere touch particle's border (Growing wave will pass particle ("miss after"))
    CROSS_WAVE_MISS_AFTER,    //!< Wave is after particle (Wave passed particle)
};

/*!
 * \brief Two spheres cross-section representation
 * \tparam T Template floating point type
 */
template <typename T>
struct ParticleWaveCrossSection
{
    const Vec3<T> particlePosition;  //!< Particle sphere center position
    const Vec3<T> wavePosition;      //!< Wave sphere center position

    const T waveRadius;      //!< Wave sphere radius
    const T particleRadius;  //!< Particle sphere radius

    ParticleWaveCrossSectionType crossSectionType;  //!< Cross-section type

    bool waveInsideParticle;  //!< Wave central position status flag

    T positionDistance;  //!< Distance between wave's and particle's sphere center position
    T cosAngle;          //!< Co-sine of cross-section angle

    ParticleWaveCrossSection(const Vec3<T> &_particlePosition,
                             const Vec3<T> &_wavePosition,
                             const T _waveRadius,
                             const T _particleRadius = T(1));

    inline Vec3<T> directionToWave() const;

    inline bool isValid() const;
    inline bool isTouch() const;

    inline T angleRad() const;
    inline T angleDeg() const;

    T crossSectionVolume() const;
    T crossSectionVolumeRatio() const;
    T crossSectionArea() const;
    T crossSectionAreaRatio() const;
    T ratio() const;
    T distanceOffset() const;

    Vec3<T> circleCenter() const;
    T circleRadius() const;
    Vec3<T> circleArm() const;
    Vec3<T> circleNormal() const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \tparam T Template floating point type
 * \param _particlePosition Particle center position
 * \param _wavePosition Wave center position
 * \param _waveRadius Wave radius
 * \param _particleRadius Particle radius
 */
template <typename T>
ParticleWaveCrossSection<T>::ParticleWaveCrossSection(const Vec3<T> &_particlePosition,
                                                      const Vec3<T> &_wavePosition,
                                                      const T _waveRadius,
                                                      const T _particleRadius)
    : particlePosition(_particlePosition)
    , wavePosition(_wavePosition)
    , waveRadius(_waveRadius)
    , particleRadius(_particleRadius)
    , crossSectionType(CROSS_INVALID)
    , waveInsideParticle(false)
    , positionDistance(T(0))
    , cosAngle(T(0))
{
    if (!isPositive(waveRadius) || !isPositive(particleRadius))
        return;

    positionDistance = particlePosition.distanceToPoint(wavePosition);

    if (Math::isNull<T>(positionDistance))
    {
        waveInsideParticle = true;

        if (Math::equals<T>(particleRadius, waveRadius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (particleRadius > waveRadius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (Math::equals<T>(positionDistance, particleRadius))
    {
        waveInsideParticle = true;
        const T diameter = T(2) * particleRadius;
        if (Math::equals<T>(waveRadius, diameter))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (waveRadius < diameter)
            crossSectionType = CROSS_WAVE_CROSSES;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (positionDistance < particleRadius)
    {

        waveInsideParticle = true;

        if (Math::equals<T>(positionDistance + waveRadius, particleRadius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Math::equals<T>(positionDistance + particleRadius, waveRadius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance + waveRadius < particleRadius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + particleRadius < waveRadius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSSES;
    }

    else
    {
        // waveInsideParticle = false;

        if (Math::equals<T>(positionDistance, particleRadius + waveRadius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Math::equals<T>(positionDistance + particleRadius, waveRadius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance > particleRadius + waveRadius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + particleRadius < waveRadius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSSES;
    }

    if (crossSectionType == CROSS_WAVE_CROSSES)
        cosAngle = Math::alignedToPM1<T>(
            (waveRadius * waveRadius + positionDistance * positionDistance - particleRadius * particleRadius) /
            (T(2) * waveRadius * positionDistance));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns direction to from particle to wave
 * \tparam T Template floating point type
 * \return Direction to from particle to wave
 */
template <typename T>
inline Vec3<T> ParticleWaveCrossSection<T>::directionToWave() const
{
    return (wavePosition - particlePosition).normalized();
}

/*!
 * \brief Test if sphere cross-section is valid
 * \tparam T Template floating point type
 * \return \c true if sphere cross-section is valid
 */
template <typename T>
inline bool ParticleWaveCrossSection<T>::isValid() const
{
    return crossSectionType != CROSS_INVALID;
}

/*!
 * \brief Test if wave sphere is touching particle sphere
 * \tparam T Template floating point type
 * \return \c true if wave sphere is touching particle sphere
 */
template <typename T>
inline bool ParticleWaveCrossSection<T>::isTouch() const
{
    switch (crossSectionType)
    {
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER: return true;
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_CROSSES:
    case CROSS_WAVE_MISS_AFTER: break;
    }
    return false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns angle of cross-section in radians
 * \tparam T Template floating point type
 * \return Angle of cross-section in radians
 */
template <typename T>
inline T ParticleWaveCrossSection<T>::angleRad() const
{
    return crossSectionType != CROSS_WAVE_CROSSES ? T(0) : std::acos(cosAngle);
}

/*!
 * \brief Returns angle of cross-section in degrees
 * \tparam T Template floating point type
 * \return Angle of cross-section in degrees
 */
template <typename T>
inline T ParticleWaveCrossSection<T>::angleDeg() const
{
    return toDeg<T>(angleRad());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns cross-section penetration volume
 * \tparam T Template floating point type
 * \return Cross-section penetration volume
 */
template <typename T>
T ParticleWaveCrossSection<T>::crossSectionVolume() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return T(0);

    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE: return (waveInsideParticle ? volumeSphere(waveRadius) : T(0));

    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return volumeSphere(particleRadius);

    case CROSS_WAVE_CROSSES:
        return volumeSphereCup(waveRadius, waveRadius * (T(1) - cosAngle)) +
            volumeSphereCup(particleRadius, particleRadius - positionDistance + waveRadius * cosAngle);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration volume ratio (against particle sphere volume)
 * \tparam T Template floating point type
 * \return Cross-section penetration volume ratio
 */
template <typename T>
T ParticleWaveCrossSection<T>::crossSectionVolumeRatio() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return T(0);

    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
        return (waveInsideParticle
                    ? (waveRadius * waveRadius * waveRadius) / (particleRadius * particleRadius * particleRadius)
                    : T(0));

    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return T(1);

    case CROSS_WAVE_CROSSES:
        return (volumeSphereCup(waveRadius, waveRadius * (T(1) - cosAngle)) +
                volumeSphereCup(particleRadius, particleRadius - positionDistance + waveRadius * cosAngle)) /
            volumeSphere(particleRadius);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration wave surface area
 * \tparam T Template floating point type
 * \return Cross-section penetration wave surface area
 */
template <typename T>
T ParticleWaveCrossSection<T>::crossSectionArea() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: return T(2) * T(M_PIl) * waveRadius * waveRadius * (T(1) - cosAngle);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration wave surface area ratio
 * \f$\frac{penetration area}{full wave sphere surface area}\f$
 * \tparam T Template floating point type
 * \return Cross-section penetration wave surface area ratio
 */
template <typename T>
T ParticleWaveCrossSection<T>::crossSectionAreaRatio() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: return T(0.5) * (T(1) - cosAngle);
    }
    return T(0);
}

/*!
 * \brief Axis-projected contribution factor
 * \tparam T Template floating point type
 * \return Cross-section ratio
 * \details
 * Axis-projected contribution factor
 * Returns cross-section ratio \f$\frac{1 - cos(\alpha)^2}{4}\f$
 */
template <typename T>
T ParticleWaveCrossSection<T>::ratio() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: return (T(1) - cosAngle * cosAngle) / T(4);
    }
    return T(0);
}

// cosAngle = Math::alignedToPM1<T>(
//     (waveRadius * waveRadius + positionDistance * positionDistance - particleRadius * particleRadius) /
//     (T(2) * waveRadius * positionDistance));

/*!
 * \brief Returns offset distance
 * \tparam T Template floating point type
 * \return Offset distance
 */
template <typename T>
T ParticleWaveCrossSection<T>::distanceOffset() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER: break;

    case CROSS_WAVE_MISS_BEFORE:
        if (waveInsideParticle)
            return particleRadius - (waveRadius + positionDistance);
        else
            return positionDistance - (waveRadius + particleRadius);

    case CROSS_WAVE_MISS_AFTER: return waveRadius - (particleRadius + positionDistance);

    case CROSS_WAVE_CROSSES:
        if (waveInsideParticle)
            return (waveRadius + positionDistance) - particleRadius;
        else
            return (waveRadius + particleRadius) - positionDistance;
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration circle center
 * \tparam T Template floating point type
 * \return Cross-section circle center
 */
template <typename T>
Vec3<T> ParticleWaveCrossSection<T>::circleCenter() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES:
        return wavePosition + (particlePosition - wavePosition).normalized() * (waveRadius * cosAngle);
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \return Cross-section circle arm
 */
template <typename T>
T ParticleWaveCrossSection<T>::circleRadius() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return T(0);
    case CROSS_WAVE_CROSSES: return waveRadius * std::sqrt(T(1) - cosAngle * cosAngle);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \return Cross-section circle arm
 */
template <typename T>
Vec3<T> ParticleWaveCrossSection<T>::circleArm() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES: {
        const Vec3<T> n = (particlePosition - wavePosition).normalized();
        const T r = waveRadius * std::sqrt(T(1) - cosAngle * cosAngle);
        return n.perpendicularNormal() * r;
    }
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle normal
 * \tparam T Template floating point type
 * \return Cross-section circle normal
 */
template <typename T>
Vec3<T> ParticleWaveCrossSection<T>::circleNormal() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES: return (particlePosition - wavePosition).normalized();
    }
    return Vec3<T>();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _scs Sphere cross-section
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const ParticleWaveCrossSection<T> &_scs)
{
    std::string tName;
    switch (_scs.crossSectionType)
    {
    case CROSS_INVALID: return _os << "[Invalid]";
    case CROSS_WAVE_MISS_BEFORE: tName = "Miss-Before"; break;
    case CROSS_WAVE_MISS_AFTER: tName = "Miss-After"; break;
    case CROSS_WAVE_TOUCH_BEFORE: tName = "Touch-Before"; break;
    case CROSS_WAVE_TOUCH_AFTER: tName = "Touch-After"; break;
    case CROSS_WAVE_CROSSES: tName = "Cross"; break;
    }

    _os << "[[" << (_scs.waveInsideParticle ? "In" : "Out") << '-' << tName << ']';
    _os << "Particle[" << _scs.particlePosition << ',' << _scs.particleRadius << ']';
    _os << "Wave[" << _scs.wavePosition << ',' << _scs.waveRadius << ']';
    _os << "Distance[" << _scs.positionDistance << ",Offset(" << _scs.distanceOffset() << ")]";
    if (_scs.crossSectionType == CROSS_WAVE_CROSSES)
    {
        _os << "Angle[" << _scs.angleDeg() << "deg]";
        _os << "Ratio[" << (_scs.ratio() * T(100)) << "%]";
        _os << "Area[" << _scs.crossSectionArea() << "(" << (_scs.crossSectionAreaRatio() * T(100)) << "%)]";
        _os << "Volume[" << _scs.crossSectionVolume() << "(" << (_scs.crossSectionVolumeRatio() * T(100)) << "%)]";
    }

    _os << ']';
    return _os;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef ParticleWaveCrossSection<float>
    ParticleWaveCrossSectionF;  //!< 32 bit floating point precision sphere cross-section
typedef ParticleWaveCrossSection<double>
    ParticleWaveCrossSectionD;  //!< 64 bit floating point precision sphere cross-section
typedef ParticleWaveCrossSection<long double>
    ParticleWaveCrossSectionL;  //!< 128 bit floating point precision sphere cross-section

}  // namespace Math
}  // namespace U1

#endif  // PHYSICS_PARTICLEWAVECROSSSECTION_H
