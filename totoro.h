#ifndef TOTORO_H
#define TOTORO_H

#include "vec2.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include <map>
#include <memory>
#include <vector>

class Totoro {
public:
	Totoro(double x, double y);
	Totoro(double x, double y, color c);
	color eval(double x, double y, color background);
	void translate(double x, double y);
private:
	vec2 pos;
	color base;
	std::vector<shared_ptr<ellipse> > Es;
	std::vector<shared_ptr<Rect> > Rs;
	std::vector<shared_ptr<Polygon> > Ps;
	std::map<std::string, color> colourMap;
};
#endif
