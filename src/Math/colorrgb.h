/*!
 * \file src/Math/colorrgb.h
 * \brief 8bit Color structure
 */

#ifndef MATH_COLORRGB_H
#define MATH_COLORRGB_H

#include "type.h"

#include <QColor>
#include <QVector3D>

namespace U1 {
namespace Math {

template <typename T>
struct Vec3;

/*! \brief The red-green-blue color structure with 8bit components */
struct ColorRGB
{
    uint8_t red = 0U;    //!< Red component
    uint8_t green = 0U;  //!< Green component
    uint8_t blue = 0U;   //!< Blue component

    ColorRGB() = default;  //!< Default constructor

    /*!
     * \brief Constructor with components
     * \param _red Red component
     * \param _green Green component
     * \param _blue Blue component
     */
    inline ColorRGB(const uint8_t _red, const uint8_t _green, const uint8_t _blue)
        : red(_red)
        , green(_green)
        , blue(_blue)
    {
    }

    /*!
     * \brief Constructor from \c QColor
     * \param _color \c QColor
     */
    inline ColorRGB(const QColor &_color)
        : red(_color.red())
        , green(_color.green())
        , blue(_color.blue())
    {
    }

    /*!
     * \brief Returns half darker color
     * \return Half darker color
     * \note RGB components are divided by 2
     */
    inline ColorRGB darker() const
    {
        ColorRGB result;
        result.red /= 2U;
        result.green /= 2U;
        result.blue /= 2U;
        return result;
    }

    /*!
     * \brief Conversion to \c QColor
     * \return
     */
    inline QColor toQColor() const
    {
        return QColor((int)red, (int)green, (int)blue);
    }

    template <typename T>
    inline Vec3<T> toVec3() const;

    template <typename T>
    inline static ColorRGB fromVec3(const Vec3<T> &_vector);

    /*!
     * \brief Create color from a \c QVector3D
     * \tparam T Template floating point type
     * \return Color constructed from a \c QVector3D
     */
    inline static ColorRGB fromQVec3(const QVector3D &_vector)
    {
        return {uint8_t(aligned(_vector.x() * 255.0f, 0.0f, 255.0f)),
                uint8_t(aligned(_vector.y() * 255.0f, 0.0f, 255.0f)),
                uint8_t(aligned(_vector.z() * 255.0f, 0.0f, 255.0f))};
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return mixHash(std::hash<uint8_t>{}(red), std::hash<uint8_t>{}(green), std::hash<uint8_t>{}(blue));
    }

    /*!
     * \brief Compare operator
     * \param other Other color
     * \return \c true if objects equals
     */
    inline bool operator==(const ColorRGB &other) const
    {
        return red == other.red && green == other.green && blue == other.blue;
    }

    /*!
     * \brief Compare operator
     * \param other Other color
     * \return \c true if objects NOT equals
     */
    inline bool operator!=(const ColorRGB &other) const
    {
        return red != other.red || green != other.green || blue != other.blue;
    }

    /*!
     * \brief Rainbow pattern
     * \param _ratio Rainbow gradient offset (0 to 1)
     * \return Color from a rainbow gradient
     */
    inline static ColorRGB rainbow(const float _ratio)
    {
        if (!isPositive(_ratio))
            return ColorRGB(255U, 0U, 0U);

        if (isMoreOrEqual(_ratio, 1.0f))
            return ColorRGB(255U, 0U, 255U);

        if (isLessOrEqual(_ratio, 0.2f))
        {
            const uint8_t tmp = uint8_t(aligned(_ratio * 5.0f * 255.0f, 0.0f, 255.0f));
            return ColorRGB{255U, tmp, 0};
        }

        if (isLessOrEqual(_ratio, 0.4f))
        {
            const uint8_t tmp = uint8_t(aligned((_ratio - 0.2f) * 5.0f * 255.0f, 0.0f, 255.0f));
            return ColorRGB(255U - tmp, 255U, 0U);
        }

        if (isLessOrEqual(_ratio, 0.6f))
        {
            const uint8_t tmp = uint8_t(aligned((_ratio - 0.4f) * 5.0f * 255.0f, 0.0f, 255.0f));
            return ColorRGB(0U, 255U, tmp);
        }

        if (isLessOrEqual(_ratio, 0.8f))
        {
            const uint8_t tmp = uint8_t(aligned((_ratio - 0.6f) * 5.0f * 255.0f, 0.0f, 255.0f));
            return ColorRGB(0U, 255U - tmp, 255U);
        }

        const uint8_t tmp = uint8_t(aligned((_ratio - 0.8f) * 5.0f * 255.0f, 0.0f, 255.0f));
        return ColorRGB(tmp, 0U, 255U);
    }
};

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Color
 * \return Output text stream
 */
inline std::ostream &operator<<(std::ostream &_os, const ColorRGB &_v)
{
    return _os << '[' << int(_v.red) << ',' << int(_v.green) << ',' << int(_v.blue) << ']';
}

}  // namespace Math
}  // namespace U1

#endif  // MATH_COLORRGB_H
