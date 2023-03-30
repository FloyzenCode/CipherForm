#pragma once

namespace CipherForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Security::Cryptography;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		
		array<unsigned char>^ AES_Encrypt(array<unsigned char>^ bytesToBeEncrypted, array<unsigned char>^ passwordBytes) {
			array<unsigned char>^ encryptedBytes = nullptr;

			// Set your salt here, change it to meet your flavor:
			// The salt bytes must be at least 8 bytes.
			array<unsigned char>^ saltBytes = gcnew array<unsigned char>(8) { 1, 2, 3, 4, 5, 6, 7, 8 };

			MemoryStream^ ms = gcnew MemoryStream();
			RijndaelManaged^ AES = gcnew RijndaelManaged();
			//auto cs = gcnew CryptoStream(ms, AES->CreateEncryptor(), CryptoStreamMode::Write);

			try {
				try {
					AES->KeySize = 256;
					AES->BlockSize = 128;
					AES->Mode = CipherMode::CBC;
					AES->Padding = System::Security::Cryptography::PaddingMode::Zeros;

					auto key = gcnew Rfc2898DeriveBytes(passwordBytes, saltBytes, 1000);
					AES->Key = key->GetBytes(AES->KeySize / 8);
					AES->IV = key->GetBytes(AES->BlockSize / 8);
					auto cs = gcnew CryptoStream(ms, AES->CreateEncryptor(), CryptoStreamMode::Write);

					try {
						cs->Write(bytesToBeEncrypted, 0, bytesToBeEncrypted->Length);
						cs->Close();
					}
					finally {
						if (cs != nullptr) delete cs;
					}

					encryptedBytes = ms->ToArray();
				}
				finally {
					if (AES != nullptr) delete AES;
				}
			}
			finally {
				if (ms != nullptr) delete ms;
			}

			return encryptedBytes;
		}

		array<unsigned char>^ AES_Decrypt(array<unsigned char>^ bytesToBeDecrypted, array<unsigned char>^ passwordBytes) {
			array<unsigned char>^ decryptedBytes = nullptr;

			// Set your salt here, change it to meet your flavor:
			// The salt bytes must be at least 8 bytes.
			array<unsigned char>^ saltBytes = gcnew array<unsigned char>(8) { 1, 2, 3, 4, 5, 6, 7, 8 };

			MemoryStream^ ms = gcnew MemoryStream();
			RijndaelManaged^ AES = gcnew RijndaelManaged();
			

			try {
				try {
					AES->KeySize = 256;
					AES->BlockSize = 128;
					AES->Mode = CipherMode::CBC;
					AES->Padding = System::Security::Cryptography::PaddingMode::Zeros;

					auto key = gcnew Rfc2898DeriveBytes(passwordBytes, saltBytes, 1000);
					AES->Key = key->GetBytes(AES->KeySize / 8);
					AES->IV = key->GetBytes(AES->BlockSize / 8);
					auto cs = gcnew CryptoStream(ms, AES->CreateDecryptor(), CryptoStreamMode::Write);

					try {
						cs->Write(bytesToBeDecrypted, 0, bytesToBeDecrypted->Length);
						cs->Close();
					}
					finally {
						if (cs != nullptr) delete cs;
					}

					decryptedBytes = ms->ToArray();
				}
				finally {
					if (AES != nullptr) delete AES;
				}
			}
			finally {
				if (ms != nullptr) delete ms;
			}

			return decryptedBytes;
		}

		//Encrypt String
		System::String^ EncryptText(System::String^ input, System::String^ password) {
			// Get the bytes of the string
			array<unsigned char>^ bytesToBeEncrypted = System::Text::Encoding::UTF8->GetBytes(input);
			array<unsigned char>^ passwordBytes = System::Text::Encoding::UTF8->GetBytes(password);

			// Hash the password with SHA256
			passwordBytes = SHA256::Create()->ComputeHash(passwordBytes);

			array<unsigned char>^ bytesEncrypted = AES_Encrypt(bytesToBeEncrypted, passwordBytes);

			System::String^ result = Convert::ToBase64String(bytesEncrypted);

			return result;
		}

		System::String^ DecryptText(System::String^ input, System::String^ password) {
			// Get the bytes of the string
			array<unsigned char>^ bytesToBeDecrypted = Convert::FromBase64String(input);
			array<unsigned char>^ passwordBytes = System::Text::Encoding::UTF8->GetBytes(password);
			passwordBytes = SHA256::Create()->ComputeHash(passwordBytes);

			array<unsigned char>^ bytesDecrypted = AES_Decrypt(bytesToBeDecrypted, passwordBytes);

			System::String^ result = System::Text::Encoding::UTF8->GetString(bytesDecrypted);

			return result;
		}

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
private: System::Windows::Forms::TextBox^ textBox3;
private: System::Windows::Forms::Label^ label4;







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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(64, 174);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(162, 20);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Location = System::Drawing::Point(473, 174);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(162, 20);
			this->textBox2->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label1.Image")));
			this->label1->Location = System::Drawing::Point(303, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 30);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Rijndael";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Book Antiqua", 8.25F, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(470, 155);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(130, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Зашифрованый текст:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Book Antiqua", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(61, 155);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Текст:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(81, 210);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(128, 39);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Зашифровать";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(490, 210);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(128, 39);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Расшифровать";
			this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox3
			// 
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox3->Location = System::Drawing::Point(308, 104);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Book Antiqua", 8.25F, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(305, 85);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 16);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Ключ:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(734, 489);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Advanced Encryption Standard";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ text1 = textBox1->Text;
			if (textBox3->Text == "") {
				textBox3->AppendText(System::Convert::ToString(Random().Next().ToString()));
			}

			if (text1 != "") {
				 System::String^ password = textBox3->Text;
				System::String^ text2 = EncryptText(text1, password);

				textBox2->Text = text2;
			}
		}

		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ text2 = textBox2->Text;
			if (textBox3->Text == "") {
				textBox3->AppendText(System::Convert::ToString(Random().Next().ToString()));
			}
			if (text2 != "") {
				System::String^ password = textBox3->Text;
				System::String^ text3 = DecryptText(text2, password);
				
				textBox1->Text = text3;
			}
		}
};
}