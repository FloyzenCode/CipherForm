#include "MyForm.h"
#include <tchar.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);

	CipherForm::MyForm form;
	Application::Run(% form);
}