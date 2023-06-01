#ifndef UNIVERSE1_VIDEO_DATA3D_H
#define UNIVERSE1_VIDEO_DATA3D_H

#include "camera.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Open GL 3D data
 */
struct Data3D
{
    Material material;               //!< Material
    std::vector<QVector3D> points;   //!< Vertex positions
    std::vector<QVector3D> normals;  //!< Vertex normal
    std::vector<uint> indexes;       //!< Triangle indices

    Data3D() = default;  //!< Default constructor

    /*!
     * \brief Constructor
     * \param _material Initial material
     */
    inline Data3D(const Material &_material)
        : material(_material)
    {
    }

    /*!
     * \brief Constructor
     * \param _material Initial material
     * \param _sizePoints Reserve size for vertices
     * \param _sizeIndexes Reserve size for indices
     */
    inline Data3D(const Material &_material, const size_t _sizePoints, const size_t _sizeIndexes)
        : material(_material)
    {
        points.reserve(_sizePoints);
        normals.reserve(_sizePoints);
        indexes.reserve(_sizeIndexes);
    }

    /*!
     * \brief Constructor
     * \param _material Initial material
     * \param _sizePoints Reserve size for vertices
     * \param _sizeIndexes Reserve size for indices
     * \param _singleNormal Single normal for all points
     */
    inline Data3D(const Material &_material,
                  const size_t _sizePoints,
                  const size_t _sizeIndexes,
                  const QVector3D &_singleNormal)
        : material(_material)
        , normals(_sizePoints, _singleNormal)
    {
        points.reserve(_sizePoints);
        indexes.reserve(_sizeIndexes);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DATA3D_H
