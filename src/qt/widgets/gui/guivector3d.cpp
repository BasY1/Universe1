/*!
 * \file qt/widgets/gui/guivector3d.cpp
 * \author Michal Steller
 * \brief The QT \c QVector3D GUI class implementations
 */

#include "guivector3d.h"

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
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiVector3D::GuiVector3D(const QVector3D &_value,
                                                  const int _minimumX,
                                                  const int _maximumX,
                                                  const int _minimumY,
                                                  const int _maximumY,
                                                  const int _minimumZ,
                                                  const int _maximumZ,
                                                  const int _decimals,
                                                  const Qt::Orientation _orientation,
                                                  QObject *_parent)
    : QObject(_parent)
    , m_keepNormalized(false)
    , m_value(_value)
    , m_x(new GuiFloat(m_value.x(), _minimumX, _maximumX, _decimals, _orientation))
    , m_y(new GuiFloat(m_value.y(), _minimumY, _maximumY, _decimals, _orientation))
    , m_z(new GuiFloat(m_value.z(), _minimumZ, _maximumZ, _decimals, _orientation))
{
    m_x->setToolTip(tr("X"));
    m_y->setToolTip(tr("Y"));
    m_z->setToolTip(tr("Z"));

    connectAll();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiVector3D::~GuiVector3D()
{
    disconnectAll();
    delete m_x;
    delete m_y;
    delete m_z;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _name Property name
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _startCol Starting column index
 */
void Universe1::Widgets::GUI::GuiVector3D::layoutRow(const QString &_name,
                                                     QGridLayout *_lay,
                                                     int &_row,
                                                     const int _startCol)
{
    _lay->addWidget(new QLabel(_name), _row, _startCol);
    _lay->addWidget(new QLabel("<b>" + tr("X") + "</b>"), _row, _startCol + 1, Qt::AlignRight);
    _lay->addWidget(m_x->box(), _row, _startCol + 2);
    _lay->addWidget(m_x->slider(), _row, _startCol + 3);
    ++_row;

    _lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum), _row, _startCol);
    _lay->addWidget(new QLabel("<b>" + tr("Y") + "</b>"), _row, _startCol + 1, Qt::AlignRight);
    _lay->addWidget(m_y->box(), _row, _startCol + 2);
    _lay->addWidget(m_y->slider(), _row, _startCol + 3);
    ++_row;

    _lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Minimum), _row, _startCol);
    _lay->addWidget(new QLabel("<b>" + tr("Z") + "</b>"), _row, _startCol + 1, Qt::AlignRight);
    _lay->addWidget(m_z->box(), _row, _startCol + 2);
    _lay->addWidget(m_z->slider(), _row, _startCol + 3);
    ++_row;
}

/*!
 * \brief Connect all vector property slots
 */
void Universe1::Widgets::GUI::GuiVector3D::connectAll()
{
    connect(m_x, &GuiFloat::changed, this, &GuiVector3D::xChanged);
    connect(m_y, &GuiFloat::changed, this, &GuiVector3D::yChanged);
    connect(m_z, &GuiFloat::changed, this, &GuiVector3D::zChanged);
}

/*!
 * \brief Disconnect all vector property slots
 */
void Universe1::Widgets::GUI::GuiVector3D::disconnectAll()
{
    disconnect(m_x, &GuiFloat::changed, this, &GuiVector3D::xChanged);
    disconnect(m_y, &GuiFloat::changed, this, &GuiVector3D::yChanged);
    disconnect(m_z, &GuiFloat::changed, this, &GuiVector3D::zChanged);
}

/*!
 * \brief Setup new value
 * \param _value New value
 */
void Universe1::Widgets::GUI::GuiVector3D::setValue(QVector3D _value)
{
    disconnectAll();

    m_value = _value;

    m_x->setValue(m_value.x());
    m_y->setValue(m_value.y());
    m_z->setValue(m_value.z());

    connectAll();

    emit changed(m_value);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiVector3D::setOrientation(Qt::Orientation _orientation)
{
    m_x->setOrientation(_orientation);
    m_y->setOrientation(_orientation);
    m_z->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiVector3D::setEnabled(bool _value)
{
    m_x->setEnabled(_value);
    m_y->setEnabled(_value);
    m_z->setEnabled(_value);
}

/*!
 * \brief Setup widgets tool-tip
 * \param _toolTip Tool tip text
 */
void Universe1::Widgets::GUI::GuiVector3D::setToolTip(QString _toolTip)
{
    m_x->setToolTip(_toolTip + " - " + tr("X"));
    m_y->setToolTip(_toolTip + " - " + tr("Y"));
    m_z->setToolTip(_toolTip + " - " + tr("Z"));
}

/*!
 * \brief X changed handler
 * \param _value New x value
 */
void Universe1::Widgets::GUI::GuiVector3D::xChanged(float _value)
{
    if (m_keepNormalized)
        m_value = QVector3D(m_x->value(), m_y->value(), m_z->value()).normalized();
    else
        m_value.setX(_value);
    emit changed(m_value);
}

/*!
 * \brief Y changed handler
 * \param _value New Y value
 */
void Universe1::Widgets::GUI::GuiVector3D::yChanged(float _value)
{
    if (m_keepNormalized)
        m_value = QVector3D(m_x->value(), m_y->value(), m_z->value()).normalized();
    else
        m_value.setY(_value);
    emit changed(m_value);
}

/*!
 * \brief Z changed handler
 * \param _value New Z value
 */
void Universe1::Widgets::GUI::GuiVector3D::zChanged(float _value)
{
    if (m_keepNormalized)
        m_value = QVector3D(m_x->value(), m_y->value(), m_z->value()).normalized();
    else
        m_value.setZ(_value);
    emit changed(m_value);
}
