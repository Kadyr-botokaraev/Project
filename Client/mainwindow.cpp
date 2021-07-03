#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLocalSocket>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1",33333);
    connect(socket, &QTcpSocket::readyRead,this, &MainWindow::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::sockDisc);
}

MainWindow::~MainWindow()
{
    socket->close();
    delete ui;

}




void MainWindow::sendToServer(QString mess)
{
    QByteArray array;
    array.clear();

    array.append(mess.toStdString());



    socket->write(array);

}


void MainWindow::on_pushButton_clicked()
{


    QString login = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    QString messageToServer = "auth&"+login+"#"+pass;

    sendToServer(messageToServer);



}



void MainWindow::on_pushButton_2_clicked()
{

    QString Text = ui->textEdit->toPlainText();
    QString Key = ui->lineEdit_3->text();

    QString messageToServer = "shifr&" + Text + "&&&" + Key;
    sendToServer(messageToServer);


}

void MainWindow::on_pushButton_3_clicked()
{

    QString Text = ui->textEdit->toPlainText();
    QString Key = ui->lineEdit_3->text();

    QString messageToServer = "de_shifr&" + Text + "&&&" + Key;


    sendToServer(messageToServer);

}


void MainWindow::sockDisc(){
    socket->close();
}







void MainWindow::sockReady(){

    QString message="";
    QByteArray array;
    while(socket->bytesAvailable()>0)
    {
        array = socket->readAll();
        message.append(array);
    }

    array.clear();



//    qDebug() << message<<"\n";


    //array.append(message.toStdString());

    //socket->write(array);

    // message is equal message from Server

    // Разобрать сообщение от сервера
    // Если автриз

     array.append(message.toStdString());
     qDebug() << message;

    if(message =="auth&ok") {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Авторизация");
        msgBox.setText("Вы успешно авторизовались!");
        msgBox.exec();
    }
    else if (message =="auth&false") {
        QMessageBox msg;
        msg.setWindowTitle("Авторизация");
        msg.setText("Авторизация прошла не успешно!");
        msg.exec();
    }



    else {
        ui->textEdit_2->setText(message);
    }








}








