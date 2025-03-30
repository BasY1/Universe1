/*!
 * \file src/Math/material.h
 * \brief Open GL material structure
 */

#ifndef MATH_MATERIAL_H
#define MATH_MATERIAL_H

#include "colorrgb.h"

namespace U1 {
namespace Math {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief The material structure for Open GL usage */
struct MaterialRGB
{
    ColorRGB ambient;                        //!< Ambient color
    ColorRGB diffuse;                        //!< Diffuse color
    ColorRGB specular = {255U, 255U, 255U};  //!< Specular color
    float shine = 32.0f;                     //!< Shine factor

    /*! \brief Default constructor */
    inline MaterialRGB() = default;

    /*!
     * \brief Constructor from color
     * \param _color Base color
     */
    inline MaterialRGB(const ColorRGB &_color)
        : ambient(_color.darker())
        , diffuse(_color)
    {
    }

    /*!
     * \brief Constructor
     * \param _ambient Initial ambient color
     * \param _diffuse Initial diffuse color
     * \param _specular Initial specular color
     * \param _shine Initial shine factor
     */
    inline MaterialRGB(const ColorRGB &_ambient,
                       const ColorRGB &_diffuse,
                       const ColorRGB &_specular,
                       const float _shine = 32.0f)
        : ambient(_ambient)
        , diffuse(_diffuse)
        , specular(_specular)
        , shine(_shine)
    {
    }

    inline MaterialRGB(const QColor &_color)
        : ambient(ColorRGB(_color).darker())
        , diffuse(ColorRGB(_color))
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(ambient.toHash(), diffuse.toHash(), specular.toHash(), std::hash<float>{}(shine));
    }

    /*!
     * \brief Returns half darker color
     * \return Half darker color
     * \note RGB components are divided by 2
     */
    inline MaterialRGB darker() const
    {
        MaterialRGB result;
        result.ambient = ambient.darker();
        result.diffuse = diffuse.darker();
        result.specular = specular.darker();
        result.shine = shine * 2.0f;
        return result;
    }

    /*!
     * \brief Material from rainbow gradient
     * \param _ratio Rainbow gradient offset (0 to 1)
     * \return Material from a rainbow gradient
     */
    inline static MaterialRGB rainbow(const float _ratio)
    {
        return MaterialRGB(ColorRGB::rainbow(_ratio));
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief The material structure for Open GL usage */
struct MaterialRGBA
{
    ColorRGB ambient;                        //!< Ambient color
    ColorRGB diffuse;                        //!< Diffuse color
    ColorRGB specular = {255U, 255U, 255U};  //!< Specular color
    float shine = 32.0f;                     //!< Shine factor
    uint8_t alpha = 255U;                    //!< Alpha factor

    /*! \brief Default constructor */
    inline MaterialRGBA() = default;

    /*!
     * \brief Constructor from color
     * \param _color Base color
     */
    inline MaterialRGBA(const ColorRGB &_color)
        : ambient(_color.darker())
        , diffuse(_color)
    {
    }

    /*!
     * \brief Constructor
     * \param _ambient Initial ambient color
     * \param _diffuse Initial diffuse color
     * \param _specular Initial specular color
     * \param _shine Initial shine factor
     * \param _alpha Initial alpha factor
     */
    inline MaterialRGBA(const ColorRGB &_ambient,
                        const ColorRGB &_diffuse,
                        const ColorRGB &_specular,
                        const float _shine = 32.0f,
                        const uint8_t _alpha = 255U)
        : ambient(_ambient)
        , diffuse(_diffuse)
        , specular(_specular)
        , shine(_shine)
        , alpha(_alpha)
    {
    }

    inline MaterialRGBA(const QColor &_color)
        : ambient(ColorRGB(_color).darker())
        , diffuse(ColorRGB(_color))
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(ambient.toHash(),
                             diffuse.toHash(),
                             specular.toHash(),
                             std::hash<float>{}(shine),
                             std::hash<uint8_t>{}(alpha));
    }

    /*!
     * \brief Returns half darker color
     * \return Half darker color
     * \note RGB components are divided by 2
     */
    inline MaterialRGBA darker() const
    {
        MaterialRGBA result = *this;
        result.ambient = ambient.darker();
        result.diffuse = diffuse.darker();
        result.specular = specular.darker();
        result.shine = shine * 2.0f;
        return result;
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \param _os Output text stream
 * \param _v Material
 * \return Output text stream
 */
inline std::ostream &operator<<(std::ostream &_os, const MaterialRGB &_v)
{
    return _os << '[' << _v.ambient << ',' << _v.diffuse << ',' << _v.specular << ',' << _v.shine << ']';
}

/*!
 * \brief Fill output text stream
 * \param _os Output text stream
 * \param _v Material
 * \return Output text stream
 */
inline std::ostream &operator<<(std::ostream &_os, const MaterialRGBA &_v)
{
    return _os << '[' << _v.ambient << ',' << _v.diffuse << ',' << _v.specular << ',' << _v.shine << ','
               << int(_v.alpha) << ']';
}

}  // namespace Math
}  // namespace U1

#endif  // MATH_MATERIAL_H
