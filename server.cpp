//up zhuce in denglu
#include "server.h"
#include "QMessageBox"
#include "QTcpSocket"
#include "QIODevice"
#include "QObject"
#include "Mainwindow.h"
#include "globalvar.h"
#include "QFile"
#include "QTextStream"
#include "qtextstream.h"
#include "string.h"
#include "map"
using namespace std;
string ACK;
QString QSACK;
Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
    connect(this,SIGNAL(newConnection()),this,SLOT(show()));
}
void Server::incommingConnection(int socketDescriptor)
{
}
void Server::updateClients(QString msg, int length)
{
    string tmp=msg.toStdString();
    string username="";
    string password="";
    string protque="";
    string protans="";
    string ip_addr="";
    string strport="";
    int flag=0;
    int tmpport=0;
    vector<string> tmpvs;
    string tmps;
    if((tmp[0]=='U')&&(tmp[1]=='P'))//zhuce
    {
        ACK.clear();
        ACK.append("3");
        ACK.append(" ");
        for(auto iter=onlinemessage.begin();iter!=onlinemessage.end();iter++)
        {
            ACK.append(iter->first);
            ACK.append(" ");
            ACK.append((iter->second)[0]);
            ACK.append(" ");
            ACK.append((iter->second)[1]);
            ACK.append(" ");
        }
		ACK.append(" ");
        ACK.append("||");
        ACK.append(" ");
        for(auto iter=usermessage.begin();iter!=usermessage.end();iter++)
        {
            if(onlinemessage.find(iter->first)==onlinemessage.end())
            {
                ACK.append(iter->first);
                ACK.append(" ");
            }
        }

        QSACK=QString::fromStdString(ACK);
        if(TcpClientSocketVector.size()!=0)
        {
        TcpClientSocketVector[TcpClientSocketVector.size()-1]->write(QSACK.toLatin1(),QSACK.length());
        }
        strport.clear();
        for(int i=3;i<tmp.size();i++)
        {

            if(tmp[i]==' ')
            {
                flag++;
            }
            if(flag==0)
            {
                username.push_back(tmp[i]);
            }
            else if(flag==1)
            {
                password.push_back((tmp[i]));
            }
            else if(flag==2)
            {
                protque.push_back((tmp[i]));
            }
            else if(flag==3)
            {
                protans.push_back((tmp[i]));
            }
            else if(flag==4)
            {
                ip_addr.push_back((tmp[i]));
            }
            else if(flag==5)
            {
                strport.push_back((tmp[i]));
                if(strport.size()==5)
                    break;
            }
        }
		UserToSocket[username] = TcpClientSocketVector[TcpClientSocketVector.size() - 1];
        tmpvs.push_back(password);
        tmpvs.push_back(protque);
        tmpvs.push_back(protans);
		usermessage[username] = tmpvs;
        tmpvs.clear();
        tmpvs.push_back(ip_addr);
        tmpvs.push_back(strport);   
        onlinemessage[username]=tmpvs;
        QFile file("C:/Users/92550/Desktop/Server_VS/usermessage.txt");
		if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
		{
			QMessageBox::warning(NULL, "warning", "Open File Failed!!", QMessageBox::Yes, QMessageBox::Yes);
		}
        QTextStream out(&file);
        tmps.append(username);
        tmps.append(" ");
        tmps.append(password);
        tmps.append(" ");
        tmps.append(protque);
        tmps.append(" ");
        tmps.append(protans);
        tmps.append("\r\n");
        QString uti=QString::fromStdString(tmps);
        out<<uti;
        
        
        tmpport=8011;
        ip_addr=(TcpClientSocketVector[TcpClientSocketVector.size()-1]->localAddress()).toString().toStdString();
        strport=std::to_string(tmpport);

        for(int i=0;i<TcpClientSocketVector.size()-1;i++)
        {
            ACK.clear();
            QTcpSocket* item=TcpClientSocketVector[i];
            ACK.append("5");
            ACK.append(" ");
            ACK.append(username);
            ACK.append(" ");
            ACK.append(ip_addr);
            ACK.append(" ");
            ACK.append(strport);
			ACK.append(" ");
            QSACK=QString::fromStdString(ACK);
            item->write(QSACK.toLatin1(),QSACK.length());
        }
    }
    else if((tmp[0]=='I')&&(tmp[1]=='N'))
    {
        for(int i=3;i<tmp.size();i++)
        {
            if(tmp[i]==' ')
            {
                flag++;
				continue;
            }
            if(flag==0)
            {
                username.push_back(tmp[i]);
            }
			else if (flag == 1)
			{
				password.push_back((tmp[i]));
			}
            else if(flag==2)
            {
                ip_addr.push_back((tmp[i]));
            }
            else if(flag==3)
            {
                strport.push_back((tmp[i]));
            }
        }
        ACK.clear();
        if(usermessage.find(username)==usermessage.end())
        {
           ACK.append("0");
           QSACK=QString::fromStdString(ACK);
           TcpClientSocketVector[TcpClientSocketVector.size()-1]->write(QSACK.toLatin1(),QSACK.length());
        }
        else if((usermessage[username])[0]!=password)
        {
            ACK.append("1");
            QSACK=QString::fromStdString(ACK);
            TcpClientSocketVector[TcpClientSocketVector.size()-1]->write(QSACK.toLatin1(),QSACK.length());
        }
		else if (onlinemessage.find(username) != onlinemessage.end())
		{
			ACK.append("7");
			QSACK = QString::fromStdString(ACK);
			TcpClientSocketVector[TcpClientSocketVector.size() - 1]->write(QSACK.toLatin1(), QSACK.length());
		}
        else
        {
			ACK.clear();
			ACK.append("4");
			ACK.append(" ");
			for (auto iter = onlinemessage.begin(); iter != onlinemessage.end(); iter++)
			{
				ACK.append(iter->first);
				ACK.append(" ");
				ACK.append((iter->second)[0]);
				ACK.append(" ");
				ACK.append((iter->second)[1]);
				ACK.append(" ");
			}
			ACK.append(" ");
			ACK.append("||");
			ACK.append(" ");
			for (auto iter = usermessage.begin(); iter != usermessage.end(); iter++)
			{
				if (onlinemessage.find(iter->first) == onlinemessage.end()&&((iter->first) != username))
				{
					ACK.append(iter->first);
					ACK.append(" ");
				}
			}
			UserToSocket[username] = TcpClientSocketVector[TcpClientSocketVector.size() - 1];
            QSACK=QString::fromStdString(ACK);
            TcpClientSocketVector[TcpClientSocketVector.size()-1]->write(QSACK.toLatin1(),QSACK.length());
            tmpvs.push_back(ip_addr);
            tmpvs.push_back(strport);
            onlinemessage[username]=tmpvs;
			strport = "8011";
			for (int i = 0; i<TcpClientSocketVector.size() - 1; i++)
			{
				ACK.clear();
				QTcpSocket* item = TcpClientSocketVector[i];
				ACK.append("5");
				ACK.append(" ");
				ACK.append(username);
				ACK.append(" ");
				ACK.append(ip_addr);
				ACK.append(" ");
				ACK.append(strport);
				ACK.append(" ");
				QSACK = QString::fromStdString(ACK);
				item->write(QSACK.toLatin1(), QSACK.length());
			}
        }
    }
	else if ((tmp[0] == 'O') && (tmp[1] == 'T'))
	{
		string username;
		for (size_t i = 3; i < tmp.size(); i++)
		{
			if (tmp[i] == ' ')
				break;
			username.push_back(tmp[i]);
		}

		QTcpSocket* DisconnectedSocket = UserToSocket[username];
		for (size_t i = 0; i < TcpClientSocketVector.size(); i++)
		{
			if (TcpClientSocketVector[i] == DisconnectedSocket)
				TcpClientSocketVector.erase(TcpClientSocketVector.begin() + i);
		}
		onlinemessage.erase(username);
		ACK.clear();
		ACK.append("6");
		ACK.append(" ");
		ACK.append(username);
		ACK.append(" ");
		QSACK = QString::fromStdString(ACK);
		for (size_t i = 0; i < TcpClientSocketVector.size(); i++)
		{
				TcpClientSocketVector[i]->write(QSACK.toLatin1(),QSACK.size());
		}
	}
	else 
    {
        /*retrive password*/
    }
}
void Server::slotDisconnected(int Descriptor)
{
}
void Server::show()
{
     QTcpSocket* m_tcpSocket = this->nextPendingConnection();
	 
     TcpClientSocketVector.push_back(m_tcpSocket);
     connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
	 connect(TcpClientSocketVector[TcpClientSocketVector.size() - 1], SIGNAL(disconnected()), this, SLOT(disconnected()));
}
void Server::readMessage()
{
	if (TcpClientSocketVector.size() == 0)
		return;
    while ((TcpClientSocketVector.size()>0)&&(TcpClientSocketVector[TcpClientSocketVector.size()-1]->bytesAvailable()>0))
    {
        int length=TcpClientSocketVector[TcpClientSocketVector.size()-1]->bytesAvailable();
        char buf[1024];
        TcpClientSocketVector[TcpClientSocketVector.size()-1]->read(buf,length);
        QString msg=buf;
        emit updateClients(msg,length);
    }
}
void Server::disconnected()
{

}