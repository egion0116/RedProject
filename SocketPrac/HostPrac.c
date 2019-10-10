#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    // 서버 리슨 큐 길이
    const int Server_Listen_Length = 10;

    int Server_Soc = socket(AF_INET, SOCK_STREAM, 0);
    if (Server_Soc == -1)
    {
        perror("socket");
        exit(1);
    }

    // 서버의 주소를 담을 구조체
    struct sockaddr_in Server_Addr = { 0 };
    Server_Addr.sin_family = AF_INET;
    Server_Addr.sin_port = htons(9000);
    Server_Addr.sin_addr.s_addr = inet_addr("192.168.149.129");

    // 만든 빈 소켓을 운영체제와 바인드
    if (bind(Server_Soc, (struct sockaddr*)&Server_Addr, sizeof(Server_Addr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // listen queue 대기열을 만들고, connection-mode로 소켓을 만들어준다.
    if (listen(Server_Soc, Server_Listen_Length) == -1)
    {
        perror("listen");
        exit(1);
    }

    // 새 변수들을 선택한다.
    int Accepted_Soc = 0;
    struct sockaddr_in Accepted_Addr = { 0 };
    socklen_t Accepted_Addr_Len = 0;

    puts("Wait..");

    // accept로 listen queue에 있는 연결 요청을 추출해서 새 소켓을 생성한다.
    Accepted_Soc = accept(Server_Soc, (struct sockaddr*)&Accepted_Addr, &Accepted_Addr_Len);
    if (Accepted_Soc == -1)
    {
        perror("accept");
        exit(1);
    }

    // 전송받은 정보를 받을 버퍼와 길이
    size_t len = 80;
    char* Buff = (char*)calloc(sizeof(char), len);

    if (recv(Accepted_Soc, Buff, len, 0) == -1)
    {
        perror("recv");
        exit(1);
    }

    printf("받은 정보 : %s\n", Buff);

    free(Buff);
    shutdown(Server_Soc, SHUT_RDWR);
    shutdown(Accepted_Soc, SHUT_RDWR);

    return 0;
}