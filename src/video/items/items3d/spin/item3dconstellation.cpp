#include "item3dconstellation.h"

const std::array<QString, 4U> Universe1::Video::Item3DConstellation::spTxt = {
    "<b>Ω</b><sub>I</sub>", "<b>Ω</b><sub>J</sub>", "<b>Ω</b><sub>K</sub>", "<b>Ω</b><sub>M</sub>"};

const float Universe1::Video::Item3DConstellation::offsetAxis1 = 0.5f;
const float Universe1::Video::Item3DConstellation::offsetAxis2 = 0.05f;

const Universe1::Video::Material Universe1::Video::Item3DConstellation::matV1(QColor(255, 128, 0), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matV2(QColor(255, 192, 64), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matV3(QColor(224, 192, 128), 8, 1);

const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOI(QColor(255, 0, 0), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOJ(QColor(0, 255, 0), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOK(QColor(0, 0, 255), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOM(QColor(0, 255, 255), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOT(QColor(255, 255, 0), 8, 1);

const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOG1(QColor(255, 0, 255), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOG2(QColor(192, 0, 255), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matOG3(QColor(255, 0, 192), 8, 1);

const Universe1::Video::Material Universe1::Video::Item3DConstellation::matHR(QColor(255, 255, 160), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matH0(QColor(160, 160, 160), 16, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matHL(QColor(160, 255, 160), 8, 1);

const Universe1::Video::Material Universe1::Video::Item3DConstellation::matAngles(QColor(255, 255, 255), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matCenter(QColor(10, 150, 130), 8, 1);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matSphereIn(QColor(130, 120, 100), 256, 0.3);
const Universe1::Video::Material Universe1::Video::Item3DConstellation::matSphereOut(QColor(220, 230, 200), 64, 0.3);

Universe1::Video::Item3DConstellation::Item3DConstellation(const uint16_t _showFlags,
                                                           const Math::ConstellationType _type,
                                                           const QVector3D &_center,
                                                           const QVector3D &_normal,
                                                           const QVector3D &_arm,
                                                           const QString &_text,
                                                           const bool _visible,
                                                           const std::string &_name)
    : Item3D(_visible, _name)
    , showSpin((_showFlags & _SPIN) != 0U, _name + ".showSpin")
    , showSpinVector((_showFlags & _SPIN_VECTOR) != 0U, _name + ".showSpinVector")
    , showSpinAxis((_showFlags & _SPIN_AXIS) != 0U, _name + ".showSpinAxis")
    , showSpinArrows((_showFlags & _SPIN_ARROWS) != 0U, _name + ".showSpinArrows")
    , showSpinDots((_showFlags & _SPIN_DOTS) != 0U, _name + ".showSpinDots")
    , showSpinSphere((_showFlags & _SPIN_SPHERE) != 0U, _name + ".showSpinSphere")
    , showSpinText((_showFlags & _SPIN_TEXT) != 0U, _name + ".showSpinText")
    , showVelocity((_showFlags & _VELOCITY) != 0U, _name + ".showVelocity")
    , showVelocityText((_showFlags & _VELOCITY_TEXT) != 0U, _name + ".showVelocityText")
    , showCenter((_showFlags & _CENTER_POINT) != 0U, _name + ".showCenter")
    , showCenterText((_showFlags & _CENTER_TEXT) != 0U, _name + ".showCenterText")
    , showCenterDots((_showFlags & _CENTER_DOTS) != 0U, _name + ".showCenterDots")
    , showSphereOuter((_showFlags & _SPHERE_OUT) != 0U, _name + ".showSphereOuter")
    , showSphereInner((_showFlags & _SPHERE_IN) != 0U, _name + ".showSphereInner")
    , showAngles((_showFlags & _ANGLES) != 0U, _name + ".showAngles")
    , showAngleText((_showFlags & _ANGLES_TEXT) != 0U, _name + ".showAngleText")

    , type(_type, _name + ".type")
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")

    , phaseDeg(0.0f, _name + ".phaseDeg")
    , R1(1.0f, _name + ".R1")

    , velocityRadiusLine(Config::cfg().lineRadius, _name + ".velocityRadiusLine")
    , velocityArrowLength(Config::cfg().arrowLength, _name + ".velocityArrowLength")
    , velocityArrowRadius(Config::cfg().arrowRadius, _name + ".velocityArrowRadius")
    , velocityTextPosition(_TextAtPointTo, _name + ".velocityTextPosition")
    , velocityTextSize(1.0f, _name + ".velocityTextSize")
    , velocityTextAlign(Qt::AlignHCenter | Qt::AlignBottom, _name + ".velocityTextAlign")

    , centerRadius(Config::cfg().lineRadius * 5.0f, _name + ".centerRadius")
    , centerRadiusLine(Config::cfg().lineRadius, _name + ".centerRadiusLine")
    , centerDotsMult(Config::cfg().lineMultSpace, _name + ".centerDotsMult")
    , centerText(_text, 1.0, Qt::AlignHCenter | Qt::AlignBottom, _name + ".centerText", props)

    , qualityLatLong(Config::cfg().qualityLatLong, _name + ".qualityLatLong")
    , qualitySphere(Config::cfg().qualitySphere, _name + ".qualitySphere")
    , qualityLine(Config::cfg().qualityLine, _name + ".qualityLine")

    , materialVelocity(matV1, _name + ".materialVelocity", props, materials)
    , materialCenter(matCenter, _name + ".materialCenter", props, materials)
    , materialSphereIn(matSphereIn, _name + ".materialSphereIn", props, materials)
    , materialSphereOut(matSphereOut, _name + ".materialSphereOut", props, materials)

    , spinI(matOI, _name + ".spinI", props, materials)
    , spinJ(matOJ, _name + ".spinJ", props, materials)
    , spinK(matOK, _name + ".spinK", props, materials)
    , spinM(matOM, _name + ".spinM", props, materials)

    , angleIJ(0.3, matAngles, _name + ".angleIJ", props, materials)
    , angleJK(0.3, matAngles, _name + ".angleJK", props, materials)
    , angleKI(0.3, matAngles, _name + ".angleKI", props, materials)
    , angleIM(0.4, matAngles.darker(), _name + ".angleIM", props, materials)
    , angleJM(0.4, matAngles.darker(), _name + ".angleJM", props, materials)
    , angleKM(0.4, matAngles.darker(), _name + ".angleKI", props, materials)

{
    props.push_back(&showSpin);
    props.push_back(&showSpinVector);
    props.push_back(&showSpinAxis);
    props.push_back(&showSpinArrows);
    props.push_back(&showSpinDots);
    props.push_back(&showSpinSphere);
    props.push_back(&showSpinText);
    props.push_back(&showCenter);
    props.push_back(&showCenterText);
    props.push_back(&showCenterDots);
    props.push_back(&showSphereOuter);
    props.push_back(&showSphereInner);
    props.push_back(&showAngles);
    props.push_back(&showAngleText);
    props.push_back(&type);
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&phaseDeg);
    props.push_back(&R1);
    props.push_back(&velocityRadiusLine);
    props.push_back(&velocityArrowLength);
    props.push_back(&velocityArrowRadius);
    props.push_back(&velocityTextPosition);
    props.push_back(&velocityTextSize);
    props.push_back(&velocityTextAlign);
    props.push_back(&centerRadius);
    props.push_back(&centerRadiusLine);
    props.push_back(&centerDotsMult);
    props.push_back(&qualityLatLong);
    props.push_back(&qualitySphere);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DConstellation::addData3DCenter(std::list<Data3D> &_out,
                                                            const Shader *_shader,
                                                            const uint64_t _timeStep,
                                                            const QVector3D &_center,
                                                            const QVector3D &_normal,
                                                            const QVector3D &_arm,
                                                            const uint _quality) const
{
    if (!showCenter.getValue(_timeStep))
        return;

    const Material mc = materialCenter.getValue(_timeStep);
    const float cr = centerRadius.getValue(_timeStep);
    const float lr = centerRadiusLine.getValue(_timeStep);

    Item3DLineCross::buildData(_out, _center, _normal, _arm, Item3DLineCross::_Diagonals, cr, lr, _quality, mc);

    if (showCenterText.getValue(_timeStep))
    {
        const QString cTxt = centerText.text.getValue(_timeStep).replace("$VAL$", Config::cfg().tVec(_center));
        if (!cTxt.isEmpty())
        {
            const float ts = centerText.sizeMult.getValue(_timeStep);
            const Qt::Alignment ta = centerText.align.getValue(_timeStep);

            Item3DText::buildData(_out, _shader, cTxt, ts, ta, _center + QVector3D(0, 0, 3) * cr, mc);
        }
    }

    if (showCenterDots.getValue(_timeStep) && !qFuzzyIsNull(_center.z()))
    {
        const uint mult = centerDotsMult.getValue(_timeStep);
        Item3DLineDotsSegment::buildData(
            _out, _center, {_center.x(), _center.y(), 0.0f}, lr * 0.75f, mult, _quality, mc.darker());
    }
}

void Universe1::Video::Item3DConstellation::addData3DVelocity(std::list<Data3D> &_out,
                                                              const Shader *_shader,
                                                              const uint64_t _timeStep,
                                                              const QVector3D &_center,
                                                              const QVector3D &_normal,
                                                              const float _r1,
                                                              const uint _quality) const
{
    if (!showVelocity.getValue(_timeStep))
        return;

    const Material m = materialVelocity.getValue(_timeStep);
    const float al = velocityArrowLength.getValue(_timeStep);
    const float ar = velocityArrowRadius.getValue(_timeStep);
    const float lr = velocityRadiusLine.getValue(_timeStep);

    if (!showVelocityText.getValue(_timeStep))
    {
        Item3DLineArrow::buildData(_out, _center, _center + _normal * _r1, al, ar, lr, _quality, m);
        return;
    }

    const TextPosition tp = velocityTextPosition.getValue(_timeStep);
    const float ts = velocityTextSize.getValue(_timeStep);
    const Qt::Alignment ta = velocityTextAlign.getValue(_timeStep);
    static const QString v1name = "<b>V</b><sub>1</sub>";

    Item3DLineArrow::buildData(
        _out, _shader, _center, _center + _normal * _r1, al, ar, lr, _quality, v1name, tp, ts, ta, true, m);
}

void Universe1::Video::Item3DConstellation::addData3DSpheres(std::list<Data3D> &_out,
                                                             const uint64_t _timeStep,
                                                             const QVector3D &_center,
                                                             const QVector3D &_normal,
                                                             const QVector3D &_arm,
                                                             const float _r1,
                                                             const uint _quality) const
{
    if (showSphereInner.getValue(_timeStep))
        Item3DSphere::buildData(_out, _center, _normal, _arm, _r1, _quality, materialSphereIn.getValue(_timeStep));
    if (showSphereOuter.getValue(_timeStep))
        Item3DSphere::buildData(_out, _center, _normal, _arm, _r1, _quality, materialSphereOut.getValue(_timeStep));
}

void Universe1::Video::Item3DConstellation::addData3DSpin(std::list<Data3D> &_out,
                                                          const Shader *_shader,
                                                          const uint64_t _timeStep,
                                                          const QVector3D &_center,
                                                          const float _r1,
                                                          const uint _qll,
                                                          const uint _qs,
                                                          const uint _ql,
                                                          const QVector3D &_normal,
                                                          const QVector3D &_phase,
                                                          const std::array<bool, 6U> &_isData,
                                                          const DynamicSpinGroup &_group,
                                                          const QString &_spinName,
                                                          const Math::Helicity _helicity) const
{
    if (!_isData[0] && !_isData[1] && !_isData[3] && !_isData[4])
        return;

    const float len = _normal.length();
    if (qFuzzyIsNull(len))
        return;

    const QVector3D nn = _normal.normalized();
    const Material m1 = _group.material.getValue(_timeStep);

    if (_isData[0])  // vector
    {
        const Material mh = getHelicityMaterial(_helicity);
        addData3DSpinVector(_out, _timeStep, _center, nn, _phase, _r1, len, _ql, _group, m1, mh);

        if (_isData[1])  // axis
            addData3DSpinAxisCut(_out, _timeStep, _center, nn, _r1, len, _ql, _group, m1);

        if (_isData[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, nn, _phase, _r1, len, _ql, _group, m1, mh);

        if (_isData[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, nn, _spinName, _r1, len, _group, m1);
    }
    else if (_isData[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, nn, _r1, _ql, _group, m1);
    }

    if (_isData[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, nn, _phase, _r1, _qs, {&_group}, {m1});

    if (_isData[4])  // wire-sphere
        addData3DSpinSphere(_out, _timeStep, _center, nn, _phase, _r1, _qll, _qs, _ql, _group, m1.darker());
}

void Universe1::Video::Item3DConstellation::addData3DQuark(std::list<Data3D> &_out,
                                                           const Shader *_shader,
                                                           const uint64_t _timeStep,
                                                           const QVector3D &_center,
                                                           const float _r1,
                                                           const uint _qll,
                                                           const uint _qs,
                                                           const uint _ql,
                                                           const Math::Constellation<float> &_constellation,
                                                           const std::array<std::array<bool, 6U>, 4U> &_isData,
                                                           const uint _spinIdx1,
                                                           const uint _spinIdx2,
                                                           const Math::Helicity _helicity1,
                                                           const Math::Helicity _helicity2) const
{
    const std::array<bool, 6U> &is1 = _isData[_spinIdx1];
    const std::array<bool, 6U> &is2 = _isData[_spinIdx2];
    const DynamicSpinGroup &g1 = *spin(_spinIdx1);
    const DynamicSpinGroup &g2 = *spin(_spinIdx2);

    const Material m1 = g1.material.getValue(_timeStep);
    const Material m2 = g2.material.getValue(_timeStep);

    const QVector3D n1 = _constellation.qSpin(_spinIdx1);
    const QVector3D n2 = _constellation.qSpin(_spinIdx2);
    const QVector3D p1 = _constellation.qPhase(_spinIdx1);
    const QVector3D p2 = _constellation.qPhase(_spinIdx2);
    const QVector3D nn1 = n1.normalized();
    const QVector3D nn2 = n2.normalized();
    const float len1 = n1.length();
    const float len2 = n2.length();

    if (is1[0] && is2[0])  // vector
    {
        const Material mh1 = getHelicityMaterial(_helicity1);
        const Material mh2 = getHelicityMaterial(_helicity2);
        addData3DSpinVector(_out, _timeStep, _center, nn1, p1, _r1, len1, _ql, g1, m1, mh1);
        addData3DSpinVector(_out, _timeStep, _center, nn2, p2, _r1, len2, _ql, g2, m2, mh2);

        if (is1[1] && is2[1])  // axis
        {
            const QVector3D pb1 = _center + nn2 * (_r1 * (len2 + offsetAxis2));
            const QVector3D pe1 = _center + nn2 * (_r1 * (1.0 + offsetAxis1));
            const QVector3D pb2 = _center + nn1 * (_r1 * (len1 + offsetAxis2));
            const QVector3D pe2 = _center + nn1 * (_r1 * (1.0 + offsetAxis1));
            const float lra1 = g1.radiusLineAxis.getValue(_timeStep);
            const float lra2 = g2.radiusLineAxis.getValue(_timeStep);
            const uint mu1 = g1.multAxis.getValue(_timeStep);
            const uint mu2 = g2.multAxis.getValue(_timeStep);
            const Material m1d = m1.darker();
            const Material m2d = m2.darker();
            Item3DLineDashSegment::buildData(_out, pb1, pe1, lra1, mu1, mu1, 2U, _ql, m1d);
            Item3DLineDashSegment::buildData(_out, pb2, pe2, lra2, mu2, mu2, 2U, _ql, m2d);
        }
        else if (is1[1])
        {
            const QVector3D pb1 = _center + nn2 * (_r1 * (len2 + offsetAxis2));
            const QVector3D pe1 = _center + nn2 * (_r1 * (1.0 + offsetAxis1));
            const QVector3D pb2 = _center + nn1 * (_r1 * (len1 + offsetAxis2));
            const QVector3D pe2 = _center + nn1 * (_r1 * (1.0 + offsetAxis1));
            const float lra1 = g1.radiusLineAxis.getValue(_timeStep);
            const uint mu1 = g1.multAxis.getValue(_timeStep);
            const Material m1d = m1.darker();
            Item3DLineDashSegment::buildData(_out, pb1, pe1, lra1, mu1, mu1, 2U, _ql, m1d);
            Item3DLineDashSegment::buildData(_out, pb2, pe2, lra1, mu1, mu1, 2U, _ql, m1d);
        }
        else if (is2[1])
        {
            const QVector3D pb1 = _center + nn2 * (_r1 * (len2 + offsetAxis2));
            const QVector3D pe1 = _center + nn2 * (_r1 * (1.0 + offsetAxis1));
            const QVector3D pb2 = _center + nn1 * (_r1 * (len1 + offsetAxis2));
            const QVector3D pe2 = _center + nn1 * (_r1 * (1.0 + offsetAxis1));
            const float lra2 = g2.radiusLineAxis.getValue(_timeStep);
            const uint mu2 = g2.multAxis.getValue(_timeStep);
            const Material m2d = m2.darker();
            Item3DLineDashSegment::buildData(_out, pb1, pe1, lra2, mu2, mu2, 2U, _ql, m2d);
            Item3DLineDashSegment::buildData(_out, pb2, pe2, lra2, mu2, mu2, 2U, _ql, m2d);
        }

        if (is1[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, nn1, p1, _r1, len1, _ql, g1, m1, mh1);

        if (is2[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, nn2, p2, _r1, len2, _ql, g2, m2, mh2);

        if (is1[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, nn1, spTxt[_spinIdx1], _r1, len1, g1, m1);

        if (is2[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, nn2, spTxt[_spinIdx2], _r1, len2, g2, m2);
    }
    else if (is1[0])
    {
        const Material mh1 = getHelicityMaterial(_helicity1);
        addData3DSpinVector(_out, _timeStep, _center, nn1, p1, _r1, len1, _ql, g1, m1, mh1);

        if (is1[1] && is2[1])  // axis
        {
            const QVector3D pb1 = _center + nn1 * (_r1 * (len1 + offsetAxis2));
            const QVector3D pe1 = _center + nn1 * (_r1 * (1.0 + offsetAxis1));
            const QVector3D pb2 = _center - nn1 * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - nn1 * (_r1 * (1.0 + offsetAxis1));
            const float lra = std::max(g1.radiusLineAxis.getValue(_timeStep), g2.radiusLineAxis.getValue(_timeStep));
            const uint mu = std::max(g1.multAxis.getValue(_timeStep), g2.multAxis.getValue(_timeStep));
            const Material m1d = m1.darker();
            const Material m2d = m2.darker();

            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mu, mu, 2U, _ql, {m1d, m2d});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mu, mu, 2U, _ql, {m1d, m2d});
        }
        else if (is1[1])  // axis
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, nn1, _r1, len1, _ql, g1, m1.darker());
        }
        else if (is2[1])  // axis
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, nn1, _r1, len1, _ql, g2, m2.darker());
        }

        if (is1[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, nn1, p1, _r1, len1, _ql, g1, m1, mh1);

        if (is1[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, nn1, spTxt[_spinIdx1], _r1, len1, g1, m1);
    }
    else if (is2[0])
    {
        const Material mh2 = getHelicityMaterial(_helicity2);
        addData3DSpinVector(_out, _timeStep, _center, nn2, p2, _r1, len2, _ql, g2, m2, mh2);

        if (is1[1] && is2[1])  // axis
        {
            const QVector3D pb1 = _center + nn2 * (_r1 * (len2 + offsetAxis2));
            const QVector3D pe1 = _center + nn2 * (_r1 * (1.0 + offsetAxis1));
            const QVector3D pb2 = _center - nn2 * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - nn2 * (_r1 * (1.0 + offsetAxis1));
            const float lra = std::max(g1.radiusLineAxis.getValue(_timeStep), g2.radiusLineAxis.getValue(_timeStep));
            const uint mu = std::max(g1.multAxis.getValue(_timeStep), g2.multAxis.getValue(_timeStep));
            const Material m1d = m1.darker();
            const Material m2d = m2.darker();

            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mu, mu, 2U, _ql, {m1d, m2d});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mu, mu, 2U, _ql, {m1d, m2d});
        }
        else if (is1[1])  // axis
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, nn2, _r1, len2, _ql, g1, m1.darker());
        }
        else if (is2[1])  // axis
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, nn2, _r1, len2, _ql, g2, m2.darker());
        }

        if (is2[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, nn2, p2, _r1, len2, _ql, g2, m2, mh2);

        if (is2[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, nn2, spTxt[_spinIdx2], _r1, len2, g2, m2);
    }
    else if (is1[1] && is2[1])  // axis without main vector
    {
        const QVector3D pb = _center + nn1 * (_r1 * (1.0 + offsetAxis1));
        const QVector3D pe = _center - nn1 * (_r1 * (1.0 + offsetAxis1));
        const float lra = std::max(g1.radiusLineAxis.getValue(_timeStep), g2.radiusLineAxis.getValue(_timeStep));
        const uint mult = std::max(g1.multAxis.getValue(_timeStep), g2.multAxis.getValue(_timeStep));
        Item3DLineDashSegment::buildMultiColor(_out, pb, pe, lra, mult, mult, 2U, _ql, {m1, m2});
    }
    else if (is1[1])
    {
        addData3DSpinAxis(_out, _timeStep, _center, nn1, _r1, _ql, g1, m1);
    }
    else if (is2[1])
    {
        addData3DSpinAxis(_out, _timeStep, _center, nn2, _r1, _ql, g2, m2);
    }

    if (is1[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, nn1, p1, _r1, _qs, {&g1}, {m1});

    if (is2[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, nn2, p2, _r1, _qs, {&g2}, {m2});

    if (is1[4])  // wire-sphere
        addData3DSpinSphere(_out, _timeStep, _center, nn1, p1, _r1, _qll, _qs, _ql, g1, m1.darker());

    if (is2[4])  // wire-sphere
        addData3DSpinSphere(_out, _timeStep, _center, nn2, p2, _r1, _qll, _qs, _ql, g2, m2.darker());
}

void Universe1::Video::Item3DConstellation::addData3DPhoton(std::list<Data3D> &_out,
                                                            const Shader *_shader,
                                                            const uint64_t _timeStep,
                                                            const QVector3D &_center,
                                                            const float _r1,
                                                            const uint _qll,
                                                            const uint _qs,
                                                            const uint _ql,
                                                            const Math::Constellation<float> &_constellation,
                                                            const std::array<std::array<bool, 6U>, 4U> &_isData,
                                                            const uint _spinIdx1,
                                                            const uint _spinIdx2) const
{
    const std::array<bool, 6U> &is1 = _isData[_spinIdx1];
    const std::array<bool, 6U> &is2 = _isData[_spinIdx2];
    const DynamicSpinGroup &g1 = *spin(_spinIdx1);
    const DynamicSpinGroup &g2 = *spin(_spinIdx2);
    const QVector3D n1 = _constellation.qSpin(_spinIdx1);
    const QVector3D p1 = _constellation.qPhase(_spinIdx1);
    const QVector3D p2 = _constellation.qPhase(_spinIdx2);
    const Material m1 = g1.material.getValue(_timeStep);
    const Material m2 = g2.material.getValue(_timeStep);
    static const Material mh = getHelicityMaterial(Math::_HelicityLeft);

    if (is1[0] && is2[0])  // vector
    {
        const float tw = std::max(g1.twistStep.getValue(_timeStep), g2.twistStep.getValue(_timeStep)) * _r1;
        const float lr = std::max(g1.radiusVector.getValue(_timeStep), g2.radiusVector.getValue(_timeStep));
        Item3DLineTwist::buildData(_out, _center, n1, p1, _r1, tw, lr, _ql, {m1, m2});

        const QString &na1 = spTxt[_spinIdx1];
        const QString &na2 = spTxt[_spinIdx2];
        addData3DSpinAxisCutPhoton(_out, _timeStep, _center, n1, _r1, _ql, is1, is2, g1, g2, m1.darker(), m2.darker());
        addData3DSpinArrowsPhoton(_out, _timeStep, _center, n1, p1, p2, _r1, _ql, is1, is2, g1, g2, m1, m2, mh);
        addData3DSpinTextPhoton(_out, _shader, _timeStep, _center, n1, _r1, is1, is2, g1, g2, m1, m2, mh, na1, na2);
    }
    else if (is1[0])  // vector
    {
        addData3DSpinVector(_out, _timeStep, _center, n1, p1, _r1, 1.0f, _ql, g1, m1, mh);

        addData3DSpinAxisCutPhoton(_out, _timeStep, _center, n1, _r1, _ql, is1, is2, g1, g2, m1.darker(), m2.darker());

        if (is1[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, n1, p1, _r1, 1.0, _ql, g1, m1, mh);

        if (is1[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[_spinIdx1], _r1, 1.0, g1, m1);
    }
    else if (is2[0])  // vector
    {
        addData3DSpinVector(_out, _timeStep, _center, n1, p2, _r1, 1.0f, _ql, g2, m2, mh);

        addData3DSpinAxisCutPhoton(_out, _timeStep, _center, n1, _r1, _ql, is1, is2, g1, g2, m1.darker(), m2.darker());

        if (is2[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, n1, p2, _r1, 1.0, _ql, g2, m2, mh);

        if (is2[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[_spinIdx2], _r1, 1.0, g2, m2);
    }
    else if (is1[1] && is2[1])  // axis without main vector
    {
        addData3DSpinAxisMix(_out, _timeStep, _center, n1, _r1, _ql, g1, g2, m1, m2);
    }
    else if (is1[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, n1, _r1, _ql, g1, m1);
    }
    else if (is2[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, n1, _r1, _ql, g2, m2);
    }

    if (is1[3] && is2[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&g1, &g2}, {m1, m2});
    else if (is1[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&g1}, {m1});
    else if (is2[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p2, _r1, _qs, {&g2}, {m2});

    if (is1[4] && is2[4])  // wire-sphere
    {
        const float lr = (g1.radiusLineSphere.getValue(_timeStep) + g2.radiusLineSphere.getValue(_timeStep)) * 0.5f;
        Item3DWireSphereSlice::buildMultiColor(_out, _center, n1, p1, _r1, lr, _qll, _qs, _ql, {m1, m2});
    }
    else if (is1[4])  // wire-sphere
    {
        addData3DSpinSphere(_out, _timeStep, _center, n1, p1, _r1, _qll, _qs, _ql, g1, m1.darker());
    }
    else if (is2[4])  // wire-sphere
    {
        addData3DSpinSphere(_out, _timeStep, _center, n1, p2, _r1, _qll, _qs, _ql, g2, m2.darker());
    }
}

void Universe1::Video::Item3DConstellation::addData3DGraviton(std::list<Data3D> &_out,
                                                              const Shader *_shader,
                                                              const uint64_t _timeStep,
                                                              const QVector3D &_center,
                                                              const float _r1,
                                                              const uint _qll,
                                                              const uint _qs,
                                                              const uint _ql,
                                                              const Math::Constellation<float> &_constellation,
                                                              const std::array<std::array<bool, 6U>, 4U> &_isData) const
{
    const std::array<bool, 6U> &is1 = _isData[0];
    const std::array<bool, 6U> &is2 = _isData[1];
    const std::array<bool, 6U> &is3 = _isData[2];
    const QVector3D n1 = _constellation.qI();
    const QVector3D p1 = _constellation.qPhI();
    const QVector3D p2 = _constellation.qPhJ();
    const QVector3D p3 = _constellation.qPhK();
    const Material m1 = spinI.material.getValue(_timeStep);
    const Material m2 = spinJ.material.getValue(_timeStep);
    const Material m3 = spinK.material.getValue(_timeStep);
    static const Material mh = getHelicityMaterial(Math::_HelicityLeft);

    if (is1[0] && is2[0] && is3[0])  // vector
    {
        const float tw = (_r1 / 3.0f) *
            (spinI.twistStep.getValue(_timeStep) + spinJ.twistStep.getValue(_timeStep) +
             spinK.twistStep.getValue(_timeStep));
        const float lr = (spinI.radiusVector.getValue(_timeStep) + spinJ.radiusVector.getValue(_timeStep) +
                          spinK.radiusVector.getValue(_timeStep)) /
            3.0f;
        Item3DLineTwist::buildData(_out, _center, n1, p1, _r1, tw, lr, _ql, {m1, m2, m3});

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        if (is1[2] && is2[2] && is3[2])  // arrows
        {
            const QVector3D cc1 = _center + n1 * (_r1 * (1.0f + spinI.arrowDirOffset.getValue(_timeStep)));
            const QVector3D cc2 = _center + n1 * (_r1 * (1.0f + spinJ.arrowDirOffset.getValue(_timeStep)));
            const QVector3D cc3 = _center + n1 * (_r1 * (1.0f + spinK.arrowDirOffset.getValue(_timeStep)));
            const float ao1 = spinI.arrowArmOffset.getValue(_timeStep);
            const float al1 = spinI.arrowLength.getValue(_timeStep);
            const float ar1 = spinI.arrowRadius.getValue(_timeStep);
            const float ao2 = spinJ.arrowArmOffset.getValue(_timeStep);
            const float al2 = spinJ.arrowLength.getValue(_timeStep);
            const float ar2 = spinJ.arrowRadius.getValue(_timeStep);
            const float ao3 = spinJ.arrowArmOffset.getValue(_timeStep);
            const float al3 = spinJ.arrowLength.getValue(_timeStep);
            const float ar3 = spinJ.arrowRadius.getValue(_timeStep);
            const QVector3D _p1r1 = QQuaternion::fromAxisAndAngle(n1, 120).rotatedVector(p1).normalized();
            const QVector3D _p1r2 = QQuaternion::fromAxisAndAngle(n1, 240).rotatedVector(p1).normalized();
            Item3DArcArrow::buildData(_out, cc1, n1, p1, ao1, al1, ar1, _ql, m1, m1.darker());
            Item3DArcArrow::buildData(_out, cc2, n1, _p1r1, ao2, al2, ar2, _ql, m2, m2.darker());
            Item3DArcArrow::buildData(_out, cc3, n1, _p1r2, ao3, al3, ar3, _ql, m3, m3.darker());
        }
        else if (is1[2] && is2[2])  // arrows
        {
            addData3DSpinArrowsPhoton(
                _out, _timeStep, _center, n1, p1, p2, _r1, _ql, is1, is2, spinI, spinJ, m1, m2, mh);
        }
        else if (is1[2] && is3[2])  // arrows
        {
            addData3DSpinArrowsPhoton(
                _out, _timeStep, _center, n1, p3, p1, _r1, _ql, is3, is1, spinK, spinI, m3, m1, mh);
        }
        else if (is2[2] && is3[2])  // arrows
        {
            addData3DSpinArrowsPhoton(
                _out, _timeStep, _center, n1, p2, p3, _r1, _ql, is2, is3, spinJ, spinK, m2, m3, mh);
        }
        else if (is1[2])  // arrows
        {
            addData3DSpinArrows(_out, _timeStep, _center, n1, p1, _r1, 1.0, _ql, spinI, m1, mh);
        }
        else if (is2[2])  // arrows
        {
            addData3DSpinArrows(_out, _timeStep, _center, n1, p2, _r1, 1.0, _ql, spinJ, m2, mh);
        }
        else if (is3[2])  // arrows
        {
            addData3DSpinArrows(_out, _timeStep, _center, n1, p3, _r1, 1.0, _ql, spinK, m3, mh);
        }

        if (is1[5] && is2[5] && is3[5])  // text
        {
            const TextPosition tp1 = spinI.textPosition.getValue(_timeStep);
            // const TextPosition tp2 = spinJ.textPosition.getValue(_timeStep);
            // const TextPosition tp3 = spinK.textPosition.getValue(_timeStep);
            const float ts = (spinI.textSize.getValue(_timeStep) + spinJ.textSize.getValue(_timeStep) +
                              spinK.textSize.getValue(_timeStep)) /
                3.0f;
            const Qt::Alignment ta = spinI.textAlign.getValue(_timeStep);
            const QString sn = spTxt[0] + "<br/>" + spTxt[1] + "<br/>" + spTxt[2];
            switch (tp1)
            {
            case _TextAtPointFrom: Item3DText::buildData(_out, _shader, sn, ts, ta, _center + n1 * 0.1f, mh); break;
            case _TextMiddle: Item3DText::buildData(_out, _shader, sn, ts, ta, _center + n1 * (_r1 * 0.5f), mh); break;
            case _TextAtPointTo:
                Item3DText::buildData(_out, _shader, sn, ts, ta, _center + n1 * (_r1 * 0.9f), mh);
                break;
            }
        }
        else if (is1[5] && is2[5])  // text
        {
            addData3DSpinTextPhoton(
                _out, _shader, _timeStep, _center, n1, _r1, is1, is2, spinI, spinJ, m1, m2, mh, spTxt[0], spTxt[1]);
        }
        else if (is1[5] && is3[5])  // text
        {
            addData3DSpinTextPhoton(
                _out, _shader, _timeStep, _center, n1, _r1, is3, is1, spinK, spinI, m3, m1, mh, spTxt[2], spTxt[0]);
        }
        else if (is2[5] && is3[5])  // text
        {
            addData3DSpinTextPhoton(
                _out, _shader, _timeStep, _center, n1, _r1, is2, is3, spinJ, spinK, m2, m3, mh, spTxt[1], spTxt[2]);
        }
        else if (is1[5])  // text
        {
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[0], _r1, 1.0, spinI, m1);
        }
        else if (is2[5])  // text
        {
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[1], _r1, 1.0, spinJ, m2);
        }
        else if (is3[5])  // text
        {
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[2], _r1, 1.0, spinK, m3);
        }
    }
    else if (is1[0] && is2[0])  // vector
    {
        const float tw = std::max(spinI.twistStep.getValue(_timeStep), spinJ.twistStep.getValue(_timeStep)) * _r1;
        const float lr = std::max(spinI.radiusVector.getValue(_timeStep), spinJ.radiusVector.getValue(_timeStep));
        Item3DLineTwist::buildData(_out, _center, n1, p1, _r1, tw, lr, _ql, {m1, m2});

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        addData3DSpinArrowsPhoton(_out, _timeStep, _center, n1, p1, p2, _r1, _ql, is1, is2, spinI, spinJ, m1, m2, mh);

        addData3DSpinTextPhoton(
            _out, _shader, _timeStep, _center, n1, _r1, is1, is2, spinI, spinJ, m1, m2, mh, spTxt[0], spTxt[1]);
    }
    else if (is1[0] && is3[0])  // vector
    {
        const float tw = std::max(spinI.twistStep.getValue(_timeStep), spinK.twistStep.getValue(_timeStep)) * _r1;
        const float lr = std::max(spinI.radiusVector.getValue(_timeStep), spinK.radiusVector.getValue(_timeStep));
        Item3DLineTwist::buildData(_out, _center, n1, p1, _r1, tw, lr, _ql, {m3, m1});

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        addData3DSpinArrowsPhoton(_out, _timeStep, _center, n1, p3, p1, _r1, _ql, is3, is1, spinK, spinI, m3, m1, mh);

        addData3DSpinTextPhoton(
            _out, _shader, _timeStep, _center, n1, _r1, is3, is1, spinK, spinI, m3, m1, mh, spTxt[2], spTxt[0]);
    }
    else if (is2[0] && is3[0])  // vector
    {
        const float tw = std::max(spinJ.twistStep.getValue(_timeStep), spinK.twistStep.getValue(_timeStep)) * _r1;
        const float lr = std::max(spinJ.radiusVector.getValue(_timeStep), spinK.radiusVector.getValue(_timeStep));
        Item3DLineTwist::buildData(_out, _center, n1, p1, _r1, tw, lr, _ql, {m2, m3});

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        addData3DSpinArrowsPhoton(_out, _timeStep, _center, n1, p2, p3, _r1, _ql, is2, is3, spinJ, spinK, m2, m3, mh);

        addData3DSpinTextPhoton(
            _out, _shader, _timeStep, _center, n1, _r1, is2, is3, spinJ, spinK, m2, m3, mh, spTxt[1], spTxt[2]);
    }
    else if (is1[0])  // vector
    {
        addData3DSpinVector(_out, _timeStep, _center, n1, p1, _r1, 1.0f, _ql, spinI, m1, mh);

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        if (is1[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, n1, p1, _r1, 1.0, _ql, spinI, m1, mh);

        if (is1[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[0], _r1, 1.0, spinI, m1);
    }
    else if (is2[0])  // vector
    {
        addData3DSpinVector(_out, _timeStep, _center, n1, p1, _r1, 1.0f, _ql, spinJ, m2, mh);

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        if (is2[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, n1, p2, _r1, 1.0, _ql, spinJ, m2, mh);

        if (is2[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[1], _r1, 1.0, spinJ, m2);
    }
    else if (is3[0])  // vector
    {
        addData3DSpinVector(_out, _timeStep, _center, n1, p1, _r1, 1.0f, _ql, spinK, m3, mh);

        addData3DSpinAxisCutGraviton(
            _out, _timeStep, _center, n1, _r1, _ql, is1, is2, is3, m1.darker(), m2.darker(), m3.darker());

        if (is3[2])  // arrows
            addData3DSpinArrows(_out, _timeStep, _center, n1, p3, _r1, 1.0, _ql, spinK, m3, mh);

        if (is3[5])  // text
            addData3DSpinText(_out, _shader, _timeStep, _center, n1, spTxt[2], _r1, 1.0, spinK, m3);
    }
    else if (is1[1] && is2[1] && is3[1])  // axis without main vector
    {
        const QVector3D pb = _center + n1 * (_r1 * (1.0 + offsetAxis1));
        const QVector3D pe = _center - n1 * (_r1 * (1.0 + offsetAxis1));
        const float lra = (spinI.radiusLineAxis.getValue(_timeStep) + spinJ.radiusLineAxis.getValue(_timeStep) +
                           spinK.radiusLineAxis.getValue(_timeStep)) /
            3.0f;
        const uint mult = (spinI.multAxis.getValue(_timeStep) + spinJ.multAxis.getValue(_timeStep) +
                           spinK.multAxis.getValue(_timeStep)) /
            3U;
        Item3DLineDashSegment::buildMultiColor(_out, pb, pe, lra, mult, mult, 2U, _ql, {m1, m2, m3});
    }
    else if (is1[1] && is2[1])  // axis without main vector
    {
        addData3DSpinAxisMix(_out, _timeStep, _center, n1, _r1, _ql, spinI, spinJ, m1, m2);
    }
    else if (is1[1] && is3[1])  // axis without main vector
    {
        addData3DSpinAxisMix(_out, _timeStep, _center, n1, _r1, _ql, spinK, spinI, m3, m1);
    }
    else if (is2[1] && is3[1])  // axis without main vector
    {
        addData3DSpinAxisMix(_out, _timeStep, _center, n1, _r1, _ql, spinJ, spinK, m2, m3);
    }
    else if (is1[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, n1, _r1, _ql, spinI, m1);
    }
    else if (is2[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, n1, _r1, _ql, spinJ, m2);
    }
    else if (is3[1])  // axis without main vector
    {
        addData3DSpinAxis(_out, _timeStep, _center, n1, _r1, _ql, spinK, m3);
    }

    if (is1[3] && is2[3] && is3[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&spinI, &spinJ, &spinK}, {m1, m2, m3});
    else if (is1[3] && is2[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&spinI, &spinJ}, {m1, m2});
    else if (is1[3] && is3[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&spinK, &spinI}, {m3, m1});
    else if (is2[3] && is3[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&spinJ, &spinK}, {m2, m3});
    else if (is1[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p1, _r1, _qs, {&spinI}, {m1});
    else if (is2[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p2, _r1, _qs, {&spinJ}, {m2});
    else if (is3[3])  // dots
        addData3DSpinDots(_out, _timeStep, _center, n1, p3, _r1, _qs, {&spinK}, {m3});

    if (is1[4] && is2[4] && is3[4])  // wire-sphere
    {
        const float lr = (spinI.radiusLineSphere.getValue(_timeStep) + spinJ.radiusLineSphere.getValue(_timeStep) +
                          spinK.radiusLineSphere.getValue(_timeStep)) /
            3.0;
        Item3DWireSphereSlice::buildMultiColor(
            _out, _center, n1, p1, _r1, lr, _qll, _qs, _ql, {m1.darker(), m2.darker(), m3.darker()});
    }
    else if (is1[4] && is2[4])  // wire-sphere
    {
        const float lr =
            (spinI.radiusLineSphere.getValue(_timeStep) + spinJ.radiusLineSphere.getValue(_timeStep)) * 0.5;
        Item3DWireSphereSlice::buildMultiColor(
            _out, _center, n1, p1, _r1, lr, _qll, _qs, _ql, {m1.darker(), m2.darker()});
    }
    else if (is1[4] && is3[4])  // wire-sphere
    {
        const float lr =
            (spinI.radiusLineSphere.getValue(_timeStep) + spinK.radiusLineSphere.getValue(_timeStep)) * 0.5;
        Item3DWireSphereSlice::buildMultiColor(
            _out, _center, n1, p1, _r1, lr, _qll, _qs, _ql, {m1.darker(), m3.darker()});
    }
    else if (is2[4] && is3[4])  // wire-sphere
    {
        const float lr =
            (spinI.radiusLineSphere.getValue(_timeStep) + spinJ.radiusLineSphere.getValue(_timeStep)) * 0.5;
        Item3DWireSphereSlice::buildMultiColor(
            _out, _center, n1, p1, _r1, lr, _qll, _qs, _ql, {m2.darker(), m3.darker()});
    }
    else if (is1[4])  // wire-sphere
    {
        addData3DSpinSphere(_out, _timeStep, _center, n1, p1, _r1, _qll, _qs, _ql, spinI, m1.darker());
    }
    else if (is2[4])  // wire-sphere
    {
        addData3DSpinSphere(_out, _timeStep, _center, n1, p2, _r1, _qll, _qs, _ql, spinJ, m2.darker());
    }
    else if (is3[4])  // wire-sphere
    {
        addData3DSpinSphere(_out, _timeStep, _center, n1, p2, _r1, _qll, _qs, _ql, spinK, m3.darker());
    }
}

void Universe1::Video::Item3DConstellation::addData3D(std::list<Data3D> &_out,
                                                      const Shader *_shader,
                                                      const uint64_t _timeStep) const
{
    using namespace Math;

    const QVector3D c = center.getValue(_timeStep);
    const QVector3D n = normal.getValue(_timeStep).normalized();
    const QVector3D a = perpendicularArm(arm.getValue(_timeStep), n);
    const float r1 = R1.getValue(_timeStep);
    const uint qll = qualityLatLong.getValue(_timeStep);
    const uint qs = qualitySphere.getValue(_timeStep);
    const uint ql = qualityLine.getValue(_timeStep);

    addData3DCenter(_out, _shader, _timeStep, c, n, a, ql);
    addData3DVelocity(_out, _shader, _timeStep, c, n, r1, ql);

    if (!showSpin.getValue(_timeStep))
    {
        addData3DSpheres(_out, _timeStep, c, n, a, r1, qs);
        return;
    }

    const ConstellationType ct = type.getValue(_timeStep);
    const std::array<bool, 4U> isSpin = {spinI.show.getValue(_timeStep),
                                         spinJ.show.getValue(_timeStep),
                                         spinK.show.getValue(_timeStep),
                                         spinM.show.getValue(_timeStep) && Constellation<float>::hasMass(ct)};
    uint8_t cntSpin = 0U;
    for (uint8_t i = 0U; i < 4U; ++i)
        if (isSpin[i])
            ++cntSpin;

    if (cntSpin == 0U || ct == _ConstellationInvalid)
    {
        addData3DSpheres(_out, _timeStep, c, n, a, r1, qs);
        return;
    }

    const float phase = phaseDeg.getValue(_timeStep);
    const Math::Constellation<float> con(ct, n, a, phase);

    const std::array<bool, 6U> isRoot = {showSpinVector.getValue(_timeStep),
                                         showSpinAxis.getValue(_timeStep),
                                         showSpinArrows.getValue(_timeStep),
                                         showSpinDots.getValue(_timeStep),
                                         showSpinSphere.getValue(_timeStep),
                                         showSpinText.getValue(_timeStep)};

    const std::array<std::array<bool, 6U>, 4U> is = {
        {{{isSpin[0] && isRoot[0] && spinI.showVector.getValue(_timeStep),
           isSpin[0] && isRoot[1] && spinI.showAxis.getValue(_timeStep),
           isSpin[0] && isRoot[2] && spinI.showArrows.getValue(_timeStep),
           isSpin[0] && isRoot[3] && spinI.showDots.getValue(_timeStep),
           isSpin[0] && isRoot[4] && spinI.showSphere.getValue(_timeStep),
           isSpin[0] && isRoot[5] && spinI.showText.getValue(_timeStep)}},
         {{isSpin[1] && isRoot[0] && spinJ.showVector.getValue(_timeStep),
           isSpin[1] && isRoot[1] && spinJ.showAxis.getValue(_timeStep),
           isSpin[1] && isRoot[2] && spinJ.showArrows.getValue(_timeStep),
           isSpin[1] && isRoot[3] && spinJ.showDots.getValue(_timeStep),
           isSpin[1] && isRoot[4] && spinJ.showSphere.getValue(_timeStep),
           isSpin[1] && isRoot[5] && spinJ.showText.getValue(_timeStep)}},
         {{isSpin[2] && isRoot[0] && spinK.showVector.getValue(_timeStep),
           isSpin[2] && isRoot[1] && spinK.showAxis.getValue(_timeStep),
           isSpin[2] && isRoot[2] && spinK.showArrows.getValue(_timeStep),
           isSpin[2] && isRoot[3] && spinK.showDots.getValue(_timeStep),
           isSpin[2] && isRoot[4] && spinK.showSphere.getValue(_timeStep),
           isSpin[2] && isRoot[5] && spinK.showText.getValue(_timeStep)}},
         {{isSpin[3] && isRoot[0] && spinM.showVector.getValue(_timeStep),
           isSpin[3] && isRoot[1] && spinM.showAxis.getValue(_timeStep),
           isSpin[3] && isRoot[2] && spinM.showArrows.getValue(_timeStep),
           isSpin[3] && isRoot[3] && spinM.showDots.getValue(_timeStep),
           isSpin[3] && isRoot[4] && spinM.showSphere.getValue(_timeStep),
           isSpin[3] && isRoot[5] && spinM.showText.getValue(_timeStep)}}}};

    const bool sa = showAngles.getValue(_timeStep);
    const bool st = showAngleText.getValue(_timeStep);
    static const QString elAng = QString("%1°").arg(Vec3F::unitX().angleDeg({-1, -1, -1}), 0, 'f', 3);

    static const std::array<Math::Helicity, 4U> hER = {_HelicityRight, _HelicityRight, _HelicityRight, _HelicityLeft};
    static const std::array<Math::Helicity, 4U> hEL = {_HelicityLeft, _HelicityLeft, _HelicityLeft, _HelicityRight};
    static const std::array<Math::Helicity, 4U> hQIR = {_HelicityZero, _HelicityRight, _HelicityRight, _HelicityLeft};
    static const std::array<Math::Helicity, 4U> hQJR = {_HelicityRight, _HelicityZero, _HelicityRight, _HelicityLeft};
    static const std::array<Math::Helicity, 4U> hQKR = {_HelicityRight, _HelicityRight, _HelicityZero, _HelicityLeft};
    static const std::array<Math::Helicity, 4U> hQIL = {_HelicityZero, _HelicityLeft, _HelicityLeft, _HelicityRight};
    static const std::array<Math::Helicity, 4U> hQJL = {_HelicityLeft, _HelicityZero, _HelicityLeft, _HelicityRight};
    static const std::array<Math::Helicity, 4U> hQKL = {_HelicityLeft, _HelicityLeft, _HelicityZero, _HelicityRight};

    switch (ct)
    {
    case _ConstellationInvalid: return;

    case _Neutrino:
        addData3DSpin(_out, _shader, _timeStep, c, r1, qll, qs, ql, con.qI(), con.qPhI(), is[0], spinI, spTxt[0]);
        addData3DSpin(_out, _shader, _timeStep, c, r1, qll, qs, ql, con.qJ(), con.qPhJ(), is[1], spinJ, spTxt[1]);
        addData3DSpin(_out, _shader, _timeStep, c, r1, qll, qs, ql, con.qK(), con.qPhK(), is[2], spinK, spTxt[2]);
        if (sa)
            addData3DAnglesIJK(_out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "120°", "120°");
        break;

    case _ElectronRight:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hER);
        if (sa)
            addData3DAngles(_out, _shader, _timeStep, c, con, is, st, qs, ql, "90°", "90°", "90°", elAng, elAng, elAng);
        break;

    case _ElectronLeft:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hEL);
        if (sa)
            addData3DAngles(_out, _shader, _timeStep, c, con, is, st, qs, ql, "90°", "90°", "90°", elAng, elAng, elAng);
        break;

    case _QuarkUpIRight:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQIR);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "60°", "120°", "90°", "135°", "135°");
        break;

    case _QuarkUpJRight:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQJR);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "120°", "60°", "135°", "90°", "135°");
        break;

    case _QuarkUpKRight:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQKR);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "120°", "60°", "135°", "135°", "90°");
        break;

    case _QuarkUpILeft:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQIL);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "60°", "120°", "90°", "135°", "135°");
        break;

    case _QuarkUpJLeft:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQJL);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "120°", "60°", "135°", "90°", "135°");
        break;

    case _QuarkUpKLeft:
        addData3DSpinAll(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, hQKL);
        if (sa)
            addData3DAngles(
                _out, _shader, _timeStep, c, con, is, st, qs, ql, "120°", "120°", "60°", "135°", "135°", "90°");
        break;

    case _QuarkDownIRight:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 0, 4, _HelicityRight, _HelicityLeft);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 2, _HelicityZero, _HelicityZero);

        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, con.qI(), con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, con.qJ(), con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }

        break;
    case _QuarkDownJRight:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 4, _HelicityRight, _HelicityLeft);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 2, 0, _HelicityZero, _HelicityZero);

        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, con.qJ(), con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, con.qK(), con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }

        break;
    case _QuarkDownKRight:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 2, 4, _HelicityRight, _HelicityLeft);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 2, _HelicityZero, _HelicityZero);

        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, con.qK(), con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, con.qJ(), con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }
        break;

    case _QuarkDownILeft:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 0, 4, _HelicityLeft, _HelicityRight);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 2, _HelicityZero, _HelicityZero);

        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, -con.qI(), con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, -con.qJ(), con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }
        break;

    case _QuarkDownJLeft:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 4, _HelicityLeft, _HelicityRight);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 2, 0, _HelicityZero, _HelicityZero);

        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, -con.qJ(), con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, -con.qK(), con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }
        break;

    case _QuarkDownKLeft:
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 2, 4, _HelicityLeft, _HelicityRight);
        addData3DQuark(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 2, _HelicityZero, _HelicityZero);
        if (sa)
        {
            if ((is[0][0] || is[0][1]) && (is[1][0] || is[1][1]))
                addData3DAngle(_out, _shader, _timeStep, "180°", c, -con.qK(), con.qI(), con.qJ(), angleIJ, qs, ql, st);

            if ((is[1][0] || is[1][1]) && (is[2][0] || is[2][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);

            if ((is[2][0] || is[2][1]) && (is[0][0] || is[0][1]))
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);

            if (is[3][0] || is[3][1])
            {
                if ((is[0][0] || is[0][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qM(), angleIM, qs, ql, st);

                if ((is[1][0] || is[1][1]))
                    addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qM(), angleJM, qs, ql, st);

                if ((is[2][0] || is[2][1]))
                    addData3DAngle(
                        _out, _shader, _timeStep, "180°", c, -con.qJ(), con.qK(), con.qM(), angleKM, qs, ql, st);
            }
        }
        break;

    case _PhotonI:
        addData3DSpin(
            _out, _shader, _timeStep, c, r1, qll, qs, ql, con.qI(), con.qPhI(), is[0], spinI, spTxt[0], _HelicityRight);

        addData3DPhoton(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 1, 2);

        if (sa)
        {
            if (is[0][0] || is[0][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);
            else if (is[2][0] || is[2][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);
        }
        break;

    case _PhotonJ:
        addData3DSpin(
            _out, _shader, _timeStep, c, r1, qll, qs, ql, con.qJ(), con.qPhJ(), is[1], spinJ, spTxt[1], _HelicityRight);
        addData3DPhoton(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 2, 0);

        if (sa)
        {
            if (is[0][0] || is[0][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qI(), con.qJ(), angleIJ, qs, ql, st);
            else if (is[1][0] || is[1][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);
        }
        break;

    case _PhotonK:
        addData3DSpin(
            _out, _shader, _timeStep, c, r1, qll, qs, ql, con.qK(), con.qPhK(), is[2], spinK, spTxt[2], _HelicityRight);
        addData3DPhoton(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is, 0, 1);

        if (sa)
        {
            if (is[1][0] || is[1][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qJ(), con.qK(), angleJK, qs, ql, st);
            else if (is[2][0] || is[2][1])
                addData3DAngle(_out, _shader, _timeStep, "90°", c, con.qK(), con.qI(), angleKI, qs, ql, st);
        }
        break;

    case _Graviton: addData3DGraviton(_out, _shader, _timeStep, c, r1, qll, qs, ql, con, is); break;
    }

    addData3DSpheres(_out, _timeStep, c, n, a, r1, qs);
}

Universe1::Video::DBItem3DConstellation::DBItem3DConstellation(const std::string &_footageName,
                                                               std::list<Item3D *> *_items)
    : DBItems3D("constellation", _footageName, _items)
{
}

Universe1::Video::Item3DConstellation *Universe1::Video::DBItem3DConstellation::add(const uint16_t _showFlags,
                                                                                    const Math::ConstellationType _type,
                                                                                    const QVector3D &_center,
                                                                                    const QVector3D &_normal,
                                                                                    const QVector3D &_arm,
                                                                                    const bool _visible,
                                                                                    const QString &_text)
{
    Item3DConstellation *result =
        new Item3DConstellation(_showFlags, _type, _center, _normal, _arm, _text, _visible, nextName());
    items->push_back(result);
    return result;
}
