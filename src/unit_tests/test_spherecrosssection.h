#ifndef TEST_SPHERECROSSSECTION_H
#define TEST_SPHERECROSSSECTION_H

#include <QTest>

#include "../math/spherecrosssection.h"

class Test_SphereCrossSection : public QObject
{
    Q_OBJECT
 public:
    Test_SphereCrossSection(QObject *parent = nullptr);

 private slots:
    void testMathFloat();
    void testMathDouble();
    void testMathLongDouble();

 private:
    template <typename T>
    void testMath();
};

template <typename T>
void Test_SphereCrossSection::testMath()
{
    using namespace std;
    using namespace Universe1;
    using namespace Universe1::Math;
    using namespace Universe1::Type;
    using namespace Universe1::Const;

    Sphere<T> element;
    Sphere<T> wave;

    element.position.x = T_1<T>();
    element.radius = T_1<T>();
    wave.radius = T_2<T>();

    {
        wave.position.x = T_1<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_MISS_AFTER);
        QVERIFY(scs.waveInsideElement);
        QVERIFY(isNull<T>(scs.positionDistance));
        QVERIFY(isUnit<T>(scs.distanceOffset()));
    }

    {
        wave.position.x = T_2<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_TOUCH_AFTER);
        QVERIFY(scs.waveInsideElement);
    }

    {
        wave.position.x = T_3<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_CROSS_ELEMENT);
        QVERIFY(!scs.waveInsideElement);
        QVERIFY(isUnit<T>(scs.distanceOffset()));
        cout << wave.position.x << "  R" << scs.ratio() << "  V" << scs.crossSectionVolume() << "  W" << wave.volume()
             << "  V_W" << (scs.crossSectionVolume() / wave.volume()) << endl;
    }

    {
        wave.position.x = T_4<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_TOUCH_BEFORE);
        QVERIFY(!scs.waveInsideElement);
    }

    {
        wave.position.x = T(5);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_MISS_BEFORE);
        QVERIFY(!scs.waveInsideElement);
        QVERIFY(isUnit<T>(scs.distanceOffset()));
    }

    wave.radius = T_01<T>();

    {
        wave.position.x = T_1<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_MISS_BEFORE);
        QVERIFY(scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T(0.9l)));
    }

    {
        wave.position.x = T(1.5l);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_MISS_BEFORE);
        QVERIFY(scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T(0.4l)));
    }

    {
        wave.position.x = T(1.9l);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_TOUCH_BEFORE);
        QVERIFY(scs.waveInsideElement);
    }

    {
        wave.position.x = T(1.95l);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_CROSS_ELEMENT);
        QVERIFY(scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T(0.05l)));
        cout << wave.position.x << "  R" << scs.ratio() << "  V" << scs.crossSectionVolume() << "  W" << wave.volume()
             << "  V_W" << (scs.crossSectionVolume() / wave.volume()) << endl;
    }

    {
        wave.position.x = T_2<T>();
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_CROSS_ELEMENT);
        QVERIFY(scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T_01<T>()));
        cout << wave.position.x << "  R" << scs.ratio() << "  V" << scs.crossSectionVolume() << "  W" << wave.volume()
             << "  V_W" << (scs.crossSectionVolume() / wave.volume()) << endl;
    }

    {
        wave.position.x = T(2.05l);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_CROSS_ELEMENT);
        QVERIFY(!scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T(0.05l)));
        cout << wave.position.x << "  R" << scs.ratio() << "  V" << scs.crossSectionVolume() << "  W" << wave.volume()
             << "  V_W" << (scs.crossSectionVolume() / wave.volume()) << endl;
    }

    {
        wave.position.x = T(2.15l);
        const SphereCrossSection<T> scs(element, wave);
        QVERIFY(scs.crossSectionType == CROSS_WAVE_MISS_BEFORE);
        QVERIFY(!scs.waveInsideElement);
        QVERIFY(equals<T>(scs.distanceOffset(), T(0.05l)));
    }
}

#endif  // TEST_SPHERECROSSSECTION_H
