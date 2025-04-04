/*!
 * \file src/Items/Triangle/itemtriangle.cpp
 * \brief Dynamic triangle video item
 */

#include "itemtriangle.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"
#include "../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

ItemTriangle::ItemTriangle(const std::string &_name,
                           const Math::Vec3F &_point1,
                           const Math::Vec3F &_point2,
                           const Math::Vec3F &_point3,
                           const Triangle::ShowTriangleType _show,
                           const bool _showWire,
                           const Math::MaterialRGB &_materialFront,
                           const Math::MaterialRGB &_materialBack,
                           const Math::MaterialRGBA &_material1Front,
                           const Math::MaterialRGBA &_material2Front,
                           const Math::MaterialRGBA &_material3Front,
                           const Math::MaterialRGBA &_material1Back,
                           const Math::MaterialRGBA &_material2Back,
                           const Math::MaterialRGBA &_material3Back,
                           const Math::MaterialRGBA &_materialWire,
                           const float _radiusWire,
                           const size_t _qualityWire,
                           const uint8_t _alpha,
                           const bool _visible)
    : Item3D(_name, _visible, _alpha)
    , point1("point1", _point1)
    , point2("point2", _point2)
    , point3("point3", _point3)
    , show("show", QMetaEnum::fromType<Triangle::ShowTriangleType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , material1Front("material1Front", _material1Front)
    , material2Front("material2Front", _material2Front)
    , material3Front("material3Front", _material3Front)
    , material1Back("material1Back", _material1Back)
    , material2Back("material2Back", _material2Back)
    , material3Back("material3Back", _material3Back)
    , showWire("showWire", _showWire)
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , qualityWire("qualityWire", _qualityWire)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&point1);
    addProperty(&point2);
    addProperty(&point3);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&material1Front);
    addProperty(&material2Front);
    addProperty(&material3Front);
    addProperty(&material1Back);
    addProperty(&material2Back);
    addProperty(&material3Back);
    addProperty(&showWire);
    addProperty(&radiusWire);
    addProperty(&qualityWire);
    addProperty(&materialWire);
}

void ItemTriangle::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const Math::Vec3F p1 = point1.value(_timeStep);
    const Math::Vec3F p2 = point2.value(_timeStep);
    const Math::Vec3F p3 = point3.value(_timeStep);

    const Triangle::ShowTriangleType st = show.valueEnum<Triangle::ShowTriangleType>(_timeStep);
    switch (st)
    {
    case Triangle::TriangleFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialBase::triangle(p1, p2, p3, materialFront.value(_timeStep), a));
            _data.push_back(OpenGL::Data3DMaterialBase::triangle(p1, p3, p2, materialBack.value(_timeStep), a));
        }
    }
    break;

    case Triangle::TriangleFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::triangle(p1, p2, p3, materialFront.value(_timeStep), a));
    }
    break;

    case Triangle::TriangleBack: {
        const uint8_t a = alpha.value(_timeStep);
        _data.push_back(OpenGL::Data3DMaterialBase::triangle(p1, p3, p2, materialBack.value(_timeStep), a));
    }
    break;

    case Triangle::TriangleVertexFrontBack: {
        _data.push_back(OpenGL::Data3DMaterialsAlpha::triangle(p1,
                                                               p2,
                                                               p3,
                                                               material1Front.value(_timeStep),
                                                               material2Front.value(_timeStep),
                                                               material3Front.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::triangle(p1,
                                                               p3,
                                                               p2,
                                                               material1Back.value(_timeStep),
                                                               material3Back.value(_timeStep),
                                                               material2Back.value(_timeStep)));
    }
    break;

    case Triangle::TriangleVertexFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::triangle(p1,
                                                               p2,
                                                               p3,
                                                               material1Front.value(_timeStep),
                                                               material2Front.value(_timeStep),
                                                               material3Front.value(_timeStep)));
        break;

    case Triangle::TriangleVertexBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::triangle(p1,
                                                               p3,
                                                               p2,
                                                               material1Back.value(_timeStep),
                                                               material3Back.value(_timeStep),
                                                               material2Back.value(_timeStep)));
        break;
    }

    if (showWire.value(_timeStep))
    {
        const float r = radiusWire.value(_timeStep);
        if (Math::isPositive(r))
        {
            const Math::MaterialRGBA mw = materialWire.value(_timeStep);
            if (mw.alpha > 0U)
            {
                const size_t q = qualityWire.value(_timeStep);
                const float d1 = p1.distanceToPoint(p2);
                const float d2 = p2.distanceToPoint(p3);
                const float d3 = p3.distanceToPoint(p1);
                const Math::Vec3F N = Math::Vec3F::cross((p2 - p1), (p3 - p1)).normalized();
                const Math::OrientF o1(p1, (p2 - p1) / d1, N);
                const Math::OrientF o2(p2, (p3 - p2) / d2, N);
                const Math::OrientF o3(p3, (p1 - p3) / d3, N);
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(o1, d1, r, r, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(o2, d2, r, r, q, mw));
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(o3, d3, r, r, q, mw));
            }
        }
    }
}

}  // namespace Items
}  // namespace U1
