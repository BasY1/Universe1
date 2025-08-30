/*!
 * \file src/Math/physicsuniverse1calculus.h
 * \brief The Universe1 physics calculus tools
 */

#ifndef MATH_PHYSICSUNIVERSE1CALCULUS_H
#define MATH_PHYSICSUNIVERSE1CALCULUS_H

#include "orientation.h"
#include "spherecrosssection.h"

namespace U1 {
namespace Math {

/*!
 * \namespace U1::Math::Universe1
 * \brief The Universe1 physics tools
 */
namespace Universe1 {
Q_NAMESPACE

// clang-format off

/*! \brief The particle type names */
enum ParticleType : int
{
    _ParticleInvalid   = 0,                                     //!< Invalid particle
    
    _NeutrinoG1Right   = (0b00000000000000000000010100000001),  //!< Anti-neutrino - 1. gen. - right handed (spin +½)
    _NeutrinoG1Left    = (0b00000000000000000000010100000010),  //!< Neutrino      - 1. gen. - left handed (spin -½)
    _NeutrinoG2Right   = (0b00000000000000000000011000000001),  //!< Anti-neutrino - 2. gen. - right handed (spin +½)
    _NeutrinoG2Left    = (0b00000000000000000000011000000010),  //!< Neutrino      - 2. gen. - left handed (spin -½)
    _NeutrinoG3Right   = (0b00000000000000000000011100000001),  //!< Anti-neutrino - 3. gen. - right handed (spin +½)
    _NeutrinoG3Left    = (0b00000000000000000000011100000010),  //!< Neutrino      - 3. gen. - left handed (spin -½)
    
    _PositronG1Right   = (0b00000000000000000000100101010101),  //!< Positron - red+green+blue - 1. gen. - right handed (spin +½)
    _PositronG1Left    = (0b00000000000000000000100101010110),  //!< Positron - red+green+blue - 1. gen. - left handed (spin -½)
    _ElectronG1Right   = (0b00000000000000000000100110101001),  //!< Electron - red+green+blue - 1. gen. - right handed (spin +½)
    _ElectronG1Left    = (0b00000000000000000000100110101010),  //!< Electron - red+green+blue - 1. gen. - left handed (spin -½)
    _PositronG2Right   = (0b00000000000000000000101001010101),  //!< Positron - red+green+blue - 2. gen. - right handed (spin +½)
    _PositronG2Left    = (0b00000000000000000000101001010110),  //!< Positron - red+green+blue - 2. gen. - left handed (spin -½)
    _ElectronG2Right   = (0b00000000000000000000101010101001),  //!< Electron - red+green+blue - 2. gen. - right handed (spin +½)
    _ElectronG2Left    = (0b00000000000000000000101010101010),  //!< Electron - red+green+blue - 2. gen. - left handed (spin -½)
    _PositronG3Right   = (0b00000000000000000000101101010101),  //!< Positron - red+green+blue - 3. gen. - right handed (spin +½)
    _PositronG3Left    = (0b00000000000000000000101101010110),  //!< Positron - red+green+blue - 3. gen. - left handed (spin -½)
    _ElectronG3Right   = (0b00000000000000000000101110101001),  //!< Electron - red+green+blue - 3. gen. - right handed (spin +½)
    _ElectronG3Left    = (0b00000000000000000000101110101010),  //!< Electron - red+green+blue - 3. gen. - left handed (spin -½)
    
    _QuarkUpG1RGRight  = (0b00000000000000000000110100010101),  //!< Up-quark      - red+green - 1. gen. - right handed (spin +½)
    _QuarkUpG1RGLeft   = (0b00000000000000000000110100010110),  //!< Up-quark      - red+green - 1. gen. - left handed (spin -½)
    _AntiQUpG1RGRight  = (0b00000000000000000000110100101001),  //!< Anti-up-quark - red+green - 1. gen. - right handed (spin +½)
    _AntiQUpG1RGLeft   = (0b00000000000000000000110100101010),  //!< Anti-up-quark - red+green - 1. gen. - left handed (spin -½)
    _QuarkUpG2RGRight  = (0b00000000000000000000111000010101),  //!< Up-quark      - red+green - 2. gen. - right handed (spin +½)
    _QuarkUpG2RGLeft   = (0b00000000000000000000111000010110),  //!< Up-quark      - red+green - 2. gen. - left handed (spin -½)
    _AntiQUpG2RGRight  = (0b00000000000000000000111000101001),  //!< Anti-up-quark - red+green - 2. gen. - right handed (spin +½)
    _AntiQUpG2RGLeft   = (0b00000000000000000000111000101010),  //!< Anti-up-quark - red+green - 2. gen. - left handed (spin -½)
    _QuarkUpG3RGRight  = (0b00000000000000000000111100010101),  //!< Up-quark      - red+green - 3. gen. - right handed (spin +½)
    _QuarkUpG3RGLeft   = (0b00000000000000000000111100010110),  //!< Up-quark      - red+green - 3. gen. - left handed (spin -½)
    _AntiQUpG3RGRight  = (0b00000000000000000000111100101001),  //!< Anti-up-quark - red+green - 3. gen. - right handed (spin +½)
    _AntiQUpG3RGLeft   = (0b00000000000000000000111100101010),  //!< Anti-up-quark - red+green - 3. gen. - left handed (spin -½)
    
