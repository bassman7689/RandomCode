#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int _collatz(long int num, int count)
{
	if(num == 1)
	{
		return count;
	}
	else if(num & 1)
	{
		num = num * 3 + 1;
		count++;
	} else {
		num = num / 2; 
		count++;
	}

	return _collatz(num, count);
}	

long double collatz(long int num)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	int count = _collatz(num, 0);
	gettimeofday(&end, NULL);
	return end.tv_usec - start.tv_usec;
}

long double collatz_loop(long int num)
{
	int count = 0;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	while(num != 1) {
		if (num & 1)
		{
			num = num + (num / 2) + 1;
			count+=2;
		} else {
			num = num / 2; 
			count++;
		}
	}
	gettimeofday(&end, NULL);
	return end.tv_usec - start.tv_usec;
}

long double collatz_for(long int num)
{
	int count = 0;
	struct timeval start, end;
	gettimeofday(&start, NULL);
	for(;num != 1; num = (num & 1 ? num * 3 + 1 : num / 2))
		count++;
	gettimeofday(&end, NULL);
	return end.tv_usec - start.tv_usec;
}

void usage(char *argv[])
{
	printf("Usage: %s <number>\n", argv[0]);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		usage(argv);
		exit(1);
	}

	long long int num;
	char * endptr;
	num = strtoll(argv[1], &endptr, 10);

	if (argv[1] == endptr || num <= 0)
	{
		printf("Error: invalid number passed. Must be a non-zero positive integer.\n");
		usage(argv);
		exit(1);
	}

	printf("Input: %lld\n", num); 

	int count;
	long double average = 0;
	int number_of_runs = 50000;
	for(count = 1; count <= number_of_runs; count++)
	{
		long double new = collatz(num);
		average = average + (new - average)/count;
	}
	printf("collatz: average time in microseconds: %Lf\n", average);

	// average = 0;
	// for(count = 1; count <= number_of_runs; count++)
	// {
	// 	long double new = collatz_loop(num);
	// 	average = average + (new - average)/count;
	// }
	// printf("collatz_loop: average time in microseconds: %Lf\n", average);

	average = 0;
	for(count = 1; count <= number_of_runs; count++)
	{
		long double new = collatz_for(num);
		average = average + (new - average)/count;
	}
	printf("collatz_for: average time in microseconds: %Lf\n", average);
}
