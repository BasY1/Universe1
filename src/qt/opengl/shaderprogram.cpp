/*!
 * \file qt/opengl/shaderprogram.cpp
 * \author Michal Steller
 * \brief The QT Open GL shader program class implementation
 */

#include "shaderprogram.h"

/*!
 * \brief Constructor
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::ShaderProgram::ShaderProgram(QObject *_parent)
    : QOpenGLShaderProgram(_parent)
    , m_attrVertex(-1)
    , m_attrNormal(-1)
    , m_attrMaterial(-1)

    , m_attrModel(-1)
    , m_attrProjXview(-1)
    , m_attrCameraPosition(-1)

    , m_attrDirectionLightMode(-1)
    , m_attrDirectionLightDirection(-1)
    , m_attrDirectionLightAmbient(-1)
    , m_attrDirectionLightDiffuse(-1)
    , m_attrDirectionLightSpecular(-1)
{
    for (int i = 0; i < materialCount; ++i)
    {
        m_attrMaterialAlpha[i] = -1;
        m_attrMaterialShininess[i] = -1;
        m_attrMaterialAmbient[i] = -1;
        m_attrMaterialDiffuse[i] = -1;
        m_attrMaterialSpecular[i] = -1;
    }

    for (int i = 0; i < pointLightsCount; ++i)
    {
        m_attrPointLightMode[i] = -1;
        m_attrPointLightPosition[i] = -1;
        m_attrPointLightConstant[i] = -1;
        m_attrPointLightLinear[i] = -1;
        m_attrPointLightQuadratic[i] = -1;
        m_attrPointLightAmbient[i] = -1;
        m_attrPointLightDiffuse[i] = -1;
        m_attrPointLightSpecular[i] = -1;
    }
}

/*!
 * \brief Initialize shaders and location properties
 * \returns Success flag
 */
