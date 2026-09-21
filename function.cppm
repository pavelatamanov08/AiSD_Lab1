export module function;
import std;
import classes;

export template<typename T>
MyMatrix<T> SearchVectorX(MyMatrix<T>& A, MyMatrix<T>& b)
{
	if (A.GetRow() != A.GetColumn() || A.GetColumn() != b.GetRow() || b.GetColumn() != 1)
	{
		throw std::invalid_argument("Error! Invalid matrix size");
	}

	for (int k = 0; k < A.GetColumn(); ++k)
	{
		int maxIndex = k;
		for (int i = k + 1; i < A.GetRow(); ++i)
		{
			if (std::abs(A(i, k)) > std::abs(A(maxIndex, k)))
			{
				maxIndex = i;
			}
		}

		if (std::abs(A(maxIndex, k)) < 0.000001)
		{
			throw std::invalid_argument("Error! Matrix is degenerate!");
		}

		if (maxIndex != k)
		{
			for (int j = 0; j < A.GetColumn(); ++j)
			{
				std::swap(A(k, j), A(maxIndex, j));
			}
			std::swap(b(k, 0), b(maxIndex, 0));
		}

		for (int i = k + 1; i < A.GetRow(); ++i)
		{
			T mult = A(i, k) / A(k, k);
			for (int j = k; j < A.GetColumn(); ++j)
			{
				A(i, j) -= mult * A(k, j);
			}
			b(i, 0) -= mult * b(k, 0);
		}
	}

	MyMatrix<T> x(A.GetRow(), 1, T());
	for (int i = A.GetRow() - 1; i >= 0; --i)
	{
		T sum = b(i, 0);
		for (int j = i + 1; j < A.GetColumn(); ++j)
		{
			sum -= A(i, j) * x(j, 0);
		}
		x(i, 0) = sum / A(i, i);
	}
	return x;
}