#include <iostream>

using namespace std;

int main()
{
	unsigned int arr[] = {117, 200, 5, 30, 56};
	int r = 0;
	unsigned int t = 107;
	for (int i = 0; i < 5; i++)
	{
		cout<<"Исходный элемент массива: "<<arr[i]<<endl;
		arr[i] = arr[i]|t;
		cout<<"Преобразованный элемент: "<<arr[i]<<endl;
		if (arr[i]<128) r++;
	}
	cout<<"Число элементов, меньших 128: "<<r<<endl;
}

