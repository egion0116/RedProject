#include "stdfx.h"

struct in_addr* NameToIp(const char* HostName)
{
    // gethostbyname 함수로 호스트 엔트리를 검색한다.
    struct hostent* Target = gethostbyname(HostName);
    if (Target == NULL)
    {
        printf("There is no name \"%s\"\n", HostName);
        return NULL;
    }

    // 실제 비트는 빅엔디안 방식으로 한 바이트당 한 자리수씩 들어가 있으므로 in_addr_t형식으로 바꿀경우 손실되지않고 그대로 들어간다.
    in_addr_t __Addr = *(in_addr_t*)Target->h_addr_list[0];

    // 읽는 방식이 항상 바뀔 수 있으므로..
    struct in_addr* Ip_Addr = (struct in_addr*)calloc(sizeof(struct in_addr), 1);
    Ip_Addr->s_addr = __Addr;

    return Ip_Addr;
}

int main(void)
{
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL)
    {
        perror("mysql conn");
        exit(1);
    }

    char HostName[20] = "MyHostServer";
    char UserName[20] = "client1";
    char a1[30] = "Night!7724Death";
    char DB_Name[20] = "";
    unsigned int Port = 3306;
    if (mysql_real_connect(conn, HostName, UserName, a1, DB_Name, Port, NULL, 0) == 0);
    {
        perror("mysql_real_connect");
        exit(1);
    }



    return 0;
}