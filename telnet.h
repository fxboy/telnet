//
// Created by 樊星 on 2021/11/28.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <pthread.h>
#include <cmath>
#include <vector>
#include "socketTest.cpp"
class socketTest;
void oPort(char* ip,unsigned int port,unsigned int t,int y);
void mPort(char* ip,unsigned int s,unsigned int e,unsigned int t,int y);
int foreach(int _port,std::vector<int>*_ports,int i,int now);
typedef socketTest client;
struct thread_data{
    char *ip;
    std::vector<int> ports = {};
    int t;
    int y;
};
void* start(void* a){
    struct thread_data *my_data;
    my_data = (struct thread_data *) a;
    for(int i = 0;i<my_data->ports.size();i++){
        oPort(my_data->ip,my_data->ports[i],my_data->t,my_data->y);
    }
    my_data->ports.clear();
    return 0;
}


int foreach(int _port,std::vector<int>*_ports,int i,int now){
    if(i == 0){
        return now;
    }
    std::vector<int> c = (*_ports);
    _ports->push_back(_port);
    --i;
    _port++;
    now++;
    return foreach(_port,_ports,i,now);
}