    _QuarkUpG1GBRight  = (0b00000000000000000001000101010001),  //!< Up-quark      - green+blue - 1. gen. - right handed (spin +½)
    _QuarkUpG1GBLeft   = (0b00000000000000000001000101010010),  //!< Up-quark      - green+blue - 1. gen. - left handed (spin -½)
    _AntiQUpG1GBRight  = (0b00000000000000000001000110100001),  //!< Anti-up-quark - green+blue - 1. gen. - right handed (spin +½)
    _AntiQUpG1GBLeft   = (0b00000000000000000001000110100010),  //!< Anti-up-quark - green+blue - 1. gen. - left handed (spin -½)
    _QuarkUpG2GBRight  = (0b00000000000000000001001001010001),  //!< Up-quark      - green+blue - 2. gen. - right handed (spin +½)
    _QuarkUpG2GBLeft   = (0b00000000000000000001001001010010),  //!< Up-quark      - green+blue - 2. gen. - left handed (spin -½)
    _AntiQUpG2GBRight  = (0b00000000000000000001001010100001),  //!< Anti-up-quark - green+blue - 2. gen. - right handed (spin +½)
    _AntiQUpG2GBLeft   = (0b00000000000000000001001010100010),  //!< Anti-up-quark - green+blue - 2. gen. - left handed (spin -½)
    _QuarkUpG3GBRight  = (0b00000000000000000001001101010001),  //!< Up-quark      - green+blue - 3. gen. - right handed (spin +½)
    _QuarkUpG3GBLeft   = (0b00000000000000000001001101010010),  //!< Up-quark      - green+blue - 3. gen. - left handed (spin -½)
    _AntiQUpG3GBRight  = (0b00000000000000000001001110100001),  //!< Anti-up-quark - green+blue - 3. gen. - right handed (spin +½)
    _AntiQUpG3GBLeft   = (0b00000000000000000001001110100010),  //!< Anti-up-quark - green+blue - 3. gen. - left handed (spin -½)
    
    _QuarkUpG1BRRight  = (0b00000000000000000001010101000101),  //!< Up-quark      - blue+red - 1. gen. - right handed (spin +½)
    _QuarkUpG1BRLeft   = (0b00000000000000000001010101000110),  //!< Up-quark      - blue+red - 1. gen. - left handed (spin -½)
    _AntiQUpG1BRRight  = (0b00000000000000000001010110001001),  //!< Anti-up-quark - blue+red - 1. gen. - right handed (spin +½)
    _AntiQUpG1BRLeft   = (0b00000000000000000001010110001010),  //!< Anti-up-quark - blue+red - 1. gen. - left handed (spin -½)
    _QuarkUpG2BRRight  = (0b00000000000000000001011001000101),  //!< Up-quark      - blue+red - 2. gen. - right handed (spin +½)
    _QuarkUpG2BRLeft   = (0b00000000000000000001011001000110),  //!< Up-quark      - blue+red - 2. gen. - left handed (spin -½)
    _AntiQUpG2BRRight  = (0b00000000000000000001011010001001),  //!< Anti-up-quark - blue+red - 2. gen. - right handed (spin +½)
    _AntiQUpG2BRLeft   = (0b00000000000000000001011010001010),  //!< Anti-up-quark - blue+red - 2. gen. - left handed (spin -½)
    _QuarkUpG3BRRight  = (0b00000000000000000001011101000101),  //!< Up-quark      - blue+red - 3. gen. - right handed (spin +½)
    _QuarkUpG3BRLeft   = (0b00000000000000000001011101000110),  //!< Up-quark      - blue+red - 3. gen. - left handed (spin -½)
    _AntiQUpG3BRRight  = (0b00000000000000000001011110001001),  //!< Anti-up-quark - blue+red - 3. gen. - right handed (spin +½)
    _AntiQUpG3BRLeft   = (0b00000000000000000001011110001010),  //!< Anti-up-quark - blue+red - 3. gen. - left handed (spin -½)
    
