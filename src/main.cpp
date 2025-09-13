/*!
 * \file src/main.cpp
 * \brief The \b main procedure file
 */

#include <QApplication>
#include <QStandardPaths>

#ifdef U1_UNIT_TESTS
#include "UnitTests/test_math.cc"
#else
#include "Examples/example_triangle.cc"
#include "Examples/example_rectangle.cc"
#include "Examples/example_circle.cc"
#include "Examples/example_circlearc.cc"
#include "Examples/example_ellipse.cc"
#include "Examples/example_text.cc"
#include "Examples/example_sphere.cc"
#include "Examples/example_ellipsoid.cc"
#include "Examples/example_line.cc"
#include "Examples/example_path.cc"
#include "Examples/example_clock.cc"
#include "Examples/example_hand.cc"
#include "Examples/example_simulation_newton.cc"
#endif

// #include "Math/physicsuniverse1.h"

// template <typename T>
// void showFermionWeight();

/*!
 * \brief The \b main procedure
 * \param argc Argument count
 * \param argv Argument array
 * \return \c EXIT_SUCCESS or \c EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    using namespace U1;
    using namespace U1::Examples;
    using namespace U1::Audio;

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Universe1");
    Q_UNUSED(app)

#ifdef U1_UNIT_TESTS
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else

    // showFermionWeight<long double>();

    // U1::Math::U1SimD sd;
    // sd.build(0, {}, 1, 1);

    // static const QString workDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
    //     QDir::separator() + "U1" + QDir::separator();

    // if (examplePathSpiralArc(workDir))
    // {
    //     SettingsAudio::runProcess("/usr/bin/vlc", {"--loop", workDir + "video.avi"});
    //     return EXIT_SUCCESS;
    // }

    return EXIT_FAILURE;

#endif
}

/*
template <typename T>
inline T energyPhoton(const T _angleBoson)
{
    const T tanBoson = T(1) / std::tan(_angleBoson);
    return tanBoson * T(6);
    // return tanBoson;
    // return tanBoson * tanBoson * tanBoson;
    // return tanBoson * tanBoson * tanBoson * tanBoson * tanBoson * tanBoson;
}

template <typename T>
inline T energyFermion(const T _angleBoson, const T _angleFermion, const uint8_t _cntActive)
{

    if (_cntActive == 0U)  // Neutrino
    {
        return energyPhoton(_angleBoson) * (T(2) / T(3));
    }
    else if (_cntActive <= 3U)  // Charged fermion
    {
        const T tanFermion = T(1) / std::tan(_angleFermion);
        T result = T(0);
        for (uint8_t n = 0U; n < _cntActive; ++n)
            result += tanFermion;
        return (energyPhoton(_angleBoson) - result) * T(4U - _cntActive) / T(_cntActive + 6U);
        // return result / T(_cntActive);T(_cntActive)
    }
    return T(-1.0f);
}

template <typename T>
inline void showFermionWeight()
{
    using namespace U1::Math;

    const T me = 0.511;
    const T mu = 2.16;
    const T md = 4.7;
    const T mue = (mu / me);
    const T mde = (md / me);
    const T ae = Vec3<T>(1, 0, 0).angleRad({1, 1, 1});
    const T au = M_PI_4;
    const T ad = M_PI_4;
    const T xe = energyFermion(ae, ae, 3U);
    const T xu = energyFermion(au, au, 2U);
    const T xd = energyFermion(ad, ad, 1U);
    const T xue = xu / xe;
    const T xde = xd / xe;

    std::cout << toDeg(ae) << "° " << toDeg(au) << "° " << toDeg(ad) << "°";
    // std::cout << " -- " << std::tan(ae) << " " << std::tan(au) << " " << std::tan(ad);
    // std::cout << " -- " << std::atan(ae) << " " << std::atan(au) << " " << std::atan(ad);
    // std::cout << "\n";

    // std::cout << " -- " << me << " " << mu << " " << md;
    std::cout << " EEE " << xe << " " << xu << " " << xd;
    std::cout << " ??? 1 : " << mue << " : " << mde;
    std::cout << " !!! 1 : " << xue << " : " << xde;
    std::cout << " xxx " << (mue / xue) << " : " << (mde / xde);
    std::cout << " /// " << (xue / mue) << " : " << (xde / mde);
    std::cout << "\n";

    // const T ce = Vec3<T>(1, 0, 0).cosAngle({1, 1, 1});
    // const T cu = M_SQRT1_2l;
    // const T cd = M_SQRT1_2l;
    // const T cd = std::cos(toRad(T(41.237)));
    // const T cd = (std::sqrt(T(3)) * T(0.5));

    // const T xe = (ce * ce * ce) * (ce * ce * ce);
    // const T xu = (cu * cu * cu) * (cu * cu);
    // const T xd = (cd * cd * cd) * (cd);
    // const T xue = xu / xe;
    // const T xde = xd / xe;

    // std::cout << ce << " " << cu << " " << cd << "  --  ";
    // std::cout << toDeg(std::acos(ce)) << " " << toDeg(std::acos(cu)) << " " << toDeg(std::acos(cd)) << "  --  ";
    // std::cout << me << " " << mu << " " << md << "  --  ";
    // std::cout << xe << " " << xu << " " << xd << "  --  ";
    // std::cout << "1 : " << mue << " : " << mde << "  --  ";
    // std::cout << "1 : " << xue << " : " << xde << "\n";
    // std::cout << "1 : x" << (mue / xue) << " : x" << (mde / xde) << " -- ";
    // std::cout << "1 : /" << (xue / mue) << " : /" << (xde / mde) << "\n";

    // T k1 = T(1.5386119775);
    // for (int N = 0; N <= 0; ++N, k1 += T(0.1))
    // {
    // const T k2 = T(0.9456885794);
    // const T nxe = (ce * ce * ce) * k2;
    // const T nxu = (cu * cu * k1);
    // const T nxd = (cd * k1 * k1);

    // const T k2 = T(1.0465764525);
    // const T nxe = std::sqrt(ce) * (ce * ce * ce) * k2;
    // const T nxu = std::sqrt(cu) * (cu * cu * k1);
    // const T nxd = std::sqrt(cd) * (cd * k1 * k1);

    // const T k2 = T(1.1582272376);
    // const T nxe = (ce) * (ce * ce * ce) * k2;
    // const T nxu = (cu) * (cu * cu * k1);
    // const T nxd = (cd) * (cd * k1 * k1);

    // const T k2 = T(1.7373408564);
    // const T nxe = (ce * ce * ce) * (ce * ce * ce) * k2;
    // const T nxu = (cu * cu * cu) * (cu * cu * k1);
    // const T nxd = (cd * cd * cd) * (cd * k1 * k1);

    // const T k2 = T(3.1916989554);
    // const T nxe = ((ce * ce * ce) * (ce * ce * ce)) * (ce * ce * ce) * k2;
    // const T nxu = ((cu * cu * cu) * (cu * cu * cu)) * (cu * cu * k1);
    // const T nxd = ((cd * cd * cd) * (cd * cd * cd)) * (cd * k1 * k1);

    // const T nxue = (nxu / nxe);
    // const T nxde = (nxd / nxe);
    // std::cout << std::fixed                                            //
    //           << std::setprecision(10)                                 //
    //           << k1 << " " << k2                                       //
    //           << " - 1 : x" << (nxue / mue) << " : x" << (nxde / mde)  //
    //           << " - 1 : /" << (mue / nxue) << " : /" << (mde / nxde)  //
    //           << " -  " << ((mue / nxue) - (mde / nxde))               //
    //           << "\n";
    //  // << std::setprecision(std::numeric_limits<T>::digits10)
    //  }
}
*/
