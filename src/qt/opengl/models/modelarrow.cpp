/*!
 * \file qt/opengl/models/modelarrow.cpp
 * \author Michal Steller
 * \brief Open GL 3D arrow model with material class implementation
 */

#include "modelarrow.h"

/*!
 * \brief Constructor
 * \param _materialLine Initial line material
 * \param _materialHeader Initial header material
 * \param _materialBottom Initial header bottom material
 * \param _fromPosition Initial from point position
 * \param _toPosition Initial to point position (Header peak)
 * \param _ratioRadiusLine Initial arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Initial arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Initial arrow header length as ratio to full arrow length
 * \param _circlePointCount Initial point count on circle
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelArrow::ModelArrow(const Material &_materialLine,
                                                  const Material &_materialHeader,
                                                  const Material &_materialBottom,
                                                  const QVector3D &_fromPosition,
                                                  const QVector3D &_toPosition,
                                                  float _ratioRadiusLine,
                                                  float _ratioRadiusHeader,
                                                  float _ratioLengthHeader,
                                                  int _circlePointCount,
                                                  QObject *_parent)
    : MeshModel(std::vector<Material>({_materialLine, _materialHeader, _materialBottom}), _parent)
    , m_fromPosition(_fromPosition)
    , m_toPosition(_toPosition)
    , m_ratioRadiusLine(_ratioRadiusLine)
    , m_ratioRadiusHeader(_ratioRadiusHeader)
    , m_ratioLengthHeader(_ratioLengthHeader)
    , m_circlePointCount(prepareCirclePointCount(_circlePointCount))
{
    prepareRatio(m_ratioRadiusLine, m_ratioRadiusHeader, m_ratioLengthHeader);
}

/*!
 * \brief Setter for arrow points
 * \param _fromPosition New arrow begin point position
 * \param _toPosition New arrow end point position
 */
