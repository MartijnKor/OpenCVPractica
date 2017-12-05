#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include "avansvisionlib.h"

using namespace std;
using namespace cv;


// int moore heeft een Mat object als input en een vector als output
int moore(Mat &input, vector<Point> firstPixel, vector<vector<Point>> &uitkomst, vector<vector<int>> &vorigeRichting);
// point heeft een Mat object nodig en returnt een cordinaat (0,0)
Point vindEerstePixel(Mat &input, vector<Point> &uitkomst, bool &eenObjectGevonden);
int bendingEnergy(vector<vector<int>> vorigeRichting);



int moore(Mat &input, vector<Point> firstPixel, vector<vector<Point>> &uitkomst, vector<vector<int>> &vorigeRichting) {

	Mat labeld_img;
	vector<Point2d *> firstpixelVec3;
	vector<Point2d *> posVec3;
	vector<int> areaVec3;
	int aantalpunten = 0;
	Mat bitconv;
	threshold(input, input, 1, 1, CV_THRESH_BINARY);
	input.convertTo(bitconv, CV_16S);

	aantalpunten = labelBLOBsInfo(bitconv, labeld_img, firstpixelVec3, posVec3, areaVec3, 20);

	// x en y omdraaien:
	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		firstPixel.push_back(Point(firstpixelVec3[i]->y, firstpixelVec3[i]->x));
		vorigeRichting.push_back(vector<int>());
	}


	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		// Calibratie.
		Point b0 = firstPixel[i];
		Point c0 = Point(firstPixel[i].x - 1, firstPixel[i].y);
		cout << "B0 : " << b0 << "     Ci : " << c0 << endl;
		vorigeRichting[i] = { 4 };

		for (int j = 0; j < firstpixelVec3.size(); j++)
		{
			uitkomst.push_back(vector<Point>());
		}




		// Nieuwe b0 vinden.
		int nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
		cout << "Nieuwe richting = " << vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1 << endl;

		do
		{
			if (nieuweRichting == 0)
			{
				c0 = Point(b0.x - 1, b0.y);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = 7;
				}
				else
					nieuweRichting++;
			}


			if (nieuweRichting == 1)
			{
				c0 = Point(b0.x - 1, b0.y - 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}


			if (nieuweRichting == 2)
			{
				c0 = Point(b0.x, b0.y - 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}


			if (nieuweRichting == 3)
			{
				c0 = Point(b0.x + 1, b0.y - 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}

			if (nieuweRichting == 4)
			{
				c0 = Point(b0.x + 1, b0.y);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}

			if (nieuweRichting == 5)
			{
				c0 = Point(b0.x + 1, b0.y + 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}

			if (nieuweRichting == 6)
			{
				c0 = Point(b0.x, b0.y + 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting++;
			}

			if (nieuweRichting == 7)
			{
				c0 = Point(b0.x - 1, b0.y + 1);
				if (input.at<bool>(c0) != 0) // Hier ligt een pixel.
				{
					uitkomst[i].push_back(c0);
					b0 = c0;
					vorigeRichting[i].push_back(nieuweRichting);
					nieuweRichting = vorigeRichting[i].at(vorigeRichting[i].size() - 1) - 1;
				}
				else
					nieuweRichting = 0;
			}
		} while (b0 != firstPixel[i]);
	}


	cout << "Klaar met Moore-functie!!!!!" << endl;

	return 0;

}

Point vindEerstePixel(Mat &input, vector<Point> &uitkomst, bool &eenObjectGevonden)
{
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			if (input.at<bool>(Point(j, i)) != 0 && eenObjectGevonden == false)
			{
				Point punt;
				punt.x = j;
				punt.y = i;
				eenObjectGevonden = true;
				return punt;

			}
			if (input.at<bool>(Point(j, i)) != 0 && eenObjectGevonden == true && pointPolygonTest(uitkomst, Point2f(j, i), false) == -1)
			{
				cout << pointPolygonTest(uitkomst, Point(j, i), false) << endl;
				Point punt;
				punt.x = j;
				punt.y = i;
				return punt;

			}
		}
	}
	return (-1, 0);
}

int bendingEnergy(vector<int> vorigeRichting) {
	// bereken hoeveel stappen de moore functie naar rechts gedraaid is.
	// zet het aantal stappen naar rechts in een vector
	// bereken het verschil tussen twee opeen volgende getallen in de vector
	// tel het totaal op van alle verschillen. 
	// totaal aantal stappen == buigenergie
	int bewegingsEnergie = 0;


		for (int i = 0; i < vorigeRichting.size() - 1; i++)
		{
			int eersteBeweging;
			int tweedeBeweging;
			int totaleBeweging;
			eersteBeweging = vorigeRichting[i];
			tweedeBeweging = vorigeRichting[i + 1];
			totaleBeweging = abs(eersteBeweging - tweedeBeweging);

			if (totaleBeweging == 7)
				totaleBeweging = 1;

			if (totaleBeweging == 6)
				totaleBeweging = 2;

			if (totaleBeweging == 5)
				totaleBeweging = 3;

			bewegingsEnergie += totaleBeweging;
		}


	return bewegingsEnergie;
}