    _AntiQDownG1RRight = (0b00000000000000000001100100000101),  //!< Down-anti-quark - red - 1. gen. - right handed (spin +½)
    _AntiQDownG1RLeft  = (0b00000000000000000001100100000110),  //!< Down-anti-quark - red - 1. gen. - left handed (spin -½)
    _QuarkDownG1RRight = (0b00000000000000000001100100001001),  //!< Down-quark      - red - 1. gen. - right handed (spin +½)
    _QuarkDownG1RLeft  = (0b00000000000000000001100100001010),  //!< Down-quark      - red - 1. gen. - left handed (spin -½)
    _AntiQDownG2RRight = (0b00000000000000000001101000000101),  //!< Down-anti-quark - red - 2. gen. - right handed (spin +½)
    _AntiQDownG2RLeft  = (0b00000000000000000001101000000110),  //!< Down-anti-quark - red - 2. gen. - left handed (spin -½)
    _QuarkDownG2RRight = (0b00000000000000000001101000001001),  //!< Down-quark      - red - 2. gen. - right handed (spin +½)
    _QuarkDownG2RLeft  = (0b00000000000000000001101000001010),  //!< Down-quark      - red - 2. gen. - left handed (spin -½)
    _AntiQDownG3RRight = (0b00000000000000000001101100000101),  //!< Down-anti-quark - red - 3. gen. - right handed (spin +½)
    _AntiQDownG3RLeft  = (0b00000000000000000001101100000110),  //!< Down-anti-quark - red - 3. gen. - left handed (spin -½)
    _QuarkDownG3RRight = (0b00000000000000000001101100001001),  //!< Down-quark      - red - 3. gen. - right handed (spin +½)
    _QuarkDownG3RLeft  = (0b00000000000000000001101100001010),  //!< Down-quark      - red - 3. gen. - left handed (spin -½)
    
    _AntiQDownG1GRight = (0b00000000000000000001110100010001),  //!< Down-anti-quark - green - 1. gen. - right handed (spin +½)
    _AntiQDownG1GLeft  = (0b00000000000000000001110100010010),  //!< Down-anti-quark - green - 1. gen. - left handed (spin -½)
    _QuarkDownG1GRight = (0b00000000000000000001110100100001),  //!< Down-quark      - green - 1. gen. - right handed (spin +½)
    _QuarkDownG1GLeft  = (0b00000000000000000001110100100010),  //!< Down-quark      - green - 1. gen. - left handed (spin -½)
    _AntiQDownG2GRight = (0b00000000000000000001111000010001),  //!< Down-anti-quark - green - 2. gen. - right handed (spin +½)
    _AntiQDownG2GLeft  = (0b00000000000000000001111000010010),  //!< Down-anti-quark - green - 2. gen. - left handed (spin -½)
    _QuarkDownG2GRight = (0b00000000000000000001111000100001),  //!< Down-quark      - green - 2. gen. - right handed (spin +½)
    _QuarkDownG2GLeft  = (0b00000000000000000001111000100010),  //!< Down-quark      - green - 2. gen. - left handed (spin -½)
    _AntiQDownG3GRight = (0b00000000000000000001111100010001),  //!< Down-anti-quark - green - 3. gen. - right handed (spin +½)
    _AntiQDownG3GLeft  = (0b00000000000000000001111100010010),  //!< Down-anti-quark - green - 3. gen. - left handed (spin -½)
    _QuarkDownG3GRight = (0b00000000000000000001111100100001),  //!< Down-quark      - green - 3. gen. - right handed (spin +½)
    _QuarkDownG3GLeft  = (0b00000000000000000001111100100010),  //!< Down-quark      - green - 3. gen. - left handed (spin -½)
    
