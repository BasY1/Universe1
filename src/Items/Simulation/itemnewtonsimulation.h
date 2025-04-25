/*!
 * \file src/Items/Simulation/itemnewtonsimulation.h
 * \brief Newtonian simulation video item
 */
#ifndef ITEMS_ITEMNEWTONSIMULATION_H
#define ITEMS_ITEMNEWTONSIMULATION_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertycolor.h"

#include "../../Math/physicsnewton.h"

namespace U1 {
namespace Items {

/*!
 * \namespace U1::Items::NewtonSimulation
 * \brief Newton simulation item tools
 */
namespace NewtonSimulation {
Q_NAMESPACE

/*! \brief Simulation color modes */
enum SimulationColor : int
{
    SimulationColorConstant,         //!< Single color for all particle
    SimulationColorCharge,           //!< 3 colors from object charge
    SimulationColorMassGrayscale,    //!< Gray-scale color from object mass
    SimulationColorMassRainbow,      //!< Rainbow-scale color from object mass
    SimulationColorChargeRainbow,    //!< Rainbow-scale color from object charge
    SimulationColorVelocityRainbow,  //!< Rainbow-scale color from object velocity
    SimulationColorAccelRainbow,     //!< Rainbow-scale color from object acceleration

};
Q_ENUM_NS(SimulationColor)

/*! \brief Simulation object radius modes */
enum SimulationRadius : int
{
    SimulationRadiusConstant,  //!< Constant object radius
    SimulationRadiusMass,      //!< Object radius relative to object mass
    SimulationRadiusCharge,    //!< Object radius relative to object charge
    SimulationRadiusVelocity,  //!< Object radius relative to object velocity
    SimulationRadiusAccel,     //!< Object radius relative to object acceleration
};
Q_ENUM_NS(SimulationRadius)

}  // namespace NewtonSimulation

/*! \brief Newtonian simulation video item */
class ItemNewtonSimulation : public Item3DExt
{
 protected:
    const bool m_deleteSimulation;  //!< Flag, if \c true then simulation data will be deleted together with object

    const Math::NewtonSimF *m_dataF = nullptr;  //!< Simulation data in 32 bit precision
    const Math::NewtonSimD *m_dataD = nullptr;  //!< Simulation data in 64 bit precision
    const Math::NewtonSimL *m_dataL = nullptr;  //!< Simulation data in 128 bit precision

 public:
    Props::ItemPropertyFloat time;   //!< Time-step within the simulation
    Props::ItemPropertyFloat scale;  //!< Simulation data scale

    Props::ItemPropertyEnum colorMode;   //!< Simulation object color mode
    Props::ItemPropertyEnum radiusMode;  //!< Simulation object radius mode

    Props::ItemPropertyUInt8 constantSize;  //!< Constant point size
    Props::ItemPropertyUInt8 maxPointSize;  //!< Maximum point size

    Props::ItemPropertyColor constantColor;  //!< Constant object color (uncharged objects color)
    Props::ItemPropertyColor positiveColor;  //!< Color for positively charged objects
    Props::ItemPropertyColor negativeColor;  //!< Color for negatively charged objects

    Props::ItemPropertyBool dynamicShine;          //!< Enable dynamic object shine flag
    Props::ItemPropertyFloat dynamicDistMaxShine;  //!< Near plane for maximal shine
    Props::ItemPropertyFloat dynamicDistMinShine;  //!< Far plane for minimal shine

    Props::ItemPropertyBool dynamicRadius;          //!< Enable dynamic object radius flag
    Props::ItemPropertyFloat dynamicDistMaxRadius;  //!< Near plane for maximal radius
    Props::ItemPropertyFloat dynamicDistMinRadius;  //!< Far plane for minimal radius

