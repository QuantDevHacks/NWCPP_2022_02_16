module;
#include <cmath>

export module MyComplex;
import <compare>;
import <limits>;
import <iostream>;		// for print() function

export class MyComplex
{
public:
	MyComplex(double x, double y);
	MyComplex(double x);
	MyComplex();

	// Accessors
	double real() const;
	double imag() const;
	double radius() const;
	double theta() const;

	// Mutator
	void reset(double x, double y);

	bool operator == (const MyComplex& rhs) const;
	std::weak_ordering operator <=> (const MyComplex& rhs) const;

	MyComplex operator + (const MyComplex& rhs) const;
	MyComplex operator - (const MyComplex& rhs) const;
	MyComplex operator * (const MyComplex& rhs) const;
	MyComplex operator / (const MyComplex& rhs) const;

	void operator += (const MyComplex& rhs);
	void operator -= (const MyComplex& rhs);
	void operator *= (const MyComplex& rhs);
	void operator /= (const MyComplex& rhs);

	void print() const;

private:
	// x and y stored as real and imaginary values:
	double real_{ 0.0 }, imag_{ 0.0 };
	// Polar form stored here:
	double radius_{ 0.0 }, theta_{ 0.0 };
	
	void calc_polar_();
//	bool essentially_zero_() const;
	bool real_zero_(double p) const;
};



MyComplex::MyComplex(double x, double y) : real_(x), imag_(y)
{
	calc_polar_();
}

MyComplex::MyComplex(double x) : real_(x) {}

MyComplex::MyComplex() {}

double MyComplex::real() const
{
	return real_;
}

double MyComplex::imag() const
{
	return imag_;
}

double MyComplex::radius() const
{
	return radius_;
}

double MyComplex::theta() const
{
	return theta_;
}

void MyComplex::reset(double real, double imag)
{
	real_ = real;
	imag_ = imag;
	calc_polar_();
}

void MyComplex::calc_polar_()
{
	radius_ = std::hypot(real_, imag_);
	theta_ = std::acos(real_ / radius_);
	if (imag_ < 0.0)
	{
		theta_ = -theta_;
	}
}

bool MyComplex::real_zero_(double p) const
{
	double tol = std::sqrt(std::numeric_limits<double>::epsilon());
	if (std::abs(p) < tol)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyComplex::operator == (const MyComplex& rhs) const
{
	if(real_zero_(real_ - rhs.real_) && real_zero_(std::abs(imag_ - rhs.imag_)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::weak_ordering MyComplex::operator <=> (const MyComplex& rhs) const
{
	if (std::hypot(real_, imag_) < std::hypot(rhs.real_, rhs.imag_))
	{
		return std::weak_ordering::less;
	}
	else if (*this == rhs)
	{
		return std::weak_ordering::equivalent;
	}
	else
	{
		return std::weak_ordering::greater;
	}
}

MyComplex MyComplex::operator + (const MyComplex& rhs) const
{
	MyComplex sum(real_ + rhs.real_, imag_ + rhs.imag_);
	return sum;
}

MyComplex MyComplex::operator - (const MyComplex& rhs) const
{
	MyComplex diff(real_ - rhs.real_, imag_ - rhs.imag_);
	return diff;
}

MyComplex MyComplex::operator * (const MyComplex& rhs) const
{
	MyComplex prod((real_ * rhs.real_ - imag_ * rhs.imag_), (imag_ * rhs.real_ + real_ * rhs.imag_));
	return prod;
}

MyComplex MyComplex::operator / (const MyComplex& rhs) const
{
	double x2 = rhs.real_;
	double y2 = rhs.imag_;
	double denom = x2 * x2 + y2 * y2;

	if (!real_zero_(denom))
	{
		MyComplex quot((real_ * x2) / denom, (x2 * imag_ - real_ * y2) / denom);
		return quot;
	}
	else
	{
		double inf = std::numeric_limits<double>::infinity();
		MyComplex quot(inf, inf);
		return quot;
	}
}

void MyComplex::operator += (const MyComplex& rhs)
{
	*this = *this + rhs;
	calc_polar_();
}

void MyComplex::operator -= (const MyComplex& rhs)
{
	*this = *this - rhs;
	calc_polar_();
}

void MyComplex::operator *= (const MyComplex& rhs)
{
	*this = *this * rhs;
	calc_polar_();
}

void MyComplex::operator /= (const MyComplex& rhs)
{
	*this = *this / rhs;
	calc_polar_();
}

void MyComplex::print() const
{
	std::cout << real_ << " + i" << imag_ << std::endl;
}

