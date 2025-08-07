/*!
 * \file src/Math/physicsuniverse1.h
 * \brief The Universe1 simulation processor
 */

#ifndef MATH_PHYSICSUNIVERSE1_H
#define MATH_PHYSICSUNIVERSE1_H

#include "orientation.h"
#include "spherecrosssection.h"

#include <fstream>
#include <set>

namespace U1 {
namespace Math {

/*!
 * \namespace U1::Math::Universe1
 * \brief The Universe1 physics tools
 */
namespace Universe1 {
Q_NAMESPACE

// clang-format off

#define U1_NULL_ID          (std::numeric_limits<size_t>::max())  //!< NULL parent or child particle ID

#define U1_MASK_RED_P       (0b00000001) //!< Active red spin with positive helicity
#define U1_MASK_RED_N       (0b00000010) //!< Active red spin with negative helicity 
#define U1_MASK_GREEN_P     (0b00000100) //!< Active green spin with positive helicity 
#define U1_MASK_GREEN_N     (0b00001000) //!< Active green spin with negative helicity
#define U1_MASK_BLUE_P      (0b00010000) //!< Active blue spin with positive helicity
#define U1_MASK_BLUE_N      (0b00100000) //!< Active blue spin with negative helicity
#define U1_MASK_MAIN_P      (0b01000000) //!< Active major spin with positive helicity
#define U1_MASK_MAIN_N      (0b10000000) //!< Active major spin with negative helicity

#define U1_MASK_RED_PN      (U1_MASK_RED_P   | U1_MASK_RED_N  ) //!< Bit-mask: Opposing red spins in bosons
#define U1_MASK_GREEN_PN    (U1_MASK_GREEN_P | U1_MASK_GREEN_N) //!< Bit-mask: Opposing green spins in bosons
#define U1_MASK_BLUE_PN     (U1_MASK_BLUE_P  | U1_MASK_BLUE_N ) //!< Bit-mask: Opposing blue spins in bosons
#define U1_MASK_BOSON_WZ    (U1_MASK_MAIN_P | U1_MASK_MAIN_N)   //!< Bit-mask: Opposing major spins in bosons W and Z

#define U1_MASK_RGB_P       (U1_MASK_RED_P | U1_MASK_GREEN_P | U1_MASK_BLUE_P) //!< Bit-mask: Positron charge
#define U1_MASK_RGB_N       (U1_MASK_RED_N | U1_MASK_GREEN_N | U1_MASK_BLUE_N) //!< Bit-mask: Electron charge

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define U1_NEUTRINO_P       (U1_MASK_MAIN_P) //!< Neutrino: major normal with positive helicity 
#define U1_NEUTRINO_N       (U1_MASK_MAIN_N) //!< Neutrino: major normal with negative helicity 

#define U1_POSITRON_P       (U1_MASK_MAIN_P | U1_MASK_RGB_P) //!< Positron: color normals with positive helicity, major normal with positive helicity 
#define U1_POSITRON_N       (U1_MASK_MAIN_N | U1_MASK_RGB_P) //!< Positron: color normals with positive helicity, major normal with negative helicity 
#define U1_ELECTRON_P       (U1_MASK_MAIN_P | U1_MASK_RGB_N) //!< Electron: color normals with negative helicity, major normal with positive helicity 
#define U1_ELECTRON_N       (U1_MASK_MAIN_N | U1_MASK_RGB_N) //!< Electron: color normals with negative helicity, major normal with negative helicity 

#define U1_QUARK_UP_RG_P    (U1_MASK_MAIN_P | U1_MASK_RED_P   | U1_MASK_GREEN_P) //!< Up quark: red-green normals with positive helicity, major normal with positive helicity
#define U1_QUARK_UP_RG_N    (U1_MASK_MAIN_N | U1_MASK_RED_P   | U1_MASK_GREEN_P) //!< Up quark: red-green normals with positive helicity, major normal with negative helicity
#define U1_QUARK_UP_RB_P    (U1_MASK_MAIN_P | U1_MASK_RED_P   | U1_MASK_BLUE_P ) //!< Up quark: red-blue normals with positive helicity, major normal with positive helicity
#define U1_QUARK_UP_RB_N    (U1_MASK_MAIN_N | U1_MASK_RED_P   | U1_MASK_BLUE_P ) //!< Up quark: red-blue normals with positive helicity, major normal with negative helicity
#define U1_QUARK_UP_GB_P    (U1_MASK_MAIN_P | U1_MASK_GREEN_P | U1_MASK_BLUE_P ) //!< Up quark: green-blue normals with positive helicity, major normal with positive helicity
#define U1_QUARK_UP_GB_N    (U1_MASK_MAIN_N | U1_MASK_GREEN_P | U1_MASK_BLUE_P ) //!< Up quark: green-blue normals with positive helicity, major normal with negative helicity

#define U1_ANTI_UP_RG_P     (U1_MASK_MAIN_P | U1_MASK_RED_N   | U1_MASK_GREEN_N) //!< Anti-up quark: red-green normals with negative helicity, major normal with positive helicity
#define U1_ANTI_UP_RG_N     (U1_MASK_MAIN_N | U1_MASK_RED_N   | U1_MASK_GREEN_N) //!< Anti-up quark: red-green normals with negative helicity, major normal with negative helicity
#define U1_ANTI_UP_RB_P     (U1_MASK_MAIN_P | U1_MASK_RED_N   | U1_MASK_BLUE_N ) //!< Anti-up quark: red-blue normals with negative helicity, major normal with positive helicity
#define U1_ANTI_UP_RB_N     (U1_MASK_MAIN_N | U1_MASK_RED_N   | U1_MASK_BLUE_N ) //!< Anti-up quark: red-blue normals with negative helicity, major normal with negative helicity
#define U1_ANTI_UP_GB_P     (U1_MASK_MAIN_P | U1_MASK_GREEN_N | U1_MASK_BLUE_N ) //!< Anti-up quark: green-blue normals with negative helicity, major normal with positive helicity 
#define U1_ANTI_UP_GB_N     (U1_MASK_MAIN_N | U1_MASK_GREEN_N | U1_MASK_BLUE_N ) //!< Anti-up quark: green-blue normals with negative helicity, major normal with negative helicity 

#define U1_QUARK_DOWN_R_P   (U1_MASK_MAIN_P | U1_MASK_RED_N  ) //!< Down quark: red normal with negative helicity, major normal with positive helicity
#define U1_QUARK_DOWN_R_N   (U1_MASK_MAIN_N | U1_MASK_RED_N  ) //!< Down quark: red normal with negative helicity, major normal with negative helicity
#define U1_QUARK_DOWN_G_P   (U1_MASK_MAIN_P | U1_MASK_GREEN_N) //!< Down quark: green normal with negative helicity, major normal with positive helicity
#define U1_QUARK_DOWN_G_N   (U1_MASK_MAIN_N | U1_MASK_GREEN_N) //!< Down quark: green normal with negative helicity, major normal with negative helicity
#define U1_QUARK_DOWN_B_P   (U1_MASK_MAIN_P | U1_MASK_BLUE_N ) //!< Down quark: blue normal with negative helicity, major normal with positive helicity
#define U1_QUARK_DOWN_B_N   (U1_MASK_MAIN_N | U1_MASK_BLUE_N ) //!< Down quark: blue normal with negative helicity, major normal with negative helicity

#define U1_ANTI_DOWN_R_P    (U1_MASK_MAIN_P | U1_MASK_RED_P  ) //!< Anti-down quark: red normal with positive helicity, major normal with positive helicity
#define U1_ANTI_DOWN_R_N    (U1_MASK_MAIN_N | U1_MASK_RED_P  ) //!< Anti-down quark: red normal with positive helicity, major normal with negative helicity
#define U1_ANTI_DOWN_G_P    (U1_MASK_MAIN_P | U1_MASK_GREEN_P) //!< Anti-down quark: green normal with positive helicity, major normal with positive helicity
#define U1_ANTI_DOWN_G_N    (U1_MASK_MAIN_N | U1_MASK_GREEN_P) //!< Anti-down quark: green normal with positive helicity, major normal with negative helicity
#define U1_ANTI_DOWN_B_P    (U1_MASK_MAIN_P | U1_MASK_BLUE_P ) //!< Anti-down quark: blue normal with positive helicity, major normal with positive helicity
#define U1_ANTI_DOWN_B_N    (U1_MASK_MAIN_N | U1_MASK_BLUE_P ) //!< Anti-down quark: blue normal with positive helicity, major normal with negative helicity

#define U1_PHOTON_P         (U1_MASK_MAIN_P | U1_MASK_RED_PN | U1_MASK_GREEN_PN | U1_MASK_BLUE_PN) //!< Photon: all color normals has opposing normal in the same color, both major normals with positive helicity
#define U1_PHOTON_N         (U1_MASK_MAIN_N | U1_MASK_RED_PN | U1_MASK_GREEN_PN | U1_MASK_BLUE_PN) //!< Photon: all color normals has opposing normal in the same color, both major normals with negative helicity

#define U1_GLUON_RG_P       (U1_MASK_MAIN_P | U1_MASK_RED_P | U1_MASK_GREEN_N | U1_MASK_BLUE_PN ) //!< Gluon: 1. red normal positive, 2. green normal negative helicity, both major normals with positive helicity
#define U1_GLUON_RG_N       (U1_MASK_MAIN_N | U1_MASK_RED_P | U1_MASK_GREEN_N | U1_MASK_BLUE_PN ) //!< Gluon: 1. red normal positive, 2. green normal negative helicity, both major normals with negative helicity
#define U1_GLUON_RB_P       (U1_MASK_MAIN_P | U1_MASK_RED_P | U1_MASK_BLUE_N | U1_MASK_GREEN_PN ) //!< Gluon: 1. red normal positive, 2. blue normal negative helicity, both major normals with positive helicity
#define U1_GLUON_RB_N       (U1_MASK_MAIN_N | U1_MASK_RED_P | U1_MASK_BLUE_N | U1_MASK_GREEN_PN ) //!< Gluon: 1. red normal positive, 2. blue normal negative helicity, both major normals with negative helicity
#define U1_GLUON_GR_P       (U1_MASK_MAIN_P | U1_MASK_GREEN_P | U1_MASK_RED_N | U1_MASK_BLUE_PN ) //!< Gluon: 1. green normal positive, 2. red normal negative helicity, both major normals with positive helicity
#define U1_GLUON_GR_N       (U1_MASK_MAIN_N | U1_MASK_GREEN_P | U1_MASK_RED_N | U1_MASK_BLUE_PN ) //!< Gluon: 1. green normal positive, 2. red normal negative helicity, both major normals with negative helicity
#define U1_GLUON_GB_P       (U1_MASK_MAIN_P | U1_MASK_GREEN_P | U1_MASK_BLUE_N | U1_MASK_RED_PN ) //!< Gluon: 1. green normal positive, 2. blue normal negative helicity, both major normals with positive helicity
#define U1_GLUON_GB_N       (U1_MASK_MAIN_N | U1_MASK_GREEN_P | U1_MASK_BLUE_N | U1_MASK_RED_PN ) //!< Gluon: 1. green normal positive, 2. blue normal negative helicity, both major normals with negative helicity
#define U1_GLUON_BR_P       (U1_MASK_MAIN_P | U1_MASK_BLUE_P | U1_MASK_RED_N | U1_MASK_GREEN_PN ) //!< Gluon: 1. blue normal positive, 2. red normal negative helicity, both major normals with positive helicity
#define U1_GLUON_BR_N       (U1_MASK_MAIN_N | U1_MASK_BLUE_P | U1_MASK_RED_N | U1_MASK_GREEN_PN ) //!< Gluon: 1. blue normal positive, 2. red normal negative helicity, both major normals with negative helicity
#define U1_GLUON_BG_P       (U1_MASK_MAIN_P | U1_MASK_BLUE_P | U1_MASK_GREEN_N | U1_MASK_RED_PN ) //!< Gluon: 1. blue normal positive, 2. green normal negative helicity, both major normals with positive helicity
#define U1_GLUON_BG_N       (U1_MASK_MAIN_N | U1_MASK_BLUE_P | U1_MASK_GREEN_N | U1_MASK_RED_PN ) //!< Gluon: 1. blue normal positive, 2. green normal negative helicity, both major normals with negative helicity

#define U1_BOSON_W_R_P      (U1_MASK_BOSON_WZ | U1_MASK_RGB_P | U1_MASK_RED_N  ) //!< Boson W+: 1. color normals with positive helicity, 1. major normal positive and 2. major normal negative helicity
#define U1_BOSON_W_G_P      (U1_MASK_BOSON_WZ | U1_MASK_RGB_P | U1_MASK_GREEN_N) //!< Boson W+: 1. color normals with positive helicity, 1. major normal positive and 2. major normal negative helicity
#define U1_BOSON_W_B_P      (U1_MASK_BOSON_WZ | U1_MASK_RGB_P | U1_MASK_BLUE_N ) //!< Boson W+: 1. color normals with positive helicity, 1. major normal positive and 2. major normal negative helicity
#define U1_BOSON_W_R_N      (U1_MASK_BOSON_WZ | U1_MASK_RGB_N | U1_MASK_RED_P  ) //!< Boson W-: 1. color normals with negative helicity, 1. major normal negative and 2. major normal positive helicity
#define U1_BOSON_W_G_N      (U1_MASK_BOSON_WZ | U1_MASK_RGB_N | U1_MASK_GREEN_P) //!< Boson W-: 1. color normals with negative helicity, 1. major normal negative and 2. major normal positive helicity
#define U1_BOSON_W_B_N      (U1_MASK_BOSON_WZ | U1_MASK_RGB_N | U1_MASK_BLUE_P ) //!< Boson W-: 1. color normals with negative helicity, 1. major normal negative and 2. major normal positive helicity

#define U1_BOSON_Z_R        (U1_MASK_BOSON_WZ | U1_MASK_RED_PN  ) //!< Boson Z: Opposing red spins
#define U1_BOSON_Z_G        (U1_MASK_BOSON_WZ | U1_MASK_GREEN_PN) //!< Boson Z: Opposing green spins
#define U1_BOSON_Z_B        (U1_MASK_BOSON_WZ | U1_MASK_BLUE_PN ) //!< Boson Z: Opposing blue spins

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #define U1_IS_RED(_MASK_)       (((_MASK_ & U1_MASK_RED_P  ) != 0U) ^ ((_MASK_ & U1_MASK_RED_N  ) != 0U))
// #define U1_IS_GREEN(_MASK_)     (((_MASK_ & U1_MASK_GREEN_P) != 0U) ^ ((_MASK_ & U1_MASK_GREEN_N) != 0U))
// #define U1_IS_BLUE(_MASK_)      (((_MASK_ & U1_MASK_BLUE_P ) != 0U) ^ ((_MASK_ & U1_MASK_BLUE_N ) != 0U))

// #define U1_IS_RED_PN(_MASK_)    ((_MASK_ & U1_MASK_RED_PN  ) == U1_MASK_RED_PN  )
// #define U1_IS_GREEN_PN(_MASK_)  ((_MASK_ & U1_MASK_GREEN_PN) == U1_MASK_GREEN_PN)
// #define U1_IS_BLUE_PN(_MASK_)   ((_MASK_ & U1_MASK_BLUE_PN ) == U1_MASK_BLUE_PN )

// #define U1_IS_FERMION(_MASK_)   ((_MASK_ & U1_MASK_BOSON ) != U1_MASK_BOSON)
// #define U1_IS_BOSON(_MASK_)     ((_MASK_ & U1_MASK_BOSON ) == U1_MASK_BOSON)

// clang-format on

template <typename T>
struct TimeStep;

/*!
 * \brief Wave created at single time-step during the existence of a particle
 * \tparam T Template floating point type
 */
template <typename T>
struct WaveSource
{
    uint8_t generation = 0U;  //!< Generation number for fermions (1, 2 or 3)

