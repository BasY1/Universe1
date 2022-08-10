#include "test_metaproperty.h"

Universe1::UnitTest::Test_MetaPropertyObject1::Test_MetaPropertyObject1(QObject *_parent)
    : QObject(_parent)
    , m_value_RO_Bool(true)
    , m_value_RO_Int(-1)
    , m_value_RO_UInt(1)
    , m_value_RO_Long(-100)
    , m_value_RO_ULong(100)
    , m_value_RO_Float(0.1)
    , m_value_RO_Double(3.14)
    , m_value_RO_String("test")
    , m_value_RO_Time(5, 10, 5)
    , m_value_RO_Date(2020, 2, 3)
    , m_value_RO_DateTime({2020, 2, 3}, {5, 10, 5, 123})
    , m_value_RO_Vec3D(1.1, 2.2, 3.3)
    , m_value_RO_Color(1, 2, 3, 4)
    , m_value_RO_Enum(Lit2)
    , m_value_RO_Flag(Flag1 | Flag3)

    , m_value_RW_Bool(true)
    , m_value_RW_Int(-1)
    , m_value_RW_UInt(1)
    , m_value_RW_Long(-100)
    , m_value_RW_ULong(100)
    , m_value_RW_Float(0.1)
    , m_value_RW_Double(3.14)
    , m_value_RW_String("test")
    , m_value_RW_Time(5, 10, 5)
    , m_value_RW_Date(2020, 2, 3)
    , m_value_RW_DateTime({2020, 2, 3}, {5, 10, 5, 123})
    , m_value_RW_Vec3D(1.1, 2.2, 3.3)
    , m_value_RW_Color(1, 2, 3, 4)
    , m_value_RW_Enum(Lit2)
    , m_value_RW_Flag(Flag1 | Flag3)

    , m_value_NO_Bool(true)
    , m_value_NO_Int(-1)
    , m_value_NO_UInt(1)
    , m_value_NO_Long(-100)
    , m_value_NO_ULong(100)
    , m_value_NO_Float(0.1)
    , m_value_NO_Double(3.14)
    , m_value_NO_String("test")
    , m_value_NO_Time(5, 10, 5)
    , m_value_NO_Date(2020, 2, 3)
    , m_value_NO_DateTime({2020, 2, 3}, {5, 10, 5, 123})
    , m_value_NO_Vec3D(1.1, 2.2, 3.3)
    , m_value_NO_Color(1, 2, 3, 4)
    , m_value_NO_Enum(Lit2)

    , m_value_CH_Bool(true)
    , m_value_CH_Int(-1)
    , m_value_CH_UInt(1)
    , m_value_CH_Long(-100)
    , m_value_CH_ULong(100)
    , m_value_CH_Float(0.1)
    , m_value_CH_Double(3.14)
    , m_value_CH_String("test")
    , m_value_CH_Time(5, 10, 5)
    , m_value_CH_Date(2020, 2, 3)
    , m_value_CH_DateTime({2020, 2, 3}, {5, 10, 5, 123})
    , m_value_CH_Vec3D(1.1, 2.2, 3.3)
    , m_value_CH_Color(1, 2, 3, 4)
    , m_value_CH_Enum(Lit2)

    , m_value_CN_Bool(true)
    , m_value_CN_Int(-1)
    , m_value_CN_UInt(1)
    , m_value_CN_Long(-100)
    , m_value_CN_ULong(100)
    , m_value_CN_Float(0.1)
    , m_value_CN_Double(3.14)
    , m_value_CN_String("test")
    , m_value_CN_Time(5, 10, 5)
    , m_value_CN_Date(2020, 2, 3)
    , m_value_CN_DateTime({2020, 2, 3}, {5, 10, 5, 123})
    , m_value_CN_Vec3D(1.1, 2.2, 3.3)
    , m_value_CN_Color(1, 2, 3, 4)
    , m_value_CN_Enum(Lit2)
{
}

