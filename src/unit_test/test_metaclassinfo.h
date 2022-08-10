#ifndef TEST_METACLASSINFO_H
#define TEST_METACLASSINFO_H

#include <QTest>

#include "qtmeta/metaclassinfo.h"

namespace Universe1 {
namespace UnitTest {

class Test_MetaClassInfo : public QObject
{
    Q_OBJECT
 public:
    Test_MetaClassInfo(QObject *_parent = nullptr);

 private slots:
    void test_takeClassInfos();
};

class Test_MetaClassInfoObject1 : public QObject
{
    Q_OBJECT

    Q_CLASSINFO("info1", "Info   <b>1</b>")

    Q_CLASSINFO("info2", "getInfo2")
    Q_CLASSINFO("info3", "getInfo3")
    Q_CLASSINFO("info4", "getInfo4")
    Q_CLASSINFO("info5", "getInfo5()")
    Q_CLASSINFO("info6", "getInfo6(text6)")
    Q_CLASSINFO("info7", "getInfo7(\"text7\")")
    Q_CLASSINFO("info8", "getInfo8(8)")
    Q_CLASSINFO("info9", "getInfo9(9)")

    Q_CLASSINFO("info10", "info10 1")
    Q_CLASSINFO("info10", "info10 2")

    Q_CLASSINFO("info12", "true")
    Q_CLASSINFO("info13", "false")

    Q_CLASSINFO("info14", "-14")
    Q_CLASSINFO("info15", "15.1")
    Q_CLASSINFO("info16", "16.123")

    Q_CLASSINFO("info17_range", "-1 to 2")
    Q_CLASSINFO("info18_range", "100 : 2000000")
    Q_CLASSINFO("info19_range", "0 2.43")
    Q_CLASSINFO("info20_range", "00:00 to 02:15:01.123")
    Q_CLASSINFO("info21_range", "2008-01-01 to 2028-12-31")
    Q_CLASSINFO("info22_range", "2009-01-01T07:00:00 to 2029-12-31T02:15:20.2")

 public:
    Test_MetaClassInfoObject1(QObject *_parent = nullptr);

 private slots:
    QString getInfo2(QString);
    QString getInfo3(const QString);
    QString getInfo4(const QString &);
    QString getInfo5();
    QString getInfo6(const QString &);
    QString getInfo7(const QString &);
    QString getInfo8(int);
    QString getInfo9(const int);
};

}  // namespace UnitTest
}  // namespace Universe1

#endif  // TEST_METACLASSINFO_H
