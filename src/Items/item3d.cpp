/*!
 * \file src/Items/item3d.cpp
 * \brief Basic 3D video item
 */

#include "item3d.h"

namespace U1 {
namespace Items {

size_t Item3D::maxClipPlanes() const
{
    return OpenGL::Data3D::MaxClipPlanes;
}

ClipPlane *Item3D::addClipPlane(const Math::Vec3F &_center,
                                const Math::Vec3F &_normal,
                                const bool _enabled,
                                const std::string &_name)
{
    if (m_clipPlanes.size() >= maxClipPlanes())
    {
        std::cerr << "Error: Item3D::addClipPlane: Maximum " << maxClipPlanes() << " clip planes allowed!\n";
        return nullptr;
    }

    ClipPlane *result = new ClipPlane(_name, _center, _normal, _enabled);
    m_clipPlanes.push_back(result);
    addProperty(result);
    return result;
}

void Item3D::createData(std::list<OpenGL::Data3D *> &_data,
                        std::vector<std::pair<Math::CamF, std::list<OpenGL::Data3D *>>> &_cameraData,
                        const std::vector<QVector4D> &_clipPlanes,
                        const size_t _timeStep) const
{
    if (!visible.value(_timeStep))
        return;

    std::list<OpenGL::Data3D *> tmp;

    std::vector<QVector4D> planes = _clipPlanes;
    for (const ClipPlane *const &cp : std::as_const(m_clipPlanes))
        if (cp->enabled.value(_timeStep))
            planes.push_back(cp->equation(_timeStep));

    createDataImpl(tmp, _timeStep);
    if (!tmp.empty())
    {
        for (OpenGL::Data3D *d : tmp)
            d->setClipPlanes(planes);

        _data.splice(_data.end(), tmp);
    }

    for (std::pair<Math::CamF, std::list<OpenGL::Data3D *>> &cd : _cameraData)
    {
        createDataImpl(tmp, cd.first, _timeStep);
        if (!tmp.empty())
        {
            for (OpenGL::Data3D *d : tmp)
                d->setClipPlanes(planes);

            cd.second.splice(cd.second.end(), tmp);
        }
    }
}

void Item3D::createDataImpl(std::list<OpenGL::Data3D *> &_data, const Math::CamF &_camera, const size_t _timeStep) const
{
    Q_UNUSED(_data)
    Q_UNUSED(_camera)
    Q_UNUSED(_timeStep)
}

}  // namespace Items
}  // namespace U1
