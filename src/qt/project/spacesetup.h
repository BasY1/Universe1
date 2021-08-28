/*!
 * \file qt/project/spacesetup.h
 * \author Michal Steller
 * \brief Visual setup for scene space - class declarations
 */

#ifndef UNIVERSE1_PROJECT_SPACESETUP_H
#define UNIVERSE1_PROJECT_SPACESETUP_H

#include "../opengl/lights.h"

#include "arrowsetup.h"

namespace Universe1 {
namespace Project {

#define SPACESETUP_AXIS_DOTS_MATERIAL header  //!< Used arrow part for main axis dots material
#define SPACESETUP_INNER_AXIS_DOTS_MATERIAL bottom  //!< Used arrow part for inner axis dots material
//#define SPACESETUP_INNER_AXIS_DOTS_MATERIAL  line

/*!
 * \brief Tool structure - Visual setup for scene space axis arrows and dots
 */
struct SpaceSetup
{
    ArrowSetup arrowX;  //!< Setup used for arrows in \b X (1, 0, 0) space dimension
    ArrowSetup arrowY;  //!< Setup used for arrows in \b Y (0, 1, 0) space dimension
    ArrowSetup arrowZ;  //!< Setup used for arrows in \b Z (0, 0, 1) space dimension

    OpenGL::Material dotsXY;  //!< Material used for dots or planes in \b X-Y (1, 1, 0) space plane
    OpenGL::Material dotsXZ;  //!< Material used for dots or planes in \b X-Z (1, 0, 1) space plane
    OpenGL::Material dotsYZ;  //!< Material used for dots or planes in \b Y-Z (0, 1, 1) space plane

    OpenGL::Material dotsXYZ;  //!< Material used for dots all space axis directions

    float pointSize;           //!< OpenGL view point size
    bool doubleAxisPointSize;  //!< Flag for use double point size for dots on axis (inner axis dots not doubled)

    bool fixedColorDots;  //!< Use fixed dots colors (Resp. Use material mode: MaterialAmbient on dots)

    bool showArrowX;  //!< Show axis arrow X flag
    bool showArrowY;  //!< Show axis arrow Y flag
    bool showArrowZ;  //!< Show axis arrow Z flag

    bool showAxisInnerDots;  //!< Show inner dots within axis directions

    bool showPlaneXY;   //!< Show dots in plane X-Y
    bool showPlaneXZ;   //!< Show dots in plane X-Z
    bool showPlaneYZ;   //!< Show dots in plane Y-Z
    bool showPlaneXYZ;  //!< Show all space dots

    int minimumX;  //!< Minimum X space coordinate (First X dot)
    int minimumY;  //!< Minimum Y space coordinate (First Y dot)
    int minimumZ;  //!< Minimum Z space coordinate (First Z dot)
    int maximumX;  //!< Maximum X space coordinate (Last X dot)
    int maximumY;  //!< Maximum Y space coordinate (Last Y dot)
    int maximumZ;  //!< Maximum Z space coordinate (Last Z dot)

    static const ArrowSetup defaultArrowX;         //!< Default setup used for arrows in \b X
    static const ArrowSetup defaultArrowY;         //!< Default setup used for arrows in \b Y
    static const ArrowSetup defaultArrowZ;         //!< Default setup used for arrows in \b Z

    SpaceSetup(const ArrowSetup &_arrowX,
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
               const int _maximumZ);

    inline SpaceSetup(const int _minimumX,
                      const int _minimumY,
                      const int _minimumZ,
                      const int _maximumX,
                      const int _maximumY,
                      const int _maximumZ);

    inline SpaceSetup();

