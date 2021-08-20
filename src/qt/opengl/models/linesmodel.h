/*!
 * \file qt/opengl/models/linesmodel.h
 * \author Michal Steller
 * \brief Base Open GL lines model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_LINESMODEL_H
#define UNIVERSE1_OPENGL_MODELS_LINESMODEL_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL lines model (object)
 */
class LinesModel : public GLModel
{
    Q_OBJECT
 public:
    LinesModel(const Material &_material, QObject *_parent = nullptr);
    ~LinesModel();

    bool isInit() const override;

    size_t memoryUsage() const override;
    std::pair<QVector3D, QVector3D> range() const override;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint> &_linesData = {}) final;

    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    /*!
     * \brief Rebuild model
     * \returns
     */
    virtual void rebuild() = 0;

 protected:
    bool m_isInit;                  //!< OpenGL buffers initialized flag

 private:
    bool m_hasIndexes;               //!< Using line index buffer flag
    size_t m_memoryUsage;            //!< Memory usage sum
    QVector3D m_minimum;             //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;             //!< Maximum scene range [x, y, z] values
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_linesCount;            //!< Line item count
};

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_LINESMODEL_H
