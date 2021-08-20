/*!
 * \file qt/opengl/models/meshmodel.h
 * \author Michal Steller
 * \brief Base Open GL mesh model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MESHMODEL_H
#define UNIVERSE1_OPENGL_MODELS_MESHMODEL_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL mesh model (object)
 */
class MeshModel : public GLModel
{
    Q_OBJECT
 public:
    MeshModel(const Material &_material, QObject *_parent = nullptr);
    ~MeshModel();

    bool isInit() const override;
    bool canSwitchDrawWireFrame() const override;
    bool drawWireFrame() const override;

    size_t memoryUsage() const override;
    std::pair<QVector3D, QVector3D> range() const override;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint> &_triangsData,
                             const std::vector<uint> &_linesData) final;

    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    /*!
     * \brief Rebuild model
     * \returns
     */
    virtual void rebuild() = 0;

 public slots:
    void setDrawWireFrame(bool _value) override;

 protected:
    bool m_isInit;                  //!< OpenGL buffers initialized flag
    bool m_canSwitchDrawWireFrame;  //!< Is possible to switch value of draw wire-framed flag
    bool m_drawWireFrame;           //!< Draw wire-framed flag

 private:
    size_t m_memoryUsage;            //!< Memory usage sum
    QVector3D m_minimum;             //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;             //!< Maximum scene range [x, y, z] values
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_triangsIndexes;  //!< Triangles faces index buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_triangsCount;          //!< Triangles faces index buffer item count
    GLsizei m_linesCount;            //!< Line index buffer item count
};


}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MESHMODEL_H
