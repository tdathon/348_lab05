/*
	EECS 348 Lab 5 Problem 2
	Name: Theodore Athon
	ID: 3117304
	Creation Date: 10/11/2023
	This lab prints all possible score combinations for an NFL game.
*/
#include <stdio.h>
#include <stdbool.h>

void scoreCount (int score) {
	/*
		This function loops through every possible score combination and prints the ones that exist
		Originally I was going to use recursion to do this but it looped through every combination regardless of order,
		but it would crash at higher score values, so I had to use nested loops instead.
	*/
	for (int eight = 0; (eight * 8) <= score; eight++) {
		for (int seven = 0; (seven * 7) <= score; seven++) {
			for (int touchdown = 0; (touchdown * 6) <= score; touchdown++) {
				for (int fieldGoal = 0; (fieldGoal * 3) <= score; fieldGoal++) {
					for (int safety = 0; (safety * 2) <= score; safety++) {
						if (((eight * 8) + (seven * 7) + (touchdown * 6) + (fieldGoal * 3) + (safety * 2)) == score) {
							printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", eight, seven, touchdown, fieldGoal, safety);
						}
					}
				}
			}
		}
	}
}

int main() {
	int score;
	while (1) {
		printf("Enter a score (enter 1 or 0 to STOP): ");
		scanf("%d", &score);

		if (score < 2) break; // if score is less than 2 break the loop

		printf("Possible combinations of scoring plays:\n");

		scoreCount(score);
		printf("\n");
	}

	return 0;
}
