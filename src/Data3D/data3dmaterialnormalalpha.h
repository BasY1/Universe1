/*!
 * \file src/Data3D/data3dmaterialnormalalpha.h
 * \brief Open GL object with per vertex normals and alpha and uniform material
 */

#ifndef OPENGL_DATA3DMATERIALNORMALALPHA_H
#define OPENGL_DATA3DMATERIALNORMALALPHA_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex normals and alpha and uniform material */
class Data3DMaterialNormalAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::MaterialRGB m_material;  //!< Material used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    Math::Vec3F *m_normalData = nullptr;  //!< Per vertex normal data array pointer
    float *m_alphaData = nullptr;         //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_normalBuffer = nullptr;  //!< Open GL buffer for vertex normals
    QOpenGLBuffer *m_alphaBuffer = nullptr;   //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _material Material used for all vertices
     */
    Data3DMaterialNormalAlpha(const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const size_t _indexCount,
                              const Math::MaterialRGB &_material);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _material Material used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialNormalAlpha(const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const size_t _indexCount,
                              const Math::Vec3F *_vertexData,
                              const Math::Vec3F *_normalData,
                              const float *_alphaData,
                              const uint *_indexData,
                              const Math::MaterialRGB &_material);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _material Material used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialNormalAlpha(const GLuint _glPrimitive,
                                     const size_t _vertexCount,
                                     const Math::Vec3F *_vertexData,
                                     const Math::Vec3F *_normalData,
                                     const float *_alphaData,
                                     const Math::MaterialRGB &_material)
        : Data3DMaterialNormalAlpha(
              _glPrimitive, _vertexCount, 0UL, _vertexData, _normalData, _alphaData, nullptr, _material)
    {
    }

    ~Data3DMaterialNormalAlpha();  //!< Destructor

    /*!
     * \brief Getter for normal data pointer (constant version)
     * \return Vertex normal data pointer
     */
    inline const Math::Vec3F *normalData() const
    {
        return m_normalData;
    }

    /*!
     * \brief Getter for normal data pointer
     * \return Vertex normal data pointer
     */
    inline Math::Vec3F *normalData()
    {
        return m_normalData;
    }

    /*!
     * \brief Getter for alpha data pointer (constant version)
     * \return Vertex alpha data pointer
     */
    inline const float *alphaData() const
    {
        return m_alphaData;
    }

    /*!
     * \brief Getter for alpha data pointer
     * \return Vertex alpha data pointer
     */
    inline float *alphaData()
    {
        return m_alphaData;
    }

    /*!
     * \brief Vertex material getter
     * \return Vertex material
     */
    inline const Math::MaterialRGB &material() const
    {
        return m_material;
    }

    /*!
     * \brief Setup vertex material
     * \param _material New vertex material
     */
    inline void setMaterial(const Math::MaterialRGB &_material)
    {
        m_material = _material;
    }

    /*!
     * \brief Setup uniform attributes for Open GL shader programs
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Setup transparency flag
     * \param _isTransparent New transparency flag
     */
    inline void setTransparent(const bool _isTransparent)
    {
        m_isTransparent = _isTransparent;
    }

    /*!
     * \brief Transparency flag getter
     * \return Transparency flag
     */
    bool isTransparent() const override;

 protected:
    /*!
     * \brief Create normal and alpha Open GL buffer
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy normal and alpha Open GL buffer
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind normal and alpha Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release normal and alpha Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;

 public:
    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \return 3D cylinder object
     */
    static Data3DMaterialNormalAlpha *cylinder(const Math::OrientF &_orientation,
                                               const float _length,
                                               const float _radius1,
                                               const float _radius2,
                                               const size_t _quality,
                                               const Math::MaterialRGB &_material,
                                               const uint8_t _alpha1,
                                               const uint8_t _alpha2);

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \return 3D cylinder object
     */
    static Data3DMaterialNormalAlpha *cylinderInn(const Math::OrientF &_orientation,
                                                  const float _length,
                                                  const float _radius1,
                                                  const float _radius2,
                                                  const size_t _quality,
                                                  const Math::MaterialRGB &_material,
                                                  const uint8_t _alpha1,
                                                  const uint8_t _alpha2);

    /*!
     * \brief Create a cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material Material
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialNormalAlpha *cylinderArc(const Math::OrientF &_orientation,
                                                  const float _length,
                                                  const float _radiusArc,
                                                  const float _radius1,
                                                  const float _radius2,
                                                  const size_t _qualityArc,
                                                  const size_t _qualityCylinder,
                                                  const Math::MaterialRGB &_material,
                                                  const uint8_t _alpha1,
                                                  const uint8_t _alpha2,
                                                  const float _offsetAngle = 0.0f);

    /*!
     * \brief Create a cylinder arc 3D object - visible from inside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material Material
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialNormalAlpha *cylinderArcInn(const Math::OrientF &_orientation,
                                                     const float _length,
                                                     const float _radiusArc,
                                                     const float _radius1,
                                                     const float _radius2,
                                                     const size_t _qualityArc,
                                                     const size_t _qualityCylinder,
                                                     const Math::MaterialRGB &_material,
                                                     const uint8_t _alpha1,
                                                     const uint8_t _alpha2,
                                                     const float _offsetAngle = 0.0f);
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALNORMALALPHA_H
