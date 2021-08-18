/*!
 * \file qt/opengl/material.cpp
 * \author Michal Steller
 * \brief The QT Open GL material class implementation
 */

#include "material.h"

/*!
 * \brief Default constructor
 */
Universe1::OpenGL::Material::Material()
    : ADSColors()
    , shininess(0.0F)
{
}

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _shininess Material shininess
 */
Universe1::OpenGL::Material::Material(const QColor &_ambient,
                                      const QColor &_diffuse,
                                      const QColor &_specular,
                                      const float _shininess)
    : ADSColors(_ambient, _diffuse, _specular)
    , shininess(_shininess)
{
}

/*!
 * \brief Constructor
 * \param _material Default material
 * \param _parent parent \c QObject
 */
Universe1::OpenGL::MaterialDB::MaterialDB(const Material &_material, QObject *_parent)
    : QObject(_parent)
    , m_defaultMaterial(_material)
{
}

/*!
 * \brief Getter for present names
 * \returns Names collection
 */
QStringList Universe1::OpenGL::MaterialDB::names() const
{
    QStringList result;
    for (const std::pair<const QString, Material> &p : m_map)
        result.push_back(p.first);
    return result;
}
