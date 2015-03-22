#ifndef DATABITS_H
#define DATABITS_H

#include "optparser.h"
#include <QSerialPort>

namespace OPTPARSER
{
    class Databits
    {
    public:
        Databits(const std::string& in);
        QSerialPort::DataBits value;
    };
}

#endif // DATABITS_H
