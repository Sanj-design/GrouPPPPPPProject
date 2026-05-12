#pragma once

#include <cmath>
#include <iostream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


int x_Screen1(double x, double x0, double x1, double W);
int y_Screen1(double y, double y0, double y1, double H);
double x_World1(int px, double x0, double x1, double W);
double y_World1(int py, double y0, double y1, double H);
void grid1(Graphics^ g, double x0, double  x1, double dx, int W, double y0, double y1, double dy, int H);
void drawFunction1(Graphics^ g, double wavelength1, double wavelength2, double phase1, double phase2, double amplitude1, double amplitude2);



int x_Screen1(double x, double x0, double x1, double W) {
	//transforms x from [x0,x1] to image coordinates [0,W] 
	return static_cast<int> ((x - x0) * W / (x1 - x0));
}
int y_Screen1(double y, double y0, double y1, double H) {
	return  ((y - y1) * H / (y0 - y1));
}
double x_World1(int px, double x0, double x1, double W) {
	return x0 + px * (x1 - x0) / W;
}
double y_World1(int py, double y0, double y1, double H) {
	return y1 - py * (y0 - y1) / H;
}

void drawFunction1(Graphics^ g, double wavelength1, double wavelength2, double phase1, double phase2, double amplitude1, double amplitude2) {
	double x0 = -1000.0, x1 = 1000.0, y0 = -2.2, y1 = 2.2;
	RectangleF r = g->ClipBounds;
	Pen^ pen1 = gcnew Pen(Color::Red, 1);
	Pen^ pen2 = gcnew Pen(Color::Blue, 1);
	Pen^ penSum = gcnew Pen(Color::Black, 1);
	int py1_alt = 0;
	int py2_alt = 0;
	int pySum_alt = 0;
	for (int px = 0; px < r.Width; px++) {
		//image coords px,py world coordinates x,y
		//transfor px to world coordinates
		double x = x_World1(px, x0, x1, r.Width);
		double y1st = std::sin((x / wavelength1) + phase1);
		double y2nd = std::sin((x / wavelength2) + phase2);
		double ySummed = y1st + y2nd;
		int py1 = y_Screen1(y1st, (y0 * (10 / amplitude1)), (y1 * (10 / amplitude1)), r.Height);
		int py2 = y_Screen1(y2nd, (y0 * (10 / amplitude2)), (y1 * (10 / amplitude2)), r.Height);
		int pySum = y_Screen1(ySummed, y0 * (20 / (amplitude1 + amplitude2)), y1 * (20 / (amplitude1 + amplitude2)), r.Height);
		if (px > 0) {
			g->DrawLine(pen1, px - 1, py1_alt, px, py1);
			g->DrawLine(pen2, px - 1, py2_alt, px, py2);
			g->DrawLine(penSum, px - 1, pySum_alt, px, pySum);
		}
		py1_alt = py1;
		py2_alt = py2;
		pySum_alt = pySum;
	}
	delete pen1, pen2, penSum;
}

