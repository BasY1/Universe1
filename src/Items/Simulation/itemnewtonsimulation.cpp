/*!
 * \file src/Items/Simulation/itemnewtonsimulation.cpp
 * \brief Newtonian simulation video item
 */

#include "itemnewtonsimulation.h"

#include "../../Data3D/data3dpointsbase.h"
#include "../../Data3D/data3dpointssize.h"
#include "../../Data3D/data3dpointscolor.h"
#include "../../Data3D/data3dpointssizecolor.h"

namespace U1 {
namespace Items {

#define MAX_POINT_SIZE 10U  //!< Maximum value for Open GL point size

ItemNewtonSimulation::ItemNewtonSimulation(const std::pair<const Math::NewtonSimF *, bool> &_data,
                                           const std::string &_name,
                                           const Math::Vec3F &_center,
                                           const Math::Vec3F &_normal,
                                           const Math::Vec3F &_arm,
                                           const float _time,
                                           const float _scale,
                                           const NewtonSimulation::SimulationColor _colorMode,
                                           const NewtonSimulation::SimulationRadius _radiusMode,
                                           const uint8_t _constantSize,
                                           const uint8_t _maxPointSize,
                                           const Math::ColorRGB &_constantColor,
                                           const Math::ColorRGB &_positiveColor,
                                           const Math::ColorRGB &_negativeColor,
                                           const bool _dynamicShine,
                                           const float _dynamicDistMaxShine,
                                           const float _dynamicDistMinShine,
                                           const bool _dynamicRadius,
                                           const float _dynamicDistMaxRadius,
                                           const float _dynamicDistMinRadius,
                                           const uint8_t _alpha,
                                           const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , m_deleteSimulation(_data.second)
    , m_dataF(_data.first)
    , time(_name + ".time", _time, 0.0f, _data.first == nullptr ? 0.0f : _data.first->lastTimeStep())
    , scale(_name + ".scale", _scale, 0.0f, std::numeric_limits<float>::max())
    , colorMode(_name + ".colorMode", QMetaEnum::fromType<NewtonSimulation::SimulationColor>(), _colorMode)
    , radiusMode(_name + ".radiusMode", QMetaEnum::fromType<NewtonSimulation::SimulationRadius>(), _radiusMode)
    , constantSize(_name + ".constantSize", _constantSize, 1U, MAX_POINT_SIZE)
    , maxPointSize(_name + ".maxPointSize", _maxPointSize, 1U, MAX_POINT_SIZE)
    , constantColor(_name + ".constantColor", _constantColor)
    , positiveColor(_name + ".positiveColor", _positiveColor)
    , negativeColor(_name + ".negativeColor", _negativeColor)
    , dynamicShine(_name + ".dynamicShine", _dynamicShine)
    , dynamicDistMaxShine(_name + ".dynamicDistMaxShine", _dynamicDistMaxShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinShine(_name + ".dynamicDistMinShine", _dynamicDistMinShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicRadius(_name + ".dynamicRadius", _dynamicRadius)
    , dynamicDistMaxRadius(
          _name + ".dynamicDistMaxRadius", _dynamicDistMaxRadius, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinRadius(
          _name + ".dynamicDistMinRadius", _dynamicDistMinRadius, 0.0f, std::numeric_limits<float>::max())
{
    addProperty(&time);
    addProperty(&scale);
    addProperty(&colorMode);
    addProperty(&radiusMode);
    addProperty(&constantSize);
    addProperty(&maxPointSize);
    addProperty(&constantColor);
    addProperty(&positiveColor);
    addProperty(&negativeColor);
    addProperty(&dynamicShine);
    addProperty(&dynamicDistMaxShine);
    addProperty(&dynamicDistMinShine);
    addProperty(&dynamicRadius);
    addProperty(&dynamicDistMaxRadius);
    addProperty(&dynamicDistMinRadius);
}

ItemNewtonSimulation::ItemNewtonSimulation(const std::pair<const Math::NewtonSimD *, bool> &_data,
                                           const std::string &_name,
                                           const Math::Vec3F &_center,
                                           const Math::Vec3F &_normal,
                                           const Math::Vec3F &_arm,
                                           const float _time,
                                           const float _scale,
                                           const NewtonSimulation::SimulationColor _colorMode,
                                           const NewtonSimulation::SimulationRadius _radiusMode,
                                           const uint8_t _constantSize,
                                           const uint8_t _maxPointSize,
                                           const Math::ColorRGB &_constantColor,
                                           const Math::ColorRGB &_positiveColor,
                                           const Math::ColorRGB &_negativeColor,
                                           const bool _dynamicShine,
                                           const float _dynamicDistMaxShine,
                                           const float _dynamicDistMinShine,
                                           const bool _dynamicRadius,
                                           const float _dynamicDistMaxRadius,
                                           const float _dynamicDistMinRadius,
                                           const uint8_t _alpha,
                                           const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , m_deleteSimulation(_data.second)
    , m_dataD(_data.first)
    , time(_name + ".time", _time, 0.0f, _data.first == nullptr ? 0.0f : float(_data.first->lastTimeStep()))
    , scale(_name + ".scale", _scale, 0.0f, std::numeric_limits<float>::max())
    , colorMode(_name + ".colorMode", QMetaEnum::fromType<NewtonSimulation::SimulationColor>(), _colorMode)
    , radiusMode(_name + ".radiusMode", QMetaEnum::fromType<NewtonSimulation::SimulationRadius>(), _radiusMode)
    , constantSize(_name + ".constantSize", _constantSize, 1U, MAX_POINT_SIZE)
    , maxPointSize(_name + ".maxPointSize", _maxPointSize, 1U, MAX_POINT_SIZE)
    , constantColor(_name + ".constantColor", _constantColor)
    , positiveColor(_name + ".positiveColor", _positiveColor)
    , negativeColor(_name + ".negativeColor", _negativeColor)
    , dynamicShine(_name + ".dynamicShine", _dynamicShine)
    , dynamicDistMaxShine(_name + ".dynamicDistMaxShine", _dynamicDistMaxShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinShine(_name + ".dynamicDistMinShine", _dynamicDistMinShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicRadius(_name + ".dynamicRadius", _dynamicRadius)
    , dynamicDistMaxRadius(
          _name + ".dynamicDistMaxRadius", _dynamicDistMaxRadius, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinRadius(
          _name + ".dynamicDistMinRadius", _dynamicDistMinRadius, 0.0f, std::numeric_limits<float>::max())
{
    addProperty(&time);
    addProperty(&scale);
    addProperty(&colorMode);
    addProperty(&radiusMode);
    addProperty(&constantSize);
    addProperty(&maxPointSize);
    addProperty(&constantColor);
    addProperty(&positiveColor);
    addProperty(&negativeColor);
    addProperty(&dynamicShine);
    addProperty(&dynamicDistMaxShine);
    addProperty(&dynamicDistMinShine);
    addProperty(&dynamicRadius);
    addProperty(&dynamicDistMaxRadius);
    addProperty(&dynamicDistMinRadius);
}

ItemNewtonSimulation::ItemNewtonSimulation(const std::pair<const Math::NewtonSimL *, bool> &_data,
                                           const std::string &_name,
                                           const Math::Vec3F &_center,
                                           const Math::Vec3F &_normal,
                                           const Math::Vec3F &_arm,
                                           const float _time,
                                           const float _scale,
                                           const NewtonSimulation::SimulationColor _colorMode,
                                           const NewtonSimulation::SimulationRadius _radiusMode,
                                           const uint8_t _constantSize,
                                           const uint8_t _maxPointSize,
                                           const Math::ColorRGB &_constantColor,
                                           const Math::ColorRGB &_positiveColor,
                                           const Math::ColorRGB &_negativeColor,
                                           const bool _dynamicShine,
                                           const float _dynamicDistMaxShine,
                                           const float _dynamicDistMinShine,
                                           const bool _dynamicRadius,
                                           const float _dynamicDistMaxRadius,
                                           const float _dynamicDistMinRadius,
                                           const uint8_t _alpha,
                                           const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , m_deleteSimulation(_data.second)
    , m_dataL(_data.first)
    , time(_name + ".time", _time, 0.0f, _data.first == nullptr ? 0.0f : float(_data.first->lastTimeStep()))
    , scale(_name + ".scale", _scale, 0.0f, std::numeric_limits<float>::max())
    , colorMode(_name + ".colorMode", QMetaEnum::fromType<NewtonSimulation::SimulationColor>(), _colorMode)
    , radiusMode(_name + ".radiusMode", QMetaEnum::fromType<NewtonSimulation::SimulationRadius>(), _radiusMode)
    , constantSize(_name + ".constantSize", _constantSize, 1U, MAX_POINT_SIZE)
    , maxPointSize(_name + ".maxPointSize", _maxPointSize, 1U, MAX_POINT_SIZE)
    , constantColor(_name + ".constantColor", _constantColor)
    , positiveColor(_name + ".positiveColor", _positiveColor)
    , negativeColor(_name + ".negativeColor", _negativeColor)
    , dynamicShine(_name + ".dynamicShine", _dynamicShine)
    , dynamicDistMaxShine(_name + ".dynamicDistMaxShine", _dynamicDistMaxShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinShine(_name + ".dynamicDistMinShine", _dynamicDistMinShine, 0.0f, std::numeric_limits<float>::max())
    , dynamicRadius(_name + ".dynamicRadius", _dynamicRadius)
    , dynamicDistMaxRadius(
          _name + ".dynamicDistMaxRadius", _dynamicDistMaxRadius, 0.0f, std::numeric_limits<float>::max())
    , dynamicDistMinRadius(
          _name + ".dynamicDistMinRadius", _dynamicDistMinRadius, 0.0f, std::numeric_limits<float>::max())
{
    addProperty(&time);
    addProperty(&scale);
    addProperty(&colorMode);
    addProperty(&radiusMode);
    addProperty(&constantSize);
    addProperty(&maxPointSize);
    addProperty(&constantColor);
    addProperty(&positiveColor);
    addProperty(&negativeColor);
    addProperty(&dynamicShine);
    addProperty(&dynamicDistMaxShine);
    addProperty(&dynamicDistMinShine);
    addProperty(&dynamicRadius);
    addProperty(&dynamicDistMaxRadius);
    addProperty(&dynamicDistMinRadius);
}

ItemNewtonSimulation::~ItemNewtonSimulation()
{
    if (m_deleteSimulation)
    {
        if (m_dataF != nullptr)
            delete m_dataF;
        if (m_dataD != nullptr)
            delete m_dataD;
        if (m_dataL != nullptr)
            delete m_dataL;
    }
}

/*!
 * \brief Helper function
 * \tparam T Floating point type
 * \param _data Output data objects
 * \param _simulation Simulation data
 * \param _radiusMode Simulation object radius mode
 * \param _tmpPos Point position data
 * \param _tmpCol Point color data
 * \param _data1Size Scalar array data size
 * \param _time Time-step
 * \param _constantSize Constant point size
 * \param _maxPointSize Maximum point size
 * \param _alpha Alpha
 */
template <typename T>
void createData1(std::list<OpenGL::Data3D *> &_data,
                 const Math::PhysicsNewton<T> *_simulation,
                 const NewtonSimulation::SimulationRadius _radiusMode,
                 const Math::Vec3F *_tmpPos,
                 const Math::Vec3F *_tmpCol,
                 const size_t _data1Size,
                 const float _time,
                 const float _constantSize,
                 const float _maxPointSize,
                 const uint8_t _alpha)
{
    switch (_radiusMode)
    {
    case NewtonSimulation::SimulationRadiusConstant:
        _data.push_back(
            new OpenGL::Data3DPointsColor(_simulation->countObjects, _tmpPos, _tmpCol, _alpha, _constantSize));
        break;

    case NewtonSimulation::SimulationRadiusMass:
        if (Math::isUnit(_maxPointSize))
        {
            _data.push_back(
                new OpenGL::Data3DPointsColor(_simulation->countObjects, _tmpPos, _tmpCol, _alpha, _maxPointSize));
        }
        else
        {
            float *tmpPS = reinterpret_cast<float *>(std::malloc(_data1Size));
            _simulation->getPointSizeByMass(tmpPS, _maxPointSize);
            _data.push_back(
                new OpenGL::Data3DPointsSizeColor(_simulation->countObjects, _tmpPos, _tmpCol, tmpPS, _alpha));
            std::free(tmpPS);
        }
        break;

    case NewtonSimulation::SimulationRadiusCharge:
        if (Math::isUnit(_maxPointSize))
        {
            _data.push_back(
                new OpenGL::Data3DPointsColor(_simulation->countObjects, _tmpPos, _tmpCol, _alpha, _maxPointSize));
        }
        else
        {
            float *tmpPS = reinterpret_cast<float *>(std::malloc(_data1Size));
            _simulation->getPointSizeByCharge(tmpPS, _maxPointSize);
            _data.push_back(
                new OpenGL::Data3DPointsSizeColor(_simulation->countObjects, _tmpPos, _tmpCol, tmpPS, _alpha));
            std::free(tmpPS);
        }
        break;

    case NewtonSimulation::SimulationRadiusVelocity:
        if (Math::isUnit(_maxPointSize))
        {
            _data.push_back(
                new OpenGL::Data3DPointsColor(_simulation->countObjects, _tmpPos, _tmpCol, _alpha, _maxPointSize));
        }
        else
        {
            float *tmpPS = reinterpret_cast<float *>(std::malloc(_data1Size));
            _simulation->getPointSizeByVelocity(tmpPS, _maxPointSize, _time);
            _data.push_back(
                new OpenGL::Data3DPointsSizeColor(_simulation->countObjects, _tmpPos, _tmpCol, tmpPS, _alpha));
            std::free(tmpPS);
        }
        break;

    case NewtonSimulation::SimulationRadiusAccel:
        if (Math::isUnit(_maxPointSize))
        {
            _data.push_back(
                new OpenGL::Data3DPointsColor(_simulation->countObjects, _tmpPos, _tmpCol, _alpha, _maxPointSize));
        }
        else
        {
            float *tmpPS = reinterpret_cast<float *>(std::malloc(_data1Size));
            _simulation->getPointSizeByAccel(tmpPS, _maxPointSize, _time);
            _data.push_back(
                new OpenGL::Data3DPointsSizeColor(_simulation->countObjects, _tmpPos, _tmpCol, tmpPS, _alpha));
            std::free(tmpPS);
        }
        break;
    }
}

/*!
 * \brief Create simulation 3D data in better floating point precision
 * \tparam T Floating point type
 * \param _data Output data objects
 * \param _simulation Simulation data
 * \param _orientation Orientation
 * \param _time Time-step within the simulation
 * \param _scale Simulation data scale
 * \param _colorMode Simulation object color mode
 * \param _radiusMode Simulation object radius mode
 * \param _constantSize Constant point size
 * \param _maxPointSize Maximum point size
 * \param _constantColor Constant object color (uncharged objects color)
 * \param _positiveColor Color for positively charged objects
 * \param _negativeColor Color for negatively charged objects
 * \param _alpha Alpha
 * \return
 */
template <typename T>
inline static void createDataT(std::list<OpenGL::Data3D *> &_data,
                               const Math::PhysicsNewton<T> *_simulation,
                               const Math::OrientF &_orientation,
                               const float _time,
                               const float _scale,
                               const NewtonSimulation::SimulationColor _colorMode,
                               const NewtonSimulation::SimulationRadius _radiusMode,
                               const float _constantSize,
                               const float _maxPointSize,
                               const Math::ColorRGB &_constantColor,
                               const Math::ColorRGB &_positiveColor,
                               const Math::ColorRGB &_negativeColor,
                               const uint8_t _alpha)
{
    const size_t data1Size = _simulation->countObjects * sizeof(float);
    const size_t data3Size = _simulation->countObjects * sizeof(Math::Vec3F);
    Math::Vec3F *tmpPos = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));

    _simulation->getPositionsAtTimeStepT(tmpPos, _orientation, _time, _scale);

    switch (_colorMode)
    {
    case NewtonSimulation::SimulationColorConstant:
        switch (_radiusMode)
        {
        case NewtonSimulation::SimulationRadiusConstant:
            _data.push_back(
                new OpenGL::Data3DPointsBase(_simulation->countObjects, tmpPos, _constantColor, _alpha, _constantSize));
            break;

        case NewtonSimulation::SimulationRadiusMass:
            if (Math::isUnit(_maxPointSize))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(
                    _simulation->countObjects, tmpPos, _constantColor, _alpha, _maxPointSize));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                _simulation->getPointSizeByMass(tmpPS, _maxPointSize);
                _data.push_back(
                    new OpenGL::Data3DPointsSize(_simulation->countObjects, tmpPos, tmpPS, _constantColor, _alpha));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusCharge:
            if (Math::isUnit(_maxPointSize))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(
                    _simulation->countObjects, tmpPos, _constantColor, _alpha, _maxPointSize));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                _simulation->getPointSizeByCharge(tmpPS, _maxPointSize);
                _data.push_back(
                    new OpenGL::Data3DPointsSize(_simulation->countObjects, tmpPos, tmpPS, _constantColor, _alpha));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusVelocity:
            if (Math::isUnit(_maxPointSize))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(
                    _simulation->countObjects, tmpPos, _constantColor, _alpha, _maxPointSize));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                _simulation->getPointSizeByVelocity(tmpPS, _maxPointSize, _time);
                _data.push_back(
                    new OpenGL::Data3DPointsSize(_simulation->countObjects, tmpPos, tmpPS, _constantColor, _alpha));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusAccel:
            if (Math::isUnit(_maxPointSize))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(
                    _simulation->countObjects, tmpPos, _constantColor, _alpha, _maxPointSize));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                _simulation->getPointSizeByAccel(tmpPS, _maxPointSize, _time);
                _data.push_back(
                    new OpenGL::Data3DPointsSize(_simulation->countObjects, tmpPos, tmpPS, _constantColor, _alpha));
                std::free(tmpPS);
            }
            break;
        }
        break;

    case NewtonSimulation::SimulationColorCharge: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByCharge(tmpCol, _constantColor, _positiveColor, _negativeColor);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorMassGrayscale: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByMassGrayscale(tmpCol);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorMassRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByMassRainbow(tmpCol);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorChargeRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByChargeRainbow(tmpCol);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorVelocityRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByVelocityRainbow(tmpCol, _time);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorAccelRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        _simulation->getColorByAccelRainbow(tmpCol, _time);
        createData1(
            _data, _simulation, _radiusMode, tmpPos, tmpCol, data1Size, _time, _constantSize, _maxPointSize, _alpha);
        std::free(tmpCol);
    }
    break;
    }

    std::free(tmpPos);
}

void ItemNewtonSimulation::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const bool ds = dynamicShine.value(_timeStep);
    if (ds)
        return;

    const bool dr = dynamicRadius.value(_timeStep);
    if (dr)
        return;

    const float s = scale.value(_timeStep);
    if (!Math::isPositive(s))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const float t = time.value(_timeStep);
    const float cs = constantSize.value(_timeStep);
    const float ms = maxPointSize.value(_timeStep);
    const NewtonSimulation::SimulationColor cm = colorMode.valueEnum<NewtonSimulation::SimulationColor>(_timeStep);
    const NewtonSimulation::SimulationRadius rm = radiusMode.valueEnum<NewtonSimulation::SimulationRadius>(_timeStep);
    const Math::ColorRGB c = constantColor.value(_timeStep);
    const Math::ColorRGB pc =
        cm == NewtonSimulation::SimulationColorCharge ? positiveColor.value(_timeStep) : Math::ColorRGB();
    const Math::ColorRGB nc =
        cm == NewtonSimulation::SimulationColorCharge ? negativeColor.value(_timeStep) : Math::ColorRGB();

    if (m_dataF == nullptr)
    {
        if (m_dataD != nullptr)
            createDataT<double>(_data, m_dataD, o, t, s, cm, rm, cs, ms, c, pc, nc, a);
        else if (m_dataL != nullptr)
            createDataT<long double>(_data, m_dataL, o, t, s, cm, rm, cs, ms, c, pc, nc, a);
        return;
    }

    const size_t data1Size = m_dataF->countObjects * sizeof(float);
    const size_t data3Size = m_dataF->countObjects * sizeof(Math::Vec3F);
    Math::Vec3F *tmpPos = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
    m_dataF->getPositionsAtTimeStep(tmpPos, o, t, s);

    switch (cm)
    {
    case NewtonSimulation::SimulationColorConstant:
        switch (rm)
        {
        case NewtonSimulation::SimulationRadiusConstant:
            _data.push_back(new OpenGL::Data3DPointsBase(m_dataF->countObjects, tmpPos, c, a, cs));
            break;

        case NewtonSimulation::SimulationRadiusMass:
            if (Math::isUnit(ms))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(m_dataF->countObjects, tmpPos, c, a, ms));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                m_dataF->getPointSizeByMass(tmpPS, ms);
                _data.push_back(new OpenGL::Data3DPointsSize(m_dataF->countObjects, tmpPos, tmpPS, c, a));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusCharge:
            if (Math::isUnit(ms))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(m_dataF->countObjects, tmpPos, c, a, ms));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                m_dataF->getPointSizeByCharge(tmpPS, ms);
                _data.push_back(new OpenGL::Data3DPointsSize(m_dataF->countObjects, tmpPos, tmpPS, c, a));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusVelocity:
            if (Math::isUnit(ms))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(m_dataF->countObjects, tmpPos, c, a, ms));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                m_dataF->getPointSizeByVelocity(tmpPS, ms, t);
                _data.push_back(new OpenGL::Data3DPointsSize(m_dataF->countObjects, tmpPos, tmpPS, c, a));
                std::free(tmpPS);
            }
            break;