 public:
    /*!
     * \brief Constructor
     * \param _data Simulation data in 32 bit precision and flag (delete simulation data together with object)
     * \param _name Object name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _time Initial time-step within the simulation
     * \param _scale Initial data scale
     * \param _colorMode Initial object color mode
     * \param _radiusMode Initial object radius mode
     * \param _constantSize Initial constant point size
     * \param _maxPointSize Initial maximum point size
     * \param _constantColor Initial constant object color (uncharged objects color)
     * \param _positiveColor Initial color for positively charged objects
     * \param _negativeColor Initial color for negatively charged objects
     * \param _dynamicShine Initial enable dynamic object shine flag
     * \param _dynamicDistMaxShine Initial near plane for maximal shine
     * \param _dynamicDistMinShine Initial far plane for minimal shine
     * \param _dynamicRadius Initial enable dynamic object radius flag
     * \param _dynamicDistMaxRadius Initial near plane for maximal radius
     * \param _dynamicDistMinRadius Initial far plane for minimal radius
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemNewtonSimulation(
        const std::pair<const Math::NewtonSimF *, bool> &_data,
        const std::string &_name = "Newton simulation",
        const Math::Vec3F &_center = {},
        const Math::Vec3F &_normal = Math::Vec3F::unitX(),
        const Math::Vec3F &_arm = Math::Vec3F::unitY(),
        const float _time = 0.0f,
        const float _scale = 1.0f,
        const NewtonSimulation::SimulationColor _colorMode = NewtonSimulation::SimulationColorVelocityRainbow,
        const NewtonSimulation::SimulationRadius _radiusMode = NewtonSimulation::SimulationRadiusMass,
        const uint8_t _constantSize = 1U,
        const uint8_t _maxPointSize = 10U,
        const Math::ColorRGB &_constantColor = {Qt::white},
        const Math::ColorRGB &_positiveColor = {Qt::blue},
        const Math::ColorRGB &_negativeColor = {Qt::red},
        const bool _dynamicShine = true,
        const float _dynamicDistMaxShine = 1.0f,
        const float _dynamicDistMinShine = 100.0f,
        const bool _dynamicRadius = true,
        const float _dynamicDistMaxRadius = 1.0f,
        const float _dynamicDistMinRadius = 100.0f,
        const uint8_t _alpha = 255U,
        const bool _visible = true);

    /*!
     * \brief Constructor
     * \param _data Simulation data in 64 bit precision and flag (delete simulation data together with object)
     * \param _name Object name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _time Initial time-step within the simulation
     * \param _scale Initial data scale
     * \param _colorMode Initial object color mode
     * \param _radiusMode Initial object radius mode
     * \param _constantSize Initial constant point size
     * \param _maxPointSize Initial maximum point size
     * \param _constantColor Initial constant object color (uncharged objects color)
     * \param _positiveColor Initial color for positively charged objects
     * \param _negativeColor Initial color for negatively charged objects
     * \param _dynamicShine Initial enable dynamic object shine flag
     * \param _dynamicDistMaxShine Initial near plane for maximal shine
     * \param _dynamicDistMinShine Initial far plane for minimal shine
     * \param _dynamicRadius Initial enable dynamic object radius flag
     * \param _dynamicDistMaxRadius Initial near plane for maximal radius
     * \param _dynamicDistMinRadius Initial far plane for minimal radius
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemNewtonSimulation(
        const std::pair<const Math::NewtonSimD *, bool> &_data,
        const std::string &_name = "Newton simulation",
        const Math::Vec3F &_center = {},
        const Math::Vec3F &_normal = Math::Vec3F::unitX(),
        const Math::Vec3F &_arm = Math::Vec3F::unitY(),
        const float _time = 0.0f,
        const float _scale = 1.0f,
        const NewtonSimulation::SimulationColor _colorMode = NewtonSimulation::SimulationColorVelocityRainbow,
        const NewtonSimulation::SimulationRadius _radiusMode = NewtonSimulation::SimulationRadiusMass,
        const uint8_t _constantSize = 1U,
        const uint8_t _maxPointSize = 10U,
        const Math::ColorRGB &_constantColor = {Qt::white},
        const Math::ColorRGB &_positiveColor = {Qt::blue},
        const Math::ColorRGB &_negativeColor = {Qt::red},
        const bool _dynamicShine = true,
        const float _dynamicDistMaxShine = 1.0f,
        const float _dynamicDistMinShine = 100.0f,
        const bool _dynamicRadius = true,
        const float _dynamicDistMaxRadius = 1.0f,
        const float _dynamicDistMinRadius = 100.0f,
        const uint8_t _alpha = 255U,
        const bool _visible = true);

    /*!
     * \brief Constructor
     * \param _data Simulation data in 128 bit precision and flag (delete simulation data together with object)
     * \param _name Object name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _time Initial time-step within the simulation
     * \param _scale Initial data scale
     * \param _colorMode Initial object color mode
     * \param _radiusMode Initial object radius mode
     * \param _constantSize Initial constant point size
     * \param _maxPointSize Initial maximum point size
     * \param _constantColor Initial constant object color (uncharged objects color)
     * \param _positiveColor Initial color for positively charged objects
     * \param _negativeColor Initial color for negatively charged objects
     * \param _dynamicShine Initial enable dynamic object shine flag
     * \param _dynamicDistMaxShine Initial near plane for maximal shine
     * \param _dynamicDistMinShine Initial far plane for minimal shine
     * \param _dynamicRadius Initial enable dynamic object radius flag
     * \param _dynamicDistMaxRadius Initial near plane for maximal radius
     * \param _dynamicDistMinRadius Initial far plane for minimal radius
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemNewtonSimulation(
        const std::pair<const Math::NewtonSimL *, bool> &_data,
        const std::string &_name = "Newton simulation",
        const Math::Vec3F &_center = {},
        const Math::Vec3F &_normal = Math::Vec3F::unitX(),
        const Math::Vec3F &_arm = Math::Vec3F::unitY(),
        const float _time = 0.0f,
        const float _scale = 1.0f,
        const NewtonSimulation::SimulationColor _colorMode = NewtonSimulation::SimulationColorVelocityRainbow,
        const NewtonSimulation::SimulationRadius _radiusMode = NewtonSimulation::SimulationRadiusMass,
        const uint8_t _constantSize = 1U,
        const uint8_t _maxPointSize = 10U,
        const Math::ColorRGB &_constantColor = {Qt::white},
        const Math::ColorRGB &_positiveColor = {Qt::blue},
        const Math::ColorRGB &_negativeColor = {Qt::red},
        const bool _dynamicShine = true,
        const float _dynamicDistMaxShine = 1.0f,
        const float _dynamicDistMinShine = 10.0f,
        const bool _dynamicRadius = true,
        const float _dynamicDistMaxRadius = 1.0f,
        const float _dynamicDistMinRadius = 10.0f,
        const uint8_t _alpha = 255U,
        const bool _visible = true);

    ~ItemNewtonSimulation();  //!< Destructor

    /*!
     * \brief Returns the latest time-step within the simulation data
     * \return Latest time-step within the simulation data
     */
    inline float latestSimulationTimestep() const
    {
        return time.maximumValue();
    }

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;

    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _camera Camera data
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data,
                        const Math::CamF &_camera,
                        const size_t _timeStep) const override;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMNEWTONSIMULATION_H
