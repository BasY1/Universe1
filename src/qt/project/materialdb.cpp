/*!
 * \file qt/project/materialdb.cpp
 * \author Michal Steller
 * \brief The project material database class implementation
 */

#include "materialdb.h"

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

/*!
 * \brief Constructor
 * \param _material Default material
 * \param _parent parent \c QObject
 */
Universe1::Project::MaterialDB::MaterialDB(const OpenGL::Material &_material, QObject *_parent)
    : QObject(_parent)
    , m_defaultMaterial(_material)
{
}

/*!
 * \brief Getter for present names
 * \returns Names collection
 */
QStringList Universe1::Project::MaterialDB::names() const
{
    QStringList result;
    for (const std::pair<const QString, OpenGL::Material> &p : m_map)
        result.push_back(p.first);
    return result;
}
