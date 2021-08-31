/*!
 * \file qt/opengl/models/glmodel.h
 * \author Michal Steller
 * \brief Base Open GL model class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_GLMODEL_H
#define UNIVERSE1_OPENGL_MODELS_GLMODEL_H

#include "../shaderprogram.h"

#include <cmath>

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Base Open GL model (object)
 */
class GLModel : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
 protected:
    GLModel(const std::vector<Material> &_materials, QObject *_parent = nullptr);

 public:
    inline bool isEnabled() const;

    inline const std::vector<Material> &materials() const;

    inline size_t memoryUsage() const;

    inline const QVector3D &minimum() const;
    inline const QVector3D &maximum() const;
    inline std::pair<QVector3D, QVector3D> range() const;
    inline QVector3D center() const;

    virtual void initGL();
    virtual void paintGL(ShaderProgram *_program);

    /*!
     * \brief Getter for initialized flag
     * \returns Initialized flag
     */
    virtual bool isInit() const = 0;

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

    void clearRange();
    void prepareRange(const std::vector<QVector3D> &_data);

 public slots:
    void setEnabled(bool _value);

    virtual void setMaterial(const Material &_value);
    virtual void setMaterial(int _materialIndex, const Material &_material);
    virtual void setMaterials(const std::vector<Material> &_materials);

    virtual void setMaterialMode(const Material::Mode _mode);
    virtual void setMaterialMode(int _materialIndex, const Material::Mode _mode);

 signals:
    void changed();  //!< Model changed

 protected:
    bool m_enabled;  //!< Enable within paint process flag

    size_t m_memoryUsage;  //!< Memory usage sum

    QVector3D m_minimum;  //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;  //!< Maximum scene range [x, y, z] values

    std::vector<Material> m_materials;  //!< Used materials

 public:
    static QVector3D rotate(const QVector3D &_p, const QVector3D &_n, const float _sa, const float _ca);
    static QVector3D rotate(const QVector3D &_p, const QVector3D &_n, const float _angleRad);
    static QVector3D perpendicularVector(const QVector3D &_pole);
    static void prepareNormals(QVector3D &_pole, QVector3D &_equator);
    static int prepareCirclePointCount(const int _count);

    static const int defaultCirclePointCount{64};  //!< Default value for point count on equator
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
 * \brief Getter for model materials
 * \returns Model materials
 */
inline const std::vector<Material> &GLModel::materials() const
{
    return m_materials;
}

/*!
 * \brief Getter for model Open GL memory usage in bytes
 * \returns Model Open GL memory usage
 */
inline size_t GLModel::memoryUsage() const
{
    return m_memoryUsage;
}

/*!
 * \brief Getter for model minimum scene range [x, y, z] values
 * \returns Minimum model scene range [x, y, z] values
 */
inline const QVector3D &GLModel::minimum() const
{
    return m_minimum;
}

/*!
 * \brief Getter for model maximum scene range [x, y, z] values
 * \returns Maximum model scene range [x, y, z] values
 */
inline const QVector3D &GLModel::maximum() const
{
    return m_maximum;
}

/*!
 * \brief Getter for model scene range
 * \returns Model scene range
 */
inline std::pair<QVector3D, QVector3D> GLModel::range() const
{
    return {m_minimum, m_maximum};
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