    T spinR = T(0);  //!< Red component magnitude
    T spinG = T(0);  //!< Green component magnitude
    T spinB = T(0);  //!< Blue component magnitude
    T spin1 = T(0);  //!< 1. generation major component magnitude
    T spin2 = T(0);  //!< 2. generation major component magnitude
    T spin3 = T(0);  //!< 3. generation major component magnitude

    T radius2 = T(0);  //!< 2. generation inner body radius
    T radius3 = T(0);  //!< 3. generation inner body radius

    Vec3<T> position1 = {};  //!< 1. generation particle wave source position
    Vec3<T> position2 = {};  //!< 2. generation particle wave source position
    Vec3<T> position3 = {};  //!< 3. generation particle wave source position

    WaveSource() = default;  //!< Default constructor

    /*!
     * \brief Generation 1 constructor
     * \param _position1 Initial position
     */
    inline WaveSource(const Vec3<T> &_position1)
        : generation(1U)
        , position1(_position1)
        , position2(_position1)
        , position3(_position1)
    {
    }

 private:
    friend struct TimeStep<T>;  //!< Friend

    /*!
     * \brief Setup spins
     * \param _spin1 1. generation major component magnitude
     * \param _spinR Red component magnitude
     * \param _spinG Green component magnitude
     * \param _spinB Blue component magnitude
     * \return This object
     */
    inline WaveSource<T> &setSpins(const T _spin1, const T _spinR, const T _spinG, const T _spinB)
    {
        spin1 = _spin1;
        spinR = _spinR;
        spinG = _spinG;
        spinB = _spinB;
        return *this;
    }
};

/*!
 * \brief Single particle state within the specific time-step in the system
 * \tparam T Template floating point type
 */
template <typename T>
struct TimeStep
{
    uint8_t type;  //!< Particle type

    T time;  //!< Time-step (in seconds)
    T spin;  //!< The amplitude of current major inner rotation (in radians per second)

    Vec3<T> position;  //!< Current position (in meters)

    Vec3<T> normal;  //!< Current particle normal - the major direction of translational motion (unit vector)

    Vec3<T> normalR;  //!< Current orientation of red matter inside the particle (unit vector)
    Vec3<T> normalG;  //!< Current orientation of green matter inside the particle (unit vector)
    Vec3<T> normalB;  //!< Current orientation of blue matter inside the particle (unit vector)

    Vec3<T> bodySpin1 = {};  //!< Current outer body major rotation (in radian per second)
    Vec3<T> bodySpin2 = {};  //!< Current generation 2 body rotation (in radian per second)

    /*!
     * \brief Save data into file
     * \param _ofs File stream
     * \return Success flag
     */
    bool save(std::ofstream &_ofs) const
    {
        _ofs << type;
        _ofs << time;
        _ofs << spin;
        _ofs << position;
        _ofs << normal;
        _ofs << normalR;
        _ofs << normalG;
        _ofs << normalB;
        _ofs << bodySpin1;
        _ofs << bodySpin2;
        return true;
    }

    /*!
     * \brief Load data from file
     * \param _ifs File stream
     * \return Success flag
     */
    bool load(std::ifstream &_ifs)
    {
        _ifs >> type;
        _ifs >> time;
        _ifs >> spin;
        _ifs >> position;
        _ifs >> normal;
        _ifs >> normalR;
        _ifs >> normalG;
        _ifs >> normalB;
        _ifs >> bodySpin1;
        _ifs >> bodySpin2;
        return true;
    }

    /*!
     * \brief Universal constant for representing a radius of a particle spherical shape (\f$R_1\f$ in meters)
     * \return Universal constant for representing a radius of a particle spherical shape
     */
    inline static T R1()
    {
        return T(1);
    }

    /*!
     * \brief Universal velocity constant (\f$C_1\f$ in meters per second)
     * \return Universal velocity constant
     */
    inline static T C1()
    {
        return T(1);
    }

    /*!
     * \brief Universal angular velocity constant (\f$\Omega_1\f$ in radians per second)
     * \return Universal angular velocity constant
     * \note \f$\Omega_1 = \frac{C_1}{R_1} \f$
     */
    inline static T O1()
    {
        return T(1);
    }

    /*!
     * \brief Universal constant for
     * \return Universal constant for
     */
    inline static T K1()
    {
        return T(1);
    }

    /*!
     * \brief Angle between the normal and active color normal for electron and positron particles
     * \return Angle between the normal and active color normal for electron and positron particles
     */
    inline static T electronDotNormalColor()
    {
        static const T value = std::sqrt(T(3)) / T(3);
        return value;
    }

    /*!
     * \brief Angle between the normal and active color normal for up quark and anti-up quark particles
     * \return Angle between the normal and active color normal for up quark and anti-up quark particles
     */
    inline static T quarkUpDotNormalColor()
    {
        static const T value = std::sqrt(T(2)) / T(2);
        return value;
    }

    /*!
     * \brief Angle between the normal and active color normal for up quark and anti-up quark particles
     * \return Angle between the normal and active color normal for up quark and anti-up quark particles
     */
    inline static T quarkDownDotNormalColor()
    {
        static const T value = std::sqrt(T(3)) / T(2);
        return value;
    }

    /*!
     * \brief Return dot products of major normal with color normals
     * \return Dot products of major normal with color normals
     */
    inline Vec3<T> getDotRGB() const
    {
        return Vec3<T>(Vec3<T>::dot(normal, normalR),  //
                       Vec3<T>::dot(normal, normalG),
                       Vec3<T>::dot(normal, normalB));
    }

    /*!
     * \brief Return mutual dot products between color normals
     * \return Mutual dot products between color normals
     */
    inline Vec3<T> getDotRG_GB_BR() const
    {
        return Vec3<T>(Vec3<T>::dot(normalR, normalG),  //
                       Vec3<T>::dot(normalG, normalB),
                       Vec3<T>::dot(normalB, normalR));
    }