        case NewtonSimulation::SimulationRadiusAccel:
            if (Math::isUnit(ms))
            {
                _data.push_back(new OpenGL::Data3DPointsBase(m_dataF->countObjects, tmpPos, c, a, ms));
            }
            else
            {
                float *tmpPS = reinterpret_cast<float *>(std::malloc(data1Size));
                m_dataF->getPointSizeByAccel(tmpPS, ms, t);
                _data.push_back(new OpenGL::Data3DPointsSize(m_dataF->countObjects, tmpPos, tmpPS, c, a));
                std::free(tmpPS);
            }
            break;
        }
        break;

    case NewtonSimulation::SimulationColorCharge: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByCharge(tmpCol, c, pc, nc);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorMassGrayscale: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByMassGrayscale(tmpCol);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorMassRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByMassRainbow(tmpCol);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorChargeRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByChargeRainbow(tmpCol);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorVelocityRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByVelocityRainbow(tmpCol, t);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;

    case NewtonSimulation::SimulationColorAccelRainbow: {
        Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
        m_dataF->getColorByAccelRainbow(tmpCol, t);
        createData1(_data, m_dataF, rm, tmpPos, tmpCol, data1Size, t, cs, ms, a);
        std::free(tmpCol);
    }
    break;
    }

    std::free(tmpPos);
}

