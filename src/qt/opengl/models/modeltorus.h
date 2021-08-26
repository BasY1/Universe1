/*!
 * \file qt/opengl/models/modeltorus.h
 * \author Michal Steller
 * \brief Open GL torus model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELTORUS_H
#define UNIVERSE1_OPENGL_MODELS_MODELTORUS_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single torus model
 */
class ModelTorus : public MeshModel
{
    Q_OBJECT
 public:
    ModelTorus(const Material &_material,
               const RenderMode _renderMode,
               const bool _invertedFaces,
               const QVector3D &_position,
               const QVector3D &_toPole,
               const QVector3D &_toEquator,
               const float _radiusRing,
               const float _radiusBody,
               const int _circlePointCount,
               QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const QVector3D &_toEquator,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const bool _invertedFaces,
                      QObject *_parent = nullptr);

    //

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const QVector3D &_toEquator,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const QVector3D &_toEquator,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const RenderMode _renderMode,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material, const RenderMode _renderMode, QObject *_parent = nullptr);

    //

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const QVector3D &_toEquator,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const QVector3D &_toEquator,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const QVector3D &_toPole,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      const int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material,
                      const QVector3D &_position,
                      const float _radiusRing,
                      const float _radiusBody,
                      QObject *_parent = nullptr);

    inline ModelTorus(const Material &_material, QObject *_parent = nullptr);

    //

    inline const QVector3D &position() const;
    inline const QVector3D &toPole() const;
    inline const QVector3D &toEquator() const;
    inline float radiusRing() const;
    inline float radiusBody() const;
    inline int circlePointCount() const;

 public slots:
    void setPosition(const QVector3D &_value);
    void setNormal(const QVector3D &_toPole, const QVector3D &_toEquator);
    void setRadiusRing(float _value);
    void setRadiusBody(float _value);
    void setCirclePointCount(int _value);

 protected:
    void rebuild();

 protected:
    QVector3D m_position;    //!< Torus position
    QVector3D m_toPole;      //!< Torus normal 1 (direction from center to pole)
    QVector3D m_toEquator;   //!< Torus normal 2 (direction from center to equator)
    float m_radiusRing;      //!< Torus radius of ring center
    float m_radiusBody;      //!< Torus radius of torus body
    int m_circlePointCount;  //!< Point count on circle
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const QVector3D &_toEquator,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material,
                 _renderMode,
                 _invertedFaces,
                 _position,
                 _toPole,
                 _toEquator,
                 _radiusRing,
                 _radiusBody,
                 defaultCirclePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material,
                 _renderMode,
                 _invertedFaces,
                 _position,
                 _toPole,
                 perpendicularVector(_toPole),
                 _radiusRing,
                 _radiusBody,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material,
                 _renderMode,
                 _invertedFaces,
                 _position,
                 _toPole,
                 perpendicularVector(_toPole),
                 _radiusRing,
                 _radiusBody,
                 defaultCirclePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material,
                 _renderMode,
                 _invertedFaces,
                 _position,
                 QVector3D(0.0F, 0.0F, 1.0F),
                 QVector3D(1.0F, 0.0F, 0.0F),
                 _radiusRing,
                 _radiusBody,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(
          _material, _renderMode, _invertedFaces, _position, _radiusRing, _radiusBody, defaultCirclePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const bool _invertedFaces,
                              QObject *_parent)
    : ModelTorus(_material, _renderMode, _invertedFaces, QVector3D(), 1.0F, 1.0F, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const QVector3D &_toEquator,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material,
                 _renderMode,
                 false,
                 _position,
                 _toPole,
                 _toEquator,
                 _radiusRing,
                 _radiusBody,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const QVector3D &_toEquator,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, _renderMode, false, _position, _toPole, _toEquator, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(
          _material, _renderMode, false, _position, _toPole, _radiusRing, _radiusBody, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, _renderMode, false, _position, _toPole, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material, _renderMode, false, _position, _radiusRing, _radiusBody, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const RenderMode _renderMode,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, _renderMode, false, _position, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material, const RenderMode _renderMode, QObject *_parent)
    : ModelTorus(_material, _renderMode, false, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const QVector3D &_toEquator,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(
          _material, RenderBoth, _position, _toPole, _toEquator, _radiusRing, _radiusBody, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const QVector3D &_toEquator,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, RenderBoth, _position, _toPole, _toEquator, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material, RenderBoth, _position, _toPole, _radiusRing, _radiusBody, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const QVector3D &_toPole,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, RenderBoth, _position, _toPole, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              const int _circlePointCount,
                              QObject *_parent)
    : ModelTorus(_material, RenderBoth, _position, _radiusRing, _radiusBody, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Torus position
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _parent Parent \c QObject
 * \note Default point count on circle
 */
inline ModelTorus::ModelTorus(const Material &_material,
                              const QVector3D &_position,
                              const float _radiusRing,
                              const float _radiusBody,
                              QObject *_parent)
    : ModelTorus(_material, RenderBoth, _position, _radiusRing, _radiusBody, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _parent Parent \c QObject
 */
inline ModelTorus::ModelTorus(const Material &_material, QObject *_parent)
    : ModelTorus(_material, RenderBoth, _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for torus position
 * \returns Torus position
 */
inline const QVector3D &ModelTorus::position() const
{
    return m_position;
}

/*!
 * \brief Getter for torus normal 1 (direction from center to pole)
 * \returns Torus normal 1
 */
inline const QVector3D &ModelTorus::toPole() const
{
    return m_toPole;
}

/*!
 * \brief Getter for torus normal 2 (direction from center to equator)
 * \returns Torus normal 2
 */
inline const QVector3D &ModelTorus::toEquator() const
{
    return m_toEquator;
}

/*!
 * \brief Getter for torus radiusRing
 * \returns Torus radiusRing
 */
inline float ModelTorus::radiusRing() const
{
    return m_radiusRing;
}

/*!
 * \brief Getter for torus radiusBody
 * \returns Torus radiusBody
 */
inline float ModelTorus::radiusBody() const
{
    return m_radiusBody;
}

/*!
 * \brief Getter for point count on circle
 * \returns Point count on circle
 */
inline int ModelTorus::circlePointCount() const
{
    return m_circlePointCount;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELTORUS_H
