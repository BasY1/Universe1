/*!
 * \file src/Data3D/data3dmaterialsnormal.h
 * \brief Open GL object with per vertex material, and uniform alpha and normal
 */

#ifndef OPENGL_DATA3DMATERIALSNORMAL_H
#define OPENGL_DATA3DMATERIALSNORMAL_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex material, and uniform alpha and normal */
class Data3DMaterialsNormal : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    uint8_t m_alpha;               //!< Alpha used for all vertices

    Math::Vec3F *m_normalData = nullptr;    //!< Per vertex normal data array pointer
    Math::Vec3F *m_ambientData = nullptr;   //!< Per vertex ambient color data array pointer
    Math::Vec3F *m_diffuseData = nullptr;   //!< Per vertex diffuse color data array pointer
    Math::Vec3F *m_specularData = nullptr;  //!< Per vertex specular color data array pointer
    float *m_shineData = nullptr;           //!< Per vertex shine data array pointer

    QOpenGLBuffer *m_normalBuffer = nullptr;    //!< Open GL buffer for vertex normal
    QOpenGLBuffer *m_ambientBuffer = nullptr;   //!< Open GL buffer for vertex ambient color
    QOpenGLBuffer *m_diffuseBuffer = nullptr;   //!< Open GL buffer for vertex diffuse color
    QOpenGLBuffer *m_specularBuffer = nullptr;  //!< Open GL buffer for vertex specular color
    QOpenGLBuffer *m_shineBuffer = nullptr;     //!< Open GL buffer for vertex shine

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _alpha Alpha used for all vertices
     */
    Data3DMaterialsNormal(const GLuint _glPrimitive,
                          const size_t _vertexCount,
                          const size_t _indexCount,
                          const uint8_t _alpha);

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
     * \param _indexData Index data pointer
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialsNormal(const GLuint _glPrimitive,
                          const size_t _vertexCount,
                          const size_t _indexCount,
                          const Math::Vec3F *_vertexData,
                          const Math::Vec3F *_normalData,
                          const Math::Vec3F *_ambientData,
                          const Math::Vec3F *_diffuseData,
                          const Math::Vec3F *_specularData,
                          const float *_shineData,
                          const uint *_indexData,
                          const uint8_t _alpha);

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
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialsNormal(const GLuint _glPrimitive,
                                 const size_t _vertexCount,
                                 const Math::Vec3F *_vertexData,
                                 const Math::Vec3F *_normalData,
                                 const Math::Vec3F *_ambientData,
                                 const Math::Vec3F *_diffuseData,
                                 const Math::Vec3F *_specularData,
                                 const float *_shineData,
                                 const uint8_t _alpha)
        : Data3DMaterialsNormal(_glPrimitive,
                                _vertexCount,
                                0UL,
                                _vertexData,
                                _normalData,
                                _ambientData,
                                _diffuseData,
                                _specularData,
                                _shineData,
                                nullptr,
                                _alpha)
    {
    }

    ~Data3DMaterialsNormal();  //!< Destructor

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
     * \brief Vertex alpha getter
     * \return Vertex alpha
     */
    inline uint8_t alpha() const
    {
        return m_alpha;
    }

    /*!
     * \brief Setup vertex alpha
     * \param _alpha New vertex alpha
     */
    inline void setAlpha(const uint8_t _alpha)
    {
        m_alpha = _alpha;
    }

    /*!
     * \brief Setup uniform attributes for Open GL shader programs
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Test if \a m_alpha is lower than 255
     * \return \c true if \a m_alpha is lower than 255
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
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha Alpha
     * \return 3D cylinder object
     */
    static Data3DMaterialsNormal *cylinder(const Math::OrientF &_orientation,
                                           const float _length,
                                           const float _radius1,
                                           const float _radius2,
                                           const size_t _quality,
                                           const Math::MaterialRGB &_material1,
                                           const Math::MaterialRGB &_material2,
                                           const uint8_t _alpha);

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material1 Material at start
     * \param _material2 Material at end
     * \param _alpha Alpha
     * \return 3D cylinder object
     */
    static Data3DMaterialsNormal *cylinderInn(const Math::OrientF &_orientation,
                                              const float _length,
                                              const float _radius1,
                                              const float _radius2,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material1,
                                              const Math::MaterialRGB &_material2,
                                              const uint8_t _alpha);

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
     * \param _alpha Alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialsNormal *cylinderArc(const Math::OrientF &_orientation,
                                              const float _length,
                                              const float _radiusArc,
                                              const float _radius1,
                                              const float _radius2,
                                              const size_t _qualityArc,
                                              const size_t _qualityCylinder,
                                              const Math::MaterialRGB &_material1,
                                              const Math::MaterialRGB &_material2,
                                              const uint8_t _alpha,
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
     * \param _alpha Alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialsNormal *cylinderArcInn(const Math::OrientF &_orientation,
                                                 const float _length,
                                                 const float _radiusArc,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const size_t _qualityArc,
                                                 const size_t _qualityCylinder,
                                                 const Math::MaterialRGB &_material1,
                                                 const Math::MaterialRGB &_material2,
                                                 const uint8_t _alpha,
                                                 const float _offsetAngle = 0.0f);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _alpha Alpha
     * \param _inverted Inverted indexes flag
     * \return 3D path object
     */
    static Data3DMaterialsNormal *path(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                                       const float _radius,
                                       const size_t _quality,
                                       const uint8_t _alpha,
                                       const bool _inverted = false);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _centerPoint Calculated central point
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _alpha Alpha
     * \param _inverted Inverted indexes flag
     * \return 3D path object
     */
    static Data3DMaterialsNormal *path(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                                       const Math::Vec3F &_centerPoint,
                                       const float _radius,
                                       const size_t _quality,
                                       const uint8_t _alpha,
                                       const bool _inverted = false);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _alpha Alpha
     * \param _inverted Inverted indexes flag
     * \return 3D path object
     */
    static Data3DMaterialsNormal *path(const std::vector<std::pair<Math::OrientF, Math::MaterialRGB>> &_path,
                                       const float _radius,
                                       const size_t _quality,
                                       const uint8_t _alpha,
                                       const bool _inverted = false);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _centerPoint Calculated central point
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _alpha Alpha
     * \param _inverted Inverted indexes flag
     * \return 3D path object
     */
    static Data3DMaterialsNormal *path(const std::vector<std::pair<Math::OrientF, Math::MaterialRGB>> &_path,
                                       const Math::Vec3F &_centerPoint,
                                       const float _radius,
                                       const size_t _quality,
                                       const uint8_t _alpha,
                                       const bool _inverted = false);
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALSNORMAL_H