    _AntiQDownG1BRight = (0b00000000000000000010000101000001),  //!< Down-anti-quark - blue - 1. gen. - right handed (spin +½)
    _AntiQDownG1BLeft  = (0b00000000000000000010000101000010),  //!< Down-anti-quark - blue - 1. gen. - left handed (spin -½)
    _QuarkDownG1BRight = (0b00000000000000000010000110000001),  //!< Down-quark      - blue - 1. gen. - right handed (spin +½)
    _QuarkDownG1BLeft  = (0b00000000000000000010000110000010),  //!< Down-quark      - blue - 1. gen. - left handed (spin -½)
    _AntiQDownG2BRight = (0b00000000000000000010001001000001),  //!< Down-anti-quark - blue - 2. gen. - right handed (spin +½)
    _AntiQDownG2BLeft  = (0b00000000000000000010001001000010),  //!< Down-anti-quark - blue - 2. gen. - left handed (spin -½)
    _QuarkDownG2BRight = (0b00000000000000000010001010000001),  //!< Down-quark      - blue - 2. gen. - right handed (spin +½)
    _QuarkDownG2BLeft  = (0b00000000000000000010001010000010),  //!< Down-quark      - blue - 2. gen. - left handed (spin -½)
    _AntiQDownG3BRight = (0b00000000000000000010001101000001),  //!< Down-anti-quark - blue - 3. gen. - right handed (spin +½)
    _AntiQDownG3BLeft  = (0b00000000000000000010001101000010),  //!< Down-anti-quark - blue - 3. gen. - left handed (spin -½)
    _QuarkDownG3BRight = (0b00000000000000000010001110000001),  //!< Down-quark      - blue - 3. gen. - right handed (spin +½)
    _QuarkDownG3BLeft  = (0b00000000000000000010001110000010),  //!< Down-quark      - blue - 3. gen. - left handed (spin -½)
    
    _PhotonRight       = (0b00000000000000000010010000000001),  //!< Photon - right handed (spin +1)
    _PhotonLeft        = (0b00000000000000000010010000000010),  //!< Photon - left handed (spin -1)
    
    _GluonRGRight      = (0b00000000000000000010110000100101),  //!< Gluon - red anti-green - right handed (spin +1)
    _GluonRGLeft       = (0b00000000000000000010110000100110),  //!< Gluon - red anti-green - left handed (spin -1)
    
    _GluonRBRight      = (0b00000000000000000011000010000101),  //!< Gluon - red anti-blue - right handed (spin +1)
    _GluonRBLeft       = (0b00000000000000000011000010000110),  //!< Gluon - red anti-blue - left handed (spin -1)
    
    _GluonGRRight      = (0b00000000000000000011100000011001),  //!< Gluon - green anti-red - right handed (spin +1)
    _GluonGRLeft       = (0b00000000000000000011100000011010),  //!< Gluon - green anti-red - left handed (spin -1)
    
    _GluonGBRight      = (0b00000000000000000011110010010001),  //!< Gluon - green anti-blue - right handed (spin +1)
    _GluonGBLeft       = (0b00000000000000000011110010010010),  //!< Gluon - green anti-blue - left handed (spin -1)
    
    _GluonBRRight      = (0b00000000000000000100000001001001),  //!< Gluon - blue anti-red - right handed (spin +1)
    _GluonBRLeft       = (0b00000000000000000100000001001010),  //!< Gluon - blue anti-red - left handed (spin -1)
    
    _GluonBGRight      = (0b00000000000000000100010001100001),  //!< Gluon - blue anti-green - right handed (spin +1)
    _GluonBGLeft       = (0b00000000000000000100010001100010),  //!< Gluon - blue anti-green - left handed (spin -1)
    
    _WbosonPositive    = (0b00000000000000000100100001010111),  //!< W+ boson - positive
    
    _WbosonNegative    = (0b00000000000000000100110010101011),  //!< W- boson - negative
    
