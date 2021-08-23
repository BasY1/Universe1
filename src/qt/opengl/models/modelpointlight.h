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
    ModelPointLight(const PointLight &_light, const float _radius, QObject *_parent = nullptr);
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
 * \param _light Point light data
 * \param _parent Parent \c QObject
 */
inline ModelPointLight::ModelPointLight(const PointLight &_light, QObject *_parent)
    : ModelPointLight(_light, 1.0F, _parent)
{
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
