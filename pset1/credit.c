#include <stdio.h>

int main (void)
{
	// paypal dummy cards https://developer.paypal.com/docs/payflow/payflow-pro/payflow-pro-testing/#credit-card-numbers-for-testing
	
	long int creditcard;
	int cardarray[16];
	int sum = 0;
	char type = '\0'; // m is MASTERCARD, v is VISA, a is AMEX, o is OTHER
	
	printf("Credit Card Number: ");
	scanf("%li", &creditcard);
	
	// init array
	long int duplicate = creditcard;
	for (int i = 0; i < 16; i++)
	{
		cardarray[i] = duplicate % 10;
		duplicate /= 10;
	}
	
	int counter = 0;
	duplicate = creditcard;
	while (duplicate != 0)
	{
		counter++;
		duplicate /= 10;
	}
	
	duplicate = creditcard;
	while (duplicate != 0) {
		if ((duplicate == 34 || duplicate == 37) && counter == 15)
		{
			type = 'a'; // amex
		}
		else if (((duplicate >= 2221 && duplicate <= 2720) || (duplicate >= 50 && duplicate <= 69)) && counter == 16)
		{
			type = 'm'; // mastercard
		}
		else if (duplicate >= 40 && duplicate <= 49 && (counter == 13 || counter == 16))
		{
			type = 'v'; // visa
		}
		else if (type == '\0')
		{
			type = 'o'; // other
		}
		duplicate /= 10;
	}
	
	// checksum
	for (int i = 1; i < 16; i+=2)
	{
		cardarray[i] *= 2;
	}
	for (int i = 0; i < 16; i++)
	{
		if (cardarray[i] < 10)
		{
			sum += cardarray[i];
		}
		else
		{
			sum += (cardarray[i] % 10);
			sum += cardarray[i]/10;
		}
	}
	
	if (sum % 10 == 0)
	{
		printf("VALID\nCARD TYPE : ");
		if (type == 'a')
		{
			printf("AMEX\n");
		}
		else if (type == 'm')
		{
			printf("MASTERCARD/MAESTRO\n");
		}
		else if (type == 'v')
		{
			printf("VISA\n");
		} 
		else if (type == 'o')
		{
			printf("OTHER\n");
		}
		else
		{
			printf("program error please call 911.\n");
		}
	} else
	{
		printf("INVALID\n");
	}
	
	return 0;
}