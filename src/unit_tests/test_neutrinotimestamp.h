#ifndef TEST_NEUTRINOTIMESTAMP_H
#define TEST_NEUTRINOTIMESTAMP_H

#include <QTest>

#include "../simulation/neutrino/neutrinotimestamp.h"

class Test_NeutrinoTimeStamp : public QObject
{
    Q_OBJECT
 public:
    Test_NeutrinoTimeStamp(QObject *parent = nullptr);

 private slots:
    void testInitGen1Float();
    void testInitGen1Double();
    void testInitGen1LongDouble();

 private:
    template <typename T>
    void testInitGen1();
};

template <typename T>
void Test_NeutrinoTimeStamp::testInitGen1()
{
    using namespace std;
    using namespace Universe1;
    using namespace Universe1::Math;
    using namespace Universe1::Type;
    using namespace Universe1::Const;
    using namespace Universe1::Simulation;
    using namespace Universe1::Simulation::GravityNeutrino;

    const Constants<T> physics;

    NeutrinoTimeStamp<T> ts;
    NeutrinoTimeStamp<T> ts2;
    Vec3<T> force;

    ts.moveVelocity1.x = T_1<T>();
    ts.spinVelocity1.x = -T_1<T>();
    ts.phase1.z = T_1<T>();

    force.x = T_1<T>();
    QVERIFY(ts.initGeneration1(force, physics) == NeutrinoGeneration1StraightMove);

    force.y = T_05<T>();
    QVERIFY(ts.initGeneration1(force, physics) == NeutrinoGeneration1);

    force.y = T_1<T>();
    QVERIFY(ts.initGeneration1(force, physics) == NeutrinoGeneration12);

    force.y = T_2<T>();

    Vec3<T> force2;
    force2.x = -T_05<T>();
    force2.y = T_01<T>();
    force2.z = T_001<T>();
    QVERIFY(ts.initGeneration1(force, physics) == NeutrinoGeneration2);
    QVERIFY(equals<T>(T_05<T>(), ts.position2.y));
    QVERIFY(ts.initGeneration2(force2, physics) == NeutrinoGeneration2);

    force2.clear();
    force2.x = -T_2<T>();
    QVERIFY(ts.initGeneration1(force, physics) == NeutrinoGeneration2);
    QVERIFY(ts.initGeneration2(force2, physics) == NeutrinoGeneration3);
    QVERIFY(equals<T>(T_05<T>(), ts.position2.y));

    ts2 = ts.moved(T_001<T>());
    for (const std::pair<std::string, std::string> &p : ts.getDetails(physics.elementRadius))
        cout << p.first << ": " << p.second << endl;
    cout << "---------------------------------------" << endl;
    for (const std::pair<std::string, std::string> &p : ts2.getDetails(physics.elementRadius))
        cout << p.first << ": " << p.second << endl;
    cout << endl << endl;
}

#endif  // TEST_NEUTRINOTIMESTAMP_H
