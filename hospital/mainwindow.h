#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlDatabase>

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
    void on_btnVer_clicked();
    void on_btnReservar_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    int citaSeleccionadaId = -1;

    void cargarDoctores();
};

#endif // MAINWINDOW_H
