#include "Matrix.h"

void testMatricies()
{
	Matrix<double, 5, 5> m;
	std::cout << "Un-initialized matrix: " << std::endl;
	std::cout << m << std::endl;
	m.toIdentity();
	std::cout << "An identity matrix: " << std::endl;
	std::cout << m << std::endl;
	std::cout << "Squared: " << std::endl;
	std::cout << operator*<double, 5, 5>(m, m) << std::endl;
	std::cout << "Randomized: " << std::endl;
	m.toRandomValues(0, 10);
	std::cout << m << std::endl;
	Matrix<double, 5, 5> copy (m);
	m.invert();
	std::cout << std::endl << "Inverted: " << std::endl << m << std::endl;
	std::cout << "Times its inverse: " << std::endl;
	std::cout << operator*<double, 5, 5>(copy, m) << std::endl;
}