    /*!
     * \brief Wave source data
     * \return Wave source data
     */
    WaveSource<T> getWave() const
    {
        WaveSource<T> result(result.position1);

        switch (type)
        {
        case U1_NEUTRINO_P: result.spin1 = +spin; break;
        case U1_NEUTRINO_N: result.spin1 = -spin; break;

        case U1_POSITRON_P: result.setSpins(+spin, T(1), T(1), T(1)); break;
        case U1_POSITRON_N: result.setSpins(-spin, T(1), T(1), T(1)); break;

        case U1_ELECTRON_P: result.setSpins(+spin, T(-1), T(-1), T(-1)); break;
        case U1_ELECTRON_N: result.setSpins(-spin, T(-1), T(-1), T(-1)); break;

        case U1_QUARK_UP_RG_P: result.setSpins(+spin, T(1), T(1), T(0)); break;
        case U1_QUARK_UP_RG_N: result.setSpins(-spin, T(1), T(1), T(0)); break;
        case U1_QUARK_UP_RB_P: result.setSpins(+spin, T(1), T(0), T(1)); break;
        case U1_QUARK_UP_RB_N: result.setSpins(-spin, T(1), T(0), T(1)); break;
        case U1_QUARK_UP_GB_P: result.setSpins(+spin, T(0), T(1), T(1)); break;
        case U1_QUARK_UP_GB_N: result.setSpins(-spin, T(0), T(1), T(1)); break;

        case U1_ANTI_UP_RG_P: result.setSpins(+spin, T(-1), T(-1), T(0)); break;
        case U1_ANTI_UP_RG_N: result.setSpins(-spin, T(-1), T(-1), T(0)); break;
        case U1_ANTI_UP_RB_P: result.setSpins(+spin, T(-1), T(0), T(-1)); break;
        case U1_ANTI_UP_RB_N: result.setSpins(-spin, T(-1), T(0), T(-1)); break;
        case U1_ANTI_UP_GB_P: result.setSpins(+spin, T(0), T(-1), T(-1)); break;
        case U1_ANTI_UP_GB_N: result.setSpins(-spin, T(0), T(-1), T(-1)); break;

        case U1_QUARK_DOWN_R_P: result.setSpins(+spin, T(-1), T(0), T(0)); break;
        case U1_QUARK_DOWN_R_N: result.setSpins(-spin, T(-1), T(0), T(0)); break;
        case U1_QUARK_DOWN_G_P: result.setSpins(+spin, T(0), T(-1), T(0)); break;
        case U1_QUARK_DOWN_G_N: result.setSpins(-spin, T(0), T(-1), T(0)); break;
        case U1_QUARK_DOWN_B_P: result.setSpins(+spin, T(0), T(0), T(-1)); break;
        case U1_QUARK_DOWN_B_N: result.setSpins(-spin, T(0), T(0), T(-1)); break;

        case U1_ANTI_DOWN_R_P: result.setSpins(+spin, T(1), T(0), T(0)); break;
        case U1_ANTI_DOWN_R_N: result.setSpins(-spin, T(1), T(0), T(0)); break;
        case U1_ANTI_DOWN_G_P: result.setSpins(+spin, T(0), T(1), T(0)); break;
        case U1_ANTI_DOWN_G_N: result.setSpins(-spin, T(0), T(1), T(0)); break;
        case U1_ANTI_DOWN_B_P: result.setSpins(+spin, T(0), T(0), T(1)); break;
        case U1_ANTI_DOWN_B_N: result.setSpins(-spin, T(0), T(0), T(1)); break;

        case U1_PHOTON_P: result.spin1 = +spin; return result;
        case U1_PHOTON_N: result.spin1 = -spin; return result;

        case U1_GLUON_RG_P: return result.setSpins(+spin, T(1), T(-1), T(0));
        case U1_GLUON_RG_N: return result.setSpins(-spin, T(1), T(-1), T(0));
        case U1_GLUON_RB_P: return result.setSpins(+spin, T(1), T(0), T(-1));
        case U1_GLUON_RB_N: return result.setSpins(-spin, T(1), T(0), T(-1));
        case U1_GLUON_GR_P: return result.setSpins(+spin, T(-1), T(1), T(0));
        case U1_GLUON_GR_N: return result.setSpins(-spin, T(-1), T(1), T(0));
        case U1_GLUON_GB_P: return result.setSpins(+spin, T(0), T(1), T(-1));
        case U1_GLUON_GB_N: return result.setSpins(-spin, T(0), T(1), T(-1));
        case U1_GLUON_BR_P: return result.setSpins(+spin, T(-1), T(0), T(1));
        case U1_GLUON_BR_N: return result.setSpins(-spin, T(-1), T(0), T(1));
        case U1_GLUON_BG_P: return result.setSpins(+spin, T(0), T(-1), T(1));
        case U1_GLUON_BG_N: return result.setSpins(-spin, T(0), T(-1), T(1));

        case U1_BOSON_W_R_P:
        case U1_BOSON_W_G_P:
        case U1_BOSON_W_B_P: return result.setSpins(std::abs(spin), T(1), T(1), T(1));

        case U1_BOSON_W_R_P:
        case U1_BOSON_W_G_P:
        case U1_BOSON_W_B_P: return result.setSpins(std::abs(spin), T(-1), T(-1), T(-1));

        case U1_BOSON_Z_R:
        case U1_BOSON_Z_G:
        case U1_BOSON_Z_B: result.spin1 = std::abs(spin); return result;

        default: return WaveSource<T>();
        }

        const Vec3<T> bodySpin1Hidden = bodySpin1.projected(normal);
        const Vec3<T> bodySpin1Apply = bodySpin1 - bodySpin1Hidden;

        const T bodySpin1ApplyMagnitude = bodySpin1Apply.length();

        if (isLessOrEqual(bodySpin1ApplyMagnitude, O1()))
            return result;

        const Vec3<T> normal2 = bodySpin1Apply.normalized();
        const Vec3<T> dirPos2 = Vec3<T>::cross(normal2, normal).normalized();
        const T radiusCurving1 = C1() / bodySpin1ApplyMagnitude;
        const T velocity1Magnitude = O1() * radiusCurving1;
        const T velocity2Magnitude = std::sqrt(C1() * C1() - velocity1Magnitude * velocity1Magnitude);

        result.generation++;
        result.position2 = position + dirPos2 * radiusCurving1;
        result.spin1 *= (velocity1Magnitude / C1());
        result.radius2 = R1() - radiusCurving1;
        result.spin2 = O1();

        const Vec3<T> bodySpin2Apply = bodySpin2.projected(dirPos2);
        const T bodySpin2ApplyMagnitude = bodySpin2Apply.length();
        const T bodySpin2Critical = velocity2Magnitude / result.radius2;

        if (isLessOrEqual(bodySpin2ApplyMagnitude, bodySpin2Critical))
            return result;

        const T helicitySign = (isPositive(spin) ? T(1) : T(-1));

        const Vec3<T> n2 = normal2 * helicitySign;
        const Vec3<T> normal3 = bodySpin2Apply.normalized();

        const Vec3<T> dirPos3 = Vec3<T>::cross(normal3, n2).normalized();
        const T radiusCurving2 = velocity2Magnitude / bodySpin2ApplyMagnitude;

        const T velocity2MagnitudeReduced = O1() * radiusCurving2;
        const T velocity3Magnitude =
            std::sqrt(velocity2Magnitude * velocity2Magnitude - velocity2MagnitudeReduced * velocity2MagnitudeReduced);

        result.generation++;
        result.position3 = result.position2 + dirPos3 * radiusCurving2;
        result.spin2 *= (velocity2MagnitudeReduced / velocity2Magnitude);
        result.radius3 = result.radius2 - radiusCurving2;
        result.spin3 = O1();

        return result;
    }

    /*!
     * \brief Wave source data
     * \param _timeDelta Time duration of the motion
     * \return Wave source data
     */
    TimeStep<T> moved(const T _timeDelta) const
    {
        TimeStep<T> result;
        result.type = type;
        result.time = time + _timeDelta;
        result.spin = spin;

        const Vec3<T> bodySpin1Hidden = bodySpin1.projected(normal);
        const Vec3<T> bodySpin1Apply = bodySpin1 - bodySpin1Hidden;

        const T bodySpin1ApplyMagnitude = bodySpin1Apply.length();
        if (isNull(bodySpin1ApplyMagnitude))
        {
            const T rot = spin * _timeDelta;
            const T srot = std::sin(rot);
            const T crot = std::cos(rot);
            result.position = position + normal * (C1() * _timeDelta);
            result.normal = normal;
            result.normalR = normalR.rotated(normal, srot, crot).normalized();
            result.normalG = normalG.rotated(normal, srot, crot).normalized();
            result.normalB = normalB.rotated(normal, srot, crot).normalized();
            return result;
        }

        const Vec3<T> n2 = bodySpin1Apply.normalized();
        const Vec3<T> dirPos2 = Vec3<T>::cross(n2, normal).normalized();
        const T radiusCurving1 = C1() / bodySpin1ApplyMagnitude;

        if (isMoreOrEqual(radiusCurving1, R1()))
        {
            const T rot = spin * _timeDelta;
            const T srot = std::sin(rot);
            const T crot = std::cos(rot);
            const T passedAngle = bodySpin1ApplyMagnitude * _timeDelta;
            const T spa = std::sin(passedAngle);
            const T cpa = std::cos(passedAngle);
            const Vec3<T> dirPos2rot = dirPos2.rotated(n2, spa, cpa).normalized();
            result.position = position + dirPos2 * radiusCurving1 - dirPos2rot * radiusCurving1;
            result.normal = normal.rotated(n2, spa, cpa).normalized();
            result.normalR = normalR.rotated(normal, srot, crot).normalized().rotated(n2, spa, cpa).normalized();
            result.normalG = normalG.rotated(normal, srot, crot).normalized().rotated(n2, spa, cpa).normalized();
            result.normalB = normalB.rotated(normal, srot, crot).normalized().rotated(n2, spa, cpa).normalized();
            return result;
        }

        const T helicitySign = (isPositive(spin) ? T(1) : T(-1));
        const T velocity1Magnitude = O1() * radiusCurving1;
        const T velocity2Magnitude = std::sqrt(C1() * C1() - velocity1Magnitude * velocity1Magnitude);

        const Vec3<T> normal2 = n2 * helicitySign;
        const Vec3<T> bodySpin2Apply = bodySpin2.projected(dirPos2);
        const T bodySpin2ApplyMagnitude = bodySpin2Apply.length();

        if (isNull(bodySpin2ApplyMagnitude))
        {
            const T rot = spin * _timeDelta * (velocity1Magnitude / C1());
            const T srot = std::sin(rot);
            const T crot = std::cos(rot);

            const T passedAngle1 = O1() * _timeDelta;
            const T spa1 = std::sin(passedAngle1);
            const T cpa1 = std::cos(passedAngle1);
            const Vec3<T> dirPos2rot = dirPos2.rotated(n2, spa1, cpa1).normalized();

            const T passedLength2 = (velocity2Magnitude * _timeDelta);

            result.position = position +                                  //
                dirPos2 * radiusCurving1 - dirPos2rot * radiusCurving1 +  //
                normal2 * passedLength2;

            result.normal = normal.rotated(n2, spa1, cpa1).normalized();
            result.normalR = normalR.rotated(normal, srot, crot).normalized().rotated(n2, spa1, cpa1).normalized();
            result.normalG = normalG.rotated(normal, srot, crot).normalized().rotated(n2, spa1, cpa1).normalized();
            result.normalB = normalB.rotated(normal, srot, crot).normalized().rotated(n2, spa1, cpa1).normalized();

            return result;
        }

        const T radius2 = R1() - radiusCurving1;
        const T bodySpin2critical = velocity2Magnitude / radius2;
        const Vec3<T> n3 = bodySpin2Apply.normalized();
        const Vec3<T> dirPos3 = Vec3<T>::cross(n3, normal2).normalized();
        const T radiusCurving2 = velocity2Magnitude / bodySpin2ApplyMagnitude;

        if (isLessOrEqual(bodySpin2ApplyMagnitude, bodySpin2critical))
        {
            const T rot = spin * _timeDelta * (velocity1Magnitude / C1());
            const T srot = std::sin(rot);
            const T crot = std::cos(rot);

            const T passedAngle1 = O1() * _timeDelta;
            const T spa1 = std::sin(passedAngle1);
            const T cpa1 = std::cos(passedAngle1);
            const Vec3<T> dirPos2rot = dirPos2.rotated(n2, spa1, cpa1).normalized();

            const T passedLength2 = (velocity2Magnitude * _timeDelta);
            const T passedAngle2 = passedLength2 / radius2;
            const T spa2 = std::sin(passedAngle2);
            const T cpa2 = std::cos(passedAngle2);
            const Vec3<T> dirPos3rot = dirPos3.rotated(n3, spa2, cpa2).normalized();

            result.position = position +                                  //
                dirPos2 * radiusCurving1 - dirPos2rot * radiusCurving1 +  //
                dirPos3 * radiusCurving2 - dirPos3rot * radiusCurving2;

            result.normal = normal.rotated(n2, spa1, cpa1).normalized().rotated(n3, spa2, cpa2).normalized();

            result.normalR = normalR.rotated(normal, srot, crot)
                                 .normalized()
                                 .rotated(n2, spa1, cpa1)
                                 .normalized()
                                 .rotated(n3, spa2, cpa2)
                                 .normalized();

            result.normalG = normalG.rotated(normal, srot, crot)
                                 .normalized()
                                 .rotated(n2, spa1, cpa1)
                                 .normalized()
                                 .rotated(n3, spa2, cpa2)
                                 .normalized();

            result.normalB = normalB.rotated(normal, srot, crot)
                                 .normalized()
                                 .rotated(n2, spa1, cpa1)
                                 .normalized()
                                 .rotated(n3, spa2, cpa2)
                                 .normalized();

            return result;
        }

        const T velocity2MagnitudeReduced = O1() * radiusCurving2;
        const T velocity3Magnitude =
            std::sqrt(velocity2Magnitude * velocity2Magnitude - velocity2MagnitudeReduced * velocity2MagnitudeReduced);

        const T rot = spin * _timeDelta * (velocity1Magnitude / C1());
        const T srot = std::sin(rot);
        const T crot = std::cos(rot);

        const T passedAngle1 = O1() * _timeDelta;
        const T spa1 = std::sin(passedAngle1);
        const T cpa1 = std::cos(passedAngle1);
        const Vec3<T> dirPos2rot = dirPos2.rotated(n2, spa1, cpa1).normalized();

        const T passedLength2 = (velocity2MagnitudeReduced * _timeDelta);
        const T passedAngle2 = passedLength2 / radius2;
        const T spa2 = std::sin(passedAngle2);
        const T cpa2 = std::cos(passedAngle2);
        const Vec3<T> dirPos3rot = dirPos3.rotated(n3, spa2, cpa2).normalized();

        const T passedLength3 = (velocity3Magnitude * _timeDelta * helicitySign);

        result.position = position +                                  //
            dirPos2 * radiusCurving1 - dirPos2rot * radiusCurving1 +  //
            dirPos3 * radiusCurving2 - dirPos3rot * radiusCurving2 +  //
            n3 * passedLength3;

        result.normal = normal.rotated(n2, spa1, cpa1).normalized().rotated(n3, spa2, cpa2).normalized();

        result.normalR = normalR.rotated(normal, srot, crot)
                             .normalized()
                             .rotated(n2, spa1, cpa1)
                             .normalized()
                             .rotated(n3, spa2, cpa2)
                             .normalized();

        result.normalG = normalG.rotated(normal, srot, crot)
                             .normalized()
                             .rotated(n2, spa1, cpa1)
                             .normalized()
                             .rotated(n3, spa2, cpa2)
                             .normalized();

        result.normalB = normalB.rotated(normal, srot, crot)
                             .normalized()
                             .rotated(n2, spa1, cpa1)
                             .normalized()
                             .rotated(n3, spa2, cpa2)
                             .normalized();

        return result;
    }