    _Zboson            = (0b00000000000000000101000011111111),  //!< Z boson
};
Q_ENUM_NS(ParticleType)

/*! \brief Major particle normal helicity names */
enum ParticleHelicity : int
{
    _HelicityInvalid   = 0,                                     //!< Invalid helicity
    _HelicityRight     = (0b00000000000000000000000000000001),  //!< Positive right-handed helicity
    _HelicityLeft      = (0b00000000000000000000000000000010),  //!< Negative left-handed helicity
    _HelicityBoth      = (0b00000000000000000000000000000011),  //!< Dual, positive and negative helicity (W and Z bosons)
};
Q_ENUM_NS(ParticleHelicity)

/*! \brief Red particle normal helicity names */
enum ParticleChargeR : int
{
    _ChargeRNull      = 0,                                     //!< Null red charge - Red normal perpendicular to the major normal
    _ChargeRRight     = (0b00000000000000000000000000000100),  //!< Positive red charge - right-handed helicity
    _ChargeRLeft      = (0b00000000000000000000000000001000),  //!< Negative red charge - left-handed helicity
    _ChargeRBosonZ    = (0b00000000000000000000000000001100),  //!< Null red charge - Two red normals active
};
Q_ENUM_NS(ParticleChargeR)

/*! \brief Green particle normal helicity names */
enum ParticleChargeG : int
{
    _ChargeGNull      = 0,                                     //!< Null green charge - Green normal perpendicular to the major normal
    _ChargeGRight     = (0b00000000000000000000000000010000),  //!< Positive green charge - right-handed helicity
    _ChargeGLeft      = (0b00000000000000000000000000100000),  //!< Negative green charge - left-handed helicity
    _ChargeGBosonZ    = (0b00000000000000000000000000110000),  //!< Null green charge - Two green normals active
};
Q_ENUM_NS(ParticleChargeG)

/*! \brief Blue particle normal helicity names */
enum ParticleChargeB : int
{
    _ChargeBNull      = 0,                                     //!< Null blue charge - Blue normal perpendicular to the major normal
    _ChargeBRight     = (0b00000000000000000000000001000000),  //!< Positive blue charge - right-handed helicity
    _ChargeBLeft      = (0b00000000000000000000000010000000),  //!< Negative blue charge - left-handed helicity
    _ChargeBBosonZ    = (0b00000000000000000000000011000000),  //!< Null blue charge - Two blue normals active
};
Q_ENUM_NS(ParticleChargeB)

/*! \brief Particle generation names */
enum ParticleGeneration : int
{
    _GenerationBoson   = 0,                                     //!< Boson or invalid particle
    _Generation1       = (0b00000000000000000000000100000000),  //!< 1. generation fermion
    _Generation2       = (0b00000000000000000000001000000000),  //!< 2. generation fermion
    _Generation3       = (0b00000000000000000000001100000000),  //!< 3. generation fermion
};
Q_ENUM_NS(ParticleGeneration)

// clang-format on

/*! \brief The particle type names */
enum ParticleState : int
{
    _ParticleStateInvalid = 0,     //!< Invalid particle state
    _ParticleHistoryIntitial = 1,  //!< Initial historical state of a particle (Initial conditions of a simulation)
    _ParticleHistory = 2,          //!< Calculated historical state of a particle
    _ParticleCurrentInit = 3,      //!< Current state of a particle - without calculated interactions
    _ParticleCurrentReady = 4      //!< Current state of a particle - with calculated interactions, ready to move
};
Q_ENUM_NS(ParticleState)

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct Particle;

/*!
 * \brief Particles collision
 * \tparam T Template floating point type
 */
template <typename T>
struct ParticleCollision
{
    std::vector<const Particle<T> *> parents = {};   //!< Particles that hit each other in a collision
    std::vector<const Particle<T> *> children = {};  //!< Particles that are created in a collision
};

/*!
 * \brief Single state of a particle at a specific time-step
 * \tparam T Template floating point type
 */
template <typename T>
struct Particle
{
    const Particle<T> *prev = nullptr;  //!< Previous position in time, previous stored state of this particle
    const Particle<T> *next = nullptr;  //!< Next position in time, next stored state of this particle

    const ParticleCollision<T> *born = nullptr;  //!< Collision where this particle was created (children)
    const ParticleCollision<T> *dead = nullptr;  //!< Collision where this particle end its lifetime decay (parents)

    size_t ID = 0UL;  //!< Particle index

    ParticleType type = _ParticleInvalid;         //!< Particle type name
    ParticleState state = _ParticleStateInvalid;  //!< Particle state

    T time = T(0);  //!< Exact time-step in abs. spacetime for this particle state (in seconds)

    // 1. Generation properties

    /*!
     * \brief The central position of a spherical particle in the abs. spacetime (in meters)
     * \note 1. generation wave source position
     */
    Vec3<T> center1 = {};

    /*! \brief Translation motion vector of a 1. generation central position (in meters per second) */
    Vec3<T> velocity1 = {};

