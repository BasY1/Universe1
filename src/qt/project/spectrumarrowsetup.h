/*!
 * \file qt/project/spectrumarrowsetup.h
 * \author Michal Steller
 * \brief Visual setup for spectrum arrows class declarations
 */

#ifndef UNIVERSE1_PROJECT_SPECTRUMARROWSETUP_H
#define UNIVERSE1_PROJECT_SPECTRUMARROWSETUP_H

#include "arrowsetup.h"

namespace Universe1 {
namespace Project {

/*!
 * \brief Tool structure - Visual setup for "spectrum" arrows forces and spins
 */
struct SpectrumArrowSetup
{
    ArrowSetup main;   //!< Arrow setup for main (gravity) vectors
    ArrowSetup red;    //!< Arrow setup for red spectrum only vectors
    ArrowSetup green;  //!< Arrow setup for green spectrum only vectors
    ArrowSetup blue;   //!< Arrow setup for blue spectrum only vectors

    bool showMain;   //!< Show main arrow flag
    bool showRed;    //!< Show red arrow flag
    bool showGreen;  //!< Show green arrow flag
    bool showBlue;   //!< Show blue arrow flag

    SpectrumArrowSetup(const ArrowSetup &_main,
                       const ArrowSetup &_red,
                       const ArrowSetup &_green,
                       const ArrowSetup &_blue,
                       const bool _showMain,
                       const bool _showRed,
                       const bool _showGreen,
                       const bool _showBlue);

    SpectrumArrowSetup(const float _ratioRadiusLine,
                       const float _ratioRadiusHeader,
                       const float _ratioLengthHeader,
                       const bool _showMain,
                       const bool _showRed,
                       const bool _showGreen,
                       const bool _showBlue);

    inline SpectrumArrowSetup(const float _ratioRadiusLine,
                              const float _ratioRadiusHeader,
                              const float _ratioLengthHeader,
                              const bool _showMain);

    inline SpectrumArrowSetup(const float _ratioRadiusLine,
                              const float _ratioRadiusHeader,
                              const float _ratioLengthHeader);
    inline SpectrumArrowSetup();
};

/*!
 * \brief Constructor
 * \param _ratioRadiusLine Arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Arrow header length as ratio to full arrow length
 * \param _showMain Show main arrow flag
 */
inline SpectrumArrowSetup::SpectrumArrowSetup(const float _ratioRadiusLine,
                                              const float _ratioRadiusHeader,
                                              const float _ratioLengthHeader,
                                              const bool _showMain)
    : SpectrumArrowSetup(_ratioRadiusLine, _ratioRadiusHeader, _ratioLengthHeader, _showMain, false, false, false)
{
}

/*!
 * \brief Constructor
 * \param _ratioRadiusLine Arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Arrow header length as ratio to full arrow length
 */
inline SpectrumArrowSetup::SpectrumArrowSetup(const float _ratioRadiusLine,
                                              const float _ratioRadiusHeader,
                                              const float _ratioLengthHeader)
    : SpectrumArrowSetup(_ratioRadiusLine, _ratioRadiusHeader, _ratioLengthHeader, true)
{
}

/*!
 * \brief Constructor
 */
inline SpectrumArrowSetup::SpectrumArrowSetup()
    : SpectrumArrowSetup(0.025F, 0.1F, 0.2F)
{
}

}  // namespace Project
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::Project::SpectrumArrowSetup)

#endif  // UNIVERSE1_PROJECT_SPECTRUMARROWSETUP_H
