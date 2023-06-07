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
    const std::string footageName;    //!< Footage name
    const uint64_t footageId;         //!< Footage index
    const uint64_t footageStartTime;  //!< Footage starting time within overall video in ms

    uint64_t duration;     //!< Footage duration in ms
    uint64_t framesCount;  //!< Footage frame count

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

    const Config &cfg;  //!< Current configuration

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

 protected:
    static const QVector3D nx;  //!< Unit \b X vector
    static const QVector3D ny;  //!< Unit \b Y vector
    static const QVector3D nz;  //!< Unit \b Z vector

    static const QString tR1;  //!< String for universe constant particle radius
    static const QString tC1;  //!< String for universe constant speed
    static const QString tV1;  //!< String for particle velocity

    static const QString tO1;  //!< String for universe constant spin
    static const QString tOI;  //!< String for red spin
    static const QString tOJ;  //!< String for green spin
    static const QString tOK;  //!< String for blue spin
    static const QString tOM;  //!< String for massive spin
    static const QString tOT;  //!< String for temperature spin
    static const QString tOG;  //!< String for outer curving spin

    static const QString tOG1;  //!< String for generation 1 outer curving spin
    static const QString tOG2;  //!< String for generation 2 outer curving spin
    static const QString tOG3;  //!< String for generation 3 outer curving spin

    static const QString tVOL;  //!< String for particle volume 4/3πR1^3[m^3]
    static const QString tLEN;  //!< String for particle period length 2πR1 [m]
    static const QString tPER;  //!< String for particle period duration [s]

    static const QString tM;    //!< String for meter
    static const QString tM_2;  //!< String for meter squared
    static const QString tM_3;  //!< String for meter cubed

    static const QString tRad;  //!< String for radian

    static const QString tS;  //!< String for second

    static const QString tM_S;  //!< String for meter per second
    static const QString tR_S;  //!< String for radian per second

    static const QString tENG;  //!< String for meter squared x radian squared / second squared

    static const std::array<QString, 5> tabR1;   //!< HTML table row for universe constant particle radius
    static const std::array<QString, 5> tabC1;   //!< HTML table row for universe constant particle speed
    static const std::array<QString, 5> tabO1;   //!< HTML table row for universe constant particle spin
    static const std::array<QString, 5> tabVOL;  //!< HTML table row for universe constant particle volume
    static const std::array<QString, 5> tabLEN;  //!< HTML table row for universe constant particle period length
    static const std::array<QString, 5> tabPER;  //!< HTML table row for universe constant particle period duration

    static const QString tab_R1_C1_O1;   //!< HTML table for major universe constants
    static const QString tab_CONSTANTS;  //!< HTML table for all universe constants

    /*!
     * \brief Create HTML table row for particle position property
     * \param _position Particle position
     * \param _time Current time-step (for index)
     * \return HTML table row for particle position
     */
    inline static std::array<QString, 5> tabPPos(const QVector3D &_position, const float _time = 0.0f)
    {
        return {tr("Position"), "<b>P</b><sub>T=" + tNum(_time) + "</sub>", "=", tVec(_position), tM};
    }

    /*!
     * \brief Create HTML table row for particle velocity
     * \param _velocity Particle velocity
     * \param _time Current time-step (for index)
     * \return HTML table row for particle velocity
     */
    inline static std::array<QString, 5> tabPV1(const QVector3D &_velocity, const float _time = 0.0f)
    {
        return {tr("Velocity"),
                tCol("<b>V</b><sub>1 T=" + tNum(_time) + "</sub>", Item3DConstellation::matV1.diffuse),
                "=",
                tVec(_velocity),
                tM_S};
    }

    /*!
     * \brief Create HTML table row for particle spin I
     * \param _spinI Particle spin I
     * \param _time Current time-step (for index)
     * \return HTML table row for particle spin I
     */
    inline static std::array<QString, 5> tabPOI(const QVector3D &_spinI, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("I"), Item3DConstellation::matOI.diffuse)),
                tCol("<b>Ω</b><sub>I T=" + tNum(_time) + "</sub>", Item3DConstellation::matOI.diffuse),
                "=",
                tVec(_spinI),
                tR_S};
    }

    /*!
     * \brief Create HTML table row for particle spin J
     * \param _spinJ Particle spin J
     * \param _time Current time-step (for index)
     * \return HTML table row for particle spin J
     */
    inline static std::array<QString, 5> tabPOJ(const QVector3D &_spinJ, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("J"), Item3DConstellation::matOJ.diffuse)),
                tCol("<b>Ω</b><sub>J T=" + tNum(_time) + "</sub>", Item3DConstellation::matOJ.diffuse),
                "=",
                tVec(_spinJ),
                tR_S};
    }

    /*!
     * \brief Create HTML table row for particle spin K
     * \param _spinK Particle spin K
     * \param _time Current time-step (for index)
     * \return HTML table row for particle spin K
     */
    inline static std::array<QString, 5> tabPOK(const QVector3D &_spinK, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("K"), Item3DConstellation::matOK.diffuse)),
                tCol("<b>Ω</b><sub>K T=" + tNum(_time) + "</sub>", Item3DConstellation::matOK.diffuse),
                "=",
                tVec(_spinK),
                tR_S};
    }

    /*!
     * \brief Create HTML table row for particle massive spin
     * \param _spinM Particle massive spin
     * \param _time Current time-step (for index)
     * \return HTML table row for particle massive spin
     */
    inline static std::array<QString, 5> tabPOM(const QVector3D &_spinM, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("Massive"), Item3DConstellation::matOM.diffuse)),
                tCol("<b>Ω</b><sub>M T=" + tNum(_time) + "</sub>", Item3DConstellation::matOM.diffuse),
                "=",
                tVec(_spinM),
                tR_S};
    }

    /*!
     * \brief Create HTML table row for particle temperature spin
     * \param _spinT Particle temperature spin
     * \param _time Current time-step (for index)
     * \return HTML table row for particle temperature spin
     */
    inline static std::array<QString, 5> tabPOT(const QVector3D &_spinT, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("Temperature"), Item3DConstellation::matOT.diffuse)),
                tCol("<b>Ω</b><sub>T T=" + tNum(_time) + "</sub>", Item3DConstellation::matOT.diffuse),
                "=",
                tVec(_spinT),
                tR_S};
    }

    /*!
     * \brief Create HTML table row for particle curving spin
     * \param _spinG Particle curving spin
     * \param _time Current time-step (for index)
     * \return HTML table row for particle curving spin
     */
    inline static std::array<QString, 5> tabPOG(const QVector3D &_spinG, const float _time = 0.0f)
    {
        return {tr("%1 spin").arg(tCol(tr("Curving"), Item3DConstellation::matOG1.diffuse)),
                tCol("<b>Ω</b><sub>G T=" + tNum(_time) + "</sub>", Item3DConstellation::matOG1.diffuse),
                "=",
                tVec(_spinG),
                tR_S};
    }

    /*!
     * \brief Create HTML table with particle properties
     * \param _data Particle spins
     * \param _position Particle position
     * \param _velocity Particle velocity
     * \param _time Current time-step (for index)
     * \return HTML table with particle properties
     */
    inline static QString tabParticle(const Math::Constellation<float> &_data,
                                      const QVector3D &_position,
                                      const QVector3D &_velocity,
                                      const float _time = 0.0f)
    {
        return mkTab({{QObject::tr("Particle at time %1 %2").arg(tNum(_time), tS), "-C-", "", "", ""},
                      tabPPos(_position, _time),
                      tabPV1(_velocity, _time),
                      tabPOI(_data.qI(), _time),
                      tabPOJ(_data.qJ(), _time),
                      tabPOK(_data.qK(), _time),
                      tabPOM(_data.qM(), _time)});
    }

    /*!
     * \brief Create HTML table with particle properties
     * \param _data Particle spins
     * \param _position Particle position
     * \param _velocity Particle velocity
     * \param _spinT Particle temperature spin
     * \param _time Current time-step (for index)
     * \return HTML table with particle properties
     */
    inline static QString tabParticle(const Math::Constellation<float> &_data,
                                      const QVector3D &_position,
                                      const QVector3D &_velocity,
                                      const QVector3D &_spinT,
                                      const float _time = 0.0f)
    {
        return mkTab({{QObject::tr("Particle at time %1 %2").arg(tNum(_time), tS), "-C-", "", "", ""},
                      tabPPos(_position, _time),
                      tabPV1(_velocity, _time),
                      tabPOI(_data.qI(), _time),
                      tabPOJ(_data.qJ(), _time),
                      tabPOK(_data.qK(), _time),
                      tabPOM(_data.qM(), _time),
                      tabPOT(_spinT, _time)});
    }

    /*!
     * \brief Create HTML table with particle properties
     * \param _data Particle spins
     * \param _position Particle position
     * \param _velocity Particle velocity
     * \param _spinT Particle temperature spin
     * \param _spinG Particle curving spin
     * \param _time Current time-step (for index)
     * \return HTML table with particle properties
     */
    inline static QString tabParticle(const Math::Constellation<float> &_data,
                                      const QVector3D &_position,
                                      const QVector3D &_velocity,
                                      const QVector3D &_spinT,
                                      const QVector3D &_spinG,
                                      const float _time = 0.0f)
    {
        return mkTab({{QObject::tr("Particle at time %1 %2").arg(tNum(_time), tS), "-C-", "", "", ""},
                      tabPPos(_position, _time),
                      tabPV1(_velocity, _time),
                      tabPOI(_data.qI(), _time),
                      tabPOJ(_data.qJ(), _time),
                      tabPOK(_data.qK(), _time),
                      tabPOM(_data.qM(), _time),
                      tabPOT(_spinT, _time),
                      tabPOG(_spinG, _time)});
    }

    /*!
     * \brief Create colored HTML text
     * \param _text HTML text
     * \param _color Color
     * \return Colored HTML text
     */
    inline static QString tCol(const QString &_text, const QColor &_color)
    {
        return QString("<font color=\"%1\">%2</font>").arg(_color.name()).arg(_text);
    }

    /*!
     * \brief Create red HTML text
     * \param _text HTML text
     * \return Red HTML text
     */
    inline static QString tR(const QString &_text)
    {
        return tCol(_text, Qt::red);
    }

    /*!
     * \brief Create green HTML text
     * \param _text HTML text
     * \return Green HTML text
     */
    inline static QString tG(const QString &_text)
    {
        return tCol(_text, Qt::green);
    }

    /*!
     * \brief Create blue HTML text
     * \param _text HTML text
     * \return Blue HTML text
     */
    inline static QString tB(const QString &_text)
    {
        return tCol(_text, Qt::blue);
    }

    /*!
     * \brief Create number text
     * \param _val Value
     * \return Number as text
     */
    inline static QString tNum(const double _val)
    {
        return Config::cfg().tNum(_val);
    }

    /*!
     * \brief Create 3D vector as text
     * \param _vec 3D vector
     * \return 3D vector as text
     */
    inline static QString tVec(const QVector3D &_vec)
    {
        return Config::cfg().tVec(_vec);
    }

    /*!
     * \brief Create text for current time value
     * \param _val Current time value
     * \return Text for current time value
     */
    inline static QString tCurTime(const double _val)
    {
        return tr("<table><tr><td align=\"right\">Time:&nbsp;</td><td align=\"left\">%1 %2</td></tr>"
                  "<tr><td align=\"right\"><sup>Period:</sup>&nbsp;</td>"
                  "<td align=\"left\"><sup>%3 [<i>s/2π</i>]</sup></td></tr></table>")
            .arg(tNum(_val), tS, tNum(_val / (2.0 * M_PI)));
    }

    /*!
     * \brief Make single column HTML table
     * \param _rows Table rows
     * \param _align Column align
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    inline static QString mkTab(const std::vector<QString> &_rows,
                                const QString &_align = "center",
                                const bool _border = false,
                                const int _cellpadding = 5)
    {
        QString result = "<table";
        if (_border)
            result += " border=\"1\"";
        if (_cellpadding > 0)
            result += " cellpadding=\"" + QString::number(_cellpadding) + "\"";
        result += ">";

        for (const QString &r : _rows)
            result += "<tr><td align=\"" + _align + "\">" + r + "</td></tr>";
        result += "</table>";
        return result;
    }

    /*!
     * \brief Make \b N column HTML table - template
     * \tparam CNT Template count of columns
     * \param _rows Table rows
     * \param _aligns Column aligns
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    template <size_t CNT>
    static QString mkTabT(const std::vector<std::array<QString, CNT>> &_rows,
                          const std::array<QString, CNT> &_aligns,
                          const bool _border = false,
                          const int _cellpadding = 5)
    {
        QString result = "<table";
        if (_border)
            result += " border=\"1\"";
        if (_cellpadding > 0)
            result += " cellpadding=\"" + QString::number(_cellpadding) + "\"";
        result += ">";

        for (const std::array<QString, CNT> &r : _rows)
        {
            bool isSingle = r[1] == "-C-";
            if (isSingle)
                for (size_t i = 2UL; i < CNT; ++i)
                    if (!r[i].isEmpty())
                    {
                        isSingle = false;
                        break;
                    }

            if (isSingle)
            {
                result +=
                    "<tr><td align=\"center\" colspan=\"" + QString::number(CNT) + "\"><b>" + r[0] + "</b></td></tr>";
                continue;
            }

            result += "<tr>";
            for (size_t i = 0UL; i < CNT; ++i)
                result += "<td align=\"" + _aligns[i] + "\">" + r[i] + "</td>";
            result += "</tr>";
        }
        result += "</table>";
        return result;
    }

    /*!
     * \brief Make two column HTML table
     * \param _rows Table rows
     * \param _aligns Column aligns
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    inline static QString mkTab(const std::vector<std::array<QString, 2>> &_rows,
                                const std::array<QString, 2> &_aligns = {"left", "left"},
                                const bool _border = false,
                                const int _cellpadding = 5)
    {
        return mkTabT<2>(_rows, _aligns, _border, _cellpadding);
    }

    /*!
     * \brief Make three column HTML table
     * \param _rows Table rows
     * \param _aligns Column aligns
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    inline static QString mkTab(const std::vector<std::array<QString, 3>> &_rows,
                                const std::array<QString, 3> &_aligns = {"left", "left", "left"},
                                const bool _border = false,
                                const int _cellpadding = 5)
    {
        return mkTabT<3>(_rows, _aligns, _border, _cellpadding);
    }

    /*!
     * \brief Make four column HTML table
     * \param _rows Table rows
     * \param _aligns Column aligns
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    inline static QString mkTab(const std::vector<std::array<QString, 4>> &_rows,
                                const std::array<QString, 4> &_aligns = {"left", "left", "left", "left"},
                                const bool _border = false,
                                const int _cellpadding = 5)
    {
        return mkTabT<4>(_rows, _aligns, _border, _cellpadding);
    }

    /*!
     * \brief Make five column HTML table
     * \param _rows Table rows
     * \param _aligns Column aligns
     * \param _border Use border flag
     * \param _cellpadding Table cell padding
     * \return HTML table
     */
    inline static QString mkTab(const std::vector<std::array<QString, 5>> &_rows,
                                const std::array<QString, 5> &_aligns = {"left", "left", "center", "left", "left"},
                                const bool _border = false,
                                const int _cellpadding = 5)
    {
        return mkTabT<5>(_rows, _aligns, _border, _cellpadding);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_FOOTAGEITEMS3D_H
