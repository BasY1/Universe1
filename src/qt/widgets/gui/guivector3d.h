/*!
 * \file qt/widgets/gui/guivector3d.h
 * \author Michal Steller
 * \brief The QT \c QVector3D GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUIVECTOR3D_H
#define UNIVERSE1_WIDGETS_GUI_GUIVECTOR3D_H

#include <QLabel>
#include <QVector3D>

#include "guifloat.h"

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief \c QVector3D GUI
 */
class GuiVector3D : public QObject
{
    Q_OBJECT
 public:
    GuiVector3D(const QVector3D &_value,
                const int _minimumX,
                const int _maximumX,
                const int _minimumY,
                const int _maximumY,
                const int _minimumZ,
                const int _maximumZ,
                const int _decimals,
                const Qt::Orientation _orientation,
                QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const int _minimumX,
                       const int _maximumX,
                       const int _minimumY,
                       const int _maximumY,
                       const int _minimumZ,
                       const int _maximumZ,
                       const int _decimals,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const int _minimumX,
                       const int _maximumX,
                       const int _minimumY,
                       const int _maximumY,
                       const int _minimumZ,
                       const int _maximumZ,
                       const Qt::Orientation _orientation,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const int _minimumX,
                       const int _maximumX,
                       const int _minimumY,
                       const int _maximumY,
                       const int _minimumZ,
                       const int _maximumZ,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const std::pair<QVector3D, QVector3D> &_sceneRange,
                       const int _decimals,
                       const Qt::Orientation _orientation,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const std::pair<QVector3D, QVector3D> &_sceneRange,
                       const int _decimals,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const std::pair<QVector3D, QVector3D> &_sceneRange,
                       const Qt::Orientation _orientation,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const std::pair<QVector3D, QVector3D> &_sceneRange,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value,
                       const int _decimals,
                       const Qt::Orientation _orientation,
                       QObject *_parent = nullptr);

    inline GuiVector3D(const QVector3D &_value, const int _decimals, QObject *_parent = nullptr);
    inline GuiVector3D(const QVector3D &_value, const Qt::Orientation _orientation, QObject *_parent = nullptr);
    inline GuiVector3D(const QVector3D &_value, QObject *_parent = nullptr);

    ~GuiVector3D();

    inline bool keepNormalized() const;
    inline const QVector3D &value() const;

    inline GuiFloat *xGui();
    inline GuiFloat *yGui();
    inline GuiFloat *zGui();

    void layoutRow(const QString &_name, QGridLayout *_lay, int &_row, const int _startCol = 0);

 protected:
    void connectAll();
    void disconnectAll();

 public slots:
    void setValue(QVector3D _value);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);
    void setToolTip(QString _toolTip);

 protected slots:
    void xChanged(float _value);
    void yChanged(float _value);
    void zChanged(float _value);

 signals:
    /*!
     * \brief Emits when 3D vector was changed
     * \param _value New 3D vector value
     */
    void changed(const QVector3D &_value);

 protected:
    bool m_keepNormalized;  //!< Keep value in normalized form
    QVector3D m_value;      //!< Current color
    GuiFloat *m_x;          //!< Red slider
    GuiFloat *m_y;          //!< Green slider
    GuiFloat *m_z;          //!< Blue slider
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _minimumX Minimum X value
 * \param _maximumX Maximum X value
 * \param _minimumY Minimum Y value
 * \param _maximumY Maximum Y value
 * \param _minimumZ Minimum Z value
 * \param _maximumZ Maximum Z value
 * \param _decimals Decimal count (range 0 to 6)
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const int _minimumX,
                                const int _maximumX,
                                const int _minimumY,
                                const int _maximumY,
                                const int _minimumZ,
                                const int _maximumZ,
                                const int _decimals,
                                QObject *_parent)
    : GuiVector3D(
          _value, _minimumX, _maximumX, _minimumY, _maximumY, _minimumZ, _maximumZ, _decimals, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _minimumX Minimum X value
 * \param _maximumX Maximum X value
 * \param _minimumY Minimum Y value
 * \param _maximumY Maximum Y value
 * \param _minimumZ Minimum Z value
 * \param _maximumZ Maximum Z value
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const int _minimumX,
                                const int _maximumX,
                                const int _minimumY,
                                const int _maximumY,
                                const int _minimumZ,
                                const int _maximumZ,
                                const Qt::Orientation _orientation,
                                QObject *_parent)
    : GuiVector3D(_value, _minimumX, _maximumX, _minimumY, _maximumY, _minimumZ, _maximumZ, 3, _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _minimumX Minimum X value
 * \param _maximumX Maximum X value
 * \param _minimumY Minimum Y value
 * \param _maximumY Maximum Y value
 * \param _minimumZ Minimum Z value
 * \param _maximumZ Maximum Z value
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 * \note Default horizontal orientation
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const int _minimumX,
                                const int _maximumX,
                                const int _minimumY,
                                const int _maximumY,
                                const int _minimumZ,
                                const int _maximumZ,
                                QObject *_parent)
    : GuiVector3D(_value, _minimumX, _maximumX, _minimumY, _maximumY, _minimumZ, _maximumZ, 3, Qt::Horizontal, _parent)
{
}

