#include <iostream>

int* subAbs(int* a, int* b, int n)
{
	int c = 0;
	int* value = new int[n + 2];
	*(value + n - 1) = 0;
	for (int i = 0; i <= n - 2; i++)
	{
		*(value + i) = (*(a + i) - *(b + i) + c) % 2;
		if (*(value + i) < 0)
		{
			*(value + i) = -(*(value + i));
			c = -1;
		}
		else
		{
			c = 0;
		}
	}
	for (int i = n-2; i >= 0; i--)
	{
		std::cout << *(value + i);
	}
	std::cout << "v" << "\t";
	return value;
}

int* gcd(int* a, int* b, int n)
{
	bool f = false;
	while (f == false)
	{
		int i;
		for (i = n - 2; i >= 0; i--)	//so sánh hai số để thực hiện phép trừ
		{
			if (*(a + i) > * (b + i))
			{
				a = subAbs(a, b, n);
				break;
			}
			else if (*(b + i) > * (a + i))
			{
				b = subAbs(b, a, n);
				break;
			}
		}
		if (i == -1)
		{
			f = true;
		}
	}
	return a;
}

void main()
{
	int* a = new int[8];
	for (int i = 0; i < 4; i++)
	{
		*(a + i) = 1;
	}
	for (int i = 3; i >= 0; i--)
	{
		std::cout << *(a + i);
	}
	std::cout << "a" << std::endl;
	int* b = new int[4];
	for (int i = 0; i < 4; i++)
	{
		*(b + i) = 1;
	}
	*(b + 2) = 0;
	for (int i = 3; i >= 0; i--)
	{
		std::cout << *(b + i);
	}
	std::cout << "b" << std::endl;
	int *v = gcd(a, b, 4);
	for (int i = 0; i < 3; i++)
	{
		std::cout << *(v + i);
	}
}