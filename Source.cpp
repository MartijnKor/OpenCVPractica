#include "functiesMartijnEnThijs.h"


int main(int argc, char** argv) {

	bool eenObjectGevonden = false;
	Mat edgeObject;
	Point b0;
	// aanmaken orginele afbeelding en omzetten naar een grijswaarde
	Mat origineelRGB = imread(argv[1], IMREAD_COLOR);
	Mat origineel = imread(argv[1], IMREAD_GRAYSCALE);

	// controleer of de afbeelding gevonden wordt. Wanneer niet het geval dan vertellen hoe de mappen structuur eruit ziet.
	if (!origineel.data)
	{
		cout << "Afbeelding niet correct!" << endl;
		cout << argv[1];
		cin.get();
		return -1;
	}

	cout << "Breedte afbeelding: " << origineel.cols << endl;
	// afbeelding weergeven
	imshow("origineel", origineel);
	Mat origineelOmgedraaid;
	inRange(origineel, 0, 180, origineelOmgedraaid);
	imshow("omgedraaid", origineelOmgedraaid);
	// mat object aanmaken met dezelfde size
	Mat uitkomstMat(Size(origineelOmgedraaid.cols, origineelOmgedraaid.rows), CV_8U, Scalar::all(0));


	vector<vector<Point>> uitkomst;
	vector<vector<int>> vorigeRichting;
	//Point firstPixel = vindEerstePixel(origineelOmgedraaid, uitkomst, eenObjectGevonden);
	vector<Point> firstPixel;
	cout << firstPixel;

	// moore functie uitvoeren
	moore(origineelOmgedraaid, firstPixel, uitkomst, vorigeRichting);
	// de uitkomst in een Mat object plaatsen.
	for (int j = 0; j < uitkomst.size(); j++)
	{
		for (int i = 0; i < uitkomst[j].size(); i++)
		{
			uitkomstMat.at<uchar>(uitkomst[j].at(i)) = 255;
		}
	}
	// boundingBoxens uitvoeren
	vector<vector<Point>> bbs(uitkomst.size());
	cout << "aantal boundingBoxes: " << allBoundingBoxes(uitkomst, bbs) << endl;
	// boundingBoxes in het Mat object uitkomst plaatsen
	for (int j = 0; j < bbs.size(); j++)
	{
		for (int i = 0; i < bbs[j].size(); i++)
		{
			uitkomstMat.at<uchar>(bbs[j].at(i)) = 255;
		}
	}
	// uitkomst uitprinten
	imshow("Uitkomst", uitkomstMat); 

	vector<int> compression;
	compression.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression.push_back(95);
	for (int i = 0; i < bbs.size(); i++)
	{
		Point minXY = Point(bbs[i].at(0).x, bbs[i].at(0).y);
		Point maxXY = Point(bbs[i].at(bbs[i].size() - 1).x, bbs[i].at(bbs[i].size() - 1).y);
		Mat blad = Mat(Size(((maxXY.x - minXY.x) +1), ((maxXY.y - minXY.y)+1)), CV_8UC3);
		roiThijsenMartijn(origineelRGB, blad, minXY, maxXY);
		imshow("blad" + i, blad);
		string naam = "blad";
		naam.append(to_string(i));
		naam.append(".bmp");
		imwrite(naam, blad);
	}
	
	waitKey(0);

	


	return 0;
}
