#include "test_singularity.h"

Test_Singularity::Test_Singularity(QObject *parent)
    : QObject(parent)
{
}

void Test_Singularity::testObjectDataFloat()
{
    testObjectData<float>();
}

void Test_Singularity::testObjectDataDouble()
{
    testObjectData<double>();
}

void Test_Singularity::testObjectDataLongDouble()
{
    testObjectData<long double>();
}

void Test_Singularity::testObjectLongDouble()
{
    typedef long double T;

    SingularityObject<T> obj(0U, 10000, 1, SingularityObjectData<T>(2, Vec3<T>(), Vec3<T>(1, 0, 0), Vec3<T>()));

    obj.addStep(0.05);

    for (int i = 0; i < 500; ++i)
        obj.addStep(0.1);

    SingularityObjectData<T> obj2 = obj.getSource(1, 8, Vec3<T>(2, 2, 2));

    QVERIFY(TypeEquals<T>(obj2.timeStamp, T(5)));
}
