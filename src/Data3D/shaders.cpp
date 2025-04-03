/*!
 * \file src/Data3D/shaders.cpp
 * \brief Open GL shader program tools
 */

#include "shaders.h"

#include "data3dpointsbase.h"
#include "data3dpointssize.h"
#include "data3dpointscolor.h"
#include "data3dpointsalpha.h"
#include "data3dpointscoloralpha.h"
#include "data3dpointssizealpha.h"
#include "data3dpointssizecolor.h"
#include "data3dpointssizecoloralpha.h"

#include "data3dmaterialbase.h"
#include "data3dmaterialalpha.h"
#include "data3dmaterialnormal.h"
#include "data3dmaterialnormalalpha.h"
#include "data3dmaterialsbase.h"
#include "data3dmaterialsalpha.h"
#include "data3dmaterialsnormal.h"
#include "data3dmaterialsnormalalpha.h"

#include "data3dtexture.h"
#include "data3dtexturealpha.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Tool function - creates shader program object
 * \param _map Shader program collection
 * \param _type Data 3D type
 * \param _vs Vertex shader code
 * \param _fs Fragment shader code
 * \return Success flag
 */
inline static bool mkShader(std::map<Data3D::GLDataType, QOpenGLShaderProgram *> &_map,
                            const Data3D::GLDataType _type,
                            const std::string &_vs,
                            const std::string &_fs)
{
    QOpenGLShaderProgram *result = new QOpenGLShaderProgram();
    result->addShaderFromSourceCode(QOpenGLShader::Vertex, _vs.c_str());
    result->addShaderFromSourceCode(QOpenGLShader::Fragment, _fs.c_str());
    if (!result->link())
    {
        std::cerr << result->log().toStdString() << "\n";
        delete result;
        return false;
    }
    _map.insert({_type, result});
    return true;
}

bool Shaders::init()
{
    return  //
        mkShader(m_shaders, Data3D::GL_POINTS_Base, Data3DPointsBase::vs, Data3DPointsBase::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_Size, Data3DPointsSize::vs, Data3DPointsSize::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_Color, Data3DPointsColor::vs, Data3DPointsColor::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_Alpha, Data3DPointsAlpha::vs, Data3DPointsAlpha::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_ColorAlpha, Data3DPointsColorAlpha::vs, Data3DPointsColorAlpha::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_SizeAlpha, Data3DPointsSizeAlpha::vs, Data3DPointsSizeAlpha::fs) &&
        mkShader(m_shaders, Data3D::GL_POINTS_SizeColor, Data3DPointsSizeColor::vs, Data3DPointsSizeColor::fs) &&
        mkShader(m_shaders,
                 Data3D::GL_POINTS_SizeColorAlpha,
                 Data3DPointsSizeColorAlpha::vs,
                 Data3DPointsSizeColorAlpha::fs) &&
        //
        mkShader(m_shaders, Data3D::GL_MATERIAL_SINGLE_Base, Data3DMaterialBase::vs, Data3DMaterialBase::fs) &&
        mkShader(m_shaders, Data3D::GL_MATERIAL_SINGLE_Alpha, Data3DMaterialAlpha::vs, Data3DMaterialAlpha::fs) &&
        mkShader(m_shaders, Data3D::GL_MATERIAL_SINGLE_Normal, Data3DMaterialNormal::vs, Data3DMaterialNormal::fs) &&
        mkShader(m_shaders,
                 Data3D::GL_MATERIAL_SINGLE_NormalAlpha,
                 Data3DMaterialNormalAlpha::vs,
                 Data3DMaterialNormalAlpha::fs) &&
        //
        mkShader(m_shaders, Data3D::GL_MATERIAL_VERTEX_Base, Data3DMaterialsBase::vs, Data3DMaterialsBase::fs) &&
        mkShader(m_shaders, Data3D::GL_MATERIAL_VERTEX_Alpha, Data3DMaterialsAlpha::vs, Data3DMaterialsAlpha::fs) &&
        mkShader(m_shaders, Data3D::GL_MATERIAL_VERTEX_Normal, Data3DMaterialsNormal::vs, Data3DMaterialsNormal::fs) &&
        mkShader(m_shaders,
                 Data3D::GL_MATERIAL_VERTEX_NormalAlpha,
                 Data3DMaterialsNormalAlpha::vs,
                 Data3DMaterialsNormalAlpha::fs) &&
        //
        mkShader(m_shaders, Data3D::GL_TEXTURE_Base, Data3DTexture::vs, Data3DTexture::fs) &&
        mkShader(m_shaders, Data3D::GL_TEXTURE_Alpha, Data3DTextureAlpha::vs, Data3DTextureAlpha::fs);
}

