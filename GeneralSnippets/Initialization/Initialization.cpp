#include <iostream>

// =====================================================================================
// static_assert
// =====================================================================================

// =====================================================================================
// https://www.grimm-jaud.de/index.php/blog/initialisierung
// und
// "Peter Pohmann" // Kapitel 2.15
// =====================================================================================

#include <iostream> 

namespace UniformInitialization {

	void test_01() {

		int n{ 99 };
		std::string s{ "Hans" };

		int* pi = new int[5]{ 1, 2, 3, 4, 5 };
		double* pd = new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 };

		std::cout << n << std::endl;
		std::cout << s << std::endl;
	}

	class MyDataClass {
	public:
		int x;
		double y;

		void print() { std::cout << "x: " << x << ", y: " << y << std::endl; }
	};

	void test_02() {

		// initialization of public attributes of an arbitrary object
		MyDataClass obj1 { 111, 1.23 };
		MyDataClass obj2 { 123, 99.9 };

		obj1.print();
		obj2.print();
	}
}

int main()
// int main_uniform_initialization()
{
	using namespace UniformInitialization;

	// test_01(); 
	test_02();

	return 0;
}
