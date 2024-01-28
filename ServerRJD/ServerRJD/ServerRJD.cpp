#include "pch.h"

#pragma comment(lib, "ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#include<vector>
#include<sstream>
#include<thread>
#include"FileCreator.h"
#include"ConsoleWriter.h"


const string delimiter = "_|*";

std::vector<std::string> split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

void CommandObserver()
{
	while (true) {
		string com;
		cin >> com;

		if (com == "Exit") {
			exit(0);
		}
	}
}

int main(int argc, char* argv[]) {

	FileCreator fileCreator;

	//поток для ввода команд
	thread th(CommandObserver);
	th.detach();

	//создание сокета
	WSAData wsaData;
	WORD DLLVersion MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {

		ConsoleWriter::ErrorMessage("Missing WSA library");
		exit(1);
	}

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8001);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	int sizeAddr = sizeof(addr);

	//цикл переподключения клиента
	while (true) {

		ConsoleWriter::Message("Waiting for connection.");

		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeAddr);

		if (newConnection == 0) {
			ConsoleWriter::ErrorMessage("Client did not connect");
		}
		else {
			ConsoleWriter::Message("Client has connected");
		}

		bool isConnect = true;

		//цикл ожидания команды
		while (isConnect)
		{
			//получает размер данных
			int size;

			int temp = recv(newConnection, (char*)&size, sizeof(int), NULL);
			if (temp <= 0) {
				isConnect = false;
				break;
			}

			//получает данные
			char* msg = new char[size + 1];
			msg[size] = '\0';

			temp = recv(newConnection, msg, size, NULL);
			if (temp <= 0) {
				isConnect = false;
				break;
			}

			//работа с данными
			std::vector<string> data = split(msg, delimiter);

			string msgAnswer = "Success";

			if (data.size() > 2) {
				msgAnswer = "Wrong data format, extra delimeter. (_|*)";
				ConsoleWriter::ErrorMessage(msgAnswer);
			}
			else {
				if (fileCreator.CreateServerFile(data[0], data[1])) {
					msgAnswer = "File create.";
					ConsoleWriter::Message(msgAnswer);
				}
				else {
					msgAnswer = "File creation error.";
					ConsoleWriter::ErrorMessage(msgAnswer);
				}
			}

			//ответ клиенту
			temp = send(newConnection, msgAnswer.c_str(), 256, NULL);

			delete[] msg;
		}

		closesocket(newConnection);
		ConsoleWriter::ErrorMessage("Connection lost.");

	}

	system("pause");

	return 0;
}