/*!
 * \file qt/project/scenesetup.h
 * \author Michal Steller
 * \brief Visual setup for scene class declarations
 */

#ifndef UNIVERSE1_PROJECT_SCENESETUP_H
#define UNIVERSE1_PROJECT_SCENESETUP_H

#include "../opengl/lights.h"

#include "spacesetup.h"
#include "spectrumarrowsetup.h"

namespace Universe1 {
namespace Project {

/*!
 * \brief Tool structure - Visual setup for elements
 */
struct ElementSetup
{
    ArrowSetup velocity;       //!< Setup used velocity vector arrows
    ArrowSetup acceleration;   //!< Setup used acceleration vector arrows
    SpectrumArrowSetup force;  //!< Setup used force vectors arrows (full spectrum)
    SpectrumArrowSetup spin;   //!< Setup used spin vector arrows (full spectrum)

    bool showVelocity;      //!< Show velocity arrow
    bool showAcceleration;  //!< Show acceleration arrow

    int circlePointsShape;  //!< Point count on circle for polygon sphere view
    int circlePointsWires;  //!< Point count on circle for wire-frame sphere view
    float defaultRadius;    //!< Default object radius
    float lineWidthMult;    //!< Line width multiplier for wire-framed view (mixes with main scene line width),
                            //!< applies on singularity and sphere wire-frames (not on arrows)

    OpenGL::Material singularity;   //!< Material for singularity visual objects
    OpenGL::Material spehereOuter;  //!< Material for sphere outer view
    OpenGL::Material spehereInner;  //!< Material for sphere inner view (inside material)
    OpenGL::Material spehereWires;  //!< Material for sphere wire-frame lines
};

/*!
 * \brief Tool structure - Visual setup for scene
 */
struct SceneSetup
{
    float lineWidth;  //!< Scene line width

    QColor backgroundColor;  //!< Background color
    float ambientFactor;     //!< Scene ambient factor

    OpenGL::DirectionLight directionLight;        //!< Scene directional light
    std::vector<OpenGL::PointLight> pointLights;  //!< Scene point lights
    std::vector<OpenGL::SpotLight> spotLights;    //!< Scene spot lights

    ArrowSetup dimension;  //!< Setup used for dimensions, distances, lengths

    SpaceSetup spaceSetup;  //!< Space setup

    ElementSetup elementSetup;  //!< Setup used for all unmarked elements
    ElementSetup currentSetup;  //!< Setup used for current (selected) elements
};

}  // namespace Project
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::Project::ElementSetup)
Q_DECLARE_METATYPE(Universe1::Project::SceneSetup)

#endif  // UNIVERSE1_PROJECT_SCENESETUP_H
