#ifndef TEST_METAPROPERTY_H
#define TEST_METAPROPERTY_H

#include <QTest>

#include "qtmeta/metaobject.h"

namespace Universe1 {
namespace UnitTest {
Q_NAMESPACE

class Test_MetaProperty : public QObject
{
    Q_OBJECT

 public:
    Test_MetaProperty(QObject *_parent = nullptr);

 private slots:
    void testNativeRO();
    void testNativeRW();
    void testNativeNO();
    void testNativeCH();
    void testNativeCN();
    void testObject();
};

class Test_MetaPropertyObject1 : public QObject
{
    Q_OBJECT_USE_CHANGED
 public:
    enum TestEnum
    {
        Lit1,
        Lit2,
    };
    Q_ENUM(TestEnum)

    enum TestFlag
    {
        Flag1 = 1,
        Flag2 = 2,
        Flag3 = 4
    };
    Q_DECLARE_FLAGS(TestFlags, TestFlag)
    Q_FLAGS(TestFlags)

    explicit Test_MetaPropertyObject1(QObject *_parent = nullptr);

    QTMETA_HPP_BOOL_RO(value_RO_Bool)
    QTMETA_HPP_INT_RO(value_RO_Int)
    QTMETA_HPP_UINT_RO(value_RO_UInt)
    QTMETA_HPP_LONGLONG_RO(value_RO_Long)
    QTMETA_HPP_ULONGLONG_RO(value_RO_ULong)
    QTMETA_HPP_FLOAT_RO(value_RO_Float)
    QTMETA_HPP_DOUBLE_RO(value_RO_Double)
    QTMETA_HPP_STRING_RO(value_RO_String)
    QTMETA_HPP_TIME_RO(value_RO_Time)
    QTMETA_HPP_DATE_RO(value_RO_Date)
    QTMETA_HPP_DATETIME_RO(value_RO_DateTime)
    QTMETA_HPP_VEC3D_RO(value_RO_Vec3D)
    QTMETA_HPP_COLOR_RO(value_RO_Color)
    QTMETA_HPP_ENUM_RO(TestEnum, value_RO_Enum)
    QTMETA_HPP_ENUM_RO(TestFlags, value_RO_Flag)

    QTMETA_HPP_BOOL_RW(value_RW_Bool, Value_RW_Bool)
    QTMETA_HPP_INT_RW_MIN(value_RW_Int, Value_RW_Int, -3)
    QTMETA_HPP_UINT_RW_MIN(value_RW_UInt, Value_RW_UInt, 3)
    QTMETA_HPP_LONGLONG_RW_MIN(value_RW_Long, Value_RW_Long, -300)
    QTMETA_HPP_ULONGLONG_RW_MIN(value_RW_ULong, Value_RW_ULong, 30)
    QTMETA_HPP_FLOAT_RW_MIN(value_RW_Float, Value_RW_Float, -4.7)
    QTMETA_HPP_DOUBLE_RW_MIN(value_RW_Double, Value_RW_Double, -3.14)
    QTMETA_HPP_STRING_RW(value_RW_String, Value_RW_String)
    QTMETA_HPP_TIME_RW(value_RW_Time, Value_RW_Time)
    QTMETA_HPP_DATE_RW(value_RW_Date, Value_RW_Date)
    QTMETA_HPP_DATETIME_RW(value_RW_DateTime, Value_RW_DateTime)
    QTMETA_HPP_VEC3D_RW_MIN(value_RW_Vec3D, Value_RW_Vec3D, -5, -4, -3)
    QTMETA_HPP_COLOR_RW(value_RW_Color, Value_RW_Color)
    QTMETA_HPP_ENUM_RW(TestEnum, value_RW_Enum, Value_RW_Enum)
    QTMETA_HPP_ENUM_RW(TestFlags, value_RW_Flag, Value_RW_Flag)

    QTMETA_HPP_BOOL_NO(value_NO_Bool, Value_NO_Bool)
    QTMETA_HPP_INT_NO_MAX(value_NO_Int, Value_NO_Int, -3)
    QTMETA_HPP_UINT_NO_MAX(value_NO_UInt, Value_NO_UInt, 3)
    QTMETA_HPP_LONGLONG_NO_MAX(value_NO_Long, Value_NO_Long, -300)
    QTMETA_HPP_ULONGLONG_NO_MAX(value_NO_ULong, Value_NO_ULong, 30)
    QTMETA_HPP_FLOAT_NO_MAX(value_NO_Float, Value_NO_Float, -4.7)
    QTMETA_HPP_DOUBLE_NO_MAX(value_NO_Double, Value_NO_Double, -3.14)
    QTMETA_HPP_STRING_NO_MAX(value_NO_String, Value_NO_String, 10)
    QTMETA_HPP_TIME_NO(value_NO_Time, Value_NO_Time)
    QTMETA_HPP_DATE_NO(value_NO_Date, Value_NO_Date)
    QTMETA_HPP_DATETIME_NO(value_NO_DateTime, Value_NO_DateTime)
    QTMETA_HPP_VEC3D_NO_MAX(value_NO_Vec3D, Value_NO_Vec3D, 5, 4, 3)
    QTMETA_HPP_COLOR_NO(value_NO_Color, Value_NO_Color)
    QTMETA_HPP_ENUM_NO(TestEnum, value_NO_Enum, Value_NO_Enum)

