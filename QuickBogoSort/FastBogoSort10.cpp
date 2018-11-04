#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#define MLD 1000000000.0

struct timespec tp0, tp1;

int a = 0;

int n = 10; // losowe dane - liczba elementow
//int n = 10; int data[10] = {2, 1, 3, 7, 1, 4, 8, 8, 5, 6}; // przykladowe dane

// stoper

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

// fast bogosort

static bool is_sorted(int* data, int x, int y)
{
	while (++x <= y)
		if (data[x] < data[x - 1]) return false;

	return true;
}

static int extract_min(int* data, int x, int y)
{
    int s = x;
    while (++x <= y)
		if (data[x] < data[s]) s = x;
    return s;
}

static void shuffle(int* data, int x, int y)
{
	int temp, rnd;
	for (int i = x; i <= y; ++i)
	{
		srand(time(NULL));		
		rnd = x + rand()%(y-x+1);
		temp = data[i];
		data[i] = data[rnd];
		data[rnd] = temp;
	}
}

static void FastBogoSort(int* data, int x, int y)
{
    printf("%12i|\t", a);
    for (int i = 0; i < n; i++) printf("%7i\t", data[i]);
    //printf("\n");
    a++;
    if (is_sorted(data, x, y)) {
        printf("    sorted\n");
        return;
    }
    else {
        if (x == extract_min(data, x, y)) {
            printf("    found\n");
            FastBogoSort(data, x+1, y);
        } else {
            printf("    shuffle\n");
            shuffle(data, x, y);
            FastBogoSort(data, x, y);
        }
    }
}

void fill_random(int* A, int n)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++)
	{
		//A[i] = rand()%(2048+1) - 1024;
        A[i] = rand()%(2048+1);
	}
}

int main()
{
    double td;
    
    int data[n]; fill_random(data, n); // dla przykladowych danych zakomentowac

    printf("Algorithm   | QUICK BOGOSORT\n");
    printf("Author      | RooiGevaar19\n");
	printf("Table       |  \t");
	for (int i = 0; i < n; i++) printf("%7i\t", data[i]);
	getchar();
    printf("------------+----------"); for (int i = 1; i < n; i++) printf("--------"); printf("\n");

    Timer t;
	t.reset();
    FastBogoSort(data, 0, n-1);
    td = t.elapsed();

    printf("------------+----------"); for (int i = 1; i < n; i++) printf("--------"); printf("\n");
    printf("Result      |  \t");
	for (int i = 0; i < n; i++) printf("%7i\t", data[i]);
	printf("\n");
	if (fmod(td,60.0) < 10.0) printf("Time        |          %02.0f:%02.0f:0%02.6f\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    else printf("Time        |          %02.0f:%02.0f:%02.6f\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    printf("Steps       |%18i\n", a-1);
	return 0;
}
