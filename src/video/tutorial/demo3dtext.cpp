#include "demo3dtext.h"

Universe1::Video::Tutorial::Demo3DText::Demo3DText(const uint64_t _footageId,
                                                   const uint64_t _footageStartTime,
                                                   const std::pair<QVector3D, QVector3D> &_lastCamera)
    : Footage("Demo3DText", _footageId, _footageStartTime, _lastCamera)
{
    typedef const uint64_t TT;
    static const QVector3D pb1 = {2, 0, 3};
    static const QVector3D pb2 = {-2, 0, 3};

    TT t1 =
        subs.add({200, 400}, tr("Hi. This is demo for 3D text."), tr("Hi. This is demo for three dimensional text."));
    TT t2 =
        subs.add({t1, 400},
                 tr("We have two kinds of 3D text.<br/>Text frozen in position and text following camera."),
                 tr("We have two kinds of three dimensional text. Text frozen in position and text following camera."));

    TT t3 = subs.add({t2, 10000}, tr("Test alignment."));
    duration = subs.add({t3, 10000}, tr("Test properties."));

    space.add();

    cross.add(pb1, Item3DLineCross::_Axis, 0.5, Material(Qt::white));
    cross.add(pb2, Item3DLineCross::_Axis, 0.5, Material(Qt::white));

    Item3DTextValue<float> *obj1 = text3D.addT(
        0.0f, mkTab({tr("Following camera"), tr("Elapsed: $VAL$")}, "left", true, 1), pb1, Material(Qt::yellow));

    Item3DTextValue<uint> *obj2 = text3D.addT(
        0U, mkTab({tr("Frozen position"), tr("Frame time: $VAL$")}, "left", true, 1), pb2, nx, nz, Material(Qt::cyan));

    obj1->value.add(duration, 1.0f);
    obj2->value.add(duration, duration);

    obj1->material.add(t1, Material(Qt::red));
    obj1->material.add(t2, Material(Qt::yellow));

    obj2->material.add(t1, Material(Qt::blue));
    obj2->material.add(t2, Material(Qt::cyan));

    Item2D *txtAlig = text2D.addHidden("");
    txtAlig->addOn(t2);

    uint64_t tt = t2;
    for (const Qt::Alignment a : Item2D::supportedAlignments)
    {
        txtAlig->text.text.add(tt, tr("Alignment: %1").arg(Item2D::alignToText(a)));
        obj1->text.align.add(tt, a);
        obj2->text.align.add(tt, a);
        tt += 1000U;
    }
    txtAlig->text.text.add(tt, tr("Alignment: %1").arg(Item2D::alignToText(Qt::AlignCenter)));
    obj1->text.align.add(tt, Qt::AlignCenter);
    obj2->text.align.add(tt, Qt::AlignCenter);

    obj1->text.sizeMult.addSame(t3);
    obj2->text.sizeMult.addSame(t3);
    obj1->text.sizeMult.addLoop(t3, duration, 0.5);
    obj2->text.sizeMult.addLoop(t3, duration, 0.75);

    obj2->normalRow.addArcAccel(t3, t3 + 1000, {}, nz, 360.0f);

    camera.lookAt = (pb1 + pb2) * 0.5f;
    camera.lookAt.addArcAccel(t1, t2, pb1, ny, 360.0f);

    camera.pos = (pb1 + pb2) * 0.5f - ny * 5.0f + nx * 0.1f;
    camera.pos.addArcAccel(t1, {}, nz, 360.0f);
}
