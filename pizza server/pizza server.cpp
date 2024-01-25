#include <iostream>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <tchar.h>

int main(int argc, char* argv[]) {
	//step 1 : Set up the DLL

	SOCKET ServerSocket, AcceptSocket; //Define nome dos sockets
	int port = 55555;; //Define numero de porta
	WSADATA wsaData; //inicializa a DLL 
	int wsaerr; //variavel de erro
	WORD wVersionRequsted = MAKEWORD(2, 2); //coloca a versão pedida do WinSock = 2.2
	wsaerr = WSAStartup(wVersionRequsted, &wsaData);
	if (wsaerr != 0) {
		std::cout << "WinSock DLL Not Found!";
	}
	else {
		std::cout << "The WinSock DLL found!!!" << std::endl;
		std::cout << "The Status:" << wsaData.szSystemStatus << std::endl;

	}
	//Step 2: Setting up the socket
	ServerSocket = INVALID_SOCKET; //cria um novo socket
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); ////Define sockets e define conexão como TCP/IP
	if (ServerSocket == INVALID_SOCKET) {
		std::cout << "Error at socket():" << WSAGetLastError() << std::endl;
		WSACleanup();
	
	}
	else {
		std::cout << "socket() is OK!" << std::endl;
	}
	//Step 3:bind socket
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(ServerSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(ServerSocket);
		WSACleanup();
	}
	else {
		std::cout << "bind () is OK!" << std::endl;
	}
	//Step 4: Listen()
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		std::cout << "Listen():Error listening on socket" << WSAGetLastError() << std::endl;
	}

	else {
		std::cout << "listen() is OK, waiting for connections..." << std::endl;
	}

	//Step 5 Accept

	AcceptSocket = accept(ServerSocket, NULL, NULL);
	if (AcceptSocket == INVALID_SOCKET) {
		std::cout << "accept failed: " << WSAGetLastError;
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "Accepted Connection" << std::endl;
		system("pause");
		WSACleanup();
	}
	return 0;
}