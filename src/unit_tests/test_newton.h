#ifndef TEST_NEWTON_H
#define TEST_NEWTON_H

#include <QTest>

#include "../simulation/newton/newtonobject.h"

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

    const T angle = toRad<T>(5);

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
}

#endif  // TEST_NEWTON_H
