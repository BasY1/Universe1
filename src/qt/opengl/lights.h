/*!
 * \file qt/opengl/lights.h
 * \author Michal Steller
 * \brief The QT Open GL lights classes declarations
 */

#ifndef UNIVERSE1_OPENGL_LIGHTS_H
#define UNIVERSE1_OPENGL_LIGHTS_H

#include "material.h"

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Directional light properties
 */
struct DirectionLight : public ADSColors
{
    /*!
     * \brief Directional light modes
     */
    enum Mode : int
    {
        LightOff = 0,  //!< Light disabled
        LightOn = 1,   //!< Light enabled
    };

    Mode mode;            //!< Light mode
    QVector3D direction;  //!< Light direction

    DirectionLight(const QVector3D &_direction,
                   const QColor &_ambient,
                   const QColor &_diffuse,
                   const QColor &_specular);

    inline DirectionLight(const QVector3D &_direction, const QColor &_colorAll);
    inline DirectionLight(const QVector3D &_direction);
    inline DirectionLight();

    void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    void loadSettings(const QSettings &_settings, const QString &_keyGroup);
};

/*!
 * \brief Constructor
 * \param _colorAll Color for ambient, diffuse and specular colors
 * \param _direction Light direction
 */
inline DirectionLight::DirectionLight(const QVector3D &_direction, const QColor &_colorAll)
    : DirectionLight(_direction, _colorAll, _colorAll, _colorAll)
{
}

/*!
 * \brief Constructor
 * \param _direction Light direction
 * \note White color
 */
inline DirectionLight::DirectionLight(const QVector3D &_direction)
    : DirectionLight(_direction, Qt::white, Qt::white, Qt::white)
{
}

/*!
 * \brief Constructor
 * \note White color, Direction: [0, -1, 0]
 */
inline DirectionLight::DirectionLight()
    : DirectionLight(QVector3D(0.0F, -1.0F, 0.0F), Qt::white, Qt::white, Qt::white)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Point light properties
 */
struct PointLight : public ADSColors
{
    /*!
     * \brief Point light modes
     */
    enum Mode : int
    {
        LightOff = 0,        //!< Light disabled
        LightFixed = 1,      //!< Light fixed, no attenuation calculation
        LightScalar = 2,     //!< Light Constant attenuation factor \f$\frac{1}{C}\f$
        LightLinear = 3,     //!< Light attenuation factor \f$\frac{1}{C + L \times dist}\f$
        LightQuadratic = 4,  //!< Light attenuation factor \f$\frac{1}{C + L \times dist + Q \times dist^2}\f$
    };

    Mode mode;           //!< Light mode
    QVector3D position;  //!< Light position
    float constant;      //!< Constant attenuation factor
    float linear;        //!< Linear attenuation factor
    float quadratic;     //!< Quadratic attenuation factor

    PointLight(const Mode _mode,
               const QVector3D &_position,
               const QColor &_ambient,
               const QColor &_diffuse,
               const QColor &_specular,
               const float _constant,
               const float _linear,
               const float _quadratic);

    inline PointLight(const QVector3D &_position,
                      const QColor &_ambient,
                      const QColor &_diffuse,
                      const QColor &_specular,
                      const float _constant,
                      const float _linear,
                      const float _quadratic);

    inline PointLight(const QVector3D &_position,
                      const QColor &_colorAll,
                      const float _constant,
                      const float _linear,
                      const float _quadratic);

    inline PointLight(const QVector3D &_position, const float _constant, const float _linear, const float _quadratic);

    inline PointLight(const QVector3D &_position,
                      const QColor &_ambient,
                      const QColor &_diffuse,
                      const QColor &_specular,
                      const float _constant,
                      const float _linear);

    inline PointLight(const QVector3D &_position, const QColor &_colorAll, const float _constant, const float _linear);

    inline PointLight(const QVector3D &_position, const float _constant, const float _linear);

    inline PointLight(const QVector3D &_position,
                      const QColor &_ambient,
                      const QColor &_diffuse,
                      const QColor &_specular,
                      const float _constant);

