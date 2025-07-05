#include <QtTest>
#include "..\untitled\math.cpp"


class Test : public QObject
{
    Q_OBJECT
    Math m;

public:
    Test();
    ~Test();

private slots:
    void nod1_data();
    void nod1();
    void testAllMethods();
};

Test::Test() {}

Test::~Test() {}

void Test::nod1(){
    QFETCH(uint, a);
    QFETCH(uint, b);
    QFETCH(ulong, result);
    m.SetA(a);
    m.SetB(b);

    QCOMPARE(m.nod(), result);
}
void Test::testAllMethods() {
    Math m1;
    QVERIFY(m1.GetA() == 0);
    QVERIFY(m1.GetB() == 0);

    Math m2(15, 25);
    QVERIFY(m2.GetA() == 15);
    QVERIFY(m2.GetB() == 25);

    m1.SetA(100);
    m1.SetB(200);
    QVERIFY(m1.GetA() == 100);
    QVERIFY(m1.GetB() == 200);

    m2.SetA(0);
    m2.SetB(1);
    QVERIFY(m2.GetA() == 0);
    QVERIFY(m2.GetB() == 1);

    Math m3(48, 18);
    QCOMPARE(m3.nod(), 6U);

    Math m4(17, 23);
    QCOMPARE(m4.nod(), 1U);

    Math m5(4, 6);
    QCOMPARE(m5.nok(), 12ULL);

    Math m6(21, 6);
    QCOMPARE(m6.nok(), 42ULL);

    Math m7(7, 10);
    QVERIFY(m7.isPrimeA());
    QVERIFY(!m7.isPrimeB());

    Math m8(1, 13);
    QVERIFY(!m8.isPrimeA());
    QVERIFY(m8.isPrimeB());

    Math m9(123, 4567);
    QCOMPARE(m9.countDigitsA(), 3U);
    QCOMPARE(m9.countDigitsB(), 4U);

    Math m10(0, 10000);
    QCOMPARE(m10.countDigitsA(), 1U);
    QCOMPARE(m10.countDigitsB(), 5U);

    Math m11(153, 370);
    QVERIFY(m11.isArmstrongA());
    QVERIFY(m11.isArmstrongB());

    Math m12(100, 123);
    QVERIFY(!m12.isArmstrongA());
    QVERIFY(!m12.isArmstrongB());
}

void Test:: nod1_data(){
    QTest::addColumn<uint>("a");
    QTest::addColumn<uint>("b");
    QTest::addColumn<ulong>("result");

    QTest::newRow("all 0") << 0U << 0U << 0UL;
    QTest::newRow("same number1") << 10U << 10U << 10UL;
    QTest::newRow("same number2") << 4U << 10U << 2UL;
    QTest::newRow("same number3") << 5U << 314901U << 1UL;

}



QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