void grid1(Graphics^ g, double x0, double  x1, double dx, int W, double y0, double y1, double dy, int H) {

	int xt = x_Screen1(0, x0, x1, W);
	Pen^ grayPen = gcnew Pen(Color::Gray, 1);
	Pen^ blackPen = gcnew Pen(Color::Blue, 2);

	SolidBrush brush(Color::Red);
	System::Drawing::Font^ font = gcnew  System::Drawing::Font("Arial", 8);
	int y = 0, i = 0;
	while (y < H) {// Draws gray lines parallel to axis. 
		g->DrawLine(grayPen, Point(0, y), Point(W, y));
		if (std::fabs(y1 - i * dy) > 0.001)	g->DrawString((y1 - i * dy).ToString(), font, % brush, Point(xt, y));
		i++;
		y = y_Screen1(y1 - i * dy, y0, y1, H);
	}
	int yt = y_Screen1(0, y0, y1, H);
	int x = W, j = 0;
	while (x > 0) {// Draws gray lines parallel to axis. 
		g->DrawLine(grayPen, Point(x, 0), Point(x, H));
		if (std::fabs(x1 + j * dx) >= 0.000)	g->DrawString((x1 + j * dx).ToString(), font, % brush, Point(x, yt));
		j--;
		x = x_Screen1(x1 + j * dx, x0, x1, W);
	}

	bool xAxisVisible = false;
	if (0 <= xt && xt <= W) xAxisVisible = true;
	else xt = 0;
	if (xAxisVisible)
	{// trace x axis black.
		Pen^ blackPen = gcnew Pen(Color::Black, 1);
		g->DrawLine(blackPen, Point(xt, H), Point(xt, 0));
	}

	bool yAxisVisible = false;
	if (0 <= yt && yt <= H) yAxisVisible = true;
	else yt = 0;
	if (yAxisVisible)
	{// trace x axis black.
		Pen^ blackPen = gcnew Pen(Color::Black, 1);
		g->DrawLine(blackPen, Point(W, yt), Point(0, yt));
	}
	g->DrawRectangle(blackPen, 0, 0, W, H);// g->ClipBounds.Width, g->ClipBounds.Height);
	delete blackPen, grayPen;

}
void drawWavefront(Graphics^ g, double wavelength1, double phase1, double amplitude1, double direction) {
	int width = (int)g->ClipBounds.Width;
	int height = (int)g->ClipBounds.Height;

	double centerY = height / 2.0;
	//double xScale = width / 8.0;
	double yScale = height / 2.0;

	double pixelsPerWave1 = wavelength1;


	Pen^ bluePen = gcnew Pen(Color::Blue, 1);
	;

	double phaseOffset1 = phase1 * pixelsPerWave1 / (2.0 * Math::PI) * direction;
	double initial_x = fmod(phaseOffset1, pixelsPerWave1);
	if (initial_x < 0) initial_x += pixelsPerWave1;
	for (double x = initial_x; x < width; x += pixelsPerWave1) {
		double lineHalfHeight = amplitude1 * yScale / 10.0;
		int xPixel = (int)x;
		int yTop = (int)(centerY - lineHalfHeight);
		int yBottom = (int)(centerY + lineHalfHeight);
		g->DrawLine(bluePen, xPixel, yTop, xPixel, yBottom);

	}
	delete bluePen;

}

void drawSlitsWaveFronts(Graphics^ g, double wavelength1, double phase1, double amplitude1, double slitSeparation, double slitWidth, int numSlits, int width, int height) {

	double centerY = height / 2.0;
	double yScale = height / 2.0;
	//double xScale = width / 8.0;

	double pixelsPerWave = wavelength1;
	double barrierX = width / 4.0;
	double slitHalfWidth = (slitWidth / 2.0);

	array <double>^ slitY = gcnew array<double>(numSlits);
	if (numSlits == 1) {
		slitY[0] = centerY;
	}
	else {
		double totalSpan = (numSlits - 1) * (slitSeparation * yScale);
		for (int i = 0; i < numSlits; i++) {
			slitY[i] = centerY - totalSpan / 2.0 + i * (slitSeparation * yScale);
		}
	}

	std::cout << barrierX << "\n";
	Pen^ barrierPen = gcnew Pen(Color::Red, 3.0f);
	//g->DrawLine(barrierPen, ,40 , , 80);

	double previousBottom = 0;
	for (int i = 0; i < numSlits; i++) {
		double slitTop = slitY[i] - slitHalfWidth;
		double slitBottom = slitY[i] + slitHalfWidth;
		g->DrawLine(barrierPen, (int)barrierX, (int)previousBottom, (int)barrierX, (int)slitTop);
		previousBottom = slitBottom;
	}
	if (previousBottom < height) {
		g->DrawLine(barrierPen, (int)barrierX, (int)previousBottom, (int)barrierX, height);
	}
	delete barrierPen;

	double phaseRadius = fmod(phase1 * pixelsPerWave / (2.0 * Math::PI), pixelsPerWave);
	if (phaseRadius < 0)phaseRadius += pixelsPerWave;

	int maxRadius = (int)Math::Sqrt((double)(width * width + height * height));
	array<Color>^ colours = gcnew array<Color>(4) {
		Color::Blue, Color::Red, Color::Green, Color::Orange
	};

	for (int i = 0; i < numSlits; i++) {
		Color c = colours[i % colours->Length];
		Pen^ circularPen = gcnew Pen(c, 1.0f);

		for (double radius = phaseRadius; radius < maxRadius; radius += pixelsPerWave) {
			if (radius < 1) continue;
			g->DrawArc(circularPen, (float)(barrierX - radius), (float)(slitY[i] - radius), (float)(2 * radius), (float)(2 * radius), -90.0f, 180.0f);
		}
		delete circularPen;
	}
}

