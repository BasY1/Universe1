/*!
 * \file qt/opengl/models/glmodel.h
 * \author Michal Steller
 * \brief Base Open GL model class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_GLMODEL_H
#define UNIVERSE1_OPENGL_MODELS_GLMODEL_H

#include "../shaderprogram.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL model (object)
 */
class GLModel : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
 public:
    GLModel(QObject *_parent = nullptr);

    inline bool isEnabled() const;

    /*!
     * \brief Memory usage: returns size of allocated memory within OpenGL context
     * \returns Size of allocated memory within OpenGL context
     */
    virtual size_t memoryUsage() const = 0;

    virtual void initGL();
    virtual void paintGL(ShaderProgram *_program);

 protected:
    /*!
     * \brief Initialize Open GL
     * \returns Void
     */
    virtual void initGLImlp() = 0;

    /*!
     * \brief Paint model within Open GL
     * \param _program Shader program
     * \returns Void
     */
    virtual void paintGLImlp(ShaderProgram *_program) = 0;

 public slots:
    void setEnabled(bool _value);

 signals:
    void changed();  //!< Model changed

 protected:
    bool m_enabled;  //!< Enable within paint process flag
};

/*!
 * \brief Getter for enabled flag
 * \returns Enabled flag
 */
inline bool GLModel::isEnabled() const
{
    return m_enabled;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_GLMODEL_H