/*!
 * \brief Update shine base on camera distance
 * \param _outColor Output colors
 * \param _tmpPos Positions
 * \param _camera Camera position
 * \param _dynamicDistMaxShine Near plane for maximal shine
 * \param _dynamicDistMinShine Far plane for minimal shine
 * \param _countObjects Number of objects
 * \param _pool Multi-thread indices
 * \return
 */
static void createShine(Math::Vec3F *_outColor,
                        const Math::Vec3F *_tmpPos,
                        const Math::Vec3F &_camera,
                        const float _dynamicDistMaxShine,
                        const float _dynamicDistMinShine,
                        const size_t _countObjects,
                        const std::vector<std::pair<size_t, size_t>> &_pool)
{
    static const float minShine = 0.3f;
    static const float difShine = 1.0f - minShine;
    const float min = std::min(_dynamicDistMaxShine, _dynamicDistMinShine);
    const float max = std::max(_dynamicDistMaxShine, _dynamicDistMinShine);
    const float dif = max - min;
    const float ratio = difShine / dif;

    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            const float d = _camera.distanceToPoint(_tmpPos[i]);
            if (Math::isLessOrEqual(d, min))
                continue;

            if (Math::isMoreOrEqual(d, max))
                _outColor[i] *= minShine;
            else
                _outColor[i] *= (minShine + ratio * (max - d));
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _camera, min, max, ratio](Math::Vec3F *__outColor, const Math::Vec3F *_pos) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const float d = _camera.distanceToPoint(_pos[i]);
                        if (Math::isLessOrEqual(d, min))
                            continue;

                        if (Math::isMoreOrEqual(d, max))
                            __outColor[i] *= minShine;
                        else
                            __outColor[i] *= (minShine + ratio * (max - d));
                    }
                },
                _outColor,
                _tmpPos));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Update radius base on camera distance
 * \param _outSize Output point radiuses
 * \param _tmpPos Positions
 * \param _camera Camera position
 * \param _dynamicDistMaxRadius Near plane for maximal radius
 * \param _dynamicDistMinRadius Far plane for minimal radius
 * \param _countObjects Number of objects
 * \param _pool Multi-thread indices
 * \return
 */
