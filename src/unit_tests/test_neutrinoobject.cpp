#include "test_neutrinoobject.h"

Test_NeutrinoObject::Test_NeutrinoObject(QObject *parent)
    : QObject(parent)
{
}

void Test_NeutrinoObject::testInitGen1Float()
{
    testInitGen1<float>();
}
void Test_NeutrinoObject::testInitGen1Double()
{
    // testInitGen1<double>();
}
void Test_NeutrinoObject::testInitGen1LongDouble()
{
    // testInitGen1<long double>();
}
