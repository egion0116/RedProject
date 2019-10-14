#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main(void)
{
    MYSQL* mysql = (MYSQL*)malloc(sizeof(MYSQL));
    MYSQL* mysql2 = mysql_init(mysql);

    printf("%p\n", mysql);
    printf("%p\n", mysql2);

    return 0;
}