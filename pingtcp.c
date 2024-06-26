/*
** pingtcp.c -- send TCP REQUEST to network hosts
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
 
void delay(int number_of_seconds){
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);

}

static bool keepRunning = true;

void intHandler(int) {
    keepRunning = false;
}

int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: showip hostname\n");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);


    for(p = res;p != NULL; p = p->ai_next) {
        while(keepRunning) {
            delay(500);
            void *addr;
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            // convert the IP to a string and print it:
            inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
            printf("  %s: %s\n", "IPv4", ipstr);

        }
    }


    freeaddrinfo(res); // free the linked list

    return 0;
}

