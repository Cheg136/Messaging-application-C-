#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serverAddr.sin_port = htons(8000); 

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    while (true) {
        char sendMsg[1024];
        std::cout << "Client: ";
        std::cin.getline(sendMsg, sizeof(sendMsg));
        send(clientSocket, sendMsg, strlen(sendMsg) + 1, 0);

        char receivedMsg[1024];
        recv(clientSocket, receivedMsg, sizeof(receivedMsg), 0);
        std::cout << "Server: " << receivedMsg << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