    inline OpenGL::Material materialDotsXY() const;
    inline OpenGL::Material materialDotsXZ() const;
    inline OpenGL::Material materialDotsYZ() const;
    inline OpenGL::Material materialDotsXYZ() const;
    inline OpenGL::Material materialDotsX() const;
    inline OpenGL::Material materialDotsY() const;
    inline OpenGL::Material materialDotsZ() const;
    inline OpenGL::Material materialInnerDotsX() const;
    inline OpenGL::Material materialInnerDotsY() const;
    inline OpenGL::Material materialInnerDotsZ() const;
};

/*!
 * \brief Constructor
 * \param _minimumX Initial value for minimum X space coordinate
 * \param _minimumY Initial value for minimum Y space coordinate
 * \param _minimumZ Initial value for minimum Z space coordinate
 * \param _maximumX Initial value for maximum X space coordinate
 * \param _maximumY Initial value for maximum Y space coordinate
 * \param _maximumZ Initial value for maximum Z space coordinate
 */
inline SpaceSetup::SpaceSetup(const int _minimumX,
                              const int _minimumY,
                              const int _minimumZ,
                              const int _maximumX,
                              const int _maximumY,
                              const int _maximumZ)
    : SpaceSetup(defaultArrowX,
                 defaultArrowY,
                 defaultArrowZ,
                 OpenGL::Material::materialAntiRedDark(),
                 OpenGL::Material::materialAntiGreenDark(),
                 OpenGL::Material::materialAntiBlueDark(),
                 OpenGL::Material::materialWhiteDark,
                 1.0F,
                 true,
                 false,
                 true,
                 true,
                 true,
                 true,
                 true,
                 false,
                 false,
                 false,
                 _minimumX,
                 _minimumY,
                 _minimumZ,
                 _maximumX,
                 _maximumY,
                 _maximumZ)
{
}

#define SPACESETUP_DEFAULT_DISTANCE 200  //!< Default initial space range
/*!
 * \brief Default constructor
 */
inline SpaceSetup::SpaceSetup()
    : SpaceSetup(-SPACESETUP_DEFAULT_DISTANCE,
                 -SPACESETUP_DEFAULT_DISTANCE,
                 -SPACESETUP_DEFAULT_DISTANCE,
                 SPACESETUP_DEFAULT_DISTANCE,
                 SPACESETUP_DEFAULT_DISTANCE,
                 SPACESETUP_DEFAULT_DISTANCE)
{
}
#undef SPACESETUP_DEFAULT_DISTANCE

/*!
 * \brief Getter for used material for X-Y dots
 * \returns Used material for X-Y dots
 */
inline OpenGL::Material SpaceSetup::materialDotsXY() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS, dotsXY);
}

/*!
 * \brief Getter for used material for X-Z dots
 * \returns Used material for X-Z dots
 */
inline OpenGL::Material SpaceSetup::materialDotsXZ() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS, dotsXZ);
}

/*!
 * \brief Getter for used material for Y-Z dots
 * \returns Used material for Y-Z dots
 */
inline OpenGL::Material SpaceSetup::materialDotsYZ() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS, dotsYZ);
}

/*!
 * \brief Getter for used material for X-Y-Z dots
 * \returns Used material for X-Y-Z dots
 */
inline OpenGL::Material SpaceSetup::materialDotsXYZ() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            dotsXYZ);
}

/*!
 * \brief Getter for used material for axis X dots
 * \returns Used material for axis X dots
 */
inline OpenGL::Material SpaceSetup::materialDotsX() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowX.SPACESETUP_AXIS_DOTS_MATERIAL);
}

/*!
 * \brief Getter for used material for axis Y dots
 * \returns Used material for axis Y dots
 */
inline OpenGL::Material SpaceSetup::materialDotsY() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowY.SPACESETUP_AXIS_DOTS_MATERIAL);
}

/*!
 * \brief Getter for used material for axis Z dots
 * \returns Used material for axis Z dots
 */
inline OpenGL::Material SpaceSetup::materialDotsZ() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowZ.SPACESETUP_AXIS_DOTS_MATERIAL);
}

/*!
 * \brief Getter for used material for axis X inner dots
 * \returns Used material for axis X inner dots
 */
inline OpenGL::Material SpaceSetup::materialInnerDotsX() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowX.SPACESETUP_INNER_AXIS_DOTS_MATERIAL);
}

/*!
 * \brief Getter for used material for axis Y inner dots
 * \returns Used material for axis Y inner dots
 */
inline OpenGL::Material SpaceSetup::materialInnerDotsY() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowY.SPACESETUP_INNER_AXIS_DOTS_MATERIAL);
}

/*!
 * \brief Getter for used material for axis Z inner dots
 * \returns Used material for axis Z inner dots
 */
inline OpenGL::Material SpaceSetup::materialInnerDotsZ() const
{
    return OpenGL::Material(fixedColorDots ? OpenGL::Material::MaterialAmbient : OpenGL::Material::MaterialADS,
                            arrowZ.SPACESETUP_INNER_AXIS_DOTS_MATERIAL);
}

#undef SPACESETUP_AXIS_DOTS_MATERIAL
#undef SPACESETUP_INNER_AXIS_DOTS_MATERIAL

}  // namespace Project
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::Project::SpaceSetup)

#endif  // UNIVERSE1_PROJECT_SPACESETUP_H
