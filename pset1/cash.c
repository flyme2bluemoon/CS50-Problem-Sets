#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	double amount = 12.48;
	
	bool coins[7] = {1, 1, 0, 1, 1, 1, 1}; // toonie, loonie, half-dollar, quarter, dime, nickel, penny
	int coinsused[7] = {0, 0, 0, 0, 0, 0, 0};
	
	while (amount >= 2)
	{
		coinsused[0]++;
		amount-=2;
	}
	while (amount >= 1)
	{
		coinsused[1]++;
		amount-=1;
	}
	while (amount >= 0.5)
	{
		coinsused[2]++;
		amount-=0.5;
	}
	while (amount >= 0.25)
	{
		coinsused[3]++;
		amount-=0.25;
	}
	while (amount >= 0.10)
	{
		coinsused[4]++;
		amount-=0.10;
	}
	while (amount >= 0.05)
	{
		coinsused[5]++;
		amount-=0.05;
	}
	while (amount >= 0.01)
	{
		coinsused[6]++;
		amount-=0.01;
	}
	
	for (int i = 0; i < 7; i++)
	{
		printf("%d\n", coinsused[i]);
	}
	
	return 0;
}