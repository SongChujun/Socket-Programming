#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include "vector"
using namespace std;
class Server:public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    vector<QTcpSocket*> TcpClientSocketVector;
signals:
    void updateServer(QString,int);
public slots:
    void show();
	void disconnected();
    void updateClients(QString, int);
    void slotDisconnected(int);
    void readMessage();
protected:
    void incommingConnection(int socketDescriptor);
};

#endif // SERVER_H
