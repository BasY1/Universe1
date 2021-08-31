/*!
 * \file qt/opengl/shaderprogram.cpp
 * \author Michal Steller
 * \brief The QT Open GL shader program class implementation
 */

#include "shaderprogram.h"

/*!
 * \brief Constructor
 * \param _pointLightsCount Maximum point light count
 * \param _spotLightsCount Maximum spot light count
 * \param _materialCount Maximum material count
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::ShaderProgram::ShaderProgram(const int _pointLightsCount,
                                                const int _spotLightsCount,
                                                const int _materialCount,
                                                QObject *_parent)
    : QOpenGLShaderProgram(_parent)
    , m_pointLightsCount(std::max(0, _pointLightsCount))
    , m_spotLightsCount(std::max(0, _spotLightsCount))
    , m_materialCount(std::max(1, _materialCount))

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
    m_attrMaterialMode.reserve(m_materialCount);
    m_attrMaterialAlpha.reserve(m_materialCount);
    m_attrMaterialShininess.reserve(m_materialCount);
    m_attrMaterialAmbient.reserve(m_materialCount);
    m_attrMaterialDiffuse.reserve(m_materialCount);
    m_attrMaterialSpecular.reserve(m_materialCount);

    for (int i = 0; i < m_materialCount; ++i)
    {
        m_attrMaterialMode[i] = -1;
        m_attrMaterialAlpha[i] = -1;
        m_attrMaterialShininess[i] = -1;
        m_attrMaterialAmbient[i] = -1;
        m_attrMaterialDiffuse[i] = -1;
        m_attrMaterialSpecular[i] = -1;
    }

    m_attrPointLightMode.reserve(m_pointLightsCount);
    m_attrPointLightPosition.reserve(m_pointLightsCount);
    m_attrPointLightConstant.reserve(m_pointLightsCount);
    m_attrPointLightLinear.reserve(m_pointLightsCount);
    m_attrPointLightQuadratic.reserve(m_pointLightsCount);
    m_attrPointLightAmbient.reserve(m_pointLightsCount);
    m_attrPointLightDiffuse.reserve(m_pointLightsCount);
    m_attrPointLightSpecular.reserve(m_pointLightsCount);
    for (int i = 0; i < m_pointLightsCount; ++i)
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

    m_attrSpotLightMode.reserve(m_spotLightsCount);
    m_attrSpotLightPosition.reserve(m_spotLightsCount);
    m_attrSpotLightDirection.reserve(m_spotLightsCount);
    m_attrSpotLightCutOff.reserve(m_spotLightsCount);
    m_attrSpotLightOuterCutOff.reserve(m_spotLightsCount);
    m_attrSpotLightConstant.reserve(m_spotLightsCount);
    m_attrSpotLightLinear.reserve(m_spotLightsCount);
    m_attrSpotLightQuadratic.reserve(m_spotLightsCount);
    m_attrSpotLightAmbient.reserve(m_spotLightsCount);
    m_attrSpotLightDiffuse.reserve(m_spotLightsCount);
    m_attrSpotLightSpecular.reserve(m_spotLightsCount);
    for (int i = 0; i < m_spotLightsCount; ++i)
    {
        m_attrSpotLightMode[i] = -1;
        m_attrSpotLightPosition[i] = -1;
        m_attrSpotLightDirection[i] = -1;
        m_attrSpotLightCutOff[i] = -1;
        m_attrSpotLightOuterCutOff[i] = -1;
        m_attrSpotLightConstant[i] = -1;
        m_attrSpotLightLinear[i] = -1;
        m_attrSpotLightQuadratic[i] = -1;
        m_attrSpotLightAmbient[i] = -1;
        m_attrSpotLightDiffuse[i] = -1;
        m_attrSpotLightSpecular[i] = -1;
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

    QString fs;

    fs += "#version 330 core\n";

    if (m_pointLightsCount > 0)
        fs += "#define POINT_LIGHT_COUNT " + QString::number(m_pointLightsCount) + "\n";

    if (m_spotLightsCount > 0)
        fs += "#define SPOT_LIGHT_COUNT " + QString::number(m_spotLightsCount) + "\n";

    fs += "#define MATERIAL_COUNT " + QString::number(m_materialCount) + "\n\n";

    fs += "struct Material {    \n";
    fs += "    int mode;        \n";
    fs += "    float alpha;     \n";
    fs += "    float shininess; \n";
    fs += "                     \n";
    fs += "    vec3 ambient;    \n";
    fs += "    vec3 diffuse;    \n";
    fs += "    vec3 specular;   \n";
    fs += "};\n\n";

    fs += "struct DirectionLight { \n";
    fs += "    int mode;           \n";
    fs += "    vec3 direction;     \n";
    fs += "                        \n";
    fs += "    vec3 ambient;       \n";
    fs += "    vec3 diffuse;       \n";
    fs += "    vec3 specular;      \n";
    fs += "};\n\n";

    if (m_pointLightsCount > 0)
    {
        fs += "struct PointLight {  \n";
        fs += "    int mode;        \n";
        fs += "    vec3 position;   \n";
        fs += "                     \n";
        fs += "    float constant;  \n";
        fs += "    float linear;    \n";
        fs += "    float quadratic; \n";
        fs += "                     \n";
        fs += "    vec3 ambient;    \n";
        fs += "    vec3 diffuse;    \n";
        fs += "    vec3 specular;   \n";
        fs += "};\n\n";
    }

    if (m_spotLightsCount > 0)
    {
        fs += "struct SpotLight {     \n";
        fs += "    int mode;          \n";
        fs += "    vec3 position;     \n";
        fs += "    vec3 direction;    \n";
        fs += "    float cutOff;      \n";
        fs += "    float outerCutOff; \n";
        fs += "                       \n";
        fs += "    float constant;    \n";
        fs += "    float linear;      \n";
        fs += "    float quadratic;   \n";
        fs += "                       \n";
        fs += "    vec3 ambient;      \n";
        fs += "    vec3 diffuse;      \n";
        fs += "    vec3 specular;     \n";
        fs += "};\n\n";
    }

    fs += "uniform vec3 cameraPosition;\n\n";

    fs += "uniform float ambientFactor;\n";
    fs += "uniform Material material[MATERIAL_COUNT];\n\n";

    fs += "uniform DirectionLight directionLight;\n";
    if (m_pointLightsCount > 0)
        fs += "uniform PointLight pointLight[POINT_LIGHT_COUNT];\n";
    if (m_spotLightsCount > 0)
        fs += "uniform SpotLight spotLight[SPOT_LIGHT_COUNT];\n";

    fs += "\n";
    fs += "in vec3 vertOut;\n";
    fs += "in vec3 normOut;\n";
    fs += "in float materialIndex;\n\n";
    fs += "out vec4 FragColor;\n\n";

    fs += "void main(void)                                                      \n";
    fs += "{                                                                    \n";
    fs += "    int usedMaterialIndex = int(materialIndex);                      \n";
    fs += "    int usedMode = material[usedMaterialIndex].mode;                 \n";
    fs += "    float matAlpha = material[usedMaterialIndex].alpha;              \n";
    fs += "    float matShin = material[usedMaterialIndex].shininess;           \n";
    fs += "    vec3 matAmbient = material[usedMaterialIndex].ambient;           \n";
    fs += "    vec3 matDiffuse = material[usedMaterialIndex].diffuse;           \n";
    fs += "    vec3 matSpecular = material[usedMaterialIndex].specular;         \n";
    fs += "    vec3 result = matAmbient;                                        \n";
    fs += "                                                                     \n";
    fs += "    if (usedMode == 1)                                               \n";
    fs += "    {                                                                \n";
    fs += "        result = matAmbient;                                         \n";
    fs += "    }                                                                \n";
    fs += "    else if (usedMode == 2)                                          \n";
    fs += "    {                                                                \n";
    fs += "        result = matDiffuse;                                         \n";
    fs += "    }                                                                \n";
    fs += "    else if (usedMode == 3)                                          \n";
    fs += "    {                                                                \n";
    fs += "        result = matSpecular;                                        \n";
    fs += "    }                                                                \n";
    fs += "    else                                                             \n";
    fs += "    {                                                                \n";
    fs += "    vec3 usedAmbient = ambientFactor * matAmbient;                   \n";
    fs += "    vec3 norm = normalize(normOut);                                  \n";
    fs += "    vec3 viewDir = normalize(cameraPosition - vertOut);              \n";
    fs += "                                                                     \n";
    fs += "    result = usedAmbient;                                            \n";
    fs += "                                                                     \n";
    fs += "    if (directionLight.mode == 1)                                    \n";
    fs += "    {                                                                \n";
    fs += "        vec3 lightDir = normalize(-directionLight.direction);        \n";
    fs += "        float d = dot(norm, lightDir);                               \n";
    fs += "        if (d >= 0.0)                                                \n";
    fs += "        {                                                            \n";
    fs += "            vec3 reflDir = reflect(-lightDir, norm);                 \n";
    fs += "                                                                     \n";
    fs += "            float s = pow(max(dot(viewDir, reflDir), 0.0), matShin); \n";
    fs += "                                                                     \n";
    fs += "            result += directionLight.ambient * usedAmbient;          \n";
    fs += "            result += d * directionLight.diffuse * matDiffuse;       \n";
    fs += "            result += s * directionLight.specular * matSpecular;     \n";
    fs += "        }                                                            \n";
    fs += "    }                                                                \n";
    fs += "    else if (directionLight.mode == 2)                               \n";
    fs += "    {                                                                \n";
    fs += "        vec3 lightDir = normalize(-directionLight.direction);        \n";
    fs += "        vec3 reflDir = reflect(-lightDir, norm);                     \n";
    fs += "                                                                     \n";
    fs += "        float d = max(dot(norm, lightDir), 0.0);                     \n";
    fs += "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShin);     \n";
    fs += "                                                                     \n";
    fs += "        result += directionLight.ambient * usedAmbient;              \n";
    fs += "        result += d * directionLight.diffuse * matDiffuse;           \n";
    fs += "        result += s * directionLight.specular * matSpecular;         \n";
    fs += "    }                                                                \n";
    fs += "                                                                     \n";

    if (m_pointLightsCount > 0)
    {
        fs += "    for (int i = 0 ; i < POINT_LIGHT_COUNT ; ++i)                    \n";
        fs += "    {                                                                \n";
        fs += "        if (pointLight[i].mode == 0)                                 \n";
        fs += "            continue;                                                \n";
        fs += "                                                                     \n";
        fs += "        vec3 lightDir = normalize(pointLight[i].position - vertOut); \n";
        fs += "        float d = dot(norm, lightDir);                               \n";
        fs += "        if (d < 0.0)                                                 \n";
        fs += "            continue;                                                \n";
        fs += "                                                                     \n";
        fs += "        vec3 reflDir = reflect(-lightDir, norm);                     \n";
        fs += "                                                                     \n";
        fs += "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShin);     \n";
        fs += "                                                                     \n";
        fs += "        float dist = length(pointLight[i].position - vertOut);       \n";
        fs += "        float a = 1.0;                                               \n";
        fs += "        switch (pointLight[i].mode)                                  \n";
        fs += "        {                                                            \n";
        fs += "        case 2: a = 1.0 / pointLight[i].constant;                    \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        case 3: a = 1.0 / (pointLight[i].constant +                  \n";
        fs += "                           pointLight[i].linear * dist);             \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        case 4: a = 1.0 / (pointLight[i].constant +                  \n";
        fs += "                           pointLight[i].linear * dist +             \n";
        fs += "                           pointLight[i].quadratic * dist * dist);   \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        default: break;                                              \n";
        fs += "        }                                                            \n";
        fs += "                                                                     \n";
        fs += "        result += a * pointLight[i].ambient * usedAmbient;           \n";
        fs += "        result += a * d * pointLight[i].diffuse * matDiffuse;        \n";
        fs += "        result += a * s *  pointLight[i].specular * matSpecular;     \n";
        fs += "    }                                                                \n";
        fs += "                                                                     \n";
    }

    if (m_spotLightsCount > 0)
    {
        fs += "    for (int i = 0 ; i < SPOT_LIGHT_COUNT ; ++i)                     \n";
        fs += "    {                                                                \n";
        fs += "        if (spotLight[i].mode == 0)                                  \n";
        fs += "            continue;                                                \n";
        fs += "                                                                     \n";
        fs += "        vec3 lightDir = normalize(spotLight[i].position - vertOut);  \n";
        fs += "        float d = dot(norm, lightDir);                               \n";
        fs += "        if (d < 0.0)                                                 \n";
        fs += "            continue;                                                \n";
        fs += "                                                                     \n";
        fs += "        vec3 reflDir = reflect(-lightDir, norm);                     \n";
        fs += "                                                                     \n";
        fs += "        float s = pow(max(dot(viewDir, reflDir), 0.0), matShin);     \n";
        fs += "        float t = dot(lightDir, normalize(-spotLight[i].direction)); \n";
        fs += "        float e = spotLight[i].cutOff - spotLight[i].outerCutOff;    \n";
        fs += "        float n = clamp((t - spotLight[i].outerCutOff)/e, 0.0, 1.0); \n";
        fs += "                                                                     \n";
        fs += "        float dist = length(spotLight[i].position - vertOut);        \n";
        fs += "        float a = 1.0;                                               \n";
        fs += "        switch (spotLight[i].mode)                                   \n";
        fs += "        {                                                            \n";
        fs += "        case 2: a = 1.0 / spotLight[i].constant;                     \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        case 3: a = 1.0 / (spotLight[i].constant +                   \n";
        fs += "                           spotLight[i].linear * dist);              \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        case 4: a = 1.0 / (spotLight[i].constant +                   \n";
        fs += "                           spotLight[i].linear * dist +              \n";
        fs += "                           spotLight[i].quadratic * dist * dist);    \n";
        fs += "                break;                                               \n";
        fs += "                                                                     \n";
        fs += "        default: break;                                              \n";
        fs += "        }                                                            \n";
        fs += "                                                                     \n";
        fs += "        result += n * a * spotLight[i].ambient * usedAmbient;        \n";
        fs += "        result += n * a * d * spotLight[i].diffuse * matDiffuse;     \n";
        fs += "        result += n * a * s *  spotLight[i].specular * matSpecular;  \n";
        fs += "    }                                                                \n";
        fs += "                                                                     \n";
    }

    fs += "    }\n";
    fs += "    FragColor = vec4(result, matAlpha);                              \n";
    fs += "}\n";

    addShaderFromSourceCode(QOpenGLShader::Fragment, fs);

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

    for (int i = 0; i < m_materialCount; ++i)
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

    for (int i = 0; i < m_pointLightsCount; ++i)
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

    for (int i = 0; i < m_spotLightsCount; ++i)
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
 */
