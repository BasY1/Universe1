#include "shader.h"

static const char *vs = "#version 430                         \n"
                        "layout (location = 0) in vec3 pos;   \n"
                        "layout (location = 1) in vec3 nor;   \n"
                        "uniform mat4 mvp;                    \n"
                        "out vec3 posOut;                     \n"
                        "out vec3 normOut;                    \n"
                        "void main() {                        \n"
                        " posOut = pos;                       \n"
                        " normOut = nor;                      \n"
                        " gl_Position = mvp * vec4(pos, 1.0); \n"
                        "}                                    \n";

static const char *fs = "#version 430                                      \n"
                        "in vec3 posOut;                                   \n"
                        "in vec3 normOut;                                  \n"
                        "uniform vec3 cam;                                 \n"
                        "uniform vec3  lightDir;                           \n"
                        "uniform vec3  lightColor;                         \n"
                        "uniform float lightAmbient;                       \n"
                        "uniform vec3  colorAmbient;                       \n"
                        "uniform vec3  colorDiffuse;                       \n"
                        "uniform vec3  colorSpecular;                      \n"
                        "uniform float shine;                              \n"
                        "uniform float alpha;                              \n"
                        "out vec4 color;                                   \n"
                        "void main() {                                     \n"
                        " vec3 norm = normalize(normOut);                  \n"
                        " vec3 lDir = normalize(-lightDir);                \n"
                        " vec3 vDir = normalize(cam - posOut);             \n"
                        " vec3 rDir = reflect(-lDir, norm);                \n"
                        " float d = max(dot(norm, lDir), 0.0);             \n"
                        " float s = pow(max(dot(vDir, rDir), 0.0), shine); \n"
                        " color = vec4(lightAmbient * colorAmbient +       \n"
                        "              d * lightColor * colorDiffuse +     \n"
                        "              s * lightColor * colorSpecular,     \n"
                        "              alpha);                             \n"
                        "}                                                 \n";

Universe1::Video::Shader::Shader(QOpenGLFunctions *_f,
                                 const std::pair<QVector3D, QMatrix4x4> &_cameraStats,
                                 const QMatrix4x4 &_perspectiveMatrix,
                                 QObject *_parent)
    : QOpenGLShaderProgram(_parent)
    , f(_f)
    , m_camPos(_cameraStats.first)
    , m_camMvp(_cameraStats.second)
    , m_perspectiveMatrix(_perspectiveMatrix)
{
}

bool Universe1::Video::Shader::initialize()
{
    addShaderFromSourceCode(QOpenGLShader::Vertex, vs);
    addShaderFromSourceCode(QOpenGLShader::Fragment, fs);
    if (!link())
    {
        std::cerr << log().toStdString() << std::endl;
        return false;
    }

    if (!bind())
    {
        std::cerr << "Error: Can't bind shader program" << std::endl;
        return false;
    }

    setUniformValue("mvp", m_perspectiveMatrix * m_camMvp);
    setUniformValue("cam", m_camPos);
    setUniformValue("lightDir", m_lightDir);
    setUniformValue("lightColor", m_lightColor);
    setUniformValue("lightAmbient", m_lightAmbient);
    return true;
}

void Universe1::Video::Shader::draw(std::list<Data3D> &_data)
{
    std::vector<const Data3D *> withAlpha;
    withAlpha.reserve(_data.size());

    for (const Data3D &d : _data)
    {
        if (d.indexes.empty())
            continue;

        if (qFuzzyCompare(d.material.alpha, 1.0f))
            drawData(&d);
        else
            withAlpha.push_back(&d);
    }

    for (const Data3D *d : withAlpha)
        drawData(d);
}

void Universe1::Video::Shader::drawData(const Data3D *_data)
{
    setUniformValue("colorAmbient", _data->material.ambientF());
    setUniformValue("colorDiffuse", _data->material.diffuseF());
    setUniformValue("colorSpecular", _data->material.specularF());
    setUniformValue("shine", _data->material.shine);
    setUniformValue("alpha", _data->material.alpha);

    QOpenGLBuffer vpb(QOpenGLBuffer::VertexBuffer);
    vpb.create();
    vpb.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vpb.bind();
    vpb.allocate(_data->points.data(), _data->points.size() * sizeof(QVector3D));
    vpb.release();

    QOpenGLBuffer vnb(QOpenGLBuffer::VertexBuffer);
    vnb.create();
    vnb.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vnb.bind();
    vnb.allocate(_data->normals.data(), _data->normals.size() * sizeof(QVector3D));
    vnb.release();

    QOpenGLBuffer ib(QOpenGLBuffer::IndexBuffer);
    ib.create();
    ib.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ib.bind();
    ib.allocate(_data->indexes.data(), _data->indexes.size() * sizeof(uint));
    ib.release();

    vpb.bind();
    enableAttributeArray(0);
    setAttributeBuffer(0, GL_FLOAT, 0, 3);

    vnb.bind();
    enableAttributeArray(1);
    setAttributeBuffer(1, GL_FLOAT, 0, 3);

    ib.bind();

    f->glDrawElements(GL_TRIANGLES, _data->indexes.size(), GL_UNSIGNED_INT, nullptr);

    disableAttributeArray(1);
    disableAttributeArray(0);

    ib.release();
    vnb.release();
    vpb.release();

    ib.destroy();
    vnb.destroy();
    vpb.destroy();
}
