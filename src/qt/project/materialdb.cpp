/*!
 * \file qt/project/materialdb.cpp
 * \author Michal Steller
 * \brief The project material database class implementation
 */

#include "materialdb.h"

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
