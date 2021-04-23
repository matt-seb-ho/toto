#ifndef FILEREAD_H
#define FILEREAD_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"

using namespace std;
void readLine(string line, vector<double>& target);

void addShape(vector<double>& shape, 
		vector<shared_ptr<ellipse> >& Es,
		vector<shared_ptr<Rect> >& Rs,
		vector<shared_ptr<Polygon> >& Ps);

void readFile(string filename,
		vector<shared_ptr<ellipse> >& Es,
		vector<shared_ptr<Rect> >& Rs,
		vector<shared_ptr<Polygon> >& Ps);
#endif
