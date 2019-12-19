// Mustafa TOSUN 150170055

#include <iostream>

class Polynomial
{
private:
	int degree;
	int *coefficients;
public:
	Polynomial(int deg, const int *coefs); // Constructor
	Polynomial(const Polynomial &pol); // Copy Constructor 
	~Polynomial() { delete[] coefficients; } // Destructor
	Polynomial operator+(const Polynomial &pol) const; // Polynomial Addition
	Polynomial operator*(const Polynomial& pol) const; // Polynomial Multiplication
	friend std::ostream& operator<<(std::ostream& output, const Polynomial& pol); // << operator
};

Polynomial::Polynomial(int deg = 0, const int *coefs = 0)	// Constructor
{
	degree = deg;
	coefficients = new int[degree + 1];
	int i;
	for (i = 0; i <= degree; i++) coefficients[i] = 0;
	if (coefs)
		for (i = 0; i <= degree; i++) coefficients[i] = coefs[i];
}

Polynomial::Polynomial(const Polynomial &pol) // Copy Constructor
{
	degree = pol.degree;
	coefficients = new int[degree + 1];
	for (int i = degree; i >= 0; i--) coefficients[i] = pol.coefficients[i];
}

Polynomial Polynomial::operator+(const Polynomial &pol) const // Polynomial Addition
{
	int great, small;
	int *coefs;
	if (degree > pol.degree) {
		great = degree;
		small = pol.degree;
	}
	else {
		great = pol.degree;
		small = degree;
	}
	coefs = new int[great];
	for (int i = small; i >= 0; i--) {
		coefs[i] = coefficients[i] + pol.coefficients[i];
	}
	for (int i = great; i > small; i--) {
		if (great == pol.degree) coefs[i] = pol.coefficients[i];
		else 				  coefs[i] = coefficients[i];
	}
	return Polynomial(great, coefs);
}

Polynomial  Polynomial::operator*(const Polynomial& pol) const // Polynomial Multiplication
{
	int x; // degree of result
	int *coefs; // coefficients of result

	x = degree + pol.degree;
	coefs = new int[x + 1];

	for (int i = x; i >= 0; i--) {
		coefs[i] = 0;
	}

	for (int i = degree; i >= 0; i--) {
		for (int j = pol.degree; j >= 0; j--) {
			coefs[i + j] += coefficients[i] * pol.coefficients[j];
		}
	}
	return Polynomial(x, coefs);
}

std::ostream& operator<<(std::ostream& output, const Polynomial& pol) // << operator
{
	for (int i = pol.degree; i >= 0; i--) {
		if (pol.coefficients[i] == 1) {
			if (i == 0) output << pol.coefficients[i];
			else if (i == 1) output << "x" << " + ";
			else output << "x^" << i << " + ";
		}
		else if (pol.coefficients[i] == 0) {
			output << "";
		}
		else {
			if (i == 0) output << pol.coefficients[i];
			else if (i == 1) output << pol.coefficients[i] << "x" << " + ";
			else output << pol.coefficients[i] << "x^" << i << " + ";
		}
	}
	return output;
}
