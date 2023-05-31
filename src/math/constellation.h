/*!
 * \file math/constellation.h
 * \author Michal Steller
 * \brief Element constellation
 */

#ifndef UNIVERSE1_MATH_CONSTELLATION_H
#define UNIVERSE1_MATH_CONSTELLATION_H

#include "orientation.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief Enumeration of element constellation names
 */
enum ConstellationType : uint8_t
{
    _ConstellationInvalid = 0U,  //!< Invalid constellation

    _Neutrino,  //!< Neutrino

    _ElectronRight,  //!< Electron right - positron
    _ElectronLeft,   //!< Electron left

    _QuarkUpIRight,  //!< Up quark right - anti-up quark (Charge I disabled, J and K charges are active)
    _QuarkUpJRight,  //!< Up quark right - anti-up quark (Charge J disabled, K and I charges are active)
    _QuarkUpKRight,  //!< Up quark right - anti-up quark (Charge K disabled, I and J charges are active)

    _QuarkUpILeft,  //!< Up quark left (Charge I disabled, J and K charges are active)
    _QuarkUpJLeft,  //!< Up quark left (Charge J disabled, K and I charges are active)
    _QuarkUpKLeft,  //!< Up quark left (Charge K disabled, I and J charges are active)

    _QuarkDownI,  //!< Down quark left (Charge I active, J and K charges are in opposite directions)
    _QuarkDownJ,  //!< Down quark left (Charge J active, K and I charges are in opposite directions)
    _QuarkDownK,  //!< Down quark left (Charge K active, I and J charges are in opposite directions)

    _PhotonI,  //!< Photon (J and K charges are merged)
    _PhotonJ,  //!< Photon (K and I charges are merged)
    _PhotonK,  //!< Photon (I and J charges are merged)

    _Graviton,  //!< Graviton (all color spins merged)
};

/*!
 * \brief Element "color" spin triplet constellation
 * \tparam T Template floating point type
 */
template <typename T>
struct Constellation
{
    /*! \brief The anonymous union for different property name access */
    union
    {
        /*!
         * \brief Union array representation, access constellation component by index
         * \details
         * | Index | Component      |
         * | :---- | :------------- |
         * | 0     | Spin I (red)   |
         * | 1     | Spin J (green) |
         * | 2     | Spin K (blue)  |
         * | 3     | Spin massive   |
         */
        Vec3<T> m_spin[4];

        /*! \brief The anonymous structure, access components by spin name */
        struct
        {
            Vec3<T> spinI;  //!< Major "red" spin (Hamiltonian \b I)
            Vec3<T> spinJ;  //!< Major "green" spin (Hamiltonian \b J)
            Vec3<T> spinK;  //!< Major "blue" spin (Hamiltonian \b K)
            Vec3<T> spinM;  //!< Major "massive" spin (Hamiltonian \b Real)
        };
    };

    /*! \brief The anonymous union for different property name access */
    union
    {
        /*!
         * \brief Union array representation, access constellation component by index
         * \details
         * | Index | Component                  |
         * | :---- | :------------------------- |
         * | 0     | Spin start phase I (red)   |
         * | 1     | Spin start phase J (green) |
         * | 2     | Spin start phase K (blue)  |
         * | 3     | Spin start phase massive   |
         */
        Vec3<T> m_phase[4];

        /*! \brief The anonymous structure, access components by spin name */
        struct
        {
            Vec3<T> phaseI;  //!< "Red" spin phase
            Vec3<T> phaseJ;  //!< "Green" spin phase
            Vec3<T> phaseK;  //!< "Blue" spin phase
            Vec3<T> phaseM;  //!< "Blue" spin phase
        };
    };

    /*!
     * \brief Constructor
     * \param _type Initial constellation type
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constellation(const ConstellationType _type = _ConstellationInvalid)
    {
        setTypeBase(_type);
    }

    /*!
     * \brief Constructor
     * \param _type Initial constellation type
     * \param _normal Initial constellation normal
     * \param _arm Initial constellation arm
     * \param _phaseDeg Initial constellation phase
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constellation(const ConstellationType _type,
                         const Vec3<T> &_normal,
                         const Vec3<T> &_arm,
                         const T _phaseDeg = T(0))
    {
        setType(_type, _normal, _arm, _phaseDeg);
    }

    /*!
     * \brief Setup new constellation type within given orientation
     * \param _type New constellation type
     * \param _normal New constellation normal
     * \param _arm New constellation arm
     * \param _phaseDeg New constellation phase
     * \return This object
     */
    Constellation<T> &
    setType(const ConstellationType _type, const Vec3<T> &_normal, const Vec3<T> &_arm, const T _phaseDeg = T(0))
    {
        setTypeBase(_type);
        return setOrientation(_normal, _arm, _phaseDeg);
    }

