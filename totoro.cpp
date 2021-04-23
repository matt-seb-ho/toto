#include "totoro.h"

Totoro::Totoro(double x, double y, color c){
	colourMap["white"] = color(255, 255, 255);
	colourMap["black"] = color(0, 0, 0);
	Es.push_back(make_shared<ellipse>(100, 100, 72, 75, 0.0, c));
	Es.push_back(make_shared<ellipse>(100, 100, 125, 0.0, c));
	Es.push_back(make_shared<ellipse>(75, 200, 75, 100, 0.0, c));
	Es.push_back(make_shared<ellipse>(125, 200, 75, 100, 0.0, c));
	Es.push_back(make_shared<ellipse>(62, 36, 7.5, 10, 0.0, c));
	Es.push_back(make_shared<ellipse>(138, 36, 7.5, 10, 0.0, c));
	Es.push_back(make_shared<ellipse>(68, 60, 11.5, 10, 1.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(132, 60, 11.5, 10, 1.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(100, 190, 85, 100, 1.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(70, 60, 5, 5, 2.0, colourMap["black"]));
	Es.push_back(make_shared<ellipse>(130, 60, 5, 5, 2.0, colourMap["black"]));
	Es.push_back(make_shared<ellipse>(100, 64, 16.5, 4.5, 2.0, colourMap["black"]));
	verts1 = {vec2(64, 0), vec2(54, 34), vec2(74, 34)};
	Ps.push_back(make_shared<Polygon>(verts1, 1.0, c));
	verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	Ps.push_back(make_shared<Polygon>(verts2, 1.0, c));
	Rs.push_back(make_shared<Rect>(23, 70, 58, 70, colourMap["black"], 2.0));
	Rs.push_back(make_shared<Rect>(17, 75, 52, 75, colourMap["black"], 2.0));
	Rs.push_back(make_shared<Rect>(25, 80, 60, 80, colourMap["black"], 2.0));
	Rs.push_back(make_shared<Rect>(142, 70, 177, 70, colourMap["black"], 2.0));
	Rs.push_back(make_shared<Rect>(148, 75, 183, 75, colourMap["black"], 2.0));
	Rs.push_back(make_shared<Rect>(140, 80, 175, 80, colourMap["black"], 2.0));
	pos.setX(x);
	pos.setY(y);
}

Totoro::Totoro(double x, double y) :
	Totoro(x, y, color(127, 130, 128)) {

	}



color Totoro::eval(double x, double y, color background){
	color inC = background;
	double curDepth = -1;
	double res;
	//iterate through all possible equations (note 'front' determined by order in vector)

	for (auto eq : Es) {
		res = eq->eval(x - pos.x(), y - pos.y());
		if (res < 0 && eq->getDepth() > curDepth) {
			inC = eq->getInC();
			curDepth = eq->getDepth();
		}
	}
	for (auto rect: Rs) {
		if (rect->evalIn(x - pos.x(), y - pos.y()) && rect->getDepth() > curDepth){
			inC = rect->getInC();
			curDepth = rect->getDepth();
		}
	}

	for (auto poly:Ps) {
		if (poly->eval(x - pos.x(), y - pos.y()) && poly->getDepth() > curDepth){
			inC = poly->getInC();
			curDepth = poly->getDepth();
		}
	}

	return inC;
}


void Totoro::translate(double x, double y){
	pos.setX(pos.x() + x);
	pos.setY(pos.y() + y);
}
