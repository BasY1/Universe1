/*!
 * \file math/spherecrosssection.h
 * \author Michal Steller
 * \brief 3D Sphere template implementation
 */

#ifndef UNIVERSE1_MATH_SPHERECROSSSECTION_H
#define UNIVERSE1_MATH_SPHERECROSSSECTION_H

#include "circle.h"
#include "sphere.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief Cross-section type
 * \details Information about wave's sphere against element's sphere
 */
enum SphereCrossSectionType : uint8_t
{
    CROSS_INVALID = 0x00U,     //!< Invalid cross-section
    CROSS_WAVE_MISS_BEFORE,    //!< Wave is before element (Wave needs to grow to hit element)
    CROSS_WAVE_TOUCH_BEFORE,   //!< Wave sphere touch element's border (Growing wave will cross element)
    CROSS_WAVE_CROSS_ELEMENT,  //!< Wave sphere cross element's sphere
    CROSS_WAVE_TOUCH_AFTER,    //!< Wave sphere touch element's border (Growing wave will pass element)
    CROSS_WAVE_MISS_AFTER,     //!< Wave is after element (Wave passed element)
};

/*!
 * \brief Sphere cross-section
 * \tparam T Template floating point type
 */
template <typename T>
struct SphereCrossSection
{
    const Sphere<T> &element;  //!< Element sphere pointer
    const Sphere<T> &wave;     //!< Wave sphere pointer

    SphereCrossSectionType crossSectionType;  //!< Cross-section type

    bool waveInsideElement;  //!< Position type

    T positionDistance;  //!< Distance between wave's and element's sphere center position
    T cosAngle;          //!< Co-sine of cross-section angle

    SphereCrossSection(const Sphere<T> &_element, const Sphere<T> &_wave);

    inline Vec3<T> directionToWave() const;

    inline bool isValid() const;
    inline bool isTouch() const;

    inline T angleRad() const;
    inline T angleDeg() const;

    T crossSectionVolume() const;
    T crossSectionArea() const;
    T crossSectionAreaRatio() const;
    T ratio() const;
    T distanceOffset() const;

    Vec3<T> circleCenter() const;
    T circleRadius() const;
    Vec3<T> circleArm() const;
    Vec3<T> circleNormal() const;

