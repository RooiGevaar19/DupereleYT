#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>

int count_test = 15;

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

static unsigned long long BogoSort(int* data, int count)
{
    unsigned long long step = 0;
    while (!IsSorted(data, count))
	{
		Shuffle(data, count);
        step++;
	}
    return step;
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
	int data[n];

	printf("Algorithm   | CLASSIC BOGOSORT (Comparison)\n");
	printf("Author      | RooiGevaar19");
	getchar();
	printf("------------+----------------------------------------------\n");
    printf(" n          | Time               | Number of steps\n");
    printf("------------+--------------------+-------------------------\n");

    for (int j = 1; j <= n; j++) {
        fill_random(data, j);
        Timer t;
	    t.reset();
	    unsigned long long step = BogoSort(data, j);
	    double td = t.elapsed();
        setlocale(LC_ALL,"");
        if (fmod(td,60.0) < 10.0) printf("%12i| %02.0f:%02.0f:0%02.9f |%'25llu\n", j, floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0), step);
        else printf("%12i| %02.0f:%02.0f:%02.9f |%'25llu\n", j, floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0), step);
    }
	return 0;
}