    inline PointLight(const QVector3D &_position, const QColor &_colorAll, const float _constant);

    inline PointLight(const QVector3D &_position, const float _constant);

    inline PointLight(const QVector3D &_position,
                      const QColor &_ambient,
                      const QColor &_diffuse,
                      const QColor &_specular);

    inline PointLight(const QVector3D &_position, const QColor &_colorAll);

    inline PointLight(const QVector3D &_position);

    inline Material toMaterial() const;

    void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    void loadSettings(const QSettings &_settings, const QString &_keyGroup);
};

/*!
 * \brief Constructor - creates \b quadratic light
 * \param _position Light position
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_ambient,
                              const QColor &_diffuse,
                              const QColor &_specular,
                              const float _constant,
                              const float _linear,
                              const float _quadratic)
    : PointLight(LightQuadratic, _position, _ambient, _diffuse, _specular, _constant, _linear, _quadratic)
{
}

/*!
 * \brief Constructor - creates \b quadratic light
 * \param _position Light position
 * \param _colorAll Color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_colorAll,
                              const float _constant,
                              const float _linear,
                              const float _quadratic)
    : PointLight(LightQuadratic, _position, _colorAll, _colorAll, _colorAll, _constant, _linear, _quadratic)
{
}

/*!
 * \brief Constructor - creates \b quadratic light
 * \param _position Light position
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const float _constant,
                              const float _linear,
                              const float _quadratic)
    : PointLight(LightQuadratic, _position, Qt::white, Qt::white, Qt::white, _constant, _linear, _quadratic)
{
}

/*!
 * \brief Constructor - creates \b linear light
 * \param _position Light position
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_ambient,
                              const QColor &_diffuse,
                              const QColor &_specular,
                              const float _constant,
                              const float _linear)
    : PointLight(LightLinear, _position, _ambient, _diffuse, _specular, _constant, _linear, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b linear light
 * \param _position Light position
 * \param _colorAll Color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_colorAll,
                              const float _constant,
                              const float _linear)
    : PointLight(LightLinear, _position, _colorAll, _colorAll, _colorAll, _constant, _linear, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b linear light
 * \param _position Light position
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position, const float _constant, const float _linear)
    : PointLight(LightLinear, _position, Qt::white, Qt::white, Qt::white, _constant, _linear, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b scalar light
 * \param _position Light position
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_ambient,
                              const QColor &_diffuse,
                              const QColor &_specular,
                              const float _constant)
    : PointLight(LightScalar, _position, _ambient, _diffuse, _specular, _constant, 0.0F, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b scalar light
 * \param _position Light position
 * \param _colorAll Color
 * \param _constant Constant attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position, const QColor &_colorAll, const float _constant)
    : PointLight(LightScalar, _position, _colorAll, _colorAll, _colorAll, _constant, 0.0F, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b scalar light
 * \param _position Light position
 * \param _constant Constant attenuation factor
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position, const float _constant)
    : PointLight(LightScalar, _position, Qt::white, Qt::white, Qt::white, _constant, 0.0F, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \param _position Light position
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 */
inline PointLight::PointLight(const QVector3D &_position,
                              const QColor &_ambient,
                              const QColor &_diffuse,
                              const QColor &_specular)
    : PointLight(LightFixed, _position, _ambient, _diffuse, _specular, 0.0F, 0.0F, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \param _position Light position
 * \param _colorAll Color
 */
inline PointLight::PointLight(const QVector3D &_position, const QColor &_colorAll)
    : PointLight(LightFixed, _position, _colorAll, _colorAll, _colorAll, 0.0F, 0.0F, 0.0F)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \param _position Light position
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position)
    : PointLight(LightFixed, _position, Qt::white, Qt::white, Qt::white, 0.0F, 0.0F, 0.0F)
{
}

/*!
 * \brief Create material from light colors
 * \return Material created from light colors
 */
inline Universe1::OpenGL::Material Universe1::OpenGL::PointLight::toMaterial() const
{
    return Material(*this);
}

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_LIGHTS_H