bool Universe1::OpenGL::ShaderProgram::initGL()
{
    addShaderFromSourceCode(QOpenGLShader::Vertex,
                            "#version 330 core                                      \n"
                            "layout (location = 0) in vec3 vertex;                  \n"
                            "layout (location = 1) in vec3 normal;                  \n"
                            "layout (location = 2) in float materialID;             \n"
                            "                                                       \n"
                            "uniform mat4 model;                                    \n"
                            "uniform mat4 projXview;                                \n"
                            "                                                       \n"
                            "out vec3 vertOut;                                      \n"
                            "out vec3 normOut;                                      \n"
                            "out float materialIndex;                               \n"
                            "                                                       \n"
                            "void main(void)                                        \n"
                            "{                                                      \n"
                            "    vertOut = vec3(model * vec4(vertex, 1.0));         \n"
                            "    normOut = mat3(transpose(inverse(model))) * normal;\n"
                            "    materialIndex = materialID;                        \n"
                            "                                                       \n"
                            "    gl_Position = projXview * vec4(vertOut, 1.0);      \n"
                            "}                                                      \n");

    addShaderFromSourceCode(QOpenGLShader::Fragment,
                            ("#version 330 core\n"
                             "#define POINT_LIGHT_COUNT " +
                             QString::number(pointLightsCount) +
                             "\n"
                             "#define SPOT_LIGHT_COUNT " +
                             QString::number(spotLightsCount) +
                             "\n"
                             "#define MATERIAL_COUNT " +
                             QString::number(materialCount) +
                             "\n"
                             "                                                                     \n"
                             "out vec4 FragColor;                                                  \n"
                             "                                                                     \n"
                             "struct Material {                                                    \n"
                             "    int mode;                                                        \n"
                             "    float alpha;                                                     \n"
                             "    float shininess;                                                 \n"
                             "                                                                     \n"
                             "    vec3 ambient;                                                    \n"
                             "    vec3 diffuse;                                                    \n"
                             "    vec3 specular;                                                   \n"
                             "};                                                                   \n"
                             "                                                                     \n"
                             "struct DirectionLight {                                              \n"
                             "    int mode;                                                        \n"
                             "    vec3 direction;                                                  \n"
                             "                                                                     \n"
                             "    vec3 ambient;                                                    \n"
                             "    vec3 diffuse;                                                    \n"
                             "    vec3 specular;                                                   \n"
                             "};                                                                   \n"
                             "                                                                     \n"
                             "struct PointLight {                                                  \n"
                             "    int mode;                                                        \n"
                             "    vec3 position;                                                   \n"
                             "                                                                     \n"
                             "    float constant;                                                  \n"
                             "    float linear;                                                    \n"
                             "    float quadratic;                                                 \n"
                             "                                                                     \n"
                             "    vec3 ambient;                                                    \n"
                             "    vec3 diffuse;                                                    \n"
                             "    vec3 specular;                                                   \n"
                             "};                                                                   \n"
                             "                                                                     \n"
                             "struct SpotLight {                                                   \n"
                             "    int mode;                                                        \n"
                             "    vec3 position;                                                   \n"
                             "    vec3 direction;                                                  \n"
                             "    float cutOff;                                                    \n"
                             "    float outerCutOff;                                               \n"
                             "                                                                     \n"
                             "    float constant;                                                  \n"
                             "    float linear;                                                    \n"
                             "    float quadratic;                                                 \n"
                             "                                                                     \n"
                             "    vec3 ambient;                                                    \n"
                             "    vec3 diffuse;                                                    \n"
                             "    vec3 specular;                                                   \n"
                             "};                                                                   \n"
                             "                                                                     \n"
                             "uniform vec3 cameraPosition;                                         \n"
                             "uniform Material material[MATERIAL_COUNT];                           \n"
                             "uniform DirectionLight directionLight;                               \n"
                             "uniform PointLight pointLight[POINT_LIGHT_COUNT];                    \n"
                             "uniform SpotLight spotLight[SPOT_LIGHT_COUNT];                       \n"
                             "uniform float ambientFactor;                                         \n"
                             "                                                                     \n"
                             "in vec3 vertOut;                                                     \n"
                             "in vec3 normOut;                                                     \n"
                             "in float materialIndex;                                              \n"
                             "                                                                     \n"
                             "void main(void)                                                      \n"
                             "{                                                                    \n"
                             "    int usedMaterialIndex = int(materialIndex);                      \n"
                             "    float matAlpha = material[usedMaterialIndex].alpha;              \n"
                             "    float matShininess = material[usedMaterialIndex].shininess;      \n"
                             "    vec3 matAmbient = material[usedMaterialIndex].ambient;           \n"
                             "    vec3 matDiffuse = material[usedMaterialIndex].diffuse;           \n"
                             "    vec3 matSpecular = material[usedMaterialIndex].specular;         \n"
                             "                                                                     \n"
                             "    if (material[usedMaterialIndex].mode == 1)                       \n"
                             "    {                                                                \n"
                             "        FragColor = vec4(matAmbient, matAlpha);                      \n"
                             "        return;                                                      \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    if (material[usedMaterialIndex].mode == 2)                       \n"
                             "    {                                                                \n"
                             "        FragColor = vec4(matDiffuse, matAlpha);                      \n"
                             "        return;                                                      \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    if (material[usedMaterialIndex].mode == 3)                       \n"
                             "    {                                                                \n"
                             "        FragColor = vec4(matSpecular, matAlpha);                     \n"
                             "        return;                                                      \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    vec3 usedAmbient = ambientFactor * matAmbient;                   \n"
                             "    vec3 result = usedAmbient;                                       \n"
                             "    vec3 norm = normalize(normOut);                                  \n"
                             "    vec3 viewDir = normalize(cameraPosition - vertOut);              \n"
                             "                                                                     \n"
                             "    if (directionLight.mode != 0)                                    \n"
                             "    {                                                                \n"
                             "        vec3 lightDir = normalize(-directionLight.direction);        \n"
                             "        vec3 reflDir = reflect(-lightDir, norm);                     \n"
                             "                                                                     \n"
                             "        float d = max(dot(norm, lightDir), 0.0);                     \n"
                             "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShininess);\n"
                             "                                                                     \n"
                             "        result += directionLight.ambient * usedAmbient;              \n"
                             "        result += d * directionLight.diffuse * matDiffuse;           \n"
                             "        result += s * directionLight.specular * matSpecular;         \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    for (int i = 0 ; i < POINT_LIGHT_COUNT ; ++i)                    \n"
                             "    {                                                                \n"
                             "        if (pointLight[i].mode == 0)                                 \n"
                             "            continue;                                                \n"
                             "                                                                     \n"
                             "        vec3 lightDir = normalize(pointLight[i].position - vertOut); \n"
                             "        vec3 reflDir = reflect(-lightDir, norm);                     \n"
                             "                                                                     \n"
                             "        float d = max(dot(norm, lightDir), 0.0);                     \n"
                             "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShininess);\n"
                             "                                                                     \n"
                             "        float dist = length(pointLight[i].position - vertOut);       \n"
                             "        float a = 1.0;                                               \n"
                             "        switch (pointLight[i].mode)                                  \n"
                             "        {                                                            \n"
                             "        case 2: a = 1.0 / pointLight[i].constant;                    \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        case 3: a = 1.0 / (pointLight[i].constant +                  \n"
                             "                           pointLight[i].linear * dist);             \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        case 4: a = 1.0 / (pointLight[i].constant +                  \n"
                             "                           pointLight[i].linear * dist +             \n"
                             "                           pointLight[i].quadratic * dist * dist);   \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        default: break;                                              \n"
                             "        }                                                            \n"
                             "                                                                     \n"
                             "        result += a * pointLight[i].ambient * usedAmbient;           \n"
                             "        result += a * d * pointLight[i].diffuse * matDiffuse;        \n"
                             "        result += a * s *  pointLight[i].specular * matSpecular;     \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    for (int i = 0 ; i < SPOT_LIGHT_COUNT ; ++i)                     \n"
                             "    {                                                                \n"
                             "        if (spotLight[i].mode == 0)                                  \n"
                             "            continue;                                                \n"
                             "                                                                     \n"
                             "        vec3 lightDir = normalize(spotLight[i].position - vertOut);  \n"
                             "        float d = dot(norm, lightDir);                               \n"
                             "        if (d < 0.0)                                                 \n"
                             "            continue;                                                \n"
                             "                                                                     \n"
                             "        vec3 reflDir = reflect(-lightDir, norm);                     \n"
                             "                                                                     \n"
                             "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShininess);\n"
                             "        float t = dot(lightDir, normalize(-spotLight[i].direction)); \n"
                             "        float e = spotLight[i].cutOff - spotLight[i].outerCutOff;    \n"
                             "        float n = clamp((t - spotLight[i].outerCutOff)/e, 0.0, 1.0); \n"
                             "                                                                     \n"
                             "        float dist = length(spotLight[i].position - vertOut);        \n"
                             "        float a = 1.0;                                               \n"
                             "        switch (spotLight[i].mode)                                   \n"
                             "        {                                                            \n"
                             "        case 2: a = 1.0 / spotLight[i].constant;                     \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        case 3: a = 1.0 / (spotLight[i].constant +                   \n"
                             "                           spotLight[i].linear * dist);              \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        case 4: a = 1.0 / (spotLight[i].constant +                   \n"
                             "                           spotLight[i].linear * dist +              \n"
                             "                           spotLight[i].quadratic * dist * dist);    \n"
                             "                break;                                               \n"
                             "                                                                     \n"
                             "        default: break;                                              \n"
                             "        }                                                            \n"
                             "                                                                     \n"
                             "        result += n * a * spotLight[i].ambient * usedAmbient;        \n"
                             "        result += n * a * d * spotLight[i].diffuse * matDiffuse;     \n"
                             "        result += n * a * s *  spotLight[i].specular * matSpecular;  \n"
                             "    }                                                                \n"
                             "                                                                     \n"
                             "    FragColor = vec4(result, matAlpha);                              \n"
                             "}                                                                    \n"));

    if (!link())
    {
        qDebug() << "ERROR GLShaderProgram:" << log();
        return false;
    }

    bind();

    bool result = true;

    m_attrVertex = attributeLocation("vertex");
    m_attrNormal = attributeLocation("normal");
    m_attrMaterial = attributeLocation("materialID");

    if (m_attrVertex < 0)
        result = false;
    if (m_attrNormal < 0)
        result = false;
    if (m_attrMaterial < 0)
        result = false;

    m_attrModel = uniformLocation("model");
    if (m_attrModel < 0)
    {
        result = false;
    }
    else
    {
        QMatrix4x4 identityMatrix;
        identityMatrix.setToIdentity();
        setUniformValue(m_attrModel, identityMatrix);
    }

    m_attrProjXview = uniformLocation("projXview");
    if (m_attrProjXview < 0)
        result = false;

    m_attrCameraPosition = uniformLocation("cameraPosition");
    if (m_attrCameraPosition < 0)
        result = false;

    for (int i = 0; i < materialCount; ++i)
    {
        const QString key = QString("material[%1].").arg(i);
        m_attrMaterialMode[i] = uniformLocation(key + "mode");
        m_attrMaterialAlpha[i] = uniformLocation(key + "alpha");
        m_attrMaterialShininess[i] = uniformLocation(key + "shininess");
        m_attrMaterialAmbient[i] = uniformLocation(key + "ambient");
        m_attrMaterialDiffuse[i] = uniformLocation(key + "diffuse");
        m_attrMaterialSpecular[i] = uniformLocation(key + "specular");

        if (m_attrMaterialMode[i] < 0)
            result = false;
        if (m_attrMaterialAlpha[i] < 0)
            result = false;
        if (m_attrMaterialShininess[i] < 0)
            result = false;
        if (m_attrMaterialAmbient[i] < 0)
            result = false;
        if (m_attrMaterialDiffuse[i] < 0)
            result = false;
        if (m_attrMaterialSpecular[i] < 0)
            result = false;
    }

    m_attrDirectionLightMode = uniformLocation("directionLight.mode");
    m_attrDirectionLightDirection = uniformLocation("directionLight.direction");
    m_attrDirectionLightAmbient = uniformLocation("directionLight.ambient");
    m_attrDirectionLightDiffuse = uniformLocation("directionLight.diffuse");
    m_attrDirectionLightSpecular = uniformLocation("directionLight.specular");

    if (m_attrDirectionLightDirection < 0)
        result = false;
    if (m_attrDirectionLightAmbient < 0)
        result = false;
    if (m_attrDirectionLightDiffuse < 0)
        result = false;
    if (m_attrDirectionLightSpecular < 0)
        result = false;

    for (int i = 0; i < pointLightsCount; ++i)
    {
        const QString key = QString("pointLight[%1].").arg(i);
        m_attrPointLightMode[i] = uniformLocation(key + "mode");
        m_attrPointLightPosition[i] = uniformLocation(key + "position");
        m_attrPointLightConstant[i] = uniformLocation(key + "constant");
        m_attrPointLightLinear[i] = uniformLocation(key + "linear");
        m_attrPointLightQuadratic[i] = uniformLocation(key + "quadratic");
        m_attrPointLightAmbient[i] = uniformLocation(key + "ambient");
        m_attrPointLightDiffuse[i] = uniformLocation(key + "diffuse");
        m_attrPointLightSpecular[i] = uniformLocation(key + "specular");

        if (m_attrPointLightMode[i] < 0)
            result = false;
        if (m_attrPointLightPosition[i] < 0)
            result = false;
        if (m_attrPointLightConstant[i] < 0)
            result = false;
        if (m_attrPointLightLinear[i] < 0)
            result = false;
        if (m_attrPointLightQuadratic[i] < 0)
            result = false;
        if (m_attrPointLightAmbient[i] < 0)
            result = false;
        if (m_attrPointLightDiffuse[i] < 0)
            result = false;
        if (m_attrPointLightSpecular[i] < 0)
            result = false;
    }

    for (int i = 0; i < spotLightsCount; ++i)
    {
        const QString key = QString("spotLight[%1].").arg(i);
        m_attrSpotLightMode[i] = uniformLocation(key + "mode");
        m_attrSpotLightPosition[i] = uniformLocation(key + "position");
        m_attrSpotLightDirection[i] = uniformLocation(key + "direction");
        m_attrSpotLightCutOff[i] = uniformLocation(key + "cutOff");
        m_attrSpotLightOuterCutOff[i] = uniformLocation(key + "outerCutOff");
        m_attrSpotLightConstant[i] = uniformLocation(key + "constant");
        m_attrSpotLightLinear[i] = uniformLocation(key + "linear");
        m_attrSpotLightQuadratic[i] = uniformLocation(key + "quadratic");
        m_attrSpotLightAmbient[i] = uniformLocation(key + "ambient");
        m_attrSpotLightDiffuse[i] = uniformLocation(key + "diffuse");
        m_attrSpotLightSpecular[i] = uniformLocation(key + "specular");

        if (m_attrSpotLightMode[i] < 0)
            result = false;
        if (m_attrSpotLightPosition[i] < 0)
            result = false;
        if (m_attrSpotLightDirection[i] < 0)
            result = false;
        if (m_attrSpotLightCutOff[i] < 0)
            result = false;
        if (m_attrSpotLightOuterCutOff[i] < 0)
            result = false;
        if (m_attrSpotLightConstant[i] < 0)
            result = false;
        if (m_attrSpotLightLinear[i] < 0)
            result = false;
        if (m_attrSpotLightQuadratic[i] < 0)
            result = false;
        if (m_attrSpotLightAmbient[i] < 0)
            result = false;
        if (m_attrSpotLightDiffuse[i] < 0)
            result = false;
        if (m_attrSpotLightSpecular[i] < 0)
            result = false;
    }

    m_attrSceneAmbientFactor = uniformLocation("ambientFactor");
    if (m_attrSceneAmbientFactor < 0)
        result = false;
    else
        setUniformValue(m_attrSceneAmbientFactor, 0.1F);
    release();

    return result;
}

