/*!
 * \file qt/project/arrowsetup.cpp
 * \author Michal Steller
 * \brief Visual setup for arrows class implementation
 */

#include "arrowsetup.h"

/*!
 * \brief Constructor
 * \param _line Initial arrow line material
 * \param _header Initial arrow header material
 * \param _bottom Initial arrow bottom material
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial header length as ratio to full arrow length
 * \param _circlePointCount Initial point count on circle
 * \param _drawWireFrame Initial draw wire-framed flag
 */
Universe1::Project::ArrowSetup::ArrowSetup(const OpenGL::Material &_line,
                                           const OpenGL::Material &_header,
                                           const OpenGL::Material &_bottom,
                                           const float _ratioRadiusLine,
                                           const float _ratioRadiusHeader,
                                           const float _ratioLengthHeader,
                                           const int _circlePointCount,
                                           const bool _drawWireFrame)
    : line(_line)
    , header(_header)
    , bottom(_bottom)
    , ratioRadiusLine(_ratioRadiusLine)
    , ratioRadiusHeader(_ratioRadiusHeader)
    , ratioLengthHeader(_ratioLengthHeader)
    , circlePointCount(_circlePointCount)
    , drawWireFrame(_drawWireFrame)
{
}
