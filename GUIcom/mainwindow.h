#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "port.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void settings(QString name, int baudrate);
    void writeData(QByteArray data);

private slots:

    void on_pushButton_clicked();
    void Print(QString data);
    void on_Connect_clicked();

private:
    Ui::MainWindow *ui;

    Port PortNew;
};
#endif // MAINWINDOW_H
