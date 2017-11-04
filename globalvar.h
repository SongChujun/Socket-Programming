#ifndef GLOBALVAR_H
#define GLOBALVAR_H
#include "map"
#include "vector"
#include "qtcpsocket.h"
using namespace std;
extern map<string,vector<string>> usermessage;
extern map<string,vector<string>> onlinemessage;
extern map<string, QTcpSocket*> UserToSocket;
/*string IntToString(int)*/;
#endif // GLOBALVAR_H
