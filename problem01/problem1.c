/*
	EECS 348 Lab 5 Problem 1
	Name: Theodore Athon
	ID: 3117304
	Creation Date: 10/11/2023
	This lab prints a sales report based on a file with 12 lines of sales data in it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sortFloats(const void* a, const void* b) {
	if(*(const float*)a < *(const float*)b)
		return -1;
	return *(const float*)a > *(const float*)b;
}

int main() {
	char filename[128];
	
	char months[12][10] = {
		"January",
		"Februrary",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	printf("Enter sales file name: ");
	scanf("%123s",filename);
	
	FILE *sales;
	sales = fopen(filename,"r");

	if (sales == NULL) {
		printf("Cannot open file!\n");
		return 1;
	}

	/* Print the intial sales report for each month */

	int bufferLength = 15; // maximum length of the number
	char buffer[bufferLength]; // the string that will be continuously overwritten during printing
	int month = 0; // first month

	double minimum = 99999999; // minimum
	double maximum = 0; // maximum
	double sum = 0; // sum of all sales (will be used for average later)
	double current = 0;
	int minMonth = 0;
	int maxMonth = 0;

	float salesArray[12];

	// Print header line
	printf("\n%s\n\n", "Monthly Sales Report for 2023:");
	printf("%10s %15s\n\n", "Month", "Sales");

	// Loop through file and print the sales along with the month name
	while(fgets(buffer, bufferLength, sales)) {
		printf("%10s %15s", months[month], buffer);

		current = atof(buffer);

		salesArray[month] = current;

		if (current < minimum) {
			minimum = current;
			minMonth = month;
		}

		if (current > maximum) {
			maximum = current;
			maxMonth = month;
		}

		sum = sum + current;
		month++;
	}
	printf("%s", "\n\n"); // new line for formatting

	printf("%s\n\n", "Sales Summary: ");
	printf("%15s %.2f (%s)\n", "Minimum Sales: ", minimum, months[minMonth]);
	printf("%15s %.2f (%s)\n", "Maximum Sales: ", maximum, months[maxMonth]);
	printf("%15s %.2f\n", "Average Sales: ", sum/12);

	// print 6 month sales averages
	printf("\n%s\n", "Six-Month Moving Average Report:");

	int startingMonth = 0;
	for (startingMonth; startingMonth <= 6; startingMonth++) {
		float sum = 0;
		int currentMonth = startingMonth;
		for (currentMonth; currentMonth <= startingMonth + 5; currentMonth++) {
			sum = sum + salesArray[currentMonth];
		}
		float average = sum/6;
		printf("%-10s %1s %-10s %.2f\n", months[startingMonth], "-", months[currentMonth-1], average);
	}
	printf("\n");

	// int numElements = sizeof(salesArray) / sizeof(salesArray[0]);
	// qsort(salesArray, numElements, sizeof(float), sortFloats);

	int monthNum[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12 - i - 1; j++)
		{
			if (salesArray[j] > salesArray[j + 1])
			{
				float temp = salesArray[j + 1];	//swaping element
				int tempMonth = monthNum[j + 1];
				salesArray[j + 1] = salesArray[j];
				salesArray[j] = temp;
				monthNum[j+1] = monthNum[j];
				monthNum[j] = tempMonth;
			}
		}
	}

	printf("%s\n", "Sales Report (Highest to Lowest):");
	printf("%-10s %s\n\n", "Month", "Sales");

	for (int i=11; i>=0; i--) {
		printf("%-10s %.2f\n", salesArray[i], months[monthNum[i]]);
	}

	return 0;
}