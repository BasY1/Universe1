/*!
 * \file qt/opengl/lights.h
 * \author Michal Steller
 * \brief The QT Open GL lights classes declarations
 */

#ifndef UNIVERSE1_OPENGL_LIGHTS_H
#define UNIVERSE1_OPENGL_LIGHTS_H

#include "material.h"

#include <QtMath>

namespace Universe1 {
namespace OpenGL {

#define DEFAULT_light_constant 1.0F  //!< Default initial value for constant attenuation factor
#define DEFAULT_light_linear 0.045F  //!< Default initial value for linear attenuation factor
#define DEFAULT_light_quadratic 0.0075F  //!< Default initial value for quadratic factor

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
        LightOff = 0,         //!< Light disabled
        LightNormalised = 1,  //!< Light enabled, vertices with normal away from direction not illuminated
        LightFull = 2,        //!< Light enabled, all vertices illuminated
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

    inline Material toMaterial() const;

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

/*!
 * \brief Create material from light colors
 * \returns Material created from light colors
 */
inline Universe1::OpenGL::Material Universe1::OpenGL::DirectionLight::toMaterial() const
{
    return Material(*this);
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
    inline PointLight();

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
    : PointLight(LightLinear, _position, _ambient, _diffuse, _specular, _constant, _linear, DEFAULT_light_quadratic)
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
    : PointLight(LightLinear, _position, _colorAll, _colorAll, _colorAll, _constant, _linear, DEFAULT_light_quadratic)
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
    : PointLight(LightLinear, _position, Qt::white, Qt::white, Qt::white, _constant, _linear, DEFAULT_light_quadratic)
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
    : PointLight(LightScalar,
                 _position,
                 _ambient,
                 _diffuse,
                 _specular,
                 _constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor - creates \b scalar light
 * \param _position Light position
 * \param _colorAll Color
 * \param _constant Constant attenuation factor
 */
inline PointLight::PointLight(const QVector3D &_position, const QColor &_colorAll, const float _constant)
    : PointLight(LightScalar,
                 _position,
                 _colorAll,
                 _colorAll,
                 _colorAll,
                 _constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor - creates \b scalar light
 * \param _position Light position
 * \param _constant Constant attenuation factor
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position, const float _constant)
    : PointLight(LightScalar,
                 _position,
                 Qt::white,
                 Qt::white,
                 Qt::white,
                 _constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
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
    : PointLight(LightFixed,
                 _position,
                 _ambient,
                 _diffuse,
                 _specular,
                 DEFAULT_light_constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \param _position Light position
 * \param _colorAll Color
 */
inline PointLight::PointLight(const QVector3D &_position, const QColor &_colorAll)
    : PointLight(LightFixed,
                 _position,
                 _colorAll,
                 _colorAll,
                 _colorAll,
                 DEFAULT_light_constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \param _position Light position
 * \note Creates white light
 */
inline PointLight::PointLight(const QVector3D &_position)
    : PointLight(LightFixed,
                 _position,
                 Qt::white,
                 Qt::white,
                 Qt::white,
                 DEFAULT_light_constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor - creates \b fixed light (No attenuation)
 * \note Creates white light at [0, 0, 0]
 */
inline PointLight::PointLight()
    : PointLight(LightFixed,
                 QVector3D(),
                 Qt::white,
                 Qt::white,
                 Qt::white,
                 DEFAULT_light_constant,
                 DEFAULT_light_linear,
                 DEFAULT_light_quadratic)
{
}

/*!
 * \brief Create material from light colors
 * \returns Material created from light colors
 */
inline Universe1::OpenGL::Material Universe1::OpenGL::PointLight::toMaterial() const
{
    return Material(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Spot light properties
 */
struct SpotLight : public PointLight
{
    QVector3D direction;   //!< Light direction
    float cutOffRad;       //!< Cut-off angle [radians]
    float outerCutOffRad;  //!< Outer cut-off angle [radians]

    SpotLight(const Mode _mode,
              const QVector3D &_position,
              const QVector3D &_direction,
              const float _cutOffRad,
              const float _outerCutOffRad,
              const QColor &_ambient,
              const QColor &_diffuse,
              const QColor &_specular,
              const float _constant,
              const float _linear,
              const float _quadratic);

    inline SpotLight(const Mode _mode,
                     const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear,
                     const float _quadratic);

    inline SpotLight(const Mode _mode,
                     const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear,
                     const float _quadratic);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant,
                     const float _linear,
                     const float _quadratic);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear,
                     const float _quadratic);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear,
                     const float _quadratic);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant,
                     const float _linear);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll);

    inline SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOff);

    inline SpotLight();

    inline float cutOffDeg() const;
    inline float outerCutOffDeg() const;

    void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    void loadSettings(const QSettings &_settings, const QString &_keyGroup);
};

/*!
 * \brief Constructor
 * \param _mode Light mode
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _colorAll Ambient - Diffuse - Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 */
SpotLight::SpotLight(const Mode _mode,
                     const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear,
                     const float _quadratic)
    : SpotLight(_mode,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _colorAll,
                _colorAll,
                _colorAll,
                _constant,
                _linear,
                _quadratic)
{
}

/*!
 * \brief Constructor
 * \param _mode Light mode
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 * \note Initialize white light
 */
SpotLight::SpotLight(const Mode _mode,
                     const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear,
                     const float _quadratic)
    : SpotLight(_mode,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                Qt::white,
                Qt::white,
                Qt::white,
                _constant,
                _linear,
                _quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 * \note Initialize quadratic mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant,
                     const float _linear,
                     const float _quadratic)
    : SpotLight(LightQuadratic,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _ambient,
                _diffuse,
                _specular,
                _constant,
                _linear,
                _quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _colorAll Ambient - Diffuse - Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 * \note Initialize quadratic mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear,
                     const float _quadratic)
    : SpotLight(LightQuadratic,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _colorAll,
                _colorAll,
                _colorAll,
                _constant,
                _linear,
                _quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 * \note Initialize white light in quadratic mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear,
                     const float _quadratic)
    : SpotLight(LightQuadratic,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                Qt::white,
                Qt::white,
                Qt::white,
                _constant,
                _linear,
                _quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \note Initialize linear mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant,
                     const float _linear)
    : SpotLight(LightLinear,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _ambient,
                _diffuse,
                _specular,
                _constant,
                _linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _colorAll Ambient - Diffuse - Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \note Initialize linear mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant,
                     const float _linear)
    : SpotLight(LightLinear,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _colorAll,
                _colorAll,
                _colorAll,
                _constant,
                _linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \note Initialize white light in linear mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant,
                     const float _linear)
    : SpotLight(LightLinear,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                Qt::white,
                Qt::white,
                Qt::white,
                _constant,
                _linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \note Initialize scalar mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular,
                     const float _constant)
    : SpotLight(LightScalar,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _ambient,
                _diffuse,
                _specular,
                _constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _colorAll Ambient - Diffuse - Specular color
 * \param _constant Constant attenuation factor
 * \note Initialize scalar mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll,
                     const float _constant)
    : SpotLight(LightScalar,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _colorAll,
                _colorAll,
                _colorAll,
                _constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _constant Constant attenuation factor
 * \note Initialize white light in scalar mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const float _constant)
    : SpotLight(LightScalar,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                Qt::white,
                Qt::white,
                Qt::white,
                _constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \note Initialize fixed mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_ambient,
                     const QColor &_diffuse,
                     const QColor &_specular)
    : SpotLight(LightFixed,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _ambient,
                _diffuse,
                _specular,
                DEFAULT_light_constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _colorAll Ambient - Diffuse - Specular color
 * \note Initialize fixed mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad,
                     const QColor &_colorAll)
    : SpotLight(LightFixed,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                _colorAll,
                _colorAll,
                _colorAll,
                DEFAULT_light_constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \note Initialize white light in fixed mode
 */
SpotLight::SpotLight(const QVector3D &_position,
                     const QVector3D &_direction,
                     const float _cutOffRad,
                     const float _outerCutOffRad)
    : SpotLight(LightFixed,
                _position,
                _direction,
                _cutOffRad,
                _outerCutOffRad,
                Qt::white,
                Qt::white,
                Qt::white,
                DEFAULT_light_constant,
                DEFAULT_light_linear,
                DEFAULT_light_quadratic)
{
}

/*!
 * \brief Constructor
 * \note Initialize white light in fixed mode at [1, 1, 1] direction [-1, -1, -1] cut-off [20deg, outer 30deg]
 */
inline SpotLight::SpotLight()
    : SpotLight(QVector3D(1.0F, 1.0F, 1.0F),
                QVector3D(-1.0F, -1.0F, -1.0F).normalized(),
                qDegreesToRadians(20.0F),
                qDegreesToRadians(30.0F))
{
}

/*!
 * \brief Getter for cut-off angle in degrees
 * \return Cut-off angle in degrees
 */
inline float SpotLight::cutOffDeg() const
{
    return qRadiansToDegrees(cutOffRad);
}

/*!
 * \brief Getter for outer cut-off angle in degrees
 * \return Outer cut-off angle in degrees
 */
inline float SpotLight::outerCutOffDeg() const
{
    return qRadiansToDegrees(outerCutOffRad);
}

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::DirectionLight)
Q_DECLARE_METATYPE(Universe1::OpenGL::PointLight)
Q_DECLARE_METATYPE(Universe1::OpenGL::SpotLight)

#endif  // UNIVERSE1_OPENGL_LIGHTS_H
