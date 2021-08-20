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
    , m_attrProjXview(-1)
    , m_attrCameraPosition(-1)
    , m_attrMaterialShininess(-1)
    , m_attrMaterialAmbient(-1)
    , m_attrMaterialDiffuse(-1)
    , m_attrMaterialSpecular(-1)
    , m_attrDirectionLightMode(-1)
    , m_attrDirectionLightDirection(-1)
    , m_attrDirectionLightAmbient(-1)
    , m_attrDirectionLightDiffuse(-1)
    , m_attrDirectionLightSpecular(-1)
{
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
                            "                                                       \n"
                            "uniform mat4 model;                                    \n"
                            "uniform mat4 projXview;                                \n"
                            "                                                       \n"
                            "out vec3 vertOut;                                      \n"
                            "out vec3 normOut;                                      \n"
                            "                                                       \n"
                            "void main(void)                                        \n"
                            "{                                                      \n"
                            "    vertOut = vec3(model * vec4(vertex, 1.0));         \n"
                            "    normOut = mat3(transpose(inverse(model))) * normal;\n"
                            "                                                       \n"
                            "    gl_Position = projXview * vec4(vertOut, 1.0);      \n"
                            "}                                                      \n");

    addShaderFromSourceCode(QOpenGLShader::Fragment,
                            ("#version 330 core                                                          \n"
                             "                                                                           \n"
                             "out vec4 FragColor;                                                        \n"
                             "                                                                           \n"
                             "#define POINT_LIGHT_COUNT " +
                             QString::number(pointLightsCount) +
                             "\n"
                             "                                                                           \n"
                             "struct Material {                                                          \n"
                             "    float alpha;                                                           \n"
                             "    float shininess;                                                       \n"
                             "                                                                           \n"
                             "    vec3 ambient;                                                          \n"
                             "    vec3 diffuse;                                                          \n"
                             "    vec3 specular;                                                         \n"
                             "};                                                                         \n"
                             "                                                                           \n"
                             "struct DirectionLight {                                                    \n"
                             "    int mode;                                                              \n"
                             "    vec3 direction;                                                        \n"
                             "                                                                           \n"
                             "    vec3 ambient;                                                          \n"
                             "    vec3 diffuse;                                                          \n"
                             "    vec3 specular;                                                         \n"
                             "};                                                                         \n"
                             "                                                                           \n"
                             "struct PointLight {                                                        \n"
                             "    int mode;                                                              \n"
                             "    vec3 position;                                                         \n"
                             "                                                                           \n"
                             "    float constant;                                                        \n"
                             "    float linear;                                                          \n"
                             "    float quadratic;                                                       \n"
                             "                                                                           \n"
                             "    vec3 ambient;                                                          \n"
                             "    vec3 diffuse;                                                          \n"
                             "    vec3 specular;                                                         \n"
                             "};                                                                         \n"
                             "                                                                           \n"
                             "uniform vec3 cameraPosition;                                               \n"
                             "uniform Material material;                                                 \n"
                             "uniform DirectionLight directionLight;                                     \n"
                             "uniform PointLight pointLight[POINT_LIGHT_COUNT];                          \n"
                             "uniform float ambientFactor;                                               \n"
                             "                                                                           \n"
                             "in vec3 vertOut;                                                           \n"
                             "in vec3 normOut;                                                           \n"
                             "                                                                           \n"
                             "void main(void)                                                            \n"
                             "{                                                                          \n"
                             "    vec3 usedAmbient = ambientFactor * material.ambient;                   \n"
                             "    vec3 result = usedAmbient;                                             \n"
                             "    vec3 norm = normalize(normOut);                                        \n"
                             "    vec3 viewDir = normalize(cameraPosition - vertOut);                    \n"
                             "    if (directionLight.mode != 0)                                          \n"
                             "    {                                                                      \n"
                             "        vec3 lightDir = normalize(-directionLight.direction);              \n"
                             "        vec3 reflDir = reflect(-lightDir, norm);                           \n"
                             "                                                                           \n"
                             "        float d = max(dot(norm, lightDir), 0.0);                           \n"
                             "        float s = pow(max(dot(viewDir, reflDir), 0.0), material.shininess);\n"
                             "                                                                           \n"
                             "        result += directionLight.ambient * usedAmbient;                    \n"
                             "        result += d * directionLight.diffuse * material.diffuse;           \n"
                             "        result += s * directionLight.specular * material.specular;         \n"
                             "    }                                                                      \n"
                             "                                                                           \n"
                             "    for (int i = 0 ; i < POINT_LIGHT_COUNT ; ++i)                          \n"
                             "    {                                                                      \n"
                             "        if (pointLight[i].mode == 0)                                       \n"
                             "            continue;                                                      \n"
                             "                                                                           \n"
                             "        vec3 lightDir = normalize(pointLight[i].position - vertOut);       \n"
                             "        vec3 reflDir = reflect(-lightDir, norm);                           \n"
                             "                                                                           \n"
                             "        float d = max(dot(norm, lightDir), 0.0);                           \n"
                             "        float s = pow(max(dot(viewDir, reflDir), 0.0), material.shininess);\n"
                             "                                                                           \n"
                             "        float dist = length(pointLight[i].position - vertOut);             \n"
                             "        float a = 1.0;                                                     \n"
                             "        switch (pointLight[i].mode)                                        \n"
                             "        {                                                                  \n"
                             "        case 2: a = 1.0 / pointLight[i].constant;                          \n"
                             "                break;                                                     \n"
                             "                                                                           \n"
                             "        case 3: a = 1.0 / (pointLight[i].constant +                        \n"
                             "                           pointLight[i].linear * dist);                   \n"
                             "                break;                                                     \n"
                             "                                                                           \n"
                             "        case 4: a = 1.0 / (pointLight[i].constant +                        \n"
                             "                           pointLight[i].linear * dist +                   \n"
                             "                           pointLight[i].quadratic * dist * dist);         \n"
                             "                break;                                                     \n"
                             "                                                                           \n"
                             "        default: break;                                                    \n"
                             "        }                                                                  \n"
                             "                                                                           \n"
                             "        result += a * pointLight[i].ambient * usedAmbient;                 \n"
                             "        result += a * d * pointLight[i].diffuse * material.diffuse;        \n"
                             "        result += a * s *  pointLight[i].specular * material.specular;     \n"
                             "    }                                                                      \n"
                             "                                                                           \n"
                             "    FragColor = vec4(result, material.alpha);                              \n"
                             "}                                                                          \n"));

    if (!link())
    {
        qDebug() << "ERROR GLShaderProgram:" << log();
        return false;
    }

    bind();

    bool result = true;

    m_attrVertex = attributeLocation("vertex");
    m_attrNormal = attributeLocation("normal");

    if (m_attrVertex < 0)
        result = false;
    if (m_attrNormal < 0)
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

    m_attrMaterialAlpha = uniformLocation("material.alpha");
    m_attrMaterialShininess = uniformLocation("material.shininess");
    m_attrMaterialAmbient = uniformLocation("material.ambient");
    m_attrMaterialDiffuse = uniformLocation("material.diffuse");
    m_attrMaterialSpecular = uniformLocation("material.specular");

    if (m_attrMaterialAlpha < 0)
        result = false;
    if (m_attrMaterialShininess < 0)
        result = false;
    if (m_attrMaterialAmbient < 0)
        result = false;
    if (m_attrMaterialDiffuse < 0)
        result = false;
    if (m_attrMaterialSpecular < 0)
        result = false;

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
 * \brief Setup material uniform values
 * \param _material Material properties
 */
void Universe1::OpenGL::ShaderProgram::setupMaterial(const Material &_material)
{
    setUniformValue(m_attrMaterialAlpha, _material.alpha);
    setUniformValue(m_attrMaterialShininess, _material.shininess);
    setUniformValue(m_attrMaterialAmbient, _material.ambientVector());
    setUniformValue(m_attrMaterialDiffuse, _material.diffuseVector());
    setUniformValue(m_attrMaterialSpecular, _material.specularVector());
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
 * \brief Setup scene ambient factor
 * \param _value New scene ambient factor value
 */
void Universe1::OpenGL::ShaderProgram::setupSceneAmbientFactor(const float _value)
{
    setUniformValue(m_attrSceneAmbientFactor, _value);
}
