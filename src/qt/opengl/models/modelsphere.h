/*!
 * \file qt/opengl/models/modelsphere.h
 * \author Michal Steller
 * \brief Open GL single sphere model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELSPHERE_H
#define UNIVERSE1_OPENGL_MODELS_MODELSPHERE_H

#include "materialmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single sphere model
 */
class ModelSphere : public MaterialModel
{
    Q_OBJECT
 public:
    ModelSphere(const Material &_material,
                const QVector3D &_position,
                const QVector3D &_toPole,
                const QVector3D &_toEquator,
                const float _radius,
                const int _equatorPointCount,
                QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material,
                       const QVector3D &_position,
                       const QVector3D &_toPole,
                       const QVector3D &_toEquator,
                       const float _radius,
                       QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material,
                       const QVector3D &_position,
                       const QVector3D &_toPole,
                       const float _radius,
                       const int _equatorPointCount,
                       QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material,
                       const QVector3D &_position,
                       const QVector3D &_toPole,
                       const float _radius,
                       QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material,
                       const QVector3D &_position,
                       const float _radius,
                       const int _equatorPointCount,
                       QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material,
                       const QVector3D &_position,
                       const float _radius,
                       QObject *_parent = nullptr);

    inline ModelSphere(const Material &_material, QObject *_parent = nullptr);

    inline const QVector3D &position() const;
    inline const QVector3D &toPole() const;
    inline const QVector3D &toEquator() const;
    inline float radius() const;
    inline int equatorPointCount() const;

 public slots:
    void setPosition(const QVector3D &_value);
    void setNormal(const QVector3D &_toPole, const QVector3D &_toEquator);
    void setRadius(float _value);
    void setEquatorPointCount(int _value);

 protected:
    void rebuild();

 protected:
    QVector3D m_position;     //!< Sphere position
    QVector3D m_toPole;       //!< Sphere normal 1 (direction from center to pole)
    QVector3D m_toEquator;    //!< Sphere normal 2 (direction from center to equator)
    float m_radius;           //!< Sphere radius
    int m_equatorPointCount;  //!< Point count on equator

    static const int defaultPointCount{64};  //!< Default value for point count on equator
    static QVector3D perpendicularVector(const QVector3D &_pole);
    static void initNormals(QVector3D &_pole, QVector3D &_equator);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _toPole Sphere normal 1 (direction from center to pole)
 * \param _toEquator Sphere normal 2 (direction from center to equator)
 * \param _radius Sphere radius
 * \param _parent Parent \c QObject
 */
inline ModelSphere::ModelSphere(const Material &_material,
                                const QVector3D &_position,
                                const QVector3D &_toPole,
                                const QVector3D &_toEquator,
                                const float _radius,
                                QObject *_parent)
    : ModelSphere(_material, _position, _toPole, _toEquator, _radius, defaultPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _toPole Sphere normal 1 (direction from center to pole)
 * \param _radius Sphere radius
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelSphere::ModelSphere(const Material &_material,
                                const QVector3D &_position,
                                const QVector3D &_toPole,
                                const float _radius,
                                const int _equatorPointCount,
                                QObject *_parent)
    : ModelSphere(_material, _position, _toPole, perpendicularVector(_toPole), _radius, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _toPole Sphere normal 1 (direction from center to pole)
 * \param _radius Sphere radius
 * \param _parent Parent \c QObject
 */
inline ModelSphere::ModelSphere(const Material &_material,
                                const QVector3D &_position,
                                const QVector3D &_toPole,
                                const float _radius,
                                QObject *_parent)
    : ModelSphere(_material, _position, _toPole, perpendicularVector(_toPole), _radius, defaultPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _radius Sphere radius
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelSphere::ModelSphere(const Material &_material,
                                const QVector3D &_position,
                                const float _radius,
                                const int _equatorPointCount,
                                QObject *_parent)
    : ModelSphere(_material,
                  _position,
                  QVector3D(0.0F, 0.0F, 1.0F),
                  QVector3D(1.0F, 0.0F, 0.0F),
                  _radius,
                  _equatorPointCount,
                  _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _radius Sphere radius
 * \param _parent Parent \c QObject
 */
inline ModelSphere::ModelSphere(const Material &_material,
                                const QVector3D &_position,
                                const float _radius,
                                QObject *_parent)
    : ModelSphere(_material,
                  _position,
                  QVector3D(0.0F, 0.0F, 1.0F),
                  QVector3D(1.0F, 0.0F, 0.0F),
                  _radius,
                  defaultPointCount,
                  _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _parent Parent \c QObject
 * \note Position [0, 0, 0], radius 1
 */
inline ModelSphere::ModelSphere(const Material &_material, QObject *_parent)
    : ModelSphere(_material,
                  QVector3D(),
                  QVector3D(0.0F, 0.0F, 1.0F),
                  QVector3D(1.0F, 0.0F, 0.0F),
                  1.0F,
                  defaultPointCount,
                  _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for sphere position
 * \returns Sphere position
 */
inline const QVector3D &ModelSphere::position() const
{
    return m_position;
}

/*!
 * \brief Getter for sphere normal 1 (direction from center to pole)
 * \returns Sphere normal 1
 */
inline const QVector3D &ModelSphere::toPole() const
{
    return m_toPole;
}

/*!
 * \brief Getter for sphere normal 2 (direction from center to equator)
 * \returns Sphere normal 2
 */
inline const QVector3D &ModelSphere::toEquator() const
{
    return m_toEquator;
}

/*!
 * \brief Getter for sphere radius
 * \returns Sphere radius
 */
inline float ModelSphere::radius() const
{
    return m_radius;
}

/*!
 * \brief Getter for point count on equator
 * \returns Point count on equator
 */
inline int ModelSphere::equatorPointCount() const
{
    return m_equatorPointCount;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELSPHERE_H
