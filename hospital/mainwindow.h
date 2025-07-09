#pragma once

#include <QMainWindow>
#include <QMap>
#include <QDate>
#include <QStandardItemModel>

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
    void on_btnReservar_clicked();
    void on_btnListarCitas_clicked();
    void on_btnEliminarCita_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *modeloCitas;

    void cargarDoctores();
    void cargarHoras();
};
