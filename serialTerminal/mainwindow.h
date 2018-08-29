#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"
#include <QThread>
#include <QMutex>

namespace Ui {
class MainWindow;
class TerminalRenderThread;
}

Q_DECLARE_METATYPE(string);

class TerminalRenderThread : public QThread
{
    Q_OBJECT

public:
    TerminalRenderThread(QObject *parent = NULL);
    ~TerminalRenderThread() override;
    void render();
    void port_connect(Ui::MainWindow *ui);
    void send_data(Ui::MainWindow *ui);
    void send_calibration_data();

protected:
    void run() override;

private:
    SerialPort port;

signals:
    void received_data(string data);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TerminalRenderThread receive_thread;
    string current_line;
    void build_current_line(string data);
    void check_line();
    void extract_heap(string* data);

private slots:
    void refresh();
    void port_connect();
    void update_data(string data);
    void catch_pressed();
    void clear_history();
    void send();
    void calibrate();
};

#endif // MAINWINDOW_H
