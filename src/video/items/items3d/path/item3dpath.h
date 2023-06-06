#ifndef UNIVERSE1_VIDEO_ITEM3DLINEPATH_H
#define UNIVERSE1_VIDEO_ITEM3DLINEPATH_H

#include "../space/item3dspace.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D line path item */
struct Item3DPath : public Item3D
{
    std::vector<DynamicVec3> points;  //!< Path point properties

    DynamicValue<float> lineRadius;   //!< Line radius
    DynamicValue<float> pointRadius;  //!< Path point radius

    DynamicMaterialGroup materialLine;   //!< Material line
    DynamicMaterialGroup materialPoint;  //!< Material point

    DynamicValue<uint> quality;  //!< Circle quality

    DynamicBool showLine;   //!< Show line flag
    DynamicBool showPoint;  //!< Show point flag

    /*!
     * \brief Constructor
     * \param _path Initial path points
     * \param _lineRadius Initial line radius
     * \param _pointRadius Initial path point radius
     * \param _quality Initial circle quality
     * \param _showLine Initial show line flag
     * \param _showPoint Initial show point flag
     * \param _visible Initial visible flag
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \param _name Item name
     */
    Item3DPath(const std::vector<QVector3D> &_path,
               const float _lineRadius,
               const float _pointRadius,
               const uint _quality,
               const bool _showLine,
               const bool _showPoint,
               const bool _visible,
               const Material &_materialLine,
               const Material &_materialPoint,
               const std::string &_name);

    /*!
     * \brief Add same position as last stored at time-step
     * \param _timeStep Time-step
     */
    inline void addSame(const uint64_t _timeStep)
    {
        for (DynamicVec3 &dp : points)
            dp.addSame(_timeStep);
    }

    /*!
     * \brief Add new positions at time-step
     * \param _timeStep Time-step
     * \param _positions Next positions
     */
    inline void add(const uint64_t _timeStep, const std::vector<QVector3D> &_positions)
    {
        if (_positions.size() != points.size())
        {
            std::cerr << "Error[" << name << "]: Can't add path invalid point count [" << _positions.size()
                      << "], expected [" << points.size() << "]" << std::endl;
            return;
        }
        for (size_t i = 0UL; i < points.size(); ++i)
            points[i].add(_timeStep, _positions[i]);
    }

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;

    /*!
     * \brief Build 3D path data
     * \param _out Output 3D data list
     * \param _path Path points
     * \param _lineRadius Line radius
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    static void buildDataPath(std::list<Data3D> &_out,
                              const std::vector<QVector3D> &_path,
                              const float _lineRadius,
                              const uint _quality,
                              const Material &_material);

    /*!
     * \brief Build 3D path points data
     * \param _out Output 3D data list
     * \param _path Path points
     * \param _lineRadius Line radius
     * \param _pointRadius Point radius
     * \param _quality Circle quality
     * \param _material Material
     * \return
     */
    static void buildDataPoints(std::list<Data3D> &_out,
                                const std::vector<QVector3D> &_path,
                                const float _lineRadius,
                                const float _pointRadius,
                                const uint _quality,
                                const Material &_material);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _path Path points
     * \param _lineRadius Line radius
     * \param _pointRadius Point radius
     * \param _quality Circle quality
     * \param _showLine Show line flag
     * \param _showPoint Show point flag
     * \param _materialLine Line material
     * \param _materialPoint Point material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const std::vector<QVector3D> &_path,
                          const float _lineRadius,
                          const float _pointRadius,
                          const uint _quality,
                          const bool _showLine,
                          const bool _showPoint,
                          const Material &_materialLine,
                          const Material &_materialPoint);
};

/*! \brief Footage 3D path database */
struct DBItem3DPath : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DPath(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D path item
     * \param _path Initial path points
     * \param _lineRadius Initial line radius
     * \param _pointRadius Initial path point radius
     * \param _quality Initial circle quality
     * \param _showLine Initial show line flag
     * \param _showPoint Initial show point flag
     * \param _visible Initial visible flag
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \return Created item
     */
    Item3DPath *add(const std::vector<QVector3D> &_path,
                    const float _lineRadius,
                    const float _pointRadius,
                    const uint _quality,
                    const bool _showLine,
                    const bool _showPoint,
                    const bool _visible,
                    const Material &_materialLine,
                    const Material &_materialPoint);

    /*!
     * \brief Add visible 3D path item
     * \param _path Initial path points
     * \param _lineRadius Initial line radius
     * \param _pointRadius Initial path point radius
     * \param _quality Initial circle quality
     * \param _showLine Initial show line flag
     * \param _showPoint Initial show point flag
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \return Created item
     */
    inline Item3DPath *add(const std::vector<QVector3D> &_path,
                           const float _lineRadius,
                           const float _pointRadius,
                           const uint _quality,
                           const bool _showLine,
                           const bool _showPoint,
                           const Material &_materialLine,
                           const Material &_materialPoint)
    {
        return add(
            _path, _lineRadius, _pointRadius, _quality, _showLine, _showPoint, true, _materialLine, _materialPoint);
    }

    /*!
     * \brief Add visible 3D path item
     * \param _path Initial path points
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \return Created item
     */
    inline Item3DPath *
    add(const std::vector<QVector3D> &_path, const Material &_materialLine, const Material &_materialPoint)
    {
        const Config &c = Config::cfg();
        return add(_path, c.lineRadius, c.lineRadius * 3.0f, c.qualityLine, true, false, _materialLine, _materialPoint);
    }

    /*!
     * \brief Add visible 3D path item
     * \param _path Initial path points
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPath *add(const std::vector<QVector3D> &_path, const Material &_material)
    {
        return add(_path, _material, _material.darker());
    }

    //

    /*!
     * \brief Add hidden 3D path item
     * \param _path Initial path points
     * \param _lineRadius Initial line radius
     * \param _pointRadius Initial path point radius
     * \param _quality Initial circle quality
     * \param _showLine Initial show line flag
     * \param _showPoint Initial show point flag
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \return Created item
     */
    inline Item3DPath *addHidden(const std::vector<QVector3D> &_path,
                                 const float _lineRadius,
                                 const float _pointRadius,
                                 const uint _quality,
                                 const bool _showLine,
                                 const bool _showPoint,
                                 const Material &_materialLine,
                                 const Material &_materialPoint)
    {
        return add(
            _path, _lineRadius, _pointRadius, _quality, _showLine, _showPoint, false, _materialLine, _materialPoint);
    }

    /*!
     * \brief Add hidden 3D path item
     * \param _path Initial path points
     * \param _materialLine Initial line material
     * \param _materialPoint Initial point material
     * \return Created item
     */
    inline Item3DPath *
    addHidden(const std::vector<QVector3D> &_path, const Material &_materialLine, const Material &_materialPoint)
    {
        const Config &c = Config::cfg();
        return addHidden(
            _path, c.lineRadius, c.lineRadius * 3.0f, c.qualityLine, true, false, _materialLine, _materialPoint);
    }

    /*!
     * \brief Add hidden 3D path item
     * \param _path Initial path points
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPath *addHidden(const std::vector<QVector3D> &_path, const Material &_material)
    {
        return addHidden(_path, _material, _material.darker());
    }

};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINEPATH_H
