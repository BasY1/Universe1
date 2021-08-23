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
    MeshModel(const std::vector<Material> &_materials, QObject *_parent = nullptr);
    inline MeshModel(const Material &_material, QObject *_parent = nullptr);
    ~MeshModel();

    inline bool canSwitchDrawWireFrame() const;
    inline bool drawWireFrame() const;

    bool isInit() const override;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint8_t> &_materialData,
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
    void setDrawWireFrame(bool _value);

 protected:
    bool m_isInit;                  //!< OpenGL buffers initialized flag
    bool m_canSwitchDrawWireFrame;  //!< Is possible to switch value of draw wire-framed flag
    bool m_drawWireFrame;           //!< Draw wire-framed flag

    std::vector<Material> m_materials;  //!< Used materials

 private:
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
    QOpenGLBuffer m_triangsIndexes;  //!< Triangles faces index buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_triangsCount;          //!< Triangles faces index buffer item count
    GLsizei m_linesCount;            //!< Line index buffer item count
};

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _parent Parent \c QObject
 */
inline MeshModel::MeshModel(const Material &_material, QObject *_parent)
    : MeshModel(std::vector<Material>({_material}), _parent)
{
}

/*!
 * \brief Getter for is possible to switch value of draw wire-framed flag
 * \returns Is possible to switch value of draw wire-framed flag
 */
inline bool MeshModel::canSwitchDrawWireFrame() const
{
    return m_canSwitchDrawWireFrame;
}

/*!
 * \brief Getter draw wire-framed flag
 * \returns Draw wire-framed flag
 */
inline bool MeshModel::drawWireFrame() const
{
    return m_drawWireFrame;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MESHMODEL_H
