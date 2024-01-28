#pragma once

#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<winsock2.h>
#include <msclr/marshal_cppstd.h>
#include <thread>

using namespace std;
using namespace msclr::interop;

namespace ClientRJD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ClientForm
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			InitializeComponent();
			InitWSA();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ClientForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ IPText;
	protected:

	protected:

	private: System::Windows::Forms::Button^ ConnectButton;
	protected:

	private: System::Windows::Forms::TextBox^ IPTextField;
	private: System::Windows::Forms::TextBox^ PathTextField;
	private: System::Windows::Forms::Label^ ConnectionPromptText;
	private: System::Windows::Forms::Label^ PathText;
	private: System::Windows::Forms::Label^ DataText;








	private: System::Windows::Forms::RichTextBox^ DataTextBox;
	private: System::Windows::Forms::Button^ CreateDataButton;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->IPText = (gcnew System::Windows::Forms::Label());
			this->ConnectButton = (gcnew System::Windows::Forms::Button());
			this->IPTextField = (gcnew System::Windows::Forms::TextBox());
			this->PathTextField = (gcnew System::Windows::Forms::TextBox());
			this->ConnectionPromptText = (gcnew System::Windows::Forms::Label());
			this->PathText = (gcnew System::Windows::Forms::Label());
			this->DataText = (gcnew System::Windows::Forms::Label());
			this->DataTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->CreateDataButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// IPText
			// 
			this->IPText->AutoSize = true;
			this->IPText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPText->Location = System::Drawing::Point(12, 9);
			this->IPText->Name = L"IPText";
			this->IPText->Size = System::Drawing::Size(239, 15);
			this->IPText->TabIndex = 0;
			this->IPText->Text = L"IP адрес сервера. (в формате 127.0.0.1)";
			// 
			// ConnectButton
			// 
			this->ConnectButton->Location = System::Drawing::Point(199, 25);
			this->ConnectButton->Name = L"ConnectButton";
			this->ConnectButton->Size = System::Drawing::Size(106, 23);
			this->ConnectButton->TabIndex = 1;
			this->ConnectButton->Text = L"Подключиться";
			this->ConnectButton->UseVisualStyleBackColor = true;
			this->ConnectButton->Click += gcnew System::EventHandler(this, &ClientForm::ConnectButton_Click);
			// 
			// IPTextField
			// 
			this->IPTextField->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPTextField->Location = System::Drawing::Point(15, 27);
			this->IPTextField->Name = L"IPTextField";
			this->IPTextField->Size = System::Drawing::Size(176, 21);
			this->IPTextField->TabIndex = 2;
			this->IPTextField->Leave += gcnew System::EventHandler(this, &ClientForm::IPTextField_Leave);
			// 
			// PathTextField
			// 
			this->PathTextField->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PathTextField->Location = System::Drawing::Point(105, 110);
			this->PathTextField->Name = L"PathTextField";
			this->PathTextField->Size = System::Drawing::Size(200, 21);
			this->PathTextField->TabIndex = 4;
			// 
			// ConnectionPromptText
			// 
			this->ConnectionPromptText->AutoSize = true;
			this->ConnectionPromptText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->ConnectionPromptText->Location = System::Drawing::Point(12, 51);
			this->ConnectionPromptText->Name = L"ConnectionPromptText";
			this->ConnectionPromptText->Size = System::Drawing::Size(112, 15);
			this->ConnectionPromptText->TabIndex = 3;
			this->ConnectionPromptText->Text = L"";
			// 
			// PathText
			// 
			this->PathText->AutoSize = true;
			this->PathText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PathText->Location = System::Drawing::Point(12, 113);
			this->PathText->Name = L"PathText";
			this->PathText->Size = System::Drawing::Size(87, 15);
			this->PathText->TabIndex = 5;
			this->PathText->Text = L"Путь к файлу:";
			// 
			// DataText
			// 
			this->DataText->AutoSize = true;
			this->DataText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DataText->Location = System::Drawing::Point(12, 140);
			this->DataText->Name = L"DataText";
			this->DataText->Size = System::Drawing::Size(98, 15);
			this->DataText->TabIndex = 6;
			this->DataText->Text = L"Данные файла:";
			// 
			// DataTextBox
			// 
			this->DataTextBox->Location = System::Drawing::Point(15, 158);
			this->DataTextBox->Name = L"DataTextBox";
			this->DataTextBox->Size = System::Drawing::Size(290, 91);
			this->DataTextBox->TabIndex = 7;
			this->DataTextBox->Text = L"";
			// 
			// CreateDataButton
			// 
			this->CreateDataButton->Location = System::Drawing::Point(199, 264);
			this->CreateDataButton->Name = L"CreateDataButton";
			this->CreateDataButton->Size = System::Drawing::Size(106, 23);
			this->CreateDataButton->TabIndex = 8;
			this->CreateDataButton->Text = L"Создать";
			this->CreateDataButton->UseVisualStyleBackColor = true;
			this->CreateDataButton->Click += gcnew System::EventHandler(this, &ClientForm::CreateDataButton_Click);
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 299);
			this->Controls->Add(this->CreateDataButton);
			this->Controls->Add(this->DataTextBox);
			this->Controls->Add(this->DataText);
			this->Controls->Add(this->PathText);
			this->Controls->Add(this->PathTextField);
			this->Controls->Add(this->ConnectionPromptText);
			this->Controls->Add(this->IPTextField);
			this->Controls->Add(this->ConnectButton);
			this->Controls->Add(this->IPText);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ClientForm";
			this->Text = L"ClientForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ConnectButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		ConnectToServer(IPTextField->Text);
	}

	private: System::Void IPTextField_Leave(System::Object^ sender, System::EventArgs^ e) 
	{

	}

	private: System::Void CreateDataButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SendMessage(PathTextField->Text, DataTextBox->Text);
	}

	private:
		SOCKET Connection;

		void InitWSA();

		void SetPrompt(String^ str);

		void ConnectToServer(String^ address);

		void SendMessage(String^ path, String^ data);

	};
}
