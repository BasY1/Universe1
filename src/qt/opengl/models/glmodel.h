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
    GLModel(const Material &_material, QObject *_parent = nullptr);

    inline bool isEnabled() const;
    inline const Material &material() const;

    /*!
     * \brief Getter for initialized flag
     * \returns Initialized flag
     */
    virtual bool isInit() const = 0;

    /*!
     * \brief Memory usage: returns size of allocated memory within OpenGL context
     * \returns Size of allocated memory within OpenGL context
     */
    virtual size_t memoryUsage() const = 0;

    /*!
     * \brief Returns object range
     * \returns Object range (pair of 3D vectors minimum [x, y, z] and maximum [x, y, z])
     */
    virtual std::pair<QVector3D, QVector3D> range() const = 0;

    inline QVector3D center() const;

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

    virtual void setMaterial(const Material &_value);

 signals:
    void changed();  //!< Model changed

 protected:
    bool m_enabled;       //!< Enable within paint process flag
    Material m_material;  //!< Model material

 public:
    static QVector3D perpendicularVector(const QVector3D &_pole);
    static void initNormals(QVector3D &_pole, QVector3D &_equator);
};

/*!
 * \brief Getter for enabled flag
 * \returns Enabled flag
 */
inline bool GLModel::isEnabled() const
{
    return m_enabled;
}

/*!
 * \brief Getter for model material
 * \returns Model material
 */
inline const OpenGL::Material &GLModel::material() const
{
    return m_material;
}

/*!
 * \brief Getter for center position
 * \returns Model central position
 * \sa Universe1::OpenGL::Models::GLModel::range() const
 */
inline QVector3D GLModel::center() const
{
    const std::pair<QVector3D, QVector3D> r = range();
    return (r.first + r.second) * 0.5F;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_GLMODEL_H