    Circle<T> circle() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor from other sphere
 * \tparam T Template floating point type
 * \param _element Element sphere pointer
 * \param _wave Wave sphere pointer
 */
template <typename T>
SphereCrossSection<T>::SphereCrossSection(const Sphere<T> &_element, const Sphere<T> &_wave)
    : element(_element)
    , wave(_wave)
    , crossSectionType(CROSS_INVALID)
    , waveInsideElement(false)
    , positionDistance(Const::T_0<T>())
    , cosAngle(Const::T_0<T>())
{
    if (!element.isValid() || !wave.isValid())
        return;

    positionDistance = element.position.distanceToPoint(wave.position);

    if (Type::isNull<T>(positionDistance))
    {
        waveInsideElement = true;

        if (Type::equals<T>(element.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (element.radius > wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (Type::equals<T>(positionDistance, element.radius))
    {
        waveInsideElement = true;
        const T diameter = Const::T_2<T>() * element.radius;
        if (Type::equals<T>(wave.radius, diameter))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (wave.radius < diameter)
            crossSectionType = CROSS_WAVE_CROSS_ELEMENT;
        else
            crossSectionType = CROSS_WAVE_MISS_AFTER;
    }

    else if (positionDistance < element.radius)
    {

        waveInsideElement = true;

        if (Type::equals<T>(positionDistance + wave.radius, element.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Type::equals<T>(positionDistance + element.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance + wave.radius < element.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + element.radius < wave.radius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSS_ELEMENT;
    }

    else
    {
        // waveInsideElement = false;

        if (Type::equals<T>(positionDistance, element.radius + wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_BEFORE;
        else if (Type::equals<T>(positionDistance + element.radius, wave.radius))
            crossSectionType = CROSS_WAVE_TOUCH_AFTER;
        else if (positionDistance > element.radius + wave.radius)
            crossSectionType = CROSS_WAVE_MISS_BEFORE;
        else if (positionDistance + element.radius < wave.radius)
            crossSectionType = CROSS_WAVE_MISS_AFTER;
        else
            crossSectionType = CROSS_WAVE_CROSS_ELEMENT;
    }

    if (crossSectionType != CROSS_WAVE_CROSS_ELEMENT)
        return;

    cosAngle = (wave.radius * wave.radius + positionDistance * positionDistance - element.radius * element.radius) /
        (Const::T_2<T>() * wave.radius * positionDistance);

    cosAngle = Type::alignedToPM1<T>(cosAngle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns direction to from element to wave
 * \tparam T Template floating point type
 * \returns Direction to from element to wave
 */
template <typename T>
inline Vec3<T> SphereCrossSection<T>::directionToWave() const
{
    return (wave.position - element.position).normalized();
}

/*!
 * \brief Test if sphere cross-section is valid
 * \tparam T Template floating point type
 * \returns \c true if sphere cross-section is valid
 */
template <typename T>
inline bool SphereCrossSection<T>::isValid() const
{
    return crossSectionType != CROSS_INVALID;
}

/*!
 * \brief Test if wave sphere is touching element sphere
 * \tparam T Template floating point type
 * \returns \c true if wave sphere is touching element sphere
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
    case CROSS_WAVE_CROSS_ELEMENT:
    case CROSS_WAVE_MISS_AFTER: break;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns angle of cross-section in radians
 * \tparam T Template floating point type
 * \returns Angle of cross-section in radians
 */
template <typename T>
inline T SphereCrossSection<T>::angleRad() const
{
    return crossSectionType != CROSS_WAVE_CROSS_ELEMENT ? Const::T_0<T>() : std::acos(cosAngle);
}

/*!
 * \brief Returns angle of cross-section in degrees
 * \tparam T Template floating point type
 * \returns Angle of cross-section in degrees
 */
template <typename T>
inline T SphereCrossSection<T>::angleDeg() const
{
    return toDeg<T>(angleRad());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns cross-section penetration volume
 * \tparam T Template floating point type
 * \returns Cross-section penetration volume
 */
template <typename T>
T SphereCrossSection<T>::crossSectionVolume() const
{
    switch (crossSectionType)
    {
    case CROSS_INVALID: return Const::T_0<T>();

    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_TOUCH_BEFORE: return (waveInsideElement ? wave.volume() : Const::T_0<T>());

    case CROSS_WAVE_TOUCH_AFTER:
    case CROSS_WAVE_MISS_AFTER: return element.volume();

    case CROSS_WAVE_CROSS_ELEMENT:
        return wave.volumeCup(wave.radius * (Const::T_1<T>() - cosAngle)) +
            element.volumeCup(element.radius - positionDistance + wave.radius * cosAngle);
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns cross-section penetration wave surface area
 * \tparam T Template floating point type
 * \returns Cross-section penetration wave surface area
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
    case CROSS_WAVE_MISS_AFTER: return Const::T_0<T>();
    case CROSS_WAVE_CROSS_ELEMENT: return Const::T_2PI<T>() * wave.radius * wave.radius * (Const::T_1<T>() - cosAngle);
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns cross-section penetration wave surface area ratio
 * \f$\frac{penetration area}{full wave sphere surface area}\f$
 * \tparam T Template floating point type
 * \returns Cross-section penetration wave surface area ratio
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
    case CROSS_WAVE_MISS_AFTER: return Const::T_0<T>();
    case CROSS_WAVE_CROSS_ELEMENT: return Const::T_05<T>() * (Const::T_1<T>() - cosAngle);
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns cross-section ratio \f$\frac{1 - cos(\alpha)^2}{4}\f$
 * \tparam T Template floating point type
 * \returns Cross-section ratio
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
    case CROSS_WAVE_MISS_AFTER: return Const::T_0<T>();
    case CROSS_WAVE_CROSS_ELEMENT: return (Const::T_1<T>() - cosAngle * cosAngle) / Const::T_4<T>();
    }
    return Const::T_0<T>();
}
/*!
 * \brief Returns offset distance
 * \tparam T Template floating point type
 * \returns Offset distance
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
        if (waveInsideElement)
            return element.radius - (wave.radius + positionDistance);
        else
            return positionDistance - (wave.radius + element.radius);

    case CROSS_WAVE_MISS_AFTER: return wave.radius - (element.radius + positionDistance);

    case CROSS_WAVE_CROSS_ELEMENT:
        if (waveInsideElement)
            return (wave.radius + positionDistance) - element.radius;
        else
            return (wave.radius + element.radius) - positionDistance;
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns cross-section penetration circle center
 * \tparam T Template floating point type
 * \returns Cross-section circle center
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
	case CROSS_WAVE_CROSS_ELEMENT:
		return wave.position + (element.position - wave.position).normalized() * (wave.radius * cosAngle);
	}
	return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \returns Cross-section circle arm
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
    case CROSS_WAVE_MISS_AFTER: return Const::T_0<T>();
    case CROSS_WAVE_CROSS_ELEMENT: return wave.radius * std::sqrt(Const::T_1<T>() - cosAngle * cosAngle);
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns cross-section penetration circle arm
 * \tparam T Template floating point type
 * \returns Cross-section circle arm
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
    case CROSS_WAVE_CROSS_ELEMENT: {
        const Vec3<T> n = (element.position - wave.position).normalized();
        const T r = wave.radius * std::sqrt(Const::T_1<T>() - cosAngle * cosAngle);
        return n.perpendicularNormal() * r;
    }
    }
    return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle normal
 * \tparam T Template floating point type
 * \returns Cross-section circle normal
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
	case CROSS_WAVE_CROSS_ELEMENT: return (element.position - wave.position).normalized();
	}
	return Vec3<T>();
}

/*!
 * \brief Returns cross-section penetration circle
 * \tparam T Template floating point type
 * \returns Cross-section circle
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
    case CROSS_WAVE_CROSS_ELEMENT: {
        result.radius = wave.radius * std::sqrt(Const::T_1<T>() - cosAngle * cosAngle);
        result.normal = (element.position - wave.position).normalized();
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
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _scs Sphere cross-section
 * \returns Output text stream
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
    case CROSS_WAVE_CROSS_ELEMENT: tName = "Cross"; break;
    }

    _os << "[[" << (_scs.waveInsideElement ? "In" : "Out") << '-' << tName << ']';
    _os << "Element" << _scs.element;
    _os << "Wave" << _scs.wave;
    _os << "Distance[" << _scs.positionDistance << ']';

    switch (_scs.crossSectionType)
    {
    case CROSS_INVALID: return _os << "[Invalid]";
    case CROSS_WAVE_MISS_BEFORE:
    case CROSS_WAVE_MISS_AFTER: _os << "Offset[" << _scs.distanceOffset() << ']'; break;
    case CROSS_WAVE_TOUCH_BEFORE:
    case CROSS_WAVE_TOUCH_AFTER: break;
    case CROSS_WAVE_CROSS_ELEMENT:
        _os << "Offset[" << _scs.distanceOffset() << ']';
        _os << "Volume[" << _scs.crossSectionVolume() << ']';
        _os << "Angle[" << _scs.angleDeg() << "deg]";
        _os << "Ratio[" << (_scs.ratio() * Const::T_100<T>()) << "%]";
        break;
    }

    _os << ']';
    return _os;
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_SPHERECROSSSECTION_H