void Universe1::OpenGL::ShaderProgram::setupMaterials(const std::vector<Material> &_materials)
{
    int i = 0;
    if (i < m_materialCount)
    {
        for (const Material &material : _materials)
        {
            setUniformValue(m_attrMaterialMode[i], static_cast<int>(material.mode));
            setUniformValue(m_attrMaterialAlpha[i], material.alpha);
            setUniformValue(m_attrMaterialShininess[i], material.shininess);
            setUniformValue(m_attrMaterialAmbient[i], material.ambientVector());
            setUniformValue(m_attrMaterialDiffuse[i], material.diffuseVector());
            setUniformValue(m_attrMaterialSpecular[i], material.specularVector());
            ++i;
            if (i >= m_materialCount)
                break;
        }
    }
}
/*!
 * \brief Setup material uniform values
 * \param _materialIndex Material index
 * \param _material Material properties
 */
void Universe1::OpenGL::ShaderProgram::setupMaterial(const int _materialIndex, const Material &_material)
{
    if (_materialIndex < 0 || _materialIndex >= m_materialCount)
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
 */
void Universe1::OpenGL::ShaderProgram::setupPointLights(const std::vector<PointLight> &_lights)
{
    int i = 0;
    if (i < m_pointLightsCount)
    {
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
            if (i >= m_pointLightsCount)
                break;
        }
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
    if (_lightIndex < 0 || _lightIndex >= m_pointLightsCount)
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
 */
void Universe1::OpenGL::ShaderProgram::setupSpotLights(const std::vector<SpotLight> &_lights)
{
    int i = 0;
    if (i < m_spotLightsCount)
    {
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
            if (i >= m_spotLightsCount)
                break;
        }
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
    if (_lightIndex < 0 || _lightIndex >= m_spotLightsCount)
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
