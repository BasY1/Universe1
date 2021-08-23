/*!
 * \file qt/opengl/models/modelbox.cpp
 * \author Michal Steller
 * \brief Open GL 3D box model with material class implementation
 */

#include "modelbox.h"

/*!
 * \brief Constructor
 * \param _material Material
 * \param _center Box center position
 * \param _normal1 Main normal
 * \param _normal2 Second normal
 * \param _normalSetup Normal setup
 * \param _boxSize1 Box size 1
 * \param _boxSize2 Box size 2
 * \param _boxSize3 Box size 3
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelBox::ModelBox(const Material &_material,
                                              const QVector3D &_center,
                                              const QVector3D &_normal1,
                                              const QVector3D &_normal2,
                                              const NormalSetup _normalSetup,
                                              const float _boxSize1,
                                              const float _boxSize2,
                                              const float _boxSize3,
                                              QObject *_parent)
    : MeshModel(_material, _parent)
    , m_normalSetup(_normalSetup)
    , m_center(_center)
    , m_normal1(_normal1)
    , m_normal2(_normal2)
    , m_boxSize1(std::max(0.000001F, _boxSize1))
    , m_boxSize2(std::max(0.000001F, _boxSize2))
    , m_boxSize3(std::max(0.000001F, _boxSize3))
{
    prepareNormals(m_normal1, m_normal2);
}

static void addQuad(uint &_idx,
                    const uint _p1,
                    const uint _p2,
                    const uint _p3,
                    const uint _p4,
                    const QVector3D _normal,
                    const std::vector<QVector3D> &_pos,
                    std::vector<QVector3D> &_vertexData,
                    std::vector<QVector3D> &_normalData,
                    std::vector<uint> &_triangData,
                    std::vector<uint> &_linesData)
{
    _vertexData.push_back(_pos.at(_p1));
    _vertexData.push_back(_pos.at(_p2));
    _vertexData.push_back(_pos.at(_p3));
    _vertexData.push_back(_pos.at(_p4));

    _normalData.push_back(_normal);
    _normalData.push_back(_normal);
    _normalData.push_back(_normal);
    _normalData.push_back(_normal);

    _triangData.push_back(_idx);
    _triangData.push_back(_idx + 2U);
    _triangData.push_back(_idx + 1U);

    _triangData.push_back(_idx);
    _triangData.push_back(_idx + 3U);
    _triangData.push_back(_idx + 2U);

    _linesData.push_back(_idx);
    _linesData.push_back(_idx + 1U);

    _linesData.push_back(_idx + 1U);
    _linesData.push_back(_idx + 2U);

    _linesData.push_back(_idx + 2U);
    _linesData.push_back(_idx + 3U);

    _linesData.push_back(_idx + 3U);
    _linesData.push_back(_idx);

    _idx += 4U;
}

/*!
 * \brief Rebuild box
 */
