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
    cargarDoctores();

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboBox_currentIndexChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &MainWindow::on_dateEdit_dateChanged);
    connect(ui->comboHora, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboHora_currentIndexChanged);
}
// Cargar las horas disponibles para el doctor y fecha seleccionados en listHoras
void MainWindow::cargarHorasDisponibles()
{
    ui->comboHora->clear();
    horaToCitaId.clear();
    // Agrega las horas fijas de 8:00 a 16:00 cada 30 minutos
    QTime hora(8, 0);
    QTime fin(16, 0);
    while (hora <= fin) {
        ui->comboHora->addItem(hora.toString("HH:mm"));
        hora = hora.addSecs(30 * 60); // suma 30 minutos
    }
    citaSeleccionadaId = -1; // No hay id de cita, solo hora seleccionada
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
    if (horaToCitaId.contains(hora)) {
        citaSeleccionadaId = horaToCitaId[hora];
    } else {
        citaSeleccionadaId = -1;
    }
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
    // Manejo robusto de error de respuesta malformada
    try {
        if (result.success) {
            QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
            cargarHorasDisponibles(); // refrescar horas
        } else {
            QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
        }
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error de backend", QString("Respuesta malformada o vacía del servidor: ") + ex.what());
    }
    qDebug("Cita enviada: %s", cmd.c_str());

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
    // Eliminado: ya no hay tableView en la interfaz
    db.disconnect();
}

// Eliminado: función para la tabla de citas (ya no existe en la interfaz)

void MainWindow::on_btnReservar_clicked()
{
    QString nombre = ui->txtPaciente->text();
    QString dni = ui->txtDNI->text();
    QString hora = ui->comboHora->currentText();
    QDate fecha = ui->dateEdit->date();
    int doctorId = ui->comboBox->currentData().toInt();
    QString doctorNombre = ui->comboBox->currentText();
    QString especialidad = "General"; // Cambia esto si tienes el dato real

    if (hora.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una hora disponible primero.");
        return;
    }
    if (nombre.isEmpty() || dni.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese nombre y DNI del paciente.");
        return;
    }
    if (doctorId == 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un doctor.");
        return;
    }

    // Generar un id único para la cita
    int citaId = QDateTime::currentSecsSinceEpoch();

    // Formato exacto: INSERT cita col1:<id>:INT col2:"<dni>":TEXT col3:"<especialidad>":TEXT col4:"<doctor>":TEXT col5:"<fecha>":TEXT col6:"<hora>":TEXT
    std::string cmd = "INSERT cita "
        "col1:" + std::to_string(citaId) + ":INT "
        "col2:\"" + dni.toStdString() + "\":TEXT "
        "col3:\"" + especialidad.toStdString() + "\":TEXT "
        "col4:\"" + doctorNombre.toStdString() + "\":TEXT "
        "col5:\"" + fecha.toString("yyyy-MM-dd").toStdString() + "\":TEXT "
        "col6:\"" + hora.toStdString() + "\":TEXT";

    DBConnector db("127.0.0.1", "65535");
    db.connect();
    std::string rawResponse;
    // Muestra el comando que se enviará a la base de datos en un QMessageBox
    try {
        auto result = db.cmd(cmd);
        // Muestra la respuesta cruda del backend en un QMessageBox
        if (result.success) {
            QMessageBox::information(this, "Éxito", "Cita reservada con éxito.");
            cargarHorasDisponibles(); // refrescar horas
        } else {
            QMessageBox::critical(this, "Error", QString::fromStdString(result.detail));
        }
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error de backend", QString("Respuesta malformada o vacía del servidor: ") + ex.what());
    }
    db.disconnect();
}
