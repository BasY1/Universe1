/*!
 * \file src/Data3D/data3dmaterialbase.cpp
 * \brief Open GL object with uniform material, alpha and normal
 */

#include "data3dmaterialbase.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialBase::vs =  //
    Data3D::VS_Header +                     //
    Data3D::VS_Uniforms +                   //
    "out vec3 posOut;\n" +                  //
    "void main() {\n" +                     //
    " posOut = pos;\n" +                    //
    Data3D::VS_InMain +                     //
    "}\n";

const std::string Data3DMaterialBase::fs =                   //
    Data3D::FS_Header +                                      //
    "uniform vec3 normal;\n" +                               //
    "uniform vec3 ambient;\n" +                              //
    "uniform vec3 diffuse;\n" +                              //
    "uniform vec3 specular;\n" +                             //
    "uniform float shine;\n" +                               //
    "uniform float alpha;\n" +                               //
    "in vec3 posOut;\n" +                                    //
    "out vec4 color;\n" +                                    //
    "void main() {\n" +                                      //
    " vec3 norm = normalize(normal);\n" +                    //
    " vec3 lDir = normalize(-lightDir);\n" +                 //
    " vec3 vDir = normalize(camera - posOut);\n" +           //
    " vec3 rDir = reflect(-lDir, norm);\n" +                 //
    " float d = max(dot(norm, lDir), 0.0);\n" +              //
    " float s = pow(max(dot(vDir, rDir), 0.0), shine);\n" +  //
    " color = vec4(lightAmbient * ambient +\n" +             //
    "              d * lightColor * diffuse +\n" +           //
    "              s * lightColor * specular,\n" +           //
    "              alpha);\n" +                              //
    "}\n";

bool Data3DMaterialBase::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DMaterialBase::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("normal", m_normal.toQVector3D());
    _program->setUniformValue("ambient", m_material.ambient.toQVec3());
    _program->setUniformValue("diffuse", m_material.diffuse.toQVec3());
    _program->setUniformValue("specular", m_material.specular.toQVec3());
    _program->setUniformValue("shine", m_material.shine);
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DMaterialBase::createBuffersImpl()
{
    return true;
}

bool Data3DMaterialBase::destroyBuffersImpl()
{
    return true;
}

bool Data3DMaterialBase::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_program)
    return true;
}

bool Data3DMaterialBase::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_program)
    return true;
}

}  // namespace OpenGL
}  // namespace U1
