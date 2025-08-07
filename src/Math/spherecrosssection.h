/*!
 * \file src/Math/spherecrosssection.h
 * \brief 3D Sphere cross-section tools
 */

#ifndef MATH_SPHERECROSSSECTION_H
#define MATH_SPHERECROSSSECTION_H

#include "circle.h"
#include "sphere.h"

namespace U1 {
namespace Math {

/*!
 * \brief Cross-section type
 * \details Information about wave's sphere against particle's sphere
 */
enum SphereCrossSectionType : int
{
    CROSS_INVALID = 0,        //!< Invalid cross-section
    CROSS_WAVE_MISS_BEFORE,   //!< Wave is before particle (Wave needs to grow to hit particle)
    CROSS_WAVE_TOUCH_BEFORE,  //!< Wave sphere touch particle's border (Growing wave will cross particle)
    CROSS_WAVE_CROSSES,       //!< Wave sphere cross particle's sphere
    CROSS_WAVE_TOUCH_AFTER,   //!< Wave sphere touch particle's border (Growing wave will pass particle ("miss after"))
    CROSS_WAVE_MISS_AFTER,    //!< Wave is after particle (Wave passed particle)
};

/*!
 * \brief Sphere cross-section
 * \tparam T Template floating point type
 */
template <typename T>
struct SphereCrossSection
{
    const Sphere<T> particle;  //!< Particle sphere pointer
    const Sphere<T> wave;      //!< Wave sphere pointer

    SphereCrossSectionType crossSectionType;  //!< Cross-section type

    bool waveInsideParticle;  //!< Wave central position status flag

    T positionDistance;  //!< Distance between wave's and particle's sphere center position
    T cosAngle;          //!< Co-sine of cross-section angle

    SphereCrossSection(const Sphere<T> &_particle, const Sphere<T> &_wave);

    /*!
     * \brief Constructor
     * \param _particlePosition Particle center position
     * \param _wavePosition Wave center position
     * \param _waveRadius Wave radius
     * \param _particleRadius Particle radius
     */
    inline SphereCrossSection(const Vec3<T> &_particlePosition,
                              const Vec3<T> &_wavePosition,
                              const T _waveRadius,
                              const T _particleRadius = T(1))
        : SphereCrossSection(Sphere<T>(_particlePosition, _particleRadius), Sphere<T>(_wavePosition, _waveRadius))
    {
    }

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

