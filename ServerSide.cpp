#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8000);
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    std::cout << "Server listening on port 8000..." << std::endl;

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    while (clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize)) {
        char receivedMsg[1024];
        recv(clientSocket, receivedMsg, sizeof(receivedMsg), 0);
        std::cout << "Client: " << receivedMsg << std::endl;

        char sendMsg[1024];
        std::cout << "Server: ";
        std::cin.getline(sendMsg, sizeof(sendMsg));
        send(clientSocket, sendMsg, strlen(sendMsg) + 1, 0);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
