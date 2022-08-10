#include "test_metaclassinfo.h"

Universe1::UnitTest::Test_MetaClassInfoObject1::Test_MetaClassInfoObject1(QObject *_parent)
    : QObject(_parent)
{
}

QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo2(QString _value)
{
    if (_value == "info2")
        return "OK info2";
    return "FAIL info2";
}
QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo3(const QString _value)
{
    if (_value == "info3")
        return "OK info3";
    return "FAIL info3";
}
QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo4(const QString &_value)
{
    if (_value == "info4")
        return "OK info4";
    return "FAIL info4";
}
QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo5()
{
    return "OK info5";
}

QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo6(const QString &_value)
{
    if (_value == "text6")
        return "OK info6";
    return "FAIL info6";
}

QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo7(const QString &_value)
{
    if (_value == "text7")
        return "OK info7";
    return "FAIL info7";
}

QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo8(int _value)
{
    if (_value == 8)
        return "OK info8";
    return "FAIL info8";
}

QString Universe1::UnitTest::Test_MetaClassInfoObject1::getInfo9(const int _value)
{
    if (_value == 9)
        return "OK info9";
    return "FAIL info9";
}

Universe1::UnitTest::Test_MetaClassInfo::Test_MetaClassInfo(QObject *_parent)
    : QObject(_parent)
{
}

void Universe1::UnitTest::Test_MetaClassInfo::test_takeClassInfos()
{
    using namespace QtMeta;

    Test_MetaClassInfoObject1 *obj = new Test_MetaClassInfoObject1();
    const QMetaObject *mo = obj->metaObject();

    QList<QMetaClassInfo> list = buildClassInfoList(mo);
    int s = list.size();

    QCOMPARE(takeClassInfo("info1", list, mo), "Info   <b>1</b>");
    QCOMPARE(list.size(), --s);

    QPair<QString, bool> tmp{"", false};
    QVERIFY(takeClassInfoText(tmp, "info2", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info2");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info3", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info3");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info4", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info4");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info5", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info5");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info6", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info6");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info7", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info7");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info8", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info8");
    QVERIFY(tmp.second);

    QVERIFY(takeClassInfoText(tmp, "info9", list, obj));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmp.first, "OK info9");
    QVERIFY(tmp.second);

    tmp.first = "aaaa";
    QVERIFY(!takeClassInfoText(tmp, "ERROR", list, obj));
    QCOMPARE(list.size(), s);
    QCOMPARE(tmp.first, "aaaa");
    QVERIFY(!tmp.second);

    QStringList l1 = takeClassInfos("info10", list);
    QCOMPARE(list.size(), s - 2);
    QCOMPARE(l1.size(), 2);
    QCOMPARE(l1[0], "info10 1");
    QCOMPARE(l1[1], "info10 2");
    s -= 2;

    bool tmpBool = false;
    QVERIFY(takeClassInfoBool(tmpBool, "info12", list, mo));
    QCOMPARE(list.size(), --s);
    QVERIFY(tmpBool);

    QVERIFY(takeClassInfoBool(tmpBool, "info13", list, mo));
    QCOMPARE(list.size(), --s);
    QVERIFY(!tmpBool);

    QVERIFY(!takeClassInfoBool(tmpBool, "ERROR", list, mo));
    QCOMPARE(list.size(), s);
    QVERIFY(!tmpBool);

    int tmpInt = -1;
    QVERIFY(takeClassInfoNumber(tmpInt, "info14", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmpInt, -14);

    float tmpFloat = -1;
    QVERIFY(takeClassInfoNumber(tmpFloat, "info15", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmpFloat, 15.1F);

    double tmpDouble = -1;
    QVERIFY(takeClassInfoNumber(tmpDouble, "info16", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(tmpDouble, 16.123);

    int r1 = -5, r2 = -5;
    QVERIFY(takeClassInfoNumbers(r1, r2, "info17_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(r1, -1);
    QCOMPARE(r2, 2);

    qulonglong u1 = 1, u2 = 2;
    QVERIFY(takeClassInfoNumbers(u1, u2, "info18_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(u1, 100U);
    QCOMPARE(u2, 2000000U);

    float f1 = -3, f2 = -3;
    QVERIFY(takeClassInfoNumbers(f1, f2, "info19_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(f1, 0.0F);
    QCOMPARE(f2, 2.43F);

    QTime t1, t2;
    QVERIFY(takeClassInfoNumbers(t1, t2, "info20_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(t1, QTime(0, 0, 0));
    QCOMPARE(t2, QTime(2, 15, 1, 123));

    QDate d1, d2;
    QVERIFY(takeClassInfoNumbers(d1, d2, "info21_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(d1, QDate(2008, 1, 1));
    QCOMPARE(d2, QDate(2028, 12, 31));

    QDateTime dt1, dt2;
    QVERIFY(takeClassInfoNumbers(dt1, dt2, "info22_range", list, mo));
    QCOMPARE(list.size(), --s);
    QCOMPARE(dt1, QDateTime(QDate(2009, 1, 1), QTime(7, 0, 0)));
    QCOMPARE(dt2, QDateTime(QDate(2029, 12, 31), QTime(2, 15, 20, 200)));
}
