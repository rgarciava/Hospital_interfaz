#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../psis-storage-cli/include/connector.hpp"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      modeloCitas(new QStandardItemModel(this))
{
    ui->setupUi(this);
    cargarDoctores();

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_comboBox_currentIndexChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged,
            this, &MainWindow::on_dateEdit_dateChanged);

    modeloCitas->setHorizontalHeaderLabels(
        {"ID", "DNI", "Especialidad", "Doctor", "Fecha", "Hora"});
    ui->tableView->setModel(modeloCitas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarDoctores()
{
    ui->comboBox->clear();
    DBConnector db;
    db.connect();

    for (int id = 0; id <= 100; ++id) {
        auto result = db.get("doctor", id);
        if (result.success && !result.data.empty()) {
            const auto &record = result.data[0];
            QString nombre = QString::fromStdString(record.at("nombre"));
            ui->comboBox->addItem(nombre, id);
        }
    }

    db.disconnect();
}

void MainWindow::on_comboBox_currentIndexChanged(int)
{
    cargarHoras();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &)
{
    cargarHoras();
}

void MainWindow::cargarHoras()
{
    ui->comboHora->clear();
    QTime hora(8, 0);
    while (hora <= QTime(16, 0)) {
        ui->comboHora->addItem(hora.toString("HH:mm"));
        hora = hora.addSecs(30 * 60);
    }
}

void MainWindow::on_btnReservar_clicked()
{
    QString dni = ui->txtDNI->text();
    QString especialidad = "General";
    QString doctor = ui->comboBox->currentText();
    QString fecha = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString hora = ui->comboHora->currentText();

    if (dni.isEmpty() || doctor.isEmpty() || hora.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Complete todos los campos.");
        return;
    }

    int citaId = QDateTime::currentSecsSinceEpoch() % 1000; // ID 0-999
    std::string cmd = "INSERT cita "
        "col1:" + std::to_string(citaId) + ":INT "
        "col2:\"" + dni.toStdString() + "\":TEXT "
        "col3:\"" + especialidad.toStdString() + "\":TEXT "
        "col4:\"" + doctor.toStdString() + "\":TEXT "
        "col5:\"" + fecha.toStdString() + "\":TEXT "
        "col6:\"" + hora.toStdString() + "\":TEXT";

    DBConnector db;
    db.connect();
    auto result = db.cmd(cmd);
    db.disconnect();

    if (result.success) {
        QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
        on_btnListarCitas_clicked();
    } else {
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
    }
}

void MainWindow::on_btnListarCitas_clicked()
{
    modeloCitas->removeRows(0, modeloCitas->rowCount());
    DBConnector db;
    db.connect();

    for (int id = 0; id <= 1000; ++id) {
        auto result = db.get("cita", id);
        if (result.success && !result.data.empty()) {
            const auto &rec = result.data[0];
            QString cid = QString::fromStdString(rec.count("id") ? rec.at("id") : "");
            QString dni = QString::fromStdString(rec.count("dniPaciente") ? rec.at("dniPaciente") : "");
            QString esp = QString::fromStdString(rec.count("especialidad") ? rec.at("especialidad") : "");
            QString doc = QString::fromStdString(rec.count("doctor") ? rec.at("doctor") : "");
            QString fecha = QString::fromStdString(rec.count("fecha") ? rec.at("fecha") : "");
            QString hora = QString::fromStdString(rec.count("hora") ? rec.at("hora") : "");

            QList<QStandardItem*> row;
            row << new QStandardItem(cid)
                << new QStandardItem(dni)
                << new QStandardItem(esp)
                << new QStandardItem(doc)
                << new QStandardItem(fecha)
                << new QStandardItem(hora);
            modeloCitas->appendRow(row);
        } else if (!result.success && result.detail.find("Registro no encontrado") != std::string::npos) {
            // No pasa nada si no se encuentra
        } else {
            // Otro error inesperado
            qDebug() << "Error al obtener cita: " << QString::fromStdString(result.detail);
        }
    }

    db.disconnect();
}

void MainWindow::on_btnEliminarCita_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una cita para eliminar.");
        return;
    }

    int citaId = modeloCitas->item(index.row(), 0)->text().toInt();
    DBConnector db;
    db.connect();
    auto result = db.remove("cita", citaId);
    db.disconnect();

    if (result.success) {
        QMessageBox::information(this, "Éxito", "Cita eliminada.");
        on_btnListarCitas_clicked();
    } else {
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
    }
}