#ifndef DOXYGEN_SKIP
#define MIN_X(_SR) (static_cast<int>(_SR.first.x()) - 1)
#define MAX_X(_SR) (static_cast<int>(_SR.second.x()) + 1)
#define MIN_Y(_SR) (static_cast<int>(_SR.first.y()) - 1)
#define MAX_Y(_SR) (static_cast<int>(_SR.second.y()) + 1)
#define MIN_Z(_SR) (static_cast<int>(_SR.first.z()) - 1)
#define MAX_Z(_SR) (static_cast<int>(_SR.second.z()) + 1)
#endif  // DOXYGEN_SKIP

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _sceneRange Vector value range (Pair of minimum and maximum)
 * \param _decimals Decimal count (range 0 to 6)
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const std::pair<QVector3D, QVector3D> &_sceneRange,
                                const int _decimals,
                                const Qt::Orientation _orientation,
                                QObject *_parent)
    : GuiVector3D(_value,
                  MIN_X(_sceneRange),
                  MAX_X(_sceneRange),
                  MIN_Y(_sceneRange),
                  MAX_Y(_sceneRange),
                  MIN_Z(_sceneRange),
                  MAX_Z(_sceneRange),
                  _decimals,
                  _orientation,
                  _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _sceneRange Vector value range (Pair of minimum and maximum)
 * \param _decimals Decimal count (range 0 to 6)
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const std::pair<QVector3D, QVector3D> &_sceneRange,
                                const int _decimals,
                                QObject *_parent)
    : GuiVector3D(_value,
                  MIN_X(_sceneRange),
                  MAX_X(_sceneRange),
                  MIN_Y(_sceneRange),
                  MAX_Y(_sceneRange),
                  MIN_Z(_sceneRange),
                  MAX_Z(_sceneRange),
                  _decimals,
                  Qt::Horizontal,
                  _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _sceneRange Vector value range (Pair of minimum and maximum)
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const std::pair<QVector3D, QVector3D> &_sceneRange,
                                const Qt::Orientation _orientation,
                                QObject *_parent)
    : GuiVector3D(_value,
                  MIN_X(_sceneRange),
                  MAX_X(_sceneRange),
                  MIN_Y(_sceneRange),
                  MAX_Y(_sceneRange),
                  MIN_Z(_sceneRange),
                  MAX_Z(_sceneRange),
                  3,
                  _orientation,
                  _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _sceneRange Vector value range (Pair of minimum and maximum)
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 * \note Default horizontal orientation
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const std::pair<QVector3D, QVector3D> &_sceneRange,
                                QObject *_parent)
    : GuiVector3D(_value,
                  MIN_X(_sceneRange),
                  MAX_X(_sceneRange),
                  MIN_Y(_sceneRange),
                  MAX_Y(_sceneRange),
                  MIN_Z(_sceneRange),
                  MAX_Z(_sceneRange),
                  3,
                  Qt::Horizontal,
                  _parent)
{
}

#undef MIN_X
#undef MAX_X
#undef MIN_Y
#undef MAX_Y
#undef MIN_Z
#undef MAX_Z

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _decimals Decimal count (range 0 to 6)
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default range from -1 to 1 (Value keeps normalized)
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value,
                                const int _decimals,
                                const Qt::Orientation _orientation,
                                QObject *_parent)
    : GuiVector3D(_value, -1, 1, -1, 1, -1, 1, _decimals, _orientation, _parent)
{
    m_keepNormalized = true;
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _decimals Decimal count (range 0 to 6)
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 * \note Default range from -1 to 1 (Value keeps normalized)
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value, const int _decimals, QObject *_parent)
    : GuiVector3D(_value, -1, 1, -1, 1, -1, 1, _decimals, Qt::Horizontal, _parent)
{
    m_keepNormalized = true;
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 * \note Default range from -1 to 1 (Value keeps normalized)
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value, const Qt::Orientation _orientation, QObject *_parent)
    : GuiVector3D(_value, -1, 1, -1, 1, -1, 1, 3, _orientation, _parent)
{
    m_keepNormalized = true;
}

/*!
 * \brief Constructor
 * \param _value Initialization value
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 * \note Default horizontal orientation
 * \note Default range from -1 to 1 (Value keeps normalized)
 */
inline GuiVector3D::GuiVector3D(const QVector3D &_value, QObject *_parent)
    : GuiVector3D(_value, -1, 1, -1, 1, -1, 1, 3, Qt::Horizontal, _parent)
{
    m_keepNormalized = true;
}

/*!
 * \brief Getter for keep normalized flag
 * \returns Keep normalized flag
 */
inline bool GuiVector3D::keepNormalized() const
{
    return m_keepNormalized;
}

/*!
 * \brief Getter for current value
 * \returns Current value
 */
inline const QVector3D &GuiVector3D::value() const
{
    return m_value;
}

/*!
 * \brief Getter for X widgets
 * \returns X widgets
 */
inline GuiFloat *GuiVector3D::xGui()
{
    return m_x;
}

/*!
 * \brief Getter for Y widgets
 * \returns Y widgets
 */
inline GuiFloat *GuiVector3D::yGui()
{
    return m_y;
}

/*!
 * \brief Getter for Z widgets
 * \returns Z widgets
 */
inline GuiFloat *GuiVector3D::zGui()
{
    return m_z;
}
}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUIVECTOR3D_H
