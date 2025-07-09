#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../psis-storage-cli/include/connector.hpp"
#include <QMessageBox>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Cambia la IP y puerto según tu servidor

    cargarDoctores();

    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableView_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarDoctores()
{
    ui->comboBox->clear();
    DBConnector db("127.0.0.1", "65535");
    db.connect();

    // Buscar los primeros 20 doctores (ajusta el rango según tus datos)
    for (int id = 1; id <= 20; ++id) {
        auto result = db.get("doctor", id);
        if (result.success && !result.data.empty()) {
            const auto& record = result.data[0];
            int doctorId = std::stoi(record.at("col1"));
            QString nombre = QString::fromStdString(record.at("col2"));
            ui->comboBox->addItem(nombre, doctorId);
        }
    }

    db.disconnect();
}

void MainWindow::on_btnVer_clicked()
{
    int doctorId = ui->comboBox->currentData().toInt();
    QString query = QString("SELECT id, fecha FROM citas WHERE doctor_id = %1 AND reservada = FALSE").arg(doctorId);
    DBConnector db("127.0.0.1", "65535");
    db.connect();

    std::string cmd = "SELECT id, fecha FROM citas WHERE doctor_id = " + std::to_string(doctorId) + " AND reservada = FALSE";
    auto result = db.cmd(cmd);

    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Fecha"});

    if (!result.success) {
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
        db.disconnect();
        return;
    }

    for (const auto& record : result.data) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(record.at("id")));
        row << new QStandardItem(QString::fromStdString(record.at("fecha")));
        model->appendRow(row);
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    db.disconnect();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    citaSeleccionadaId = index.sibling(index.row(), 0).data().toInt();
}

void MainWindow::on_btnReservar_clicked()
{
    if (citaSeleccionadaId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una cita primero.");
        return;
    }

    QString nombre = ui->txtPaciente->text();
    QString dni = ui->txtDNI->text();

    if (nombre.isEmpty() || dni.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese nombre y DNI del paciente.");
        return;
    }

    // Usar DBConnector para actualizar la cita
    DBConnector db("127.0.0.1", "65535");
    db.connect();

    // Actualizar la cita (puedes adaptar el comando según tu API)
    std::string cmd = "UPDATE citas SET paciente_nombre = '" + nombre.toStdString() + "', paciente_dni = '" + dni.toStdString() + "', reservada = TRUE WHERE id = " + std::to_string(citaSeleccionadaId);
    auto result = db.cmd(cmd);

    if (result.success) {
        QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
        on_btnVer_clicked();  // refrescar tabla
    } else {
        QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
    }

    db.disconnect();
    citaSeleccionadaId = -1;
}
