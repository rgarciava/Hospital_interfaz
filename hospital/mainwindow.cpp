#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../psis-storage-cli/include/connector.hpp"
#include <QMessageBox>
#include <QStandardItemModel>

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
    connect(ui->comboHora, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_comboHora_currentIndexChanged);

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

    for (int id = 1; id <= 20; ++id) {
        auto result = db.get("doctor", id);
        if (result.success && !result.data.empty()) {
            const auto &record = result.data[0];
            QString nombre = QString::fromStdString(record.at("col2"));
            ui->comboBox->addItem(nombre, id);
        }
    }
    db.disconnect();
}

void MainWindow::cargarHorasDisponibles()
{
    ui->comboHora->clear();
    horaToCitaId.clear();
    QTime hora(8, 0);
    QTime fin(16, 0);
    while (hora <= fin) {
        ui->comboHora->addItem(hora.toString("HH:mm"));
        hora = hora.addSecs(30 * 60);
    }
    citaSeleccionadaId = -1;
}

void MainWindow::on_comboBox_currentIndexChanged(int)
{
    cargarHorasDisponibles();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &)
{
    cargarHorasDisponibles();
}

void MainWindow::on_comboHora_currentIndexChanged(int index)
{
    QString hora = ui->comboHora->currentText();
    citaSeleccionadaId = horaToCitaId.value(hora, -1);
}

void MainWindow::on_btnReservar_clicked()
{
    QString nombre = ui->txtPaciente->text();
    QString dni = ui->txtDNI->text();
    QString hora = ui->comboHora->currentText();
    QDate fecha = ui->dateEdit->date();
    int doctorId = ui->comboBox->currentData().toInt();
    QString doctorNombre = ui->comboBox->currentText();

    if (nombre.isEmpty() || dni.isEmpty() || hora.isEmpty() || doctorId == 0) {
        QMessageBox::warning(this, "Advertencia", "Complete todos los campos y seleccione un horario.");
        return;
    }

    int citaId = QDateTime::currentSecsSinceEpoch();
    std::string cmd = "INSERT cita "
        "col1:" + std::to_string(citaId) + ":INT "
        "col2:\"" + dni.toStdString() + "\":TEXT "
        "col3:\"General\":TEXT "
        "col4:\"" + doctorNombre.toStdString() + "\":TEXT "
        "col5:\"" + fecha.toString("yyyy-MM-dd").toStdString() + "\":TEXT "
        "col6:\"" + hora.toStdString() + "\":TEXT";

    DBConnector db;
    db.connect();
    auto result = db.cmd(cmd);
    db.disconnect();

    if (result.success)
        QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
    else
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
}

void MainWindow::on_btnListarCitas_clicked()
{
    modeloCitas->removeRows(0, modeloCitas->rowCount());
    DBConnector db;
    db.connect();

    for (int id = 0; id < 100; ++id) { // Buscar citas con id 0 a 99
        auto result = db.get("cita", id);
        if (result.success && !result.data.empty()) {
            const auto &rec = result.data[0];
            QList<QStandardItem*> row;
            row << new QStandardItem(QString::fromStdString(rec.at("col1"))); // ID
            row << new QStandardItem(QString::fromStdString(rec.at("col2"))); // DNI
            row << new QStandardItem(QString::fromStdString(rec.at("col3"))); // Especialidad
            row << new QStandardItem(QString::fromStdString(rec.at("col4"))); // Doctor
            row << new QStandardItem(QString::fromStdString(rec.at("col5"))); // Fecha
            row << new QStandardItem(QString::fromStdString(rec.at("col6"))); // Hora
            modeloCitas->appendRow(row);
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

    QString idStr = modeloCitas->item(index.row(), 0)->text();
    int citaId = idStr.toInt();

    DBConnector db;
    db.connect();
    auto result = db.remove("cita", citaId);
    db.disconnect();

    if (result.success) {
        QMessageBox::information(this, "Éxito", "Cita eliminada correctamente.");
        on_btnListarCitas_clicked(); // Refrescar la lista
    } else {
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
    }
}