 protected:
    /*!
     * \brief Tool function - test all normals are unit vectors
     * \return \c true when all the normals are unit vectors
     */
    inline bool isValid_UnitVectors() const
    {
        return normal.isUnit() && normalR.isUnit() && normalG.isUnit() && normalB.isUnit();
    }

 public:
    /*!
     * \brief Return \c true if this time-step has valid normal configuration for positive helicity neutrino
     * \return \c true if this time-step has valid normal configuration for positive helicity neutrino
     * \details Conditions for valid positive helicity neutrino:
     *  - all normals are unit vectors
     *  - all the mutual angle in between color normals are equal to 120°
     *  - all color normals are perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_NEUTRINO_P() const
    {
        return isValid_UnitVectors() &&                         //
            normal.isPerpendicular(normalR) &&                  //
            normal.isPerpendicular(normalG) &&                  //
            normal.isPerpendicular(normalB) &&                  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&  //
            isPositive(spin) &&                                 //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this time-step has valid normal configuration for negative helicity neutrino
     * \return \c true if this time-step has valid normal configuration for negative helicity neutrino
     * \details Conditions for valid negative helicity neutrino:
     *  - all normals are unit vectors
     *  - all color normals are perpendicular to the major normal
     *  - all the mutual angle in between color normals are equal to 120°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_NEUTRINO_N() const
    {
        return isValid_UnitVectors() &&                         //
            normal.isPerpendicular(normalR) &&                  //
            normal.isPerpendicular(normalG) &&                  //
            normal.isPerpendicular(normalB) &&                  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&  //
            isNegative(spin) &&                                 //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    //

    /*!
     * \brief Return \c true if this time-step has valid normal configuration for positive helicity positron
     * \return \c true if this time-step has valid normal configuration for positive helicity positron
     * \details Conditions for valid positive helicity positron:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle to the major normal: \f$acos(\frac{\sqrt{3}}{3})\f$
     *  - all the color normals are perpendicular to each other right-handed configuration (\f$N_B = N_R \times N_G\f$)
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_POSITRON_P() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), electronDotNormalColor()) &&  //
            normalR.isPerpendicular(normalG) &&                                 //
            normalG.isPerpendicular(normalB) &&                                 //
            normalB.isPerpendicular(normalR) &&                                 //
            isPositive(spin) &&                                                 //
            normalB.equals(Vec3<T>::cross(normalR, normalG).normalized());      //
    }

    /*!
     * \brief Return \c true if this time-step has valid normal configuration for negative helicity positron
     * \return \c true if this time-step has valid normal configuration for negative helicity positron
     * \details Conditions for valid negative helicity positron:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle to the major normal: \f$acos(\frac{\sqrt{3}}{3})\f$
     *  - all the color normals are perpendicular to each other left-handed configuration (\f$N_B = N_G \times N_R\f$)
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_POSITRON_N() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), electronDotNormalColor()) &&  //
            normalR.isPerpendicular(normalG) &&                                 //
            normalG.isPerpendicular(normalB) &&                                 //
            normalB.isPerpendicular(normalR) &&                                 //
            isNegative(spin) &&                                                 //
            normalB.equals(Vec3<T>::cross(normalG, normalR).normalized());      //
    }

    //

    /*!
     * \brief Return \c true if this time-step has valid normal configuration for positive helicity electron
     * \return \c true if this time-step has valid normal configuration for positive helicity electron
     * \details Conditions for valid positive helicity electron:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle to the major normal: \f$-acos(\frac{\sqrt{3}}{3})\f$
     *  - all the color normals are perpendicular to each other left-handed configuration (\f$N_B = N_G \times N_R\f$)
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ELECTRON_P() const
    {
        return isValid_UnitVectors() &&                                          //
            equals(Vec3<T>::dot(normal, normalR), -electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), -electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), -electronDotNormalColor()) &&  //
            normalR.isPerpendicular(normalG) &&                                  //
            normalG.isPerpendicular(normalB) &&                                  //
            normalB.isPerpendicular(normalR) &&                                  //
            isPositive(spin) &&                                                  //
            normalB.equals(Vec3<T>::cross(normalG, normalR).normalized());       //
    }

    /*!
     * \brief Return \c true if this time-step has valid normal configuration for negative helicity electron
     * \return \c true if this time-step has valid normal configuration for negative helicity electron
     * \details Conditions for valid negative helicity electron:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle to the major normal: \f$-acos(\frac{\sqrt{3}}{3})\f$
     *  - all the color normals are perpendicular to each other right-handed configuration (\f$N_B = N_R \times N_G\f$)
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ELECTRON_N() const
    {
        return isValid_UnitVectors() &&                                          //
            equals(Vec3<T>::dot(normal, normalR), -electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), -electronDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), -electronDotNormalColor()) &&  //
            normalR.isPerpendicular(normalG) &&                                  //
            normalG.isPerpendicular(normalB) &&                                  //
            normalB.isPerpendicular(normalR) &&                                  //
            isNegative(spin) &&                                                  //
            normalB.equals(Vec3<T>::cross(normalR, normalG).normalized());       //
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-green up quark
     * \return \c true if this is valid normal configuration for positive helicity red-green up quark
     * \details Conditions for valid positive helicity red-green up quark:
     *  - all normals are unit vectors
     *  - red and green normals are at 45° with the major normal
     *  - blue normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 60°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_UP_RG_P() const
    {
        return isValid_UnitVectors() &&                                        //
            equals(Vec3<T>::dot(normal, normalR), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                 //
            equals(Vec3<T>::dot(normalR, normalG), T(0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                 //
            isPositive(spin) &&                                                //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-green up quark
     * \return \c true if this is valid normal configuration for negative helicity red-green up quark
     * \details Conditions for valid negative helicity red-green up quark:
     *  - all normals are unit vectors
     *  - red and green normals are at 45° with the major normal
     *  - blue normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 60°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_UP_RG_N() const
    {
        return isValid_UnitVectors() &&                                        //
            equals(Vec3<T>::dot(normal, normalR), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                 //
            equals(Vec3<T>::dot(normalR, normalG), T(0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                 //
            isNegative(spin) &&                                                //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-blue up quark
     * \return \c true if this is valid normal configuration for positive helicity red-blue up quark
     * \details Conditions for valid positive helicity red-blue up quark:
     *  - all normals are unit vectors
     *  - red and blue normals are at 45° with the major normal
     *  - green normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 60°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_UP_RB_P() const
    {
        return isValid_UnitVectors() &&                                        //
            equals(Vec3<T>::dot(normal, normalR), quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                 //
            equals(Vec3<T>::dot(normal, normalB), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalB, normalR), T(0.5)) &&                  //
            isPositive(spin) &&                                                //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-blue up quark
     * \return \c true if this is valid normal configuration for negative helicity red-blue up quark
     * \details Conditions for valid negative helicity red-blue up quark:
     *  - all normals are unit vectors
     *  - red and blue normals are at 45° with the major normal
     *  - green normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 60°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_UP_RB_N() const
    {
        return isValid_UnitVectors() &&                                        //
            equals(Vec3<T>::dot(normal, normalR), quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                 //
            equals(Vec3<T>::dot(normal, normalB), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalB, normalR), T(0.5)) &&                  //
            isNegative(spin) &&                                                //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green-blue up quark
     * \return \c true if this is valid normal configuration for positive helicity green-blue up quark
     * \details Conditions for valid positive helicity green-blue up quark:
     *  - all normals are unit vectors
     *  - green and blue normals are at 45° with the major normal
     *  - red normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 60°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_UP_GB_P() const
    {
        return isValid_UnitVectors() &&                                        //
            normal.isPerpendicular(normalR) &&                                 //
            equals(Vec3<T>::dot(normal, normalG), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalG, normalB), T(0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                 //
            isPositive(spin) &&                                                //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green-blue up quark
     * \return \c true if this is valid normal configuration for negative helicity green-blue up quark
     * \details Conditions for valid negative helicity green-blue up quark:
     *  - all normals are unit vectors
     *  - green and blue normals are at 45° with the major normal
     *  - red normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 60°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_UP_GB_N() const
    {
        return isValid_UnitVectors() &&                                        //
            normal.isPerpendicular(normalR) &&                                 //
            equals(Vec3<T>::dot(normal, normalG), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                 //
            equals(Vec3<T>::dot(normalG, normalB), T(0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                 //
            isNegative(spin) &&                                                //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-green anti-up quark
     * \return \c true if this is valid normal configuration for positive helicity red-green anti-up quark
     * \details Conditions for valid positive helicity red-green anti-up quark:
     *  - all normals are unit vectors
     *  - red and green normals are at 135° with the major normal
     *  - blue normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 60°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_UP_RG_P() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), -quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                  //
            equals(Vec3<T>::dot(normalR, normalG), T(0.5)) &&                   //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                  //
            isPositive(spin) &&                                                 //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-green anti-up quark
     * \return \c true if this is valid normal configuration for negative helicity red-green anti-up quark
     * \details Conditions for valid negative helicity red-green anti-up quark:
     *  - all normals are unit vectors
     *  - red and green normals are at 135° with the major normal
     *  - blue normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 60°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_UP_RG_N() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalG), -quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                  //
            equals(Vec3<T>::dot(normalR, normalG), T(0.5)) &&                   //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                  //
            isNegative(spin) &&                                                 //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-blue anti-up quark
     * \return \c true if this is valid normal configuration for positive helicity red-blue anti-up quark
     * \details Conditions for valid positive helicity red-blue anti-up quark:
     *  - all normals are unit vectors
     *  - red and blue normals are at 135° with the major normal
     *  - green normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 60°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_UP_RB_P() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), -quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                  //
            equals(Vec3<T>::dot(normal, normalB), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(0.5)) &&                   //
            isPositive(spin) &&                                                 //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-blue anti-up quark
     * \return \c true if this is valid normal configuration for negative helicity red-blue anti-up quark
     * \details Conditions for valid negative helicity red-blue anti-up quark:
     *  - all normals are unit vectors
     *  - red and blue normals are at 135° with the major normal
     *  - green normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 60°
     *  - Mutual angle in between green and blue normal is 120°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_UP_RB_N() const
    {
        return isValid_UnitVectors() &&                                         //
            equals(Vec3<T>::dot(normal, normalR), -quarkUpDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                  //
            equals(Vec3<T>::dot(normal, normalB), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalB, normalR), T(0.5)) &&                   //
            isNegative(spin) &&                                                 //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green-blue anti-up quark
     * \return \c true if this is valid normal configuration for positive helicity green-blue anti-up quark
     * \details Conditions for valid positive helicity green-blue anti-up quark:
     *  - all normals are unit vectors
     *  - green and blue normals are at 135° with the major normal
     *  - red normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 60°
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_UP_GB_P() const
    {
        return isValid_UnitVectors() &&                                         //
            normal.isPerpendicular(normalR) &&                                  //
            equals(Vec3<T>::dot(normal, normalG), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(0.5)) &&                   //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                  //
            isPositive(spin) &&                                                 //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green-blue anti-up quark
     * \return \c true if this is valid normal configuration for negative helicity green-blue anti-up quark
     * \details Conditions for valid negative helicity green-blue anti-up quark:
     *  - all normals are unit vectors
     *  - green and blue normals are at 135° with the major normal
     *  - red normal is perpendicular to the major normal
     *  - Mutual angle in between red and green normal is 120°
     *  - Mutual angle in between red and blue normal is 120°
     *  - Mutual angle in between green and blue normal is 60°
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_UP_GB_N() const
    {
        return isValid_UnitVectors() &&                                         //
            normal.isPerpendicular(normalR) &&                                  //
            equals(Vec3<T>::dot(normal, normalG), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normal, normalB), -quarkUpDotNormalColor()) &&  //
            equals(Vec3<T>::dot(normalR, normalG), T(-0.5)) &&                  //
            equals(Vec3<T>::dot(normalG, normalB), T(0.5)) &&                   //
            equals(Vec3<T>::dot(normalB, normalR), T(-0.5)) &&                  //
            isNegative(spin) &&                                                 //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red down quark
     * \return \c true if this is valid normal configuration for positive helicity red down quark
     * \details Conditions for valid positive helicity red down quark:
     *  - all normals are unit vectors
     *  - red normal is at 150° with the major normal
     *  - green and blue normals are perpendicular to the major normal
     *  - red normal is perpendicular to the green and blue normals
     *  - green and blue normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_DOWN_R_P() const
    {
        return isValid_UnitVectors() &&                                           //
            equals(Vec3<T>::dot(normal, normalR), -quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                    //
            normal.isPerpendicular(normalB) &&                                    //
            normalR.isPerpendicular(normalG) &&                                   //
            normalR.isPerpendicular(normalB) &&                                   //
            normalG.equals(-normalB) &&                                           //
            isPositive(spin) &&                                                   //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red down quark
     * \return \c true if this is valid normal configuration for negative helicity red down quark
     * \details Conditions for valid negative helicity red down quark:
     *  - all normals are unit vectors
     *  - red normal is at 150° with the major normal
     *  - green and blue normals are perpendicular to the major normal
     *  - red normal is perpendicular to the green and blue normals
     *  - green and blue normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_DOWN_R_N() const
    {
        return isValid_UnitVectors() &&                                           //
            equals(Vec3<T>::dot(normal, normalR), -quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                    //
            normal.isPerpendicular(normalB) &&                                    //
            normalR.isPerpendicular(normalG) &&                                   //
            normalR.isPerpendicular(normalB) &&                                   //
            normalG.equals(-normalB) &&                                           //
            isNegative(spin) &&                                                   //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green down quark
     * \return \c true if this is valid normal configuration for positive helicity green down quark
     * \details Conditions for valid positive helicity green down quark:
     *  - all normals are unit vectors
     *  - green normal is at 150° with the major normal
     *  - red and blue normals are perpendicular to the major normal
     *  - green normal is perpendicular to the red and blue normals
     *  - red and blue normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_DOWN_G_P() const
    {
        return isValid_UnitVectors() &&                                           //
            normal.isPerpendicular(normalR) &&                                    //
            equals(Vec3<T>::dot(normal, normalG), -quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                    //
            normalG.isPerpendicular(normalR) &&                                   //
            normalG.isPerpendicular(normalB) &&                                   //
            normalR.equals(-normalB) &&                                           //
            isPositive(spin) &&                                                   //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalG, normalB)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green down quark
     * \return \c true if this is valid normal configuration for negative helicity green down quark
     * \details Conditions for valid negative helicity green down quark:
     *  - all normals are unit vectors
     *  - green normal is at 150° with the major normal
     *  - red and blue normals are perpendicular to the major normal
     *  - green normal is perpendicular to the red and blue normals
     *  - red and blue normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_DOWN_G_N() const
    {
        return isValid_UnitVectors() &&                                           //
            normal.isPerpendicular(normalR) &&                                    //
            equals(Vec3<T>::dot(normal, normalG), -quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                    //
            normalG.isPerpendicular(normalR) &&                                   //
            normalG.isPerpendicular(normalB) &&                                   //
            normalR.equals(-normalB) &&                                           //
            isNegative(spin) &&                                                   //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalG, normalB)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity blue down quark
     * \return \c true if this is valid normal configuration for positive helicity blue down quark
     * \details Conditions for valid positive helicity blue down quark:
     *  - all normals are unit vectors
     *  - blue normal is at 150° with the major normal
     *  - red and green normals are perpendicular to the major normal
     *  - blue normal is perpendicular to the red and green normals
     *  - red and green normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_QUARK_DOWN_B_P() const
    {
        return isValid_UnitVectors() &&                                           //
            normal.isPerpendicular(normalR) &&                                    //
            normal.isPerpendicular(normalG) &&                                    //
            equals(Vec3<T>::dot(normal, normalB), -quarkDownDotNormalColor()) &&  //
            normalB.isPerpendicular(normalR) &&                                   //
            normalB.isPerpendicular(normalG) &&                                   //
            normalR.equals(-normalG) &&                                           //
            isPositive(spin) &&                                                   //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalB, normalR)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity blue down quark
     * \return \c true if this is valid normal configuration for negative helicity blue down quark
     * \details Conditions for valid negative helicity blue down quark:
     *  - all normals are unit vectors
     *  - blue normal is at 150° with the major normal
     *  - red and green normals are perpendicular to the major normal
     *  - blue normal is perpendicular to the red and green normals
     *  - red and green normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_QUARK_DOWN_B_N() const
    {
        return isValid_UnitVectors() &&                                           //
            normal.isPerpendicular(normalR) &&                                    //
            normal.isPerpendicular(normalG) &&                                    //
            equals(Vec3<T>::dot(normal, normalB), -quarkDownDotNormalColor()) &&  //
            normalB.isPerpendicular(normalR) &&                                   //
            normalB.isPerpendicular(normalG) &&                                   //
            normalR.equals(-normalG) &&                                           //
            isNegative(spin) &&                                                   //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalB, normalR)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red anti-down quark
     * \return \c true if this is valid normal configuration for positive helicity red anti-down quark
     * \details Conditions for valid positive helicity red anti-down quark:
     *  - all normals are unit vectors
     *  - red normal is at 30° with the major normal
     *  - green and blue normals are perpendicular to the major normal
     *  - red normal is perpendicular to the green and blue normals
     *  - green and blue normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_DOWN_R_P() const
    {
        return isValid_UnitVectors() &&                                          //
            equals(Vec3<T>::dot(normal, normalR), quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                   //
            normal.isPerpendicular(normalB) &&                                   //
            normalR.isPerpendicular(normalG) &&                                  //
            normalR.isPerpendicular(normalB) &&                                  //
            normalG.equals(-normalB) &&                                          //
            isPositive(spin) &&                                                  //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red anti-down quark
     * \return \c true if this is valid normal configuration for negative helicity red anti-down quark
     * \details Conditions for valid negative helicity red anti-down quark:
     *  - all normals are unit vectors
     *  - red normal is at 30° with the major normal
     *  - green and blue normals are perpendicular to the major normal
     *  - red normal is perpendicular to the green and blue normals
     *  - green and blue normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_DOWN_R_N() const
    {
        return isValid_UnitVectors() &&                                          //
            equals(Vec3<T>::dot(normal, normalR), quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalG) &&                                   //
            normal.isPerpendicular(normalB) &&                                   //
            normalR.isPerpendicular(normalG) &&                                  //
            normalR.isPerpendicular(normalB) &&                                  //
            normalG.equals(-normalB) &&                                          //
            isNegative(spin) &&                                                  //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green anti-down quark
     * \return \c true if this is valid normal configuration for positive helicity green anti-down quark
     * \details Conditions for valid positive helicity green anti-down quark:
     *  - all normals are unit vectors
     *  - green normal is at 30° with the major normal
     *  - red and blue normals are perpendicular to the major normal
     *  - green normal is perpendicular to the red and blue normals
     *  - red and blue normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_DOWN_G_P() const
    {
        return isValid_UnitVectors() &&                                          //
            normal.isPerpendicular(normalR) &&                                   //
            equals(Vec3<T>::dot(normal, normalG), quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                   //
            normalG.isPerpendicular(normalR) &&                                  //
            normalG.isPerpendicular(normalB) &&                                  //
            normalR.equals(-normalB) &&                                          //
            isPositive(spin) &&                                                  //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalG, normalB)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green anti-down quark
     * \return \c true if this is valid normal configuration for negative helicity green anti-down quark
     * \details Conditions for valid negative helicity green anti-down quark:
     *  - all normals are unit vectors
     *  - green normal is at 30° with the major normal
     *  - red and blue normals are perpendicular to the major normal
     *  - green normal is perpendicular to the red and blue normals
     *  - red and blue normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_DOWN_G_N() const
    {
        return isValid_UnitVectors() &&                                          //
            normal.isPerpendicular(normalR) &&                                   //
            equals(Vec3<T>::dot(normal, normalG), quarkDownDotNormalColor()) &&  //
            normal.isPerpendicular(normalB) &&                                   //
            normalG.isPerpendicular(normalR) &&                                  //
            normalG.isPerpendicular(normalB) &&                                  //
            normalR.equals(-normalB) &&                                          //
            isNegative(spin) &&                                                  //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalG, normalB)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity blue anti-down quark
     * \return \c true if this is valid normal configuration for positive helicity blue anti-down quark
     * \details Conditions for valid positive helicity blue anti-down quark:
     *  - all normals are unit vectors
     *  - blue normal is at 30° with the major normal
     *  - red and green normals are perpendicular to the major normal
     *  - blue normal is perpendicular to the red and green normals
     *  - red and green normals are opposite vectors
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_ANTI_DOWN_B_P() const
    {
        return isValid_UnitVectors() &&                                          //
            normal.isPerpendicular(normalR) &&                                   //
            normal.isPerpendicular(normalG) &&                                   //
            equals(Vec3<T>::dot(normal, normalB), quarkDownDotNormalColor()) &&  //
            normalB.isPerpendicular(normalR) &&                                  //
            normalB.isPerpendicular(normalG) &&                                  //
            normalR.equals(-normalG) &&                                          //
            isPositive(spin) &&                                                  //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalB, normalR)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity blue anti-down quark
     * \return \c true if this is valid normal configuration for negative helicity blue anti-down quark
     * \details Conditions for valid negative helicity blue anti-down quark:
     *  - all normals are unit vectors
     *  - blue normal is at 30° with the major normal
     *  - red and green normals are perpendicular to the major normal
     *  - blue normal is perpendicular to the red and green normals
     *  - red and green normals are opposite vectors
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_ANTI_DOWN_B_N() const
    {
        return isValid_UnitVectors() &&                                          //
            normal.isPerpendicular(normalR) &&                                   //
            normal.isPerpendicular(normalG) &&                                   //
            equals(Vec3<T>::dot(normal, normalB), quarkDownDotNormalColor()) &&  //
            normalB.isPerpendicular(normalR) &&                                  //
            normalB.isPerpendicular(normalG) &&                                  //
            normalR.equals(-normalG) &&                                          //
            isNegative(spin) &&                                                  //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalB, normalR)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity photon
     * \return \c true if this is valid normal configuration for positive helicity photon
     * \note Photon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity photon:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle with the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_PHOTON_P() const
    {
        const T d = Vec3<T>::dot(normal, normalR);
        return isValid_UnitVectors() &&                  //
            equals(d, Vec3<T>::dot(normal, normalG)) &&  //
            equals(d, Vec3<T>::dot(normal, normalB)) &&  //
            isPositive(spin) &&                          //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity photon
     * \return \c true if this is valid normal configuration for negative helicity photon
     * \note Photon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity photon:
     *  - all normals are unit vectors
     *  - all color normals are at the same angle with the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_PHOTON_N() const
    {
        const T d = Vec3<T>::dot(normal, normalR);
        return isValid_UnitVectors() &&                  //
            equals(d, Vec3<T>::dot(normal, normalG)) &&  //
            equals(d, Vec3<T>::dot(normal, normalB)) &&  //
            isNegative(spin) &&                          //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-green gluon
     * \return \c true if this is valid normal configuration for positive helicity red-green gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity red-green gluon:
     *  - all normals are unit vectors
     *  - red and green normals are perpendicular each other
     *  - red normal is at 45° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 135° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_RG_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalG) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.r, quarkUpDotNormalColor()) && isNull(d.g) && isPositive(d.b)) ||  //
             (isNull(d.r) && equals(d.g, -quarkUpDotNormalColor()) && isNegative(d.b)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-green gluon
     * \return \c true if this is valid normal configuration for negative helicity red-green gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity red-green gluon:
     *  - all normals are unit vectors
     *  - red and green normals are perpendicular each other
     *  - red normal is at 45° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 135° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_RG_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalG) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.r, quarkUpDotNormalColor()) && isNull(d.g) && isPositive(d.b)) ||  //
             (isNull(d.r) && equals(d.g, -quarkUpDotNormalColor()) && isNegative(d.b)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity red-blue gluon
     * \return \c true if this is valid normal configuration for positive helicity red-blue gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity red-blue gluon:
     *  - all normals are unit vectors
     *  - red and blue normals are perpendicular each other
     *  - red normal is at 45° to the major normal and blue normal is perpendicular to the major normal \b or
     *    blue normal is at 135° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_RB_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalB) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.r, quarkUpDotNormalColor()) && isNull(d.b) && isPositive(d.g)) ||  //
             (isNull(d.r) && equals(d.b, -quarkUpDotNormalColor()) && isNegative(d.g)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity red-blue gluon
     * \return \c true if this is valid normal configuration for negative helicity red-blue gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity red-blue gluon:
     *  - all normals are unit vectors
     *  - red and blue normals are perpendicular each other
     *  - red normal is at 45° to the major normal and blue normal is perpendicular to the major normal \b or
     *    blue normal is at 135° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_RB_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalB) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.r, quarkUpDotNormalColor()) && isNull(d.b) && isPositive(d.g)) ||  //
             (isNull(d.r) && equals(d.b, -quarkUpDotNormalColor()) && isNegative(d.g)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green-red gluon
     * \return \c true if this is valid normal configuration for positive helicity green-red gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity green-red gluon:
     *  - all normals are unit vectors
     *  - red and green normals are perpendicular each other
     *  - red normal is at 135° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 45° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_GR_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalG) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.g, quarkUpDotNormalColor()) && isNull(d.r) && isPositive(d.b)) ||  //
             (isNull(d.g) && equals(d.r, -quarkUpDotNormalColor()) && isNegative(d.b)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green-red gluon
     * \return \c true if this is valid normal configuration for negative helicity green-red gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity green-red gluon:
     *  - all normals are unit vectors
     *  - red and green normals are perpendicular each other
     *  - red normal is at 135° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 45° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_GR_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalG) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.g, quarkUpDotNormalColor()) && isNull(d.r) && isPositive(d.b)) ||  //
             (isNull(d.g) && equals(d.r, -quarkUpDotNormalColor()) && isNegative(d.b)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity green-blue gluon
     * \return \c true if this is valid normal configuration for positive helicity green-blue gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity green-blue gluon:
     *  - all normals are unit vectors
     *  - green and blue normals are perpendicular each other
     *  - blue normal is at 135° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 45° to the major normal and blue normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_GB_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalG.isPerpendicular(normalB) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.g, quarkUpDotNormalColor()) && isNull(d.b) && isPositive(d.r)) ||  //
             (isNull(d.g) && equals(d.b, -quarkUpDotNormalColor()) && isNegative(d.r)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity green-blue gluon
     * \return \c true if this is valid normal configuration for negative helicity green-blue gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity green-blue gluon:
     *  - all normals are unit vectors
     *  - green and blue normals are perpendicular each other
     *  - blue normal is at 135° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 45° to the major normal and blue normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_GB_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalG.isPerpendicular(normalB) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.g, quarkUpDotNormalColor()) && isNull(d.b) && isPositive(d.r)) ||  //
             (isNull(d.g) && equals(d.b, -quarkUpDotNormalColor()) && isNegative(d.r)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity blue-red gluon
     * \return \c true if this is valid normal configuration for positive helicity blue-red gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity blue-red gluon:
     *  - all normals are unit vectors
     *  - red and blue normals are perpendicular each other
     *  - red normal is at 135° to the major normal and blue normal is perpendicular to the major normal \b or
     *    blue normal is at 45° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_BR_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalB) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.b, quarkUpDotNormalColor()) && isNull(d.r) && isPositive(d.g)) ||  //
             (isNull(d.b) && equals(d.r, -quarkUpDotNormalColor()) && isNegative(d.g)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity blue-red gluon
     * \return \c true if this is valid normal configuration for negative helicity blue-red gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity blue-red gluon:
     *  - all normals are unit vectors
     *  - red and blue normals are perpendicular each other
     *  - red normal is at 135° to the major normal and blue normal is perpendicular to the major normal \b or
     *    blue normal is at 45° to the major normal and red normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_BR_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalR.isPerpendicular(normalB) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.b, quarkUpDotNormalColor()) && isNull(d.r) && isPositive(d.g)) ||  //
             (isNull(d.b) && equals(d.r, -quarkUpDotNormalColor()) && isNegative(d.g)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for positive helicity blue-green gluon
     * \return \c true if this is valid normal configuration for positive helicity blue-green gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid positive helicity blue-green gluon:
     *  - all normals are unit vectors
     *  - green and blue normals are perpendicular each other
     *  - blue normal is at 45° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 135° to the major normal and blue normal is perpendicular to the major normal
     *  - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has positive value
     */
    inline bool isValid_GLUON_BG_P() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalG.isPerpendicular(normalB) &&                                           //
            isPositive(spin) &&                                                           //
            isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.b, quarkUpDotNormalColor()) && isNull(d.g) && isPositive(d.r)) ||  //
             (isNull(d.b) && equals(d.g, -quarkUpDotNormalColor()) && isNegative(d.r)));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative helicity blue-green gluon
     * \return \c true if this is valid normal configuration for negative helicity blue-green gluon
     * \note Gluon is a boson made from two "fermionic" configurations.
     * \details Conditions for valid negative helicity blue-green gluon:
     *  - all normals are unit vectors
     *  - green and blue normals are perpendicular each other
     *  - blue normal is at 45° to the major normal and green normal is perpendicular to the major normal \b or
     *    green normal is at 135° to the major normal and blue normal is perpendicular to the major normal
     *  - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *  - \a spin has negative value
     */
    inline bool isValid_GLUON_BG_N() const
    {
        const Vec3<T> d = getDotRGB();
        return isValid_UnitVectors() &&                                                   //
            normalG.isPerpendicular(normalB) &&                                           //
            isNegative(spin) &&                                                           //
            isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG))) &&         //
            ((equals(d.b, quarkUpDotNormalColor()) && isNull(d.g) && isPositive(d.r)) ||  //
             (isNull(d.b) && equals(d.g, -quarkUpDotNormalColor()) && isNegative(d.r)));
    }

    //

    /*!
     * \brief Return \c true if this is valid normal configuration for positive W boson
     * \return \c true if this is valid normal configuration for positive W boson
     * \note Positive W boson is made from two "fermionic" configurations.
     * \details Conditions for valid positive W boson:
     *  - all normals are unit vectors
     *  - Conditions for the \b first configuration:
     *    - all color normals are at the same angle to the major normal: \f$acos(\frac{\sqrt{3}}{3})\f$
     *    - all the color normals are perpendicular to each other right-handed config (\f$N_B = N_R \times N_G\f$)
     *    - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has positive value
     *  - Conditions for the \b second configuration:
     *    - all color normals are perpendicular to the major normal
     *    - all the mutual angle in between color normals are equal to 120°
     *    - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has negative value
     */
    inline bool isValid_BOSON_W_P() const
    {
        const Vec3<T> d = getDotRGB();
        const Vec3<T> e = getDotRG_GB_BR();

        return isValid_UnitVectors() &&
            ((equals(d.r, electronDotNormalColor()) &&  //
              equals(d.g, electronDotNormalColor()) &&  //
              equals(d.b, electronDotNormalColor()) &&  //
              isNull(e.r) &&                            //
              isNull(e.g) &&                            //
              isNull(e.b) &&                            //
              isPositive(spin) &&                       //
              normalB.equals(Vec3<T>::cross(normalR, normalG).normalized())) ||
             (isNull(d.r) &&           //
              isNull(d.g) &&           //
              isNull(d.b) &&           //
              equals(e.r, T(-0.5)) &&  //
              equals(e.g, T(-0.5)) &&  //
              equals(e.b, T(-0.5)) &&  //
              isNegative(spin) &&      //
              isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)))));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for negative W boson
     * \return \c true if this is valid normal configuration for negative W boson
     * \note Negative W boson is made from two "fermionic" configurations.
     * \details Conditions for valid negative W boson:
     *  - all normals are unit vectors
     *  - Conditions for the \b first configuration:
     *    - all color normals are at the same angle to the major normal: \f$-acos(\frac{\sqrt{3}}{3})\f$
     *    - all the color normals are perpendicular to each other right-handed config (\f$N_B = N_R \times N_G\f$)
     *    - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has negative value
     *  - Conditions for the \b second configuration:
     *    - all color normals are perpendicular to the major normal
     *    - all the mutual angle in between color normals are equal to 120°
     *    - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has positive value
     */
    inline bool isValid_BOSON_W_N() const
    {
        const Vec3<T> d = getDotRGB();
        const Vec3<T> e = getDotRG_GB_BR();

        return isValid_UnitVectors() &&
            ((equals(d.r, -electronDotNormalColor()) &&  //
              equals(d.g, -electronDotNormalColor()) &&  //
              equals(d.b, -electronDotNormalColor()) &&  //
              isNull(e.r) &&                             //
              isNull(e.g) &&                             //
              isNull(e.b) &&                             //
              isNegative(spin) &&                        //
              normalB.equals(Vec3<T>::cross(normalR, normalG).normalized())) ||
             (isNull(d.r) &&           //
              isNull(d.g) &&           //
              isNull(d.b) &&           //
              equals(e.r, T(-0.5)) &&  //
              equals(e.g, T(-0.5)) &&  //
              equals(e.b, T(-0.5)) &&  //
              isPositive(spin) &&      //
              isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)))));
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for red Z boson
     * \return \c true if this is valid normal configuration for red Z boson
     * \note Red Z boson is made from two "fermionic" configurations with opposing red normals.
     * \details Conditions for valid red Z boson:
     *  - all normals are unit vectors
     *  - Conditions for the \b first configuration:
     *    - red normal has positive helicity
     *    - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has positive value
     *  - Conditions for the \b second configuration:
     *    - red normal has negative helicity
     *    - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has negative value
     */
    inline bool isValid_BOSON_Z_R() const
    {
        const T r = Vec3<T>::dot(normal, normalR);
        if (isPositive(r))
            return isValid_UnitVectors() &&  //
                isPositive(spin) &&          //
                isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        if (isNegative(r))
            return isValid_UnitVectors() &&  //
                isNegative(spin) &&          //
                isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        return false;
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for green Z boson
     * \return \c true if this is valid normal configuration for green Z boson
     * \note Red Z boson is made from two "fermionic" configurations with opposing green normals.
     * \details Conditions for valid green Z boson:
     *  - all normals are unit vectors
     *  - Conditions for the \b first configuration:
     *    - green normal has positive helicity
     *    - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has positive value
     *  - Conditions for the \b second configuration:
     *    - green normal has negative helicity
     *    - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has negative value
     */
    inline bool isValid_BOSON_Z_G() const
    {
        const T g = Vec3<T>::dot(normal, normalG);
        if (isPositive(g))
            return isValid_UnitVectors() &&  //
                isPositive(spin) &&          //
                isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        if (isNegative(g))
            return isValid_UnitVectors() &&  //
                isNegative(spin) &&          //
                isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        return false;
    }

    /*!
     * \brief Return \c true if this is valid normal configuration for blue Z boson
     * \return \c true if this is valid normal configuration for blue Z boson
     * \note Red Z boson is made from two "fermionic" configurations with opposing blue normals.
     * \details Conditions for valid blue Z boson:
     *  - all normals are unit vectors
     *  - Conditions for the \b first configuration:
     *    - blue normal has positive helicity
     *    - color normals appears in counter-clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has positive value
     *  - Conditions for the \b second configuration:
     *    - blue normal has negative helicity
     *    - color normals appears in clockwise red-green-blue order when observing from major normal direction
     *    - \a spin has negative value
     */
    inline bool isValid_BOSON_Z_B() const
    {
        const T b = Vec3<T>::dot(normal, normalB);
        if (isPositive(b))
            return isValid_UnitVectors() &&  //
                isPositive(spin) &&          //
                isPositive(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        if (isNegative(b))
            return isValid_UnitVectors() &&  //
                isNegative(spin) &&          //
                isNegative(Vec3<T>::dot(normal, Vec3<T>::cross(normalR, normalG)));
        return false;
    }

    //

    /*!
     * \brief Test if this time-step is valid
     * \return \c true if this particle time-step has valid configuration of vectors
     */
    bool isValid() const
    {
        switch (type)
        {
        case U1_NEUTRINO_P: return isValid_NEUTRINO_P();
        case U1_NEUTRINO_N: return isValid_NEUTRINO_N();

        case U1_POSITRON_P: return isValid_POSITRON_P();
        case U1_POSITRON_N: return isValid_POSITRON_N();

        case U1_ELECTRON_P: return isValid_ELECTRON_P();
        case U1_ELECTRON_N: return isValid_ELECTRON_N();

        case U1_QUARK_UP_RG_P: return isValid_QUARK_UP_RG_P();
        case U1_QUARK_UP_RG_N: return isValid_QUARK_UP_RG_N();
        case U1_QUARK_UP_RB_P: return isValid_QUARK_UP_RB_P();
        case U1_QUARK_UP_RB_N: return isValid_QUARK_UP_RB_N();
        case U1_QUARK_UP_GB_P: return isValid_QUARK_UP_GB_P();
        case U1_QUARK_UP_GB_N: return isValid_QUARK_UP_GB_N();

        case U1_ANTI_UP_RG_P: return isValid_ANTI_UP_RG_P();
        case U1_ANTI_UP_RG_N: return isValid_ANTI_UP_RG_N();
        case U1_ANTI_UP_RB_P: return isValid_ANTI_UP_RB_P();
        case U1_ANTI_UP_RB_N: return isValid_ANTI_UP_RB_N();
        case U1_ANTI_UP_GB_P: return isValid_ANTI_UP_GB_P();
        case U1_ANTI_UP_GB_N: return isValid_ANTI_UP_GB_N();

        case U1_QUARK_DOWN_R_P: return isValid_QUARK_DOWN_R_P();
        case U1_QUARK_DOWN_R_N: return isValid_QUARK_DOWN_R_N();
        case U1_QUARK_DOWN_G_P: return isValid_QUARK_DOWN_G_P();
        case U1_QUARK_DOWN_G_N: return isValid_QUARK_DOWN_G_N();
        case U1_QUARK_DOWN_B_P: return isValid_QUARK_DOWN_B_P();
        case U1_QUARK_DOWN_B_N: return isValid_QUARK_DOWN_B_N();

        case U1_ANTI_DOWN_R_P: return isValid_ANTI_DOWN_R_P();
        case U1_ANTI_DOWN_R_N: return isValid_ANTI_DOWN_R_N();
        case U1_ANTI_DOWN_G_P: return isValid_ANTI_DOWN_G_P();
        case U1_ANTI_DOWN_G_N: return isValid_ANTI_DOWN_G_N();
        case U1_ANTI_DOWN_B_P: return isValid_ANTI_DOWN_B_P();
        case U1_ANTI_DOWN_B_N: return isValid_ANTI_DOWN_B_N();

        case U1_PHOTON_P: return isValid_PHOTON_P();
        case U1_PHOTON_N: return isValid_PHOTON_N();

        case U1_GLUON_RG_P: return isValid_GLUON_RG_P();
        case U1_GLUON_RG_N: return isValid_GLUON_RG_N();
        case U1_GLUON_RB_P: return isValid_GLUON_RB_P();
        case U1_GLUON_RB_N: return isValid_GLUON_RB_N();

        case U1_GLUON_GR_P: return isValid_GLUON_GR_P();
        case U1_GLUON_GR_N: return isValid_GLUON_GR_N();
        case U1_GLUON_GB_P: return isValid_GLUON_GB_P();
        case U1_GLUON_GB_N: return isValid_GLUON_GB_N();

        case U1_GLUON_BR_P: return isValid_GLUON_BR_P();
        case U1_GLUON_BR_N: return isValid_GLUON_BR_N();
        case U1_GLUON_BG_P: return isValid_GLUON_BG_P();
        case U1_GLUON_BG_N: return isValid_GLUON_BG_N();

        case U1_BOSON_W_R_P:
        case U1_BOSON_W_G_P:
        case U1_BOSON_W_B_P: return isValid_BOSON_W_P();

        case U1_BOSON_W_R_N:
        case U1_BOSON_W_G_N:
        case U1_BOSON_W_B_N: return isValid_BOSON_W_N();

        case U1_BOSON_Z_R: return isValid_BOSON_Z_R();
        case U1_BOSON_Z_G: return isValid_BOSON_Z_G();
        case U1_BOSON_Z_B: return isValid_BOSON_Z_B();

        default: break;
        }
        return false;
    }
};

/*!
 * \brief Tool class for particle path calculation
 * \tparam T Template floating point type
 */
template <typename T>
class ParticleBuild
{
 public:
    uint8_t type = 0U;  //!< Particle type
    size_t ID = 0UL;    //!< Particle ID

    size_t parent1 = U1_NULL_ID;  //!< First parent particle ID
    size_t parent2 = U1_NULL_ID;  //!< Second parent particle ID
    size_t child1 = U1_NULL_ID;   //!< First child particle ID
    size_t child2 = U1_NULL_ID;   //!< Second child particle ID

    std::list<TimeStep<T>> path;  //!< Particle path

    /*!
     * \brief Test if this particle has parent particle with given ID
     * \param _id Parent particle ID
     * \return \c true if this particle has parent particle with given ID
     */
    inline bool hasParent(const size_t _id) const
    {
        return parent1 == _id || parent2 == _id;
    }

    /*!
     * \brief Test if this particle decays to child particle with given ID
     * \param _id Child particle ID
     * \return \c true if this particle decays to child particle with given ID
     */
    inline bool hasChild(const size_t _id) const
    {
        return child1 == _id || child2 == _id;
    }
};

/*!
 * \brief Single particle lifetime stored time-steps
 * \tparam T Template floating point type
 */
template <typename T>
class ParticlePath
{
 public:
    uint8_t type = 0U;       //!< Particle type
    size_t ID = 0UL;         //!< Particle ID
    size_t stepCount = 0UL;  //!< Number of stored time-steps

    size_t parent1 = U1_NULL_ID;  //!< First parent particle ID
    size_t parent2 = U1_NULL_ID;  //!< Second parent particle ID
    size_t child1 = U1_NULL_ID;   //!< First child particle ID
    size_t child2 = U1_NULL_ID;   //!< Second child particle ID

    TimeStep<T> *path = nullptr;  //!< Particle path

    virtual ~ParticlePath()  //!< Destructor
    {
        if (path != nullptr)
            std::free(path);
    }

    /*!
     * \brief Save data into file
     * \param _ofs File stream
     * \return Success flag
     */
    bool save(std::ofstream &_ofs) const
    {
        _ofs << type;
        _ofs << ID;
        _ofs << stepCount;
        _ofs << parent1;
        _ofs << parent2;
        _ofs << child1;
        _ofs << child1;

        if (path != nullptr)
        {
            for (size_t i = 0UL; i < stepCount; ++i)
                if (!path[i].save(_ofs))
                    return false;
        }

        return true;
    }

    /*!
     * \brief Load data from file
     * \param _ifs File stream
     * \return Success flag
     */
    bool load(std::ifstream &_ifs)
    {
        _ifs >> type;
        _ifs >> ID;
        _ifs >> stepCount;
        _ifs >> parent1;
        _ifs >> parent2;
        _ifs >> child1;
        _ifs >> child1;

        if (stepCount > 0UL)
        {
            if (path != nullptr)
                std::free(path);

            path = reinterpret_cast<TimeStep<T> *>(std::malloc(stepCount * sizeof(TimeStep<T>)));

            for (size_t i = 0UL; i < stepCount; ++i)
                if (!path[i].load(_ifs))
                    return false;
        }
        return true;
    }
};

}  // namespace Universe1

