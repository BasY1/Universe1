/*!
 * \file qt/opengl/shaderprogram.h
 * \author Michal Steller
 * \brief The QT Open GL shader program class declarations
 */

#ifndef UNIVERSE1_OPENGL_SHADERPROGRAM_H
#define UNIVERSE1_OPENGL_SHADERPROGRAM_H

#include "camera.h"
#include "lights.h"
#include "material.h"

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
    static const int pointLightsCount{8};  //!< Maximum point light count
    static const int materialCount{8};     //!< Maximum material count

    ShaderProgram(QObject *_parent = nullptr);
    bool initGL();

    inline int attrVertex() const;
    inline int attrNormal() const;
    inline int attrMaterial() const;

    void setupCamera(const Camera *_camera);
    void setupMaterials(const std::vector<Material> &_materials);
    void setupMaterial(const int _materialIndex, const Material &_material);
    void setupDirectionLight(const DirectionLight &_light);
    void setupPointLights(const std::vector<PointLight> &_lights);
    void setupPointLight(const int _lightIndex, const PointLight &_light);
    void setupSceneAmbientFactor(const float _value);

 protected:
    int m_attrVertex;    //!< Vertex position attribute location
    int m_attrNormal;    //!< Vertex normal attribute location
    int m_attrMaterial;  //!< Vertex material index attribute location

    int m_attrModel;           //!< Camera projection x camera view matrix attribute location
    int m_attrProjXview;       //!< Camera projection x camera view matrix attribute location
    int m_attrCameraPosition;  //!< Camera position attribute location

    int m_attrMaterialAlpha[materialCount];      //!< Materials alpha attribute locations
    int m_attrMaterialShininess[materialCount];  //!< Materials shininess attribute locations
    int m_attrMaterialAmbient[materialCount];    //!< Materials ambient color attribute locations
    int m_attrMaterialDiffuse[materialCount];    //!< Materials diffuse color attribute locations
    int m_attrMaterialSpecular[materialCount];   //!< Materials specular color attribute locations

    int m_attrDirectionLightMode;       //!< Material mode attribute location
    int m_attrDirectionLightDirection;  //!< Direction light direction attribute location
    int m_attrDirectionLightAmbient;    //!< Direction light ambient color attribute location
    int m_attrDirectionLightDiffuse;    //!< Direction light diffuse color attribute location
    int m_attrDirectionLightSpecular;   //!< Direction light specular color attribute location

    int m_attrPointLightMode[pointLightsCount];       //!< Direction lights mode factor attribute locations
    int m_attrPointLightPosition[pointLightsCount];   //!< Direction lights position attribute locations
    int m_attrPointLightConstant[pointLightsCount];   //!< Direction lights constant factor attribute locations
    int m_attrPointLightLinear[pointLightsCount];     //!< Direction lights linear factor attribute locations
    int m_attrPointLightQuadratic[pointLightsCount];  //!< Direction lights quadratic factor attribute locations
    int m_attrPointLightAmbient[pointLightsCount];    //!< Direction lights ambient color attribute locations
    int m_attrPointLightDiffuse[pointLightsCount];    //!< Direction lights diffuse color attribute locations
    int m_attrPointLightSpecular[pointLightsCount];   //!< Direction lights specular color attribute locations

    int m_attrSceneAmbientFactor;  //!< Scene ambient factor attribute location
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

/*!
 * \brief Getter for vertex material location
 * \returns Vertex material attribute location
 */
inline int ShaderProgram::attrMaterial() const
{
    return m_attrMaterial;
}

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_SHADERPROGRAM_H