    Vec3<T> normal1 = {};  //   !< The orientated axis for color vectors of a particle (unit vector)
    // Vec3<T> arm1 = {};     //!< The secondary direction perpendicular to a major normal (unit vector)

    Vec3<T> boson1R = {};  //!< Primary boson red matter orientation (unit vector)
    Vec3<T> boson1G = {};  //!< Primary boson green matter orientation (unit vector)
    Vec3<T> boson1B = {};  //!< Primary boson blue matter orientation (unit vector)

    /*! \brief The anonymous union for secondary red normal */
    union
    {
        Vec3<T> fermionR = {};  //!< Primary fermion red matter orientation (unit vector)
        Vec3<T> boson2R;        //!< Secondary boson red matter orientation (unit vector)
    };

    /*! \brief The anonymous union for secondary green normal */
    union
    {
        Vec3<T> fermionG = {};  //!< Primary fermion green matter orientation (unit vector)
        Vec3<T> boson2G;        //!< Secondary boson green matter orientation (unit vector)
    };

    /*! \brief The anonymous union for secondary blue normal */
    union
    {
        Vec3<T> fermionB = {};  //!< Primary fermion blue matter orientation (unit vector)
        Vec3<T> boson2B;        //!< Secondary boson blue matter orientation (unit vector)
    };

    T angle = T(0);  //!< Angle between boson color normals with the major normal, with the value between 0 to π/2
                     //!< (in radians)

    T phase = T(0);  //!< Inner phase, rotational shift between boson and fermion normals (in radians)

    T rotation = T(0);  //!< Inner rotation angular velocity  of boson normals within the fermion normals
                        //!< (in radians per second)

    T charge1 = T(0);  //!< 1. generation wave charge

    Vec3<T> avgWaveR = {};  //!< Avg. red wave vector from all red waves penetrating the major body
    Vec3<T> avgWaveG = {};  //!< Avg. green wave vector from all green waves penetrating the major body
    Vec3<T> avgWaveB = {};  //!< Avg. blue wave vector from all blue waves penetrating the major body
    Vec3<T> avgWave1 = {};  //!< Avg. major wave vector from all major waves penetrating the major body

    Vec3<T> avgBodyR = {};  //!< Avg. red body vector from red vectors of colliding particles with major body
    Vec3<T> avgBodyG = {};  //!< Avg. green body vector from green vectors of colliding particles with major body
    Vec3<T> avgBodyB = {};  //!< Avg. blue body vector from blue vectors of colliding particles with major body
    Vec3<T> avgBody1 = {};  //!< Avg. major body vector from major vectors of colliding particles with major body

    Vec3<T> bodySpin1 = {};  //!< Current outer body major rotation (in radian per second)

    // 2. Generation properties

    //  Vec3<T> center2 = {};  //!< 2. generation sub-particle center (2. generation wave source position)

    //  Vec3<T> normal2 = {};  //!< Current normal - the major direction of translational motion (unit vector)
    //  Vec3<T> normal3 = {};  //!< Current normal - the major direction of translational motion (unit vector)

    //  // T charge1 = T(0);  //!< Charge amplitude of a major wave generated at a major particle position
    //  // T charge2 = T(0);  //!< Charge amplitude of a 2. generation wave generated at a \a position2
    //  // T charge3 = T(0);  //!< Charge amplitude of a 3. generation wave generated at a \a position3

    //  Vec3<T> position3 = {};  //!< 3. generation sub-particle center (3. generation wave source position)

    //  Vec3<T> normal1R = {};  //!< Major (boson) red color vector
    //  Vec3<T> normal1G = {};  //!< Major (boson) green color vector
    //  Vec3<T> normal1B = {};  //!< Major (boson) blue color vector

    //  Vec3<T> normal2R = {};  //!< Secondary (fermion) red color vector
    //  Vec3<T> normal2G = {};  //!< Secondary (fermion) green color vector
    //  Vec3<T> normal2B = {};  //!< Secondary (fermion) blue color vector

    //  Vec3<T> bodySpin1 = {};  //!< Current outer body major rotation (in radian per second)
    //  Vec3<T> bodySpin2 = {};  //!< Current generation 2 body rotation (in radian per second)

