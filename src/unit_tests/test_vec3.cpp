#include "test_vec3.h"

Test_Vec3::Test_Vec3(QObject *parent)
    : QObject(parent)
{
}

void Test_Vec3::initTestCase()
{
    Vec3<float> vf(2.0f / 3.0f, 2.0f, 3.0f);
    Vec3<double> vd(2.0 / 3.0, 2.0, 3.0);
    Vec3<long double> vl(2.0l / 3.0l, 2.0l, 3.0l);

    TypeSetDefaultPrecision<float>(std::cout);
    std::cout << "Default float:        " << vf << std::endl;
    TypeSetDefaultPrecision<double>(std::cout);
    std::cout << "Default double:       " << vd << std::endl;
    TypeSetDefaultPrecision<long double>(std::cout);
    std::cout << "Default long double:  " << vl << std::endl;
}

void Test_Vec3::testMathFloat()
{
    testMath<float>();
}
void Test_Vec3::testMathDouble()
{
    testMath<double>();
}
void Test_Vec3::testMathLongDouble()
{
    testMath<long double>();
}
