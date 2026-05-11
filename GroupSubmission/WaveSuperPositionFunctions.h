#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

using namespace System;
using namespace System::Drawing;

double x_World(int px, double x0, double x1, double W) {
	return x0 + px * (x1 - x0) / W;
}

int y_Screen(double y, double y0, double y1, double H) {
	return (int)((y - y1) * H / (y0 - y1));
}
// GRID
void grid(Graphics^ g, double x0, double x1, double dx, int W,
	double y0, double y1, double dy, int H)
{
	Pen^ grayPen = gcnew Pen(Color::LightGray, 1);

	for (int x = 0; x < W; x += 100)
		g->DrawLine(grayPen, x, 0, x, H);

	for (int y = 0; y < H; y += 100)
		g->DrawLine(grayPen, 0, y, W, y);

	delete grayPen;
}

// DRAW WAVES
void drawFunction(Graphics^ g,
	double wavelength1, double wavelength2,
	double frequency1, double frequency2,
	double time,
	double amplitude1, double amplitude2,
	double direction,
	bool standingMode,
	bool showWave1,
	bool showWave2)
{
	RectangleF r = g->ClipBounds;

	Pen^ pen1 = gcnew Pen(Color::Red, 1);
	Pen^ pen2 = gcnew Pen(Color::Blue, 1);
	Pen^ penSum = gcnew Pen(Color::Black, 2);

	double k1 = 2 * M_PI / wavelength1;
	double k2 = 2 * M_PI / wavelength2;

	double w1 = 2 * M_PI * frequency1;
	double w2 = 2 * M_PI * frequency2;

	int py1_prev = 0, py2_prev = 0, pySum_prev = 0;

	for (int px = 0; px < r.Width; px++) {

		double x = x_World(px, -1000, 1000, r.Width);

		double y1, y2, ySum;

		if (standingMode) {
			y1 = amplitude1 * sin(k1 * x) * cos(w1 * time);
			y2 = 0;
			ySum = 2 * amplitude1 * sin(k1 * x) * cos(w1 * time);
		}
		else {
			y1 = amplitude1 * sin(k1 * x - direction * w1 * time);
			y2 = amplitude2 * sin(k2 * x - w2 * time);
			ySum = y1 + y2;
		}

		int py1 = y_Screen(y1, -10, 10, r.Height);
		int py2 = y_Screen(y2, -10, 10, r.Height);
		int pySum = y_Screen(ySum, -20, 20, r.Height);

		if (px > 0) {
			if (showWave1)
				g->DrawLine(pen1, px - 1, py1_prev, px, py1);

			if (showWave2 && !standingMode)
				g->DrawLine(pen2, px - 1, py2_prev, px, py2);

			g->DrawLine(penSum, px - 1, pySum_prev, px, pySum);
		}

		py1_prev = py1;
		py2_prev = py2;
		pySum_prev = pySum;
	}

	delete pen1;
	delete pen2;
	delete penSum;
}