    //  Vec3<T> avgWaveR = {};  //!< Avg. red wave vector from all red waves penetrating major body
    //  Vec3<T> avgWaveG = {};  //!< Avg. green wave vector from all green waves penetrating major body
    //  Vec3<T> avgWaveB = {};  //!< Avg. blue wave vector from all blue waves penetrating major body
    //  Vec3<T> avgWave1 = {};  //!< Avg. major wave vector from all major waves penetrating major body
    //  Vec3<T> avgWave2 = {};  //!< Avg. major wave vector from all major waves penetrating 2. generation body

    //  Vec3<T> avgBodyR = {};  //!< Avg. red body vector from red vectors colliding particles with major body
    //  Vec3<T> avgBodyG = {};  //!< Avg. green body vector from green vectors colliding particles with major body
    //  Vec3<T> avgBodyB = {};  //!< Avg. blue body vector from blue vectors colliding particles with major body
    //  Vec3<T> avgBody1 = {};  //!< Avg. major body vector from major vectors colliding particles with major body
    //  Vec3<T> avgBody2 = {};  //!< Avg. 2. gen. body vector from major vectors colliding particles with 2. gen.
    //  body

    inline ParticleGeneration generation() const;
    Particle<T> moved(const T _timeDelta) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Particle generation
 * \tparam T Template floating point type
 * \return Particle generation
 */
template <typename T>
inline ParticleGeneration Particle<T>::generation() const
{
    switch ((static_cast<int>(type) & (0b00000000000000000000001100000000)))
    {
    case (0b00000000000000000000000000000000): return _GenerationBoson;
    case (0b00000000000000000000000100000000): return _Generation1;
    case (0b00000000000000000000001000000000): return _Generation2;
    case (0b00000000000000000000001100000000): return _Generation3;
    default: break;
    }
    return _GenerationBoson;
}

/*!
 * \brief Particle moved by a given time-delta
 * \tparam T Template floating point type
 * \param _timeDelta Time delta to move
 * \return This particle moved by a given time-delta
 */
template <typename T>
Particle<T> Particle<T>::moved(const T _timeDelta) const
{
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \namespace U1::Math::Universe1::Calculus
 * \brief The Universe1 physics calculus tools
 */
namespace Calculus {

/*!
 * \brief Tool function for failing build method
 * \tparam T Template floating point type
 * \param _dbSize Particle database size
 * \param _particles Initial particles and their histories
 * \param _timeEnd Final time in calculation
 * \param _timeDelta General time-step duration
 * \param _msg Error message
 * \return Always \c false
 */
template <typename T>
inline static bool failBuild(
    const size_t _dbSize, const size_t _particlesSize, const T _timeEnd, const T _timeDelta, const std::string &_msg)
{
    std::cerr << "Error: PhysicsUniverse1::build(" << _dbSize << ", " << _particlesSize << ", " << _timeEnd << ", "
              << _timeDelta << "): " << _msg;
    return false;
}

/*!
 * \brief Test if initial particle is valid
 * \param _p1 Particle 1
 * \param _p2 Particle 2
 * \return \c true if major particle parameters are valid
 */
template <typename T>
static bool testInitParticle(const Particle<T> &_particle)
{
    if (_particle.type == _ParticleInvalid || !isBetween0_PI2(_particle.chargeAngle) ||
        !isPositive(_particle.charge1) || !_particle.normal.isNormalized() || !_particle.arm.isNormalized() ||
        !_particle.normal.isPerpendicular(_particle.arm))
        return false;

    const int t = static_cast<int>(_particle.type);
    // clang-format off
    switch (t & (0b00000000000000000000000000001100)) {
    case (0b00000000000000000000000000000100): if (_particle.chargeR !=  1) return false; break;
    case (0b00000000000000000000000000001000): if (_particle.chargeR != -1) return false; break;
    default:                                   if (_particle.chargeR !=  0) return false; break;
    }

    switch (t & (0b00000000000000000000000000110000)) {
    case (0b00000000000000000000000000010000): if (_particle.chargeG !=  1) return false; break;
    case (0b00000000000000000000000000100000): if (_particle.chargeG != -1) return false; break;
    default:                                   if (_particle.chargeG !=  0) return false; break;
    }

    switch (t & (0b00000000000000000000000011000000)) {
    case (0b00000000000000000000000001000000): if (_particle.chargeB !=  1) return false; break;
    case (0b00000000000000000000000010000000): if (_particle.chargeB != -1) return false; break;
    default:                                   if (_particle.chargeB !=  0) return false; break;
    }

    switch (_particle.generation()) {
    case _GenerationBoson: break;
    case _Generation1: break;
    case _Generation2:
        if (!isPositive(_particle.charge2)) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position2))) return false;
        break;
    case _Generation3:
        if (!isPositive(_particle.charge2) || !isPositive(_particle.charge3)) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position2))) return false;
        if (!isBetween0_1(_particle.position.distanceToPoint(_particle.position3))) return false;
        if (!isBetween0_1(_particle.position2.distanceToPoint(_particle.position3))) return false;
        break;
    }
    // clang-format on

