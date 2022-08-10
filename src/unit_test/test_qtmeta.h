#ifndef TEST_QTMETA_H
#define TEST_QTMETA_H

#include <QTest>

//#include "qtmeta/qtmeta.h"

namespace Universe1 {
namespace UnitTest {
/*
class Test_QtMetaObject1 : public QObject
{
    Q_OBJECT

    // QT_META_HPP_NOTIFY_BOOL(valueBOOL, ValueBOOL)
    // QT_META_HPP_INT(valueINT, ValueINT)
    // QT_META_HPP_UINT(valueUINT, ValueUINT)
    // QT_META_HPP_NOTIFY_LONG(valueLONG, ValueLONG)
    // QT_META_HPP_NOTIFY_ULONG(valueULONG, ValueULONG)
    // QT_META_HPP_NOTIFY_FLOAT(valueFLOAT, ValueFLOAT)
    // QT_META_HPP_NOTIFY_DOUBLE(valueDOUBLE, ValueDOUBLE)

 signals:
    void changed();

 public:
    enum TestEnum
    {
        _Enum1,
        _Enum2,
        _Enum3,
    };
    Q_ENUM(TestEnum)

    enum TestFlag
    {
        _Flag1 = 0x01,
        _Flag2 = 0x02,
        _Flag3 = 0x04,
    };
    Q_DECLARE_FLAGS(TestFlags, TestFlag)
    Q_FLAG(TestFlags)

    Test_QtMetaObject1(QObject *_parent = nullptr);

 protected:
    QColor m_colorValue;
    QVector3D m_vec3dValue;
    QMatrix3x3 m_mat3Value;
    QMatrix4x4 m_mat4Value;
    QString m_textValue;

    TestEnum m_enumValue;
    TestFlags m_flagsValue;
};
*/
class Test_QtMeta : public QObject
{
    Q_OBJECT
 public:
    Test_QtMeta(QObject *_parent = nullptr);

 private slots:
    void test1();
};

}  // namespace UnitTest
}  // namespace Universe1
#endif  // TEST_QTMETA_H