/*!
 * \brief Setup camera matrix uniform value from camera object
 * \param _camera Camera
 */
void Universe1::OpenGL::ShaderProgram::setupCamera(const Camera *_camera)
{
    setUniformValue(m_attrProjXview, _camera->viewMatrix());
    setUniformValue(m_attrCameraPosition, _camera->position());
}

/*!
 * \brief Setup materials from given collection
 * \param _materials Collection of materials
 * \note Maximum material count is \a GLShaderProgram::materialCount
 */
void Universe1::OpenGL::ShaderProgram::setupMaterials(const std::vector<Material> &_materials)
{
    int i = 0;
    for (const Material &material : _materials)
    {
        setUniformValue(m_attrMaterialMode[i], static_cast<int>(material.mode));
        setUniformValue(m_attrMaterialAlpha[i], material.alpha);
        setUniformValue(m_attrMaterialShininess[i], material.shininess);
        setUniformValue(m_attrMaterialAmbient[i], material.ambientVector());
        setUniformValue(m_attrMaterialDiffuse[i], material.diffuseVector());
        setUniformValue(m_attrMaterialSpecular[i], material.specularVector());
        ++i;
        if (i == materialCount)
            break;
    }
}
/*!
 * \brief Setup material uniform values
 * \param _materialIndex Material index
 * \param _material Material properties
 */
