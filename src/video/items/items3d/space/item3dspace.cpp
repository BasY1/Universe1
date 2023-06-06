#include "item3dspace.h"

Universe1::Video::Item3DSpace::Item3DSpace(const bool _showArrows,
                                           const bool _showArrowNames,
                                           const bool _showPlaneXY,
                                           const uint _sizePlanePX,
                                           const uint _sizePlaneMX,
                                           const uint _sizePlanePY,
                                           const uint _sizePlaneMY,
                                           const bool _visible,
                                           const std::string &_name)
    : Item3D(_visible, _name)
    , showArrows(_showArrows, name + ".showArrows")
    , showArrowNames(_showArrowNames, name + ".showArrowNames")
    , showPlaneXY(_showPlaneXY, name + ".showPlaneXY")
    , sizePlanePX(_sizePlanePX, name + ".sizePlanePX")
    , sizePlaneMX(_sizePlaneMX, name + ".sizePlaneMX")
    , sizePlanePY(_sizePlanePY, name + ".sizePlanePY")
    , sizePlaneMY(_sizePlaneMY, name + ".sizePlaneMY")
{
    props.push_back(&showArrows);
    props.push_back(&showArrowNames);
    props.push_back(&showPlaneXY);
    props.push_back(&sizePlanePX);
    props.push_back(&sizePlaneMX);
    props.push_back(&sizePlanePY);
    props.push_back(&sizePlaneMY);
}

