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
    QComboBox *comboBox;
    QPushButton *btnVer;
    QPushButton *btnReservar;
    QLabel *label_2;
    QTableView *tableView;
    QLineEdit *txtDNI;
    QLineEdit *txtPaciente;
    QLabel *label_3;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(465, 487);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/imagenes/walla.jpg);  /* Si la imagen est\303\241 en recursos */\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-attachment: fixed;\n"
"    background-color: #f4f4f4;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(50, 30, 141, 22));
        btnVer = new QPushButton(centralwidget);
        btnVer->setObjectName("btnVer");
        btnVer->setGeometry(QRect(180, 70, 111, 31));
        btnVer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1c5980;\n"
"}\n"
""));
        btnReservar = new QPushButton(centralwidget);
        btnReservar->setObjectName("btnReservar");
        btnReservar->setGeometry(QRect(190, 400, 75, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 10, 61, 16));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial Rounded MT\";"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(60, 110, 361, 191));
        txtDNI = new QLineEdit(centralwidget);
        txtDNI->setObjectName("txtDNI");
        txtDNI->setGeometry(QRect(190, 340, 91, 22));
        txtPaciente = new QLineEdit(centralwidget);
        txtPaciente->setObjectName("txtPaciente");
        txtPaciente->setGeometry(QRect(190, 310, 231, 22));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 340, 101, 16));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 310, 111, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 465, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "--Seleccione Doctor--", nullptr));

        btnVer->setText(QCoreApplication::translate("MainWindow", "Ver horarios", nullptr));
        btnReservar->setText(QCoreApplication::translate("MainWindow", "Reservar cita", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Doctor", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "DNI del paciente:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nombre de paciente:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
