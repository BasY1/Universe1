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
    LinesModel(const std::vector<Material> &_materials, QObject *_parent = nullptr);
    inline LinesModel(const Material &_material, QObject *_parent = nullptr);

    ~LinesModel();

    bool isInit() const override;

 protected:
    virtual bool initBuffers(const std::vector<QVector3D> &_vertexData,
                             const std::vector<QVector3D> &_normalData,
                             const std::vector<uint8_t> &_materialData,
                             const std::vector<uint> &_linesData) final;

    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    /*!
     * \brief Rebuild model
     * \returns
     */
    virtual void rebuild() = 0;

 private:
    bool m_hasIndexes;               //!< Using line index buffer flag
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
    QOpenGLBuffer m_linesIndexes;    //!< Line index buffer
    GLsizei m_linesCount;            //!< Line item count
};

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _parent Parent \c QObject
 */
inline LinesModel::LinesModel(const Material &_material, QObject *_parent)
    : LinesModel(std::vector<Material>({_material}), _parent)
{
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_LINESMODEL_H