    Circle3<T> circle() const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor from other sphere
 * \tparam T Template floating point type
 * \param _particle Particle sphere pointer
 * \param _wave Wave sphere pointer
 */
template <typename T>
SphereCrossSection<T>::SphereCrossSection(const Sphere<T> &_particle, const Sphere<T> &_wave)
    : particle(_particle)
    , wave(_wave)
    , crossSectionType(CROSS_INVALID)
    , waveInsideParticle(false)
    , positionDistance(T(0))
    , cosAngle(T(0))
{
    if (!particle.isValid() || !wave.isValid())
        return;

    positionDistance = particle.center.distanceToPoint(wave.center);

    if (Math::isNull<T>(positionDistance))
    {
        waveInsideParticle = true;

        if (Math::equals<T>(particle.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (particle.radius > wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (Math::equals<T>(positionDistance, particle.radius))
    {
        waveInsideParticle = true;
        const T diameter = T(2) * particle.radius;
        if (Math::equals<T>(wave.radius, diameter))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (wave.radius < diameter)
            crossSectionType = CROSS_WAVE_CROSSES;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (positionDistance < particle.radius)
    {

        waveInsideParticle = true;

        if (Math::equals<T>(positionDistance + wave.radius, particle.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Math::equals<T>(positionDistance + particle.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance + wave.radius < particle.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + particle.radius < wave.radius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSSES;
    }

    else
    {
        // waveInsideParticle = false;

        if (Math::equals<T>(positionDistance, particle.radius + wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Math::equals<T>(positionDistance + particle.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance > particle.radius + wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + particle.radius < wave.radius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSSES;
    }

    if (crossSectionType == CROSS_WAVE_CROSSES)
        cosAngle = Math::alignedToPM1<T>(
            (wave.radius * wave.radius + positionDistance * positionDistance - particle.radius * particle.radius) /
            (T(2) * wave.radius * positionDistance));
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
inline Vec3<T> SphereCrossSection<T>::directionToWave() const
{
    return (wave.center - particle.center).normalized();
}

/*!
 * \brief Test if sphere cross-section is valid
 * \tparam T Template floating point type
 * \return \c true if sphere cross-section is valid
 */
template <typename T>
inline bool SphereCrossSection<T>::isValid() const
{
    return crossSectionType != CROSS_INVALID;
}

/*!
 * \brief Test if wave sphere is touching particle sphere
 * \tparam T Template floating point type
 * \return \c true if wave sphere is touching particle sphere
 */
template <typename T>
inline bool SphereCrossSection<T>::isTouch() const
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
inline T SphereCrossSection<T>::angleRad() const
{
    return crossSectionType != CROSS_WAVE_CROSSES ? T(0) : std::acos(cosAngle);
}

/*!
 * \brief Returns angle of cross-section in degrees
 * \tparam T Template floating point type
 * \return Angle of cross-section in degrees
 */
template <typename T>
inline T SphereCrossSection<T>::angleDeg() const
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
T SphereCrossSection<T>::crossSectionVolume() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return T(0);

    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE: return (waveInsideParticle ? wave.volume() : T(0));

    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return particle.volume();

    case CROSS_WAVE_CROSSES:
        return wave.volumeCup(wave.radius * (T(1) - cosAngle)) +
            particle.volumeCup(particle.radius - positionDistance + wave.radius * cosAngle);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration volume ratio (against particle sphere volume)
 * \tparam T Template floating point type
 * \return Cross-section penetration volume ratio
 */
template <typename T>
T SphereCrossSection<T>::crossSectionVolumeRatio() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return T(0);

    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
        return (waveInsideParticle
                    ? (wave.radius * wave.radius * wave.radius) / (particle.radius * particle.radius * particle.radius)
                    : T(0));

    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return T(1);

    case CROSS_WAVE_CROSSES:
        return (wave.volumeCup(wave.radius * (T(1) - cosAngle)) +
                particle.volumeCup(particle.radius - positionDistance + wave.radius * cosAngle)) /
            particle.volume();
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration wave surface area
 * \tparam T Template floating point type
 * \return Cross-section penetration wave surface area
 */
template <typename T>
T SphereCrossSection<T>::crossSectionArea() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: return T(2) * T(M_PIl) * wave.radius * wave.radius * (T(1) - cosAngle);
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
T SphereCrossSection<T>::crossSectionAreaRatio() const
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
 * \brief Returns cross-section ratio \f$\frac{1 - cos(\alpha)^2}{4}\f$
 * \tparam T Template floating point type
 * \return Cross-section ratio
 */
template <typename T>
T SphereCrossSection<T>::ratio() const
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
/*!
 * \brief Returns offset distance
 * \tparam T Template floating point type
 * \return Offset distance
 */
template <typename T>
T SphereCrossSection<T>::distanceOffset() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER: break;

    case CROSS_WAVE_MISS_BEFORE:
        if (waveInsideParticle)
            return particle.radius - (wave.radius + positionDistance);
        else
            return positionDistance - (wave.radius + particle.radius);

    case CROSS_WAVE_MISS_AFTER: return wave.radius - (particle.radius + positionDistance);

    case CROSS_WAVE_CROSSES:
        if (waveInsideParticle)
            return (wave.radius + positionDistance) - particle.radius;
        else
            return (wave.radius + particle.radius) - positionDistance;
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration circle center
 * \tparam T Template floating point type
 * \return Cross-section circle center
 */
template <typename T>
Vec3<T> SphereCrossSection<T>::circleCenter() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES:
        return wave.center + (particle.center - wave.center).normalized() * (wave.radius * cosAngle);
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \return Cross-section circle arm
 */
template <typename T>
T SphereCrossSection<T>::circleRadius() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return T(0);
    case CROSS_WAVE_CROSSES: return wave.radius * std::sqrt(T(1) - cosAngle * cosAngle);
    }
    return T(0);
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \return Cross-section circle arm
 */
template <typename T>
Vec3<T> SphereCrossSection<T>::circleArm() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES: {
        const Vec3<T> n = (particle.center - wave.center).normalized();
        const T r = wave.radius * std::sqrt(T(1) - cosAngle * cosAngle);
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
Vec3<T> SphereCrossSection<T>::circleNormal() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return Vec3<T>();
    case CROSS_WAVE_CROSSES: return (particle.center - wave.center).normalized();
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle
 * \tparam T Template floating point type
 * \return Cross-section circle
 */
template <typename T>
Circle3<T> SphereCrossSection<T>::circle() const
{
    Circle3<T> result;
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: {
        result.normal = (particle.center - wave.center).normalized();
        result.center = wave.center + result.normal * (wave.radius * cosAngle);
        result.radius = wave.radius * std::sqrt(T(1) - cosAngle * cosAngle);
    }
    break;
    }
    return result;
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
inline std::ostream &operator<<(std::ostream &_os, const SphereCrossSection<T> &_scs)
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
    _os << "Particle" << _scs.particle;
    _os << "Wave" << _scs.wave;
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

typedef SphereCrossSection<float> SphereCrossSectionF;        //!< 32 bit floating point precision sphere cross-section
typedef SphereCrossSection<double> SphereCrossSectionD;       //!< 64 bit floating point precision sphere cross-section
typedef SphereCrossSection<long double> SphereCrossSectionL;  //!< 128 bit floating point precision sphere cross-section

}  // namespace Math
}  // namespace U1

#endif  // MATH_SPHERECROSSSECTION_H
