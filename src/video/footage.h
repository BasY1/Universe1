#ifndef UNIVERSE1_VIDEO_FOOTAGE_H
#define UNIVERSE1_VIDEO_FOOTAGE_H

#include "items/items3d/spin/item3dconstellation.h"

namespace Universe1 {
namespace Video {

/*! \brief Base class for video footage */
class Footage : public QObject
{
    Q_OBJECT
 public:
    static const QVector3D nx;  //!< Unit \b X vector
    static const QVector3D ny;  //!< Unit \b Y vector
    static const QVector3D nz;  //!< Unit \b Z vector

    const std::string footageName;    //!< Footage name
    const uint64_t footageId;         //!< Footage index
    const uint64_t footageStartTime;  //!< Footage starting time within overall video in ms
    uint64_t duration;                //!< Footage duration in ms
    uint64_t framesCount;             //!< Footage frame count

    Camera camera;              //!< Open GL camera
    std::list<Item3D *> items;  //!< All rendered 3D items

    DBSubs subs;            //!< 2D subtitles
    DBItem2D text2D;        //!< 2D text items
    DBItem2DImage image2D;  //!< 2D image items

    DBItem3DText text3D;  //!< 3D text items

    DBItem3DPlane plane;                        //!< Rectangle planes
    DBItem3DPlaneCircle planeCircle;            //!< Circle planes
    DBItem3DPlaneCircleSlice planeCircleSlice;  //!< Circle plane slices

    DBItem3DCone cone;            //!< Cones
    DBItem3DConeSlice coneSlice;  //!< Cone slices

    DBItem3DCylinder cylinder;            //!< Cylinders
    DBItem3DCylinderSlice cylinderSlice;  //!< Cylinder slices

    DBItem3DSphere sphere;            //!< Spheres
    DBItem3DSphereCup sphereCup;      //!< Sphere cups
    DBItem3DSphereSlice sphereSlice;  //!< Sphere slices

    DBItem3DWireSphere wireSphere;            //!< Wire-spheres
    DBItem3DWireSphereCup wireSphereCup;      //!< Wire-sphere cups
    DBItem3DWireSphereSlice wireSphereSlice;  //!< Wire-sphere slices

    DBItem3DTorus torus;                  //!< Torus
    DBItem3DTorusArc torusArc;            //!< Torus arc
    DBItem3DTorusCup torusCup;            //!< Torus cup
    DBItem3DTorusArcCup torusArcCup;      //!< Torus arc cup
    DBItem3DTorusSlice torusSlice;        //!< Torus slice
    DBItem3DTorusArcSlice torusArcSlice;  //!< Torus arc slice

    DBItem3DLine line;            //!< 3D lines and segments
    DBItem3DLineDots lineDots;    //!< 3D dot lines and segments
    DBItem3DLineDash lineDash;    //!< 3D dash lines and segments
    DBItem3DLineTwist lineTwist;  //!< 3D twist lines

    DBItem3DLineCircle lineCircle;    //!< 3D line circle
    DBItem3DLineArc lineArc;          //!< 3D line arc
    DBItem3DLineArcDots lineArcDots;  //!< 3D line arc dots
    DBItem3DLineArcDash lineArcDash;  //!< 3D line arc dashes

    DBItem3DLineCross cross;  //!< 3D crosses

    DBItem3DPath path;  //!< 3D path

    DBItem3DLineArrow arrow;    //!< 3D line arrow
    DBItem3DArcArrow arcArrow;  //!< Arrow over circle

    DBItem3DAngleDim angleDim;  //!< 3D angle dimensions

    DBItem3DSpace space;  //!< 3D Cartesian space

    DBItem3DHand hand;  //!< Hand items

    DBItem3DSpin spin;  //!< Spin items

    DBItem3DConstellation constellation;  //!< Constellation items

    const Config &c;  //!< Current configuration

    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _footageId Footage index
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     */
    Footage(const std::string &_footageName,
            const uint64_t _footageId,
            const uint64_t _footageStartTime,
            const std::pair<QVector3D, QVector3D> &_lastCamera);

    virtual ~Footage();  //!< Destructor

    /*!
     * \brief Initialize footage
     * \return Success flag
     */
    virtual bool initialize();

    /*!
     * \brief Save images
     * \return Success flag
     */
    virtual bool saveImages() const;

    /*!
     * \brief Static save image processor (for multi-thread support)
     * \param _footage Footage
     * \param _frameId Frame ID
     * \return Success flag
     */
    static bool saveImage(const Footage *_footage, const uint64_t _frameId);

    /*!
     * \brief Create Open GL image
     * \param _out Output image
     * \param _timeStep Time-step
     * \return Success flag
     */
    virtual bool getImage3D(QImage &_out, const uint64_t _timeStep) const;

    /*!
     * \brief Append 2D context over Open GL image
     * \param _painter Image painter
     * \param _timeStep Time-step
     * \return
     */
    virtual void paint2D(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Append 2D subtitles over Open GL image
     * \param _painter Image painter
     * \param _timeStep Time-step
     * \return
     */
    virtual void paintSubs(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Additional 2D draw over Open GL image (for overload)
     * \param _painter Image painter
     * \param _timeStep Time-step
     * \return
     */
    virtual void paint2DPost(QPainter *_painter, const uint64_t _timeStep) const;
};

/*! \brief Footage factory interface */
class FootageFactoryInterface
{
 public:
    /*!
     * \brief Create footage
     * \param _footageId Footage ID
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     * \return Created object
     */
    virtual Footage *create(const uint64_t _footageId,
                            const uint64_t _footageStartTime,
                            const std::pair<QVector3D, QVector3D> &_lastCamera) const = 0;
};

/*!
 * \brief Footage factory
 * \tparam T Footage class
 */
template <typename T>
class FootageFactory : public FootageFactoryInterface
{
 public:
    /*!
     * \brief Constructor
     */
    template <typename = std::enable_if<std::is_base_of<Footage, T>::value>>
    inline FootageFactory()
    {
    }

    /*!
     * \brief Create footage
     * \param _footageId Footage ID
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     * \return Created object
     */
    Footage *create(const uint64_t _footageId,
                    const uint64_t _footageStartTime,
                    const std::pair<QVector3D, QVector3D> &_lastCamera) const
    {
        return new T(_footageId, _footageStartTime, _lastCamera);
    }
};

/*!
 * \brief Footage database
 */
struct Footages
{
    static std::list<FootageFactoryInterface *> sequence;  //!< Sequence of footage classes

    /*!
     * \brief Append footage class to sequence
     * \return
     */
    template <typename T>
    static void add()
    {
        sequence.push_back(new FootageFactory<T>());
    }

    /*!
     * \brief Initialize footage
     * \param _footages Output footage objects
     * \return Total video duration in ms
     */
    static uint64_t init(std::list<Footage *> &_footages);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_FOOTAGEITEMS3D_H