/*!
 * \brief Setup light to shader program
 * \param _map Shader program collection
 * \param _type Data 3D type
 * \param _lightColor Light color
 * \param _lightDir Light direction
 * \param _lightAmbient Scene ambient factor
 * \return
 */
inline static void _setupLight(std::map<Data3D::GLDataType, QOpenGLShaderProgram *> &_map,
                               const Data3D::GLDataType _type,
                               const Math::Vec3F &_lightColor,
                               const Math::Vec3F &_lightDir,
                               const float _lightAmbient)
{
    QOpenGLShaderProgram *const &sp = _map.at(_type);
    sp->bind();
    sp->setUniformValue("lightDir", _lightDir.toQVector3D());
    sp->setUniformValue("lightColor", _lightColor.toQVector3D());
    sp->setUniformValue("lightAmbient", _lightAmbient);
    sp->release();
}

void Shaders::setupLight(const Math::Vec3F &_lightColor, const Math::Vec3F &_lightDir, const float _lightAmbient)
{
    if (m_shaders.empty())
    {
        std::cerr << "Error Open GL shaders not initialized!\n";
        return;
    }
    _setupLight(m_shaders, Data3D::GL_MATERIAL_SINGLE_Base, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_SINGLE_Alpha, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_SINGLE_Normal, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_SINGLE_NormalAlpha, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_VERTEX_Base, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_VERTEX_Alpha, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_VERTEX_Normal, _lightColor, _lightDir, _lightAmbient);
    _setupLight(m_shaders, Data3D::GL_MATERIAL_VERTEX_NormalAlpha, _lightColor, _lightDir, _lightAmbient);
}

/*!
 * \brief Setup camera view
 * \param _map Shader program collection
 * \param _type Data 3D type
 * \param _view 4x4 view matrix
 * \return
 */
inline static void _setupCamera1(std::map<Data3D::GLDataType, QOpenGLShaderProgram *> &_map,
                                 const Data3D::GLDataType _type,
                                 const QMatrix4x4 &_view)
{
    QOpenGLShaderProgram *const &sp = _map.at(_type);
    sp->bind();
    sp->setUniformValue("view", _view);
    sp->release();
}

/*!
 * \brief Setup camera view
 * \param _map Shader program collection
 * \param _type Data 3D type
 * \param _camera Camera
 * \param _view 4x4 view matrix
 * \return
 */
inline static void _setupCamera2(std::map<Data3D::GLDataType, QOpenGLShaderProgram *> &_map,
                                 const Data3D::GLDataType _type,
                                 const Math::CamF &_camera,
                                 const QMatrix4x4 &_view)
{
    QOpenGLShaderProgram *const &sp = _map.at(_type);
    sp->bind();
    sp->setUniformValue("view", _view);
    sp->setUniformValue("camera", _camera.position.toQVector3D());
    sp->release();
}

void Shaders::setupCamera(const Math::CamF &_camera)
{
    if (m_shaders.empty())
    {
        std::cerr << "Error Open GL shaders not initialized!\n";
        return;
    }
    const QMatrix4x4 view = _camera.getView();

    _setupCamera1(m_shaders, Data3D::GL_POINTS_Base, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_Size, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_Color, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_Alpha, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_ColorAlpha, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_SizeAlpha, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_SizeColor, view);
    _setupCamera1(m_shaders, Data3D::GL_POINTS_SizeColorAlpha, view);

    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_SINGLE_Base, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_SINGLE_Alpha, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_SINGLE_Normal, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_SINGLE_NormalAlpha, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_VERTEX_Base, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_VERTEX_Alpha, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_VERTEX_Normal, _camera, view);
    _setupCamera2(m_shaders, Data3D::GL_MATERIAL_VERTEX_NormalAlpha, _camera, view);

    _setupCamera1(m_shaders, Data3D::GL_TEXTURE_Base, view);
    _setupCamera1(m_shaders, Data3D::GL_TEXTURE_Alpha, view);
}

}  // namespace OpenGL
}  // namespace U1