static void createRadius(float *_outSize,
                         const Math::Vec3F *_tmpPos,
                         const Math::Vec3F &_camera,
                         const float _dynamicDistMaxRadius,
                         const float _dynamicDistMinRadius,
                         const size_t _countObjects,
                         const std::vector<std::pair<size_t, size_t>> &_pool)
{
    const float min = std::min(_dynamicDistMaxRadius, _dynamicDistMinRadius);
    const float max = std::max(_dynamicDistMaxRadius, _dynamicDistMinRadius);
    const float dif = max - min;

    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            const float d = _camera.distanceToPoint(_tmpPos[i]);
            if (Math::isLessOrEqual(d, min))
                continue;

            if (Math::isMoreOrEqual(d, max))
                _outSize[i] = 1.0f;
            else
                _outSize[i] = (1.0f + std::max(0.0f, _outSize[i] - 1.0f) * (max - d) / dif);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _camera, min, max, dif](float *__outSize, const Math::Vec3F *_pos) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const float d = _camera.distanceToPoint(_pos[i]);
                        if (Math::isLessOrEqual(d, min))
                            continue;

                        if (Math::isMoreOrEqual(d, max))
                            __outSize[i] = 1.0f;
                        else
                            __outSize[i] = (1.0f + std::max(0.0f, __outSize[i] - 1.0f) * (max - d) / dif);
                    }
                },
                _outSize,
                _tmpPos));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Create simulation 3D data in better floating point precision
 * \param _data Output data objects
 * \param _simulation Simulation data
 * \param _camera Camera
 * \param _orientation Orientation
 * \param _time Time-step within the simulation
 * \param _scale Simulation data scale
 * \param _colorMode Simulation object color mode
 * \param _radiusMode Simulation object radius mode
 * \param _constantSize Constant point size
 * \param _maxPointSize Maximum point size
 * \param _constantColor Constant object color (uncharged objects color)
 * \param _positiveColor Color for positively charged objects
 * \param _negativeColor Color for negatively charged objects
 * \param _alpha Alpha
 * \param _dynamicShine Enable dynamic object shine flag
 * \param _dynamicDistMaxShine Near plane for maximal shine
 * \param _dynamicDistMinShine Far plane for minimal shine
 * \param _dynamicRadius Enable dynamic object radius flag
 * \param _dynamicDistMaxRadius Near plane for maximal radius
 * \param _dynamicDistMinRadius Far plane for minimal radius
 * \return
 */
