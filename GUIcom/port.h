#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Port:public QObject
{
Q_OBJECT
public:

  explicit Port(QObject *parent = nullptr);

  ~Port();

  QSerialPort thisPort;

public slots:
  void ReadInPort();
  void Write_Settings_Port(QString name, int baudrate);
  void Process_Port();
  void WriteToPort(QByteArray data);

signals:
  void OutPort(QString data);
  void finished_Port();

private:

};

#endif // PORT_H
