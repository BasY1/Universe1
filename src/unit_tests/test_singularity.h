#ifndef TEST_SINGULARITY_H
#define TEST_SINGULARITY_H

#include <QTest>

#include "../math/singularity/singularityobject.h"
#include "../math/singularity/singularityobjectdata.h"

class Test_Singularity : public QObject
{
    Q_OBJECT
 public:
    Test_Singularity(QObject *parent = nullptr);

 private slots:
    void testObjectDataFloat();
    void testObjectDataDouble();
    void testObjectDataLongDouble();

    void testObjectLongDouble();

 private:
    template <typename T>
    void testObjectData();
};

template <typename T>
void Test_Singularity::testObjectData()
{
    SingularityObjectData<T> obj1(2, Vec3<T>(), Vec3<T>(1, 0, 0), Vec3<T>(0, 0, 0));
    SingularityObjectData<T> obj2 = obj1.getSource(1, 8, Vec3<T>(2, 2, 2));

    QVERIFY(TypeEquals<T>(obj2.timeStamp, T(5)));
    if (!std::is_same<T, float>::value)
        QVERIFY(obj2.position == Vec3<T>(3, 0, 0));
}

#endif  // TEST_SINGULARITY_H
