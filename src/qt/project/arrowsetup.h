/*!
 * \file qt/project/arrowsetup.h
 * \author Michal Steller
 * \brief Visual setup for arrows class declarations
 */

#ifndef UNIVERSE1_PROJECT_ARROWSETUP_H
#define UNIVERSE1_PROJECT_ARROWSETUP_H

#include "../opengl/material.h"

namespace Universe1 {
namespace Project {

/*!
 * \brief Tool structure - Visual setup for arrows
 */
struct ArrowSetup
{
    OpenGL::Material line;    //!< Arrow line material
    OpenGL::Material header;  //!< Arrow header material
    OpenGL::Material bottom;  //!< Arrow bottom material

    float ratioRadiusLine;    //!< Arrow line radius as ratio to full arrow length
    float ratioRadiusHeader;  //!< Arrow header circle radius as ratio to full arrow length
    float ratioLengthHeader;  //!< Arrow header length as ratio to full arrow length

    int circlePointCount;  //!< Point count on circle

    bool drawWireFrame;  //!< Draw wire-framed flag

    ArrowSetup(const OpenGL::Material &_line,
               const OpenGL::Material &_header,
               const OpenGL::Material &_bottom,
               const float _ratioRadiusLine,
               const float _ratioRadiusHeader,
               const float _ratioLengthHeader,
               const int _circlePointCount,
               const bool _drawWireFrame);

    inline ArrowSetup(const OpenGL::Material &_allMaterial,
                      const float _ratioRadiusLine,
                      const float _ratioRadiusHeader,
                      const float _ratioLengthHeader,
                      const int _circlePointCount,
                      const bool _drawWireFrame);

    inline ArrowSetup(const OpenGL::Material &_line,
                      const OpenGL::Material &_header,
                      const OpenGL::Material &_bottom,
                      const float _ratioRadiusLine,
                      const float _ratioRadiusHeader,
                      const float _ratioLengthHeader);

    inline ArrowSetup(const OpenGL::Material &_allMaterial,
                      const float _ratioRadiusLine,
                      const float _ratioRadiusHeader,
                      const float _ratioLengthHeader);

    inline ArrowSetup(const OpenGL::Material &_line,
                      const OpenGL::Material &_header,
                      const OpenGL::Material &_bottom,
                      const float _ratioRadiusLine,
                      const float _ratioRadiusHeader);

    inline ArrowSetup(const OpenGL::Material &_allMaterial,
                      const float _ratioRadiusLine,
                      const float _ratioRadiusHeader);

    inline ArrowSetup(const OpenGL::Material &_line, const OpenGL::Material &_header, const OpenGL::Material &_bottom);
    inline ArrowSetup(const OpenGL::Material &_allMaterial);
    inline ArrowSetup();
};

/*!
 * \brief Constructor
 * \param _allMaterial Initial material for line, header and bottom
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial header length as ratio to full arrow length
 * \param _circlePointCount Initial point count on circle
 * \param _drawWireFrame Initial draw wire-framed flag
 * \note header is lighter and bottom is darker material
 * \sa OpenGL::Material::lighter(int)
 * \sa OpenGL::Material::darker(int)
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_allMaterial,
                              const float _ratioRadiusLine,
                              const float _ratioRadiusHeader,
                              const float _ratioLengthHeader,
                              const int _circlePointCount,
                              const bool _drawWireFrame)
    : ArrowSetup(_allMaterial,
                 _allMaterial.lighter(),
                 _allMaterial.darker(),
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader,
                 _circlePointCount,
                 _drawWireFrame)
{
}

/*!
 * \brief Constructor
 * \param _line Initial arrow line material
 * \param _header Initial arrow header material
 * \param _bottom Initial arrow bottom material
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial header length as ratio to full arrow length
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_line,
                              const OpenGL::Material &_header,
                              const OpenGL::Material &_bottom,
                              const float _ratioRadiusLine,
                              const float _ratioRadiusHeader,
                              const float _ratioLengthHeader)
    : ArrowSetup(_line, _header, _bottom, _ratioRadiusLine, _ratioRadiusHeader, _ratioLengthHeader, 32, false)
{
}

/*!
 * \brief Constructor
 * \param _allMaterial Initial material for line, header and bottom
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial header length as ratio to full arrow length
 * \note header is lighter and bottom is darker material
 * \sa OpenGL::Material::lighter(int)
 * \sa OpenGL::Material::darker(int)
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_allMaterial,
                              const float _ratioRadiusLine,
                              const float _ratioRadiusHeader,
                              const float _ratioLengthHeader)
    : ArrowSetup(_allMaterial,
                 _allMaterial.lighter(),
                 _allMaterial.darker(),
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader)
{
}

/*!
 * \brief Constructor
 * \param _line Initial arrow line material
 * \param _header Initial arrow header material
 * \param _bottom Initial arrow bottom material
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_line,
                              const OpenGL::Material &_header,
                              const OpenGL::Material &_bottom,
                              const float _ratioRadiusLine,
                              const float _ratioRadiusHeader)
    : ArrowSetup(_line, _header, _bottom, _ratioRadiusLine, _ratioRadiusHeader, 0.2F)
{
}

/*!
 * \brief Constructor
 * \param _allMaterial Initial material for line, header and bottom
 * \param _ratioRadiusLine Initial line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial header circle radius as ratio to full arrow length
 * \note header is lighter and bottom is darker material
 * \sa OpenGL::Material::lighter(int)
 * \sa OpenGL::Material::darker(int)
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_allMaterial,
                              const float _ratioRadiusLine,
                              const float _ratioRadiusHeader)
    : ArrowSetup(_allMaterial, _allMaterial.lighter(), _allMaterial.darker(), _ratioRadiusLine, _ratioRadiusHeader)
{
}

/*!
 * \brief Constructor
 * \param _line Initial arrow line material
 * \param _header Initial arrow header material
 * \param _bottom Initial arrow bottom material
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_line,
                              const OpenGL::Material &_header,
                              const OpenGL::Material &_bottom)
    : ArrowSetup(_line, _header, _bottom, 0.025F, 0.1F)
{
}

/*!
 * \brief Constructor
 * \param _allMaterial Initial material for line, header and bottom
 * \note header is lighter and bottom is darker material
 * \sa OpenGL::Material::lighter(int)
 * \sa OpenGL::Material::darker(int)
 */
inline ArrowSetup::ArrowSetup(const OpenGL::Material &_allMaterial)
    : ArrowSetup(_allMaterial, _allMaterial.lighter(), _allMaterial.darker())
{
}

/*!
 * \brief Constructor
 */
inline ArrowSetup::ArrowSetup()
    : ArrowSetup(OpenGL::Material(QColor(200, 0, 0), QColor(200, 100, 0), Qt::lightGray),
                 OpenGL::Material(QColor(255, 0, 0), QColor(255, 128, 0), Qt::white),
                 OpenGL::Material(QColor(128, 0, 0), QColor(128, 60, 0), Qt::gray))
{
}

}  // namespace Project
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::Project::ArrowSetup)

#endif  // UNIVERSE1_PROJECT_ARROWSETUP_H
