/*!
 * \file src/Data3D/data3dmaterialsnormalalpha.h
 * \brief Open GL object with per vertex material, and uniform alpha and normal
 */

#ifndef OPENGL_DATA3DMATERIALSNORMALALPHA_H
#define OPENGL_DATA3DMATERIALSNORMALALPHA_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex material, and uniform alpha and normal */
class Data3DMaterialsNormalAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    bool m_isTransparent = false;  //!< Transparency flag

    Math::Vec3F *m_normalData = nullptr;    //!< Per vertex normal data array pointer
    Math::Vec3F *m_ambientData = nullptr;   //!< Per vertex ambient color data array pointer
    Math::Vec3F *m_diffuseData = nullptr;   //!< Per vertex diffuse color data array pointer
    Math::Vec3F *m_specularData = nullptr;  //!< Per vertex specular color data array pointer
    float *m_shineData = nullptr;           //!< Per vertex shine data array pointer
    float *m_alphaData = nullptr;           //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_normalBuffer = nullptr;    //!< Open GL buffer for vertex normal
    QOpenGLBuffer *m_ambientBuffer = nullptr;   //!< Open GL buffer for vertex ambient color
    QOpenGLBuffer *m_diffuseBuffer = nullptr;   //!< Open GL buffer for vertex diffuse color
    QOpenGLBuffer *m_specularBuffer = nullptr;  //!< Open GL buffer for vertex specular color
    QOpenGLBuffer *m_shineBuffer = nullptr;     //!< Open GL buffer for vertex shine
    QOpenGLBuffer *m_alphaBuffer = nullptr;     //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     */
    Data3DMaterialsNormalAlpha(const GLuint _glPrimitive, const size_t _vertexCount, const size_t _indexCount);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _ambientData Vertex diffuse color data pointer
     * \param _diffuseData Vertex specular color data pointer
     * \param _specularData Vertex specular color data pointer
     * \param _shineData Vertex shine data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _indexData Index data pointer
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialsNormalAlpha(const GLuint _glPrimitive,
                               const size_t _vertexCount,
                               const size_t _indexCount,
                               const Math::Vec3F *_vertexData,
                               const Math::Vec3F *_normalData,
                               const Math::Vec3F *_ambientData,
                               const Math::Vec3F *_diffuseData,
                               const Math::Vec3F *_specularData,
                               const float *_shineData,
                               const float *_alphaData,
                               const uint *_indexData);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _ambientData Vertex ambient color data pointer
     * \param _diffuseData Vertex diffuse color data pointer
     * \param _specularData Vertex specular color data pointer
     * \param _shineData Vertex shine data pointer
     * \param _alphaData Vertex alpha data pointer
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialsNormalAlpha(const GLuint _glPrimitive,
                                      const size_t _vertexCount,
                                      const Math::Vec3F *_vertexData,
                                      const Math::Vec3F *_normalData,
                                      const Math::Vec3F *_ambientData,
                                      const Math::Vec3F *_diffuseData,
                                      const Math::Vec3F *_specularData,
                                      const float *_shineData,
                                      const float *_alphaData)
        : Data3DMaterialsNormalAlpha(_glPrimitive,
                                     _vertexCount,
                                     0UL,
                                     _vertexData,
                                     _normalData,
                                     _ambientData,
                                     _diffuseData,
                                     _specularData,
                                     _shineData,
                                     _alphaData,
                                     nullptr)
    {
    }

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
     * \brief Getter for ambient color data pointer (constant version)
     * \return Vertex ambient color data pointer
     */
    inline const Math::Vec3F *ambientData() const
    {
        return m_ambientData;
    }

    /*!
     * \brief Getter for ambient color data pointer
     * \return Vertex ambient color data pointer
     */
    inline Math::Vec3F *ambientData()
    {
        return m_ambientData;
    }

    /*!
     * \brief Getter for diffuse color data pointer (constant version)
     * \return Vertex diffuse color data pointer
     */
    inline const Math::Vec3F *diffuseData() const
    {
        return m_diffuseData;
    }

    /*!
     * \brief Getter for diffuse color data pointer
     * \return Vertex diffuse color data pointer
     */
    inline Math::Vec3F *diffuseData()
    {
        return m_diffuseData;
    }

    /*!
     * \brief Getter for specular color data pointer (constant version)
     * \return Vertex specular color data pointer
     */
    inline const Math::Vec3F *specularData() const
    {
        return m_specularData;
    }

    /*!
     * \brief Getter for specular color data pointer
     * \return Vertex specular color data pointer
     */
    inline Math::Vec3F *specularData()
    {
        return m_specularData;
    }

    /*!
     * \brief Getter for shine data pointer (constant version)
     * \return Vertex shine data pointer
     */
    inline const float *shineData() const
    {
        return m_shineData;
    }

    /*!
     * \brief Getter for shine data pointer
     * \return Vertex shine data pointer
     */
    inline float *shineData()
    {
        return m_shineData;
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
     * \brief Create material Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy material Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind material Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release material Open GL buffers
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
     * \param _material1 Material with alpha at start
     * \param _material2 Material with alpha at end
     * \return 3D cylinder object
     */
    static Data3DMaterialsNormalAlpha *cylinder(const Math::OrientF &_orientation,
                                                const float _length,
                                                const float _radius1,
                                                const float _radius2,
                                                const size_t _quality,
                                                const Math::MaterialRGBA &_material1,
                                                const Math::MaterialRGBA &_material2);

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \return 3D cylinder object
     */
    inline static Data3DMaterialsNormalAlpha *cylinder(const Math::OrientF &_orientation,
                                                       const float _length,
                                                       const float _radius1,
                                                       const float _radius2,
                                                       const size_t _quality,
                                                       const Math::MaterialRGB &_material1,
                                                       const Math::MaterialRGB &_material2,
                                                       const uint8_t _alpha1,
                                                       const uint8_t _alpha2)
    {
        return cylinder(
            _orientation, _length, _radius1, _radius2, _quality, {_material1, _alpha1}, {_material2, _alpha2});
    }

    /*!
     * \brief Create a cylinder 3D object - visible from inside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material1 Material with alpha at start
     * \param _material2 Material with alpha at end
     * \return 3D cylinder object
     */
    static Data3DMaterialsNormalAlpha *cylinderInn(const Math::OrientF &_orientation,
                                                   const float _length,
                                                   const float _radius1,
                                                   const float _radius2,
                                                   const size_t _quality,
                                                   const Math::MaterialRGBA &_material1,
                                                   const Math::MaterialRGBA &_material2);

    /*!
     * \brief Create a cylinder 3D object - visible from inside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \return 3D cylinder object
     */
    inline static Data3DMaterialsNormalAlpha *cylinderInn(const Math::OrientF &_orientation,
                                                          const float _length,
                                                          const float _radius1,
                                                          const float _radius2,
                                                          const size_t _quality,
                                                          const Math::MaterialRGB &_material1,
                                                          const Math::MaterialRGB &_material2,
                                                          const uint8_t _alpha1,
                                                          const uint8_t _alpha2)
    {
        return cylinderInn(
            _orientation, _length, _radius1, _radius2, _quality, {_material1, _alpha1}, {_material2, _alpha2});
    }

    /*!
     * \brief Create a cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material1 Material with alpha at start
     * \param _material2 Material with alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialsNormalAlpha *cylinderArc(const Math::OrientF &_orientation,
                                                   const float _length,
                                                   const float _radiusArc,
                                                   const float _radius1,
                                                   const float _radius2,
                                                   const size_t _qualityArc,
                                                   const size_t _qualityCylinder,
                                                   const Math::MaterialRGBA &_material1,
                                                   const Math::MaterialRGBA &_material2,
                                                   const float _offsetAngle = 0.0f);

    /*!
     * \brief Create a cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    inline static Data3DMaterialsNormalAlpha *cylinderArc(const Math::OrientF &_orientation,
                                                          const float _length,
                                                          const float _radiusArc,
                                                          const float _radius1,
                                                          const float _radius2,
                                                          const size_t _qualityArc,
                                                          const size_t _qualityCylinder,
                                                          const Math::MaterialRGB &_material1,
                                                          const Math::MaterialRGB &_material2,
                                                          const uint8_t _alpha1,
                                                          const uint8_t _alpha2,
                                                          const float _offsetAngle = 0.0f)
    {
        return cylinderArc(_orientation,
                           _length,
                           _radiusArc,
                           _radius1,
                           _radius2,
                           _qualityArc,
                           _qualityCylinder,
                           {_material1, _alpha1},
                           {_material2, _alpha2},
                           _offsetAngle);
    }

    /*!
     * \brief Create a cylinder arc 3D object - visible from inside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material1 Material with alpha at start
     * \param _material2 Material with alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialsNormalAlpha *cylinderArcInn(const Math::OrientF &_orientation,
                                                      const float _length,
                                                      const float _radiusArc,
                                                      const float _radius1,
                                                      const float _radius2,
                                                      const size_t _qualityArc,
                                                      const size_t _qualityCylinder,
                                                      const Math::MaterialRGBA &_material1,
                                                      const Math::MaterialRGBA &_material2,
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
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha1 Alpha at start
     * \param _alpha2 Alpha at end
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    inline static Data3DMaterialsNormalAlpha *cylinderArcInn(const Math::OrientF &_orientation,
                                                             const float _length,
                                                             const float _radiusArc,
                                                             const float _radius1,
                                                             const float _radius2,
                                                             const size_t _qualityArc,
                                                             const size_t _qualityCylinder,
                                                             const Math::MaterialRGB &_material1,
                                                             const Math::MaterialRGB &_material2,
                                                             const uint8_t _alpha1,
                                                             const uint8_t _alpha2,
                                                             const float _offsetAngle = 0.0f)
    {
        return cylinderArcInn(_orientation,
                              _length,
                              _radiusArc,
                              _radius1,
                              _radius2,
                              _qualityArc,
                              _qualityCylinder,
                              {_material1, _alpha1},
                              {_material2, _alpha2},
                              _offsetAngle);
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALSNORMALALPHA_H