Bitmap^ buildInterferenceScreen(Graphics^ g, double wavelength1, double phase1, double slitSeparation, double slitWidth, int numSlits) {
	int width = (int)g->ClipBounds.Width;
	int height = (int)g->ClipBounds.Height;

	double centerY = height / 2.0;
	double yScale = height / 2.0;
	/*double xScale = width / 8.0;*/

	double pixelsPerWave = wavelength1;
	double constantK = 2.0 * Math::PI / pixelsPerWave;
	double barrierX = width * 0.25;
	double screenX = width * 0.95;
	double length = screenX - barrierX;
	double slitHalfWidth = (slitWidth / 2.0) * yScale;

	array<double>^ slitY = gcnew array<double>(numSlits);
	if (numSlits == 1) {
		slitY[0] = centerY;
	}
	else {
		double totalSpan = (numSlits - 1) * (slitSeparation * yScale);
		for (int i = 0; i < numSlits; i++) {
			slitY[i] = centerY - totalSpan / 2.0 + i * (slitSeparation * yScale);
		}

	}

	Pen^ displayScreenPen = gcnew Pen(Color::Gray, 2.0f);
	g->DrawLine(displayScreenPen, (int)screenX, 0, (int)screenX, height);
	delete displayScreenPen;

	int stripWidthOfScreen = 25;
	
	Bitmap^ bitmap = gcnew Bitmap(stripWidthOfScreen, height, Imaging::PixelFormat::Format32bppArgb);
	Imaging::BitmapData^ bitmapData = bitmap->LockBits(
		System::Drawing::Rectangle(0, 0, stripWidthOfScreen, height),
		Imaging::ImageLockMode::WriteOnly,
		Imaging::PixelFormat::Format32bppArgb
	);
	int stride = bitmapData->Stride;
	unsigned char* scan0 = (unsigned char*)(void*)bitmapData->Scan0;

	double maxIntensity = 0.0;
	array<double>^ intensities = gcnew array<double>(height);
	for (int h = 0; h < height; h++) {
		double realPart = 0.0, imaginaryPart = 0.0;
		for (int i = 0; i < numSlits; i++) {
			double dh = h - slitY[i];
			double radius = Math::Sqrt(length * length + dh * dh);

			double arguement = (slitHalfWidth > 0) ? constantK * slitHalfWidth * dh / radius : 0.0;
			double sinc = (Math::Abs(arguement) > 1e-10) ? Math::Sin(arguement) / arguement : 1.0;
			//A wave travelling distance r from a point source is written as :
			//psi = A * e ^ (ikr) = A * cos(kr) + i * A * sin(kr)
		    // where k = 2 * pi / lambda is the wavenumber.
		    //realPart += sinc * cos(k * r + phase)
			// imaginaryPart += sinc * sin(k * r + phase)

			realPart += sinc * Math::Cos(constantK * radius + phase1);
			imaginaryPart += sinc * Math::Sin(constantK * radius + phase1);
		}

		//Intensity is the squared magnitude of the total wave :
		//I = | psi_total | ^ 2 = realPart ^ 2 + imaginaryPart ^ 2
		//For two slits this expands to :
		//I = 2 + 2 * cos(k * delta_r)    where delta_r = r1 - r2(path difference)
		intensities[h] = realPart * realPart + imaginaryPart * imaginaryPart;
		if (intensities[h] > maxIntensity) {
			maxIntensity = intensities[h];
		}
	}
		
	for (int h = 0; h < height; h++) {
		double normalizedIntensity = (maxIntensity > 0) ? intensities[h] / maxIntensity : 0.0;	
		unsigned char brightness = (unsigned char)(normalizedIntensity * 255.0);	
		unsigned char* pixelData = scan0 + h * stride;
		for (int w = 0; w < stripWidthOfScreen; w++) {
			pixelData[w * 4] = brightness;		
			pixelData[w * 4 + 1] = brightness;	
			pixelData[w * 4 + 2] = brightness;	
			pixelData[w * 4 + 3] = 255;		
		}
	}
	bitmap->UnlockBits(bitmapData);
	return bitmap;
}




