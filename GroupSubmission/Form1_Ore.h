#pragma once


namespace SlitWidthProject {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Form1_Ore : public System::Windows::Forms::Form
	{
	public:
		Form1_Ore(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1_Ore()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ timer1;

	private:
		double slitWidth = 20.0;
		double wavelength = 50.0;
		double wavePhase = 0.0;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();

			this->pictureBox1->Location = System::Drawing::Point(44, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(797, 227);
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1_Ore::pictureBox1_Paint);

			this->numericUpDown1->Location = System::Drawing::Point(54, 294);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array<System::Int32>(4) { 60, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array<System::Int32>(4) { 0, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 22);
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array<System::Int32>(4) { 20, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1_Ore::numericUpDown1_ValueChanged);

			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(51, 275);
			this->label1->Name = L"label1";
			this->label1->Text = L"Slit Width: 20";

			this->timer1->Enabled = true;
			this->timer1->Interval = 50;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1_Ore::timer1_Tick);

			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(876, 354);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1_Ore";
			this->Text = L"Slit Width Diffraction";

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

#pragma endregion

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::Black);

		int width = pictureBox1->Width;
		int height = pictureBox1->Height;
		int centreY = height / 2;
		int barrierX = 200;
		int screenX = width - 100;
		int slitPixelHeight = (int)slitWidth;

		Pen^ wavePen = gcnew Pen(Color::DodgerBlue, 1);
		Pen^ barrierPen = gcnew Pen(Color::White, 5);
		Pen^ screenPen = gcnew Pen(Color::Gray, 2);

		for (int x = 20 + (int)wavePhase % 30; x < barrierX; x += 30)
		{
			g->DrawLine(wavePen, x, 20, x, height - 20);
		}

		g->DrawLine(barrierPen, barrierX, 0, barrierX, centreY - slitPixelHeight / 2);
		g->DrawLine(barrierPen, barrierX, centreY + slitPixelHeight / 2, barrierX, height);

		if (slitWidth > 2)
		{
			float spreadAngle = 160.0f - (float)slitWidth;

			if (spreadAngle < 25.0f)
			{
				spreadAngle = 25.0f;
			}

			float startAngle = -spreadAngle / 2.0f;

			for (int radius = 20 + (int)wavePhase % 30; radius < width; radius += 30)
			{
				g->DrawArc(
					wavePen,
					(float)(barrierX - radius),
					(float)(centreY - radius),
					(float)(radius * 2),
					(float)(radius * 2),
					startAngle,
					spreadAngle
				);
			}

			g->DrawLine(screenPen, screenX, 0, screenX, height);

		}

		delete wavePen;
		delete barrierPen;
		delete screenPen;
	}

	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		slitWidth = (double)numericUpDown1->Value;
		label1->Text = "Slit Width: " + slitWidth.ToString();
		pictureBox1->Invalidate();
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		wavePhase += 5.0;
		pictureBox1->Invalidate();
	}
	};
}

