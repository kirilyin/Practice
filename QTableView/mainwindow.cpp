#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Загрузка данных
    QFile f1("in1.txt"), f2("in2.txt"), f3("in3.txt"), f4("in4.txt");
    if (f1.open(QIODevice::ReadOnly)) {
        QTextStream in(&f1);
        in >> m1;
        f1.close();
    }
    if (f2.open(QIODevice::ReadOnly)) {
        QTextStream in(&f2);
        in >> m2;
        f2.close();
    }
    if (f3.open(QIODevice::ReadOnly)) {
        QTextStream in(&f3);
        in >> k1;
        f3.close();
    }
    if (f4.open(QIODevice::ReadOnly)) {
        QTextStream in(&f4);
        in >> k2;
        f4.close();
    }

    // Сигналы для радиокнопок
    connect(ui->rM1, &QRadioButton::clicked, this, &MainWindow::onModelSelected);
    connect(ui->rM2, &QRadioButton::clicked, this, &MainWindow::onModelSelected);
    connect(ui->rM3, &QRadioButton::clicked, this, &MainWindow::onModelSelected);
    connect(ui->rK1, &QRadioButton::clicked, this, &MainWindow::onModelSelected);
    connect(ui->rK2, &QRadioButton::clicked, this, &MainWindow::onModelSelected);
    connect(ui->rK3, &QRadioButton::clicked, this, &MainWindow::onModelSelected);

    // Начальное отображение
    ui->rM1->setChecked(true);
    onModelSelected();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onModelSelected() {
    if (ui->rM1->isChecked()) curModel = 0;
    else if (ui->rM2->isChecked()) curModel = 1;
    else if (ui->rM3->isChecked()) curModel = 2;
    else if (ui->rK1->isChecked()) curModel = 3;
    else if (ui->rK2->isChecked()) curModel = 4;
    else if (ui->rK3->isChecked()) curModel = 5;
    updateView();
}

void MainWindow::updateView() {
    QTableView* tv = nullptr;
    switch (curModel) {
    case 0: tv = m1.Table(); break;
    case 1: tv = m2.Table(); break;
    case 2: tv = m3.Table(); break;
    case 3: tv = k1.Table(); break;
    case 4: tv = k2.Table(); break;
    case 5: tv = k3.Table(); break;
    }

    if (ui->verticalLayout->count() > 0)
        delete ui->verticalLayout->takeAt(0)->widget();

    if (tv) {
        ui->verticalLayout->addWidget(tv);
        tv->show();
    }
}

void MainWindow::on_btnMerge_clicked() {
    m3 = m1 + m2;
    k3 = k1 + k2;
    updateView();
}

void MainWindow::on_btnSort_clicked() {
    switch (curModel) {
    case 0: m1.Sort(); break;
    case 1: m2.Sort(); break;
    case 2: m3.Sort(); break;
    case 3: k1.Sort(); break;
    case 4: k2.Sort(); break;
    case 5: k3.Sort(); break;
    }
    updateView();
}

void MainWindow::on_btnSortD_clicked() {
    switch (curModel) {
    case 0: m1.SortD(); break;
    case 1: m2.SortD(); break;
    case 2: m3.SortD(); break;
    case 3: k1.SortD(); break;
    case 4: k2.SortD(); break;
    case 5: k3.SortD(); break;
    }
    updateView();
}

void MainWindow::on_btnStrange_clicked() {
    QString s = QInputDialog::getText(this, "Strange Sort", "Enter section:");
    switch (curModel) {
    case 0: m1.StrangeSort(s); break;
    case 1: m2.StrangeSort(s); break;
    case 2: m3.StrangeSort(s); break;
    case 3: k1.StrangeSort(s); break;
    case 4: k2.StrangeSort(s); break;
    case 5: k3.StrangeSort(s); break;
    }
    updateView();
}

void MainWindow::on_btnRev_clicked() {
    switch (curModel) {
    case 0: m1.Revers(); break;
    case 1: m2.Revers(); break;
    case 2: m3.Revers(); break;
    case 3: k1.Revers(); break;
    case 4: k2.Revers(); break;
    case 5: k3.Revers(); break;
    }
    updateView();
}

void MainWindow::on_btnFind_clicked() {
    QString name = QInputDialog::getText(this, "Search", "Enter name:");
    int idx = -1;
    switch (curModel) {
    case 0: idx = m1.Search(name); break;
    case 1: idx = m2.Search(name); break;
    case 2: idx = m3.Search(name); break;
    case 3: idx = k1.Search(name); break;
    case 4: idx = k2.Search(name); break;
    case 5: idx = k3.Search(name); break;
    }

    if (idx != -1) {
        QString msg;
        switch (curModel) {
        case 0: msg = m1[idx].Name + " | " + m1[idx].section; break;
        case 1: msg = m2[idx].Name + " | " + m2[idx].section; break;
        case 2: msg = m3[idx].Name + " | " + m3[idx].section; break;
        case 3: msg = k1[idx].Name + " | " + k1[idx].section; break;
        case 4: msg = k2[idx].Name + " | " + k2[idx].section; break;
        case 5: msg = k3[idx].Name + " | " + k3[idx].section; break;
        }
        QMessageBox::information(this, "Found", msg);
    }
    else {
        QMessageBox::warning(this, "Not Found", "Item not found!");
    }
}

void MainWindow::on_btnAdd_clicked() {
    if (curModel < 3) { // comp models
        comp c;
        c.Name = QInputDialog::getText(this, "Add", "Name:");
        c.section = QInputDialog::getText(this, "Add", "Section:");
        c.price = QInputDialog::getInt(this, "Add", "Price:");

        switch (curModel) {
        case 0: m1.append(c); break;
        case 1: m2.append(c); break;
        case 2: m3.append(c); break;
        }
    }
    else { // bag models
        bag b;
        b.Name = QInputDialog::getText(this, "Add", "Name:");
        b.section = QInputDialog::getText(this, "Add", "Section:");
        b.num = QInputDialog::getInt(this, "Add", "Count:");

        switch (curModel) {
        case 3: k1.append(b); break;
        case 4: k2.append(b); break;
        case 5: k3.append(b); break;
        }
    }
    updateView();
}
