#include <QtTest>
#include <QApplication>
#include <QComboBox>
#include "mainwindow.h"

class TestMathGui : public QObject
{
    Q_OBJECT

public:
    TestMathGui();
    ~TestMathGui();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testGuiOperations_data();
    void testGuiOperations();

private:
    MainWindow* mainWindow;
};

TestMathGui::TestMathGui() {}

TestMathGui::~TestMathGui() {}

void TestMathGui::initTestCase()
{
    mainWindow = new MainWindow();
    mainWindow->show();
}

void TestMathGui::cleanupTestCase()
{
    delete mainWindow;
}

void TestMathGui::testGuiOperations_data()
{
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("operation");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Prime A (true)")   << "7"   << "0"  << "isPrimeA"     << "Да";
    QTest::newRow("Prime A (false)")  << "8"   << "0"  << "isPrimeA"     << "Нет";
    QTest::newRow("Prime B (true)")   << "0"   << "13" << "isPrimeB"     << "Да";
    QTest::newRow("Armstrong A")      << "153" << "0"  << "isArmstrongA" << "Да";
    QTest::newRow("Armstrong B")      << "371" << "0"  << "isArmstrongB" << "Да";
    QTest::newRow("NOD")              << "54"  << "24" << "Nod"          << "6";
    QTest::newRow("NOK")              << "54"  << "24" << "Nok"          << "216";
}

void TestMathGui::testGuiOperations()
{
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, operation);
    QFETCH(QString, expected);

    mainWindow->ui->lineEdit->clear();
    mainWindow->ui->lineEdit_2->clear();
    mainWindow->ui->lineEdit_3->clear();

    QTest::keyClicks(mainWindow->ui->lineEdit, a);
    QTest::keyClicks(mainWindow->ui->lineEdit_2, b);

    QComboBox* combo = mainWindow->ui->comboBox;
    combo->setCurrentIndex(combo->findText(operation));

    QTest::mouseClick(mainWindow->ui->pushButton, Qt::LeftButton);

    QCOMPARE(mainWindow->ui->lineEdit_3->text(), expected);
}

QTEST_MAIN(TestMathGui)
#include "tst_test.moc"
