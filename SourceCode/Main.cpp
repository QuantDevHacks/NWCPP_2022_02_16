import FunctionAndHelpersModule;
import Shapes;
import RangesAndViews;
import Dates;
import MyComplex;

#include <format>
#include <iostream>
using std::cout;
using std::endl;

void format_examples();
void spaceship_operator_examples();


int main()
{
	cout << "*** Module Function ***" << endl;
	auto result = primary_fcn(1.0, 2.0, -1.0, 1.0, 1.0);
	cout << std::format("primary_fcn({},{},{},{},{}) = {}", 1.0, 2.0, -1.0, 0.5, 0.5, result);
	cout << endl << endl;

	format_examples();
	spaceship_operator_examples();
	ranges_and_views();
	date_examples();

	return 0;
}

void format_examples()
{
	cout << endl << "*** std::format examples ***" << endl;
	Rectangle rec1(1.0, 1.0);
	Rectangle rec2(3.0, 2.0);

	cout << std::format("Area of first rectangle is {0}, second rectangle is {1}", 
		rec1.area(), rec2.area()) << endl;
	cout << std::format("Area of first rectangle is {}, second rectangle is {}", 
		rec1.area(), rec2.area()) << endl;
	cout << std::format("Area of second rectangle is {1}, first rectangle is {0}",
		rec1.area(), rec2.area()) << endl;

	cout << endl << endl;

}

void spaceship_operator_examples()
{
	cout << endl << "*** spaceship_operator_examples() (MyComplex) ***" << endl;
	MyComplex z1{ 1.0, 1.0 };
	MyComplex z2{ 3.0, 2.0 };

	// Define inequality in terms of the *norm*
	// of a complex number.

	cout << std::boolalpha
		<< std::format("{} + {}i == {} + {}i ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 == z2) << endl;
	cout << std::boolalpha
		<< std::format("{} + {}i != {} + {}i ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 != z2) << endl;
	cout << std::boolalpha
		<< std::format("|{} + {}i| < |{} + {}i| ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 < z2) << endl;
	cout << std::boolalpha
		<< std::format("|{} + {}i| <= |{} + {}i| ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 <= z2) << endl;
	cout << std::boolalpha
		<< std::format("|{} + {}i| > |{} + {}i| ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 > z2) << endl;
	cout << std::boolalpha
		<< std::format("|{} + {}i| >= |{} + {}i| ? ", z1.real(), z1.imag(), z2.real(), z2.imag())
		<< (z1 >= z2) << endl << endl;
}