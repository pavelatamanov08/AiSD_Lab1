import classes;
import function;
import std;

int main()
{
	MyMatrix<double> obj1(5, 6, -100, 100);
	std::cout << "First matrix:\n" << obj1;

	MyMatrix<double> obj2(5, 6, -100, 100);
	std::cout << "Second matrix:\n" << obj2;

	MyMatrix<double> obj3(6, 5, -100, 100);
	std::cout << "Third matrix:\n" << obj3;

	MyMatrix<double> obj4(obj1);
	std::cout << "Using copy constructor obj4(obj1):\n" << obj4;

	MyMatrix<double> obj5 = obj2;
	std::cout << "Using assignment operator (obj5 = obj2):\n" << obj5;

	MyMatrix<double> sum = obj1 + obj2;
	std::cout << "Sum of matrix(1 and 2):\n" << sum;

	MyMatrix<double> differense = obj1 - obj2;
	std::cout << "Differense of matrix(1 and 2):\n" << differense;

	MyMatrix<double> product = obj1 * obj3;
	std::cout << "Product of matrix(1 and 3):\n" << product;

	double multiplier = 5.18;
	MyMatrix<double> obj6 = obj1 * multiplier;
	std::cout << "Product of matrix and multiplier (obj1 * 5.18):\n" << obj6;
	MyMatrix<double> obj7 = multiplier * obj1;
	std::cout << "Product of multiplier and matrix (5.18 * obj1):\n" << obj7;

	double divider = 2.86;
	MyMatrix<double> obj8 = obj2 / divider;
	std::cout << "Quotient of matrix and divider (obj2 / 2.86):\n" << obj8;

	MyMatrix<double> SquareMatrix(5, 5, -100, 100);
	std::cout << "Square Matrix:\n" << SquareMatrix;
	std::cout << "Trase matrix (SquareMatrix):\n" << SquareMatrix.TraseMatrix() << "\n\n";

	std::cout << "comparison matrix (obj1 == obj2): ";
	if (obj1 == obj2) std::cout << "true\n";
	else std::cout << "false\n";

	std::cout << "comparison matrix (obj3 != obj4): ";
	if (obj3 != obj4) std::cout << "true\n\n";
	else std::cout << "false\n\n";

	MyMatrix<double> obj9(3, 4, 5.8);
	std::cout << "Matrix 9:\n" << obj9;
	std::cout << "Input index \"i\" and \"j\"\n";
	int i = 0;
	int j = 0;
	std::cout << "i: ";
	std::cin >> i;
	std::cout << "j: ";
	std::cin >> j;
	double number = 0;
	std::cout << "Input number for change: ";
	std::cin >> number;
	obj9(i, j) = number;
	std::cout << obj9;

	MyMatrix<double> A(4, 4, -5.0, 5.0);
	MyMatrix<double> b(4, 1, -5.0, 5.0);
	std::cout << "Search x: " << "A * x = b\n";
	std::cout << "Matrix A: \n" << A;
	std::cout << "Vector b: \n" << b;
	std::cout << "Matrix x: \n" << SearchVectorX(A, b);
}
