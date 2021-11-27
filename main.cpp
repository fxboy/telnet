#include "telnet.h"
int main (int value,char **point){
    // mPort("10.211.55.6", 4000,5010,10,1);
    //oPort(point[1], atoi(point[2]),10);
    if(value < 3){
        std::cout<<"telnet <IP> <PORT1> <PORT2> <VIEW> *为必填项目" <<std::endl;
        std::cout<<"* <IP> 主机地址" <<std::endl;
        std::cout<<"* <PORT1> 端口号" <<std::endl;
        std::cout<<"  <PORT2> 结束爆破端口" <<std::endl;
        std::cout<<"  <VIEW> 是否只显示连接成功 1.是 (默认) 0.否 只对爆破生效" <<std::endl;
        return 0;
    }
    // 查找当前端口
    if(value == 3){
        oPort(point[1], atoi(point[2]),10,0);
    }
    if(value == 4){
        mPort(point[1], atoi(point[2]),atoi(point[3]),10,1);
    }
    if(value == 5){
        mPort(point[1], atoi(point[2]),atoi(point[3]),10,atoi(point[4]));
    }
    return 0;
}

void oPort(char* ip,unsigned int s,unsigned int t,int y){
    client c = client();
    c._client(ip,s,t,y);
}

void mPort(char* ip,unsigned int s,unsigned int e,unsigned int t ,int y){
    // 防止结尾端口比开始端口小
    if(e < s ){
        int temp = s;
         s = e;
         e = temp;
    }
    if(s < 0 || e > 65536){
        printf("\033[01;31m%s\033[0m \n","请输入正确的端口范围");
        return;
    }
    // xs 为200 个线程下，每一个线程有多少内容
    double x = (e - s) / 200.00;
    int xs = ceil(x);
    // 定义线程数量为200个
    struct thread_data _tda[200];
    pthread_t tids[200];
    // 开始从i循环，次数为200次，每一次都会加xs个数，进下一批线程
    int _sta = s;
    int now = 0;
    for(int i = 0;i< 200;i++){
        // 这里应该判断，是否分完当前的端口
        if(now > e - s){
            break;
        }
        // 分配线程参数
        _tda[i].ip = ip;
        _tda[i].t = t;
        _tda[i].y = y;
       now = foreach(_sta,&_tda[i].ports,xs,now);
        _sta += xs;
        pthread_create(&tids[i], NULL , start,(void *)&_tda[i]);
    }
    // 线程结束后直接退出程序
    pthread_exit(NULL);
}




