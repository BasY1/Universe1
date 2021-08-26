/*!
 * \file qt/opengl/models/modelspinarrow.h
 * \author Michal Steller
 * \brief Open GL 3D spin arrow model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELSPINARROW_H
#define UNIVERSE1_OPENGL_MODELS_MODELSPINARROW_H

#include "modelarrow.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL spin arrow model
 */
class ModelSpinArrow : public ModelArrow
{
    Q_OBJECT
 public:
    ModelSpinArrow(const Material &_materialLine,
                   const Material &_materialHeader,
                   const Material &_materialBottom,
                   const QVector3D &_fromPosition,
                   const QVector3D &_toPosition,
                   float _ratioRadiusLine,
                   float _ratioRadiusHeader,
                   float _ratioLengthHeader,
                   int _circlePointCount,
                   QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_materialLine,
                          const Material &_materialHeader,
                          const Material &_materialBottom,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          float _ratioRadiusLine,
                          float _ratioRadiusHeader,
                          float _ratioLengthHeader,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_materialLine,
                          const Material &_materialHeader,
                          const Material &_materialBottom,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          int _circlePointCount,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_materialLine,
                          const Material &_materialHeader,
                          const Material &_materialBottom,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_material,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          float _ratioRadiusLine,
                          float _ratioRadiusHeader,
                          float _ratioLengthHeader,
                          int _circlePointCount,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_material,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          float _ratioRadiusLine,
                          float _ratioRadiusHeader,
                          float _ratioLengthHeader,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_material,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          int _circlePointCount,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_material,
                          const QVector3D &_fromPosition,
                          const QVector3D &_toPosition,
                          QObject *_parent = nullptr);

    inline ModelSpinArrow(const Material &_material, QObject *_parent = nullptr);

 protected:
    void rebuild() override;
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
inline ModelSpinArrow::ModelSpinArrow(const Material &_materialLine,
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
 * \param _circlePointCount Initial point count on circle
 * \param _parent Parent \c QObject
 */
inline ModelSpinArrow::ModelSpinArrow(const Material &_materialLine,
                                      const Material &_materialHeader,
                                      const Material &_materialBottom,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      int _circlePointCount,
                                      QObject *_parent)
    : ModelArrow(
          _materialLine, _materialHeader, _materialBottom, _fromPosition, _toPosition, _circlePointCount, _parent)
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
inline ModelSpinArrow::ModelSpinArrow(const Material &_materialLine,
                                      const Material &_materialHeader,
                                      const Material &_materialBottom,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      QObject *_parent)
    : ModelArrow(_materialLine, _materialHeader, _materialBottom, _fromPosition, _toPosition, _parent)
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
inline ModelSpinArrow::ModelSpinArrow(const Material &_material,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      float _ratioRadiusLine,
                                      float _ratioRadiusHeader,
                                      float _ratioLengthHeader,
                                      int _circlePointCount,
                                      QObject *_parent)
    : ModelArrow(_material,
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
inline ModelSpinArrow::ModelSpinArrow(const Material &_material,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      float _ratioRadiusLine,
                                      float _ratioRadiusHeader,
                                      float _ratioLengthHeader,
                                      QObject *_parent)
    : ModelArrow(
          _material, _fromPosition, _toPosition, _ratioRadiusLine, _ratioRadiusHeader, _ratioLengthHeader, _parent)
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
inline ModelSpinArrow::ModelSpinArrow(const Material &_material,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      int _circlePointCount,
                                      QObject *_parent)
    : ModelArrow(_material, _fromPosition, _toPosition, _circlePointCount, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _parent Parent \c QObject
 */
inline ModelSpinArrow::ModelSpinArrow(const Material &_material,
                                      const QVector3D &_fromPosition,
                                      const QVector3D &_toPosition,
                                      QObject *_parent)
    : ModelArrow(_material, _fromPosition, _toPosition, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material for all arrow parts
 * \param _parent Parent \c QObject
 */
inline ModelSpinArrow::ModelSpinArrow(const Material &_material, QObject *_parent)
    : ModelArrow(_material, _parent)
{
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELSPINARROW_H
