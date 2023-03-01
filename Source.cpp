/*
the single machine version of the pizza calculator. later I will make the multi machine server and the multi machine client

Pizza calculated by etienne chamberlain
*/
/* the plan for the pizza calculator

what needs calculating
pizza diameter in inches raw input the program assumes you are making a circular pizza
pizza radius is half the pizza diameter
pi is 3.14159 in this application so dont order a pizza too big or accuracy will be lost
pizza radius squared times pi equals pizza area in square inches

next is the pizza price in dollars and cents
pizza price is a dollars and cents value input as raw input
warning the price of the pizza can include micropennies if you accidentally put three or more digits in cents
pizza deal is the pizza area divided by the pizza price


the next step:
error handling. sometime after that socket code
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
float pizza_calculation(float pizza_diameter)
{
	float pizza_radius = (pizza_diameter / 2);
	float pi = 3.14159;
	float pizza_area = (pizza_radius * pizza_radius) * pi;
	return pizza_area;
}

float price_per_square_inch(float dollar_and_cents_price, float area_sq_inch)
{
	float per_square_inch_exact = dollar_and_cents_price / area_sq_inch;
	return per_square_inch_exact;
}

int main(void)
{
	float pizza_diameter = 0;

//pasted code that we will try to work with
	char input[100];



/*	int i;

	printf("Enter input: ");
	fgets(input, sizeof(input), stdin);

	for (i = 0; input[i] != '\0'; i++) {
		if (isalpha(input[i])) {
			printf("Invalid input: Contains letters\n");
			return 1;
		}
*/
	while (pizza_diameter <= 0)
	{


		printf("input the diameter of your pizza in inches: ");

		scanf_s("%s", input, (unsigned)_countof(input));
		sscanf_s(input, "%f", &pizza_diameter);
	
	}

	float Calculated_pizza_area = pizza_calculation(pizza_diameter);
	printf("your pizza is %f square inches \n", Calculated_pizza_area);


	float pizza_price = -1;
	
	
	while (pizza_price < 0)
	{

		printf_s("please input the price: ");
		scanf_s("%s", input, (unsigned)_countof(input));
		sscanf_s(input, "%f", &pizza_price);
	}
	
	float spending_per_square_inch = price_per_square_inch(pizza_price, Calculated_pizza_area);
	printf("the amount of money you are paying per square inch of pizza is $%f \n", spending_per_square_inch);

	int no_input_no_close = 0;
	scanf_s("%d", &no_input_no_close);

	return(0);

}