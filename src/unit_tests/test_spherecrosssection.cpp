#include "test_spherecrosssection.h"

Test_SphereCrossSection::Test_SphereCrossSection(QObject *parent)
    : QObject(parent)
{
}

void Test_SphereCrossSection::testMathFloat()
{
    // testMath<float>();
}
void Test_SphereCrossSection::testMathDouble()
{
    // testMath<double>();
}
void Test_SphereCrossSection::testMathLongDouble()
{
    testMath<long double>();
}
