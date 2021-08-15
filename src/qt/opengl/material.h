/*!
 * \file qt/opengl/material.h
 * \author Michal Steller
 * \brief The QT Open GL material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MATERIAL_H
#define UNIVERSE1_OPENGL_MATERIAL_H

#include "adscolors.h"
#include <QVector3D>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Material properties
 */
struct Material : public ADSColors
{
    float shininess;  //!< Material shininess
};

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::Material)

#endif  // UNIVERSE1_OPENGL_MATERIAL_H
