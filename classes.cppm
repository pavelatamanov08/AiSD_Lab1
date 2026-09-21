export module classes;
import std;

export template<typename T>
class MyMatrix {
private:
	int _row = 0;
	int _column = 0;
	T* _matrix = nullptr;
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

		std::random_device rd;
		std::mt19937 gen(rd());

		if constexpr (std::is_same_v<T, int>)
		{
			std::uniform_int_distribution<T> dist(min, max);
			for (int i = 0; i < r * c; ++i)
			{
				_matrix[i] = dist(gen);
			}
		}

		else if constexpr (std::is_same_v<T, float>)
		{
			std::uniform_real_distribution<T> dist(min, max);
			for (int i = 0; i < r * c; ++i)
			{
				_matrix[i] = dist(gen);
			}
		}

		else if constexpr (std::is_same_v<T, double>)
		{
			std::uniform_real_distribution<T> dist(min, max);
			for (int i = 0; i < r * c; ++i)
			{
				_matrix[i] = dist(gen);
			}
		}

		else if constexpr (std::is_same_v<T, std::complex<float>> || std::is_same_v<T, std::complex<double>>)
		{
			using U = decltype(min.real());
			std::uniform_real_distribution<U> dist(min.real(), max.real());
			for (int i = 0; i < r * c; ++i)
			{
				_matrix[i] = T(dist(gen), dist(gen));
			}
		}
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
}