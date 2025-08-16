/*!
 * \file src/Items/BodyParts/Head/itemhead.cpp
 * \brief Dynamic Head video item
 */

#include "itemeye.h"

#include "../../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

void ItemEye::createDataImpl(std::list<OpenGL::Data3D *> &_out, const size_t _timeStep) const
{
    createEye(_out, eyeBall.value(_timeStep, valueOrientation(_timeStep)), alpha.value(_timeStep));
}

void ItemEye::createEye(std::list<OpenGL::Data3D *> &_data,
                        const Props::ItemGroupEyeBall::Data &_eye,
                        const uint8_t _alpha)
{
    if (!Math::isPositive(_eye.radius) || _alpha == 0U)
        return;

    const float a1 = std::min(_eye.anglePupil, _eye.angleIris);
    const float a2 = std::max(_eye.anglePupil, _eye.angleIris);

    if (Math::isPositive(a1))
    {
        if (!Math::isPositive(_eye.offsetPupil))
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
                _eye.orientation, 0.0f, 2.0f * M_PI, 0.0f, a1, _eye.radius, _eye.quality, _eye.materialPupil, _alpha));
        }
        else
        {
            const float tmp1 = std::sin(a1) * _eye.radius;
            const float tmp2 = std::cos(a1) * _eye.radius;
            const float tmp3 = _eye.offsetPupil * _eye.radius;
            const float tmp4 = std::max(0.0f, tmp2 - tmp3);
            const float tmp5 = std::sqrt(tmp1 * tmp1 + tmp4 * tmp4);
            const float tmp6 = Math::isNull(tmp4) ? M_PI_2 : std::atan2(tmp1, tmp4);
            _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
                _eye.orientation.moved(_eye.orientation.center + _eye.orientation.normal1 * tmp3),
                0.0f,
                2.0f * M_PI,
                0.0f,
                tmp6,
                tmp5,
                _eye.quality,
                _eye.materialPupil,
                _alpha));
        }
    }

    if (Math::isMoreNotEqual(a2, a1))
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
            _eye.orientation, 0.0f, 2.0f * M_PI, a1, a2, _eye.radius, _eye.quality, _eye.materialIris, _alpha));
    }

    _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
        _eye.orientation, 0.0f, 2.0f * M_PI, a2, M_PI, _eye.radius, _eye.quality, _eye.materialSclera, _alpha));

    if (!Math::isPositive(_eye.offsetLid))
        return;

    const float olr = _eye.radius + _eye.radius * _eye.offsetLid;

    Math::OrientF ol = _eye.orientation;
    ol.normal1 = Math::Vec3F::cross(_eye.orientation.normal1, _eye.orientation.normal2).normalized();
    ol.normal2 = _eye.orientation.normal1;
    ol.normal3 = Math::Vec3F::cross(ol.normal1, ol.normal2).normalized();

    const float al1 = std::max(0.0f, float(M_PI) - _eye.angleLidUp);
    const float al2 = std::min(2.0f * float(M_PI), float(M_PI) + _eye.angleLidBottom);

    _data.push_back(
        OpenGL::Data3DMaterialNormal::sphereArc(ol, al1, al2, 0.0f, M_PI, olr, _eye.quality, _eye.materialLid, _alpha));

    const float oer = _eye.radius * std::max(_eye.offsetLid, _eye.offsetLidEdge);

    Math::OrientF oe = _eye.orientation;
    oe.normal1 = _eye.orientation.normal2.rotated(ol.normal1, al1).normalized();
    oe.normal2 = ol.normal1;
    oe.normal3 = Math::Vec3F::cross(oe.normal1, oe.normal2).normalized();
    _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
        oe, _eye.radius * M_PI, _eye.radius, oer, oer, _eye.quality, _eye.quality, _eye.materialLidEdge, _alpha));

    oe.normal1 = _eye.orientation.normal2.rotated(ol.normal1, al2).normalized();
    oe.normal2 = ol.normal1;
    oe.normal3 = Math::Vec3F::cross(oe.normal1, oe.normal2).normalized();

    _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
        oe, _eye.radius * M_PI, _eye.radius, oer, oer, _eye.quality, _eye.quality, _eye.materialLidEdge, _alpha));
}

}  // namespace Items
}  // namespace U1
