#include <netdb.h> 
#include <stdio.h> 
int main(void) 
{ 
    struct servent *port; 
    int n; setservent(0); // 포트 정보 데이터베이스에서 현재 읽기 위치를 시작으로 이동시킴. 
    // 처음 5개의 포트 정보를 차례로 읽어서 출력한다. 
    for(n=0; n < 5; n++) 
    { 
        port = getservent(); 
        printf("Name=%s, Port=%d, Proto=%s\n", port->s_name, port->s_port, port->s_proto); 
    } 
    // 포트 정보 데이터베이스를 닫는다. 
    endservent(); 
    return 0; 
}