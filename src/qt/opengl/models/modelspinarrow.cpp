/*!
 * \file qt/opengl/models/modelspinarrow.cpp
 * \author Michal Steller
 * \brief Open GL 3D spin arrow model with material class implementation
 */

#include "modelspinarrow.h"

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
Universe1::OpenGL::Models::ModelSpinArrow::ModelSpinArrow(const Material &_materialLine,
                                                          const Material &_materialHeader,
                                                          const Material &_materialBottom,
                                                          const QVector3D &_fromPosition,
                                                          const QVector3D &_toPosition,
                                                          float _ratioRadiusLine,
                                                          float _ratioRadiusHeader,
                                                          float _ratioLengthHeader,
                                                          int _circlePointCount,
                                                          QObject *_parent)
    : ModelArrow(_materialLine,
                 _materialHeader,
                 _materialBottom,
                 _fromPosition,
                 _toPosition,
                 _ratioRadiusLine,
                 _ratioRadiusHeader,
                 _ratioLengthHeader,
                 _circlePointCount,
                 _parent)
{
}

/*!
 * \brief Rebuild spin arrow
 */
void Universe1::OpenGL::Models::ModelSpinArrow::rebuild()
{
    if (qFuzzyCompare(m_fromPosition, m_toPosition))
    {
        initBuffers({}, {}, {}, {}, {});
        return;
    }

    const float angle = 2.0 * M_PI / static_cast<float>(m_circlePointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);

    const uint loopCnt = m_circlePointCount;
    const uint pointCountLine = 2U + 4U * loopCnt;
    const uint triangCountLine = 12U * loopCnt;
    const uint linesCountLine = 10U * loopCnt;

    const uint pointCountTorus = loopCnt * loopCnt;
    const uint triangCountTorus = 4U * pointCountTorus;
    const uint linesCountTorus = 6U * pointCountTorus;

    const float lLine = lengthFull();
    const float rLine = m_ratioRadiusLine * lLine;
    const float rHeader = m_ratioRadiusHeader * lLine;
    const float lHeader = m_ratioLengthHeader * lLine;
    const float rRing = rLine + rHeader + lHeader;

    const QVector3D toPole = (m_toPosition - m_fromPosition).normalized();
    const QVector3D toEquator = perpendicularVector(toPole);

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    std::vector<uint8_t> materialData;
    std::vector<uint> triangData;
    std::vector<uint> linesData;

    vertexData.reserve(pointCountLine + pointCountTorus);
    normalData.reserve(pointCountLine + pointCountTorus);
    materialData.reserve(pointCountLine + pointCountTorus);
    triangData.reserve(triangCountLine + triangCountTorus);
    linesData.reserve(linesCountLine + linesCountTorus);

#ifndef DOXYGEN_SKIP
#define ADD_VERTEX(MAT, NOR, POS)                                                                                      \
    vertexData.push_back(POS);                                                                                         \
    normalData.push_back(NOR);                                                                                         \
    materialData.push_back(MAT)
#endif  // DOXYGEN_SKIP

    ADD_VERTEX(2U, -toPole, m_fromPosition);
    ADD_VERTEX(2U, toPole, m_toPosition);

    QVector3D normal1 = toEquator;
    for (uint i = 0; i < loopCnt; ++i)
    {
        const QVector3D arm = normal1 * rLine;
        ADD_VERTEX(2U, -toPole, m_fromPosition + arm);
        ADD_VERTEX(0U, normal1, m_fromPosition + arm);
        ADD_VERTEX(0U, normal1, m_toPosition + arm);
        ADD_VERTEX(2U, toPole, m_toPosition + arm);
        normal1 = rotate(normal1, toPole, sa, ca).normalized();
    }

    normal1 = toEquator;
    for (uint i = 0U; i < loopCnt; ++i)
    {
        const QVector3D rotNormal = QVector3D::crossProduct(toPole, normal1).normalized();
        const QVector3D bodyCenter = m_toPosition + normal1 * rRing;
        QVector3D normal2 = normal1;
        for (uint j = 0U; j < loopCnt; ++j)
        {
            ADD_VERTEX(1U, normal2, bodyCenter + normal2 * rHeader);
            normal2 = rotate(normal2, rotNormal, sa, ca).normalized();
        }
        normal1 = rotate(normal1, toPole, sa, ca).normalized();
    }
#undef ADD_VERTEX

    for (uint i = 0U; i < loopCnt - 1U; ++i)
    {
        triangData.push_back(0U);
        triangData.push_back(2U + (i + 1U) * 4U);
        triangData.push_back(2U + i * 4U);

        triangData.push_back(1U);
        triangData.push_back(2U + i * 4U + 3U);
        triangData.push_back(2U + (i + 1U) * 4U + 3U);

        triangData.push_back(2U + i * 4U + 1U);
        triangData.push_back(2U + (i + 1U) * 4U + 1U);
        triangData.push_back(2U + (i + 1U) * 4U + 2U);

        triangData.push_back(2U + i * 4U + 1U);
        triangData.push_back(2U + (i + 1U) * 4U + 2U);
        triangData.push_back(2U + i * 4U + 2U);

        linesData.push_back(0U);
        linesData.push_back(2U + i * 4U);

        linesData.push_back(2U + i * 4U + 1U);
        linesData.push_back(2U + i * 4U + 2U);

        linesData.push_back(2U + i * 4U + 1U);
        linesData.push_back(2U + (i + 1U) * 4U + 1U);

        linesData.push_back(2U + i * 4U + 2U);
        linesData.push_back(2U + (i + 1U) * 4U + 2U);

        linesData.push_back(2U + i * 4U + 3U);
        linesData.push_back(1U);
    }

    triangData.push_back(0U);
    triangData.push_back(2U);
    triangData.push_back(loopCnt * 4U - 2U);

    triangData.push_back(1U);
    triangData.push_back(loopCnt * 4U + 1U);
    triangData.push_back(5U);

    triangData.push_back(3U);
    triangData.push_back(loopCnt * 4U);
    triangData.push_back(loopCnt * 4U - 1U);

    triangData.push_back(3U);
    triangData.push_back(4U);
    triangData.push_back(loopCnt * 4U);

    linesData.push_back(0U);
    linesData.push_back(loopCnt * 4U - 2U);

    linesData.push_back(loopCnt * 4U - 1U);
    linesData.push_back(loopCnt * 4U);

    linesData.push_back(loopCnt * 4U + 1U);
    linesData.push_back(5U);

    linesData.push_back(3U);
    linesData.push_back(loopCnt * 4U - 1U);

    linesData.push_back(4U);
    linesData.push_back(loopCnt * 4U);

    for (uint i = 0U; i < loopCnt - 1U; ++i)
    {
        for (uint j = 0U; j < loopCnt - 1U; ++j)
        {
            triangData.push_back(pointCountLine + i * loopCnt + j);
            triangData.push_back(pointCountLine + (i + 1U) * loopCnt + j + 1U);
            triangData.push_back(pointCountLine + (i + 1U) * loopCnt + j);

            triangData.push_back(pointCountLine + i * loopCnt + j);
            triangData.push_back(pointCountLine + i * loopCnt + j + 1U);
            triangData.push_back(pointCountLine + (i + 1U) * loopCnt + j + 1U);

            linesData.push_back(pointCountLine + i * loopCnt + j);
            linesData.push_back(pointCountLine + i * loopCnt + j + 1U);

            linesData.push_back(pointCountLine + i * loopCnt + j);
            linesData.push_back(pointCountLine + (i + 1U) * loopCnt + j);
        }

        triangData.push_back(pointCountLine + (i + 1U) * loopCnt - 1U);
        triangData.push_back(pointCountLine + i * loopCnt);
        triangData.push_back(pointCountLine + (i + 1U) * loopCnt);

        triangData.push_back(pointCountLine + (i + 1U) * loopCnt - 1U);
        triangData.push_back(pointCountLine + (i + 1U) * loopCnt);
        triangData.push_back(pointCountLine + (i + 2U) * loopCnt - 1U);

        linesData.push_back(pointCountLine + (i + 1) * loopCnt - 1);
        linesData.push_back(pointCountLine + i * loopCnt);

        linesData.push_back(pointCountLine + (i + 1) * loopCnt - 1);
        linesData.push_back(pointCountLine + (i + 2) * loopCnt - 1);
    }

    for (uint j = 0U; j < loopCnt - 1U; ++j)
    {
        triangData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j);
        triangData.push_back(pointCountLine + j + 1U);
        triangData.push_back(pointCountLine + j);

        triangData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j);
        triangData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j + 1U);
        triangData.push_back(pointCountLine + j + 1U);

        linesData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j);
        linesData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j + 1U);

        linesData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt + j);
        linesData.push_back(pointCountLine + j);
    }

    triangData.push_back(pointCountLine + loopCnt * loopCnt - 1U);
    triangData.push_back(pointCountLine + 0U);
    triangData.push_back(pointCountLine + loopCnt - 1U);

    triangData.push_back(pointCountLine + loopCnt * loopCnt - 1U);
    triangData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt);
    triangData.push_back(pointCountLine + 0U);

    linesData.push_back(pointCountLine + loopCnt * loopCnt - 1U);
    linesData.push_back(pointCountLine + (loopCnt - 1U) * loopCnt);

    linesData.push_back(pointCountLine + loopCnt * loopCnt - 1U);
    linesData.push_back(pointCountLine + loopCnt - 1U);

    initBuffers(vertexData, normalData, materialData, triangData, linesData);
}