void Universe1::Video::Item3DSpace::addData3D(std::list<Data3D> &_out,
                                              const Shader *_shader,
                                              const uint64_t _timeStep) const
{
    static const QVector3D p0(0, 0, 0);
    static const Material matX = Material(Qt::red);
    static const Material matY = Material(Qt::green);
    static const Material matZ = Material(Qt::blue);
    static const Material space1 = Material(QColor(96, 96, 96), 32, 1);
    static const Material space5 = Material(QColor(128, 128, 128), 24, 1);
    static const Material space10 = Material(QColor(192, 192, 192), 16, 1);

    const Config &c = Config::cfg();
    const bool isArrow = showArrows.getValue(_timeStep);

    if (isArrow)
    {
        const uint qa = c.qualityLine;
        const float lr = c.lineRadius * 2.0f;
        const float ar = c.arrowRadius * 2.0f;
        const float al = c.arrowLength * 2.0f;

        Item3DLineArrow::buildData(_out, p0, nx, al, ar, lr, qa, matX);
        Item3DLineArrow::buildData(_out, p0, ny, al, ar, lr, qa, matY);
        Item3DLineArrow::buildData(_out, p0, nz, al, ar, lr, qa, matZ);

        if (showArrowNames.getValue(_timeStep))
        {
            static const float add = 1.1f;
            static const QVector3D px = nx * add;
            static const QVector3D py = ny * add;
            static const QVector3D pz = nz * add;
            static const Qt::Alignment alg = Qt::AlignHCenter | Qt::AlignTop;
            Item3DText::buildData(_out, _shader, QObject::tr("X"), 1.0f, alg, px, matX);
            Item3DText::buildData(_out, _shader, QObject::tr("Y"), 1.0f, alg, py, matY);
            Item3DText::buildData(_out, _shader, QObject::tr("Z"), 1.0f, alg, pz, matZ);
        }
    }

    if (!showPlaneXY.getValue(_timeStep))
        return;

    const int xb = -static_cast<int>(sizePlaneMX.getValue(_timeStep));
    const int xe = static_cast<int>(sizePlanePX.getValue(_timeStep));
    const int yb = -static_cast<int>(sizePlaneMY.getValue(_timeStep));
    const int ye = static_cast<int>(sizePlanePY.getValue(_timeStep));
    if ((xb == 0 && xe == 0) || (yb == 0 && ye == 0))
        return;

    const float maxX = static_cast<float>(xe) + 0.5F;
    const float minX = static_cast<float>(xb) - 0.5F;
    const float maxY = static_cast<float>(ye) + 0.5F;
    const float minY = static_cast<float>(yb) - 0.5F;
    const float lr1 = c.lineRadius * 0.5f;
    const float ql1 = c.qualityLine;
    if (c.level == 0U)
    {
        for (int x = xb; x <= xe; ++x)
            Item3DLineSegment::buildData(_out, QVector3D(x, minY, 0), QVector3D(x, maxY, 0), lr1, ql1, space1);
        for (int y = yb; y <= ye; ++y)
            Item3DLineSegment::buildData(_out, QVector3D(minX, y, 0), QVector3D(maxX, y, 0), lr1, ql1, space1);
        return;
    }

    const float lr5 = c.lineRadius * 0.75f;
    const float ql5 = c.qualityLine;
    const float lr10 = c.lineRadius;
    const float ql10 = c.qualityLine;

    static const float len1 = 0.2;
    static const float len5 = 0.225;
    static const float len10 = 0.25;

    for (int x = xb; x <= xe; ++x)
    {
        const float xf = static_cast<float>(x);
        if (x == 0)
        {
            if (isArrow)
            {
                if (xb < 0)
                    Item3DLineSegment::buildData(
                        _out, QVector3D(xf, minY, 0), QVector3D(xf, -0.25f, 0), lr10, ql10, space10);
                if (xe > 1)
                    Item3DLineSegment::buildData(
                        _out, QVector3D(xf, 1.25f, 0), QVector3D(xf, maxY, 0), lr10, ql10, space10);
            }
            else
            {
                Item3DLineSegment::buildData(_out, QVector3D(xf, minY, 0), QVector3D(xf, maxY, 0), lr10, ql10, space10);
            }
        }
        else if (x % 10 == 0)
        {
            Item3DLineSegment::buildData(_out, QVector3D(xf, minY, 0), QVector3D(xf, maxY, 0), lr10, ql10, space10);
        }
        else if (x % 5 == 0)
        {
            Item3DLineSegment::buildData(_out, QVector3D(xf, minY, 0), QVector3D(xf, maxY, 0), lr5, ql5, space5);
        }
        else
        {
            for (int y = yb; y <= ye; ++y)
            {
                const float yf = static_cast<float>(y);
                float l = len1;
                if (y % 10 == 0)
                    l = len10;
                else if (y % 5 == 0)
                    l = len5;
                Item3DLineSegment::buildData(
                    _out, QVector3D(xf, yf - l, 0), QVector3D(xf, yf + l, 0), lr1, ql1, space1);
            }
        }
    }

    for (int y = yb; y <= ye; ++y)
    {
        const float yf = static_cast<float>(y);
        if (y == 0)
        {
            if (isArrow)
            {
                if (yb < 0)
                    Item3DLineSegment::buildData(
                        _out, QVector3D(minX, yf, 0), QVector3D(-0.25f, yf, 0), lr10, ql10, space10);

                if (ye > 1)
                    Item3DLineSegment::buildData(
                        _out, QVector3D(1.25f, yf, 0), QVector3D(maxX, yf, 0), lr10, ql10, space10);
            }
            else
            {
                Item3DLineSegment::buildData(_out, QVector3D(minX, yf, 0), QVector3D(maxX, yf, 0), lr10, ql10, space10);
            }
        }
        else if (y % 10 == 0)
        {
            Item3DLineSegment::buildData(_out, QVector3D(minX, yf, 0), QVector3D(maxX, yf, 0), lr10, ql10, space10);
        }
        else if (y % 5 == 0)
        {
            Item3DLineSegment::buildData(_out, QVector3D(minX, yf, 0), QVector3D(maxX, yf, 0), lr5, ql5, space5);
        }
        else
        {
            for (int x = xb; x <= xe; ++x)
            {
                const float xf = static_cast<float>(x);
                float l = len1;
                if (x % 10 == 0)
                    l = len10;
                else if (x % 5 == 0)
                    l = len5;
                Item3DLineSegment::buildData(
                    _out, QVector3D(xf - l, yf, 0), QVector3D(xf + l, yf, 0), lr1, ql1, space1);
            }
        }
    }
}

Universe1::Video::DBItem3DSpace::DBItem3DSpace(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("space", _footageName, _items)
{
}

Universe1::Video::Item3DSpace *Universe1::Video::DBItem3DSpace::add(const bool _showArrows,
                                                                    const bool _showArrowNames,
                                                                    const bool _showPlaneXY,
                                                                    const uint _sizePlanePX,
                                                                    const uint _sizePlaneMX,
                                                                    const uint _sizePlanePY,
                                                                    const uint _sizePlaneMY,
                                                                    const bool _visible)
{
    if (curSpace != nullptr)
    {
        std::cerr << "Error[" << footageName << "]: Can't add secondary 3D space!" << std::endl;
        return curSpace;
    }
    curSpace = new Item3DSpace(_showArrows,
                               _showArrowNames,
                               _showPlaneXY,
                               _sizePlanePX,
                               _sizePlaneMX,
                               _sizePlanePY,
                               _sizePlaneMY,
                               _visible,
                               nextName());
    items->push_back(curSpace);
    return curSpace;
}
