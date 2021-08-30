/*!
 * \file qt/opengl/models/modelsingularity.h
 * \author Michal Steller
 * \brief Singularity model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELSINGULARITY_H
#define UNIVERSE1_OPENGL_MODELS_MODELSINGULARITY_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Singularity Open GL model
 */
class ModelSingularity : public GLModel
{
    Q_OBJECT
 public:
    ModelSingularity(const Material &_materialLineOut,
                     const Material &_materialLineIn,
                     const Material &_materialDot,
                     const QVector3D &_position,
                     const float _radius,
                     const float _ratioLine,
                     QObject *_parent = nullptr);
    inline ModelSingularity(const Material &_material,
                            const QVector3D &_position,
                            const float _radius,
                            const float _ratioLine,
                            QObject *_parent = nullptr);

    inline ModelSingularity(const Material &_materialLineOut,
                            const Material &_materialLineIn,
                            const Material &_materialDot,
                            const QVector3D &_position,
                            QObject *_parent = nullptr);

    inline ModelSingularity(const Material &_material, const QVector3D &_position, QObject *_parent = nullptr);

    inline ModelSingularity(const QVector3D &_position, QObject *_parent = nullptr);
    inline ModelSingularity(QObject *_parent = nullptr);

    ~ModelSingularity();

    bool isInit() const override;

    inline const Material &materialLineOut() const;
    inline const Material &materialLineIn() const;
    inline const Material &materialDot() const;
    inline const QVector3D &position() const;
    inline float radius() const;
    inline float ratioLine() const;

 public slots:
    void setPosition(const QVector3D &_value);
    void setRadius(float _value);
    void setRatioLine(float _value);
    void setup(const QVector3D &_position, const float _radius, const float _ratioLine);

 protected:
    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    void rebuild();

 protected:
    bool m_isInit;         //!< OpenGL buffers initialized flag
    QVector3D m_position;  //!< Singularity position
    float m_radius;        //!< Singularity outer radius
    float m_ratioLine;     //!< Singularity line length ratio

 private:
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
};

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Initial position
 * \param _radius Initial radius
 * \param _ratioLine Initial line length ratio
 * \param _parent Parent \c QObject
 */
inline ModelSingularity::ModelSingularity(const Material &_material,
                                          const QVector3D &_position,
                                          const float _radius,
                                          const float _ratioLine,
                                          QObject *_parent)
    : ModelSingularity(_material.darker(), _material, _material.lighter(), _position, _radius, _ratioLine, _parent)
{
}

/*!
 * \brief Constructor
 * \param _materialLineOut Initial material for lines outer vertex
 * \param _materialLineIn Initial material for lines inner vertex
 * \param _materialDot Initial material for dot
 * \param _position Initial position
 * \param _parent Parent \c QObject
 */
inline ModelSingularity::ModelSingularity(const Material &_materialLineOut,
                                          const Material &_materialLineIn,
                                          const Material &_materialDot,
                                          const QVector3D &_position,
                                          QObject *_parent)
    : ModelSingularity(_materialLineOut, _materialLineIn, _materialDot, _position, 0.5F, 0.95F, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _position Initial position
 * \param _parent Parent \c QObject
 */
inline ModelSingularity::ModelSingularity(const Material &_material, const QVector3D &_position, QObject *_parent)
    : ModelSingularity(_material.darker(), _material, _material.lighter(), _position, _parent)
{
}

/*!
 * \brief Constructor
 * \param _position Initial position
 * \param _parent Parent \c QObject
 */
inline ModelSingularity::ModelSingularity(const QVector3D &_position, QObject *_parent)
    : ModelSingularity(OpenGL::Material::materialWhiteDark,
                       OpenGL::Material::materialWhite,
                       OpenGL::Material::materialWhiteLight,
                       _position,
                       _parent)
{
}

/*!
 * \brief Constructor
 * \param _parent Parent \c QObject
 */
inline ModelSingularity::ModelSingularity(QObject *_parent)
    : ModelSingularity(QVector3D(), _parent)
{
}

/*!
 * \brief Getter for line outer vertex material
 * \returns Line outer vertex material
 */
inline const Material &ModelSingularity::materialLineOut() const
{
    return GLModel::m_materials.at(0U);
}

/*!
 * \brief Getter for line inner vertex material
 * \returns Line inner vertex material
 */
inline const Material &ModelSingularity::materialLineIn() const
{
    return GLModel::m_materials.at(1U);
}

/*!
 * \brief Getter for central dot material
 * \returns Central dot material
 */
inline const Material &ModelSingularity::materialDot() const
{
    return GLModel::m_materials.at(2U);
}

/*!
 * \brief Getter for singularity position
 * \returns Singularity position
 */
inline const QVector3D &ModelSingularity::position() const
{
    return m_position;
}

/*!
 * \brief Getter for singularity radius
 * \returns Singularity radius
 */
inline float ModelSingularity::radius() const
{
    return m_radius;
}

/*!
 * \brief Getter for line length ratio
 * \returns Line length ratio
 */
inline float ModelSingularity::ratioLine() const
{
    return m_ratioLine;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELSINGULARITY_H