    return true;
}

/*!
 * \brief Test validity of initial following particles
 * \param _p1 Particle 1
 * \param _p2 Particle 2
 * \return \c true if particles are valid and particle 2 is properly following particle 1
 */
template <typename T>
inline static bool testInitParticles(const Particle<T> &_p1, const Particle<T> &_p2)
{
    if (_p1.type != _p2.type || _p1.chargeR != _p2.chargeR || _p1.chargeG != _p2.chargeG ||
        _p1.chargeB != _p2.chargeB || !equals(_p1.chargeAngle, _p2.chargeAngle) || isMoreOrEqual(_p1.time, _p2.time))
        return false;

    const ParticleGeneration g = _p1.generation();
    switch (g)
    {
    case _GenerationBoson:
    case _Generation1:
        if (!equals(_p1.charge1, _p2.charge1))
            return false;
        break;
    case _Generation2:
        if (!equals(std::sqrt(_p1.charge1 * _p1.charge1 + _p1.charge2 * _p1.charge2),
                    std::sqrt(_p2.charge1 * _p2.charge1 + _p2.charge2 * _p2.charge2)))
            return false;
        break;

    case _Generation3:
        if (!equals(std::sqrt(_p1.charge1 * _p1.charge1 + _p1.charge2 * _p1.charge2 + _p1.charge3 * _p1.charge3),
                    std::sqrt(_p2.charge1 * _p2.charge1 + _p2.charge2 * _p2.charge2 + _p2.charge3 * _p2.charge3)))
            return false;
        break;
    }

    const T dt = _p2.time - _p1.time;

    // if (!equals(_p1.charge1, _p2.charge1))
    //     return false;
}

/*!
 * \brief Calculate the "energy" of a photon
 * \tparam T Template floating point type
 * \param _angleBoson Color vector normals angle (in radians)
 * \return Energy of a photon
 */
template <typename T>
inline static T energyPhoton(const T _angleBoson)
{
    return T(6) * std::cos(_angleBoson) / std::sin(_angleBoson);
}

/*!
 * \brief Calculate the "energy" of a gluon
 * \tparam T Template floating point type
 * \param _angleBoson Color vector normals angle (in radians)
 * \return Energy of a gluon
 */
template <typename T>
inline static T energyGluon(const T _angleBoson)
{
    return T(2) * std::cos(_angleBoson) / std::sin(_angleBoson);
}

/*!
 * \brief Calculate the "energy" of a fermion
 * \tparam T Template floating point type
 * \param _angleBoson Boson color vector normals angle (in radians)
 * \param _angleFermion Fermion color vector normals angle (in radians)
 * \return Energy of a fermion
 */
template <typename T>
inline static T energyFermion(const T _angleBoson, const T _angleFermion, const uint8_t _cntActive)
{
    if (_cntActive == 0U)  // Neutrino
    {
        // return energyPhoton(_angleBoson) * (T(2) / T(3));
        // return T(6) * std::cos(_angleBoson) / std::sin(_angleBoson) * T(4) / T(6);
        return T(4) * std::cos(_angleBoson) / std::sin(_angleBoson);
    }
    else if (_cntActive <= 3U)  // Charged fermion
    {
        // const T tanFermion = T(1) / std::tan(_angleFermion);
        // T result = T(0);
        // for (uint8_t n = 0U; n < _cntActive; ++n)
        //     result += tanFermion;
        // return (energyPhoton(_angleBoson) - result) * T(4U - _cntActive) / T(_cntActive + 6U);

        return (T(6) * std::cos(_angleBoson) / std::sin(_angleBoson) -
                T(_cntActive) * std::cos(_angleFermion) / std::sin(_angleFermion)) *
            T(4U - _cntActive) / T(_cntActive + 6U);
    }
    return T(-1.0f);
}

}  // namespace Calculus

}  // namespace Universe1
}  // namespace Math
}  // namespace U1

#endif  // MATH_PHYSICSUNIVERSE1CALCULUS_H
