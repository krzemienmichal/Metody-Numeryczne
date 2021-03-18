#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float lagrangeInterpolation(float*, float*, float, int);
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

	float result = lagrangeInterpolation(x_array, y_array, searched_value, size);
	//system("cls");
	cout << "Result of interpolation for point:  " << searched_value << " is: " << result << endl;
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

float lagrangeInterpolation(float* x_array, float* y_array, float searched_value, int size)
{
	float value = 0.0;
	float l = 1.0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i) 
				continue;
			l *= ((searched_value - x_array[j]) / (x_array[i] - x_array[j]));
		}
		value += l * y_array[i];
		l = 1;
	}
	return value;
}
