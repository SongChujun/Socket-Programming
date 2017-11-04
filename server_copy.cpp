#include "server.h"
#include "QMessageBox"
#include "QTcpSocket"
#include "QIODevice"
#include "QObject"
#include "Mainwindow.h"
#include "globalvar.h"
#include "QFile"
#include "string.h"
using namespace std;
QString ACK;
Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
    connect(this,SIGNAL(newConnection()),this,SLOT(show()));
}
void Server::incommingConnection(int socketDescriptor)
{
    QMessageBox::warning(NULL, "warning", "No username!", QMessageBox::Yes, QMessageBox::Yes);
//    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
//    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
//    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
//    tcpClientSocket->setSocketDescriptor(socketDescriptor);
//    tcpClientSocketList.append(tcpClientSocket);
}
void Server::updateClients(QString msg, int length)
{
    emit updateClients(msg,length);
}
void Server::slotDisconnected(int Descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item=tcpClientSocketList.at(i);
        if(item->socketDescriptor()==Descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return ;
}
void Server::show()
{
     m_tcpSocket = this->nextPendingConnection();
     connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}
void Server::readMessage()
{
//    QMessageBox::warning(NULL, "warning", "No password!", QMessageBox::Yes, QMessageBox::Yes);
    while ((m_tcpSocket->bytesAvailable())>0)
    {
        int length=m_tcpSocket->bytesAvailable();
        char buf[1024];
        m_tcpSocket->read(buf,length);
        string tmp=buf;
        string username="";
        string password="";
        if((tmp[0]=='U')&&(tmp[1]=='P'))
        {
            int i=tmp.find_first_of(' ');
            username=tmp.substr(2,i-2);
            password=tmp.substr(i+1,tmp.size()-i-2);
            usermessage[username]=std::make_pair(password,1);
            QFile file("C:/Users/92550/Documents/Server/usermessage.txt");
            QTextStream out(&file);
            tmp.append(" 1");
            tmp.append("\r\n");
            QString uti=QString::fromStdString(tmp);
            out<<uti;
            ACK="ack";
        }
        else
        {
            int i=tmp.find_first_of(' ');
            username=tmp.substr(2,i-2);
            password=tmp.substr(i+1,tmp.size()-i-1);
            if(usermessage.find(username)==usermessage.end())
            {
               ACK="1";
            }
            else if((usermessage[username]).first==password)
            {
                ACK="2";
            }
            else
            {
                usermessage[username].second=1;
                ACK="ack";
            }
        }
        m_tcpSocket->write(ACK.toLatin1(),ACK.length());
    }
}
