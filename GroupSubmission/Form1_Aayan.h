#pragma once
#include "WaveSuperPositionFunctions.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Form1_Aayan : public Form
	{
	public:
		Form1_Aayan(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1_Aayan()
		{
			if (components)
				delete components;
		}

	private:
		System::ComponentModel::IContainer^ components;

		// Physics variables
		double direction = 1.0;
		double amplitude1 = 5.0;
		double amplitude2 = 5.0;
		double frequency1 = 1.0;
		double frequency2 = 1.0;
		double time = 0.0;

		bool standingMode = false;
		bool showWave1 = true;
		bool showWave2 = true;

		// UI Controls
		PictureBox^ pictureBox1;
		Button^ button1;
		CheckBox^ checkBoxDirection;
		CheckBox^ checkBoxStanding;
		CheckBox^ checkBoxShow1;
		CheckBox^ checkBoxShow2;

		NumericUpDown^ numW1;
		NumericUpDown^ numW2;
		NumericUpDown^ numA1;
		NumericUpDown^ numA2;
		NumericUpDown^ numF1;
		NumericUpDown^ numF2;

		// Labels
		Label^ labelW1;
		Label^ labelW2;
		Label^ labelA1;
		Label^ labelA2;
		Label^ labelF1;
		Label^ labelF2;

		Timer^ timer1;

#pragma region Windows Form Designer code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();

			pictureBox1 = gcnew PictureBox();
			button1 = gcnew Button();

			checkBoxDirection = gcnew CheckBox();
			checkBoxStanding = gcnew CheckBox();
			checkBoxShow1 = gcnew CheckBox();
			checkBoxShow2 = gcnew CheckBox();

			numW1 = gcnew NumericUpDown();
			numW2 = gcnew NumericUpDown();
			numA1 = gcnew NumericUpDown();
			numA2 = gcnew NumericUpDown();
			numF1 = gcnew NumericUpDown();
			numF2 = gcnew NumericUpDown();

			labelW1 = gcnew Label();
			labelW2 = gcnew Label();
			labelA1 = gcnew Label();
			labelA2 = gcnew Label();
			labelF1 = gcnew Label();
			labelF2 = gcnew Label();

			timer1 = gcnew Timer(this->components);

			this->SuspendLayout();

			// PictureBox
			pictureBox1->Location = Point(10, 10);
			pictureBox1->Size = Drawing::Size(1200, 400);
			pictureBox1->Paint += gcnew PaintEventHandler(this, &Form1_Aayan::draw);

			// Button
			button1->Text = L"Start / Stop";
			button1->Location = Point(1000, 500);
			button1->Click += gcnew EventHandler(this, &Form1_Aayan::toggle);

			// Checkboxes
			checkBoxDirection->Text = L"Opposite Direction";
			checkBoxDirection->Location = Point(1000, 420);
			checkBoxDirection->CheckedChanged += gcnew EventHandler(this, &Form1_Aayan::directionChanged);

			checkBoxStanding->Text = L"Standing Wave";
			checkBoxStanding->Location = Point(1000, 450);
			checkBoxStanding->CheckedChanged += gcnew EventHandler(this, &Form1_Aayan::standingChanged);

			checkBoxShow1->Text = L"Show Wave 1";
			checkBoxShow1->Location = Point(1000, 480);
			checkBoxShow1->Checked = true;
			checkBoxShow1->CheckedChanged += gcnew EventHandler(this, &Form1_Aayan::show1Changed);

			checkBoxShow2->Text = L"Show Wave 2";
			checkBoxShow2->Location = Point(1000, 510);
			checkBoxShow2->Checked = true;
			checkBoxShow2->CheckedChanged += gcnew EventHandler(this, &Form1_Aayan::show2Changed);

			// Labels + Inputs
			int y = 420;

			labelW1->Text = L"Wavelength 1";
			labelW1->Location = Point(20, y);
			numW1->Location = Point(120, y);
			numW1->Value = 20;

			labelW2->Text = L"Wavelength 2";
			labelW2->Location = Point(20, y + 30);
			numW2->Location = Point(120, y + 30);
			numW2->Value = 20;

			labelA1->Text = L"Amplitude 1";
			labelA1->Location = Point(250, y);
			numA1->Location = Point(350, y);
			numA1->Value = 5;

			labelA2->Text = L"Amplitude 2";
			labelA2->Location = Point(250, y + 30);
			numA2->Location = Point(350, y + 30);
			numA2->Value = 5;

			labelF1->Text = L"Frequency 1";
			labelF1->Location = Point(500, y);
			numF1->Location = Point(600, y);
			numF1->DecimalPlaces = 1;
			numF1->Increment = System::Decimal(gcnew cli::array<int>{1, 0, 0, 65536});
			numF1->Value = 1;

			labelF2->Text = L"Frequency 2";
			labelF2->Location = Point(500, y + 30);
			numF2->Location = Point(600, y + 30);
			numF2->DecimalPlaces = 1;
			numF2->Increment = System::Decimal(gcnew cli::array<int>{1, 0, 0, 65536});
			numF2->Value = 1;

			// Timer
			timer1->Interval = 20;
			timer1->Tick += gcnew EventHandler(this, &Form1_Aayan::tick);

			// Add Controls
			this->Controls->Add(pictureBox1);
			this->Controls->Add(button1);

			this->Controls->Add(checkBoxDirection);
			this->Controls->Add(checkBoxStanding);
			this->Controls->Add(checkBoxShow1);
			this->Controls->Add(checkBoxShow2);

			this->Controls->Add(labelW1);
			this->Controls->Add(labelW2);
			this->Controls->Add(labelA1);
			this->Controls->Add(labelA2);
			this->Controls->Add(labelF1);
			this->Controls->Add(labelF2);

			this->Controls->Add(numW1);
			this->Controls->Add(numW2);
			this->Controls->Add(numA1);
			this->Controls->Add(numA2);
			this->Controls->Add(numF1);
			this->Controls->Add(numF2);

			this->ClientSize = Drawing::Size(1250, 580);
			this->Text = L"Wave Interference Demo";

			this->ResumeLayout(false);
		}
#pragma endregion

	private: void toggle(Object^, EventArgs^) {
		timer1->Enabled = !timer1->Enabled;
	}

	private: void tick(Object^, EventArgs^) {
		time += 0.05;
		pictureBox1->Invalidate();
	}

	private: void directionChanged(Object^, EventArgs^) {
		direction = checkBoxDirection->Checked ? -1.0 : 1.0;
	}

	private: void standingChanged(Object^, EventArgs^) {
		standingMode = checkBoxStanding->Checked;
	}

	private: void show1Changed(Object^, EventArgs^) {
		showWave1 = checkBoxShow1->Checked;
	}

	private: void show2Changed(Object^, EventArgs^) {
		showWave2 = checkBoxShow2->Checked;
	}

	private: void draw(Object^, PaintEventArgs^ e) {

		double w1 = (double)numW1->Value;
		double w2 = (double)numW2->Value;

		amplitude1 = (double)numA1->Value;
		amplitude2 = (double)numA2->Value;

		frequency1 = (double)numF1->Value;
		frequency2 = (double)numF2->Value;

		grid(e->Graphics, -4, 4, 1, e->ClipRectangle.Width, -2, 2, 1, e->ClipRectangle.Height);

		drawFunction(e->Graphics,
			w1, w2,
			frequency1, frequency2,
			time,
			amplitude1, amplitude2,
			direction,
			standingMode,
			showWave1,
			showWave2);
	}
	};
}

