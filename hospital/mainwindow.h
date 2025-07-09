#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QListWidgetItem>

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
    void on_comboBox_currentIndexChanged(int index);
    void on_dateEdit_dateChanged(const QDate &date);
    void on_comboHora_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    int citaSeleccionadaId = -1;
    QMap<QString, int> horaToCitaId; // Mapea hora (texto) a id de cita

    void cargarDoctores();
    void cargarHorasDisponibles();
};

#endif // MAINWINDOW_H
