/*!
 * \file qt/opengl/models/modelpointlight.h
 * \author Michal Steller
 * \brief Open GL point light model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELPOINTLIGHT_H
#define UNIVERSE1_OPENGL_MODELS_MODELPOINTLIGHT_H

#include "linesmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL point light model
 */
class ModelPointLight : public LinesModel
{
    Q_OBJECT
 public:
    ModelPointLight(const Material &_material,
                    const QVector3D &_position,
                    const float _radius,
                    QObject *_parent = nullptr);

    inline ModelPointLight(const Material &_material, const QVector3D &_position, QObject *_parent = nullptr);

    inline ModelPointLight(const PointLight &_light, const float _radius, QObject *_parent = nullptr);
    inline ModelPointLight(const PointLight &_light, QObject *_parent = nullptr);

    inline const QVector3D &position() const;
    inline float radius() const;

 public slots:
    void setPointLight(const PointLight &_light);

    void setPosition(const QVector3D &_value);
    void setRadius(float _value);

 protected:
    void rebuild();

 protected:
    QVector3D m_position;  //!< Point light position
    float m_radius;        //!< Point light radius
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Point light position
 * \param _parent Point light \c QObject
 */
inline ModelPointLight::ModelPointLight(const Material &_material, const QVector3D &_position, QObject *_parent)
    : ModelPointLight(_material, _position, 1.0F, _parent)
{
}

/*!
 * \brief Constructor
 * \param _light Point light
 * \param _radius Point light radius
 * \param _parent Point light \c QObject
 */
inline ModelPointLight::ModelPointLight(const PointLight &_light, const float _radius, QObject *_parent)
    : ModelPointLight(_light.toMaterial(), _light.position, _radius, _parent)
{
    m_enabled = _light.mode != PointLight::LightOff;
}

/*!
 * \brief Constructor
 * \param _light Point light
 * \param _parent Point light \c QObject
 */
inline ModelPointLight::ModelPointLight(const PointLight &_light, QObject *_parent)
    : ModelPointLight(_light.toMaterial(), _light.position, 1.0F, _parent)
{
    m_enabled = _light.mode != PointLight::LightOff;
}

/*!
 * \brief Getter for point light position
 * \returns Point light position
 */
inline const QVector3D &ModelPointLight::position() const
{
    return m_position;
}

/*!
 * \brief Getter for point light radius
 * \returns Point light radius
 */
inline float ModelPointLight::radius() const
{
    return m_radius;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELPOINTLIGHT_H
