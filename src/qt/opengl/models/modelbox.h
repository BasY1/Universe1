/*!
 * \file qt/opengl/models/modelbox.h
 * \author Michal Steller
 * \brief Open GL 3D box model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELBOX_H
#define UNIVERSE1_OPENGL_MODELS_MODELBOX_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single triangle model
 */
class ModelBox : public MeshModel
{
    Q_OBJECT
 public:
    /*!
     * \brief Normal setup enumeration
     */
    enum NormalSetup
    {
        NormalPrecise,     //!< Precise box normals (24 vertices with plane normal)
        NormalFromCenter,  //!< Normals are in direction from center to vertex (8 vertices and normals)
        Normal45deg        //!< Normals are in 45 degrees with normals
    };
    Q_ENUM(NormalSetup)

    ModelBox(const Material &_material,
             const QVector3D &_center,
             const QVector3D &_normal1,
             const QVector3D &_normal2,
             const NormalSetup _normalSetup,
             const float _boxSize1,
             const float _boxSize2,
             const float _boxSize3,
             QObject *_parent = nullptr);

    inline ModelBox(const Material &_material,
                    const QVector3D &_center,
                    const QVector3D &_normal1,
                    const QVector3D &_normal2,
                    const float _boxSize1,
                    const float _boxSize2,
                    const float _boxSize3,
                    QObject *_parent = nullptr);

    inline ModelBox(const Material &_material,
                    const QVector3D &_center,
                    const float _boxSize1,
                    const float _boxSize2,
                    const float _boxSize3,
                    QObject *_parent = nullptr);

    inline ModelBox(const Material &_material, QObject *_parent = nullptr);

    inline NormalSetup normalSetup() const;

    inline const QVector3D &center() const;
    inline const QVector3D &normal1() const;
    inline const QVector3D &normal2() const;
    inline QVector3D normal3() const;

    inline float boxSize1() const;
    inline float boxSize2() const;
    inline float boxSize3() const;
    inline QVector3D boxSizes() const;

 protected:
    void rebuild() override;

 public slots:
    void setCenter(const QVector3D &_value);

    void setNormals(const QVector3D &_normal1, const QVector3D &_normal2);
    void setNormalSetup(NormalSetup _value);

    void setBoxSize1(float _value);
    void setBoxSize2(float _value);
    void setBoxSize3(float _value);

    void setBoxSizes(const QVector3D &_boxSizes);

 protected:
    NormalSetup m_normalSetup;  //!< Normal setup
    QVector3D m_center;         //!< Box center position
    QVector3D m_normal1;        //!< Main normal
    QVector3D m_normal2;        //!< Second normal
    float m_boxSize1;           //!< Box size 1 (side parallel to main normal)
    float m_boxSize2;           //!< Box size 2 (side parallel to second normal)
    float m_boxSize3;           //!< Box size 3 (side parallel to cross-product normal )
};

/*!
 * \brief Constructor
 * \param _material Material
 * \param _center Box center position
 * \param _normal1 Main normal
 * \param _normal2 Second normal
 * \param _boxSize1 Box size 1
 * \param _boxSize2 Box size 2
 * \param _boxSize3 Box size 3
 * \param _parent Parent \c QObject
 */
inline ModelBox::ModelBox(const Material &_material,
                          const QVector3D &_center,
                          const QVector3D &_normal1,
                          const QVector3D &_normal2,
                          const float _boxSize1,
                          const float _boxSize2,
                          const float _boxSize3,
                          QObject *_parent)
    : ModelBox(_material, _center, _normal1, _normal2, NormalPrecise, _boxSize1, _boxSize2, _boxSize3, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _center Box center position
 * \param _boxSize1 Box size 1
 * \param _boxSize2 Box size 2
 * \param _boxSize3 Box size 3
 * \param _parent Parent \c QObject
 */
inline ModelBox::ModelBox(const Material &_material,
                          const QVector3D &_center,
                          const float _boxSize1,
                          const float _boxSize2,
                          const float _boxSize3,
                          QObject *_parent)
    : ModelBox(_material,
               _center,
               QVector3D(1.0F, 0.0F, 0.0F),
               QVector3D(0.0F, 1.0F, 0.0F),
               NormalPrecise,
               _boxSize1,
               _boxSize2,
               _boxSize3,
               _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Material
 * \param _parent Parent \c QObject
 * \note Center [0, 0, 0], size [1, 1, 1]
 */
inline ModelBox::ModelBox(const Material &_material, QObject *_parent)
    : ModelBox(_material,
               QVector3D(),
               QVector3D(1.0F, 0.0F, 0.0F),
               QVector3D(0.0F, 1.0F, 0.0F),
               NormalPrecise,
               1.0F,
               1.0F,
               1.0F,
               _parent)
{
}

/*!
 * \brief Getter for normal setup
 * \returns Normal setup
 */
inline ModelBox::NormalSetup ModelBox::normalSetup() const
{
    return m_normalSetup;
}

/*!
 * \brief Getter for box center position
 * \returns Box center position
 */
inline const QVector3D &ModelBox::center() const
{
    return m_center;
}

/*!
 * \brief Getter for box main normal
 * \returns Box main normal
 */
inline const QVector3D &ModelBox::normal1() const
{
    return m_normal1;
}

/*!
 * \brief Getter for box second normal
 * \returns Box second normal
 */
inline const QVector3D &ModelBox::normal2() const
{
    return m_normal2;
}

/*!
 * \brief Getter for box third normal (as cross-product of main and second normal)
 * \returns Box third normal
 */
inline QVector3D ModelBox::normal3() const
{
    return QVector3D::crossProduct(m_normal1, m_normal2);  //.normalized();
}

/*!
 * \brief Getter for box size 1
 * \returns Box size 1
 */
inline float ModelBox::boxSize1() const
{
    return m_boxSize1;
}

/*!
 * \brief Getter for box size 2
 * \returns Box size 2
 */
inline float ModelBox::boxSize2() const
{
    return m_boxSize2;
}

/*!
 * \brief Getter for box size 3
 * \returns Box size 3
 */
inline float ModelBox::boxSize3() const
{
    return m_boxSize3;
}

/*!
 * \brief Getter for box sizes
 * \returns Box sizes
 */
inline QVector3D ModelBox::boxSizes() const
{
    return QVector3D(m_boxSize1, m_boxSize2, m_boxSize3);
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELBOX_H
