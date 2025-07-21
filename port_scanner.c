#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void scan_ports(const char *ip, int start_port, int end_port) {
    struct sockaddr_in target;
    int sock;
    printf("\nScanning IP: %s\n", ip);

    for (int port = start_port; port <= end_port; port++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(1);
        }

        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(ip);

        if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("Port %d is OPEN\n", port);
        }
        close(sock);
    }
}

int main() {
    char ip[20];
    int start_port, end_port;

    printf("Enter IP address: ");
    scanf("%s", ip);
    printf("Enter start port: ");
    scanf("%d", &start_port);
    printf("Enter end port: ");
    scanf("%d", &end_port);

    scan_ports(ip, start_port, end_port);
    return 0;
}
