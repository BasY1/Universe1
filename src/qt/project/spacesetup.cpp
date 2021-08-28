/*!
 * \file qt/project/spacesetup.cpp
 * \author Michal Steller
 * \brief Visual setup for scene space - class implementation
 */

#include "spacesetup.h"

/*!
 * \brief Constructor
 * \param _arrowX Initial value for setup used for arrows in \b X (1, 0, 0) space dimension
 * \param _arrowY Initial value for setup used for arrows in \b Y (0, 1, 0) space dimension
 * \param _arrowZ Initial value for setup used for arrows in \b Z (0, 0, 1) space dimension
 * \param _dotsXY Initial value for material used for dots or planes in \b X-Y (1, 1, 0) space plane
 * \param _dotsXZ Initial value for material used for dots or planes in \b X-Z (1, 0, 1) space plane
 * \param _dotsYZ Initial value for material used for dots or planes in \b Y-Z (0, 1, 1) space plane
 * \param _dotsXYZ Initial value for material used for dots all space axis directions
 * \param _pointSize Initial value for view point size
 * \param _doubleAxisPointSize Initial value for use double point size for dots on axis flag
 * \param _fixedColorDots Initial value for use fixed dots colors flag
 * \param _showArrowX Initial value for show axis arrow X flag
 * \param _showArrowY Initial value for show axis arrow Y flag
 * \param _showArrowZ Initial value for show axis arrow Z flag
 * \param _showAxisInnerDots Initial value for show inner dots within axis directions
 * \param _showPlaneXY Initial value for show dots in plane X-Y
 * \param _showPlaneXZ Initial value for show dots in plane X-Z
 * \param _showPlaneYZ Initial value for show dots in plane Y-Z
 * \param _showPlaneXYZ Initial value for show all space dots
 * \param _minimumX Initial value for minimum X space coordinate
 * \param _minimumY Initial value for minimum Y space coordinate
 * \param _minimumZ Initial value for minimum Z space coordinate
 * \param _maximumX Initial value for maximum X space coordinate
 * \param _maximumY Initial value for maximum Y space coordinate
 * \param _maximumZ Initial value for maximum Z space coordinate
 */
Universe1::Project::SpaceSetup::SpaceSetup(const ArrowSetup &_arrowX,
                                           const ArrowSetup &_arrowY,
                                           const ArrowSetup &_arrowZ,
                                           const OpenGL::Material &_dotsXY,
                                           const OpenGL::Material &_dotsXZ,
                                           const OpenGL::Material &_dotsYZ,
                                           const OpenGL::Material &_dotsXYZ,
                                           const float _pointSize,
                                           const bool _doubleAxisPointSize,
                                           const bool _fixedColorDots,
                                           const bool _showArrowX,
                                           const bool _showArrowY,
                                           const bool _showArrowZ,
                                           const bool _showAxisInnerDots,
                                           const bool _showPlaneXY,
                                           const bool _showPlaneXZ,
                                           const bool _showPlaneYZ,
                                           const bool _showPlaneXYZ,
                                           const int _minimumX,
                                           const int _minimumY,
                                           const int _minimumZ,
                                           const int _maximumX,
                                           const int _maximumY,
                                           const int _maximumZ)
    : arrowX(_arrowX)
    , arrowY(_arrowY)
    , arrowZ(_arrowZ)
    , dotsXY(_dotsXY)
    , dotsXZ(_dotsXZ)
    , dotsYZ(_dotsYZ)
    , dotsXYZ(_dotsXYZ)
    , pointSize(_pointSize)
    , doubleAxisPointSize(_doubleAxisPointSize)
    , fixedColorDots(_fixedColorDots)
    , showArrowX(_showArrowX)
    , showArrowY(_showArrowY)
    , showArrowZ(_showArrowZ)
    , showAxisInnerDots(_showAxisInnerDots)
    , showPlaneXY(_showPlaneXY)
    , showPlaneXZ(_showPlaneXZ)
    , showPlaneYZ(_showPlaneYZ)
    , showPlaneXYZ(_showPlaneXYZ)
    , minimumX(_minimumX)
    , minimumY(_minimumY)
    , minimumZ(_minimumZ)
    , maximumX(_maximumX)
    , maximumY(_maximumY)
    , maximumZ(_maximumZ)
{
}

#define SPACESETUP_DEFAULT_ARROW_RADIUS_LINE 0.02F  //!< Default arrow line radius ratio
#define SPACESETUP_DEFAULT_ARROW_RADIUS_HEAD 0.15F  //!< Default arrow head radius ratio
#define SPACESETUP_DEFAULT_ARROW_LENGTH_HEAD 0.25F  //!< Default arrow head length ratio
#define SPACESETUP_DEFAULT_ARROW_CIRCLE_SIZE 16  //!< Default arrow circle point count
#define SPACESETUP_DEFAULT_ARROW_WIRE_FRAME false  //!< Default arrow wire-frame flag

const Universe1::Project::ArrowSetup Universe1::Project::SpaceSetup::defaultArrowX =
    ArrowSetup(OpenGL::Material::materialRed,
               OpenGL::Material::materialRedLight,
               OpenGL::Material::materialRedDark,
               SPACESETUP_DEFAULT_ARROW_RADIUS_LINE,
               SPACESETUP_DEFAULT_ARROW_RADIUS_HEAD,
               SPACESETUP_DEFAULT_ARROW_LENGTH_HEAD,
               SPACESETUP_DEFAULT_ARROW_CIRCLE_SIZE,
               SPACESETUP_DEFAULT_ARROW_WIRE_FRAME);

const Universe1::Project::ArrowSetup Universe1::Project::SpaceSetup::defaultArrowY =
    ArrowSetup(OpenGL::Material::materialGreen,
               OpenGL::Material::materialGreenLight,
               OpenGL::Material::materialGreenDark,
               SPACESETUP_DEFAULT_ARROW_RADIUS_LINE,
               SPACESETUP_DEFAULT_ARROW_RADIUS_HEAD,
               SPACESETUP_DEFAULT_ARROW_LENGTH_HEAD,
               SPACESETUP_DEFAULT_ARROW_CIRCLE_SIZE,
               SPACESETUP_DEFAULT_ARROW_WIRE_FRAME);

const Universe1::Project::ArrowSetup Universe1::Project::SpaceSetup::defaultArrowZ =
    ArrowSetup(OpenGL::Material::materialBlue,
               OpenGL::Material::materialBlueLight,
               OpenGL::Material::materialBlueDark,
               SPACESETUP_DEFAULT_ARROW_RADIUS_LINE,
               SPACESETUP_DEFAULT_ARROW_RADIUS_HEAD,
               SPACESETUP_DEFAULT_ARROW_LENGTH_HEAD,
               SPACESETUP_DEFAULT_ARROW_CIRCLE_SIZE,
               SPACESETUP_DEFAULT_ARROW_WIRE_FRAME);

#undef SPACESETUP_DEFAULT_ARROW_RADIUS_LINE
#undef SPACESETUP_DEFAULT_ARROW_RADIUS_HEAD
#undef SPACESETUP_DEFAULT_ARROW_LENGTH_HEAD
#undef SPACESETUP_DEFAULT_ARROW_CIRCLE_SIZE
#undef SPACESETUP_DEFAULT_ARROW_WIRE_FRAME
