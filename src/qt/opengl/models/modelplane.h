/*!
 * \file qt/opengl/models/modelplane.h
 * \author Michal Steller
 * \brief Open GL 3D plane model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELPLANE_H
#define UNIVERSE1_OPENGL_MODELS_MODELPLANE_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single triangle model
 */
class ModelPlane : public MeshModel
{
    Q_OBJECT
 public:
    ModelPlane(const Material &_material,
               const QVector3D &_center,
               const QVector3D &_normal1,
               const QVector3D &_normal2,
               const int _dots1,
               const int _dots2,
               QObject *_parent = nullptr);

    inline ModelPlane(const Material &_material,
                      const QVector3D &_center,
                      const QVector3D &_normal1,
                      const QVector3D &_normal2,
                      QObject *_parent = nullptr);

    inline ModelPlane(const Material &_material, QObject *_parent = nullptr);

    inline const QVector3D &center() const;
    inline const QVector3D &normal1() const;
    inline const QVector3D &normal2() const;
    inline QVector3D normal() const;
    inline int dots1() const;
    inline int dots2() const;

 protected:
    void rebuild() override;

 public slots:
    void setCenter(const QVector3D &_value);

    void setNormals(const QVector3D &_normal1, const QVector3D &_normal2);
    void setNormal1(const QVector3D &_value);
    void setNormal2(const QVector3D &_value);

    void setDots(int _value);
    void setDots(int _dots1, int _dots2);
    void setDots1(int _value);
    void setDots2(int _value);

 protected:
    QVector3D m_center;   //!< Plane center position
    QVector3D m_normal1;  //!< First plane normal
    QVector3D m_normal2;  //!< Second plane normal
    int m_dots1;          //!< Dots count over normal 1
    int m_dots2;          //!< Dots count over normal 2
};

/*!
 * \brief Constructor
 * \param _material Material
 * \param _center Plane center position
 * \param _normal1 First plane normal
 * \param _normal2 Second plane normal
 * \param _parent Parent \c QObject
 */
inline ModelPlane::ModelPlane(const Material &_material,
                              const QVector3D &_center,
                              const QVector3D &_normal1,
                              const QVector3D &_normal2,
                              QObject *_parent)
    : ModelPlane(_material, _center, _normal1, _normal2, 5, 5, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _parent Parent \c QObject
 */
inline ModelPlane::ModelPlane(const Material &_material, QObject *_parent)
    : ModelPlane(_material, QVector3D(), QVector3D(1.0F, 0.0F, 0.0F), QVector3D(0.0F, 1.0F, 0.0F), 5, 5, _parent)
{
}

/*!
 * \brief Getter for plane center position
 * \returns Plane center position
 */
inline const QVector3D &ModelPlane::center() const
{
    return m_center;
}

/*!
 * \brief Getter for plane normal 1
 * \returns Plane normal 1
 */
inline const QVector3D &ModelPlane::normal1() const
{
    return m_normal1;
}

/*!
 * \brief Getter for plane normal 2
 * \returns Plane normal 2
 */
inline const QVector3D &ModelPlane::normal2() const
{
    return m_normal2;
}

/*!
 * \brief Getter for real plane normal
 * \returns Real plane normal
 */
inline QVector3D ModelPlane::normal() const
{
    return QVector3D::crossProduct(m_normal1, m_normal2).normalized();
}

/*!
 * \brief Getter for dots count over normal 1
 * \returns Dots count over normal 1
 */
inline int ModelPlane::dots1() const
{
    return m_dots1;
}

/*!
 * \brief Getter for dots count over normal 2
 * \returns Dots count over normal 2
 */
inline int ModelPlane::dots2() const
{
    return m_dots2;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELPLANE_H
