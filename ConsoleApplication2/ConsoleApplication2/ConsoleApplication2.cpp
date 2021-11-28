#include <Windows.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include "Eigen/Dense"
#include<cmath>

using namespace std;
using namespace Eigen;

int main() {
	system("color F0");
	srand(time(NULL));

	vector <double> x_help, y_help;



	int amm_poin;
	cout << "How many points do you want to enter? The maximum possible number of points is 12!" << endl;
	cin >> amm_poin;
	if (amm_poin > 12)
	{
		amm_poin = 12;
	}
	for (int i = 0; i < amm_poin; i++)
	{
		system("cls");
		double in_x_help, in_y_help;
		cout << "Enter your number on the axis X" << endl;
		cin >> in_x_help;
		cout << "Enter your number on the axis Y" << endl;
		cin >> in_y_help;

		if (in_x_help > 300)
		{
			in_x_help = 300;
		}
		if (in_x_help < -300)
		{
			in_x_help = -300;
		}
		if (in_y_help < -300)
		{
			in_y_help = -300;
		}
		if (in_y_help > 300)
		{
			in_y_help = 300;
		}

		x_help.push_back(in_x_help);
		y_help.push_back(in_y_help);
		system("cls");
	}

	double min;
	double max;
	vector<double> x;
	vector <double> y;

	if (x_help.size() < 2)
	{
		return 0;
	}
	else
	{
		double helper_num = x_help[0];
		int helper_ind = 0;
		for (int i = 0; i < x_help.size(); i++)
		{
			if (helper_num > x_help[i])
			{
				helper_num = x_help[i];
				helper_ind = i;
			}
			if (i + 1 == x_help.size())
			{
				x.push_back(helper_num);
				y.push_back(y_help[helper_ind]);

				x_help.erase(x_help.begin() + helper_ind);
				y_help.erase(y_help.begin() + helper_ind);

				if (x_help.empty())
				{
					break;
				}

				helper_num = x_help[0];
				helper_ind = 0;
				i = -1;
			}
		}
	}
	min = x[0];
	max = x[x.size() - 1];


	int size = x.size();

	vector<double> xx, yy;
	double step = 0.1;
	double value = x[0];
	int num = (max - min) / step;
	for (double i = 0; i <= num; i++) {
		xx.push_back(value);
		value = value + step;
	}
	int size_xx = xx.size();

	vector<double> dx;
	vector<double> dy;
	for (int i = 0; i < size - 1; i++) {
		double temp_dx = x[i + 1] - x[i];
		dx.push_back(temp_dx);
		double temp_dy = y[i + 1] - y[i];
		dy.push_back(temp_dy);
	}

	MatrixXd H = MatrixXd::Random(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			H(i, j) = 0;
		}
	}
	VectorXd Y(size);
	for (int i = 0; i < size; i++) {
		Y(i) = 0;
	}
	VectorXd M(size);
	for (int i = 0; i < size; i++) {
		M(i) = 0;
	}

	H(0, 0) = 1;
	H(size - 1, size - 1) = 1;
	for (int i = 1; i < size - 1; i++) {
		H(i, i - 1) = dx[i - 1];
		H(i, i) = 2 * (dx[i - 1] + dx[i]);
		H(i, i + 1) = dx[i];
		Y(i) = 3 * (dy[i] / dx[i] - dy[i - 1] / dx[i - 1]);
	}

	M = H.colPivHouseholderQr().solve(Y);

	vector<double> ai, bi, ci, di;
	for (int i = 0; i < size - 1; i++) {
		ai.push_back(y[i]);
		di.push_back((M(i + 1) - M(i)) / (3 * dx[i]));
		bi.push_back(dy[i] / dx[i] - dx[i] * (2 * M(i) + M(i + 1)) / 3);
		ci.push_back(M(i));
	}

	vector<int> x_, xx_;
	for (int i = 0; i < size; i++) {
		int temp = x[i] / 0.1;
		x_.push_back(temp);
	}
	for (int i = 0; i < size_xx; i++) {
		int temp = xx[i] / 0.1;
		xx_.push_back(temp);
	}

	for (int i = 0; i < size_xx; i++) {
		int k = 0;
		for (int j = 0; j < size - 1; j++) {
			if (xx_[i] >= x_[j] && xx_[i] < x_[j + 1]) {
				k = j;
				break;
			}
			else if (round(xx[i] * 10) / 10 == x[size - 1]) {
				k = size - 1 - 1;
			}
		}
		double temp = ai[k] + bi[k] * (xx[i] - x[k]) + M(k) * pow((xx[i] - x[k]), 2) + di[k] * pow((xx[i] - x[k]), 3);
		yy.push_back(temp);
	}



	for (int i = 0; i < x.size(); i++)
	{
		cout << "(" << x[i] << "," << y[i] << ")" << " ";
	}


	int a = 600;


	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hDC, Pen);
	MoveToEx(hDC, 0, a / 2, NULL);
	LineTo(hDC, a, a / 2);
	MoveToEx(hDC, a / 2, 0, NULL);
	LineTo(hDC, a / 2, a);


	Pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	SelectObject(hDC, Pen);

	for (int i = 1; i < size_xx; i++)
	{
		if (i != 1)
		{
			for (int l = 0; l < size; l++)
			{
				if ((round(xx[i - 1] * 10) / 10) == x[l])
				{
					int r = rand() % 255, g = rand() % 255, b = rand() % 255;
					while (r == 0 && g == 0 && b == 0)
					{
						r = rand() % 255, g = rand() % 255, b = rand() % 255;
					}
					Pen = CreatePen(PS_SOLID, 3, RGB(r, g, b));
					SelectObject(hDC, Pen);
				}
			}
		}
		MoveToEx(hDC, 10 * xx[i - 1] + a / 2, -10 * yy[i - 1] + a / 2, NULL);
		LineTo(hDC, 10 * xx[i] + a / 2, -10 * yy[i] + a / 2);
	}


	Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hDC, Pen);
	for (int i = 0; i < x.size() - 1; i++)
	{
		MoveToEx(hDC, 10 * x[i] + a / 2, -10 * y[i] + a / 2, NULL);
		LineTo(hDC, 10 * x[i + 1] + a / 2, -10 * y[i + 1] + a / 2);
	}

	int aa;
	cin >> aa;
}