/*!
 * \brief The Universe1 simulation processor
 * \tparam T Template floating point type
 */
template <typename T>
class PhysicsUniverse1
{
 public:
    size_t dataHash = 0UL;        //!< Simulation data hash value
    size_t countParticles = 0UL;  //!< Number of objects in the simulation

    T minimalTimeStep = T(0);  //!< Oldest time-step within the initial particle history
    T initialTimeStep = T(0);  //!< Initial calculation time-step
    T maximalTimeStep = T(0);  //!< Youngest calculated time-step

    Universe1::ParticlePath<T> **particles = nullptr;  //!< Particles

    virtual ~PhysicsUniverse1()  //!< Destructor
    {
        if (particles != nullptr)
        {
            for (size_t i = 0UL; i < countParticles; ++i)
                delete particles[i];
            std::free(particles);
        }
    }

    /*!
     * \brief Save simulation data into file
     * \param _fileName File name
     * \return Success flag
     */
    bool save(const std::string &_fileName) const
    {
        if (_fileName.empty())
        {
            std::cerr << "PhysicsUniverse1::save(): Empty file name!\n";
            return false;
        }

        std::ofstream ofs(_fileName, std::ios::binary);
        if (!ofs.is_open())
        {
            std::cerr << "PhysicsUniverse1::save(): Can't write into file:" << _fileName << "!\n";
            return false;
        }

        ofs << dataHash;
        ofs << countParticles;
        ofs << minimalTimeStep;
        ofs << initialTimeStep;
        ofs << maximalTimeStep;

        for (size_t i = 0UL; i < countParticles; ++i)
            if (!particles[i]->save(ofs))
            {
                ofs.close();
                return false;
            }

        ofs.close();

        return true;
    }

