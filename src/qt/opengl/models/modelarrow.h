/*!
 * \file qt/opengl/models/modelarrow.h
 * \author Michal Steller
 * \brief Open GL 3D arrow model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELARROW_H
#define UNIVERSE1_OPENGL_MODELS_MODELARROW_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL arrow model
 */
class ModelArrow : public MeshModel
{
    Q_OBJECT
 public:
    ModelArrow(const Material &_materialLine,
               const Material &_materialHeader,
               const Material &_materialBottom,
               const QVector3D &_fromPosition,
               const QVector3D &_toPosition,
               float _ratioRadiusLine,
               float _ratioRadiusHeader,
               float _ratioLengthHeader,
               int _circlePointCount,
               QObject *_parent = nullptr);

    inline ModelArrow(const Material &_materialLine,
                      const Material &_materialHeader,
                      const Material &_materialBottom,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      float _ratioRadiusLine,
                      float _ratioRadiusHeader,
                      float _ratioLengthHeader,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_materialLine,
                      const Material &_materialHeader,
                      const Material &_materialBottom,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_materialLine,
                      const Material &_materialHeader,
                      const Material &_materialBottom,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_material,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      float _ratioRadiusLine,
                      float _ratioRadiusHeader,
                      float _ratioLengthHeader,
                      int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_material,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      float _ratioRadiusLine,
                      float _ratioRadiusHeader,
                      float _ratioLengthHeader,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_material,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      int _circlePointCount,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_material,
                      const QVector3D &_fromPosition,
                      const QVector3D &_toPosition,
                      QObject *_parent = nullptr);

    inline ModelArrow(const Material &_material, QObject *_parent = nullptr);

    inline const Material &materialLine() const;
    inline const Material &materialHeader() const;
    inline const Material &materialBottom() const;

    inline const QVector3D &fromPosition() const;
    inline const QVector3D &toPosition() const;
    inline float ratioRadiusLine() const;
    inline float ratioRadiusHeader() const;
    inline float ratioLengthHeader() const;
    inline int circlePointCount() const;

    inline float lengthFull() const;
    inline float radiusLine() const;
    inline float radiusHeader() const;
    inline float lengthHeader() const;

 protected:
    void rebuild() override;

 public slots:
    void setArrow(const QVector3D &_fromPosition, const QVector3D &_toPosition);

    void setFromPosition(const QVector3D &_value);
    void setToPosition(const QVector3D &_value);

    void setRatioRadiusLine(float _value);
    void setRatioRadiusHeader(float _value);
    void setRatioLengthHeader(float _value);

    void setCirclePointCount(int _value);

    void setMaterial(const Material &_value) override;
    void setMaterialLine(const Material &_value);
    void setMaterialHeader(const Material &_value);
    void setMaterialBottom(const Material &_value);

 protected:
    QVector3D m_fromPosition;   //!< Arrow begin point position
    QVector3D m_toPosition;     //!< Arrow end point position (Header peak)
    float m_ratioRadiusLine;    //!< Arrow line radius as ratio to full arrow length
    float m_ratioRadiusHeader;  //!< Arrow header circle radius as ratio to full arrow length
    float m_ratioLengthHeader;  //!< Arrow header length as ratio to full arrow length
    int m_circlePointCount;     //!< Point count on circle

    static void prepareRatio(float &_ratioRadiusLine, float &_ratioRadiusHeader, float &_ratioLengthHeader);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _materialLine Initial line material
 * \param _materialHeader Initial header material
 * \param _materialBottom Initial header bottom material
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _ratioRadiusLine Initial arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial arrow header length as ratio to full arrow length
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_materialLine,
                              const Material &_materialHeader,
                              const Material &_materialBottom,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              float _ratioRadiusLine,
                              float _ratioRadiusHeader,
                              float _ratioLengthHeader,
                              QObject *_parent)
    : ModelArrow(_materialLine,
                 _materialHeader,
                 _materialBottom,
                 _fromPosition,
                 _toPosition,
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader,
                 defaultCirclePointCount,
                 _parent)
{
}

#define DEF__ratioRadiusLine 0.025F  //!< Default initial value for arrow line radius
#define DEF__ratioRadiusHeader 0.1F  //!< Default initial value for arrow header circle radius
#define DEF__ratioLengthHeader 0.2F  //!< Default initial value for arrow header length

