#include "port.h"
#include <QDebug>
#include <windows.h>

Port::Port(QObject *parent) : QObject(parent) {}

Port::~Port()
{
    qDebug("By in Thread!");
    emit finished_Port();
}

void Port :: Write_Settings_Port(QString name, int baudrate){
    thisPort.setPortName(name);
    thisPort.setBaudRate(baudrate);
    if (!thisPort.open(QIODevice::ReadWrite)) {
        return;
    }
}

void Port :: Process_Port(){
    qDebug("In Thread!");
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
}

void Port :: WriteToPort(QByteArray data){
    if(thisPort.isOpen()){
        thisPort.write(data);
    }
}

void Port :: ReadInPort(){
    QString data;
    data.append(thisPort.readAll());
    OutPort(data);
}