    /*!
     * \brief Load simulation data from file
     * \param _fileName File name
     * \return Success flag
     */
    bool load(const std::string &_fileName)
    {
        if (_fileName.empty())
        {
            std::cerr << "PhysicsUniverse1::load(): Empty file name!\n";
            return false;
        }

        std::ifstream ifs(_fileName, std::ios::binary);
        if (!ifs.is_open())
        {
            std::cerr << "PhysicsUniverse1::load(): Can't load file:" << _fileName << "!\n";
            return false;
        }

        if (particles != nullptr)
        {
            for (size_t i = 0UL; i < countParticles; ++i)
                delete particles[i];
            std::free(particles);
            particles = nullptr;
        }

        ifs >> dataHash;
        ifs >> countParticles;
        ifs >> minimalTimeStep;
        ifs >> initialTimeStep;
        ifs >> maximalTimeStep;

        bool result = true;
        if (countParticles > 0UL)
        {
            particles = reinterpret_cast<Universe1::ParticlePath<T> **>(
                std::malloc(countParticles * sizeof(Universe1::ParticlePath<T> *)));

            for (size_t i = 0UL; i < countParticles; ++i)
            {
                particles[i] = new Universe1::ParticlePath<T>();
                if (!particles[i]->load(ifs))
                    result = false;
            }
        }

        ifs.close();

        return result;
    }

