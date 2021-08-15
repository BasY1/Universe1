/*!
 * \file qt/opengl/shaderprogram.cpp
 * \author Michal Steller
 * \brief The QT Open GL camera class implementation
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
    , m_attrDirectionLightDirection(-1)
    , m_attrDirectionLightAmbient(-1)
    , m_attrDirectionLightDiffuse(-1)
    , m_attrDirectionLightSpecular(-1)
    , m_attrPointLightCount(-1)
{
    for (int i = 0; i < pointLightsCount; ++i)
    {
        m_attrPointLightPosition[i] = -1;
        m_attrPointLightConstant[i] = -1;
        m_attrPointLightLinear[i] = -1;
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
                            ("#version 330 core                                                       \n"
                             "                                                                        \n"
                             "struct Material {                                                       \n"
                             "    float shininess;                                                    \n"
                             "                                                                        \n"
                             "    vec3 ambient;                                                       \n"
                             "    vec3 diffuse;                                                       \n"
                             "    vec3 specular;                                                      \n"
                             "};                                                                      \n"
                             "                                                                        \n"
                             "struct DirectionLight {                                                 \n"
                             "    vec3 direction;                                                     \n"
                             "                                                                        \n"
                             "    vec3 ambient;                                                       \n"
                             "    vec3 diffuse;                                                       \n"
                             "    vec3 specular;                                                      \n"
                             "};                                                                      \n"
                             "                                                                        \n"
                             "struct PointLight {                                                     \n"
                             "    vec3 position;                                                      \n"
                             "                                                                        \n"
                             "    float constant;                                                     \n"
                             "    float linear;                                                       \n"
                             "                                                                        \n"
                             "    vec3 ambient;                                                       \n"
                             "    vec3 diffuse;                                                       \n"
                             "    vec3 specular;                                                      \n"
                             "};                                                                      \n"
                             "                                                                        \n"
                             "#define NR_POINT_LIGHTS " +
                             QString::number(pointLightsCount) +
                             "                                               \n"
                             "                                                                        \n"
                             "uniform vec3 cameraPosition;                                            \n"
                             "uniform Material material;                                              \n"
                             "uniform DirectionLight dirLight;                                        \n"
                             "uniform PointLight pointLight[NR_POINT_LIGHTS];                         \n"
                             "uniform int pointLightCount;                                            \n"
                             "                                                                        \n"
                             "in vec3 vertOut;                                                        \n"
                             "in vec3 normOut;                                                        \n"
                             "                                                                        \n"
                             "void main(void)                                                         \n"
                             "{                                                                       \n"
                             "    vec3 norm = normalize(normOut);                                     \n"
                             "    vec3 viewDir = normalize(cameraPosition - vertOut);                 \n"
                             "    vec3 lightDir = normalize(-dirLight.direction);                     \n"
                             "    vec3 reflectDir = reflect(-lightDir, norm);                         \n"
                             "                                                                        \n"
                             "    float d = max(dot(norm, lightDir), 0.0);                            \n"
                             "    float s = pow(max(dot(viewDir, reflectDir), 0.0),                   \n"
                             "                  material.shininess);                                  \n"
                             "                                                                        \n"
                             "    vec3 out = dirLight.ambient * material.ambient;                     \n"
                             "    out += d * dirLight.diffuse * material.diffuse;                     \n"
                             "    out += s * dirLight.specular * material.specular;                   \n"
                             "                                                                        \n"
                             "    for (int i = 0 ; i < pointLightCount ; ++i)                         \n"
                             "    {                                                                   \n"
                             "        lightDir = normalize(pointLight[i].position - vertOut);         \n"
                             "        d = max(dot(norm, lightDir), 0.0);                              \n"
                             "        s = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
                             "        float dist = length(pointLight[i].position - vertOut);          \n"
                             "        float a = 1.0 / (light.constant + light.linear * dist);         \n"
                             "                                                                        \n"
                             "        out += a * pointLight[i].ambient * material.ambient;            \n"
                             "        out += a * d * pointLight[i].diffuse * material.diffuse;        \n"
                             "        out += a * s *  pointLight[i].specular * material.specular;     \n"
                             "    }                                                                   \n"
                             "                                                                        \n"
                             "    gl_FragColor = vec4(out, 1.0);                                      \n"
                             "}                                                                       \n"));

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

    m_attrProjXview = uniformLocation("projXview");
    m_attrCameraPosition = uniformLocation("cameraPosition");

    if (m_attrProjXview < 0)
        result = false;
    if (m_attrCameraPosition < 0)
        result = false;

    m_attrMaterialShininess = uniformLocation("material.shininess");
    m_attrMaterialAmbient = uniformLocation("material.ambient");
    m_attrMaterialDiffuse = uniformLocation("material.diffuse");
    m_attrMaterialSpecular = uniformLocation("material.specular");

    if (m_attrMaterialShininess < 0)
        result = false;
    if (m_attrMaterialAmbient < 0)
        result = false;
    if (m_attrMaterialDiffuse < 0)
        result = false;
    if (m_attrMaterialSpecular < 0)
        result = false;

    m_attrDirectionLightDirection = uniformLocation("dirLight.direction");
    m_attrDirectionLightAmbient = uniformLocation("dirLight.ambient");
    m_attrDirectionLightDiffuse = uniformLocation("dirLight.diffuse");
    m_attrDirectionLightSpecular = uniformLocation("dirLight.specular");

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
        m_attrPointLightPosition[i] = uniformLocation(key + "position");
        m_attrPointLightConstant[i] = uniformLocation(key + "constant");
        m_attrPointLightLinear[i] = uniformLocation(key + "linear");
        m_attrPointLightAmbient[i] = uniformLocation(key + "ambient");
        m_attrPointLightDiffuse[i] = uniformLocation(key + "diffuse");
        m_attrPointLightSpecular[i] = uniformLocation(key + "specular");

        if (m_attrPointLightPosition[i] < 0)
            result = false;
        if (m_attrPointLightConstant[i] < 0)
            result = false;
        if (m_attrPointLightLinear[i] < 0)
            result = false;
        if (m_attrPointLightAmbient[i] < 0)
            result = false;
        if (m_attrPointLightDiffuse[i] < 0)
            result = false;
        if (m_attrPointLightSpecular[i] < 0)
            result = false;
    }

    m_attrPointLightCount = uniformLocation("pointLightCount");

    if (m_attrPointLightCount < 0)
        result = false;

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
    setUniformValue(m_attrMaterialShininess, _material.shininess);
    setUniformValue(m_attrMaterialAmbient, _material.ambient);
    setUniformValue(m_attrMaterialDiffuse, _material.diffuse);
    setUniformValue(m_attrMaterialSpecular, _material.specular);
}

/*!
 * \brief Setup material uniform values
 * \param _light Material properties
 */
void Universe1::OpenGL::ShaderProgram::setupDirectionLight(const DirectionLight &_light)
{
    setUniformValue(m_attrDirectionLightDirection, _light.direction);
    setUniformValue(m_attrDirectionLightAmbient, _light.ambient);
    setUniformValue(m_attrDirectionLightDiffuse, _light.diffuse);
    setUniformValue(m_attrDirectionLightSpecular, _light.specular);
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
        setUniformValue(m_attrPointLightPosition[i], light.position);
        setUniformValue(m_attrPointLightConstant[i], light.constant);
        setUniformValue(m_attrPointLightLinear[i], light.linear);
        setUniformValue(m_attrPointLightAmbient[i], light.ambient);
        setUniformValue(m_attrPointLightDiffuse[i], light.diffuse);
        setUniformValue(m_attrPointLightSpecular[i], light.specular);
        ++i;
        if (i == pointLightsCount)
            break;
    }
    setUniformValue(m_attrPointLightCount, i);
}
