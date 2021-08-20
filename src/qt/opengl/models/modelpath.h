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
    ModelPath(const std::vector<QVector3D> &_pathData, const Material &_material, QObject *_parent = nullptr);
    inline ModelPath(const Material &_material, QObject *_parent = nullptr);

    ~ModelPath();

    bool isInit() const override;

    size_t memoryUsage() const override;
    std::pair<QVector3D, QVector3D> range() const override;

    inline const std::vector<QVector3D> &pathData() const;

 protected:
    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    virtual void rebuild();

 public slots:
    void setPath(const std::vector<QVector3D> &_pathData);

 protected:
    bool m_isInit;  //!< OpenGL buffers initialized flag

    std::vector<QVector3D> m_pathData;  //!< Path vertex position data

 private:
    size_t m_memoryUsage;            //!< Memory usage sum
    QVector3D m_minimum;             //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;             //!< Maximum scene range [x, y, z] values
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    GLsizei m_linesCount;            //!< Line item count
};

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
inline ModelPath::ModelPath(const Material &_material, QObject *_parent)
    : ModelPath({}, _material, _parent)
{
}

/*!
 * \brief Getter for path vertex position data
 * \return Path vertex position data
 */
inline const std::vector<QVector3D> &ModelPath::pathData() const
{
    return m_pathData;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELPATH_H
