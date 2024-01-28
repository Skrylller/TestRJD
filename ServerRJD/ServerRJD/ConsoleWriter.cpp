#include "pch.h"
#include "ConsoleWriter.h"   


void ConsoleWriter::Message(string str)
{
	cout << str << endl;
}

void ConsoleWriter::ErrorMessage(string str)
{
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);
	cout << "Error: " << std::ctime(&end_time) << str << endl;
}