    /*!
     * \brief Build simulation
     * \param _dataHash Data hash value
     * \param _initialPaths Initial particle paths
     * \param _timeStop Time-step when stop and finish the calculation (in seconds)
     * \param _timeStep Single time-step duration (in seconds)
     * \return Success flag
     */
    bool build(const size_t _dataHash,
               const std::vector<Universe1::ParticleBuild<T>> &_initialPaths,
               const T _timeStop,
               const T _timeStep);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool PhysicsUniverse1<T>::build(const size_t _dataHash,
                                const std::vector<Universe1::ParticleBuild<T>> &_initialPaths,
                                const T _timeStop,
                                const T _timeStep)
{
    using namespace Universe1;

    if (_initialPaths.empty() || !isPositive(_timeStep))
    {
        std::cerr << "PhysicsUniverse1::build(): Invalid input data!\n";
        return false;
    }

    if (particles != nullptr)
    {
        std::cerr << "Warning: PhysicsUniverse1::build(): Erasing old simulation data!\n";
        for (size_t i = 0UL; i < countParticles; ++i)
            delete particles[i];
        std::free(particles);
        particles = nullptr;
    }

    bool isMin = false, isInit = false;
    std::list<ParticleBuild<T>> tmp;

    for (const ParticleBuild<T> &pb : std::as_const(_initialPaths))
    {
        if (pb.ID != tmp.size())
        {
            std::cerr << "PhysicsUniverse1::build(): Invalid object ID: " << pb.ID << ", not follow the order!\n";
            return false;
        }

        if (pb.path.size() < 2UL || isLessOrEqual(pb.path.back().time, pb.path.front().time))
        {
            std::cerr << "PhysicsUniverse1::build(): Empty object[" << pb.ID << "] input path!\n";
            return false;
        }

        typename std::list<TimeStep<T>>::const_iterator i1 = pb.path.cbegin();
        typename std::list<TimeStep<T>>::const_iterator i2 = pb.path.cbegin();
        i2++;

        for (; i2 != pb.path.cend(); ++i1, ++i2)
            if (isLessOrEqual((*i2).time, (*i1).time))
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid path time-step order!\n";
                return false;
            }

        const bool isParent = pb.parent1 != U1_NULL_ID;
        if (!isParent && pb.parent2 != U1_NULL_ID)
        {
            std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid parent IDs!\n";
            return false;
        }

        if (isParent)
        {
            if (pb.parent1 >= _initialPaths.size() || pb.parent1 == pb.ID)
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid parent1 ID!\n";
                return false;
            }

            const ParticleBuild<T> &ppb1 = _initialPaths.at(pb.parent1);
            if (!equals(pb.path.front().time, ppb1.path.back().time) || !ppb1.hasChild(pb.ID))
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid connection parent1 object["
                          << pb.parent1 << "]!\n";
                return false;
            }

            if (pb.parent2 != U1_NULL_ID)
            {
                if (pb.parent2 >= _initialPaths.size() || pb.parent2 == pb.ID || pb.parent1 == pb.parent2)
                {
                    std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid parent2 ID!\n";
                    return false;
                }

                const ParticleBuild<T> &ppb2 = _initialPaths.at(pb.parent2);
                if (!equals(pb.path.front().time, ppb2.path.back().time) || !ppb2.hasChild(pb.ID))
                {
                    std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid connection parent2 object["
                              << pb.parent2 << "]!\n";
                    return false;
                }
            }
        }
        else
        {
            if (isMin == false)
            {
                minimalTimeStep = pb.path.front().time;
                isMin = true;
            }
            else
            {
                minimalTimeStep = std::min(minimalTimeStep, pb.path.front().time);
            }
        }

        const bool isChild = pb.child1 != U1_NULL_ID;
        if (isChild)
        {
            if (pb.child1 >= _initialPaths.size() || pb.child2 >= _initialPaths.size() || pb.child1 == pb.child2 ||
                pb.child1 == pb.ID || pb.child2 == pb.ID)
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid child IDs!\n";
                return false;
            }

            const ParticleBuild<T> &cpb1 = _initialPaths.at(pb.child1);
            const ParticleBuild<T> &cpb2 = _initialPaths.at(pb.child2);

            if (!equals(cpb1.path.front().time, pb.path.back().time) || !cpb1.hasParent(pb.ID))
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid connection child1 object["
                          << pb.child1 << "]!\n";
                return false;
            }

            if (!equals(cpb2.path.front().time, pb.path.back().time) || !cpb2.hasParent(pb.ID))
            {
                std::cerr << "PhysicsUniverse1::build(): Object[" << pb.ID << "] invalid connection child2 object["
                          << pb.child2 << "]!\n";
                return false;
            }
        }
        else
        {
            if (isInit == false)
            {
                initialTimeStep = pb.path.back().time;
                isInit = true;
            }
            else
            {
                if (!equals(initialTimeStep, pb.path.back().time))
                {
                    std::cerr << "PhysicsUniverse1::build(): Invalid input, invalid initial time !\n";
                    return false;
                }
            }
        }

