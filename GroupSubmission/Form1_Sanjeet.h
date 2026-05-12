#pragma once

#include "DoubleSlitPropagation.h"


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1_Sanjeet
	/// </summary>
	public ref class Form1_Sanjeet : public System::Windows::Forms::Form
	{
	public:
		Form1_Sanjeet(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1_Sanjeet()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


	private:
		Bitmap^ cachedScreen = nullptr;
		double cachedWavelength1 = -1, cachedSlitSeparation = -1, cachedSlitWidth = -1;
		int cachedNumSlits = -1;

		double wavelength1;
		double slitSeparation;
		double slitWidth;
		int numSlits;

		double phase1 = 0.0;
		double direction = 1.0; // positive for copropagating
		double amplitude1 = 5.0;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown3;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Timer^ timer1;


#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(192)));
			   this->pictureBox1->Location = System::Drawing::Point(12, 12);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(1304, 568);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1_Sanjeet::pictureBox1_Paint);
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(696, 586);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(108, 34);
			   this->button1->TabIndex = 1;
			   this->button1->Text = L"Start/Stop";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Form1_Sanjeet::button1_Click);
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Location = System::Drawing::Point(609, 594);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(22, 21);
			   this->checkBox1->TabIndex = 2;
			   this->checkBox1->UseVisualStyleBackColor = true;
			   this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::checkBox1_CheckedChanged);
			   // 
			   // numericUpDown1
			   // 
			   this->numericUpDown1->Location = System::Drawing::Point(12, 594);
			   this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			   this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			   this->numericUpDown1->Name = L"numericUpDown1";
			   this->numericUpDown1->Size = System::Drawing::Size(120, 26);
			   this->numericUpDown1->TabIndex = 3;
			   this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			   this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::numericUpDown1_ValueChanged);
			   // 
			   // numericUpDown2
			   // 
			   this->numericUpDown2->DecimalPlaces = 1;
			   this->numericUpDown2->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			   this->numericUpDown2->Location = System::Drawing::Point(283, 594);
			   this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			   this->numericUpDown2->Name = L"numericUpDown2";
			   this->numericUpDown2->Size = System::Drawing::Size(120, 26);
			   this->numericUpDown2->TabIndex = 4;
			   this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 65536 });
			   this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::numericUpDown2_ValueChanged);
			   // 
			   // numericUpDown3
			   // 
			   this->numericUpDown3->Location = System::Drawing::Point(13, 643);
			   this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			   this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			   this->numericUpDown3->Name = L"numericUpDown3";
			   this->numericUpDown3->Size = System::Drawing::Size(120, 26);
			   this->numericUpDown3->TabIndex = 5;
			   this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			   this->numericUpDown3->ValueChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::numericUpDown3_ValueChanged);
			   // 
			   // numericUpDown4
			   // 
			   this->numericUpDown4->DecimalPlaces = 2;
			   this->numericUpDown4->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			   this->numericUpDown4->Location = System::Drawing::Point(283, 643);
			   this->numericUpDown4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			   this->numericUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 131072 });
			   this->numericUpDown4->Name = L"numericUpDown4";
			   this->numericUpDown4->Size = System::Drawing::Size(120, 26);
			   this->numericUpDown4->TabIndex = 6;
			   this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4000, 0, 0, 131072 });
			   this->numericUpDown4->ValueChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::numericUpDown4_ValueChanged);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(140, 600);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(102, 20);
			   this->label1->TabIndex = 7;
			   this->label1->Text = L"Wavelength1";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(409, 600);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(113, 20);
			   this->label2->TabIndex = 8;
			   this->label2->Text = L"Slit Separation";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(140, 649);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(89, 20);
			   this->label3->TabIndex = 9;
			   this->label3->Text = L"Amplitude1";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(409, 645);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(72, 20);
			   this->label4->TabIndex = 10;
			   this->label4->Text = L"Slit width";
			   // 
			   // timer1
			   // 
			   this->timer1->Interval = 20;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Form1_Sanjeet::timer1_Tick);
			   // 
			   // numericUpDown5
			   // 
			   this->numericUpDown5->Location = System::Drawing::Point(575, 643);
			   this->numericUpDown5->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			   this->numericUpDown5->Name = L"numericUpDown5";
			   this->numericUpDown5->Size = System::Drawing::Size(120, 26);
			   this->numericUpDown5->TabIndex = 11;
			   this->numericUpDown5->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			   this->numericUpDown5->ValueChanged += gcnew System::EventHandler(this, &Form1_Sanjeet::numericUpDown5_ValueChanged);
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(710, 649);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(94, 20);
			   this->label5->TabIndex = 12;
			   this->label5->Text = L"Num of Silts";
			   // 
			   // Form1_Sanjeet
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1328, 722);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->numericUpDown5);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->numericUpDown4);
			   this->Controls->Add(this->numericUpDown3);
			   this->Controls->Add(this->numericUpDown2);
			   this->Controls->Add(this->numericUpDown1);
			   this->Controls->Add(this->checkBox1);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->pictureBox1);
			   this->Name = L"Form1_Sanjeet";
			   this->Text = L" ";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		double x0 = 0, y0 = -1, x1 = 8, y1 = 1, dx = 1, dy = 2;

		grid1(e->Graphics, x0, x1, dx, e->Graphics->ClipBounds.Width, y0, y1, dy, e->Graphics->ClipBounds.Height);

		int pictureBoxWidth = this->pictureBox1->Width;
		int pictureBoxHeight = this->pictureBox1->Height;

		wavelength1 = (double)this->numericUpDown1->Value;
		slitSeparation = (double)this->numericUpDown2->Value;
		slitWidth = (double)this->numericUpDown4->Value;
		numSlits = (double)this->numericUpDown5->Value;

		//drawFunction(e->Graphics, wavelength1, wavelength2, phase1, phase2, amplitude1, amplitude2);
		if (cachedScreen == nullptr || wavelength1 != cachedWavelength1 || slitSeparation != cachedSlitSeparation || slitWidth != cachedSlitWidth || numSlits != cachedNumSlits) {
			if (cachedScreen != nullptr) {
				delete cachedScreen;
			}
			cachedScreen = buildInterferenceScreen(e->Graphics, wavelength1, phase1, slitSeparation, slitWidth, numSlits);
			cachedWavelength1 = wavelength1;
			cachedSlitSeparation = slitSeparation;
			cachedSlitWidth = slitWidth;
			cachedNumSlits = numSlits;
		}

		int barrierX = (int)(e->Graphics->ClipBounds.Width * 0.25);
		int screenX = (int)(e->Graphics->ClipBounds.Width * 0.95);

		e->Graphics->SetClip(System::Drawing::Rectangle(0, 0, barrierX, pictureBoxHeight));
		drawWavefront(e->Graphics, wavelength1, phase1, amplitude1, direction);
		e->Graphics->ResetClip();

		e->Graphics->SetClip(System::Drawing::Rectangle(barrierX, 0, screenX - barrierX, pictureBoxHeight));
		drawSlitsWaveFronts(e->Graphics, wavelength1, phase1, amplitude1,
			slitSeparation, slitWidth, numSlits, pictureBoxWidth, pictureBoxHeight);
		e->Graphics->ResetClip();

		int stripWidthOfScreen = 25;
		int leftScreen = screenX - stripWidthOfScreen / 2;
		e->Graphics->DrawImage(cachedScreen, leftScreen, 0);

		Pen^ screenPen = gcnew Pen(Color::Gray, 2.0f);
		e->Graphics->DrawLine(screenPen, screenX, 0, screenX, pictureBoxHeight);
		delete screenPen;

	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		wavelength1 = (double)this->numericUpDown1->Value;
		this->pictureBox1->Invalidate();
	}
	private: System::Void numericUpDown2_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		slitSeparation = (double)this->numericUpDown2->Value;
		this->pictureBox1->Invalidate();
	}
	private: System::Void numericUpDown3_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		amplitude1 = (double)this->numericUpDown3->Value;
		this->pictureBox1->Invalidate();
	}
	private: System::Void numericUpDown4_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		slitWidth = (double)this->numericUpDown4->Value;
		this->pictureBox1->Invalidate();
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->checkBox1->Checked) {
			direction = -1.0;
		}
		else {
			direction = 1.0;
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->timer1->Enabled) {
			this->timer1->Enabled = false;
		}
		else {
			this->timer1->Enabled = true;
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		phase1 += (0.1 * direction);
		this->pictureBox1->Invalidate();
	}
	private: System::Void numericUpDown5_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		this->pictureBox1->Invalidate();
	}

	};
}



