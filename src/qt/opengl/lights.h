/*!
 * \file qt/opengl/lights.h
 * \author Michal Steller
 * \brief The QT Open GL lights classes declarations
 */

#ifndef UNIVERSE1_OPENGL_LIGHTS_H
#define UNIVERSE1_OPENGL_LIGHTS_H

#include "adscolors.h"

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
};

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
    float constant;      //!< Constant attenuation factor
    float linear;        //!< Linear attenuation factor
    float quadratic;     //!< Quadratic attenuation factor
    QVector3D position;  //!< Light position
};

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_LIGHTS_H
