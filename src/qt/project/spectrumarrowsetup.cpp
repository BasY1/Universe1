/*!
 * \file qt/project/spectrumarrowsetup.cpp
 * \author Michal Steller
 * \brief Visual setup for scene class implementation
 */

#include "spectrumarrowsetup.h"

/*!
 * \brief Constructor
 * \param _main Arrow setup for main (gravity) vectors
 * \param _red Arrow setup for red spectrum only vectors
 * \param _green Arrow setup for green spectrum only vectors
 * \param _blue Arrow setup for blue spectrum only vectors
 * \param _showMain Show main arrow flag
 * \param _showRed Show red arrow flag
 * \param _showGreen Show green arrow flag
 * \param _showBlue Show blue arrow flag
 */
Universe1::Project::SpectrumArrowSetup::SpectrumArrowSetup(const ArrowSetup &_main,
                                                           const ArrowSetup &_red,
                                                           const ArrowSetup &_green,
                                                           const ArrowSetup &_blue,
                                                           const bool _showMain,
                                                           const bool _showRed,
                                                           const bool _showGreen,
                                                           const bool _showBlue)
    : main(_main)
    , red(_red)
    , green(_green)
    , blue(_blue)
    , showMain(_showMain)
    , showRed(_showRed)
    , showGreen(_showGreen)
    , showBlue(_showBlue)
{
}

/*!
 * \brief Constructor
 * \param _ratioRadiusLine Arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Arrow header length as ratio to full arrow length
 * \param _showMain Show main arrow flag
 * \param _showRed Show red arrow flag
 * \param _showGreen Show green arrow flag
 * \param _showBlue Show blue arrow flag
 */
Universe1::Project::SpectrumArrowSetup::SpectrumArrowSetup(const float _ratioRadiusLine,
                                                           const float _ratioRadiusHeader,
                                                           const float _ratioLengthHeader,
                                                           const bool _showMain,
                                                           const bool _showRed,
                                                           const bool _showGreen,
                                                           const bool _showBlue)
    : main(OpenGL::Material::materialWhite,
           OpenGL::Material::materialWhiteLight,
           OpenGL::Material::materialWhiteDark,
           _ratioRadiusLine,
           _ratioRadiusHeader,
           _ratioLengthHeader)
    , red(OpenGL::Material::materialRed,
          OpenGL::Material::materialRedLight,
          OpenGL::Material::materialRedDark,
          _ratioRadiusLine,
          _ratioRadiusHeader,
          _ratioLengthHeader)
    , green(OpenGL::Material::materialGreen,
            OpenGL::Material::materialGreenLight,
            OpenGL::Material::materialGreenDark,
            _ratioRadiusLine,
            _ratioRadiusHeader,
            _ratioLengthHeader)
    , blue(OpenGL::Material::materialBlue,
           OpenGL::Material::materialBlueLight,
           OpenGL::Material::materialBlueDark,
           _ratioRadiusLine,
           _ratioRadiusHeader,
           _ratioLengthHeader)
    , showMain(_showMain)
    , showRed(_showRed)
    , showGreen(_showGreen)
    , showBlue(_showBlue)
{
}
