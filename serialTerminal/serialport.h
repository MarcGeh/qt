#ifndef SERIALPORT_H
#define SERIALPORT_H

#include<bits/stdc++.h>
#include<iostream>
#include <termios.h>
using namespace std;

typedef struct termios Termios;

class SerialPort
{
private:
    int port;
    Termios tty;
public:
    SerialPort();
    bool open_port(string device, unsigned int baudrate);
    void close_port();
    bool is_open();
    string read_data();
    void send_data(string data);
    static vector<string> list_all_ports();
};

#endif // SERIALPORT_H
