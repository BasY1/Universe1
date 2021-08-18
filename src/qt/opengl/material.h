/*!
 * \file qt/opengl/material.h
 * \author Michal Steller
 * \brief The QT Open GL material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MATERIAL_H
#define UNIVERSE1_OPENGL_MATERIAL_H

#include "adscolors.h"

#include <QObject>
#include <unordered_map>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Material properties
 */
struct Material : public ADSColors
{
    float shininess;  //!< Material shininess
    Material();
    Material(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular, const float _shininess);
};

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::Material)

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Material database
 */
class MaterialDB : public QObject
{
    Q_OBJECT
 public:
    MaterialDB(const Material &_material, QObject *_parent = nullptr);

    inline const Material &defaultMaterial() const;
    inline const Material &get(const QString &_name) const;
    inline bool contains(const QString &_name) const;

    QStringList names() const;

    inline void setDefaultMaterial(const Material &_material);

    inline bool add(const QString &_name, const Material &_material);
    inline bool remove(const QString &_name);

 protected:
    Material m_defaultMaterial;                   //!< Default material
    std::unordered_map<QString, Material> m_map;  //!< Hash map buffer
};

/*!
 * \brief Getter for default material
 * \returns Default material
 */
inline const Material &MaterialDB::defaultMaterial() const
{
    return m_defaultMaterial;
}

/*!
 * \brief Test if given name already exists in database
 * \param _name Name to test
 * \returns \c true if given name already exists in database
 */
inline bool MaterialDB::contains(const QString &_name) const
{
    return m_map.find(_name) != m_map.cend();
}

/*!
 * \brief Test if given name already exists in database
 * \param _name Name to test
 * \returns \c true if given name already exists in database
 */
inline const Material &MaterialDB::get(const QString &_name) const
{
    std::unordered_map<QString, Material>::const_iterator it = m_map.find(_name);
    return it == m_map.cend() ? m_defaultMaterial : it->second;
}

/*!
 * \brief Setter for default material
 * \param _material New default material object with values
 */
inline void MaterialDB::setDefaultMaterial(const Material &_material)
{
    m_defaultMaterial = _material;
}

/*!
 * \brief Insert material into database
 * \param _name New material name
 * \param _material New material object with values
 * \returns \c true if insert success
 */
inline bool Universe1::OpenGL::MaterialDB::add(const QString &_name, const Material &_material)
{
    return m_map.insert({_name, _material}).second;
}

/*!
 * \brief Remove material from database
 * \param _name Material name
 * \returns \c true if erase success
 */
inline bool Universe1::OpenGL::MaterialDB::remove(const QString &_name)
{
    return m_map.erase(_name) > 0;
}

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MATERIAL_H
