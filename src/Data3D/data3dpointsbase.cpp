/*!
 * \file src/Data3D/data3dpointsbase.h
 * \brief Base Open GL point-cloud object
 */

#include "data3dpointsbase.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsBase::vs =  //
    Data3D::VS_Header +                   //
    Data3D::VS_Uniforms +                 //
    "uniform float pointSize;\n" +        //
    "void main() {\n" +                   //
    " gl_PointSize = pointSize;\n" +      //
    Data3D::VS_InMain +                   //
    "}\n";

const std::string Data3DPointsBase::fs =     //
    Data3D::GLSL_Version +                   //
    "uniform vec3 pointColor;\n" +           //
    "uniform float alpha;\n" +               //
    "out vec4 color;\n" +                    //
    "void main() {\n" +                      //
    " color = vec4(pointColor, alpha);\n" +  //
    "}\n";

bool Data3DPointsBase::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DPointsBase::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("pointColor", m_color.toQVec3());
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    _program->setUniformValue("pointSize", m_pointSize);
    return true;
}

bool Data3DPointsBase::createBuffersImpl()
{
    return true;
}

bool Data3DPointsBase::destroyBuffersImpl()
{
    return true;
}

bool Data3DPointsBase::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_program)
    return true;
}

bool Data3DPointsBase::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_program)
    return true;
}

}  // namespace OpenGL
}  // namespace U1
