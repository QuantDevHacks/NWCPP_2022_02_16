export module FunctionAndHelpersModule;

void fcn_of_x(double x);
void fcn_of_y(double y);

double f_x{ 0.0 }, f_y{ 0.0 };
double a_, b_, c_;

export double primary_fcn(double a, double b, double c, double x, double y)
{
	a_ = a;
	b_ = b;
	c_ = c;

	fcn_of_x(x);
	fcn_of_y(y);

	return f_x + f_y;
}

// The following functions are "private"
// within the module:
void fcn_of_x(double x)
{
	f_x = a_ * x + b_;
}

void fcn_of_y(double y)
{
	f_y = (a_ * y + b_) * y + c_;
}