/*!
 * \brief Constructor
 * \param _materialLine Initial line material
 * \param _materialHeader Initial header material
 * \param _materialBottom Initial header bottom material
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _circlePointCount Initial point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_materialLine,
                              const Material &_materialHeader,
                              const Material &_materialBottom,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              int _circlePointCount,
                              QObject *_parent)
    : ModelArrow(_materialLine,
                 _materialHeader,
                 _materialBottom,
                 _fromPosition,
                 _toPosition,
                 DEF__ratioRadiusLine,
                 DEF__ratioRadiusHeader,
                 DEF__ratioLengthHeader,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _materialLine Initial line material
 * \param _materialHeader Initial header material
 * \param _materialBottom Initial header bottom material
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_materialLine,
                              const Material &_materialHeader,
                              const Material &_materialBottom,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              QObject *_parent)
    : ModelArrow(_materialLine,
                 _materialHeader,
                 _materialBottom,
                 _fromPosition,
                 _toPosition,
                 DEF__ratioRadiusLine,
                 DEF__ratioRadiusHeader,
                 DEF__ratioLengthHeader,
                 defaultCirclePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _ratioRadiusLine Initial arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial arrow header length as ratio to full arrow length
 * \param _circlePointCount Initial point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_material,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              float _ratioRadiusLine,
                              float _ratioRadiusHeader,
                              float _ratioLengthHeader,
                              int _circlePointCount,
                              QObject *_parent)
    : ModelArrow(_material,
                 _material.lighter(),
                 _material.darker(),
                 _fromPosition,
                 _toPosition,
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _ratioRadiusLine Initial arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial arrow header length as ratio to full arrow length
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_material,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              float _ratioRadiusLine,
                              float _ratioRadiusHeader,
                              float _ratioLengthHeader,
                              QObject *_parent)
    : ModelArrow(_material,
                 _material.lighter(),
                 _material.darker(),
                 _fromPosition,
                 _toPosition,
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader,
                 _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _circlePointCount Initial point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_material,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              int _circlePointCount,
                              QObject *_parent)
    : ModelArrow(
          _material, _material.lighter(), _material.darker(), _fromPosition, _toPosition, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_material,
                              const QVector3D &_fromPosition,
                              const QVector3D &_toPosition,
                              QObject *_parent)
    : ModelArrow(_material, _material.lighter(), _material.darker(), _fromPosition, _toPosition, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _parent Parent \c QObject
 */
inline ModelArrow::ModelArrow(const Material &_material, QObject *_parent)
    : ModelArrow(_material, QVector3D(), QVector3D(0.0F, 0.0F, 1.0F), _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for line material
 * \returns Line material
 */
inline const Material &ModelArrow::materialLine() const
{
    return GLModel::m_materials.at(0U);
}

/*!
 * \brief Getter for header material
 * \returns Header material
 */
inline const Material &ModelArrow::materialHeader() const
{
    return GLModel::m_materials.at(2U);
}

/*!
 * \brief Getter for header bottom material
 * \returns Header bottom material
 */
inline const Material &ModelArrow::materialBottom() const
{
    return GLModel::m_materials.at(1U);
}

/*!
 * \brief Getter for begin point position
 * \returns Begin point position
 */
inline const QVector3D &ModelArrow::fromPosition() const
{
    return m_fromPosition;
}

/*!
 * \brief Getter for end point position (Header peak)
 * \returns End point position
 */
inline const QVector3D &ModelArrow::toPosition() const
{
    return m_toPosition;
}

/*!
 * \brief Getter for arrow line radius as ratio to full arrow length
 * \returns Arrow line radius as ratio to full arrow length
 */
inline float ModelArrow::ratioRadiusLine() const
{
    return m_ratioRadiusLine;
}

/*!
 * \brief Getter for arrow header circle radius as ratio to full arrow length
 * \returns Arrow header circle radius as ratio to full arrow length
 */
inline float ModelArrow::ratioRadiusHeader() const
{
    return m_ratioRadiusHeader;
}

/*!
 * \brief Getter for arrow header length as ratio to full arrow length
 * \returns Arrow header length as ratio to full arrow length
 */
inline float ModelArrow::ratioLengthHeader() const
{
    return m_ratioLengthHeader;
}

/*!
 * \brief Getter for point count on circle
 * \returns Point count on circle
 */
inline int ModelArrow::circlePointCount() const
{
    return m_circlePointCount;
}

/*!
 * \brief Getter for header full length (distance between begin and end position)
 * \returns Header full length
 */
inline float ModelArrow::lengthFull() const
{
    return m_fromPosition.distanceToPoint(m_toPosition);
}

/*!
 * \brief Getter for real line radius
 * \returns Real line radius
 */
inline float ModelArrow::radiusLine() const
{
    return m_ratioRadiusLine * lengthFull();
}

/*!
 * \brief Getter for real header circle radius
 * \returns Real header circle radius
 */
inline float ModelArrow::radiusHeader() const
{
    return m_ratioRadiusHeader * lengthFull();
}

/*!
 * \brief Getter for real header length
 * \returns Real header length
 */
inline float ModelArrow::lengthHeader() const
{
    return m_ratioLengthHeader * lengthFull();
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELARROW_H
