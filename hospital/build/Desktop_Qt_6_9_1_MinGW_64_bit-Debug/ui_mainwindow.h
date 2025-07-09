/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblDoctor;
    QComboBox *comboBox;
    QLabel *lblFecha;
    QDateEdit *dateEdit;
    QLabel *lblHora;
    QComboBox *comboHora;
    QLabel *lblPaciente;
    QLineEdit *txtPaciente;
    QLabel *lblDNI;
    QLineEdit *txtDNI;
    QPushButton *btnReservar;
    QTableView *tableView;
    QPushButton *btnListarCitas;
    QPushButton *btnEliminarCita;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lblDoctor = new QLabel(centralwidget);
        lblDoctor->setObjectName("lblDoctor");
        lblDoctor->setGeometry(QRect(20, 20, 150, 20));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(180, 20, 200, 25));
        lblFecha = new QLabel(centralwidget);
        lblFecha->setObjectName("lblFecha");
        lblFecha->setGeometry(QRect(20, 60, 150, 20));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(180, 60, 200, 25));
        dateEdit->setCalendarPopup(true);
        lblHora = new QLabel(centralwidget);
        lblHora->setObjectName("lblHora");
        lblHora->setGeometry(QRect(20, 100, 150, 20));
        comboHora = new QComboBox(centralwidget);
        comboHora->setObjectName("comboHora");
        comboHora->setGeometry(QRect(180, 100, 200, 25));
        lblPaciente = new QLabel(centralwidget);
        lblPaciente->setObjectName("lblPaciente");
        lblPaciente->setGeometry(QRect(20, 140, 150, 20));
        txtPaciente = new QLineEdit(centralwidget);
        txtPaciente->setObjectName("txtPaciente");
        txtPaciente->setGeometry(QRect(180, 140, 200, 25));
        lblDNI = new QLabel(centralwidget);
        lblDNI->setObjectName("lblDNI");
        lblDNI->setGeometry(QRect(20, 180, 150, 20));
        txtDNI = new QLineEdit(centralwidget);
        txtDNI->setObjectName("txtDNI");
        txtDNI->setGeometry(QRect(180, 180, 200, 25));
        btnReservar = new QPushButton(centralwidget);
        btnReservar->setObjectName("btnReservar");
        btnReservar->setGeometry(QRect(180, 220, 150, 30));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 270, 550, 200));
        btnListarCitas = new QPushButton(centralwidget);
        btnListarCitas->setObjectName("btnListarCitas");
        btnListarCitas->setGeometry(QRect(20, 480, 150, 30));
        btnEliminarCita = new QPushButton(centralwidget);
        btnEliminarCita->setObjectName("btnEliminarCita");
        btnEliminarCita->setGeometry(QRect(200, 480, 150, 30));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestor de Citas M\303\251dicas", nullptr));
        lblDoctor->setText(QCoreApplication::translate("MainWindow", "Seleccionar Doctor:", nullptr));
        lblFecha->setText(QCoreApplication::translate("MainWindow", "Seleccionar Fecha:", nullptr));
        lblHora->setText(QCoreApplication::translate("MainWindow", "Seleccionar Hora:", nullptr));
        lblPaciente->setText(QCoreApplication::translate("MainWindow", "Nombre del Paciente:", nullptr));
        lblDNI->setText(QCoreApplication::translate("MainWindow", "DNI del Paciente:", nullptr));
        btnReservar->setText(QCoreApplication::translate("MainWindow", "Reservar Cita", nullptr));
        btnListarCitas->setText(QCoreApplication::translate("MainWindow", "Listar Citas", nullptr));
        btnEliminarCita->setText(QCoreApplication::translate("MainWindow", "Eliminar Cita Seleccionada", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
