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
    struct in_addr* Ip_Addr = (struct in_addr*)calloc(1, sizeof(struct in_addr));
    Ip_Addr->s_addr = __Addr;

    return Ip_Addr;
}

void Mysql_Error_Handle(MYSQL* pConn)
{
    perror(mysql_error(pConn));
    mysql_close(pConn);
    exit(1);
}

int main(void)
{
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL)
    {
        perror("mysql conn");
        exit(1);
    }

    char HostName[20] = "heimdall.iptime.org";
    char UserName[20] = "client";
    char a1[30] = "10dktmskf!)";
    char DB_Name[20] = "redproject";
    unsigned int Port = 13306;
    if (!mysql_real_connect(conn, HostName, UserName, a1, DB_Name, Port, NULL, 0))
    {
        perror("mysql_real_connect");
        exit(1);
    }

    char Table_Col[100] = "time, no, log_area, log_name, floor";
    char Value[100] = { 0 };
    sprintf(Value, "\"%s\", %d, \"%s\", \"%s\", %d", "20191024035820", 2, "Hello", "Good", 3);

    char Query[200] = { 0 };
    sprintf(Query, "INSERT INTO %s (%s) VALUES (%s)", "log_data", Table_Col, Value);

    sprintf(Query, "SELECT * FROM log_data");

    printf("%u\n", mysql_field_count(conn));

    // 쿼리를 실행하고
    if (mysql_query(conn, Query))
    {
        // Error Handle
        Mysql_Error_Handle(conn);
    }

    // 결과를 불러온다.
    MYSQL_RES* Result = mysql_store_result(conn);
    unsigned int row_num = 0;
    unsigned int field_num = 0;
    if (Result)
    {
        // TODO : 결과가 있었다면 row를 하나씩 불러서 그 값을 출력 후 Res를 해제한다.
        
        // Result 구조체에서 필드의 길이를 불러온다.
        field_num = mysql_num_fields(Result);
        row_num = 

        mysql_free_result(Result);
    }
    else    // 결과가 없었다면..
    {
        field_num = mysql_field_count(conn);
        if (field_num)  // 처리해야할 필드가 있는데도?
        {
            // 에러핸들 함수로 넘김
            Mysql_Error_Handle(conn);
        }
        else
        {
            row_num = (unsigned int)mysql_affected_rows(conn);
            printf("%affected row : ld\n", row_num);
        }
    }
    

    mysql_close(conn);

    return 0;
}