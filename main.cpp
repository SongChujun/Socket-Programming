#include "mainwindow.h"
#include <QApplication>
#include "QTextCodec"
#include "QFile"
#include <utility>
#include "globalvar.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("C:/Users/92550/Desktop/Server_VS/usermessage.txt");
    int flag;
    string username;
    string password;
    string protque;
    string protans;
    vector<string> tmpvs;
    if(file.open(QIODevice::ReadWrite))
    {
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            string str(line);
            vector<string> tmpvs;
            flag=0;
            for(int i=0;i<str.size();i++)
            {
				if ((str[i] == '\r') || (str[i] == '\n'))
					break;
				while ((str[i] == ' ') && (str[i + 1] == ' '))
				{
					i++;
				}
				if (str[i] == ' ')
				{
					flag++;
					continue;
				}
                if(flag==0)
                {
                    username.push_back(str[i]);
                }
                else if(flag==1)
                {
                    password.push_back(str[i]);
                }
                else if(flag==2)
                {
                    protque.push_back(str[i]);
                }
                else if(flag==3)
                {
                    protans.push_back(str[i]);
                }
            }
            tmpvs.push_back(password);
            tmpvs.push_back(protque);
            tmpvs.push_back(protans);
            usermessage[username]=tmpvs;
            tmpvs.clear();
            username.clear();
            password.clear();
            protque.clear();
            protans.clear();
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
