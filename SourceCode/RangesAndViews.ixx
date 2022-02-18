export module RangesAndViews;
import <vector>;
import <algorithm>;
import <numeric>;
import <ranges>;
import <utility>;

import <format>;
import <iostream>;
using std::cout;
using std::endl;

void algos_and_ranges();
void views_naive();
void views_functional();

export void ranges_and_views()
{
	algos_and_ranges();
	views_naive();
	views_functional();
}

void algos_and_ranges()
{
	auto is_odd = [](int n)-> bool
	{
		return ((n % 2) == 1);
	};

	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto u(v);		// Backup
	std::vector<int> w;

	auto num_odd = std::count_if(v.begin(), v.end(), is_odd);
	auto num_odd_ranges = std::ranges::count_if(v, is_odd);
	cout << std::format("Number of odd elements: {}, with ranges: {}", num_odd, num_odd_ranges);
	cout << endl << endl;

	auto square = [](int n)-> int
	{
		return n * n;
	};

	// Compare the old way vs using the ranges version (num_odd = 5):
	std::transform(v.begin(), v.end(), v.begin(), square);
	for (auto k : v)
	{
		cout << k << " ";
	}
	cout << endl << endl;

	v = u;		// Reset
	std::ranges::transform(v, v.begin(), square);
	for (auto k : v)
	{
		cout << k << " ";
	}
	cout << endl << endl;

	// Can also use back_inserter
	std::ranges::transform(u, std::back_inserter(w), square);
	for (auto k : w)
	{
		cout << k << " ";
	}
	cout << endl << endl;

	// const iterators:
	num_odd_ranges = std::ranges::count_if(u.cbegin(), u.cend(), is_odd);
	cout << std::format("Number of odd elements with const iter: {}", num_odd_ranges);
	cout << endl << endl;

	w.clear();
	std::ranges::transform(u.cbegin(), u.cend(), std::back_inserter(w), square);
	for (auto k : w)
	{
		cout << k << " ";
	}
	cout << endl << endl;
}

void views_naive()
{
	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);  // -5.5, -4.5, . . ., 3.5 (10 elements)

	auto take_five = std::views::take(w, 5);
	auto two_below = std::views::filter(take_five, [](double x) {return x < -2.0; });
	auto squares = std::views::transform(two_below, [](double x) {return x * x; });
	auto drop_two = std::views::drop(squares, 2);
	auto sum_result = std::accumulate(drop_two.begin(), drop_two.end(), 0.0);

	auto print = [](double x)
	{
		cout << x << " ";
	};

	std::ranges::for_each(take_five, print);
	cout << endl;
	std::ranges::for_each(two_below, print);
	cout << endl;
	std::ranges::for_each(squares, print);
	cout << endl;
	std::ranges::for_each(drop_two, print);
	cout << endl;

	cout << std::format("Sum of elements in drop_two (naive) = {}", sum_result);
	cout << endl << endl;
}

void views_functional()
{
	std::vector<double> w(10);
	std::iota(w.begin(), w.end(), -5.5);  // -5.5, -4.5, . . ., 3.5 (10 elements)

	auto drop_two = std::views::take(w, 5)
		| std::views::filter([](double x) {return x < -2.0; })
		| std::views::transform([](double x) {return x * x; })
		| std::views::drop(2);
	
	auto print = [](double x)
	{
		cout << x << " ";
	};

	std::ranges::for_each(drop_two, print);
	cout << endl;

	auto sum_result = std::accumulate(drop_two.begin(), drop_two.end(), 0.0);
	cout << std::format("Sum of elements in drop_two (functional) = {}", sum_result);
	cout << endl << endl;
}