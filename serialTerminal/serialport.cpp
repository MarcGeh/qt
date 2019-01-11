#include "serialport.h"
#include <unistd.h>
#include <fcntl.h>


SerialPort::SerialPort()
{
    this->port = -1;
    memset(&this->tty, 0, sizeof(tty));
}

vector<string> SerialPort::list_all_ports()
{
    int fd;
    string port;
    vector<string> list;
    for(int i = 0; i < 256; i++)
    {
        port.clear();
        port.append("/dev/ttyUSB");
        port.append(to_string(i));
        fd = open(port.c_str(), O_RDWR);
        if(fd != -1)
        {
            list.push_back(port);
            cout << "Found: " << port << endl;
            close(fd);
        }
    }
    /*for(int i = 0; i < 256; i++)
    {
        port.clear();
        port.append("/dev/ttyS");
        port.append(to_string(i));
        fd = open(port.c_str(), O_RDWR);
        if(fd != -1)
        {
            list.push_back(port);
            close(fd);
        }
    }*/
    return list;
}

bool SerialPort::open_port(string device, unsigned int baudrate)
{
    close_port();

    this->port = open(device.c_str(), O_RDWR | O_NOCTTY);
    if(this->port == -1)
    {
        return false;
    }

    memset(&this->tty, 0, sizeof(tty));
    if(tcgetattr(this->port, &this->tty) != 0)
    {
        cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << endl;
        return false;
    }

    speed_t baud_flag = B0;
    switch(baudrate)
    {
        case 9600: baud_flag = B9600; break;
        case 19200: baud_flag =B19200; break;
        case 38400: baud_flag =B38400; break;
        case 57600: baud_flag =B57600; break;
        case 115200: baud_flag =B115200; break;
        case 230400: baud_flag =B230400; break;
        case 460800: baud_flag =B460800; break;
        case 921600: baud_flag =B921600; break;
        default: baud_flag = B115200; break;
    };

    cfsetospeed (&tty, static_cast<speed_t>(baud_flag));
    cfsetispeed (&tty, static_cast<speed_t>(baud_flag));

    tty.c_cflag     &=  static_cast<unsigned int>(~PARENB);        // Make 8n1
    tty.c_cflag     &=  static_cast<unsigned int>(~CSTOPB);
    tty.c_cflag     &=  static_cast<unsigned int>(~CSIZE);
    tty.c_cflag     |=  CS8;
    tty.c_cflag     &=  ~CRTSCTS;       // no flow control
    tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
    tty.c_oflag     =   0;                  // no remapping, no delays
    tty.c_cc[VMIN]      =   1;
    tty.c_cc[VTIME]     =   10;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    cfmakeraw(&tty);

    tcflush(port, TCIFLUSH);
    if (tcsetattr (port, TCSANOW, &tty) != 0)
    {
        cout << "Error " << errno << " from tcsetattr" << endl;
        return false;
    }
    return true;
}

void SerialPort::close_port()
{
    if(this->port != -1)
    {
        close(this->port);
        this->port = -1;
    }
}

bool SerialPort::is_open()
{
    if(this->port != -1)
    {
        return true;
    }
    return false;
}

string SerialPort::read_data()
{
    char buf[4096];
    memset(buf, '\0', sizeof(buf));

    ssize_t n = read(port, buf, sizeof(buf));
    if(n < 0)
    {
        cout << "Error reading: " << strerror(errno) << endl;
        return string("");
    }
    return string(buf);
}

void SerialPort::send_data(string data)
{
    char d[2];
    d[1] = '\0';
    for(unsigned long i = 0; i < data.length(); i++)
    {
        d[0] = data.c_str()[i];
        write(port, d, 1);
        usleep(1000);
    }

    d[0] = '\r';
    write(port, d, 1);
    usleep(1000);
    d[0] = '\n';
    write(port, d, 1);
    usleep(10000);
}
