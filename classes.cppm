export module classes;
import std;

export template<typename T>
class MyMatrix {
private:
	int _row = 0;
	int _column = 0;
	T* _matrix = nullptr;

	inline static const double epsilon = 0.000001;
	static bool comparison(float a, float b) { return std::abs(a - b) < epsilon; }
	static bool comparison(double a, double b) { return std::abs(a - b) < epsilon; }
	static bool comparison(int a, int b) { return a == b; }
	template<typename U>
	static bool comparison(const std::complex<U>& a, const std::complex<U>& b) { return a == b; }

	static void FillRandom(int* data, int size, int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(min, max);
		for (int i = 0; i < size; ++i)
		{
			data[i] = dist(gen);
		}
	}
	template<typename U>
	static void FillRandom(U* data, int size, U min, U max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<U> dist(min, max);
		for (int i = 0; i < size; ++i)
		{
			data[i] = dist(gen);
		}
	}
	template<typename U>
	static void FillRandom(std::complex<U>* data, int size, const std::complex<U>& min, const std::complex<U>& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<U> dist1(min.real(), max.real());
		std::uniform_real_distribution<U> dist2(min.imag(), max.imag());
		for (int i = 0; i < size; ++i)
		{
			data[i] = std::complex<U>(dist1(gen), dist2(gen));
		}
	}
public:
	MyMatrix(int r, int c, const T& m) : _row(r), _column(c), _matrix(new T[r * c])
	{
		if (r <= 0 || c <= 0)
		{
			throw std::invalid_argument("Error! Invalid value!");
		}

		for (int i = 0; i < r * c; ++i)
		{
			_matrix[i] = m;
		}
	}

	MyMatrix(int r, int c, const T& min, const T& max) : _row(r), _column(c), _matrix(new T[r * c])
	{
		if (r <= 0 || c <= 0)
		{
			throw std::invalid_argument("Error! Invalid value!");
		}
		FillRandom(_matrix, r * c, min, max);
	}

	~MyMatrix()
	{
		delete[] _matrix;
	}

	MyMatrix(const MyMatrix& other) : _row(other._row), _column(other._column), _matrix(new T[other._row * other._column])
	{
		for (int i = 0; i < other._row * other._column; ++i)
		{
			_matrix[i] = other._matrix[i];
		}
	}

	MyMatrix& operator=(const MyMatrix& other) 
	{
		if (this == &other) return *this;
		delete[] _matrix;
		_row = other._row;
		_column = other._column;
		_matrix = new T[_row * _column];
		for (int i = 0; i < _row * _column; ++i)
		{
			_matrix[i] = other._matrix[i];
		}
		return *this;
	}

	int GetRow() const { return _row; }
	int GetColumn() const { return _column; }

	T& operator()(int row, int column)
	{
		if (row < 0 || row >= _row || column < 0 || column >= _column)
		{
			throw std::out_of_range("Value out of range");
		}
		return _matrix[row * _column + column];
	}

	const T& operator()(int row, int column) const 
	{
		if (row < 0 || row >= _row || column < 0 || column >= _column)
		{
			throw std::out_of_range("Value out of range");
		}
		return _matrix[row * _column + column];
	}

	MyMatrix operator+(const MyMatrix& other) const 
	{
		if (_row != other._row || _column != other._column)
		{
			throw std::invalid_argument("Error! The matrix sizes are not equal.");
		}
		MyMatrix result = *this;
		for (int i = 0; i < _row * _column; ++i)
		{
			result._matrix[i] += other._matrix[i];
		}
		return result;
	}

	MyMatrix operator-(const MyMatrix& other) const 
	{
		if (_row != other._row || _column != other._column)
		{
			throw std::invalid_argument("Error! The matrix sizes are not equal.");
		}
		MyMatrix result = *this;
		for (int i = 0; i < _row * _column; ++i)
		{
			result._matrix[i] -= other._matrix[i];
		}
		return result;
	}

	MyMatrix operator*(const MyMatrix& other) const 
	{
		if (_column != other._row)
		{
			throw std::invalid_argument("Error! Invalid matrix size!");
		}
		MyMatrix result(_row, other._column, T());
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < other._column; ++j)
			{
				T sum = T();
				for (int t = 0; t < _column; ++t)
				{
					sum += _matrix[i * _column + t] * other._matrix[t * other._column + j];
				}
				result._matrix[i * other._column + j] = sum;
			}
		}
		return result;
	}

	MyMatrix operator*(const T& multiplier) const 
	{
		MyMatrix result = *this;
		for (int i = 0; i < _row * _column; ++i)
		{
			result._matrix[i] *= multiplier;
		}
		return result;
	}

	MyMatrix operator/(const T& divider) const 
	{
		if (divider == T())
		{
			throw std::invalid_argument("Error! Division by zero!");
		}
		MyMatrix result = *this;
		for (int i = 0; i < _row * _column; ++i)
		{
			result._matrix[i] /= divider;
		}
		return result;
	}

	bool operator==(const MyMatrix& other) const 
	{
		if (_row != other._row || _column != other._column) return false;
		for (int i = 0; i < _row * _column; ++i)
		{
			if (!comparison(_matrix[i], other._matrix[i])) return false;
		}
		return true;
	}

	bool operator!=(const MyMatrix& other) const 
	{
		return !(*this == other);
	}

	T TraseMatrix() const 
	{
		if (_row != _column)
		{
			throw std::invalid_argument("Error! Matrix is not square.");
		}
		T Trase = T();
		for (int i = 0; i < _column; ++i)
		{
			Trase += _matrix[i * _column + i];
		}
		return Trase;
	}
};

export template<typename T>
MyMatrix<T> operator*(const T& multiplier, const MyMatrix<T>& matrix) 
{
	return matrix * multiplier;
}

export template<typename T>
std::ostream& operator<<(std::ostream& os, const MyMatrix<T>& obj)
{
	for (int i = 0; i < obj.GetRow(); ++i) 
	{
		for (int j = 0; j < obj.GetColumn(); ++j)
		{
			os << obj(i, j) << "  ";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}