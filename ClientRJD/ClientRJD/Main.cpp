#include "ClientForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace ClientRJD;

[STAThreadAttribute]
int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	ClientForm form;
	Application::Run(% form);
}

