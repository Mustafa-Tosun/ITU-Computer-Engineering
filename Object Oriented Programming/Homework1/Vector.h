// Mustafa TOSUN 150170055

#include <iostream>

class Vector
{
private:
	int dimension;
	int *magnitudes;
public:
	Vector(int dim, const int *mags); // Constructor
	Vector(const Vector& vec); // Copy Constructor
	~Vector() { delete[] magnitudes; } // Destructor
	Vector operator+(const Vector &vec) const; // Vector Addition
	int operator*(const Vector &vec) const; // Dot Product
	Vector operator*(const int scalar) const; // Scalar Multiplication
	friend std::ostream& operator<<(std::ostream& output, const Vector &vec); // << operator
	int getdimension() { return dimension; } // Getter for dimension
};

Vector::Vector(int dim = 0, const int *mags = 0) // Constructor
{
	dimension = dim;
	magnitudes = new int[dimension];
	int i;
	for (i = 0; i < dimension; i++) magnitudes[i] = 0;
	if (mags)
		for (i = 0; i < dimension; i++) magnitudes[i] = mags[i];
}

Vector::Vector(const Vector &vec) // Copy Constructor
{
	dimension = vec.dimension;
	magnitudes = new int[dimension];
	for (int i = dimension - 1; i >= 0; i--) {
		magnitudes[i] = vec.magnitudes[i];
	}
}

Vector Vector::operator+(const Vector &vec) const // Vector Addition
{
	int *mags;
	mags = new int[dimension];
	for (int i = 0; i < dimension; i++) {
		mags[i] = magnitudes[i] + vec.magnitudes[i];
	}
	return Vector(dimension, mags);
}

int Vector::operator*(const Vector &vec) const //  Dot Product
{
	int result=0;
	for (int i = 0; i < dimension; i++) {
		result += magnitudes[i] * vec.magnitudes[i];
	}
	return result;
}

Vector Vector::operator*(const int scalar) const // Scalar Multiplication
{
	int *mags;
	mags = new int[dimension];
	for (int i = 0; i < dimension; i++) {
		mags[i] = magnitudes[i] * scalar;
	}
	return Vector(dimension, mags);
}

std::ostream& operator<<(std::ostream& output, const Vector &vec) // << operator
{
	output << "(";
	for (int i = vec.dimension - 1; i >= 0; i--) {
		output << vec.magnitudes[i];
		if (i == 0) output << ")";
		else output << ", ";
	}
	return output;
}