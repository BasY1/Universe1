/*!
 * \file qt/opengl/shaderprogram.h
 * \author Michal Steller
 * \brief The QT Open GL shader program class declarations
 */

#ifndef UNIVERSE1_OPENGL_SHADERPROGRAM_H
#define UNIVERSE1_OPENGL_SHADERPROGRAM_H

#include "camera.h"

#include <QColor>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief The Open GL shader program for Universe 1 purposes
 */
class ShaderProgram : public QOpenGLShaderProgram
{
    Q_OBJECT
 public:
    static const int pointLightsCount{6};  //!< Maximum point light count

    /*!
     * \brief Material properties
     */
    struct Material
    {
        float shininess;     //!< Material shininess
        QVector3D ambient;   //!< Material ambient color
        QVector3D diffuse;   //!< Material diffuse color
        QVector3D specular;  //!< Material specular color
    };

    /*!
     * \brief Directional light properties
     */
    struct DirectionLight
    {
        QVector3D direction;  //!< Light direction
        QVector3D ambient;    //!< Light ambient color
        QVector3D diffuse;    //!< Light diffuse color
        QVector3D specular;   //!< Light specular color
    };

    /*!
     * \brief Point light properties
     */
    struct PointLight
    {
        float constant;      //!< Constant attenuation factor
        float linear;        //!< Linear attenuation factor
        QVector3D position;  //!< Light position
        QVector3D ambient;   //!< Light ambient color
        QVector3D diffuse;   //!< Light diffuse color
        QVector3D specular;  //!< Light specular color
    };

    ShaderProgram(QObject *_parent = nullptr);
    bool initGL();

    inline int attrVertex() const;
    inline int attrNormal() const;

    void setupCamera(const Camera *camera);
    void setupMaterial(const Material &material);
    void setupDirectionLight(const DirectionLight &light);
    void setupPointLights(const std::vector<PointLight> &lights);

 protected:
    int m_attrVertex;  //!< Vertex attribute location
    int m_attrNormal;  //!< Color attribute location

    int m_attrProjXview;       //!< Camera projection x camera view matrix attribute location
    int m_attrCameraPosition;  //!< Camera position attribute location

    int m_attrMaterialShininess;  //!< Material shininess attribute location
    int m_attrMaterialAmbient;    //!< Material ambient color attribute location
    int m_attrMaterialDiffuse;    //!< Material diffuse color attribute location
    int m_attrMaterialSpecular;   //!< Material specular color attribute location

    int m_attrDirectionLightDirection;  //!< Direction light direction attribute location
    int m_attrDirectionLightAmbient;    //!< Direction light ambient color attribute location
    int m_attrDirectionLightDiffuse;    //!< Direction light diffuse color attribute location
    int m_attrDirectionLightSpecular;   //!< Direction light specular color attribute location

    int m_attrPointLightPosition[pointLightsCount];  //!< Direction light position attribute locations
    int m_attrPointLightConstant[pointLightsCount];  //!< Direction light constant factor attribute locations
    int m_attrPointLightLinear[pointLightsCount];    //!< Direction light linear factor attribute locations
    int m_attrPointLightAmbient[pointLightsCount];   //!< Direction light ambient color attribute locations
    int m_attrPointLightDiffuse[pointLightsCount];   //!< Direction light diffuse color attribute locations
    int m_attrPointLightSpecular[pointLightsCount];  //!< Direction light specular color attribute locations
    int m_attrPointLightCount;                       //!< Used direction light count attribute locations
};

/*!
 * \brief Getter for vertex attribute location
 * \returns Vertex attribute location
 */
inline int ShaderProgram::attrVertex() const
{
    return m_attrVertex;
}

/*!
 * \brief Getter for vertex normal location
 * \returns Vertex normal attribute location
 */
inline int ShaderProgram::attrNormal() const
{
    return m_attrNormal;
}

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_SHADERPROGRAM_H
