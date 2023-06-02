#include "item3d.h"

Universe1::Video::Item3D::Item3D(const bool _visible, const std::string &_name)
    : Item(_name)
    , visible(_visible, _name + ".visible")
{
    props.push_back(&visible);
}

static const float lowestShine = 256.0f;

void Universe1::Video::Item3D::addHide(const uint64_t _startHidingTime, const uint64_t _endHidingTime)
{
    const Config &cfg = Config::cfg();
    const uint64_t startFixed = cfg.fixedTime(_startHidingTime);
    const uint64_t endFixed = cfg.fixedTime(_endHidingTime);
    if (_startHidingTime != startFixed || _endHidingTime != endFixed)
        std::cerr << "Warning[" << name << "]: addHide(" << _startHidingTime << "ms, " << _endHidingTime
                  << "ms): Using aligned time: " << startFixed << "ms, " << endFixed << "ms !" << std::endl;

    for (DynamicMaterialGroup *m : materials)
    {
        float a = m->alpha.addSame(startFixed);
        m->alpha.add(endFixed - cfg.frameDuration, 0.0f);
        m->alpha.add(endFixed, a);

        a = m->shine.addSame(startFixed);
        m->shine.add(endFixed - cfg.frameDuration, lowestShine);
        m->shine.add(endFixed, a);
    }
    visible.add(endFixed, false);
}

void Universe1::Video::Item3D::addShow(const uint64_t _startShowingTime, const uint64_t _endShowingTime)
{
    const Config &cfg = Config::cfg();
    const uint64_t startFixed = cfg.fixedTime(_startShowingTime);
    const uint64_t endFixed = cfg.fixedTime(_endShowingTime);
    if (_startShowingTime != startFixed || _endShowingTime != endFixed)
        std::cerr << "Warning[" << name << "]: addShow(" << _startShowingTime << "ms, " << _endShowingTime
                  << "ms): Using aligned time: " << startFixed << "ms, " << endFixed << "ms !" << std::endl;

    if (startFixed == 0UL)
    {
        visible = true;
        for (DynamicMaterialGroup *m : materials)
        {
            const float a = m->alpha.values.back().second;
            const float s = m->shine.values.back().second;
            m->alpha = 0.0f;
            m->alpha.add(endFixed, a);
            m->shine = lowestShine;
            m->shine.add(endFixed, s);
        }
        return;
    }

    if (visible.values.empty() || visible.values.back().second == true)
    {
        std::cerr << "[" << name << "]: Can't addShow(" << startFixed << ", ...), already visible !" << std::endl;
        return;
    }

    visible.add(startFixed, true);
    for (DynamicMaterialGroup *m : materials)
    {
        const float a = m->alpha.values.back().second;
        const float s = m->shine.values.back().second;
        m->alpha.add(startFixed, 0.0f);
        m->alpha.add(endFixed, a);
        m->shine.add(startFixed, lowestShine);
        m->shine.add(endFixed, s);
    }
}

Universe1::Video::Item3DBase::Item3DBase(const bool _visible, const Material &_material, const std::string &_name)
    : Item3D(_visible, _name)
    , material(_material, _name + ".material", props, materials)
{
}

Universe1::Video::DBItems3D::DBItems3D(const std::string &_propertyName,
                                       const std::string &_footageName,
                                       std::list<Item3D *> *_items)
    : propertyName(_propertyName)
    , footageName(_footageName)
    , items(_items)
{
}

std::string Universe1::Video::DBItems3D::nextName()
{
    return footageName + "." + propertyName + "[" + std::to_string(++count) + "]";
}