template <typename T>
inline static void createDataT(std::list<OpenGL::Data3D *> &_data,
                               const Math::PhysicsNewton<T> *_simulation,
                               const Math::CamF &_camera,
                               const Math::OrientF &_orientation,
                               const float _time,
                               const float _scale,
                               const NewtonSimulation::SimulationColor _colorMode,
                               const NewtonSimulation::SimulationRadius _radiusMode,
                               const float _constantSize,
                               const float _maxPointSize,
                               const Math::ColorRGB &_constantColor,
                               const Math::ColorRGB &_positiveColor,
                               const Math::ColorRGB &_negativeColor,
                               const uint8_t _alpha,
                               const bool _dynamicShine,
                               const float _dynamicDistMaxShine,
                               const float _dynamicDistMinShine,
                               const bool _dynamicRadius,
                               const float _dynamicDistMaxRadius,
                               const float _dynamicDistMinRadius)
{
    const std::vector<std::pair<size_t, size_t>> pool = Math::createPool(_simulation->countObjects);
    const size_t data1Size = _simulation->countObjects * sizeof(float);
    const size_t data3Size = _simulation->countObjects * sizeof(Math::Vec3F);
    Math::Vec3F *tmpPos = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
    Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
    float *tmpSiz = reinterpret_cast<float *>(std::malloc(data1Size));

    _simulation->getPositionsAtTimeStepT(tmpPos, _orientation, _time, _scale);

    switch (_colorMode)
    {
    case NewtonSimulation::SimulationColorConstant:
        Math::setConstantData(tmpCol, _constantColor.toVec3F(), _simulation->countObjects, pool);
        break;
    case NewtonSimulation::SimulationColorCharge:
        _simulation->getColorByCharge(tmpCol, _constantColor, _positiveColor, _negativeColor);
        break;
    case NewtonSimulation::SimulationColorMassGrayscale: _simulation->getColorByMassGrayscale(tmpCol); break;
    case NewtonSimulation::SimulationColorMassRainbow: _simulation->getColorByMassRainbow(tmpCol); break;
    case NewtonSimulation::SimulationColorChargeRainbow: _simulation->getColorByChargeRainbow(tmpCol); break;
    case NewtonSimulation::SimulationColorVelocityRainbow: _simulation->getColorByVelocityRainbow(tmpCol, _time); break;
    case NewtonSimulation::SimulationColorAccelRainbow: _simulation->getColorByAccelRainbow(tmpCol, _time); break;
    }

    switch (_radiusMode)
    {
    case NewtonSimulation::SimulationRadiusConstant:
        Math::setConstantData(tmpSiz, _constantSize, _simulation->countObjects, pool);
        break;
    case NewtonSimulation::SimulationRadiusMass: _simulation->getPointSizeByMass(tmpSiz, _maxPointSize); break;
    case NewtonSimulation::SimulationRadiusCharge: _simulation->getPointSizeByCharge(tmpSiz, _maxPointSize); break;
    case NewtonSimulation::SimulationRadiusVelocity:
        _simulation->getPointSizeByVelocity(tmpSiz, _maxPointSize, _time);
        break;
    case NewtonSimulation::SimulationRadiusAccel: _simulation->getPointSizeByAccel(tmpSiz, _maxPointSize, _time); break;
    }

    if (_dynamicShine && !Math::equals(_dynamicDistMaxShine, _dynamicDistMinShine))
        createShine(tmpCol,
                    tmpPos,
                    _camera.position,
                    _dynamicDistMaxShine,
                    _dynamicDistMinShine,
                    _simulation->countObjects,
                    pool);

    if (_dynamicRadius && !Math::equals(_dynamicDistMaxRadius, _dynamicDistMinRadius))
        createRadius(tmpSiz,
                     tmpPos,
                     _camera.position,
                     _dynamicDistMaxRadius,
                     _dynamicDistMinRadius,
                     _simulation->countObjects,
                     pool);

    _data.push_back(new OpenGL::Data3DPointsSizeColor(_simulation->countObjects, tmpPos, tmpCol, tmpSiz, _alpha));

    std::free(tmpPos);
    std::free(tmpCol);
    std::free(tmpSiz);
}