        tmp.push_back(pb);
    }

    if (isMin == false || isInit == false)
    {
        std::cerr << "PhysicsUniverse1::build(): Invalid input timing!\n";
        return false;
    }

    if (isLessOrEqual(_timeStop, initialTimeStep))
    {
        std::cerr << "PhysicsUniverse1::build(): Invalid STOP time, must be higher than: " << initialTimeStep << "!\n";
        return false;
    }

    for (const ParticleBuild<T> &pb1 : std::as_const(_initialPaths))
    {
        if (pb1.child1 != U1_NULL_ID)
            continue;

        const T &t1 = pb1.path.back().time;
        const Vec3<T> &p1 = pb1.path.back().position;

        for (const ParticleBuild<T> &pb2 : std::as_const(_initialPaths))
        {
            if (pb2.parent1 != U1_NULL_ID)
                continue;

            const Vec3<T> &p2 = pb2.path.front().position;
            const T &t2 = pb2.path.front().time;
            const T waveDis = p1.distanceToPoint(p2);
            const T waveRadius = (t2 - t1) * TimeStep<T>::C1();

            if (isLessNotEqual(waveDis, waveRadius))
            {
                std::cerr << "PhysicsUniverse1::build(): Not enough history, input paths are short!\n";
                return false;
            }
        }
    }

    static const T _2PI = T(2.0l * M_PIl);
    static const T _2R1 = TimeStep<T>::R1() * T(2);
    static const T _V1 = T(M_PIl * 4.0l / 3.0l) * TimeStep<T>::R1() * TimeStep<T>::R1() * TimeStep<T>::R1();

    T tt = initialTimeStep;

    while (!isLessNotEqual(tt, _timeStop))
    {
        const T te = std::min(tt + _timeStep, _timeStop);
        const T dt = te - tt;
        if (!isPositive(dt))
            break;

        for (ParticleBuild<T> &pb1 : tmp)
        {
            if (pb1.child1 != U1_NULL_ID)
                continue;

            TimeStep<T> &ts1 = pb1.path.back();
            ts1.bodySpin1 = {};
            for (const ParticleBuild<T> &pb2 : std::as_const(tmp))
            {
                const TimeStep<T> &ts2B = pb2.path.back();
                const TimeStep<T> &ts2F = pb2.path.front();
                if (pb1.ID != pb2.ID && pb2.child1 != U1_NULL_ID)
                {
                    const T dist = ts1.position.distanceToPoint(ts2B.position);
                    // if (isLessOrEqual(dist, _2R1))
                    if (isLessNotEqual(dist, _2R1))
                    {
                        // Two particles are penetrating each other
                        const T h = TimeStep<T>::R1() - T(0.5) * dist;                     // Penetration height
                        const T V = _2PI * h * h * (T(3) * TimeStep<T>::R1() - h) / T(3);  // Cross-section volume
                        const T ratio = V / _V1;                                           // Cross-section volume ratio
                        const T X = TimeStep<T>::K1() * ratio;  // Cross-section volume multiplier

                        ts1.bodySpin1 += Vec3<T>::cross(ts2B.normal, ts1.normal) *
                            (X * Vec3<T>::dot(ts2B.normal, ts1.normal) / ts1.normal.lengthSquared());

                        if ((((ts1.type & U1_MASK_RED_P) != 0U) != ((ts1.type & U1_MASK_RED_N) != 0U)) &&
                            (((ts2B.type & U1_MASK_RED_P) != 0U) != ((ts2B.type & U1_MASK_RED_N) != 0U)))
                            ts1.bodySpin1 +=
                                Vec3<T>::cross(ts2B.normalR, ts1.normalR) * (X / ts1.normalR.lengthSquared());

                        if ((((ts1.type & U1_MASK_GREEN_P) != 0U) != ((ts1.type & U1_MASK_GREEN_N) != 0U)) &&
                            (((ts2B.type & U1_MASK_GREEN_P) != 0U) != ((ts2B.type & U1_MASK_GREEN_N) != 0U)))
                            ts1.bodySpin1 +=
                                Vec3<T>::cross(ts2B.normalG, ts1.normalG) * (X / ts1.normalG.lengthSquared());

                        if ((((ts1.type & U1_MASK_BLUE_P) != 0U) != ((ts1.type & U1_MASK_BLUE_N) != 0U)) &&
                            (((ts2B.type & U1_MASK_BLUE_P) != 0U) != ((ts2B.type & U1_MASK_BLUE_N) != 0U)))
                            ts1.bodySpin1 +=
                                Vec3<T>::cross(ts2B.normalB, ts1.normalB) * (X / ts1.normalB.lengthSquared());
                    }
                }

                const T waveRadiusF = (ts1.time - ts2F.time) * TimeStep<T>::C1();
                const T distF = ts1.position.distanceToPoint(ts2F.position);

                if (isLessNotEqual(waveRadiusF + TimeStep<T>::R1(), distF))
                {
                    if (pb2.parent1 == U1_NULL_ID)
                    {
                        std::cerr << "PhysicsUniverse1::build(): Missing a parent with history!\n";
                        return false;
                    }
                    continue;
                }

                const T waveRadiusB = (ts1.time - ts2B.time) * TimeStep<T>::C1();
                const T distB = ts1.position.distanceToPoint(ts2B.position);

                if (isMoreNotEqual(waveRadiusB - TimeStep<T>::R1(), distB))
                {
                    if (pb2.child1 == U1_NULL_ID)
                    {
                        std::cerr << "PhysicsUniverse1::build(): Missing a child with history!\n";
                        return false;
                    }
                    continue;
                }

                typename std::list<TimeStep<T>>::const_iterator i1 = pb2.path.cbegin();
                typename std::list<TimeStep<T>>::const_iterator iBeg = pb2.path.cend();
                typename std::list<TimeStep<T>>::const_iterator iEnd = pb2.path.cend();

                while (i1 != pb2.path.cend())
                {
                    const SphereCrossSection<T> scs(
                        ts1.position, (*i1).position, (tt - (*i1).time) * TimeStep<T>::C1(), TimeStep<T>::R1());

                    switch (scs.crossSectionType)
                    {
                    case CROSS_INVALID:
                        std::cerr << "PhysicsUniverse1::build(): Invalid sphere cross-section!\n";
                        return false;

                    case CROSS_WAVE_MISS_BEFORE:
                    case CROSS_WAVE_MISS_AFTER: break;

                    case CROSS_WAVE_TOUCH_BEFORE:
                    case CROSS_WAVE_CROSSES:
                    case CROSS_WAVE_TOUCH_AFTER: iBeg = i1; break;
                    }

                    if (iBeg != pb2.path.cend())
                        break;
                    ++i1;
                }

                if (iBeg != pb2.path.cend())
                {
                    std::cerr << "PhysicsUniverse1::build(): Invalid path begin!\n";
                    return false;
                }

                while (i1 != pb2.path.cend())
                {
                    const SphereCrossSection<T> scs(
                        ts1.position, (*i1).position, (tt - (*i1).time) * TimeStep<T>::C1(), TimeStep<T>::R1());

                    switch (scs.crossSectionType)
                    {
                    case CROSS_INVALID:
                        std::cerr << "PhysicsUniverse1::build(): Invalid sphere cross-section!\n";
                        return false;

                    case CROSS_WAVE_TOUCH_BEFORE:
                    case CROSS_WAVE_CROSSES:
                    case CROSS_WAVE_TOUCH_AFTER: break;

                    case CROSS_WAVE_MISS_BEFORE:
                    case CROSS_WAVE_MISS_AFTER: iEnd = i1; break;
                    }
                    if (iEnd != pb2.path.cend())
                        break;
                    ++i1;
                }

                i1 = iBeg;
                while (i1 != iEnd)
                {
                    const SphereCrossSection<T> scs(
                        ts1.position, (*i1).position, (tt - (*i1).time) * TimeStep<T>::C1(), TimeStep<T>::R1());

                    //

                    ++i1;
                }

                //
            }
        }

        tt = te;
    }

    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef PhysicsUniverse1<float> U1SimF;        //!< 32 bit floating point precision version
typedef PhysicsUniverse1<double> U1SimD;       //!< 64 bit floating point precision version
typedef PhysicsUniverse1<long double> U1SimL;  //!< 128 bit floating point precision version

}  // namespace Math
}  // namespace U1

#endif  // MATH_PHYSICSNEWTON_H
