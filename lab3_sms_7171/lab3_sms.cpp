#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));
	long long n = rand() % 9 + 2;
	long long array[n][n];
	cout<<"Исходный массив"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			array[i][j] = rand() % 9 + 1;
			cout<<array[i][j]<<" ";
		}
		cout<<endl;
	}
	long long row;
        long long column;

	cout<<"Введите строку для удаления: ";
	cin>>row;
	cout<<"Введите столбец для удаления: ";
	cin>>column;
	long long *ptr_row = &array[row][0];
	long long *ptr_column = &array[0][column];
	long long *end_array = &array[n-1][n-1];
	long long *last_row = &array[n-1][0];
	long long *last_column = &array[0][n-1];
	long long m = column+1;
	long long k = n - 1;
/*	cout<<"Проверка: "<<endl;
	for (int i = 0; i < n-1; i++)
        {
                for (int j = 0; j < n-1; j++)
                {
			if (i < row)
				if (j < column) array[i][j]=array[i][j];
				else array[i][j]= array[i][j+1];
			else
				if (j < column) array[i][j] = array[i+1][j];
				else array[i][j] = array[i+1][j+1];
                }
                cout<<endl;
       }
*/
	asm(
		"mov $8, %%rax\n\t"
		"mulq %[n]\n\t"
		"mov %[ptr_row], %%rbx\n\t"
		"mov %%rbx, %%rcx\n\t"
		"cmp %%rbx, %[last_row]\n\t"
                "je column\n\t"
		"jmp loop_row\n\t"

		"loop_row:\n\t"
			"mov %%rbx, %%rcx\n\t"
			"add %%rax, %%rcx\n\t"
			"push (%%rcx)\n\t"
			"pop (%%rbx)\n\t"
			"cmp %%rcx, %[end_array]\n\t"
			"je column\n\t"
			"add $8, %%rbx\n\t"
			"jmp loop_row\n\t"

		"column:\n\t"
			"mov $8, %%rax\n\t"
			"mulq %[m]\n\t"
			"mov %[ptr_column], %%rbx\n\t"
			"mov %%rbx, %%rcx\n\t"
			"mov %[column], %%rdx\n\t"
			"cmp %%rbx, %[last_column]\n\t"
			"je end_asm\n\t"
			"jmp loop_column\n\t"

		"next:\n\t"
			"add %%rax, %%rbx\n\t"
			"mov %[column], %%rdx\n\t"
			"jmp loop_column\n\t"

		"loop_column:\n\t"
			"cmp %[k], %%rdx\n\t"
			"je next\n\t"

			"mov %%rbx, %%rcx\n\t"
                        "add $8, %%rcx\n\t"
                        "push (%%rcx)\n\t"
                        "pop (%%rbx)\n\t"
                        "cmp %%rcx, %[end_array]\n\t"
                        "je end_asm\n\t"
			"add $8, %%rbx\n\t"
			"inc %%rdx\n\t"
                        "jmp loop_column\n\t"

		"end_asm:\n\t"
		:
		:[k]"m"(k), [m]"m"(m), [column]"m"(column),[last_row]"m"(last_row), [ptr_row]"m"(ptr_row), [end_array]"m"(end_array), [n]"m"(n), [last_column]"m"(last_column), [ptr_column]"m"(ptr_column)
		:"%rax", "%rbx", "%rcx", "%rdx"
		);
	n = n - 1;
	cout<<"Преобразованный массив"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout<<array[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
