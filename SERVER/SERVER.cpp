﻿#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
using namespace std;
#pragma warning(disable: 4996);
SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index) {
	int choice;
	while (true) {

		recv(Connections[index], (char*)&choice, sizeof(int), NULL);
		char terms[4][100] = { "Book is a paper thing", "Tree is a plant", "Laptop is a device", "Apple is a fruit" };
		send(Connections[index], terms[choice], sizeof(terms[choice]), NULL);

	}
}
int main(int argc, char* argv[]) {

	cout << "Vadim Laboda 30.04.2020 0:35\n";

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;

	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			cout << "Error: failed connect to server.\n";
		}
		else {
			cout << "Client Connected!\n";
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}
