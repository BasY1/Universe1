/*!
 * \file qt/project/materialdb.h
 * \author Michal Steller
 * \brief The project material database class declarations
 */

#ifndef UNIVERSE1_PROJECT_MATERIALDB_H
#define UNIVERSE1_PROJECT_MATERIALDB_H

#include "scenesetup.h"

#include <QObject>
#include <map>

namespace Universe1 {
namespace Project {

/*!
 * \brief Material database
 */
class MaterialDB : public QObject
{
    Q_OBJECT
 public:
    MaterialDB(const OpenGL::Material &_material, QObject *_parent = nullptr);

    inline const OpenGL::Material &defaultMaterial() const;
    inline const std::map<QString, OpenGL::Material> &map() const;

    inline const OpenGL::Material &get(const QString &_name) const;
    inline bool contains(const QString &_name) const;

    QStringList names() const;

    inline void setDefaultMaterial(const OpenGL::Material &_material);

    inline bool add(const QString &_name, const OpenGL::Material &_material);
    inline bool remove(const QString &_name);

 protected:
    OpenGL::Material m_defaultMaterial;  //!< Default material

    ArrowSetup m_spaceAxisX;  //!< Materials used for arrows in \b X (1, 0, 0) space dimension
    ArrowSetup m_spaceAxisY;  //!< Materials used for arrows in \b Y (0, 1, 0) space dimension
    ArrowSetup m_spaceAxisZ;  //!< Materials used for arrows in \b Z (0, 0, 1) space dimension

    OpenGL::Material m_spacePlaneXY;  //!< Material used for dots or planes in \b X-Y (1, 1, 0) space plane
    OpenGL::Material m_spacePlaneXZ;  //!< Material used for dots or planes in \b X-Z (1, 0, 1) space plane
    OpenGL::Material m_spacePlaneYZ;  //!< Material used for dots or planes in \b Y-Z (0, 1, 1) space plane

    ArrowSetup m_dimension;  //!< Materials used for dimensions, distances, lengths

    ArrowSetup m_velocity;  //!< Materials used for velocity (direction of move) vectors

    ArrowSetup m_force;       //!< Materials used for force or acceleration vectors
    ArrowSetup m_forceRed;    //!< Materials used for "red" force vectors
    ArrowSetup m_forceGreen;  //!< Materials used for "green" force vectors
    ArrowSetup m_forceBlue;   //!< Materials used for "blue" force vectors

    ArrowSetup m_spin;       //!< Materials used for element master spin
    ArrowSetup m_spinRed;    //!< Materials used for "red" spin
    ArrowSetup m_spinGreen;  //!< Materials used for "green" spin
    ArrowSetup m_spinBlue;   //!< Materials used for "blue" spin

    OpenGL::Material m_elementCenterCross;  //!< Materials used for element's center position cross
    OpenGL::Material m_elementSphere;       //!< Materials used for element's sphere
    OpenGL::Material m_elementSphereInner;  //!< Materials used for element's sphere inside (inverted faces sphere)

    std::map<QString, OpenGL::Material> m_map;  //!< Hash map buffer
};

/*!
 * \brief Getter for default material
 * \returns Default material
 */
inline const OpenGL::Material &MaterialDB::defaultMaterial() const
{
    return m_defaultMaterial;
}

/*!
 * \brief Getter for material map
 * \returns Material map
 */
inline const std::map<QString, OpenGL::Material> &MaterialDB::map() const
{
    return m_map;
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
 * \brief Get material by name
 * \param _name Name to find
 * \returns Found material or \a m_defaultMaterial
 */
inline const OpenGL::Material &MaterialDB::get(const QString &_name) const
{
    std::map<QString, OpenGL::Material>::const_iterator it = m_map.find(_name);
    return it == m_map.cend() ? m_defaultMaterial : it->second;
}

/*!
 * \brief Setter for default material
 * \param _material New default material object with values
 */
inline void MaterialDB::setDefaultMaterial(const OpenGL::Material &_material)
{
    m_defaultMaterial = _material;
}

/*!
 * \brief Insert material into database
 * \param _name New material name
 * \param _material New material object with values
 * \returns \c true if insert success
 */
inline bool MaterialDB::add(const QString &_name, const OpenGL::Material &_material)
{
    return m_map.insert({_name, _material}).second;
}

/*!
 * \brief Remove material from database
 * \param _name Material name
 * \returns \c true if erase success
 */
inline bool MaterialDB::remove(const QString &_name)
{
    return m_map.erase(_name) > 0;
}

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_MATERIALDB_H
