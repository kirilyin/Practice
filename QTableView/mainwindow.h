#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "COMP.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateView();
    void on_btnMerge_clicked();
    void on_btnSort_clicked();
    void on_btnSortD_clicked();
    void on_btnStrange_clicked();
    void on_btnRev_clicked();
    void on_btnFind_clicked();
    void on_btnAdd_clicked();
    void onModelSelected();

private:
    Ui::MainWindow *ui;
    COMP<comp> m1, m2, m3;
    COMP<bag> k1, k2, k3;
    int curModel = 0;
};
#endif // MAINWINDOW_H