/*!
 * \file qt/opengl/models/modelspotlight.h
 * \author Michal Steller
 * \brief Open GL spot light model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELSPOTLIGHT_H
#define UNIVERSE1_OPENGL_MODELS_MODELSPOTLIGHT_H

#include "linesmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL spot light model
 */
class ModelSpotLight : public LinesModel
{
    Q_OBJECT
 public:
    ModelSpotLight(const SpotLight &_light,
                   const float _radius,
                   const int _circlePointCount,
                   QObject *_parent = nullptr);
    inline ModelSpotLight(const SpotLight &_light, const float _radius, QObject *_parent = nullptr);
    inline ModelSpotLight(const SpotLight &_light, QObject *_parent = nullptr);

    inline const QVector3D &position() const;
    inline const QVector3D &direction() const;
    inline float cutOffRad() const;
    inline float outerCutOffRad() const;
    inline float radius() const;
    inline int circlePointCount() const;

 public slots:
    void setSpotLight(const SpotLight &_light);

    void setPosition(const QVector3D &_value);
    void setDirection(const QVector3D &_value);
    void setCutOffRad(float _value);
    void setOuterCutOffRad(float _value);
    void setRadius(float _value);
    void setCirclePointCount(int _value);

 protected:
    void rebuild();

 protected:
    QVector3D m_position;    //!< Spot light position
    QVector3D m_direction;   //!< Spot light direction
    float m_cutOffRad;       //!< Spot light cut-off angle
    float m_outerCutOffRad;  //!< Spot light outer cut-off angle
    float m_radius;          //!< Spot light radius
    int m_circlePointCount;  //!< Point count on circle
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _light Spot light data
 * \param _radius Spot light radius
 * \param _parent Parent \c QObject
 */
inline ModelSpotLight::ModelSpotLight(const SpotLight &_light, const float _radius, QObject *_parent)
    : ModelSpotLight(_light, _radius, defaultCirclePointCount, _parent)
{
}
/*!
 * \brief Constructor
 * \param _light Spot light data
 * \param _parent Parent \c QObject
 */
inline ModelSpotLight::ModelSpotLight(const SpotLight &_light, QObject *_parent)
    : ModelSpotLight(_light, 1.0F, defaultCirclePointCount, _parent)
{
}

/*!
 * \brief Getter for spot light position
 * \returns Spot light position
 */
inline const QVector3D &ModelSpotLight::position() const
{
    return m_position;
}

/*!
 * \brief Getter for spot light direction
 * \returns Spot light direction
 */
inline const QVector3D &ModelSpotLight::direction() const
{
    return m_direction;
}

/*!
 * \brief Getter for spot light cut-off angle
 * \returns Spot light cut-off angle
 */
inline float ModelSpotLight::cutOffRad() const
{
    return m_cutOffRad;
}

/*!
 * \brief Getter for spot light outer cut-off angle
 * \returns Spot light outer cut-off angle
 */
inline float ModelSpotLight::outerCutOffRad() const
{
    return m_outerCutOffRad;
}

/*!
 * \brief Getter for spot light radius
 * \returns Spot light radius
 */
inline float ModelSpotLight::radius() const
{
    return m_radius;
}

/*!
 * \brief Getter for point count on circle
 * \returns Point count on circle
 */
inline int ModelSpotLight::circlePointCount() const
{
    return m_circlePointCount;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELSPOTLIGHT_H
