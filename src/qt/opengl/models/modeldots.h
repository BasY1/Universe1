/*!
 * \file qt/opengl/models/modeldots.h
 * \author Michal Steller
 * \brief Open GL dots point-cloud model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELDOTS_H
#define UNIVERSE1_OPENGL_MODELS_MODELDOTS_H

#include "glmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Line path Open GL model
 */
class ModelDots : public GLModel
{
    Q_OBJECT
 public:
    ModelDots(const std::vector<QVector3D> &_dotsData,
              const QVector3D &_normal,
              const Material &_material,
              QObject *_parent = nullptr);
    inline ModelDots(const std::vector<QVector3D> &_dotsData, const Material &_material, QObject *_parent = nullptr);
    inline ModelDots(const Material &_material, QObject *_parent = nullptr);

    ~ModelDots();

    bool isInit() const override;

    size_t memoryUsage() const override;
    std::pair<QVector3D, QVector3D> range() const override;

    inline const QVector3D &normal() const;
    inline const std::vector<QVector3D> &dotsData() const;

 protected:
    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    virtual void rebuild();

 public slots:
    void setDots(const std::vector<QVector3D> &_dotsData);
    void setNormal(const QVector3D &_normal);
    void setData(const std::vector<QVector3D> &_dotsData, const QVector3D &_normal);

 protected:
    bool m_isInit;  //!< OpenGL buffers initialized flag

    QVector3D m_normal;                 //!< Dots normal
    std::vector<QVector3D> m_dotsData;  //!< Dots vertex position data

 private:
    size_t m_memoryUsage;            //!< Memory usage sum
    QVector3D m_minimum;             //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;             //!< Maximum scene range [x, y, z] values
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    GLsizei m_dotsCount;             //!< Point item count
};

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _dotsData Initial dots vertex position data
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const std::vector<QVector3D> &_dotsData, const Material &_material, QObject *_parent)
    : ModelDots(_dotsData, QVector3D(0.0F, 0.0F, 1.0F), _material, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const Material &_material, QObject *_parent)
    : ModelDots({}, QVector3D(0.0F, 0.0F, 1.0F), _material, _parent)
{
}

/*!
 * \brief Getter for dots vertex normal
 * \returns Dots vertex normal
 */
inline const QVector3D &ModelDots::normal() const
{
    return m_normal;
}

/*!
 * \brief Getter for dots vertex position data
 * \returns Dots vertex position data
 */
inline const std::vector<QVector3D> &ModelDots::dotsData() const
{
    return m_dotsData;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELDOTS_H