    QTMETA_HPP_BOOL_CH(value_CH_Bool, Value_CH_Bool)
    QTMETA_HPP_INT_CH_RANGE(value_CH_Int, Value_CH_Int, -3, 3)
    QTMETA_HPP_UINT_CH_RANGE(value_CH_UInt, Value_CH_UInt, 3, 6)
    QTMETA_HPP_LONGLONG_CH_RANGE(value_CH_Long, Value_CH_Long, -300, 300)
    QTMETA_HPP_ULONGLONG_CH_RANGE(value_CH_ULong, Value_CH_ULong, 300, 600)
    QTMETA_HPP_FLOAT_CH_RANGE(value_CH_Float, Value_CH_Float, -1.1, 1.1)
    QTMETA_HPP_DOUBLE_CH_RANGE(value_CH_Double, Value_CH_Double, -3.14, 3.14)
    QTMETA_HPP_STRING_CH(value_CH_String, Value_CH_String)
    QTMETA_HPP_TIME_CH(value_CH_Time, Value_CH_Time)
    QTMETA_HPP_DATE_CH(value_CH_Date, Value_CH_Date)
    QTMETA_HPP_DATETIME_CH(value_CH_DateTime, Value_CH_DateTime)
    QTMETA_HPP_VEC3D_CH_RANGE(value_CH_Vec3D, Value_CH_Vec3D, -5, -4, -3, 5, 4, 3)
    QTMETA_HPP_COLOR_CH(value_CH_Color, Value_CH_Color)
    QTMETA_HPP_ENUM_CH(TestEnum, value_CH_Enum, Value_CH_Enum)

    QTMETA_HPP_BOOL_CN(value_CN_Bool, Value_CN_Bool)
    QTMETA_HPP_INT_CN(value_CN_Int, Value_CN_Int)
    QTMETA_HPP_UINT_CN(value_CN_UInt, Value_CN_UInt)
    QTMETA_HPP_LONGLONG_CN(value_CN_Long, Value_CN_Long)
    QTMETA_HPP_ULONGLONG_CN(value_CN_ULong, Value_CN_ULong)
    QTMETA_HPP_DEC_FLOAT_CN(value_CN_Float, Value_CN_Float, 5)
    QTMETA_HPP_DEC_DOUBLE_CN(value_CN_Double, Value_CN_Double, 10)
    QTMETA_HPP_STRING_CN(value_CN_String, Value_CN_String)
    QTMETA_HPP_TIME_CN(value_CN_Time, Value_CN_Time)
    QTMETA_HPP_DATE_CN(value_CN_Date, Value_CN_Date)
    QTMETA_HPP_DATETIME_CN(value_CN_DateTime, Value_CN_DateTime)
    QTMETA_HPP_VEC3D_CN(value_CN_Vec3D, Value_CN_Vec3D)
    QTMETA_HPP_COLOR_CN(value_CN_Color, Value_CN_Color)
    QTMETA_HPP_ENUM_CN(TestEnum, value_CN_Enum, Value_CN_Enum)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Test_MetaPropertyObject1::TestFlags)
class Test_MetaPropertyObject2 : public QObject
{
    Q_OBJECT_USE_CHANGED

    QTMETA_HPP_OBJ_RO(Universe1::UnitTest::Test_MetaPropertyObject1, objRO)
    QTMETA_HPP_OBJ_RW(Universe1::UnitTest::Test_MetaPropertyObject1, objRW, ObjRW)
    QTMETA_HPP_OBJ_NO(Universe1::UnitTest::Test_MetaPropertyObject1, objNO, ObjNO)
    QTMETA_HPP_CH_OBJ_CH(Universe1::UnitTest::Test_MetaPropertyObject1,
                         objCH,
                         ObjCH,
                         Universe1::UnitTest::Test_MetaPropertyObject2)
    QTMETA_HPP_CH_OBJ_CN(Universe1::UnitTest::Test_MetaPropertyObject1,
                         objCN,
                         ObjCN,
                         Universe1::UnitTest::Test_MetaPropertyObject2)

 public:
    explicit Test_MetaPropertyObject2(QObject *_parent = nullptr);
    ~Test_MetaPropertyObject2();
};

}  // namespace UnitTest
}  // namespace Universe1

// Q_DECLARE_METATYPE(Universe1::UnitTest::Test_MetaPropertyObject1 *);
// Q_DECLARE_METATYPE(Universe1::UnitTest::Test_MetaPropertyObject2 *);

#endif  // TEST_METAPROPERTY_H
