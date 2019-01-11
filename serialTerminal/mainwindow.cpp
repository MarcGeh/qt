#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QtWidgets>

TerminalRenderThread::TerminalRenderThread(QObject *parent) : QThread(parent)
{
    this->port = SerialPort();
}

TerminalRenderThread::~TerminalRenderThread()
{
    port.close_port();
}

void TerminalRenderThread::render()
{
    if(!isRunning())
    {
        start(LowPriority);
    }
}

void TerminalRenderThread::run()
{
    forever {
        if(port.is_open())
        {
            string received = port.read_data();
            if(received.length() > 0)
            {
                emit received_data(received);
            }
        }
        msleep(200);
    }
}

void TerminalRenderThread::send_data(Ui::MainWindow *ui)
{
    port.send_data(ui->send_input->text().toStdString());
}

void TerminalRenderThread::send_calibration_data_led()
{
    port.send_data("test --adjust_led 100 100 100");
}

void TerminalRenderThread::send_calibration_data_3v()
{
    port.send_data("test --battery 3000");
}

void TerminalRenderThread::send_calibration_data_2v()
{
    port.send_data("test --battery 2000");
}

void TerminalRenderThread::send_calibration_data_commit()
{
    port.send_data("test --commit_cal");
}


void TerminalRenderThread::port_connect(Ui::MainWindow *ui)
{
    QString device = ui->select_port->currentText();
    unsigned int baudrate = static_cast<unsigned int>(stoi(ui->select_baudrate->currentText().toStdString()));
    if(port.is_open())
    {
        port.close_port();
        ui->button_send->setEnabled(0);
        ui->button_calib_led->setEnabled(0);
        ui->button_calib_2V->setEnabled(0);
        ui->button_calib_3V->setEnabled(0);
        ui->button_calib_commit->setEnabled(0);
        ui->button_connect->setText("Connect");
    }
    else
    {
        if(port.open_port(device.toStdString(), baudrate))
        {
            ui->button_connect->setText("Disconnect");
            ui->button_send->setEnabled(1);
            ui->button_calib_led->setEnabled(1);
            ui->button_calib_2V->setEnabled(1);
            ui->button_calib_3V->setEnabled(1);
            ui->button_calib_commit->setEnabled(1);
        }
        else
        {
            ui->button_connect->setText("Connect");
            ui->statusBar->showMessage("Unable to connect to port", 5000);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("serialTerminal");

    qRegisterMetaType<string>();
    this->refresh();
    connect(ui->button_refresh, SIGNAL(clicked()), SLOT(refresh()));
    connect(ui->button_connect, SIGNAL(clicked()), SLOT(port_connect()));
    connect(ui->button_catch, SIGNAL(clicked()), SLOT(catch_pressed()));
    connect(ui->button_clear_history, SIGNAL(clicked()), SLOT(clear_history()));
    connect(ui->button_send, SIGNAL(clicked()), SLOT(send()));
    connect(ui->button_calib_led, SIGNAL(clicked()), SLOT(calibrate_led()));
    connect(ui->button_calib_2V, SIGNAL(clicked()), SLOT(calibrate_2v()));
    connect(ui->button_calib_3V, SIGNAL(clicked()), SLOT(calibrate_3v()));
    connect(ui->button_calib_commit, SIGNAL(clicked()), SLOT(commit_calibration()));
    connect(&receive_thread, SIGNAL(received_data(string)), SLOT(update_data(string)));

    QStringList baudrates = {
        "9600",
        "19200",
        "38400",
        "57600",
        "115200",
        "230400",
        "460800",
        "921600"
    };
    ui->select_baudrate->addItems(baudrates);
    ui->select_baudrate->setCurrentIndex(4);
    ui->input1->setMaximumBlockCount(51200);
}

MainWindow::~MainWindow()
{
    receive_thread.terminate();
    QThread::msleep(1000);
    delete ui;
}

void MainWindow::refresh()
{
    vector<string> list = SerialPort::list_all_ports();
    ui->select_port->clear();
    if(list.size() > 0)
    {
        for(vector<string>::iterator it = list.begin(); it != list.end(); it++)
        {
            ui->select_port->addItem(QString::fromStdString(*it));
        }
        ui->button_connect->setDisabled(0);
    }
    else
    {
        ui->statusBar->showMessage("No connected ports found", 5000);
        ui->button_connect->setDisabled(1);
    }
}

void MainWindow::port_connect()
{
    receive_thread.port_connect(ui);
    receive_thread.render();
}

void MainWindow::build_current_line(string data)
{
    const char *str_data = data.c_str();

    for(unsigned long i = 0; i < data.length(); i++)
    {
        if(str_data[i] == '\n')
        {
            check_line();
            current_line.clear();
        }
        else
        {
            current_line += str_data[i];
        }
    }
}

void MainWindow::check_line()
{
    if(!ui->button_catch->isEnabled())
    {
        string look_for = ui->catch_phrase->text().toStdString();
        if(look_for.length() > 0)
        {
//            cout << "Look for: " << look_for << endl << flush;
            if(current_line.find(look_for) != string::npos)
            {
                ui->input_catch->clear();
                ui->input_catch->insertPlainText(ui->input1->toPlainText());
                ui->button_catch->setEnabled(1);
            }
        }
    }
}

void MainWindow::extract_heap(string* data)
{
    static string heap_string = "";
    static bool append = false;

    const char* data_str = data->c_str();
    bool start_found = false;
    size_t start_pos = 0;
    bool end_found = false;
    size_t end_pos = data->length();

    for(size_t i = 0; i < strlen(data_str); i++)
    {
        if(data_str[i] == 3)
        {
            append = false;
            end_found = true;
            end_pos = i+1;
            cout << heap_string << endl;
            heap_string = "";
            continue;
        }
        else if(data_str[i] == 2)
        {
            append = true;
            start_found = true;
            start_pos = i;
            continue;
        }
        if(append)
        {
            heap_string.append(&data_str[i], 1);
            //data->erase(i, 1);
        }
    }

    if(start_found || end_found)
    {
        data->erase(start_pos, end_pos - start_pos);
    }
}

void MainWindow::update_data(string data)
{
//    replace(data.begin(), data.end(), '\r', ' ');
//    QCursor cursor = QCursor(ui->input1->cursor());
    extract_heap(&data);

    QTextCursor cursor = ui->input1->textCursor();
    QScrollBar* scrollbar = ui->input1->verticalScrollBar();
    int scroll_position = scrollbar->value();
    bool auto_scroll = false;
    if(scroll_position == scrollbar->maximum())
    {
        auto_scroll = true;
    }
    int anchor = cursor.anchor();
    int position = cursor.position();
    ui->input1->moveCursor(QTextCursor::End);
    ui->input1->insertPlainText(QString::fromStdString(data));
    cursor.setPosition(anchor);
    cursor.setPosition(position, QTextCursor::MoveMode::KeepAnchor);
    ui->input1->setTextCursor(cursor);

    if(auto_scroll)
    {
        scrollbar->setValue(scrollbar->maximum());
    }
    else
    {
        scrollbar->setValue(scroll_position);
    }

    build_current_line(data);
//    cout << ui->input1->blockCount() << " of " << ui->input1->maximumBlockCount() << endl;
}

void MainWindow::catch_pressed()
{
    ui->button_catch->setEnabled(0);
}

void MainWindow::clear_history()
{
    ui->input1->clear();
}

void MainWindow::send()
{
    receive_thread.send_data(ui);
}

void MainWindow::calibrate_led()
{
    receive_thread.send_calibration_data_led();
}

void MainWindow::calibrate_3v()
{
    receive_thread.send_calibration_data_3v();
}

void MainWindow::calibrate_2v()
{
    receive_thread.send_calibration_data_2v();
}

void MainWindow::commit_calibration()
{
    receive_thread.send_calibration_data_commit();
}
