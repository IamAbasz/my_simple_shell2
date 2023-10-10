/**
 *  * main - Entry point of the program
 *   *
 *    * Return: Always 0 (Success)
 *     */
int main(void)
{
	    int number1 = 10;
	        int number2 = 20;
		    int sum;

		        sum = add_numbers(number1, number2);
			    print_sum(sum);

			        return 0;
}

/**
 *  * add_numbers - Adds two numbers
 *   * @a: First number
 *    * @b: Second number
 *     *
 *      * Return: The sum of the two numbers
 *       */
int add_numbers(int a, int b)
{
	    return a + b;
}

/**
 *  * print_sum - Prints the sum of two numbers
 *   * @sum: The sum of the two numbers
 *    */
void print_sum(int sum)
{
	    printf("The sum is: %d\n", sum);
}
