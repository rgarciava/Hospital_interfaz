#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include "serverclient.h"
#include <QMessageBox>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Cambia la IP y puerto según tu servidor
    serverClient = new ServerClient("127.0.0.1", 65535);
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
    QStringList lines = serverClient->sendQuery("SELECT id, nombre FROM doctores");
    for (const QString& line : lines) {
        if (line.startsWith("ERROR")) {
            QMessageBox::critical(this, "Error", line);
            return;
        }
        QStringList parts = line.split(",");
        if (parts.size() >= 2) {
            int id = parts[0].toInt();
            QString nombre = parts[1];
            ui->comboBox->addItem(nombre, id);
        }
    }
}

void MainWindow::on_btnVer_clicked()
{
    int doctorId = ui->comboBox->currentData().toInt();
    QString query = QString("SELECT id, fecha FROM citas WHERE doctor_id = %1 AND reservada = FALSE").arg(doctorId);
    QStringList lines = serverClient->sendQuery(query);

    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Fecha"});

    for (const QString& line : lines) {
        if (line.startsWith("ERROR")) {
            QMessageBox::critical(this, "Error", line);
            return;
        }
        QStringList parts = line.split(",");
        if (parts.size() >= 2) {
            QList<QStandardItem*> row;
            row << new QStandardItem(parts[0]);
            row << new QStandardItem(parts[1]);
            model->appendRow(row);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
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

    QSqlQuery query;
    query.prepare("UPDATE citas SET paciente_nombre = ?, paciente_dni = ?, reservada = TRUE WHERE id = ?");
    query.addBindValue(nombre);
    query.addBindValue(dni);
    query.addBindValue(citaSeleccionadaId);

    if (query.exec()) {
        QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
        on_btnVer_clicked();  // refrescar tabla
    } else {
        QMessageBox::critical(this, "Error", "No se pudo reservar la cita.");
    }

    citaSeleccionadaId = -1;
}
