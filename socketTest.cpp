typedef timeval t;
//
// Created by 樊星 on 2021/11/28.
//

class socketTest{
public:
    void* _client(std::string _host,int _port,int _sec,int _y);
private:
    int _unlock(int _fd);

};
int socketTest::_unlock(int _fd){
    int old_option = fcntl( _fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( _fd, F_SETFL, new_option );
    return old_option;
}
void* socketTest::_client(std::string _host,int _port,int _sec,int _y){
    t _t;
    _t.tv_sec = _sec;
    _t.tv_usec = 0;
    int _socket;
    int _reuse_addr = 1;
    const int* RESUSE_ADDR = &_reuse_addr;
    struct sockaddr_in _addrin;
    fd_set readfds;
    fd_set writefds;
    // 设置连接参数
    _addrin.sin_addr.s_addr = inet_addr(reinterpret_cast<const char *>(&_host));
    _addrin.sin_family = AF_INET;
    _addrin.sin_port = htons(_port);
    memset(&(_addrin.sin_zero),0,8);
    _socket = socket(PF_INET, SOCK_STREAM, 0);
    if (_socket == -1){
        perror("socket error");
        return 0;
    }
    int fdopt = _unlock( _socket );      //套接字设置为非阻塞套接字
    setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR,RESUSE_ADDR,sizeof(RESUSE_ADDR));
    int a = connect (_socket, (struct sockaddr *)& _addrin, sizeof(struct sockaddr_in));
    if ( a == 0 )
    {
        //  printf( "connect with server immediately\n" );
        fcntl( _socket, F_SETFL, fdopt );   //set old optional back
    }
    FD_ZERO( &readfds );
    FD_SET( _socket, &writefds );
    int ret = select(_socket + 1 , NULL, &writefds, NULL, &_t);
    std::string res = "\033[01;32mConnection succeeded ！！!\033[0m";
    if(ret <=  0){
        res = "Time out...";
    }
    int error = 0;
    socklen_t length = sizeof( error );
    if( getsockopt( _socket, SOL_SOCKET, SO_ERROR, &error, &length ) < 0 )
    {
        //        std::cout<<_port << " ----> " << "端口获取套接字失败" <<std::endl;
        //        close(_socket);
        //        return;
        res = "Time out...";
    }
    if( error != 0 )
    {
        //        std::cout<<_port << " ----> " << "端口连接失败:"<< error <<std::endl;
        //        close(_socket);
        //        return;
        res = "Time out...";
    }

    if((strcmp(res.c_str(),"Time out...") == 0) &&  _y == 1){
        //printf("\033[01;31m%d\033[0m  -----> %s ----->%d \n",_port,"超时",_y);
    }else{
        printf("\033[01;31m%d\033[0m  -----> %s\n",_port,res.c_str());
    }
    close(_socket);
    return 0;
}