void Universe1::OpenGL::Models::ModelArrow::setArrow(const QVector3D &_fromPosition, const QVector3D &_toPosition)
{
    // TODO make sure same ??
    m_fromPosition = _fromPosition;
    m_toPosition = _toPosition;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for arrow begin point position
 * \param _value New arrow begin point position
 */
void Universe1::OpenGL::Models::ModelArrow::setFromPosition(const QVector3D &_value)
{
    setArrow(_value, m_toPosition);
}

/*!
 * \brief Setter for arrow end point position
 * \param _value New arrow end point position
 */
void Universe1::OpenGL::Models::ModelArrow::setToPosition(const QVector3D &_value)
{
    setArrow(m_fromPosition, _value);
}

/*!
 * \brief Setter for line radius ratio
 * \param _value New line radius ratio
 */
void Universe1::OpenGL::Models::ModelArrow::setRatioRadiusLine(float _value)
{
    m_ratioRadiusLine = _value;
    prepareRatio(m_ratioRadiusLine, m_ratioRadiusHeader, m_ratioLengthHeader);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for header circle radius ratio
 * \param _value New header circle radius ratio
 */
void Universe1::OpenGL::Models::ModelArrow::setRatioRadiusHeader(float _value)
{
    m_ratioRadiusHeader = _value;
    prepareRatio(m_ratioRadiusLine, m_ratioRadiusHeader, m_ratioLengthHeader);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for header length ratio
 * \param _value New header length ratio
 */
void Universe1::OpenGL::Models::ModelArrow::setRatioLengthHeader(float _value)
{
    m_ratioLengthHeader = _value;
    prepareRatio(m_ratioRadiusLine, m_ratioRadiusHeader, m_ratioLengthHeader);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for header length ratio
 * \param _ratioRadiusLine New ratio for line radius
 * \param _ratioRadiusHeader New ratio for header radius
 * \param _ratioLengthHeader New ratio for header length
 */
void Universe1::OpenGL::Models::ModelArrow::setRatios(float _ratioRadiusLine,
                                                      float _ratioRadiusHeader,
                                                      float _ratioLengthHeader)
{
    m_ratioRadiusLine = _ratioRadiusLine;
    m_ratioRadiusHeader = _ratioRadiusHeader;
    m_ratioLengthHeader = _ratioLengthHeader;
    prepareRatio(m_ratioRadiusLine, m_ratioRadiusHeader, m_ratioLengthHeader);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for circle point count
 * \param _value New circle point count
 */
void Universe1::OpenGL::Models::ModelArrow::setCirclePointCount(int _value)
{
    m_circlePointCount = prepareCirclePointCount(_value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Tool function make sure all ratios are in valid range
 * \param _ratioRadiusLine Arrow line radius as ratio to full arrow length
 * \param _ratioRadiusHeader Arrow header circle radius as ratio to full arrow length
 * \param _ratioLengthHeader Arrow header length as ratio to full arrow length
 * \returns
 */
void Universe1::OpenGL::Models::ModelArrow::prepareRatio(float &_ratioRadiusLine,
                                                         float &_ratioRadiusHeader,
                                                         float &_ratioLengthHeader)
{
    _ratioRadiusLine = std::min(std::max(_ratioRadiusLine, 0.00001F), 0.2F);
    _ratioRadiusHeader = std::min(std::max(_ratioRadiusHeader, _ratioRadiusLine * 1.1F), 0.75F);
    _ratioLengthHeader = std::min(std::max(_ratioLengthHeader, 0.00001F), 0.9F);
}

/*!
 * \brief Rebuild arrow
 */
void Universe1::OpenGL::Models::ModelArrow::rebuild()
{
    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    std::vector<uint8_t> materialData;
    std::vector<uint> triangData;
    std::vector<uint> linesData;

    if (qFuzzyCompare(m_fromPosition, m_toPosition))
    {
        initBuffers(vertexData, normalData, materialData, triangData, linesData);
        return;
    }

    const float lFull = lengthFull();
    const float rLine = m_ratioRadiusLine * lFull;
    const float rHeader = m_ratioRadiusHeader * lFull;
    const float lHeader = m_ratioLengthHeader * lFull;
    const float lLine = lFull - lHeader;
    const float angle = 2.0 * M_PI / static_cast<float>(m_circlePointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);

    const size_t vCnt = 7U * m_circlePointCount + 1U;
    vertexData.reserve(vCnt);
    normalData.reserve(vCnt);
    materialData.reserve(vCnt);

    const QVector3D normalDir = (m_toPosition - m_fromPosition).normalized();
    const QVector3D normalBack = -normalDir;
    const QVector3D normalArm = perpendicularVector(normalDir);
    const QVector3D normalSide = QVector3D::crossProduct(normalArm, normalDir).normalized();

    const QVector3D headerAdd = normalDir * lLine;

    const float headAngle = std::atan(rHeader / lHeader);
    const float sinHeadAngle = std::sin(headAngle);
    const float cosHeadAngle = std::cos(headAngle);

    QVector3D arm1 = normalArm;
    QVector3D arm2 = rotate(normalArm, normalSide, sinHeadAngle, cosHeadAngle).normalized();
    QVector3D arm3 = rotate(arm2, normalDir, std::sin(angle * 0.5F), std::cos(angle * 0.5F));

    vertexData.push_back(m_fromPosition);
    normalData.push_back(normalBack);
    materialData.push_back(0U);

    for (int i = 0; i < m_circlePointCount; ++i)
    {
        const QVector3D posBack = m_fromPosition + arm1 * rLine;
        const QVector3D posH1 = m_fromPosition + headerAdd + arm1 * rLine;
        const QVector3D posH2 = m_fromPosition + headerAdd + arm1 * rHeader;

        vertexData.push_back(posBack);
        normalData.push_back(normalBack);
        materialData.push_back(0U);

        vertexData.push_back(posBack);
        normalData.push_back(arm1);
        materialData.push_back(0U);

        vertexData.push_back(posH1);
        normalData.push_back(arm1);
        materialData.push_back(0U);

        vertexData.push_back(posH1);
        normalData.push_back(normalBack);
        materialData.push_back(2U);

        vertexData.push_back(posH2);
        normalData.push_back(normalBack);
        materialData.push_back(2U);

        vertexData.push_back(posH2);
        normalData.push_back(arm2);
        materialData.push_back(1U);

        vertexData.push_back(m_toPosition);
        normalData.push_back(arm3);
        materialData.push_back(1U);

        arm1 = rotate(arm1, normalDir, sa, ca);
        arm2 = rotate(arm2, normalDir, sa, ca);
        arm3 = rotate(arm3, normalDir, sa, ca);
    }

    linesData.reserve(m_circlePointCount * 14U);

    uint j = 1U;
    for (int i = 0; i < m_circlePointCount; ++i)
    {
        linesData.push_back(0U);
        linesData.push_back(j);

        linesData.push_back(j + 1U);
        linesData.push_back(j + 2U);

        linesData.push_back(j + 3U);
        linesData.push_back(j + 4U);

        linesData.push_back(j + 5U);
        linesData.push_back(j + 6U);

        j += 7U;
    }

    triangData.reserve(m_circlePointCount * 18U);

    j = 1U;
    for (int i = 0; i < m_circlePointCount - 1; ++i)
    {
        triangData.push_back(0U);
        triangData.push_back(j + 7U);
        triangData.push_back(j);

        triangData.push_back(j + 1U);
        triangData.push_back(j + 9U);
        triangData.push_back(j + 2U);

        triangData.push_back(j + 1U);
        triangData.push_back(j + 8U);
        triangData.push_back(j + 9U);

        triangData.push_back(j + 3U);
        triangData.push_back(j + 11U);
        triangData.push_back(j + 4U);

        triangData.push_back(j + 3U);
        triangData.push_back(j + 10U);
        triangData.push_back(j + 11U);

        triangData.push_back(j + 5U);
        triangData.push_back(j + 12U);
        triangData.push_back(j + 6U);

        linesData.push_back(j);
        linesData.push_back(j + 7U);

        linesData.push_back(j + 2U);
        linesData.push_back(j + 9U);

        linesData.push_back(j + 4U);
        linesData.push_back(j + 11U);

        j += 7U;
    }

    triangData.push_back(0U);
    triangData.push_back(1U);
    triangData.push_back(m_circlePointCount * 7U - 6U);

    triangData.push_back(m_circlePointCount * 7U - 5U);
    triangData.push_back(3U);
    triangData.push_back(m_circlePointCount * 7U - 4U);

    triangData.push_back(m_circlePointCount * 7U - 5U);
    triangData.push_back(2U);
    triangData.push_back(3U);

    triangData.push_back(m_circlePointCount * 7U - 3U);
    triangData.push_back(5U);
    triangData.push_back(m_circlePointCount * 7U - 2U);

    triangData.push_back(m_circlePointCount * 7U - 3U);
    triangData.push_back(4U);
    triangData.push_back(5U);

    triangData.push_back(m_circlePointCount * 7U - 1U);
    triangData.push_back(6U);
    triangData.push_back(m_circlePointCount * 7U);

    linesData.push_back(m_circlePointCount * 7U - 6U);
    linesData.push_back(1U);

    linesData.push_back(m_circlePointCount * 7U - 4U);
    linesData.push_back(3U);

    linesData.push_back(m_circlePointCount * 7U - 2U);
    linesData.push_back(5U);

    initBuffers(vertexData, normalData, materialData, triangData, linesData);
}

/*!
 * \brief Setter for material for all three components
 * \param _value New material object with values
 */
void Universe1::OpenGL::Models::ModelArrow::setMaterial(const Material &_value)
{
    GLModel::setMaterial(0, _value);
    GLModel::setMaterial(1, _value.lighter());
    GLModel::setMaterial(2, _value.darker());
}

/*!
 * \brief Setter for line material
 * \param _value New material object with values
 */
void Universe1::OpenGL::Models::ModelArrow::setMaterialLine(const Material &_value)
{
    GLModel::setMaterial(0, _value);
}

/*!
 * \brief Setter for header material
 * \param _value New material object with values
 */
void Universe1::OpenGL::Models::ModelArrow::setMaterialHeader(const Material &_value)
{
    GLModel::setMaterial(1, _value);
}

/*!
 * \brief Setter for header bottom material
 * \param _value New material object with values
 */
void Universe1::OpenGL::Models::ModelArrow::setMaterialBottom(const Material &_value)
{
    GLModel::setMaterial(2, _value);
}
