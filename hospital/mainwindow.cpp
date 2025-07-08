#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cargarDoctores();

    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableView_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarDoctores()
{
    QSqlQuery query("SELECT id, nombre FROM doctores");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString nombre = query.value(1).toString();
        ui->comboBox->addItem(nombre, id);
    }
}

void MainWindow::on_btnVer_clicked()
{
    int doctorId = ui->comboBox->currentData().toInt();

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString("SELECT id, fecha FROM citas WHERE doctor_id = %1 AND reservada = FALSE").arg(doctorId));

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Fecha");

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
