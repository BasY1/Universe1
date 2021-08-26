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
    ShaderProgram(const int _pointLightsCount,
                  const int _spotLightsCount,
                  const int _materialCount,
                  QObject *_parent = nullptr);
    bool initGL();

    inline int pointLightsCount() const;
    inline int spotLightsCount() const;
    inline int materialCount() const;

    inline int attrVertex() const;
    inline int attrNormal() const;
    inline int attrMaterial() const;

    void setupCamera(const Camera *_camera);
    void setupMaterials(const std::vector<Material> &_materials);
    void setupMaterial(const int _materialIndex, const Material &_material);
    void setupDirectionLight(const DirectionLight &_light);
    void setupPointLights(const std::vector<PointLight> &_lights);
    void setupPointLight(const int _lightIndex, const PointLight &_light);
    void setupSpotLights(const std::vector<SpotLight> &_lights);
    void setupSpotLight(const int _lightIndex, const SpotLight &_light);
    void setupSceneAmbientFactor(const float _value);

 protected:
    const int m_pointLightsCount;  //!< Maximum point light count
    const int m_spotLightsCount;   //!< Maximum spot light count
    const int m_materialCount;     //!< Maximum material count

    int m_attrVertex;    //!< Vertex position attribute location
    int m_attrNormal;    //!< Vertex normal attribute location
    int m_attrMaterial;  //!< Vertex material index attribute location

    int m_attrModel;           //!< Camera projection x camera view matrix attribute location
    int m_attrProjXview;       //!< Camera projection x camera view matrix attribute location
    int m_attrCameraPosition;  //!< Camera position attribute location

    std::vector<int> m_attrMaterialMode;       //!< Materials mode attribute locations
    std::vector<int> m_attrMaterialAlpha;      //!< Materials alpha attribute locations
    std::vector<int> m_attrMaterialShininess;  //!< Materials shininess attribute locations
    std::vector<int> m_attrMaterialAmbient;    //!< Materials ambient color attribute locations
    std::vector<int> m_attrMaterialDiffuse;    //!< Materials diffuse color attribute locations
    std::vector<int> m_attrMaterialSpecular;   //!< Materials specular color attribute locations

    int m_attrDirectionLightMode;       //!< Material mode attribute location
    int m_attrDirectionLightDirection;  //!< Direction light direction attribute location
    int m_attrDirectionLightAmbient;    //!< Direction light ambient color attribute location
    int m_attrDirectionLightDiffuse;    //!< Direction light diffuse color attribute location
    int m_attrDirectionLightSpecular;   //!< Direction light specular color attribute location

    std::vector<int> m_attrPointLightMode;       //!< Direction lights mode factor attribute locations
    std::vector<int> m_attrPointLightPosition;   //!< Direction lights position attribute locations
    std::vector<int> m_attrPointLightConstant;   //!< Direction lights constant factor attribute locations
    std::vector<int> m_attrPointLightLinear;     //!< Direction lights linear factor attribute locations
    std::vector<int> m_attrPointLightQuadratic;  //!< Direction lights quadratic factor attribute locations
    std::vector<int> m_attrPointLightAmbient;    //!< Direction lights ambient color attribute locations
    std::vector<int> m_attrPointLightDiffuse;    //!< Direction lights diffuse color attribute locations
    std::vector<int> m_attrPointLightSpecular;   //!< Direction lights specular color attribute locations

    std::vector<int> m_attrSpotLightMode;         //!< Spot lights mode factor attribute locations
    std::vector<int> m_attrSpotLightPosition;     //!< Spot lights position attribute locations
    std::vector<int> m_attrSpotLightDirection;    //!< Spot lights position direction locations
    std::vector<int> m_attrSpotLightCutOff;       //!< Spot lights position cut-off locations
    std::vector<int> m_attrSpotLightOuterCutOff;  //!< Spot lights position outer cut-off locations
    std::vector<int> m_attrSpotLightConstant;     //!< Spot lights constant factor attribute locations
    std::vector<int> m_attrSpotLightLinear;       //!< Spot lights linear factor attribute locations
    std::vector<int> m_attrSpotLightQuadratic;    //!< Spot lights quadratic factor attribute locations
    std::vector<int> m_attrSpotLightAmbient;      //!< Spot lights ambient color attribute locations
    std::vector<int> m_attrSpotLightDiffuse;      //!< Spot lights diffuse color attribute locations
    std::vector<int> m_attrSpotLightSpecular;     //!< Spot lights specular color attribute locations

    int m_attrSceneAmbientFactor;  //!< Scene ambient factor attribute location
};

/*!
 * \brief Getter for maximum point light count
 * \returns Maximum point light count
 */
inline int ShaderProgram::pointLightsCount() const
{
    return m_pointLightsCount;
}

/*!
 * \brief Getter for maximum spot light count
 * \returns Maximum spot light count
 */
inline int ShaderProgram::spotLightsCount() const
{
    return m_spotLightsCount;
}

/*!
 * \brief Getter for maximum material count
 * \returns Maximum material count
 */
inline int ShaderProgram::materialCount() const
{
    return m_materialCount;
}

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
