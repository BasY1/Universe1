/*!
 * \file math/orientation.h
 * \author Michal Steller
 * \brief Orientation of 3D object template implementation
 */

#ifndef UNIVERSE1_MATH_ORIENTATION_H
#define UNIVERSE1_MATH_ORIENTATION_H

#include "vec3.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief Orientation of 3D object
 * \tparam T Template floating point type
 */
template <typename T>
struct Orientation
{
    /*! \brief The anonymous union for different property name access */
    union
    {
        /*! \brief The anonymous structure, access components by "GEO" name */
        struct
        {
            Vec3<T> toPole;     //!< Direction to object's pole
            Vec3<T> toEquator;  //!< Direction to object's prime meridian (to Greenwich Meridian)
        };

        /*! \brief The anonymous structure, access components by "normal" name */
        struct
        {
            Vec3<T> normal1;  //!< Main orientation direction
            Vec3<T> normal2;  //!< Secondary orientation direction
        };
    };

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Orientation()
        : toPole(Vec3<T>::unitZ())
        , toEquator(Vec3<T>::unitY())
    {
    }

    /*!
     * \brief Constructor with orientation components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Orientation(const Vec3<T> &_toPole,     //!< Main orientation direction
                       const Vec3<T> &_toEquator)  //!< Secondary orientation direction
        : toPole(_toPole)
        , toEquator(_toEquator)
    {
        Vec3<T>::makePerpendicularNormals(toPole, toEquator);
    }

    inline bool isValid() const;

    inline Vec3<T> thirdDirection() const;
    inline Vec3<T> thirdDirectionByHand(const bool _rightHanded) const;

#ifdef UNIVERSE1_USE_QT_LIB
    inline std::pair<QVector3D, QVector3D> toQt() const;
#endif

    inline void setOrientation(const Vec3<T> &_toPole, const Vec3<T> &_toEquator);

    /*!
     * \brief Conversion to different precision
     * \tparam T2 Output template floating point type
     * \return Orientation in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    inline Orientation<T2> converted() const
    {
        return Orientation<T2>(toPole.template converted<T2>(), toEquator.template converted<T2>());
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if orientation is valid (contains unit vectors perpendicular each other)
 * \tparam T Template floating point type
 * \return \c true if orientation is valid
 */
template <typename T>
inline bool Orientation<T>::isValid() const
{
    return toPole.isNormalized() && toEquator.isNormalized() && toPole.isPerpendicular(toEquator);
}

/*!
 * \brief Returns third direction of orientation created by right-handed cross product of orientation normals
 * \tparam T Template floating point type
 * \return Third direction
 */
template <typename T>
inline Vec3<T> Orientation<T>::thirdDirection() const
{
    return Vec3<T>::cross(toPole, toEquator);
}

/*!
 * \brief Returns third direction of orientation created by right-handed cross product of orientation normals
 * \tparam T Template floating point type
 * \param _rightHanded Hand rule orientation
 * \return Third direction
 */
template <typename T>
inline Vec3<T> Orientation<T>::thirdDirectionByHand(const bool _rightHanded) const
{
    return Vec3<T>::crossByHand(toPole, toEquator, _rightHanded);
}

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief Conversion to QT 3D vector pair
 * \return Orientation as pair of \c QVector3D
 */
template <typename T>
inline std::pair<QVector3D, QVector3D> Orientation<T>::toQt() const
{
    return {toPole.toQVector3D(), toEquator.toQVector3D()};
}

#endif

/*!
 * \brief Setup new orientation
 * \param _toPole New main orientation direction
 * \param _toEquator New secondary orientation direction
 */
template <typename T>
inline void Orientation<T>::setOrientation(const Vec3<T> &_toPole, const Vec3<T> &_toEquator)
{
    toPole = _toPole;
    toEquator = _toEquator;
    Vec3<T>::makePerpendicularNormals(toPole, toEquator);
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_ORIENTATION_H
