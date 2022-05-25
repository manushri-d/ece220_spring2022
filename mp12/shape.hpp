/*In this MP, I made various classes under the Shape class. For every class, I had
constructors and getters. I also had area and volume methods given the formulas. I also
had operators, where I created a new shape and added and subtracted variables. 
CreateShapes utilized a file, and checked what type of shape it was, and depending, I would
create a new shape pointer and add it to a list. I also had 2 methods, a maxArea and a maxVolume
method which compared the current max area/volume with the current area/volume
*/
#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>  

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name; //assigned name of shape given the parameter
	}
	
  	string getName() {
		return name_; //returned name
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width; //assigned variables of rectangle given the parameter
		length_ = length;
	}
	
  	double getArea() const {
		return (double) width_*length_; //returned area given formula(typecasted)
	}
	
  	double getVolume() const {
		return 0; //volume is 0 in this case
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		Rectangle r = Rectangle(0.0,0.0); //made a new rectangle(initialized)
		r.width_ = width_ + rec.width_; //set the width to be added
		r.length_ = length_ + rec.length_; //set the length to be added
		return r; //return the new rectangle
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		Rectangle r = Rectangle(0.0,0.0); //made a new rectangle(initialized)
		r.width_ = max(0.0, (double) width_ - (double) rec.width_); //set the width to be subtracted
		r.length_ = max(0.0, (double) length_ - (double) rec.length_); //set the length to be subtracted
		return r; //return the new rectangle
	} 
	
	T getWidth() const { 
		return width_; //return width
	}
	
	T getLength() const { 
		return length_; //return length
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius; //assigned variables of circle given the parameter
	}
	
  	double getArea() const{
		return radius_*radius_* M_PI; //returned area given formula
	}
	
 	double getVolume() const{
		return 0; //volume is 0 for a circle
	}
	
  	Circle operator + (const Circle& cir){
		Circle c = Circle(0); //initialized
		c.radius_ = radius_ + cir.radius_; //set the radius to be added
		return c; //returned new c obj
	}
	
	Circle operator - (const Circle& cir){
		Circle c = Circle(0); //initialized
		c.radius_ = max(0.0, radius_ - cir.radius_); //subtracted radius
		return c; //returned new c obj
	} 

	double getRadius() const { 
		return radius_; //variable we are returning
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius; //assigned variables of sphere given the parameter
	}

  	double getVolume() const {
		return (4.0 / 3.0) * radius_ * radius_ * radius_ * M_PI; //returned volume given formula
	}	
	
  	double getArea() const {
		return 4 * M_PI * radius_ * radius_; //returned area given formula
	}

	Sphere operator + (const Sphere& sph) {
		Sphere s = Sphere(0); //initialized
		s.radius_ = radius_ + sph.radius_; //added radius
		return s;
	}

	Sphere operator - (const Sphere& sph) {
		Sphere s = Sphere(0); //initialized
		s.radius_ = max(0.0, radius_-sph.radius_); //subtracted radius
		return s;
	} 
	
	double getRadius() const {
		return radius_;	//getter
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		width_ = width; //assigned variables of RectPrism given the parameter
		length_ = length;
		height_ = height;
	}
	
  	double getVolume() const {
		return length_ * width_ * height_; //returned volume given formula
	}
  	
	double getArea() const {
		return 2 * (length_*width_ + length_*height_ + width_*height_); //returned area given formula
	}
	
	RectPrism operator + (const RectPrism& rectp){
		RectPrism rp = RectPrism(0,0,0); //initialized
		rp.width_ = width_ + rectp.width_; //adding width
		rp.length_ = length_ + rectp.length_; //adding length
		rp.height_ = height_ + rectp.height_; //adding height
		return rp;
	}
	
	RectPrism operator - (const RectPrism& rectp){
		RectPrism rp = RectPrism(0,0,0); //initialized
		rp.width_ = max(0.0, width_ - rectp.width_); //subtracting using max
		rp.length_ = max(0.0, length_ - rectp.length_);
		rp.height_ = max(0.0, height_ - rectp.height_);
		return rp;
	}	
	
	double getWidth() const { 
		return width_; //private variable
	}
	
	double getLength() const { 
		return length_; //private variable
	}
	
	double getHeight() const { 
		return height_; //private variable
	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	list<Shape*> l; //list 
	int fSize; //size of the amount of elements in the file
	string sName; //checking the name
	double width, length, height, radius; //diff values for the variables for sspace
	Shape* shape_ptr; //shape pointer
	ifstream ifs (file_name, std::ifstream::in);
  	ifs >> fSize;
  	for (int i = 0; i < fSize; i++){ //for loop
		ifs >> sName; //reading the new name
		if(sName == "Rectangle"){ //checking what the object is
			ifs >> width >> length; //reads the variables
			shape_ptr = new Rectangle<double>(width,length); //creates a new shape
		}else if(sName == "Circle"){ //checking what the object is
			ifs >> radius; //reads the variables
			shape_ptr = new Circle(radius); //creates a new shape
		}else if(sName == "Sphere"){ //checking what the object is
			ifs >> radius; //reads the variables
			shape_ptr = new Sphere(radius); //creates a new shape
		}else if(sName == "RectPrism"){ //checking what the object is
			ifs >> width >> length >> height; //reads the variables
			shape_ptr = new RectPrism(width,length,height); //creates a new shape
		}
		l.push_back(shape_ptr); //adds the object to the end of the list
	}
	return l;
}
 
// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) { //special for loop to iterate through lists
		if(max_area < (*it)->getArea()){ //if the current max area is smaller than the current area, then change val of max_area
			max_area = (*it)->getArea();
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) { //special for loop to iterate through lists
		if(max_volume < (*it)->getVolume()){ //if the current max volume is smaller than the current volume, then change val of max_volume
			max_volume = (*it)->getVolume();
		}
	}
	
	return max_volume;
}
#endif

