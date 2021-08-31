#ifndef TEST_NEWTON_H
#define TEST_NEWTON_H

#include <QTest>

#include "../simulation/newton/newtonsimulation.h"

class Test_Newton : public QObject
{
    Q_OBJECT
 public:
    Test_Newton(QObject *parent = nullptr);

 private slots:
    void testObjectDataFloat();
    // void testObjectDataDouble();
    // void testObjectDataLongDouble();
    //
    // void testObjectLongDouble();

 private:
    template <typename T>
    void testObjectData();
};

template <typename T>
void Test_Newton::testObjectData()
{
    using namespace Universe1;
    using namespace Universe1::Math;
    using namespace Universe1::Const;
    using namespace Universe1::Simulation;
    using namespace Universe1::Simulation::GravityNewton;

    std::cout.precision(4);
    std::cout << std::fixed;
    // static const T angle = toRad<T>(5);
    static const int loops = 7;

    //#define __CLAZZ__ NewtonObjectCurrent
#define __CLAZZ__ NewtonObjectByWave

    Universe1::Simulation::Simulation<T, __CLAZZ__<T>, NewtonTimeStamp<T>> simCur;

    simCur.initObjects().push_back(__CLAZZ__<T>(0, 5, 5));
    simCur.initObjects().back().current()->moveVelocity = Vec3<T>(0.1, 0, 0);

    for (int i = 0; i < loops; ++i)
        simCur.initObjects().back().addStep(1);

    simCur.initObjects().push_back(__CLAZZ__<T>(1, 5, 5));
    simCur.initObjects().back().current()->position = Vec3<T>(2.5, -1, 0);
    simCur.initObjects().back().current()->moveVelocity = Vec3<T>(0, 0.1, 0);

    for (int i = 0; i < loops; ++i)
        simCur.initObjects().back().addStep(1);

    for (size_t j = 0; j < simCur.initObjects().front().history().size(); ++j)
        std::cout << "* " << j << " " << (simCur.initObjects().front().history().at(j)) << std::endl;

    for (size_t j = 0; j < simCur.initObjects().back().history().size(); ++j)
        std::cout << "+ " << j << " " << (simCur.initObjects().back().history().at(j)) << std::endl;
    const uint32_t res = simCur.testStart();
    std::cout << res << ":" << strSimulationProperties(res) << std::endl;

    std::list<std::pair<size_t, size_t>> invalid;
    simCur.testHistoryVisibility(&invalid);
    for (const std::pair<size_t, size_t> &p : invalid)
        std::cout << "  > " << p.first << " " << p.second << std::endl;

    simCur.initialize(10U);
    std::cout << "------------------------------------------------------------" << std::endl;

    for (const __CLAZZ__<T> &o : simCur.objects())
    {
        std::cout << o.ID() << std::endl;
        std::cout << o.currentIdx() << std::endl;
        size_t ii = 0U;
        for (const NewtonTimeStamp<T> &ts : o.history())
            std::cout << ii++ << " : " << ts << std::endl;
        std::cout << "------------------------------" << std::endl;
    }

    const __CLAZZ__<T> &o0 = simCur.objects().at(0U);
    const __CLAZZ__<T> &o1 = simCur.objects().at(1U);

    std::cout
        << " aaaa: "
        << (*o1.eventSource(simCur.physics().universeVelocity, o0.current()->timeStamp, o0.current()->position).second)
        << std::endl;

    std::cout << " bbbb: "
              << (o1.eventSource(simCur.physics().universeVelocity, o0.current()->timeStamp, o0.current()->position)
                      .second
                      ->movedToEventSource(
                          simCur.physics().universeVelocity, o0.current()->timeStamp, o0.current()->position)
                      .first)
              << std::endl;

    std::cout << "Add: " << (simCur.addStep() ? "OK" : "FAIL") << std::endl;

    // Universe1::Simulation::Simulation<T, NewtonObjectByWave<T>, NewtonTimeStamp<T>> simWave;
}

#endif  // TEST_NEWTON_H
/*
    if (true)
    {
        NewtonObject<T> obj1(1, T_1<T>(), 5U);
        obj1.current()->moveVelocity = Vec3<T>(1, 0, 0);
        std::cout << obj1.currentIdx() << " * " << (*obj1.current()) << std::endl;

        for (int i = 0; i < 7; ++i)
        {
            obj1.addToHistory(obj1.current()->moved(T_1<T>()));
            std::cout << obj1.currentIdx() << " + " << (*obj1.current()) << " = "
                      << (obj1.currentCurvingTimeDuration(angle)) << std::endl;

            for (size_t j = 0; j < obj1.history().size(); ++j)
                std::cout << "* " << j << " " << (obj1.history().at(j)) << std::endl;
            std::cout << std::endl;
        }
    }

    if (true)
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        NewtonObject<T> obj2(2, T_1<T>(), 5U);
        obj2.current()->position = Vec3<T>(1, 1, 1);
        obj2.current()->moveVelocity = Vec3<T>(0, 1, 0);
        obj2.current()->moveAccel = Vec3<T>(0, 0, 0.1);
        std::cout << obj2.currentIdx() << " * " << (*obj2.current()) << std::endl;

        for (int i = 0; i < 7; ++i)
        {
            obj2.addToHistory(obj2.current()->moved(T_1<T>()));
            obj2.current()->moveAccel = Vec3<T>(0, 0, 0.1);

            const T tt = obj2.currentCurvingTimeDuration(angle);

            std::cout << obj2.currentIdx() << " + " << (*obj2.current()) << " = " << (tt) << " - "
                      << toDeg<T>(obj2.current()->curvingAngleRad(tt)) << std::endl;

            for (size_t j = 0; j < obj2.history().size(); ++j)
                std::cout << "* " << j << " " << (obj2.history().at(j)) << std::endl;
            std::cout << std::endl;
        }
    }
*/