void Universe1::OpenGL::ShaderProgram::setupMaterial(const int _materialIndex, const Material &_material)
{
    if (_materialIndex < 0 || _materialIndex >= materialCount)
        return;
    setUniformValue(m_attrMaterialMode[_materialIndex], static_cast<int>(_material.mode));
    setUniformValue(m_attrMaterialAlpha[_materialIndex], _material.alpha);
    setUniformValue(m_attrMaterialShininess[_materialIndex], _material.shininess);
    setUniformValue(m_attrMaterialAmbient[_materialIndex], _material.ambientVector());
    setUniformValue(m_attrMaterialDiffuse[_materialIndex], _material.diffuseVector());
    setUniformValue(m_attrMaterialSpecular[_materialIndex], _material.specularVector());
}

/*!
 * \brief Setup material uniform values
 * \param _light Material properties
 */
void Universe1::OpenGL::ShaderProgram::setupDirectionLight(const DirectionLight &_light)
{
    setUniformValue(m_attrDirectionLightMode, static_cast<int>(_light.mode));
    setUniformValue(m_attrDirectionLightDirection, _light.direction);
    setUniformValue(m_attrDirectionLightAmbient, _light.ambientVector());
    setUniformValue(m_attrDirectionLightDiffuse, _light.diffuseVector());
    setUniformValue(m_attrDirectionLightSpecular, _light.specularVector());
}

