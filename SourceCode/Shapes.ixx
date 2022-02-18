export module Shapes;
import <string>;
import <numbers>;	// To be used in the Circle class to follow

export class Shape
{
public:
	virtual double area() const = 0;
	virtual std::string what_am_i() const = 0;
	virtual ~Shape() = default;		// still need virtual dtor 
};

export class Circle : public Shape
{
public:
	Circle(double radius) :radius_{ radius } {}
	double area() const override
	{
		return std::numbers::pi * radius_ * radius_;
	}

	std::string what_am_i() const override
	{
		return "Circle";
	}

private:
	double radius_;
};

export class Rectangle : public Shape
{
public:
	Rectangle(double length, double width):
		length_{length}, width_{width} {}

	double area() const override
	{
		return length_ * width_;
	}

	std::string what_am_i() const override
	{
		return "Rectangle";
	}
private:
	double length_, width_;
};