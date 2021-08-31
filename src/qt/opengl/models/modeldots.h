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
 * \brief Dots Open GL model
 */
class ModelDots : public GLModel
{
    Q_OBJECT
 public:
    ModelDots(const std::vector<Material> &_materials,
              const std::vector<QVector3D> &_vertexData,
              const std::vector<QVector3D> &_normalData,
              const std::vector<uint8_t> &_materialData,
              QObject *_parent = nullptr);

    ModelDots(const std::vector<Material> &_materials,
              const std::vector<QVector3D> &_vertexData,
              const QVector3D &_normalSingle,
              const std::vector<uint8_t> &_materialData,
              QObject *_parent = nullptr);

    inline ModelDots(const std::vector<Material> &_materials,
                     const std::vector<QVector3D> &_vertexData,
                     const std::vector<uint8_t> &_materialData,
                     QObject *_parent = nullptr);

    inline ModelDots(const Material &_material,
                     const std::vector<QVector3D> &_vertexData,
                     const std::vector<QVector3D> &_normalData,
                     QObject *_parent = nullptr);

    inline ModelDots(const Material &_material,
                     const std::vector<QVector3D> &_vertexData,
                     const QVector3D &_normalSingle,
                     QObject *_parent = nullptr);

    inline ModelDots(const Material &_material, const std::vector<QVector3D> &_vertexData, QObject *_parent = nullptr);
    inline ModelDots(const Material &_material, QObject *_parent = nullptr);

    ~ModelDots();

    bool isInit() const override;

    inline const std::vector<QVector3D> &vertexData() const;
    inline const std::vector<QVector3D> &normalData() const;
    inline const QVector3D &normalSingle() const;
    inline const std::vector<uint8_t> &materialData() const;

 protected:
    void initGLImlp() override;
    void paintGLImlp(ShaderProgram *_program) override;

    virtual void rebuild();

 public slots:
    void setDots(const std::vector<QVector3D> &_vertexData,
                 const std::vector<QVector3D> &_normalData,
                 const std::vector<uint8_t> &_materialData);

    void setDots(const std::vector<QVector3D> &_vertexData, const std::vector<uint8_t> &_materialData);

    void setDots(const std::vector<QVector3D> &_vertexData, const std::vector<QVector3D> &_normalData);
    void setDots(const std::vector<QVector3D> &_vertexData, const QVector3D &_normalSingle);

    void setDots(const std::vector<QVector3D> &_vertexData);

    void setPlaneXY(const int minX, const int minY, const int maxX, const int maxY);

 protected:
    std::vector<QVector3D> m_vertexData;  //!< Dots vertex position data

    std::vector<QVector3D> m_normalData;  //!< Dots vertex normal data
    QVector3D m_normalSingle;             //!< Dots single normal (used only when normal data are empty)

    std::vector<uint8_t> m_materialData;  //!< Dots vertex material data

 private:
    size_t m_memoryUsage;            //!< Memory usage sum
    QVector3D m_minimum;             //!< Minimum scene range [x, y, z] values
    QVector3D m_maximum;             //!< Maximum scene range [x, y, z] values
    QOpenGLBuffer m_vertexBuffer;    //!< Vertex position buffer
    QOpenGLBuffer m_normalBuffer;    //!< Vertex normal buffer
    QOpenGLBuffer m_materialBuffer;  //!< Vertex material buffer
    GLsizei m_dotsCount;             //!< Point item count
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _materials Initial used material collection
 * \param _vertexData Initial vertex positions
 * \param _materialData Initial vertex materials
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const std::vector<Material> &_materials,
                            const std::vector<QVector3D> &_vertexData,
                            const std::vector<uint8_t> &_materialData,
                            QObject *_parent)
    : ModelDots(_materials, _vertexData, QVector3D(0.0F, 0.0F, 1.0F), _materialData, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial used material
 * \param _vertexData Initial vertex positions
 * \param _normalData Initial vertex normals
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const Material &_material,
                            const std::vector<QVector3D> &_vertexData,
                            const std::vector<QVector3D> &_normalData,
                            QObject *_parent)
    : ModelDots({_material}, _vertexData, _normalData, {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial used material
 * \param _vertexData Initial vertex positions
 * \param _normalSingle Initial vertex single normal
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const Material &_material,
                            const std::vector<QVector3D> &_vertexData,
                            const QVector3D &_normalSingle,
                            QObject *_parent)
    : ModelDots({_material}, _vertexData, _normalSingle, {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial used material
 * \param _vertexData Initial vertex positions
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const Material &_material, const std::vector<QVector3D> &_vertexData, QObject *_parent)
    : ModelDots({_material}, _vertexData, QVector3D(0.0F, 0.0F, 1.0F), {}, _parent)
{
}

/*!
 * \brief Constructor
 * \param _material Initial used material
 * \param _parent Parent \c QObject
 */
inline ModelDots::ModelDots(const Material &_material, QObject *_parent)
    : ModelDots({_material}, {}, QVector3D(0.0F, 0.0F, 1.0F), {}, _parent)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for dots vertex position data
 * \returns Dots vertex position data
 */
inline const std::vector<QVector3D> &ModelDots::vertexData() const
{
    return m_vertexData;
}

/*!
 * \brief Getter for dots vertex normal data
 * \returns Dots vertex normal data
 */
inline const std::vector<QVector3D> &ModelDots::normalData() const
{
    return m_normalData;
}

/*!
 * \brief Getter for dots vertex single normal
 * \returns Dots vertex single normal
 */
inline const QVector3D &ModelDots::normalSingle() const
{
    return m_normalSingle;
}

/*!
 * \brief Getter for dots vertex material data
 * \returns Dots vertex material data
 */
inline const std::vector<uint8_t> &ModelDots::materialData() const
{
    return m_materialData;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELDOTS_H
