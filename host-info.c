/*
 * File Name: host-info.c
 * Description: Shows host information - the IP address and Hostname
 * Author: Suyash Singh Bitti
 * 
 * Note:
 * gethostbyname() is DEPRECATED and doesn't work well with IPv6, you should be
 * using getaddrinfo()
 */

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define HOST_NAME_BUFF_LEN 255

int main(int argc, char *argv[])
{
    char hostNameBuff[HOST_NAME_BUFF_LEN];
    struct hostent *ci; /* Client Info */
    struct in_addr **addr_list;
    int i;

    if(argc == 2){
        /* hostname passed as command line arg */
        if((ci = gethostbyname(argv[1])) == NULL) {
            herror("gethostbyname");
            return 2;
        }
    } else {
        if(gethostname(hostNameBuff, sizeof hostNameBuff) == -1) {
            perror("gethostname");
            return 1;
        }

        if((ci = gethostbyname(hostNameBuff)) == NULL) {
            herror("gethostbyname");
            return 2;
        }
    }

    printf("Hostname: %s\n", ci->h_name);
    addr_list = (struct in_addr **)ci->h_addr_list;

    printf("IP Address: ");
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");

    return 0;
}