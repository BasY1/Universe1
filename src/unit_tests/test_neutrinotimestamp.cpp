#include "test_neutrinotimestamp.h"

Test_NeutrinoTimeStamp::Test_NeutrinoTimeStamp(QObject *parent)
    : QObject(parent)
{
}

void Test_NeutrinoTimeStamp::testInitGen1Float()
{
    testInitGen1<float>();
}
void Test_NeutrinoTimeStamp::testInitGen1Double()
{
    // testInitGen1<double>();
}
void Test_NeutrinoTimeStamp::testInitGen1LongDouble()
{
    // testInitGen1<long double>();
}
