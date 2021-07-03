#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include"functions.h"




MyTcpServer::~MyTcpServer()
{
    //mTcpSocket->close();
    mTcpServer->close();
    server_status=0;
}



MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}




void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
    }
}






void MyTcpServer::slotServerRead(){

    QString message="";



    QByteArray array;


    while(mTcpSocket->bytesAvailable()>0)
    {
        array = mTcpSocket->readAll();
        message.append(array);

    }

    array.clear();
  //  qDebug() << message<<"\n";
    message = parsing(message);

   //qDebug() << message;
    array.append(message.toStdString());

    mTcpSocket->write(array);



}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
