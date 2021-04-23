/* ZJW simple C++ code to write out a PPM file representing shapes */
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "totoro.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"
#include <map>
#include "fileread.h"

using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

//This is getting so ugly, so glad we get to fix it soon
void writeOut(ostream& out, ppmR& theWriter, 
		/*
		vector<shared_ptr<ellipse> > IEs, vector<shared_ptr<Rect> > Rs,
		vector<shared_ptr<Polygon> > Ps) {
		*/
		Totoro t){

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;

			inC = t.eval(x, y, background);
			
			
			/*
			//iterate through all possible equations
			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
			/* compare my ret.h with yours 
			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}

			//loop through any polygons
			for (auto poly: Ps) {
				if (poly->eval(x, y) && poly->getDepth() > curDepth){
					inC = poly->getInC();
					inTrue = true;
					curDepth = poly->getDepth();
				}
			}

		*/

				theWriter.writePixel(out, x, y, inC);
				//theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}

/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	/*
	map<string, color> colourMap;
	colourMap["base"] = color(127, 130, 128);
	colourMap["white"] = color(255, 255, 255);
	colourMap["black"] = color(0, 0, 0);

	vector<shared_ptr<ellipse> > Es;
	vector<shared_ptr<Rect> > Rs;
	vector<shared_ptr<Polygon> > Ps;
	/*
	   vector<vec2> rverts = {vec2(136, 0), vec2(146, 34), vec2(126,34)};
	   vector<vec2> lverts = {vec2(64, 0), vec2(74, 34), vec2(54,34)};


	   Ps.push_back(make_shared<Polygon>(rverts, 1.0, color(127, 130, 128)));
	   Ps.push_back(make_shared<Polygon>(lverts, 1.0, color(127, 130, 128)));
	   vector<vec2> verts1 = {vec2(64, 0), vec2(54, 34), vec2(74, 34)};
	   Ps.push_back(make_shared<Polygon>(verts1, 1.0, colourMap["base"]));
	   vector<vec2> verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	   Ps.push_back(make_shared<Polygon>(verts2, 1.0, colourMap["base"]));
	   vector<vec2> verts3 = {vec2(100, 120), vec2(90, 130), vec2(110, 130)};
	   Ps.push_back(make_shared<Polygon>(verts3, 1.0, colourMap["black"]));
	   vector<vec2> verts4 = {vec2(120, 140), vec2(110, 150), vec2(130, 150)};
	   Ps.push_back(make_shared<Polygon>(verts4, 1.0, colourMap["black"]));
	   vector<vec2> verts5 = {vec2(80, 140), vec2(70, 150), vec2(90, 150)};
	   Ps.push_back(make_shared<Polygon>(verts5, 1.0, colourMap["black"]));
	   vector<vec2> verts6 = {vec2(140, 160), vec2(130, 170), vec2(150, 170)};
	   Ps.push_back(make_shared<Polygon>(verts6, 1.0, colourMap["black"]));
	   vector<vec2> verts7 = {vec2(60, 160), vec2(50, 170), vec2(70, 170)};
	   Ps.push_back(make_shared<Polygon>(verts7, 1.0, colourMap["black"]));

	   vector<vec2> verts1 = {vec2(64, 0), vec2(74, 34), vec2(54, 34)};
	   Ps.push_back(make_shared<Polygon>(verts1, 8, colourMap["base"]));
	   vector<vec2> verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	   Ps.push_back(make_shared<Polygon>(verts2, 8, colourMap["base"]));
	   vector<vec2> verts3 = {vec2(100, 120), vec2(90, 130), vec2(110, 130)};
	   Ps.push_back(make_shared<Polygon>(verts3, 8, colourMap["black"]));
	   vector<vec2> verts4 = {vec2(120, 140), vec2(110, 150), vec2(130, 150)};
	   Ps.push_back(make_shared<Polygon>(verts4, 8, colourMap["black"]));
	   vector<vec2> verts5 = {vec2(80, 140), vec2(70, 150), vec2(90, 150)};
	   Ps.push_back(make_shared<Polygon>(verts5, 8, colourMap["black"]));
	   vector<vec2> verts6 = {vec2(140, 160), vec2(130, 170), vec2(150, 170)};
	   Ps.push_back(make_shared<Polygon>(verts6, 8, colourMap["black"]));
	   vector<vec2> verts7 = {vec2(60, 160), vec2(50, 170), vec2(70, 50)};
	   Es.push_back(make_shared<ellipse>(100, 100, 72, 75, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(100, 175, 100, 125, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(75, 200, 75, 100, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(125, 200, 75, 100, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(62, 36, 7.5, 10, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(138, 36, 7.5, 10, 0.0, colourMap["base"]));
	   Es.push_back(make_shared<ellipse>(68, 60, 11.5, 10, 1.0, colourMap["white"]));
	   Es.push_back(make_shared<ellipse>(132, 60, 11.5, 10, 1.0, colourMap["white"]));
	   Es.push_back(make_shared<ellipse>(100, 190, 85, 100, 1.0, colourMap["white"]));
	   Es.push_back(make_shared<ellipse>(70, 60, 5, 5, 2.0, colourMap["black"]));
	   Es.push_back(make_shared<ellipse>(130, 60, 5, 5, 2.0, colourMap["black"]));
	   Es.push_back(make_shared<ellipse>(100, 64, 16.5, 4.5, 2.0, colourMap["black"]));
	   vector<vec2> verts1 = {vec2(64, 0), vec2(54, 34), vec2(74, 34)};
	   Ps.push_back(make_shared<Polygon>(verts1, 1.0, colourMap["base"]));
	   vector<vec2> verts1 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	   Ps.push_back(make_shared<Polygon>(verts1, 1.0, colourMap["base"]));
	   Rs.push_back(make_shared<Rect>(23, 70, 58, 70, colourMap["black"], 2.0));
	   Rs.push_back(make_shared<Rect>(17, 75, 52, 75, colourMap["black"], 2.0));
	   Rs.push_back(make_shared<Rect>(25, 80, 60, 80, colourMap["black"], 2.0));
	   Rs.push_back(make_shared<Rect>(142, 70, 177, 70, colourMap["black"], 2.0));
	   Rs.push_back(make_shared<Rect>(148, 75, 183, 75, colourMap["black"], 2.0));
	   Rs.push_back(make_shared<Rect>(140, 80, 175, 80, colourMap["black"], 2.0));
	 */

	/*
	   vector<vec2> verts1 = {vec2(64, 0), vec2(74, 34), vec2(54, 34)};
	   Ps.push_back(make_shared<Polygon>(verts1, 1.0, colourMap["base"]));
	   vector<vec2> verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	   Ps.push_back(make_shared<Polygon>(verts2, 1.0, colourMap["base"]));
	   vector<vec2> verts3 = {vec2(100, 120), vec2(110, 130), vec2(90, 130)};
	   Ps.push_back(make_shared<Polygon>(verts3, 1.0, colourMap["black"]));
	   vector<vec2> verts4 = {vec2(120, 140), vec2(130, 150), vec2(110, 150)};
	   Ps.push_back(make_shared<Polygon>(verts4, 1.0, colourMap["black"]));
	   vector<vec2> verts5 = {vec2(80, 140), vec2(90, 150), vec2(70, 150)};
	   Ps.push_back(make_shared<Polygon>(verts5, 1.0, colourMap["black"]));
	   vector<vec2> verts6 = {vec2(140, 160), vec2(150, 170), vec2(130, 170)};
	   Ps.push_back(make_shared<Polygon>(verts6, 1.0, colourMap["black"]));
	   vector<vec2> verts7 = {vec2(60, 160), vec2(70, 170), vec2(50, 170)};
	   Ps.push_back(make_shared<Polygon>(verts7, 1.0, colourMap["black"]));
	   vector<vec2> verts8 = {vec2(120, 160), vec2(130, 170), vec2(110, 170)};
	   Ps.push_back(make_shared<Polygon>(verts8, 1.0, colourMap["black"]));
	   vector<vec2> verts9 = {vec2(80, 160), vec2(90, 170), vec2(70, 170)};
	   Ps.push_back(make_shared<Polygon>(verts9, 1.0, colourMap["black"]));

	vector<vec2> verts1 = {vec2(64, 0), vec2(74, 34), vec2(54, 34)};
	Ps.push_back(make_shared<Polygon>(verts1, 8.0, colourMap["base"]));
	vector<vec2> verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	Ps.push_back(make_shared<Polygon>(verts2, 8.0, colourMap["base"]));
	vector<vec2> verts3 = {vec2(100, 120), vec2(110, 130), vec2(90, 130)};
	Ps.push_back(make_shared<Polygon>(verts3, 8.0, colourMap["black"]));
	vector<vec2> verts4 = {vec2(120, 140), vec2(130, 150), vec2(110, 150)};
	Ps.push_back(make_shared<Polygon>(verts4, 8.0, colourMap["black"]));
	vector<vec2> verts5 = {vec2(80, 140), vec2(90, 150), vec2(70, 150)};
	Ps.push_back(make_shared<Polygon>(verts5, 8.0, colourMap["black"]));
	vector<vec2> verts6 = {vec2(140, 160), vec2(150, 170), vec2(130, 170)};
	Ps.push_back(make_shared<Polygon>(verts6, 8.0, colourMap["black"]));
	vector<vec2> verts7 = {vec2(60, 160), vec2(70, 170), vec2(50, 170)};
	Ps.push_back(make_shared<Polygon>(verts7, 8.0, colourMap["black"]));
	vector<vec2> verts8 = {vec2(120, 160), vec2(130, 170), vec2(110, 170)};
	Ps.push_back(make_shared<Polygon>(verts8, 8.0, colourMap["black"]));
	vector<vec2> verts9 = {vec2(80, 160), vec2(90, 170), vec2(70, 170)};
	Ps.push_back(make_shared<Polygon>(verts9, 8.0, colourMap["black"]));
	readFile("totoro.csv", Es, Rs, Ps);
	*/

	Totoro t(0, 0);

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);
		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, t);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}

}
