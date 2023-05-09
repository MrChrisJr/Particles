#include "Matrices.h"

using namespace std;
//Most of this is pulled from M04 Assignment (Matrices)
namespace Matrices {

	Matrix::Matrix(int _rows; int _cols)
	{
		// Creating the ints for rows and cols based on constructor
		rows = _rows;
		cols = _cols;
		// Resizes Vector of Vectors to be rows # wide
		a.resize(rows);
		// Loops through Vector to resize each independent vector to be columns wide
		for (int i = 0; i < rows; ++i)
		{
			a.at(i).resize(cols);
			// Sets each item within vector to be set as 0 to initialize
			for (int j = 0; j < cols; ++j)
			{
				a(i, j) = 0;
			}
		}
	}

	// Matrix Addition : Requires both matrices to be the same dimensions
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix retMatrix(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); ++i)
		{
			for (int j = 0; j < a.getCols() ++j)
			{
				retMatrix(i, j) = a(i, j) + b(i, j);
			}
		}
		return retMatrix;
	}

	// Matrix multiplication : Requires first Cols to be equal to second's rows
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix retMatrix(a.getRows(), b.getCols());
		for (int a_row = 0; a_row < a.getRows(); ++a_row)
		{
			for (int b_col = 0; b_col < b.getCols(); ++b_col)
			{
				for (int m_term = 0; m_term < a.getCols(); ++m_term)
				{
					retMatrix(a_row, b_col) += a(a_row, m_term) * b(m_term, b_col);
				}
			}
		}
		return retMatrix;
	}

	// Equivalency: Returns a bool if both matrices are close enough to equal (Absolute value of difference of Doubles)
	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) return false;

		for (int i = 0; i < a.getRows(); ++i)
		{
			for (int j = 0; j < a.getCols(); ++j)
			{
				if (abs(a(i, j) - b(i, j)) > 0.001) return false;
			}
		}
		return true;
	}

	// Opposite of Equivalency, returns the negated equivalency test
	bool operator!=(const Matrix& a, const Matrix& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); ++i)
		{
			for (int j = 0; j < a.getCols(); ++j)
			{
				os << setw(15) << a(i, j) << " ";
			}
			os << endl;
		}
		return os;
	}
}
RotationMatrix::RotationMatrix(double theta) : Matrix::Matrix(2, 2)
{
	a(0, 0) = cos(theta);
	a(0, 1) = sin(theta);
	a(1, 0) = 0 - a(0, 1);
	a(1, 1) = a(0, 0);
}

ScalingMatrix::ScalingMatrix(double scale) : Matrix::Matrix(2, 2)
{
	a(0, 0) = scale;
	a(1, 1) = scale;
}

TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols): Matrix::Matrix(2, nCols) 
{
	for (int i = 0; i < nCols; ++i)
	{
		a(i, 0) = xShift;
		a(i, 1) = yShift;
	}
}
