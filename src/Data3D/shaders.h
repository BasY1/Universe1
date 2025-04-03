/*!
 * \file src/Data3D/shaders.h
 * \brief Open GL shader program tools
 */

#ifndef OPENGL_SHADERS_H
#define OPENGL_SHADERS_H

#include "data3d.h"
#include "../Math/camera.h"

namespace U1 {
namespace OpenGL {

/*! \brief Shader program database */
class Shaders
{
 private:
    std::map<Data3D::GLDataType, QOpenGLShaderProgram *> m_shaders = {};  //!< Shader program collection

 public:
    /*! \brief Default constructor */
    Shaders() = default;

    /*!
     * \brief Initialize all shader programs
     * \return Success flag
     */
    bool init();

    /*!
     * \brief Setup light to material shader
     * \param _lightColor Light color
     * \param _lightDir Light direction
     * \param _lightAmbient Scene ambient factor
     */
    void setupLight(const Math::Vec3F &_lightColor, const Math::Vec3F &_lightDir, const float _lightAmbient);

    /*!
     * \brief Setup camera view to shaders
     * \param _camera Camera position
     */
    void setupCamera(const Math::CamF &_camera);

    /*!
     * \brief Get shader program by the type of 3D object
     * \param _type Data 3D type
     * \return Shader program for 3D data type
     */
    inline QOpenGLShaderProgram *getShader(const Data3D::GLDataType _type)
    {
        if (m_shaders.empty())
        {
            std::cerr << "Error Open GL shaders not initialized!\n";
            return nullptr;
        }

        return m_shaders.at(_type);
    }

    /*!
     * \brief Get shader program by the type of 3D object
     * \param _data Data 3D
     * \return Shader program for 3D data type
     */
    inline QOpenGLShaderProgram *getShader(const Data3D *_data)
    {
        return getShader(_data->glDataType);
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_SHADERS_H
