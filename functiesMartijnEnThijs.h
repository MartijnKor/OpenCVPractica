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
int allBoundingBoxes(const vector<vector<Point>> & contours, vector<vector<Point>> & bbs);
int roiThijsenMartijn(Mat &input, Mat &output, Point & minXY, Point & maxXY);
string type2str(int type);

// deze functie omlijnt een object in een matobject.
int moore(Mat &input, vector<Point> firstPixel, vector<vector<Point>> &uitkomst, vector<vector<int>> &vorigeRichting) {

	Mat labeld_img;
	vector<Point2d *> firstpixelVec3;
	vector<Point2d *> posVec3;
	vector<int> areaVec3;
	int aantalpunten = 0;
	Mat bitconv;
	threshold(input, input, 1, 1, CV_THRESH_BINARY);
	input.convertTo(bitconv, CV_16S);
	// bereken het aantal blobs in een afbeelding
	// schrijf in firstpixelVec3 de eerste pixel van de vector
	aantalpunten = labelBLOBsInfo(bitconv, labeld_img, firstpixelVec3, posVec3, areaVec3, 20);

	// x en y omdraaien:
	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		firstPixel.push_back(Point(firstpixelVec3[i]->y, firstpixelVec3[i]->x));
		vorigeRichting.push_back(vector<int>());
	}

	// wanneer er een fistpixelgevonden is:
	for (int i = 0; i < firstpixelVec3.size(); i++)
	{
		// Calibratie.
		Point b0 = firstPixel[i];
		Point c0 = Point(firstPixel[i].x - 1, firstPixel[i].y);
		cout << "B0 : " << b0 << "     Ci : " << c0 << endl;
		vorigeRichting[i] = { 4 };

		uitkomst.push_back(vector<Point>());





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

// functie die de firstpixel vind voor een object
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

// functie die de engergie berekent voor het buigen van de contour
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
			// de eerste richting wordt van de tweede afgehaad.
			eersteBeweging = vorigeRichting[i];
			tweedeBeweging = vorigeRichting[i + 1];
			totaleBeweging = abs(eersteBeweging - tweedeBeweging);

			if (totaleBeweging == 7)
				totaleBeweging = 1;

			if (totaleBeweging == 6)
				totaleBeweging = 2;

			if (totaleBeweging == 5)
				totaleBeweging = 3;
			// de bewegings engergie bij elkaar optellen
			bewegingsEnergie += totaleBeweging;
		}


	return bewegingsEnergie;
}

// deze functies maakt boxen om de objecten in een afbeelding
int allBoundingBoxes(const vector<vector<Point>> & contours, vector<vector<Point>> & bbs)
{
	
	for (int j = 0; j < contours.size(); j++) 
	{
		int minX = INT_MAX;
		int minY = INT_MAX;
		int maxX = INT_MIN;
		int maxY = INT_MIN;

		for (int i = 0; i < contours[j].size(); i++)
		{
			if (contours[j][i].x < minX)
			{
				minX = contours[j][i].x;
			}

			if (contours[j][i].y < minY)
			{
				minY = contours[j][i].y;
			}

			if (contours[j][i].x > maxX)
			{
				maxX = contours[j][i].x;
			}

			if (contours[j][i].y > maxY)
			{
				maxY = contours[j][i].y;
			}
		}
		for (int y = minY; y <= maxY; y++)
		{
			for (int x = minX; x <= maxX; x++)
			{
				if (y == minY || y == maxY)
				{
					bbs[j].push_back(Point(x, y));
				}

				else if (x == minX | x == maxX )
				{
					bbs[j].push_back(Point(x, y));
				}


			}
		}

	}
	return bbs.size();
}

// deze functie maakt een ROI om de objecten in een afbeelding
int roiThijsenMartijn(Mat &input, Mat &output, Point & minXY, Point & maxXY)
{
	cout << "Output: " << type2str(output.type()) << endl;
	cout << "Input: " << type2str(input.type()) << endl;
	
	for (int y = minXY.y; y < maxXY.y; y++)
	{
		for (int x = minXY.x; x < maxXY.x; x++)
		{
			output.at<Vec3b>(Point(x - minXY.x, y - minXY.y)) = input.at<Vec3b>(Point(x, y));
//			cout << x << "   " << y << "       " << x - minXY.x << "     " << y - minXY.y << endl;
		}
	}

	return 0;
}


string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}