    /*!
     * \brief Setup new constellation type within normal NX and arm NY
     * \param _type New constellation type
     * \return This object
     */
    Constellation<T> &setTypeBase(const ConstellationType _type)
    {
        static const Vec3<T> ux = Vec3<T>::unitX();
        static const Vec3<T> uy = Vec3<T>::unitY();
        static const Vec3<T> uz = Vec3<T>::unitZ();
        static const Vec3<T> p1 = Vec3<T>(Const::T_1_SQRT2<T>(), Const::T_1_SQRT2<T>(), T(0));
        static const Vec3<T> p2 = Vec3<T>(Const::T_1_SQRT2<T>(), -Const::T_1_SQRT2<T>(), T(0));

        static const Vec3<T> ne2(T(0), -Const::T_SQRT3_2<T>(), T(-0.5));
        static const Vec3<T> ne3(T(0), Const::T_SQRT3_2<T>(), T(-0.5));

        static const T angleElectron = ux.angleRad(Vec3<T>(T(1), T(1), T(1)));
        static const Vec3<T> e1 = ux.rotated(Vec3<T>(T(0), T(-1), T(0)), angleElectron).normalized();
        static const Vec3<T> e2 = ux.rotated(Vec3<T>(T(0), T(0.5), -Const::T_SQRT3_2<T>()), angleElectron).normalized();
        static const Vec3<T> e3 = ux.rotated(Vec3<T>(T(0), T(0.5), Const::T_SQRT3_2<T>()), angleElectron).normalized();

        static const T angleQuarkUp = std::acos(T(1) / T(3));
        static const Vec3<T> qr2 = ne2.rotated(uz, Const::T_PI_2<T>() - (angleQuarkUp * T(0.5))).normalized();
        static const Vec3<T> qr3 = ne2.rotated(uz, Const::T_PI_2<T>() + (angleQuarkUp * T(0.5))).normalized();
        static const Vec3<T> qrn2 = Vec3<T>::cross(qr2, Vec3<T>::cross(uz, qr2).normalized()).normalized();
        static const Vec3<T> qrn3 = Vec3<T>::cross(qr3, Vec3<T>::cross(uz, qr3).normalized()).normalized();

        static const Vec3<T> ql2 = ne2.rotated(-uz, Const::T_PI_2<T>() + (angleQuarkUp * T(0.5))).normalized();
        static const Vec3<T> ql3 = ne2.rotated(-uz, Const::T_PI_2<T>() - (angleQuarkUp * T(0.5))).normalized();
        static const Vec3<T> qln2 = Vec3<T>::cross(ql2, Vec3<T>::cross(uz, ql2).normalized()).normalized();
        static const Vec3<T> qln3 = Vec3<T>::cross(ql3, Vec3<T>::cross(uz, ql3).normalized()).normalized();

        static const Vec3<T> em = ux / T(3);
        static const Vec3<T> qm = ux * Const::T_1_SQRT2<T>();

        switch (_type)
        {
        case _ConstellationInvalid: return set({}, {}, {}, {}, {}, {}, {}, {});

        case _Neutrino: return set(uz, ne2, ne3, {}, ux, ux, ux, {});

        case _ElectronRight: return set(e1, e2, e3, -em, -e2, -e3, -e1, uz);
        case _ElectronLeft: return set(e1, e3, e2, em, -e3, -e2, -e1, uz);

        case _QuarkUpIRight: return set(uz, qr2, qr3, -qm, ux, qrn2, qrn3, uz);
        case _QuarkUpJRight: return set(qr3, uz, qr2, -qm, qrn3, ux, qrn2, uz);
        case _QuarkUpKRight: return set(qr2, qr3, uz, -qm, qrn2, qrn3, ux, uz);

        case _QuarkUpILeft: return set(uz, ql2, ql3, -qm, ux, qln2, qln3, uz);
        case _QuarkUpJLeft: return set(ql3, uz, ql2, -qm, qln3, ux, qln2, uz);
        case _QuarkUpKLeft: return set(ql2, ql3, uz, -qm, qln2, qln3, ux, uz);

        case _QuarkDownI: return set(ux, uy, -uy, -ux, uy, ux, -ux, uy);
        case _QuarkDownJ: return set(uy, ux, -uy, -ux, ux, uy, -ux, uy);
        case _QuarkDownK: return set(-uy, uy, ux, -ux, -ux, ux, uy, uy);

        case _PhotonI: return set(p1, p2, p2, {}, uz, p1, -p1, {});
        case _PhotonJ: return set(p2, p1, p2, {}, -p1, uz, p1, {});
        case _PhotonK: return set(p2, p2, p1, {}, p1, -p1, uz, {});

        case _Graviton: return set(ux, ux, ux, -ux, uz, ne2, ne3, -uz);
        }
        return set({}, {}, {}, {}, {}, {}, {}, {});
    }

