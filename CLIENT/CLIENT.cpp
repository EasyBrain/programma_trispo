#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <exception>
using namespace std;
#pragma warning(disable: 4996)

SOCKET Connection;
int client_choice;

void ClientHandler() {
	while (true) {
		char terms[100];
		recv(Connection, terms, sizeof(terms), NULL);
		cout << terms << endl;
	}
}

int main(int argc, char* argv[]) {

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
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	cout << "Connected!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	cout << "Enter the number of term:\n1 - Book\n2 - Tree\n3 - Laptop\n4 - Apple" << endl << endl;
	while (true) {

		cout << "Number: ";
		cin >> client_choice;
		while (client_choice <= 0 || client_choice > 4) {
			cout << "Incorrect number, try again\n";
			cout << "Number: ";
			cin >> client_choice;
		}

		client_choice--;
		send(Connection, (char*)&client_choice, sizeof(int), NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}
