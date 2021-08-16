/*!
 * \file qt/opengl/models/materialmodel.h
 * \author Michal Steller
 * \brief Base Open GL model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MATERIALMODEL_H
#define UNIVERSE1_OPENGL_MODELS_MATERIALMODEL_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL model (object)
 */
class MaterialModel : public GLModel
{
    Q_OBJECT
 public:
    MaterialModel(const Material &_material, QObject *_parent = nullptr);
    ~MaterialModel();

    inline bool isInit() const;
    inline bool canDrawWireFrame() const;
    inline bool drawWireFrame() const;
    inline const Material &material() const;

    size_t memoryUsage() const;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint> &_triangsData,
                             const std::vector<uint> &_linesData = {}) final;

    void paintGLImlp(ShaderProgram *_program);

 public slots:
    void setDrawWireFrame(bool _value);
    void setMaterial(Material _value);

 protected:
    bool m_isInit;            //!< OpenGL buffers initialized flag
    bool m_canDrawWireFrame;  //!< Is possible draw wire-framed flag
    bool m_drawWireFrame;     //!< Draw wire-framed flag
    Material m_material;      //!< Material

 private:
    size_t m_memoryUsage;            //!< Memory usage sum
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex buffer
    QOpenGLBuffer m_normalBuffer;    //!< Normal buffer
    QOpenGLBuffer m_triangsIndexes;  //!< Triangles faces index buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_triangsCount;          //!< Triangles faces index buffer item count
    GLsizei m_linesCount;            //!< Line index buffer item count
};

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
inline bool MaterialModel::isInit() const
{
    return m_isInit;
}

/*!
 * \brief Getter for is possible draw wire-framed flag
 * \returns Is possible draw wire-framed flag
 */
inline bool MaterialModel::canDrawWireFrame() const
{
    return m_canDrawWireFrame;
}

/*!
 * \brief Getter draw wire-framed flag
 * \returns Draw wire-framed flag
 */
inline bool MaterialModel::drawWireFrame() const
{
    return m_drawWireFrame;
}

/*!
 * \brief Getter for model's material
 * \returns Model's material
 */
inline const Material &MaterialModel::material() const
{
    return m_material;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MATERIALMODEL_H
