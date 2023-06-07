#include <QDebug>
#include "mytcpserver-ex.h"

void Parsing(int connection_id, QString message,MyTcpServer& server){
    QList<QString> parts = message.split('&');
    qDebug() << parts[0];

}
