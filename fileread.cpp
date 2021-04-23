#include "fileread.h"

using namespace std;

void printV(vector<double>& v){
	if(v.size() == 0){
		cout << "{}";
		return;
	}
	cout << "{";
	for(int i = 0; i < v.size() - 1; i++){
		cout << v[i] << ", ";
	}
	cout << v[v.size() - 1] << "}";
}

void readLine(string line, vector<double>& target){
	target.clear();
	stringstream ss(line);
	string data;
	getline(ss, data, ',');
	// skip label
	getline(ss, data, ',');
	while(ss.good()){
		target.push_back(stod(data));
		getline(ss, data, ',');
	}
}

int polyCounter = 0;
color grey(127, 130, 128);
color base(125, 125, 0);
void addShape(vector<double>& shape, 
		vector<shared_ptr<ellipse> >& Es,
		vector<shared_ptr<Rect> >& Rs,
		vector<shared_ptr<Polygon> >& Ps){
	vector<color> picker = {grey, color(250,250,250), color(0, 0, 0)};
	vector<string> picker2 = {"colourMap[\"base\"]", "colourMap[\"white\"]", "colourMap[\"black\"]"};
	if(shape[0] == 0){
		//cout << "is ell\n";

		cout << "Es.push_back(make_shared<ellipse>(" 
			<< shape[1] << ", " 
			<< shape[2] << ", " 
			<< shape[3] << ", " 
			<< shape[4] << ", " 
			<< shape[5] << ".0, "
			<< picker2[shape[5]] << "));" << endl;

		Es.push_back(make_shared<ellipse>(
					shape[1],
					shape[2],
					shape[3],
					shape[4],
					1.0 * shape[5],
					picker[shape[5]]));

	}
	if(shape[0] == 1){
		polyCounter++;
		cout << "vector<vec2> verts" << polyCounter << " = {";
		for(int i = 1; i < 3; i++){
			cout << "vec2(" << shape[i * 2 - 1] << ", " << shape[i * 2] << "), ";
		}
		cout << "vec2(" << shape[5] << ", " << shape[6] << ")};" << endl;
		cout << "Ps.push_back(make_shared<Polygon>(verts" 
			<< polyCounter << ", 8.0, " << picker2[shape[7]] << "));" << endl;
	}
	if(shape[0] == 2){

		cout << "Rs.push_back(make_shared<Rect>(" 
			<< shape[1] << ", " 
			<< shape[2] << ", " 
			<< shape[3] << ", " 
			<< shape[4] << ", "
			<< picker2[shape[5]] << ", "
			<< "2.0));" << endl;

		Rs.push_back(make_shared<Rect>(
					shape[1],
					shape[2],
					shape[3],
					shape[4],
					picker[shape[5]],
					2.0));
	}
}

void readFile(string filename,
		vector<shared_ptr<ellipse> >& Es,
		vector<shared_ptr<Rect> >& Rs,
		vector<shared_ptr<Polygon> >& Ps){
	ifstream is;
	is.open(filename);
	string line;
	getline(is, line);
	vector<double> data;
	int counter = 1;
	while(!is.eof()){
		readLine(line, data);
		addShape(data, Es, Rs, Ps);
		getline(is, line);
	}
	is.close();
}
