#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float newtonInterpolation(float*, float*, int, float);
void loadData(float*, float*, string, int);
void fillArray(float*, int);

int main()
{
	int size = 0;
	float searched_value = 0;

	cout << "Amount of interpolation knots: ";
	cin >> size;
	cout << endl;
	float* x_array = new float[size];
	float* y_array = new float[size];

	fillArray(x_array, size);
	fillArray(y_array, size);

	loadData(x_array, y_array, "file.txt", size);

	cout << "Point: ";
	cin >> searched_value;
	cout << endl;

	while (true)
	{
		if (searched_value < x_array[0] || searched_value > x_array[size - 1])
		{
			//system("cls");
			cout << "Point: " << searched_value << " is out of range" << endl;
			cout << "Input correct point: ";
			cin >> searched_value;
			cout << endl;
		}
		else
			break;
	}

	float result = newtonInterpolation(x_array, y_array, size, searched_value);
	cout << "Result of Newton Interpolation for point: " << searched_value <<  " is: " << result << endl;
	return 0;
}

void fillArray(float* arr, int size)
{
	for (int i = 0; i < size; i++)
		arr[i] = 0;
}
void loadData(float* x_array, float* y_array, string FileName, int size)
{
	fstream file;
	file.open(FileName, ios::in);
	if (file.good())
	{
		int i = 0;
		while (!file.eof())
		{
			string x;
			string y;
			getline(file, x, ',');
			getline(file, y);
			x_array[i] = stof(x);
			y_array[i] = stof(y);
			i++;
		}
	}
	file.close();
}

float newtonInterpolation(float* x_array, float* y_array, int size, float searched_value)
{
	float** b_array = new float* [size];
	for (int i = 0; i < size; i++)
	{
		b_array[i] = new float[i + 1];
		b_array[i][0] = y_array[i];
	}

	for (int i = 0; i < size; i++)
		for (int j = 1; j <= i; j++)
			b_array[i][j] = (b_array[i][j - 1] - b_array[i - 1][j - 1]) / (x_array[i] - x_array[i - j]);

	float* result = new float[size];
	for (int i = 0; i < size; i++)
		result[i] = b_array[i][i];

	for (int i = 0; i < size; i++)
		delete[] b_array[i];

	delete[] b_array;
	
	float value = 0;

	for (int i = 0; i < size; i++)
	{
		float temp = result[i];
		for (int j = 0; j < i; j++)
		{
			temp *= searched_value - x_array[j];
		}
		value += temp;
	}
	
	delete[] result;

	return value;
}