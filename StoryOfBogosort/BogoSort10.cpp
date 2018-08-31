#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>

int step = 0;
int count_test = 10;

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
            (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};

static bool IsSorted(int* data, int count)
{
	while (--count >= 1)
		if (data[count] < data[count - 1]) return false;

	return true;
}

static void Shuffle(int* data, int count)
{
	int temp, rnd;
	for (int i = 0; i < count; ++i)
	{		
		rnd = rand() % count;
		temp = data[i];
		data[i] = data[rnd];
		data[rnd] = temp;
	}
}

static void BogoSort(int* data, int count)
{
	while (!IsSorted(data, count))
	{
		Shuffle(data, count);
		step++;
		printf("%12i|\t", step);
		for (int i = 0; i < count; i++) printf("%7i\t", data[i]);
		printf("\n");
	}
}

void fill_random(int* A, int n)
{
	int i;	
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		A[i] = rand()%(2048+1);
	}
}

int main()
{
	int n = count_test;
	double td;	
	int data[n];
	

	fill_random(data, n);
	printf("Algorithm   | CLASSIC BOGOSORT\n");
	printf("Author      | RooiGevaar19\n");
	printf("Table       |  \t");
	for (int i = 0; i < n; i++) printf("%7i\t", data[i]);
	getchar();
	printf("------------+----------"); for (int i = 1; i < n; i++) printf("--------"); printf("\n");

	Timer t;
	t.reset();
	BogoSort(data, n);
	td = t.elapsed();

	printf("------------+----------"); for (int i = 1; i < n; i++) printf("--------"); printf("\n");
    	printf("Result      |  \t");
	for (int i = 0; i < n; i++) printf("%7i\t", data[i]);
	printf("\n");
	if (fmod(td,60.0) < 10.0) printf("Time        |          %02.0f:%02.0f:0%02.6f\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    else printf("Time        |          %02.0f:%02.0f:%02.6f\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    printf("Steps       |%18i\n", step);
	return 0;
}
