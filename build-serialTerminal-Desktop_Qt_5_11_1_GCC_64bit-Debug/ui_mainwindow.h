/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tap_input;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *input1;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *send_input;
    QPushButton *button_send;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_clear_history;
    QPushButton *button_calib_led;
    QPushButton *button_calib_3V;
    QPushButton *button_calib_2V;
    QPushButton *button_calib_commit;
    QWidget *tap_catch;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *catch_phrase;
    QPushButton *button_catch;
    QPlainTextEdit *input_catch;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *button_refresh;
    QComboBox *select_port;
    QComboBox *select_baudrate;
    QPushButton *button_connect;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1146, 591);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tap_input = new QWidget();
        tap_input->setObjectName(QStringLiteral("tap_input"));
        verticalLayout_2 = new QVBoxLayout(tap_input);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        input1 = new QPlainTextEdit(tap_input);
        input1->setObjectName(QStringLiteral("input1"));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font.setItalic(false);
        input1->setFont(font);
        input1->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        input1->setUndoRedoEnabled(false);
        input1->setReadOnly(true);

        verticalLayout_2->addWidget(input1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        send_input = new QLineEdit(tap_input);
        send_input->setObjectName(QStringLiteral("send_input"));

        horizontalLayout_4->addWidget(send_input);

        button_send = new QPushButton(tap_input);
        button_send->setObjectName(QStringLiteral("button_send"));
        button_send->setEnabled(false);

        horizontalLayout_4->addWidget(button_send);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        button_clear_history = new QPushButton(tap_input);
        button_clear_history->setObjectName(QStringLiteral("button_clear_history"));

        horizontalLayout->addWidget(button_clear_history);

        button_calib_led = new QPushButton(tap_input);
        button_calib_led->setObjectName(QStringLiteral("button_calib_led"));
        button_calib_led->setEnabled(false);

        horizontalLayout->addWidget(button_calib_led);

        button_calib_3V = new QPushButton(tap_input);
        button_calib_3V->setObjectName(QStringLiteral("button_calib_3V"));
        button_calib_3V->setEnabled(false);

        horizontalLayout->addWidget(button_calib_3V);

        button_calib_2V = new QPushButton(tap_input);
        button_calib_2V->setObjectName(QStringLiteral("button_calib_2V"));
        button_calib_2V->setEnabled(false);

        horizontalLayout->addWidget(button_calib_2V);

        button_calib_commit = new QPushButton(tap_input);
        button_calib_commit->setObjectName(QStringLiteral("button_calib_commit"));
        button_calib_commit->setEnabled(false);

        horizontalLayout->addWidget(button_calib_commit);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tap_input, QString());
        tap_catch = new QWidget();
        tap_catch->setObjectName(QStringLiteral("tap_catch"));
        verticalLayout_3 = new QVBoxLayout(tap_catch);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(tap_catch);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        catch_phrase = new QLineEdit(tap_catch);
        catch_phrase->setObjectName(QStringLiteral("catch_phrase"));

        horizontalLayout_3->addWidget(catch_phrase);

        button_catch = new QPushButton(tap_catch);
        button_catch->setObjectName(QStringLiteral("button_catch"));
        button_catch->setEnabled(false);

        horizontalLayout_3->addWidget(button_catch);


        verticalLayout_3->addLayout(horizontalLayout_3);

        input_catch = new QPlainTextEdit(tap_catch);
        input_catch->setObjectName(QStringLiteral("input_catch"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        input_catch->setFont(font1);
        input_catch->setReadOnly(true);

        verticalLayout_3->addWidget(input_catch);

        tabWidget->addTab(tap_catch, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 1, 0, 2, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        button_refresh = new QPushButton(centralWidget);
        button_refresh->setObjectName(QStringLiteral("button_refresh"));

        horizontalLayout_2->addWidget(button_refresh);

        select_port = new QComboBox(centralWidget);
        select_port->setObjectName(QStringLiteral("select_port"));

        horizontalLayout_2->addWidget(select_port);

        select_baudrate = new QComboBox(centralWidget);
        select_baudrate->setObjectName(QStringLiteral("select_baudrate"));

        horizontalLayout_2->addWidget(select_baudrate);

        button_connect = new QPushButton(centralWidget);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(false);

        horizontalLayout_2->addWidget(button_connect);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1146, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        button_send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        button_clear_history->setText(QApplication::translate("MainWindow", "Clear History", nullptr));
        button_calib_led->setText(QApplication::translate("MainWindow", "Calibrate LED", nullptr));
        button_calib_3V->setText(QApplication::translate("MainWindow", "Calibrate 3V", nullptr));
        button_calib_2V->setText(QApplication::translate("MainWindow", "Calibrate 2V", nullptr));
        button_calib_commit->setText(QApplication::translate("MainWindow", "Commit Calibration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tap_input), QApplication::translate("MainWindow", "Input", nullptr));
        label->setText(QApplication::translate("MainWindow", "Capture first occurrence of: ", nullptr));
        button_catch->setText(QApplication::translate("MainWindow", "Catch", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tap_catch), QApplication::translate("MainWindow", "Catch", nullptr));
        button_refresh->setText(QApplication::translate("MainWindow", "Refresh", nullptr));
        button_connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
