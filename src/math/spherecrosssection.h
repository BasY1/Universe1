/*!
 * \file math/spherecrosssection.h
 * \author Michal Steller
 * \brief 3D Sphere template implementation
 */

#ifndef UNIVERSE1_MATH_SPHERECROSSSECTION_H
#define UNIVERSE1_MATH_SPHERECROSSSECTION_H

#include "sphere.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief Cross-section type
 * \details Information about wave's sphere against particle's sphere
 */
enum SphereCrossSectionType : uint8_t
{
    CROSS_INVALID = 0x00U,    //!< Invalid cross-section
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

    inline Vec3<T> directionToWave() const;

    inline bool isValid() const;
    inline bool isTouch() const;

    inline T angleRad() const;
    inline T angleDeg() const;

    T particleAngleRad() const;
    inline T particleAngleDeg() const;

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

    Circle<T> circle() const;

    static T calculateLinearRatio(const uint64_t _steps);
    static Vec3<T>
    calculateCircularRatio(const uint64_t _steps, const T _trajectoryRadius = T(1), const T _particleRadius = T(1));
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    positionDistance = particle.position.distanceToPoint(wave.position);

    if (isNull<T>(positionDistance))
    {
        waveInsideParticle = true;

        if (equals<T>(particle.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (particle.radius > wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (equals<T>(positionDistance, particle.radius))
    {
        waveInsideParticle = true;
        const T diameter = T(2) * particle.radius;
        if (equals<T>(wave.radius, diameter))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (wave.radius < diameter)
            crossSectionType = CROSS_WAVE_CROSSES;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (positionDistance < particle.radius)
    {

        waveInsideParticle = true;

        if (equals<T>(positionDistance + wave.radius, particle.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (equals<T>(positionDistance + particle.radius, wave.radius))
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

        if (equals<T>(positionDistance, particle.radius + wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (equals<T>(positionDistance + particle.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance > particle.radius + wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + particle.radius < wave.radius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSSES;
    }

    if (crossSectionType == CROSS_WAVE_CROSSES)
        cosAngle = alignedToPM1<T>(
            (wave.radius * wave.radius + positionDistance * positionDistance - particle.radius * particle.radius) /
            (T(2) * wave.radius * positionDistance));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns direction to from particle to wave
 * \tparam T Template floating point type
 * \return Direction to from particle to wave
 */
template <typename T>
inline Vec3<T> SphereCrossSection<T>::directionToWave() const
{
    return (wave.position - particle.position).normalized();
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/*!
 * \brief Returns angle of cross-section in radians from particle perspective
 * \tparam T Template floating point type
 * \return Angle of cross-section in radians from particle perspective
 */
template <typename T>
T SphereCrossSection<T>::particleAngleRad() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return T(0);
    case CROSS_WAVE_MISS_BEFORE: return Const::T_PI<T>();
    case CROSS_WAVE_TOUCH_BEFORE: return Const::T_PI<T>();
    case CROSS_WAVE_CROSSES:
        return Const::T_PI<T>() -
            std::acos(alignedToPM1<T>(
                (particle.radius * particle.radius + positionDistance * positionDistance - wave.radius * wave.radius) /
                (T(2) * particle.radius * positionDistance)));
    case CROSS_WAVE_TOUCH_AFTER: return T(0);
    case CROSS_WAVE_MISS_AFTER: return T(0);
    }
    return T(0);
}

/*!
 * \brief Returns angle of cross-section in degrees from particle perspective
 * \tparam T Template floating point type
 * \return Angle of cross-section in degrees from particle perspective
 */
template <typename T>
inline T SphereCrossSection<T>::particleAngleDeg() const
{
    return toDeg<T>(particleAngleRad());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    case CROSS_WAVE_CROSSES: return Const::T_2PI<T>() * wave.radius * wave.radius * (T(1) - cosAngle);
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
        return wave.position + (particle.position - wave.position).normalized() * (wave.radius * cosAngle);
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
        const Vec3<T> n = (particle.position - wave.position).normalized();
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
    case CROSS_WAVE_CROSSES: return (particle.position - wave.position).normalized();
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle
 * \tparam T Template floating point type
 * \return Cross-section circle
 */
template <typename T>
Circle<T> SphereCrossSection<T>::circle() const
{
    Circle<T> result;
    switch (crossSectionType)
    {
    case CROSS_INVALID:
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: break;
    case CROSS_WAVE_CROSSES: {
        result.radius = wave.radius * std::sqrt(T(1) - cosAngle * cosAngle);
        result.normal = (particle.position - wave.position).normalized();
        result.position = wave.position + result.normal * (wave.radius * cosAngle);
    }
    break;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Straight line move gravitational constant calculator
 * \tparam T Template floating point type
 * \param _steps No. of dividing steps
 * \return "Self information wave ratio" over particle on straight line move
 * \note When count of steps rises to infinity then linear ratio will be always exact value of 0.05.
 */
template <typename T>
T SphereCrossSection<T>::calculateLinearRatio(const uint64_t _steps)
{
    const T angleStep = Const::T_PI_2<T>() / static_cast<T>(_steps + 1U);
    const Sphere<T> particle(T(1), Vec3<T>());
    const T volumeParticle = particle.volume();

    T result = T(0);
    T angle = angleStep;
    T lastRatio = T(0);
    T lastVolume = T(0.5);
    lastVolume = Const::T_4PI_3<T>() * lastVolume * lastVolume * lastVolume;
    for (uint64_t i = 0U; i < _steps; ++i, angle += angleStep)
    {
        const T tmpS = std::sin(angle);
        const T tmpC = std::cos(angle);
        const T tmpR = (tmpS * tmpS + tmpC * tmpC) / (T(2) * tmpC);
        const SphereCrossSection<T> scs(particle, Sphere<T>(tmpR, Vec3<T>(-tmpR, T(0), T(0))));
        const T tmpRatio = scs.ratio();
        const T tmpVolume = scs.crossSectionVolume();
        const T tmpVolumeAdd = (tmpVolume - lastVolume);
        const T tmpVolumeRatio = tmpVolumeAdd / volumeParticle;
        const T tmpAreaRatio = (lastRatio + tmpRatio) * T(0.5);
        const T tmpAdd = tmpVolumeRatio * tmpAreaRatio;
        result += tmpAdd;
        lastVolume = tmpVolume;
        lastRatio = tmpRatio;
        // std::cout << i << ": A=" << toDeg<T>(angle) << "deg, V=" << tmpVolumeAdd
        //          << ", R=" << tmpRatio * Const::T_100<T>() << "% +=" << tmpAdd << std::endl;
    }

    const T finalVolume = (volumeParticle * T(0.5) - lastVolume) / volumeParticle;
    const T finalRatio = lastRatio * T(0.5);
    result += finalVolume * finalRatio;

    return result;
}

/*!
 * \brief Circular line move gravitational constant calculator
 * \tparam T Template floating point type
 * \param _steps No. of dividing steps
 * \param _trajectoryRadius Trajectory circle radius
 * \param _particleRadius Particle radius
 * \return "Self information wave ratio" over particle on circle trajectory
 */
template <typename T>
Vec3<T>
SphereCrossSection<T>::calculateCircularRatio(const uint64_t _steps, const T _trajectoryRadius, const T _particleRadius)
{
    static const uint8_t maxLoops = 20U;
    static const Vec3<T> n = Vec3<T>::unitZ();
    const Vec3<T> arm = Vec3<T>(_trajectoryRadius, T(0), T(0));

    uint8_t loop1 = 0U;
    uint8_t loop2 = 0U;

#ifndef DOXYGEN_SKIP
#define ___DIFF1(WR, DIST) _particleRadius - WR - DIST

    T path1 = _particleRadius * T(0.5);
    T angle1 = path1 / _trajectoryRadius;
    T dist1 = arm.distanceToPoint(arm.rotated(n, angle1));
    T diff1 = ___DIFF1(path1, dist1);
    if (!isNull<T>(diff1))
    {
        T path2 = path1 + diff1;
        T angle2 = path2 / _trajectoryRadius;
        const T dist2 = arm.distanceToPoint(arm.rotated(n, angle2));
        T diff2 = ___DIFF1(path2, dist2);
        if (isNull<T>(diff2))
        {
            path1 = path2;
            angle1 = angle2;
        }
        else
        {
            // std::cout << diff1 << " " << diff2 << "    " << toDeg<T>(angle1) << " " << toDeg<T>(angle2) << std::endl;
            for (; loop1 < maxLoops; ++loop1)
            {
                const T angle3 = angle1 - (angle1 - angle2) * diff1 / (diff1 - diff2);
                const T path3 = angle3 * _trajectoryRadius;
                const T dist3 = arm.distanceToPoint(arm.rotated(n, angle3));
                const T diff3 = ___DIFF1(path3, dist3);
                // std::cout << diff3 << " " << toDeg<T>(angle3) << std::endl;
                if (isNull<T>(diff2))
                {
                    path1 = path3;
                    angle1 = angle3;
                    break;
                }
                path1 = path2;
                path2 = path3;
                angle1 = angle2;
                angle2 = angle3;
                diff1 = diff2;
                diff2 = diff3;
            }
            if (loop1 >= maxLoops)
                return Vec3<T>();
        }
    }

    const T pathBegin = path1;
    const T angleBegin = angle1;

//#define ___DIFF2(WR, DIST) WR - (_particleRadius + DIST)
//#define ___DIFF2(WR, DIST) -(WR - (_particleRadius + DIST))
#define ___DIFF2(WR, DIST) (_particleRadius + DIST - WR)

    dist1 = arm.distanceToPoint(arm.rotated(n, angleBegin));
    diff1 = ___DIFF2(pathBegin, dist1);
    if (!isNull<T>(diff1))
    {

        T path2 = path1 + diff1;
        T angle2 = path2 / _trajectoryRadius;
        // if (_trajectoryRadius > _particleRadius)
        //{
        //    angle2 = Const::T_PI_2<T>();
        //    path2 = angle2 * _trajectoryRadius;
        //}

        T dist2 = arm.distanceToPoint(arm.rotated(n, angle2));
        T diff2 = ___DIFF2(path2, dist2);
        bool needStep = isPositive<T>(diff2);
        while (needStep)
        {
            path2 += _particleRadius;
            angle2 = path2 / _trajectoryRadius;
            dist2 = arm.distanceToPoint(arm.rotated(n, angle2));
            diff2 = ___DIFF2(path2, dist2);
            needStep = isPositive<T>(diff2);
            if (needStep)
            {
                path1 = path2;
                angle1 = angle2;
                diff1 = diff2;
            }
        }

        if (isNull<T>(diff2))
        {
            path1 = path2;
            angle1 = angle2;
        }
        else
        {
            T minPath = path1;
            T minAngle = angle1;
            T minDiff = diff1;
            if (std::abs(diff2) < std::abs(diff1))
            {
                minPath = path2;
                minAngle = angle2;
                minDiff = diff2;
            }

            for (; loop2 < maxLoops; ++loop2)
            {
                const T angle3 = angle1 - (angle1 - angle2) * diff1 / (diff1 - diff2);
                const T path3 = angle3 * _trajectoryRadius;
                const T dist3 = arm.distanceToPoint(arm.rotated(n, angle3));
                const T diff3 = ___DIFF2(path3, dist3);
                // std::cout << diff3 << " " << toDeg<T>(angle3) << std::endl;
                if (isNull<T>(diff3))
                {
                    path1 = path3;
                    angle1 = angle3;
                    break;
                }

                if (std::abs(diff3) < std::abs(minDiff))
                {
                    minPath = path3;
                    minAngle = angle3;
                    minDiff = diff3;
                }

                path1 = path2;
                path2 = path3;
                angle1 = angle2;
                angle2 = angle3;
                diff1 = diff2;
                diff2 = diff3;
            }
            if (loop2 >= maxLoops)
            {
                path1 = minPath;
                angle1 = minAngle;
            }
        }
    }

    const T pathEnd = path1;
    const T angleEnd = angle1;
    const T angleStep = (angleEnd - angleBegin) / static_cast<T>(_steps + 1U);
    const T pathStep = (pathEnd - pathBegin) / static_cast<T>(_steps + 1U);
    const Sphere<T> particle(_particleRadius, arm);
    const T volumeParticle = particle.volume();

    Vec3<T> result;

    const SphereCrossSection<T> scs(particle, Sphere<T>(pathBegin, arm.rotated(n, angleBegin)));
    T lastVolume = scs.crossSectionVolume();
    T lastRatio = scs.ratio();
    Vec3<T> lastDir = scs.directionToWave();

    T angle = angleBegin + angleStep;
    T path = pathBegin + pathStep;
    for (uint64_t i = 0U; i < _steps; ++i, angle += angleStep, path += pathStep)
    {
        const SphereCrossSection<T> scs(particle, Sphere<T>(path, arm.rotated(n, angle)));
        const T tmpVolume = scs.crossSectionVolume();
        const T tmpRatio = scs.ratio();
        const Vec3<T> tmpDir = scs.directionToWave();
        const T tmpVolumeAdd = (tmpVolume - lastVolume);
        const T tmpVolumeRatio = tmpVolumeAdd / volumeParticle;
        const T tmpAreaRatio = (lastRatio + tmpRatio) * T(0.5);
        const T tmpAdd = tmpVolumeRatio * tmpAreaRatio;

        result += (tmpDir + lastDir).normalized() * tmpAdd;

        lastVolume = tmpVolume;
        lastRatio = tmpRatio;
        lastDir = tmpDir;
    }

    // std::cout << "Begin loops[" << ((int)loop1) << "] angle: " << toDeg<T>(angleBegin) << " " << pathBegin <<
    // std::endl; std::cout << "End   loops[" << ((int)loop2) << "] angle: " << toDeg<T>(angleEnd) << " " << pathEnd <<
    // std::endl;
    /*
    0.01000    [-0.00371534593818 x -0.00608775870109 | 0.00713194233313]
    0.10000    [-0.07668915864998 x -0.01039162573400 | 0.07739000542600]
    0.25000    [-0.15242941253251 x -0.04433406537989 | 0.15874581934059]
    0.50000    [-0.10478929506897 x  0.05508414607552 | 0.11838521660208]
    0.75000    [-0.06779824530226 x  0.06762759836220 | 0.09576060842698]
    0.95000    [-0.05137272355017 x  0.06843250411162 | 0.08556964616001]
    0.97173349 [-0.05000000045278 x  0.06837400783062 | 0.08470540119791]

    1.00000    [-0.04830733788870 x  0.06827470064972 | 0.08363631772563]
    1.10000    [-0.04304972379673 x  0.06777202047339 | 0.08028901218735]
    1.50000    [-0.02943076688474 x  0.06502649526833 | 0.07137657267134]
    2.00000    [-0.02062316384666 x  0.06200925913839 | 0.06534878044722]
    3.00000    [-0.01252252375792 x  0.05819264070500 | 0.05952475983563]
    5.00000    [-0.00675750834410 x  0.05473071937631 | 0.05514631050641]
    10.0000    [-0.00300899569187 x  0.05209587491847 | 0.05218270056824]
    1000.00    [-0.00002375093414 x  0.05000529577987 | 0.05000530142034]

    0.97173349 [-1.00000000905557 x 1.36748015661267 | 1.69410802395849]

    1.00000000 [-0.96614675777990 x 1.36549401301387 | 1.67272635453182]
    1.10000000 [-0.86099447594058 x 1.35544040949038 | 1.60578024376925]
    1.50000000 [-0.58861533770171 x 1.30052990540308 | 1.42753145346274]
    2.00000000 [-0.41246327694108 x 1.24018518282404 | 1.30697560900014]
    3.00000000 [-0.25045047516798 x 1.16385281420128 | 1.19049519681354]
    5.00000000 [-0.13515016689378 x 1.09461438773570 | 1.10292621033749]
    10.0000000 [-0.06017991385311 x 1.04191749891786 | 1.04365401191325]
    1000.00000 [-0.00047501875975 x 1.00010618549532 | 1.00010629830475]


    */
    return result;

#undef ___DIFF1
#undef ___DIFF2
#endif  // DOXYGEN_SKIP
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_SPHERECROSSSECTION_H
