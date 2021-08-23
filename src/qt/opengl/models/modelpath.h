/*!
 * \file qt/opengl/models/modelpath.h
 * \author Michal Steller
 * \brief Base Open GL line path model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELPATH_H
#define UNIVERSE1_OPENGL_MODELS_MODELPATH_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Line path Open GL model
 */
class ModelPath : public GLModel
{
    Q_OBJECT
 public:
    ModelPath(const std::vector<Material> &_materials,
              const std::vector<QVector3D> &_vertexData,
              const std::vector<QVector3D> &_normalData,
              const std::vector<uint8_t> &_materialData,
              QObject *_parent = nullptr);

    inline ModelPath(const std::vector<Material> &_materials,
                     const std::vector<QVector3D> &_vertexData,
                     const std::vector<uint8_t> &_materialData,
                     QObject *_parent = nullptr);

    inline ModelPath(const Material &_material,
                     const std::vector<QVector3D> &_vertexData,
                     const std::vector<QVector3D> &_normalData,
                     QObject *_parent = nullptr);

    inline ModelPath(const Material &_material, const std::vector<QVector3D> &_vertexData, QObject *_parent = nullptr);

    inline ModelPath(const std::vector<Material> &_materials, QObject *_parent = nullptr);
    inline ModelPath(const Material &_material, QObject *_parent = nullptr);

    ~ModelPath();

    bool isInit() const override;

    inline const std::vector<QVector3D> &vertexData() const;
    inline const std::vector<QVector3D> &normalData() const;
    inline const std::vector<uint8_t> &materialData() const;

 protected:
    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    virtual void rebuild();

 public slots:
    void setPath(const std::vector<QVector3D> &_vertexData,
                 const std::vector<QVector3D> &_normalData,
                 const std::vector<uint8_t> &_materialData);

    void setPath(const std::vector<QVector3D> &_vertexData, const std::vector<uint8_t> &_materialData);
    void setPath(const std::vector<QVector3D> &_vertexData, const std::vector<QVector3D> &_normalData);
    void setPath(const std::vector<QVector3D> &_vertexData);

 protected:
    bool m_isInit;  //!< OpenGL buffers initialized flag

    std::vector<QVector3D> m_vertexData;  //!< Path vertex position data
    std::vector<QVector3D> m_normalData;  //!< Path vertex normal data
    std::vector<uint8_t> m_materialData;  //!< Path vertex material data

 private:
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
    GLsizei m_linesCount;            //!< Line item count
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _materials Initial materials
 * \param _vertexData Initial vertex positions
 * \param _materialData Initial vertex materials
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const std::vector<Material> &_materials,
                            const std::vector<QVector3D> &_vertexData,
                            const std::vector<uint8_t> &_materialData,
                            QObject *_parent)
    : ModelPath(_materials, _vertexData, {}, _materialData, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _vertexData Initial vertex positions
 * \param _normalData Initial vertex normals
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const Material &_material,
                            const std::vector<QVector3D> &_vertexData,
                            const std::vector<QVector3D> &_normalData,
                            QObject *_parent)
    : ModelPath({_material}, _vertexData, _normalData, {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _vertexData Initial vertex positions
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const Material &_material, const std::vector<QVector3D> &_vertexData, QObject *_parent)
    : ModelPath({_material}, _vertexData, {}, {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _materials Initial materials
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const std::vector<Material> &_materials, QObject *_parent)
    : ModelPath(_materials, {}, {}, {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const Material &_material, QObject *_parent)
    : ModelPath({_material}, {}, {}, {}, _parent)
{
}

/*!
 * \brief Getter for path vertex position data
 * \returns Path vertex position data
 */
inline const std::vector<QVector3D> &ModelPath::vertexData() const
{
    return m_vertexData;
}

/*!
 * \brief Getter for path vertex normal data
 * \returns Path vertex normal data
 */
inline const std::vector<QVector3D> &ModelPath::normalData() const
{
    return m_normalData;
}

/*!
 * \brief Getter for path vertex material data
 * \returns Path vertex material data
 */
inline const std::vector<uint8_t> &ModelPath::materialData() const
{
    return m_materialData;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELPATH_H
