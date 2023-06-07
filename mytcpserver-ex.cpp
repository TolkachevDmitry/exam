#include "mytcpserver-ex.h"
#include "serverfunction.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 34576)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        qDebug() << "New client connected";
        QTcpSocket *mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        int connection_id = mTcpSocket->socketDescriptor();
        mTcpSocket->write("Your connection ID: ");
        mTcpSocket->write(QString::number(connection_id).toUtf8());
        mTcpSocket->write("\r\n");
        mTcpSocket->flush(); // Добавьте эту строку
        Clients.insert(mTcpSocket, connection_id);
        connect(mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket * mTcpSocket;
    mTcpSocket = (QTcpSocket*)sender();
    QByteArray array;
    QString str;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array=mTcpSocket->readAll();
        str.append(array);
    }
    qDebug()<< "recieve:"<<str;
    Parsing(str.toUtf8());
}

int MyTcpServer::getConnectionId(QTcpSocket *socket)
{
    return Clients.value(socket);
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *mTcpSocket = (QTcpSocket*)sender();
    qDebug() << "Client disconnected";
    Clients.remove(mTcpSocket);
    mTcpSocket->close();
}
