#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }

    QThread *thread= new QThread;
    Port *PortNew = new Port();

    PortNew->moveToThread(thread);
    PortNew->thisPort.moveToThread(thread);

    connect(PortNew, SIGNAL(OutPort(QString)), this, SLOT(Print(QString)));
    connect(thread, SIGNAL(started()), PortNew, SLOT(Process_Port()));
    connect(PortNew, SIGNAL(finished_Port()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), PortNew, SLOT(deleteLater()));
    connect(PortNew, SIGNAL(finished_Port()), thread, SLOT(deleteLater()));
    connect(this,SIGNAL(settings(QString,int)),PortNew,SLOT(Write_Settings_Port(QString,int)));
    connect(this,SIGNAL(writeData(QByteArray)),PortNew,SLOT(WriteToPort(QByteArray)));

    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    writeData(qPrintable(this->ui->txtSend->text())); // Отправка данных в порт
}

void MainWindow::Print(QString data)
{
  ui->txtOutput->appendPlainText(data);
}


void MainWindow::on_Connect_clicked()
{
    settings(ui->cmbPort->currentText(),ui->txtBaud->text().toInt());
}