/*!
 * \brief Setup point lights from given collection
 * \param _lights Collection of point lights
 * \note Maximum light count is \a GLShaderProgram::pointLightsCount
 */
void Universe1::OpenGL::ShaderProgram::setupPointLights(const std::vector<PointLight> &_lights)
{
    int i = 0;
    for (const PointLight &light : _lights)
    {
        setUniformValue(m_attrPointLightMode[i], static_cast<int>(light.mode));
        setUniformValue(m_attrPointLightPosition[i], light.position);
        setUniformValue(m_attrPointLightConstant[i], light.constant);
        setUniformValue(m_attrPointLightLinear[i], light.linear);
        setUniformValue(m_attrPointLightQuadratic[i], light.quadratic);
        setUniformValue(m_attrPointLightAmbient[i], light.ambientVector());
        setUniformValue(m_attrPointLightDiffuse[i], light.diffuseVector());
        setUniformValue(m_attrPointLightSpecular[i], light.specularVector());
        ++i;
        if (i == pointLightsCount)
            break;
    }
}

/*!
 * \brief Setup point light at given index
 * \param _lightIndex Light index
 * \param _light Point lights
 * \note Also checks and updates active light count if is lower then given index
 */
void Universe1::OpenGL::ShaderProgram::setupPointLight(const int _lightIndex, const PointLight &_light)
{
    if (_lightIndex < 0 || _lightIndex >= pointLightsCount)
        return;
    setUniformValue(m_attrPointLightMode[_lightIndex], static_cast<int>(_light.mode));
    setUniformValue(m_attrPointLightPosition[_lightIndex], _light.position);
    setUniformValue(m_attrPointLightConstant[_lightIndex], _light.constant);
    setUniformValue(m_attrPointLightLinear[_lightIndex], _light.linear);
    setUniformValue(m_attrPointLightQuadratic[_lightIndex], _light.quadratic);
    setUniformValue(m_attrPointLightAmbient[_lightIndex], _light.ambientVector());
    setUniformValue(m_attrPointLightDiffuse[_lightIndex], _light.diffuseVector());
    setUniformValue(m_attrPointLightSpecular[_lightIndex], _light.specularVector());
}