QTMETA_CPP_BOOL_RO(value_RO_Bool, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_INT_RO(value_RO_Int, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_UINT_RO(value_RO_UInt, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_LONGLONG_RO(value_RO_Long, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ULONGLONG_RO(value_RO_ULong, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_FLOAT_RO(value_RO_Float, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DOUBLE_RO(value_RO_Double, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_STRING_RO(value_RO_String, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_TIME_RO(value_RO_Time, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATE_RO(value_RO_Date, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATETIME_RO(value_RO_DateTime, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_VEC3D_RO(value_RO_Vec3D, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_COLOR_RO(value_RO_Color, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_RO(Universe1::UnitTest::Test_MetaPropertyObject1::TestEnum,
                   value_RO_Enum,
                   Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_RO(Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags,
                   value_RO_Flag,
                   Universe1::UnitTest::Test_MetaPropertyObject1)

QTMETA_CPP_BOOL_RW(value_RW_Bool, Value_RW_Bool, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_INT_RW(value_RW_Int, Value_RW_Int, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_UINT_RW(value_RW_UInt, Value_RW_UInt, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_LONGLONG_RW(value_RW_Long, Value_RW_Long, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ULONGLONG_RW(value_RW_ULong, Value_RW_ULong, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_FLOAT_RW(value_RW_Float, Value_RW_Float, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DOUBLE_RW(value_RW_Double, Value_RW_Double, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_STRING_RW(value_RW_String, Value_RW_String, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_TIME_RW(value_RW_Time, Value_RW_Time, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATE_RW(value_RW_Date, Value_RW_Date, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATETIME_RW(value_RW_DateTime, Value_RW_DateTime, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_VEC3D_RW(value_RW_Vec3D, Value_RW_Vec3D, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_COLOR_RW(value_RW_Color, Value_RW_Color, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_RW(Universe1::UnitTest::Test_MetaPropertyObject1::TestEnum,
                   value_RW_Enum,
                   Value_RW_Enum,
                   Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_RW(Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags,
                   value_RW_Flag,
                   Value_RW_Flag,
                   Universe1::UnitTest::Test_MetaPropertyObject1)

QTMETA_CPP_BOOL_NO(value_NO_Bool, Value_NO_Bool, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_INT_NO(value_NO_Int, Value_NO_Int, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_UINT_NO(value_NO_UInt, Value_NO_UInt, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_LONGLONG_NO(value_NO_Long, Value_NO_Long, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ULONGLONG_NO(value_NO_ULong, Value_NO_ULong, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_FLOAT_NO(value_NO_Float, Value_NO_Float, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DOUBLE_NO(value_NO_Double, Value_NO_Double, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_STRING_NO(value_NO_String, Value_NO_String, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_TIME_NO(value_NO_Time, Value_NO_Time, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATE_NO(value_NO_Date, Value_NO_Date, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATETIME_NO(value_NO_DateTime, Value_NO_DateTime, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_VEC3D_NO(value_NO_Vec3D, Value_NO_Vec3D, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_COLOR_NO(value_NO_Color, Value_NO_Color, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_NO(Universe1::UnitTest::Test_MetaPropertyObject1::TestEnum,
                   value_NO_Enum,
                   Value_NO_Enum,
                   Universe1::UnitTest::Test_MetaPropertyObject1)

QTMETA_CPP_BOOL_CH(value_CH_Bool, Value_CH_Bool, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_INT_CH(value_CH_Int, Value_CH_Int, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_UINT_CH(value_CH_UInt, Value_CH_UInt, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_LONGLONG_CH(value_CH_Long, Value_CH_Long, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ULONGLONG_CH(value_CH_ULong, Value_CH_ULong, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_FLOAT_CH(value_CH_Float, Value_CH_Float, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DOUBLE_CH(value_CH_Double, Value_CH_Double, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_STRING_CH(value_CH_String, Value_CH_String, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_TIME_CH(value_CH_Time, Value_CH_Time, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATE_CH(value_CH_Date, Value_CH_Date, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATETIME_CH(value_CH_DateTime, Value_CH_DateTime, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_VEC3D_CH(value_CH_Vec3D, Value_CH_Vec3D, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_COLOR_CH(value_CH_Color, Value_CH_Color, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_CH(Universe1::UnitTest::Test_MetaPropertyObject1::TestEnum,
                   value_CH_Enum,
                   Value_CH_Enum,
                   Universe1::UnitTest::Test_MetaPropertyObject1)

QTMETA_CPP_BOOL_CN(value_CN_Bool, Value_CN_Bool, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_INT_CN(value_CN_Int, Value_CN_Int, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_UINT_CN(value_CN_UInt, Value_CN_UInt, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_LONGLONG_CN(value_CN_Long, Value_CN_Long, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ULONGLONG_CN(value_CN_ULong, Value_CN_ULong, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_FLOAT_CN(value_CN_Float, Value_CN_Float, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DOUBLE_CN(value_CN_Double, Value_CN_Double, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_STRING_CN(value_CN_String, Value_CN_String, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_TIME_CN(value_CN_Time, Value_CN_Time, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATE_CN(value_CN_Date, Value_CN_Date, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_DATETIME_CN(value_CN_DateTime, Value_CN_DateTime, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_VEC3D_CN(value_CN_Vec3D, Value_CN_Vec3D, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_COLOR_CN(value_CN_Color, Value_CN_Color, Universe1::UnitTest::Test_MetaPropertyObject1)
QTMETA_CPP_ENUM_CN(Universe1::UnitTest::Test_MetaPropertyObject1::TestEnum,
                   value_CN_Enum,
                   Value_CN_Enum,
                   Universe1::UnitTest::Test_MetaPropertyObject1)

Universe1::UnitTest::Test_MetaPropertyObject2::Test_MetaPropertyObject2(QObject *_parent)
    : QObject(_parent)
    //, m_objRO(nullptr)
    , m_objRO(new Test_MetaPropertyObject1(this))
    , m_objRW(new Test_MetaPropertyObject1(this))
    , m_objNO(new Test_MetaPropertyObject1(this))
    , m_objCH(new Test_MetaPropertyObject1(this))
    , m_objCN(new Test_MetaPropertyObject1(this))
//, m_objRO(new Test_MetaPropertyObject1())
{
    connectObjCH();
    connectObjCN();
}

Universe1::UnitTest::Test_MetaPropertyObject2::~Test_MetaPropertyObject2()
{
    disconnectObjCH();
    disconnectObjCN();
}

QTMETA_CPP_OBJ_RO(Universe1::UnitTest::Test_MetaPropertyObject1, objRO, Universe1::UnitTest::Test_MetaPropertyObject2)
QTMETA_CPP_OBJ_RW(Universe1::UnitTest::Test_MetaPropertyObject1,
                  objRW,
                  ObjRW,
                  Universe1::UnitTest::Test_MetaPropertyObject2)
QTMETA_CPP_OBJ_NO(Universe1::UnitTest::Test_MetaPropertyObject1,
                  objNO,
                  ObjNO,
                  Universe1::UnitTest::Test_MetaPropertyObject2)
QTMETA_CPP_CH_OBJ_CH(Universe1::UnitTest::Test_MetaPropertyObject1,
                     objCH,
                     ObjCH,
                     Universe1::UnitTest::Test_MetaPropertyObject2)
QTMETA_CPP_CH_OBJ_CN(Universe1::UnitTest::Test_MetaPropertyObject1,
                     objCN,
                     ObjCN,
                     Universe1::UnitTest::Test_MetaPropertyObject2)

Universe1::UnitTest::Test_MetaProperty::Test_MetaProperty(QObject *_parent)
    : QObject(_parent)
{
}

void Universe1::UnitTest::Test_MetaProperty::testNativeRO()
{
    using namespace QtMeta;

    Test_MetaPropertyObject1 *obj = new Test_MetaPropertyObject1();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    const QVector<const char *> checkNames = {"value_RO_Bool",
                                              "value_RO_Int",
                                              "value_RO_UInt",
                                              "value_RO_Long",
                                              "value_RO_ULong",
                                              "value_RO_Float",
                                              "value_RO_Double",
                                              "value_RO_String",
                                              "value_RO_Time",
                                              "value_RO_Date",
                                              "value_RO_DateTime",
                                              "value_RO_Vec3D",
                                              "value_RO_Color",
                                              "value_RO_Enum",
                                              "value_RO_Flag"};

    QHash<const char *, MetaProperty *> checkData;

    for (const char *const p : checkNames)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(!prop->isWritable(), p);

        QVERIFY2(!prop->hasNotifySignal(), p);
        QVERIFY2(!prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeDisabled, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    QCOMPARE(checkData.size(), checkNames.size());

    QCOMPARE(checkData["value_RO_Bool"]->defaultValue().type(), QVariant::Bool);
    QCOMPARE(checkData["value_RO_Bool"]->defaultValue().toBool(), true);
    QCOMPARE(checkData["value_RO_Int"]->defaultValue().type(), QVariant::Int);
    QCOMPARE(checkData["value_RO_Int"]->defaultValue().toInt(), -1);
    QCOMPARE(checkData["value_RO_UInt"]->defaultValue().type(), QVariant::UInt);
    QCOMPARE(checkData["value_RO_UInt"]->defaultValue().toUInt(), 1U);
    QCOMPARE(checkData["value_RO_Long"]->defaultValue().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_RO_Long"]->defaultValue().toLongLong(), -100L);
    QCOMPARE(checkData["value_RO_ULong"]->defaultValue().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_RO_ULong"]->defaultValue().toLongLong(), 100L);
    QCOMPARE(checkData["value_RO_Float"]->defaultValue().type(), QMetaType::Float);
    QCOMPARE(checkData["value_RO_Float"]->defaultValue().toFloat(), 0.1F);
    QCOMPARE(checkData["value_RO_Double"]->defaultValue().type(), QVariant::Double);
    QCOMPARE(checkData["value_RO_Double"]->defaultValue().toDouble(), 3.14);
    QCOMPARE(checkData["value_RO_String"]->defaultValue().type(), QVariant::String);
    QCOMPARE(checkData["value_RO_String"]->defaultValue().toString(), "test");
    QCOMPARE(checkData["value_RO_Time"]->defaultValue().type(), QVariant::Time);
    QCOMPARE(checkData["value_RO_Time"]->defaultValue().toTime(), QTime(5, 10, 5));
    QCOMPARE(checkData["value_RO_Date"]->defaultValue().type(), QVariant::Date);
    QCOMPARE(checkData["value_RO_Date"]->defaultValue().toDate(), QDate(2020, 2, 3));
    QCOMPARE(checkData["value_RO_DateTime"]->defaultValue().type(), QVariant::DateTime);
    QCOMPARE(checkData["value_RO_DateTime"]->defaultValue().toDateTime(), QDateTime({2020, 2, 3}, {5, 10, 5, 123}));
    QCOMPARE(checkData["value_RO_Vec3D"]->defaultValue().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_RO_Vec3D"]->defaultValue().value<QVector3D>(), QVector3D(1.1, 2.2, 3.3));
    QCOMPARE(checkData["value_RO_Color"]->defaultValue().type(), QVariant::Color);
    QCOMPARE(checkData["value_RO_Color"]->defaultValue().value<QColor>(), QColor(1, 2, 3, 4));
    QCOMPARE(checkData["value_RO_Enum"]->defaultValue().value<Test_MetaPropertyObject1::TestEnum>(),
             Test_MetaPropertyObject1::Lit2);

    const Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags tmp =
        static_cast<Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags>(
            checkData["value_RO_Flag"]->defaultValue().toInt());
    QVERIFY(tmp.testFlag(Test_MetaPropertyObject1::Flag1));
    QVERIFY(tmp.testFlag(Test_MetaPropertyObject1::Flag3));
    QVERIFY(!tmp.testFlag(Test_MetaPropertyObject1::Flag2));

    QCOMPARE(checkData["value_RO_Float"]->decimals(), QTMETA_DEFAULT_FLOAT_DECIMALS);
    QCOMPARE(checkData["value_RO_Double"]->decimals(), QTMETA_DEFAULT_DOUBLE_DECIMALS);
}

void Universe1::UnitTest::Test_MetaProperty::testNativeRW()
{
    using namespace QtMeta;

    Test_MetaPropertyObject1 *obj = new Test_MetaPropertyObject1();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    const QVector<const char *> checkNames1 = {"value_RW_Bool",
                                               "value_RW_String",
                                               "value_RW_Time",
                                               "value_RW_Date",
                                               "value_RW_DateTime",
                                               "value_RW_Color",
                                               "value_RW_Enum",
                                               "value_RW_Flag"};

    const QVector<const char *> checkNames2 = {"value_RW_Int",
                                               "value_RW_UInt",
                                               "value_RW_Long",
                                               "value_RW_ULong",
                                               "value_RW_Float",
                                               "value_RW_Double",
                                               "value_RW_Vec3D"};

    QHash<const char *, MetaProperty *> checkData;

    for (const char *const p : checkNames1)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(!prop->hasNotifySignal(), p);
        QVERIFY2(!prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeDisabled, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    for (const char *const p : checkNames2)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(!prop->hasNotifySignal(), p);
        QVERIFY2(!prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeMinimum, p);
        QVERIFY2(prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    QCOMPARE(checkData.size(), checkNames1.size() + checkNames2.size());

    QCOMPARE(checkData["value_RW_Bool"]->defaultValue().type(), QVariant::Bool);
    QCOMPARE(checkData["value_RW_Bool"]->defaultValue().toBool(), true);
    QCOMPARE(checkData["value_RW_Int"]->defaultValue().type(), QVariant::Int);
    QCOMPARE(checkData["value_RW_Int"]->defaultValue().toInt(), -1);
    QCOMPARE(checkData["value_RW_UInt"]->defaultValue().type(), QVariant::UInt);
    QCOMPARE(checkData["value_RW_UInt"]->defaultValue().toUInt(), 1U);
    QCOMPARE(checkData["value_RW_Long"]->defaultValue().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_RW_Long"]->defaultValue().toLongLong(), -100L);
    QCOMPARE(checkData["value_RW_ULong"]->defaultValue().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_RW_ULong"]->defaultValue().toLongLong(), 100L);
    QCOMPARE(checkData["value_RW_Float"]->defaultValue().type(), QMetaType::Float);
    QCOMPARE(checkData["value_RW_Float"]->defaultValue().toFloat(), 0.1F);
    QCOMPARE(checkData["value_RW_Double"]->defaultValue().type(), QVariant::Double);
    QCOMPARE(checkData["value_RW_Double"]->defaultValue().toDouble(), 3.14);
    QCOMPARE(checkData["value_RW_String"]->defaultValue().type(), QVariant::String);
    QCOMPARE(checkData["value_RW_String"]->defaultValue().toString(), "test");
    QCOMPARE(checkData["value_RW_Time"]->defaultValue().type(), QVariant::Time);
    QCOMPARE(checkData["value_RW_Time"]->defaultValue().toTime(), QTime(5, 10, 5));
    QCOMPARE(checkData["value_RW_Date"]->defaultValue().type(), QVariant::Date);
    QCOMPARE(checkData["value_RW_Date"]->defaultValue().toDate(), QDate(2020, 2, 3));
    QCOMPARE(checkData["value_RW_DateTime"]->defaultValue().type(), QVariant::DateTime);
    QCOMPARE(checkData["value_RW_DateTime"]->defaultValue().toDateTime(), QDateTime({2020, 2, 3}, {5, 10, 5, 123}));
    QCOMPARE(checkData["value_RW_Vec3D"]->defaultValue().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_RW_Vec3D"]->defaultValue().value<QVector3D>(), QVector3D(1.1, 2.2, 3.3));
    QCOMPARE(checkData["value_RW_Color"]->defaultValue().type(), QVariant::Color);
    QCOMPARE(checkData["value_RW_Color"]->defaultValue().value<QColor>(), QColor(1, 2, 3, 4));
    QCOMPARE(checkData["value_RW_Enum"]->defaultValue().value<Test_MetaPropertyObject1::TestEnum>(),
             Test_MetaPropertyObject1::Lit2);

    const Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags tmp =
        static_cast<Universe1::UnitTest::Test_MetaPropertyObject1::TestFlags>(
            checkData["value_RW_Flag"]->defaultValue().toInt());
    QVERIFY(tmp.testFlag(Test_MetaPropertyObject1::Flag1));
    QVERIFY(tmp.testFlag(Test_MetaPropertyObject1::Flag3));
    QVERIFY(!tmp.testFlag(Test_MetaPropertyObject1::Flag2));

    QCOMPARE(checkData["value_RW_Int"]->rangeMinimum().type(), QVariant::Int);
    QCOMPARE(checkData["value_RW_Int"]->rangeMinimum().toInt(), -3);
    QCOMPARE(checkData["value_RW_UInt"]->rangeMinimum().type(), QVariant::UInt);
    QCOMPARE(checkData["value_RW_UInt"]->rangeMinimum().toUInt(), 3U);
    QCOMPARE(checkData["value_RW_Long"]->rangeMinimum().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_RW_Long"]->rangeMinimum().toLongLong(), -300L);
    QCOMPARE(checkData["value_RW_ULong"]->rangeMinimum().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_RW_ULong"]->rangeMinimum().toLongLong(), 30L);
    QCOMPARE(checkData["value_RW_Float"]->rangeMinimum().type(), QMetaType::Float);
    QCOMPARE(checkData["value_RW_Float"]->rangeMinimum().toFloat(), -4.7F);
    QCOMPARE(checkData["value_RW_Double"]->rangeMinimum().type(), QVariant::Double);
    QCOMPARE(checkData["value_RW_Double"]->rangeMinimum().toDouble(), -3.14);
    QCOMPARE(checkData["value_RW_Vec3D"]->rangeMinimum().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_RW_Vec3D"]->rangeMinimum().value<QVector3D>(), QVector3D(-5, -4, -3));

    QCOMPARE(checkData["value_RW_Float"]->decimals(), QTMETA_DEFAULT_FLOAT_DECIMALS);
    QCOMPARE(checkData["value_RW_Double"]->decimals(), QTMETA_DEFAULT_DOUBLE_DECIMALS);
}

void Universe1::UnitTest::Test_MetaProperty::testNativeNO()
{
    using namespace QtMeta;

    Test_MetaPropertyObject1 *obj = new Test_MetaPropertyObject1();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    const QVector<const char *> checkNames1 = {
        "value_NO_Bool", "value_NO_Time", "value_NO_Date", "value_NO_DateTime", "value_NO_Color", "value_NO_Enum"};

    const QVector<const char *> checkNames2 = {"value_NO_Int",
                                               "value_NO_UInt",
                                               "value_NO_Long",
                                               "value_NO_ULong",
                                               "value_NO_Float",
                                               "value_NO_Double",
                                               "value_NO_Vec3D",
                                               "value_NO_String"};

    QHash<const char *, MetaProperty *> checkData;

    for (const char *const p : checkNames1)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(prop->hasNotifySignal(), p);
        QVERIFY2(!prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeDisabled, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    for (const char *const p : checkNames2)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(prop->hasNotifySignal(), p);
        QVERIFY2(!prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeMaximum, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    QCOMPARE(checkData.size(), checkNames1.size() + checkNames2.size());

    QCOMPARE(checkData["value_NO_Bool"]->defaultValue().type(), QVariant::Bool);
    QCOMPARE(checkData["value_NO_Bool"]->defaultValue().toBool(), true);
    QCOMPARE(checkData["value_NO_Int"]->defaultValue().type(), QVariant::Int);
    QCOMPARE(checkData["value_NO_Int"]->defaultValue().toInt(), -1);
    QCOMPARE(checkData["value_NO_UInt"]->defaultValue().type(), QVariant::UInt);
    QCOMPARE(checkData["value_NO_UInt"]->defaultValue().toUInt(), 1U);
    QCOMPARE(checkData["value_NO_Long"]->defaultValue().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_NO_Long"]->defaultValue().toLongLong(), -100L);
    QCOMPARE(checkData["value_NO_ULong"]->defaultValue().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_NO_ULong"]->defaultValue().toLongLong(), 100L);
    QCOMPARE(checkData["value_NO_Float"]->defaultValue().type(), QMetaType::Float);
    QCOMPARE(checkData["value_NO_Float"]->defaultValue().toFloat(), 0.1F);
    QCOMPARE(checkData["value_NO_Double"]->defaultValue().type(), QVariant::Double);
    QCOMPARE(checkData["value_NO_Double"]->defaultValue().toDouble(), 3.14);
    QCOMPARE(checkData["value_NO_String"]->defaultValue().type(), QVariant::String);
    QCOMPARE(checkData["value_NO_String"]->defaultValue().toString(), "test");
    QCOMPARE(checkData["value_NO_Time"]->defaultValue().type(), QVariant::Time);
    QCOMPARE(checkData["value_NO_Time"]->defaultValue().toTime(), QTime(5, 10, 5));
    QCOMPARE(checkData["value_NO_Date"]->defaultValue().type(), QVariant::Date);
    QCOMPARE(checkData["value_NO_Date"]->defaultValue().toDate(), QDate(2020, 2, 3));
    QCOMPARE(checkData["value_NO_DateTime"]->defaultValue().type(), QVariant::DateTime);
    QCOMPARE(checkData["value_NO_DateTime"]->defaultValue().toDateTime(), QDateTime({2020, 2, 3}, {5, 10, 5, 123}));
    QCOMPARE(checkData["value_NO_Vec3D"]->defaultValue().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_NO_Vec3D"]->defaultValue().value<QVector3D>(), QVector3D(1.1, 2.2, 3.3));
    QCOMPARE(checkData["value_NO_Color"]->defaultValue().type(), QVariant::Color);
    QCOMPARE(checkData["value_NO_Color"]->defaultValue().value<QColor>(), QColor(1, 2, 3, 4));
    QCOMPARE(checkData["value_NO_Enum"]->defaultValue().value<Test_MetaPropertyObject1::TestEnum>(),
             Test_MetaPropertyObject1::Lit2);

    QCOMPARE(checkData["value_NO_Int"]->rangeMaximum().type(), QVariant::Int);
    QCOMPARE(checkData["value_NO_Int"]->rangeMaximum().toInt(), -3);
    QCOMPARE(checkData["value_NO_UInt"]->rangeMaximum().type(), QVariant::UInt);
    QCOMPARE(checkData["value_NO_UInt"]->rangeMaximum().toUInt(), 3U);
    QCOMPARE(checkData["value_NO_Long"]->rangeMaximum().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_NO_Long"]->rangeMaximum().toLongLong(), -300L);
    QCOMPARE(checkData["value_NO_ULong"]->rangeMaximum().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_NO_ULong"]->rangeMaximum().toLongLong(), 30L);
    QCOMPARE(checkData["value_NO_Float"]->rangeMaximum().type(), QMetaType::Float);
    QCOMPARE(checkData["value_NO_Float"]->rangeMaximum().toFloat(), -4.7F);
    QCOMPARE(checkData["value_NO_Double"]->rangeMaximum().type(), QVariant::Double);
    QCOMPARE(checkData["value_NO_Double"]->rangeMaximum().toDouble(), -3.14);
    QCOMPARE(checkData["value_NO_String"]->rangeMaximum().type(), QVariant::Int);
    QCOMPARE(checkData["value_NO_String"]->rangeMaximum().toInt(), 10);
    QCOMPARE(checkData["value_NO_Vec3D"]->rangeMaximum().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_NO_Vec3D"]->rangeMaximum().value<QVector3D>(), QVector3D(5, 4, 3));

    QCOMPARE(checkData["value_NO_Float"]->decimals(), QTMETA_DEFAULT_FLOAT_DECIMALS);
    QCOMPARE(checkData["value_NO_Double"]->decimals(), QTMETA_DEFAULT_DOUBLE_DECIMALS);
}

void Universe1::UnitTest::Test_MetaProperty::testNativeCH()
{
    using namespace QtMeta;

    Test_MetaPropertyObject1 *obj = new Test_MetaPropertyObject1();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    const QVector<const char *> checkNames1 = {"value_CH_Bool",
                                               "value_CH_String",
                                               "value_CH_Time",
                                               "value_CH_Date",
                                               "value_CH_DateTime",
                                               "value_CH_Color",
                                               "value_CH_Enum"};

    const QVector<const char *> checkNames2 = {"value_CH_Int",
                                               "value_CH_UInt",
                                               "value_CH_Long",
                                               "value_CH_ULong",
                                               "value_CH_Float",
                                               "value_CH_Double",
                                               "value_CH_Vec3D"};

    QHash<const char *, MetaProperty *> checkData;

    for (const char *const p : checkNames1)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(!prop->hasNotifySignal(), p);
        QVERIFY2(prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeDisabled, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    for (const char *const p : checkNames2)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(!prop->hasNotifySignal(), p);
        QVERIFY2(prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeFull, p);
        QVERIFY2(prop->rangeMinimum().isValid(), p);
        QVERIFY2(prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    QCOMPARE(checkData.size(), checkNames1.size() + checkNames2.size());

    QCOMPARE(checkData["value_CH_Bool"]->defaultValue().type(), QVariant::Bool);
    QCOMPARE(checkData["value_CH_Bool"]->defaultValue().toBool(), true);
    QCOMPARE(checkData["value_CH_Int"]->defaultValue().type(), QVariant::Int);
    QCOMPARE(checkData["value_CH_Int"]->defaultValue().toInt(), -1);
    QCOMPARE(checkData["value_CH_UInt"]->defaultValue().type(), QVariant::UInt);
    QCOMPARE(checkData["value_CH_UInt"]->defaultValue().toUInt(), 1U);
    QCOMPARE(checkData["value_CH_Long"]->defaultValue().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_CH_Long"]->defaultValue().toLongLong(), -100L);
    QCOMPARE(checkData["value_CH_ULong"]->defaultValue().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_CH_ULong"]->defaultValue().toLongLong(), 100L);
    QCOMPARE(checkData["value_CH_Float"]->defaultValue().type(), QMetaType::Float);
    QCOMPARE(checkData["value_CH_Float"]->defaultValue().toFloat(), 0.1F);
    QCOMPARE(checkData["value_CH_Double"]->defaultValue().type(), QVariant::Double);
    QCOMPARE(checkData["value_CH_Double"]->defaultValue().toDouble(), 3.14);
    QCOMPARE(checkData["value_CH_String"]->defaultValue().type(), QVariant::String);
    QCOMPARE(checkData["value_CH_String"]->defaultValue().toString(), "test");
    QCOMPARE(checkData["value_CH_Time"]->defaultValue().type(), QVariant::Time);
    QCOMPARE(checkData["value_CH_Time"]->defaultValue().toTime(), QTime(5, 10, 5));
    QCOMPARE(checkData["value_CH_Date"]->defaultValue().type(), QVariant::Date);
    QCOMPARE(checkData["value_CH_Date"]->defaultValue().toDate(), QDate(2020, 2, 3));
    QCOMPARE(checkData["value_CH_DateTime"]->defaultValue().type(), QVariant::DateTime);
    QCOMPARE(checkData["value_CH_DateTime"]->defaultValue().toDateTime(), QDateTime({2020, 2, 3}, {5, 10, 5, 123}));
    QCOMPARE(checkData["value_CH_Vec3D"]->defaultValue().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_CH_Vec3D"]->defaultValue().value<QVector3D>(), QVector3D(1.1, 2.2, 3.3));
    QCOMPARE(checkData["value_CH_Color"]->defaultValue().type(), QVariant::Color);
    QCOMPARE(checkData["value_CH_Color"]->defaultValue().value<QColor>(), QColor(1, 2, 3, 4));
    QCOMPARE(checkData["value_CH_Enum"]->defaultValue().value<Test_MetaPropertyObject1::TestEnum>(),
             Test_MetaPropertyObject1::Lit2);

    QCOMPARE(checkData["value_CH_Int"]->rangeMinimum().type(), QVariant::Int);
    QCOMPARE(checkData["value_CH_Int"]->rangeMaximum().type(), QVariant::Int);
    QCOMPARE(checkData["value_CH_Int"]->rangeMinimum().toInt(), -3);
    QCOMPARE(checkData["value_CH_Int"]->rangeMaximum().toInt(), 3);

    QCOMPARE(checkData["value_CH_UInt"]->rangeMinimum().type(), QVariant::UInt);
    QCOMPARE(checkData["value_CH_UInt"]->rangeMaximum().type(), QVariant::UInt);
    QCOMPARE(checkData["value_CH_UInt"]->rangeMinimum().toUInt(), 3U);
    QCOMPARE(checkData["value_CH_UInt"]->rangeMaximum().toUInt(), 6U);

    QCOMPARE(checkData["value_CH_Long"]->rangeMinimum().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_CH_Long"]->rangeMaximum().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_CH_Long"]->rangeMinimum().toLongLong(), -300L);
    QCOMPARE(checkData["value_CH_Long"]->rangeMaximum().toLongLong(), 300L);

    QCOMPARE(checkData["value_CH_ULong"]->rangeMinimum().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_CH_ULong"]->rangeMaximum().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_CH_ULong"]->rangeMinimum().toLongLong(), 300L);
    QCOMPARE(checkData["value_CH_ULong"]->rangeMaximum().toLongLong(), 600L);

    QCOMPARE(checkData["value_CH_Float"]->rangeMinimum().type(), QMetaType::Float);
    QCOMPARE(checkData["value_CH_Float"]->rangeMaximum().type(), QMetaType::Float);
    QCOMPARE(checkData["value_CH_Float"]->rangeMinimum().toFloat(), -1.1f);
    QCOMPARE(checkData["value_CH_Float"]->rangeMaximum().toFloat(), 1.1f);

    QCOMPARE(checkData["value_CH_Double"]->rangeMinimum().type(), QVariant::Double);
    QCOMPARE(checkData["value_CH_Double"]->rangeMaximum().type(), QVariant::Double);
    QCOMPARE(checkData["value_CH_Double"]->rangeMinimum().toDouble(), -3.14);
    QCOMPARE(checkData["value_CH_Double"]->rangeMaximum().toDouble(), 3.14);

    QCOMPARE(checkData["value_CH_Vec3D"]->rangeMinimum().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_CH_Vec3D"]->rangeMaximum().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_CH_Vec3D"]->rangeMinimum().value<QVector3D>(), QVector3D(-5, -4, -3));
    QCOMPARE(checkData["value_CH_Vec3D"]->rangeMaximum().value<QVector3D>(), QVector3D(5, 4, 3));

    QCOMPARE(checkData["value_CH_Float"]->decimals(), QTMETA_DEFAULT_FLOAT_DECIMALS);
    QCOMPARE(checkData["value_CH_Double"]->decimals(), QTMETA_DEFAULT_DOUBLE_DECIMALS);
}

void Universe1::UnitTest::Test_MetaProperty::testNativeCN()
{
    using namespace QtMeta;

    Test_MetaPropertyObject1 *obj = new Test_MetaPropertyObject1();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    const QVector<const char *> checkNames = {"value_CN_Bool",
                                              "value_CN_Int",
                                              "value_CN_UInt",
                                              "value_CN_Long",
                                              "value_CN_ULong",
                                              "value_CN_Float",
                                              "value_CN_Double",
                                              "value_CN_String",
                                              "value_CN_Time",
                                              "value_CN_Date",
                                              "value_CN_DateTime",
                                              "value_CN_Vec3D",
                                              "value_CN_Color",
                                              "value_CN_Enum"};

    QHash<const char *, MetaProperty *> checkData;

    for (const char *const p : checkNames)
    {
        const int idx = mo->indexOfProperty(p);
        QVERIFY2(idx >= 0, p);

        MetaProperty *prop = new MetaProperty(1, mo->property(idx), mo);
        prop->init(list, obj);

        QVERIFY2(!prop->isPointerToQObject(), p);
        QVERIFY2(prop->isReadable(), p);
        QVERIFY2(prop->isWritable(), p);

        QVERIFY2(prop->hasNotifySignal(), p);
        QVERIFY2(prop->hasChangedSignal(), p);

        QVERIFY2(prop->rangeMode() == MetaProperty::_RangeDisabled, p);
        QVERIFY2(!prop->rangeMinimum().isValid(), p);
        QVERIFY2(!prop->rangeMaximum().isValid(), p);

        checkData.insert(p, prop);
    }

    QCOMPARE(checkData.size(), checkNames.size());

    QCOMPARE(checkData["value_CN_Bool"]->defaultValue().type(), QVariant::Bool);
    QCOMPARE(checkData["value_CN_Bool"]->defaultValue().toBool(), true);
    QCOMPARE(checkData["value_CN_Int"]->defaultValue().type(), QVariant::Int);
    QCOMPARE(checkData["value_CN_Int"]->defaultValue().toInt(), -1);
    QCOMPARE(checkData["value_CN_UInt"]->defaultValue().type(), QVariant::UInt);
    QCOMPARE(checkData["value_CN_UInt"]->defaultValue().toUInt(), 1U);
    QCOMPARE(checkData["value_CN_Long"]->defaultValue().type(), QVariant::LongLong);
    QCOMPARE(checkData["value_CN_Long"]->defaultValue().toLongLong(), -100L);
    QCOMPARE(checkData["value_CN_ULong"]->defaultValue().type(), QVariant::ULongLong);
    QCOMPARE(checkData["value_CN_ULong"]->defaultValue().toLongLong(), 100L);
    QCOMPARE(checkData["value_CN_Float"]->defaultValue().type(), QMetaType::Float);
    QCOMPARE(checkData["value_CN_Float"]->defaultValue().toFloat(), 0.1F);
    QCOMPARE(checkData["value_CN_Double"]->defaultValue().type(), QVariant::Double);
    QCOMPARE(checkData["value_CN_Double"]->defaultValue().toDouble(), 3.14);
    QCOMPARE(checkData["value_CN_String"]->defaultValue().type(), QVariant::String);
    QCOMPARE(checkData["value_CN_String"]->defaultValue().toString(), "test");
    QCOMPARE(checkData["value_CN_Time"]->defaultValue().type(), QVariant::Time);
    QCOMPARE(checkData["value_CN_Time"]->defaultValue().toTime(), QTime(5, 10, 5));
    QCOMPARE(checkData["value_CN_Date"]->defaultValue().type(), QVariant::Date);
    QCOMPARE(checkData["value_CN_Date"]->defaultValue().toDate(), QDate(2020, 2, 3));
    QCOMPARE(checkData["value_CN_DateTime"]->defaultValue().type(), QVariant::DateTime);
    QCOMPARE(checkData["value_CN_DateTime"]->defaultValue().toDateTime(), QDateTime({2020, 2, 3}, {5, 10, 5, 123}));
    QCOMPARE(checkData["value_CN_Vec3D"]->defaultValue().type(), QVariant::Vector3D);
    QCOMPARE(checkData["value_CN_Vec3D"]->defaultValue().value<QVector3D>(), QVector3D(1.1, 2.2, 3.3));
    QCOMPARE(checkData["value_CN_Color"]->defaultValue().type(), QVariant::Color);
    QCOMPARE(checkData["value_CN_Color"]->defaultValue().value<QColor>(), QColor(1, 2, 3, 4));
    QCOMPARE(checkData["value_CN_Enum"]->defaultValue().value<Test_MetaPropertyObject1::TestEnum>(),
             Test_MetaPropertyObject1::Lit2);

    QCOMPARE(checkData["value_CN_Float"]->decimals(), 5);
    QCOMPARE(checkData["value_CN_Double"]->decimals(), 10);
}

void Universe1::UnitTest::Test_MetaProperty::testObject()
{
    using namespace QtMeta;

    Test_MetaPropertyObject2 *obj = new Test_MetaPropertyObject2();
    const QMetaObject *mo = obj->metaObject();
    QList<QMetaClassInfo> list = buildClassInfoList(mo);

    MetaProperty mpRO(1, mo->property(mo->indexOfProperty("objRO")), mo);
    MetaProperty mpRW(1, mo->property(mo->indexOfProperty("objRW")), mo);
    MetaProperty mpNO(1, mo->property(mo->indexOfProperty("objNO")), mo);
    MetaProperty mpCH(1, mo->property(mo->indexOfProperty("objCH")), mo);
    MetaProperty mpCN(1, mo->property(mo->indexOfProperty("objCN")), mo);
    mpRO.init(list, obj);
    mpRW.init(list, obj);
    mpNO.init(list, obj);
    mpCH.init(list, obj);
    mpCN.init(list, obj);

    QVERIFY(mpRO.isPointerToQObject());
    QVERIFY(mpRO.isPointerToQObject());
    QVERIFY(mpRO.isPointerToQObject());
    QVERIFY(mpRO.isPointerToQObject());
    QVERIFY(mpRO.isPointerToQObject());

    const QMetaObject *moChild1 = obj->objRO()->metaObject();
    const QMetaObject *moChild2 = &Test_MetaPropertyObject1::staticMetaObject;

    QVERIFY(moChild1 == moChild2);
    QVERIFY(mpRO.userMetaObject() == moChild1);

    QString tmp = mpRO.metaProperty().typeName();
    QCOMPARE(tmp, "Universe1::UnitTest::Test_MetaPropertyObject1*");

    const QMetaObject *mo2 = QMetaType::metaObjectForType(QMetaType::type(tmp.toLatin1()));
    QVERIFY(mo2 == moChild1);
}