void Universe1::OpenGL::Models::ModelBox::rebuild()
{
    static const std::vector<uint> triangDataUgly = {
        0U, 3U, 1U, 0U, 2U, 3U, 4U, 5U, 7U, 4U, 7U, 6U,  //
        0U, 1U, 5U, 0U, 5U, 4U, 2U, 6U, 7U, 2U, 7U, 3U,  //
        0U, 4U, 6U, 0U, 6U, 2U, 1U, 3U, 7U, 1U, 7U, 5U,  //
    };

    static const std::vector<uint> linesDataUgly = {
        0U, 1U, 0U, 2U, 1U, 3U, 3U, 2U,  //
        4U, 5U, 4U, 6U, 7U, 5U, 7U, 6U,  //
        0U, 4U, 1U, 5U, 2U, 6U, 3U, 7U,  //
    };

    const QVector3D n3 = normal3();
    const std::vector<QVector3D> pos = {
        m_center + 0.5F * (m_normal1 * m_boxSize1 + m_normal2 * m_boxSize2 + n3 * m_boxSize3),
        m_center + 0.5F * (m_normal1 * m_boxSize1 + m_normal2 * m_boxSize2 - n3 * m_boxSize3),
        m_center + 0.5F * (m_normal1 * m_boxSize1 - m_normal2 * m_boxSize2 + n3 * m_boxSize3),
        m_center + 0.5F * (m_normal1 * m_boxSize1 - m_normal2 * m_boxSize2 - n3 * m_boxSize3),
        m_center + 0.5F * (-m_normal1 * m_boxSize1 + m_normal2 * m_boxSize2 + n3 * m_boxSize3),
        m_center + 0.5F * (-m_normal1 * m_boxSize1 + m_normal2 * m_boxSize2 - n3 * m_boxSize3),
        m_center + 0.5F * (-m_normal1 * m_boxSize1 - m_normal2 * m_boxSize2 + n3 * m_boxSize3),
        m_center + 0.5F * (-m_normal1 * m_boxSize1 - m_normal2 * m_boxSize2 - n3 * m_boxSize3)};

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    std::vector<uint> triangData;
    std::vector<uint> linesData;
    uint idx = 0U;

    switch (m_normalSetup)
    {
    case NormalPrecise:
        vertexData.reserve(24U);
        normalData.reserve(24U);
        triangData.reserve(36U);
        linesData.reserve(48U);
        addQuad(idx, 0U, 1U, 3U, 2U, m_normal1, pos, vertexData, normalData, triangData, linesData);
        addQuad(idx, 4U, 6U, 7U, 5U, -m_normal1, pos, vertexData, normalData, triangData, linesData);
        addQuad(idx, 0U, 4U, 5U, 1U, m_normal2, pos, vertexData, normalData, triangData, linesData);
        addQuad(idx, 2U, 3U, 7U, 6U, -m_normal2, pos, vertexData, normalData, triangData, linesData);
        addQuad(idx, 0U, 2U, 6U, 4U, n3, pos, vertexData, normalData, triangData, linesData);
        addQuad(idx, 1U, 5U, 7U, 3U, -n3, pos, vertexData, normalData, triangData, linesData);
        break;

    case NormalFromCenter:
        vertexData = pos;
        normalData.reserve(8U);
        for (size_t i = 0; i < 8U; ++i)
            normalData.push_back((pos[i] - m_center).normalized());
        triangData = triangDataUgly;
        linesData = linesDataUgly;
        break;

    case Normal45deg:
        vertexData = pos;
        normalData = {(m_normal1 + m_normal2 + n3).normalized(),
                      (m_normal1 + m_normal2 - n3).normalized(),
                      (m_normal1 - m_normal2 + n3).normalized(),
                      (m_normal1 - m_normal2 - n3).normalized(),
                      (-m_normal1 + m_normal2 + n3).normalized(),
                      (-m_normal1 + m_normal2 - n3).normalized(),
                      (-m_normal1 - m_normal2 + n3).normalized(),
                      (-m_normal1 - m_normal2 - n3).normalized()};
        triangData = triangDataUgly;
        linesData = linesDataUgly;
        break;
    }

    initBuffers(vertexData, normalData, {}, triangData, linesData);
}

/*!
 * \brief Setter for box center position
 * \param _value New box center position
 */
void Universe1::OpenGL::Models::ModelBox::setCenter(const QVector3D &_value)
{
    m_center = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for normals
 * \param _normal1 New main normal
 * \param _normal2 New second normal
 */
void Universe1::OpenGL::Models::ModelBox::setNormals(const QVector3D &_normal1, const QVector3D &_normal2)
{
    m_normal1 = _normal1;
    m_normal2 = _normal2;
    prepareNormals(m_normal1, m_normal2);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for normal setup
 * \param _value New normal setup
 */
void Universe1::OpenGL::Models::ModelBox::setNormalSetup(NormalSetup _value)
{
    m_normalSetup = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for box size 1
 * \param _value New box size 1
 */
void Universe1::OpenGL::Models::ModelBox::setBoxSize1(float _value)
{
    m_boxSize1 = std::max(0.000001F, _value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for box size 2
 * \param _value New box size 2
 */
void Universe1::OpenGL::Models::ModelBox::setBoxSize2(float _value)
{
    m_boxSize2 = std::max(0.000001F, _value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for box size 3
 * \param _value New box size 3
 */
void Universe1::OpenGL::Models::ModelBox::setBoxSize3(float _value)
{
    m_boxSize3 = std::max(0.000001F, _value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for box sizes
 * \param _boxSizes New box sizes
 */
void Universe1::OpenGL::Models::ModelBox::setBoxSizes(const QVector3D &_boxSizes)
{
    m_boxSize1 = std::max(0.000001F, _boxSizes.x());
    m_boxSize2 = std::max(0.000001F, _boxSizes.y());
    m_boxSize3 = std::max(0.000001F, _boxSizes.z());
    if (isInit())
        rebuild();
    emit changed();
}
