#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

void SendData(const string& data) {
	setlocale(LC_ALL, "rus");
	WSADATA wsadata;
	SOCKET sock;
	struct sockaddr_in server;

	WSAStartup(MAKEWORD(2, 2), &wsadata);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cout << "Ошибка создания сокета : " << WSAGetLastError << endl;
		return;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		cout << "Ошибка подключения к серверу" << endl;
		return;
	}

	send(sock, data.c_str(), data.length(), 0);

	closesocket(sock);
	WSACleanup();
}

string GetUserActivity() {
	char username[256];
	DWORD username_len = sizeof(username);
	GetUserNameA(username, &username_len);
	return string(username);
}

int main() {
	string userActivity = GetUserActivity();
	SendData(userActivity);

	return 0;
}