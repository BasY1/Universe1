/*!
 * \file qt/opengl/models/modelcylinder.h
 * \author Michal Steller
 * \brief Open GL cylinder model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELCYLINDER_H
#define UNIVERSE1_OPENGL_MODELS_MODELCYLINDER_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single cylinder model
 */
class ModelCylinder : public MeshModel
{
    Q_OBJECT
 public:
    ModelCylinder(const Material &_material,
                  const RenderMode _renderMode,
                  const bool _invertedFaces,
                  const QVector3D &_position,
                  const QVector3D &_toPole,
                  const QVector3D &_toEquator,
                  const float _radius,
                  const float _height,
                  const int _equatorPointCount,
                  QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const QVector3D &_toEquator,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const bool _invertedFaces,
                         QObject *_parent = nullptr);

    //

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const QVector3D &_toEquator,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const QVector3D &_toEquator,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const RenderMode _renderMode,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material, const RenderMode _renderMode, QObject *_parent = nullptr);

    //

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const QVector3D &_toEquator,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const QVector3D &_toEquator,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const QVector3D &_toPole,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         const int _equatorPointCount,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material,
                         const QVector3D &_position,
                         const float _radius,
                         const float _height,
                         QObject *_parent = nullptr);

    inline ModelCylinder(const Material &_material, QObject *_parent = nullptr);

    //

    inline const QVector3D &position() const;
    inline const QVector3D &toPole() const;
    inline const QVector3D &toEquator() const;
    inline float radius() const;
    inline float height() const;
    inline int equatorPointCount() const;

 public slots:
    void setPosition(const QVector3D &_value);
    void setNormal(const QVector3D &_toPole, const QVector3D &_toEquator);
    void setRadius(float _value);
    void setHeight(float _value);
    void setEquatorPointCount(int _value);

 protected:
    void rebuild();

 protected:
    QVector3D m_position;     //!< Cylinder position
    QVector3D m_toPole;       //!< Cylinder normal 1 (direction from center to pole)
    QVector3D m_toEquator;    //!< Cylinder normal 2 (direction from center to equator)
    float m_radius;           //!< Cylinder radius
    float m_height;           //!< Cylinder radius
    int m_equatorPointCount;  //!< Point count on equator
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const QVector3D &_toEquator,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material,
                    _renderMode,
                    _invertedFaces,
                    _position,
                    _toPole,
                    _toEquator,
                    _radius,
                    _height,
                    defaultCirclePointCount,
                    _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material,
                    _renderMode,
                    _invertedFaces,
                    _position,
                    _toPole,
                    perpendicularVector(_toPole),
                    _radius,
                    _height,
                    _equatorPointCount,
                    _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material,
                    _renderMode,
                    _invertedFaces,
                    _position,
                    _toPole,
                    perpendicularVector(_toPole),
                    _radius,
                    _height,
                    defaultCirclePointCount,
                    _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    const QVector3D &_position,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material,
                    _renderMode,
                    _invertedFaces,
                    _position,
                    QVector3D(0.0F, 0.0F, 1.0F),
                    QVector3D(1.0F, 0.0F, 0.0F),
                    _radius,
                    _height,
                    _equatorPointCount,
                    _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    const QVector3D &_position,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(
          _material, _renderMode, _invertedFaces, _position, _radius, _height, defaultCirclePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const bool _invertedFaces,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, _invertedFaces, QVector3D(), 1.0F, 1.0F, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const QVector3D &_toEquator,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(
          _material, _renderMode, false, _position, _toPole, _toEquator, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const QVector3D &_toEquator,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _position, _toPole, _toEquator, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _position, _toPole, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _position, _toPole, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _position, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const RenderMode _renderMode,
                                    const QVector3D &_position,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _position, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material, const RenderMode _renderMode, QObject *_parent)
    : ModelCylinder(_material, _renderMode, false, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const QVector3D &_toEquator,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(
          _material, RenderBoth, _position, _toPole, _toEquator, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const QVector3D &_toEquator,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _position, _toPole, _toEquator, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _position, _toPole, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const QVector3D &_position,
                                    const QVector3D &_toPole,
                                    const float _radius,
                                    const float _height,
                                    QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _position, _toPole, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material,
                                    const QVector3D &_position,
                                    const float _radius,
                                    const float _height,
                                    const int _equatorPointCount,
                                    QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _position, _radius, _height, _equatorPointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Cylinder position
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _parent Parent \c QObject
 * \note Default point count on equator
 */
inline ModelCylinder::ModelCylinder(
    const Material &_material, const QVector3D &_position, const float _radius, const float _height, QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _position, _radius, _height, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _parent Parent \c QObject
 */
inline ModelCylinder::ModelCylinder(const Material &_material, QObject *_parent)
    : ModelCylinder(_material, RenderBoth, _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for cylinder position
 * \returns Cylinder position
 */
inline const QVector3D &ModelCylinder::position() const
{
    return m_position;
}

/*!
 * \brief Getter for cylinder normal 1 (direction from center to pole)
 * \returns Cylinder normal 1
 */
inline const QVector3D &ModelCylinder::toPole() const
{
    return m_toPole;
}

/*!
 * \brief Getter for cylinder normal 2 (direction from center to equator)
 * \returns Cylinder normal 2
 */
inline const QVector3D &ModelCylinder::toEquator() const
{
    return m_toEquator;
}

/*!
 * \brief Getter for cylinder radius
 * \returns Cylinder radius
 */
inline float ModelCylinder::radius() const
{
    return m_radius;
}

/*!
 * \brief Getter for cylinder height
 * \returns Cylinder height
 */
inline float ModelCylinder::height() const
{
    return m_height;
}

/*!
 * \brief Getter for point count on equator
 * \returns Point count on equator
 */
inline int ModelCylinder::equatorPointCount() const
{
    return m_equatorPointCount;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELCYLINDER_H