    /*!
     * \brief Set new orientation
     * \param _normal New constellation normal
     * \param _arm New constellation arm
     * \param _phaseDeg New constellation phase
     * \return This object
     */
    Constellation<T> &setOrientation(const Vec3<T> &_normal, const Vec3<T> &_arm, const T _phaseDeg = T(0))
    {
        const Quaternion<T> rot1 = Quaternion<T>::fromTwoVectors(Vec3<T>::unitX(), _normal);
        const Vec3<T> up2 = rot1.rotated(Vec3<T>::unitZ()).normalized();

        bool ok;
        Quaternion<T> rot2 = Quaternion<T>::fromTwoVectors(up2, _arm, &ok);
        if (!ok)
            rot2 = Quaternion<T>::fromAxisAndAngle(_normal, M_PI);

        const T pr = toRad<T>(_phaseDeg);
        const Quaternion<T> rotI = Quaternion<T>::fromAxisAndAngle(spinI, pr);
        const Quaternion<T> rotJ = Quaternion<T>::fromAxisAndAngle(spinJ, pr);
        const Quaternion<T> rotK = Quaternion<T>::fromAxisAndAngle(spinK, pr);
        const Quaternion<T> rotM = Quaternion<T>::fromAxisAndAngle(Vec3<T>::unitX(), pr * spinM.length());
        return set(rot2.rotated(rot1.rotated(spinI).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(spinJ).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(spinK).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(spinM)),
                   rot2.rotated(rot1.rotated(rotI.rotated(phaseI).normalized()).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(rotJ.rotated(phaseJ).normalized()).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(rotK.rotated(phaseK).normalized()).normalized()).normalized(),
                   rot2.rotated(rot1.rotated(rotM.rotated(phaseM).normalized()).normalized()).normalized());
    }

    /*!
     * \brief Setup constellation properties
     * \param _spinI New value for spin I
     * \param _spinJ New value for spin J
     * \param _spinK New value for spin K
     * \param _spinM New value for spin M
     * \param _phaseI New value for phase I
     * \param _phaseJ New value for phase J
     * \param _phaseK New value for phase K
     * \param _phaseM New value for phase M
     * \return This object
     */
    Constellation<T> &set(const Vec3<T> &_spinI,
                          const Vec3<T> &_spinJ,
                          const Vec3<T> &_spinK,
                          const Vec3<T> &_spinM,
                          const Vec3<T> &_phaseI,
                          const Vec3<T> &_phaseJ,
                          const Vec3<T> &_phaseK,
                          const Vec3<T> &_phaseM)
    {
        spinI = _spinI;
        spinJ = _spinJ;
        spinK = _spinK;
        spinM = _spinM;
        phaseI = _phaseI;
        phaseJ = _phaseJ;
        phaseK = _phaseK;
        phaseM = _phaseM;
        return *this;
    }

    /*!
     * \brief Constellation to different precision
     * \tparam T2 Output template floating point type
     * \return Constellation in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    inline Constellation<T2> converted() const
    {
        return Constellation<T2>(spinI.template converted<T2>(),
                                 spinJ.template converted<T2>(),
                                 spinK.template converted<T2>(),
                                 spinM.template converted<T2>(),
                                 phaseI.template converted<T2>(),
                                 phaseJ.template converted<T2>(),
                                 phaseK.template converted<T2>(),
                                 phaseM.template converted<T2>());
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Quaternion
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Constellation<T> &_v)
{
    return _os << "[I" << _v.spinI << "|J" << _v.spinJ << "|K" << _v.spinK << "|M" << _v.spinM << ']';
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_CONSTELLATION_H
