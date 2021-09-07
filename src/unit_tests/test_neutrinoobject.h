#ifndef TEST_NEUTRINOOBJECT_H
#define TEST_NEUTRINOOBJECT_H

#include <QTest>

#include "../simulation/neutrino/neutrinoobject.h"

class Test_NeutrinoObject : public QObject
{
    Q_OBJECT
 public:
    Test_NeutrinoObject(QObject *parent = nullptr);

 private slots:
    void testInitGen1Float();
    void testInitGen1Double();
    void testInitGen1LongDouble();

 private:
    template <typename T>
    void testInitGen1();
};

template <typename T>
void Test_NeutrinoObject::testInitGen1()
{
    using namespace std;
    using namespace Universe1;
    using namespace Universe1::Math;
    using namespace Universe1::Type;
    using namespace Universe1::Const;
    using namespace Universe1::Simulation;
    using namespace Universe1::Simulation::GravityNeutrino;

    const size_t stepCount = 100U;
    const Constants<T> physics;

    const Sphere<T> eventSphere(physics.elementRadius, Vec3<T>());

    const T length = T_10<T>() * physics.elementRadius;

    NeutrinoTimeStamp<T> ts0;
    ts0.position.x = -length * T_05<T>();
    ts0.position.y = length * T_05<T>();
    ts0.moveVelocity1.x = T_1<T>();
    ts0.spinVelocity1.x = -T_1<T>();
    ts0.phase1.z = T_1<T>();

    Vec3<T> force;
    force.x = T_1<T>();
    QVERIFY(ts0.initGeneration1(force, physics) == NeutrinoGeneration1StraightMove);

    const T stepSize = length / static_cast<T>(stepCount);

    NeutrinoObject<T> obj(0U);
    obj.initHistory(false, stepCount - 1U, stepCount + 10U);

    obj.history()[0] = ts0;

    for (size_t i = 1U; i < stepCount; ++i)
        obj.history()[i] = ts0.moved(stepSize * static_cast<T>(i));

    std::vector<std::pair<size_t, size_t>> offsetRange =
        obj.stepsForSphereSource(physics, obj.current()->timeStamp, eventSphere);
    QVERIFY(offsetRange.size() == 1U);
    // for (const pair<size_t, size_t> &p : offsetRange)
    //     cout << p.first << " - " << p.second << endl;

    const NeutrinoTimeStamp<T> *ts1 = obj.historyTimeStampByOffset(offsetRange.front().first);
    const NeutrinoTimeStamp<T> *ts2 = obj.historyTimeStampByOffset(offsetRange.front().second);
    const NeutrinoTimeStamp<T> *ts3 = obj.historyTimeStampByOffset(offsetRange.front().first - 1U);
    const NeutrinoTimeStamp<T> *ts4 = obj.historyTimeStampByOffset(offsetRange.front().second + 1U);

    QVERIFY(ts1 != nullptr);
    QVERIFY(ts2 != nullptr);
    QVERIFY(ts3 != nullptr);
    QVERIFY(ts4 != nullptr);

    Sphere<T> waveSphere;
    waveSphere.reset((obj.current()->timeStamp - ts1->timeStamp) * physics.universeVelocity, ts1->position);
    QVERIFY(SphereCrossSection<T>(eventSphere, waveSphere).crossSectionType == CROSS_WAVE_CROSS_ELEMENT);

    waveSphere.reset((obj.current()->timeStamp - ts2->timeStamp) * physics.universeVelocity, ts2->position);
    QVERIFY(SphereCrossSection<T>(eventSphere, waveSphere).crossSectionType == CROSS_WAVE_CROSS_ELEMENT);

    waveSphere.reset((obj.current()->timeStamp - ts3->timeStamp) * physics.universeVelocity, ts3->position);
    QVERIFY(SphereCrossSection<T>(eventSphere, waveSphere).crossSectionType == CROSS_WAVE_MISS_BEFORE);

    waveSphere.reset((obj.current()->timeStamp - ts4->timeStamp) * physics.universeVelocity, ts4->position);
    QVERIFY(SphereCrossSection<T>(eventSphere, waveSphere).crossSectionType == CROSS_WAVE_MISS_AFTER);
}

#endif  // TEST_NEUTRINOOBJECT_H