/*!
 * \brief Setup spot lights from given collection
 * \param _lights Collection of spot lights
 * \note Maximum light count is \a GLShaderProgram::spotLightsCount
 */
void Universe1::OpenGL::ShaderProgram::setupSpotLights(const std::vector<SpotLight> &_lights)
{
    int i = 0;
    for (const SpotLight &light : _lights)
    {
        setUniformValue(m_attrSpotLightMode[i], static_cast<int>(light.mode));
        setUniformValue(m_attrSpotLightPosition[i], light.position);
        setUniformValue(m_attrSpotLightDirection[i], light.direction);
        setUniformValue(m_attrSpotLightCutOff[i], std::cos(light.cutOffRad));
        setUniformValue(m_attrSpotLightOuterCutOff[i], std::cos(light.outerCutOffRad));
        setUniformValue(m_attrSpotLightConstant[i], light.constant);
        setUniformValue(m_attrSpotLightLinear[i], light.linear);
        setUniformValue(m_attrSpotLightQuadratic[i], light.quadratic);
        setUniformValue(m_attrSpotLightAmbient[i], light.ambientVector());
        setUniformValue(m_attrSpotLightDiffuse[i], light.diffuseVector());
        setUniformValue(m_attrSpotLightSpecular[i], light.specularVector());
        ++i;
        if (i == pointLightsCount)
            break;
    }
}

/*!
 * \brief Setup spot light at given index
 * \param _lightIndex Light index
 * \param _light Spot lights
 * \note Also checks and updates active light count if is lower then given index
 */
void Universe1::OpenGL::ShaderProgram::setupSpotLight(const int _lightIndex, const SpotLight &_light)
{
    if (_lightIndex < 0 || _lightIndex >= pointLightsCount)
        return;
    setUniformValue(m_attrSpotLightMode[_lightIndex], static_cast<int>(_light.mode));
    setUniformValue(m_attrSpotLightPosition[_lightIndex], _light.position);
    setUniformValue(m_attrSpotLightDirection[_lightIndex], _light.direction);
    setUniformValue(m_attrSpotLightCutOff[_lightIndex], std::cos(_light.cutOffRad));
    setUniformValue(m_attrSpotLightOuterCutOff[_lightIndex], std::cos(_light.outerCutOffRad));
    setUniformValue(m_attrSpotLightConstant[_lightIndex], _light.constant);
    setUniformValue(m_attrSpotLightLinear[_lightIndex], _light.linear);
    setUniformValue(m_attrSpotLightQuadratic[_lightIndex], _light.quadratic);
    setUniformValue(m_attrSpotLightAmbient[_lightIndex], _light.ambientVector());
    setUniformValue(m_attrSpotLightDiffuse[_lightIndex], _light.diffuseVector());
    setUniformValue(m_attrSpotLightSpecular[_lightIndex], _light.specularVector());
}

/*!
 * \brief Setup scene ambient factor
 * \param _value New scene ambient factor value
 */
void Universe1::OpenGL::ShaderProgram::setupSceneAmbientFactor(const float _value)
{
    setUniformValue(m_attrSceneAmbientFactor, _value);
}
