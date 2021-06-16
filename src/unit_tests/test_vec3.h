#ifndef TEST_VEC3_H
#define TEST_VEC3_H

#include <QTest>

#include "../math/vec3.h"

class Test_Vec3 : public QObject
{
    Q_OBJECT
 private slots:
    void initTestCase();

    void testMathFloat();
    void testMathDouble();
    void testMathLongDouble();

 private:
    template <typename T>
    void testMath();
};

template <typename T>
void Test_Vec3::testMath()
{
    Vec3<T> v0(2, 3, 4);
    Vec3<T> v1(2, 3, 4);
    Vec3<T> v2(5, 9, 7);

    QVERIFY(v1.equals(v0));
    QVERIFY(v1 == v0);
    QVERIFY(v1 != v2);

    QVERIFY(!v1.isNull());
    QVERIFY(!v2.isNull());
    QVERIFY(Vec3<T>(0, 0, 0).isNull());
    QVERIFY(Vec3<T>().isNull());

    QVERIFY(-v1 == Vec3<T>(-2, -3, -4));
    QVERIFY(v1.inverted() == Vec3<T>(-2, -3, -4));

    QVERIFY((v1 + v2) == Vec3<T>(7, 12, 11));
    QVERIFY((v2 - v1) == Vec3<T>(3, 6, 3));
    QVERIFY((v1 * T(2)) == Vec3<T>(4, 6, 8));
    QVERIFY((v2 / T(2)) == Vec3<T>(2.5, 4.5, 3.5));

    v1 += Vec3<T>(4, 1, -2);
    QVERIFY(v1 == Vec3<T>(6, 4, 2));

    v1 *= T(2);
    QVERIFY(v1 == Vec3<T>(12, 8, 4));

    v1 /= T(4);
    QVERIFY(v1 == Vec3<T>(3, 2, 1));

    v1 -= Vec3<T>(0, -1, -2);
    QVERIFY(v1 == Vec3<T>(3, 3, 3));

    QVERIFY(Vec3<T>::cross(Vec3<T>(1, 0, 0), Vec3<T>(0, 1, 0)) == Vec3<T>(0, 0, 1));
    QVERIFY(Vec3<T>::cross(Vec3<T>(0, 1, 0), Vec3<T>(0, 0, 1)) == Vec3<T>(1, 0, 0));
    QVERIFY(Vec3<T>::cross(Vec3<T>(0, 0, 1), Vec3<T>(1, 0, 0)) == Vec3<T>(0, 1, 0));
    QVERIFY(Vec3<T>::cross(Vec3<T>(0, 1, 0), Vec3<T>(1, 0, 0)) == Vec3<T>(0, 0, -1));
    QVERIFY(Vec3<T>::cross(Vec3<T>(0, 0, 1), Vec3<T>(0, 1, 0)) == Vec3<T>(-1, 0, 0));
    QVERIFY(Vec3<T>::cross(Vec3<T>(1, 0, 0), Vec3<T>(0, 0, 1)) == Vec3<T>(0, -1, 0));

    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(1, 0, 0), Vec3<T>(0, 1, 0)) == Vec3<T>(0, 0, -1));
    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(0, 1, 0), Vec3<T>(0, 0, 1)) == Vec3<T>(-1, 0, 0));
    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(0, 0, 1), Vec3<T>(1, 0, 0)) == Vec3<T>(0, -1, 0));
    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(0, 1, 0), Vec3<T>(1, 0, 0)) == Vec3<T>(0, 0, 1));
    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(0, 0, 1), Vec3<T>(0, 1, 0)) == Vec3<T>(1, 0, 0));
    QVERIFY(Vec3<T>::crossLeftHand(Vec3<T>(1, 0, 0), Vec3<T>(0, 0, 1)) == Vec3<T>(0, 1, 0));

    QVERIFY(TypeEquals<T>(Vec3<T>::dot(Vec3<T>(1, 2, 3), Vec3<T>(6, 5, 4)), T(28)));

    QVERIFY(Vec3<T>(1, 0, 0).isNormalized());
    QVERIFY(Vec3<T>(0, 1, 0).isNormalized());
    QVERIFY(Vec3<T>(0, 0, 1).isNormalized());
    QVERIFY(!v1.isNormalized());

    v1.normalize();
    QVERIFY(v1 == Vec3<T>(T_SQRT3_3<T>(), T_SQRT3_3<T>(), T_SQRT3_3<T>()));
    QVERIFY(v1.isNormalized());

    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, 1, 0)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, 0, 1)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, -1, 0)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, 0, -1)));
    QVERIFY(Vec3<T>(-1, 0, 0).isPerpendicular(Vec3<T>(0, 1, 0)));
    QVERIFY(Vec3<T>(-1, 0, 0).isPerpendicular(Vec3<T>(0, 0, 1)));
    QVERIFY(Vec3<T>(-1, 0, 0).isPerpendicular(Vec3<T>(0, -1, 0)));
    QVERIFY(Vec3<T>(-1, 0, 0).isPerpendicular(Vec3<T>(0, 0, -1)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, 1, 1)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, 1, -1)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, -1, 1)));
    QVERIFY(Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(0, -1, -1)));

    QVERIFY(!Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(1, 0, 0)));
    QVERIFY(!Vec3<T>(1, 0, 0).isPerpendicular(Vec3<T>(1, 1, 1)));

    QVERIFY(Vec3<T>(1, 0, 0).perpendicularNormal() == Vec3<T>(0, 0, 1));
    QVERIFY(Vec3<T>(0, 1, 0).perpendicularNormal() == Vec3<T>(0, 0, -1));
    QVERIFY(Vec3<T>(0, 0, 1).perpendicularNormal() == Vec3<T>(0, 1, 0));
    QVERIFY(Vec3<T>(-1, 0, 0).perpendicularNormal() == Vec3<T>(0, 0, -1));
    QVERIFY(Vec3<T>(0, -1, 0).perpendicularNormal() == Vec3<T>(0, 0, 1));
    QVERIFY(Vec3<T>(0, 0, -1).perpendicularNormal() == Vec3<T>(0, -1, 0));

    bool tmp;

    QVERIFY(Vec3<T>(1, 0, 0).isSameDir(Vec3<T>(10, 0, 0)));
    QVERIFY(!Vec3<T>(1, 0, 0).isSameDir(Vec3<T>(-1, 0, 0)));

    QVERIFY(Vec3<T>(1, 0, 0).isParallel(Vec3<T>(10, 0, 0)));
    QVERIFY(Vec3<T>(1, 0, 0).isParallel(Vec3<T>(-10, 0, 0)));

    QVERIFY(Vec3<T>(1, 0, 0).isParallelInDir(Vec3<T>(10, 0, 0), tmp));
    QVERIFY(tmp);
    QVERIFY(Vec3<T>(1, 0, 0).isParallelInDir(Vec3<T>(-10, 0, 0), tmp));
    QVERIFY(!tmp);

    QVERIFY(Vec3<T>(1, 0, 0).rotated(Vec3<T>(0, 0, 1), T_PI_2<T>()) == Vec3<T>(0, 1, 0));

    QVERIFY(TypeEquals<T>(Vec3<T>(1, 0, 0).angleRad(Vec3<T>(0, 0, 1)), T_PI_2<T>()));
    QVERIFY(TypeEquals<T>(Vec3<T>(1, 0, 0).angleRad(Vec3<T>(0, 0, -1)), T_PI_2<T>()));

    QVERIFY(TypeEquals<T>(Vec3<T>(1, 0, 0).angleNormRad(Vec3<T>(0, 0, 1), Vec3<T>(0, -1, 0)), T_PI_2<T>()));
    QVERIFY(TypeEquals<T>(Vec3<T>(1, 0, 0).angleNormRad(Vec3<T>(0, 0, -1), Vec3<T>(0, -1, 0)), -T_PI_2<T>()));
}

#endif  // TEST_VEC3_H
