#include "ClientForm.h"

void ClientRJD::ClientForm::SetPrompt(String^ str)
{
	ConnectionPromptText->Text = str;
}

void ClientRJD::ClientForm::InitWSA()
{
	WSAData wsaData;
	WORD DLLVersion MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		SetPrompt(gcnew String("Missing WSA library."));
	}
}

void ClientRJD::ClientForm::ConnectToServer(String^ address)
{
	closesocket(Connection);

	SOCKADDR_IN addr; 

	marshal_context^ marshal = gcnew marshal_context();
	const char* strAddress = marshal->marshal_as<const char*>(address);

	int sizeAddr = sizeof(addr);

	const wchar_t* wstrAddress = marshal->marshal_as<const wchar_t*>(address);

	INT adr = WSAStringToAddress((LPTSTR)wstrAddress, AF_INET, NULL, (LPSOCKADDR)&addr, &sizeAddr);
	if (adr != 0) {
		SetPrompt(gcnew String("No valid address."));
		return;
	}

	addr.sin_addr.s_addr = inet_addr(strAddress);
	addr.sin_port = htons(8001);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	
	//блокирование сокета
	unsigned long block = 1;
	ioctlsocket((unsigned int)Connection, FIONBIO, &block);

	connect(Connection, (SOCKADDR*)&addr, sizeof(addr));
		
	//установка таймаута
	timeval time_out;
	time_out.tv_sec = 0;
	time_out.tv_usec = 1000000;

	fd_set setW, setE;

	//проверка подключения
	FD_ZERO(&setW);
	FD_SET(Connection, &setW);
	FD_ZERO(&setE);
	FD_SET(Connection, &setE);
	select(0, NULL, &setW, &setE, &time_out);

	if (FD_ISSET(Connection, &setW)) {
		SetPrompt(gcnew String("Success connection."));

		//разблокировка сокета
		unsigned long block = 0;
		ioctlsocket((unsigned int)Connection, FIONBIO, &block);
	}
	else {
		SetPrompt(gcnew String("No connection."));

		closesocket(Connection);
	}
}

void ClientRJD::ClientForm::SendMessage(String^ path, String^ data)
{
	String^ msg = path + "_|*" + data;
	string msgChar = marshal_as<string>(msg);

	//отправка размера сообщения
	int size = msgChar.size();
	send(Connection, (char*)&size, sizeof(int), NULL);

	//отправка сообщения
	send(Connection, msgChar.c_str(), size, NULL);
	
	//получение ответа от сервера
	char msgAnswer[256];
	if (recv(Connection, msgAnswer, sizeof(msgAnswer), NULL) <= 0) {
		SetPrompt(gcnew String("Connection lost."));
	}
	else {
		SetPrompt(gcnew String(msgAnswer));
	}
}
