#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool okA, okB;
    unsigned int a = ui->lineEdit->text().toUInt(&okA);
    unsigned int b = ui->lineEdit_2->text().toUInt(&okB);

    if (!okA || !okB) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректные целые числа");
        return;
    }

    math.SetA(a);
    math.SetB(b);

    QString operation = ui->comboBox->currentText();
    QString result;

    if (operation == "isPrimeA") {
        result = math.isPrimeA() ? "Да" : "Нет";
    }
    else if (operation == "isPrimeB") {
        result = math.isPrimeB() ? "Да" : "Нет";
    }
    else if (operation == "isArmstrongA") {
        result = math.isArmstrongA() ? "Да" : "Нет";
    }
    else if (operation == "isArmstrongB") {
        result = math.isArmstrongB() ? "Да" : "Нет";
    }
    else if (operation == "Nod") {
        result = QString::number(math.nod());
    }
    else if (operation == "Nok") {
        result = QString::number(math.nok());
    }

    ui->lineEdit_3->setText(result);
}
