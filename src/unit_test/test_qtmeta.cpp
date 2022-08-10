#include "test_qtmeta.h"
/*
Universe1::UnitTest::Test_QtMetaObject1::Test_QtMetaObject1(QObject *_parent)
    : QObject(_parent)
//, m_valueBOOL(true)
//, m_valueINT(-1)
//, m_valueUINT(1)
//, m_valueLONG(-100)
//, m_valueULONG(100)
//, m_valueFLOAT(0.5F)
//, m_valueDOUBLE(3.14)
{
}

// QT_META_CPP_NOTIFY_BOOL(valueBOOL, ValueBOOL, Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_SIGNAL_INT(valueINT, ValueINT, emit changed(), Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_SIGNAL_UINT(valueUINT, ValueUINT, emit changed(), Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_NOTIFY_LONG(valueLONG, ValueLONG, Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_NOTIFY_ULONG(valueULONG, ValueULONG, Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_NOTIFY_FLOAT(valueFLOAT, ValueFLOAT, Universe1::UnitTest::Test_QtMetaObject1)
// QT_META_CPP_NOTIFY_DOUBLE(valueDOUBLE, ValueDOUBLE, Universe1::UnitTest::Test_QtMetaObject1)
*/
Universe1::UnitTest::Test_QtMeta::Test_QtMeta(QObject *_parent)
    : QObject(_parent)
{
}

void Universe1::UnitTest::Test_QtMeta::test1()
{
    /*
    using namespace Universe1::QtMeta;

    Test_QtMetaObject1 *o = new Test_QtMetaObject1();
    // const QMetaObject *mo = &Universe1::UnitTest::Test_QtMetaObject1::staticMetaObject;
    const QMetaObject *mo = findMetaObject("Test_QtMetaObject1");
    QVERIFY(mo != nullptr);

    // qDebug() << getPropertyNames(mo, _PropsCurrentLevel);
    // qDebug() << getPropertyNames(mo, _PropsRecursive);
    // qDebug() << getPropertyTypes(mo, _PropsCurrentLevel);
    // qDebug() << getPropertyTypes(mo, _PropsRecursive);

    // qDebug() << getPropertyValues(o, _PropsCurrentLevel);
    // qDebug() << getPropertyValues(o, _PropsRecursive);

    const QList<QPair<QString, QVariant>> propVals3 = getPropertyValues(o);
    qDebug() << toString(o);
    o->setObjectName("Test name");
    const QList<QPair<QString, QVariant>> propVals4 = getPropertyValues(o);
    QVERIFY(propVals3.size() + 1 == propVals4.size());
    // qDebug() << propVals3;
    // qDebug() << propVals4;
    qDebug() << toString(o);
*/
}
