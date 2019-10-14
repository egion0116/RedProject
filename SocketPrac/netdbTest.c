#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct hostent* hent = NULL;

    while ((hent = gethostent()) != NULL)
    {
        printf("%s:\t", hent->h_name);
        for (int i = 0; hent->h_addr_list[i] != NULL; i++)
            printf("%s\t", inet_ntoa(*(struct in_addr*)hent->h_addr_list[i]));
        putchar('\n');
    }

    return 0;
}