void ItemNewtonSimulation::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                          const Math::CamF &_camera,
                                          const size_t _timeStep) const
{
    const bool ds = dynamicShine.value(_timeStep);
    const bool dr = dynamicRadius.value(_timeStep);
    if (ds == false && dr == false)
        return;

    const float s = scale.value(_timeStep);
    if (!Math::isPositive(s))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const float t = time.value(_timeStep);
    const float cs = constantSize.value(_timeStep);
    const float ms = maxPointSize.value(_timeStep);

    const NewtonSimulation::SimulationColor cm = colorMode.valueEnum<NewtonSimulation::SimulationColor>(_timeStep);
    const NewtonSimulation::SimulationRadius rm = radiusMode.valueEnum<NewtonSimulation::SimulationRadius>(_timeStep);

    const Math::ColorRGB c = constantColor.value(_timeStep);
    const Math::ColorRGB pc =
        cm == NewtonSimulation::SimulationColorCharge ? positiveColor.value(_timeStep) : Math::ColorRGB();
    const Math::ColorRGB nc =
        cm == NewtonSimulation::SimulationColorCharge ? negativeColor.value(_timeStep) : Math::ColorRGB();

    const float ds1 = ds ? dynamicDistMaxShine.value(_timeStep) : 0.0f;
    const float ds2 = ds ? dynamicDistMinShine.value(_timeStep) : 0.0f;
    const float dr1 = dr ? dynamicDistMaxRadius.value(_timeStep) : 0.0f;
    const float dr2 = dr ? dynamicDistMinRadius.value(_timeStep) : 0.0f;

    if (m_dataF == nullptr)
    {
        if (m_dataD != nullptr)
            createDataT<double>(
                _data, m_dataD, _camera, o, t, s, cm, rm, cs, ms, c, pc, nc, a, ds, ds1, ds2, dr, dr1, dr2);
        else if (m_dataL != nullptr)
            createDataT<long double>(
                _data, m_dataL, _camera, o, t, s, cm, rm, cs, ms, c, pc, nc, a, ds, ds1, ds2, dr, dr1, dr2);
        return;
    }

    const std::vector<std::pair<size_t, size_t>> pool = Math::createPool(m_dataF->countObjects);
    const size_t data1Size = m_dataF->countObjects * sizeof(float);
    const size_t data3Size = m_dataF->countObjects * sizeof(Math::Vec3F);
    Math::Vec3F *tmpPos = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
    Math::Vec3F *tmpCol = reinterpret_cast<Math::Vec3F *>(std::malloc(data3Size));
    float *tmpSiz = reinterpret_cast<float *>(std::malloc(data1Size));

    m_dataF->getPositionsAtTimeStep(tmpPos, o, t, s);

    switch (cm)
    {
    case NewtonSimulation::SimulationColorConstant:
        Math::setConstantData(tmpCol, c.toVec3F(), m_dataF->countObjects, pool);
        break;
    case NewtonSimulation::SimulationColorCharge: m_dataF->getColorByCharge(tmpCol, c, pc, nc); break;
    case NewtonSimulation::SimulationColorMassGrayscale: m_dataF->getColorByMassGrayscale(tmpCol); break;
    case NewtonSimulation::SimulationColorMassRainbow: m_dataF->getColorByMassRainbow(tmpCol); break;
    case NewtonSimulation::SimulationColorChargeRainbow: m_dataF->getColorByChargeRainbow(tmpCol); break;
    case NewtonSimulation::SimulationColorVelocityRainbow: m_dataF->getColorByVelocityRainbow(tmpCol, t); break;
    case NewtonSimulation::SimulationColorAccelRainbow: m_dataF->getColorByAccelRainbow(tmpCol, t); break;
    }

    switch (rm)
    {
    case NewtonSimulation::SimulationRadiusConstant:
        Math::setConstantData(tmpSiz, cs, m_dataF->countObjects, pool);
        break;
    case NewtonSimulation::SimulationRadiusMass: m_dataF->getPointSizeByMass(tmpSiz, ms); break;
    case NewtonSimulation::SimulationRadiusCharge: m_dataF->getPointSizeByCharge(tmpSiz, ms); break;
    case NewtonSimulation::SimulationRadiusVelocity: m_dataF->getPointSizeByVelocity(tmpSiz, ms, t); break;
    case NewtonSimulation::SimulationRadiusAccel: m_dataF->getPointSizeByAccel(tmpSiz, ms, t); break;
    }

    if (ds && !Math::equals(ds1, ds2))
        createShine(tmpCol, tmpPos, _camera.position, ds1, ds2, m_dataF->countObjects, pool);

    if (dr && !Math::equals(dr1, dr2))
        createRadius(tmpSiz, tmpPos, _camera.position, dr1, dr2, m_dataF->countObjects, pool);

    _data.push_back(new OpenGL::Data3DPointsSizeColor(m_dataF->countObjects, tmpPos, tmpCol, tmpSiz, a));

    std::free(tmpPos);
    std::free(tmpCol);
    std::free(tmpSiz);
}

}  // namespace Items
}  // namespace U1
