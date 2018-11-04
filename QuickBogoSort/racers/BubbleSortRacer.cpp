#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>

#define MLD 1000000000.0

struct timespec tp0, tp1;

int a = 0;

int n = 500;


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

// bubblesort


static void BubbleSort(int* data, int x, int y)
{
    for (int n = y; n > 1; n--) {
        for (int i = x; i < n; i++) {
            a++;
            if (data[i] > data[i+1]) {
                int pom = data[i];
                data[i] = data[i+1];
                data[i+1] = pom;
            }
        }
    }
}

void fill_random(int* A, int n)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
        A[i] = rand()%(2048+1);
	}
}

int main(int argc, char** argv)
{
    double td;
    n = atoi(argv[1]);
    int data[n]; fill_random(data, n);
    printf("BubbleSort started!\n");

    Timer t;
	t.reset();
    BubbleSort(data, 0, n-1);
    td = t.elapsed();

    if (fmod(td,60.0) < 10.0) printf("BubbleSort finished after %02.0f:%02.0f:0%02.6f.\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    else printf("BubbleSort finished after %02.0f:%02.0f:%02.6f.\n", floor(td/3600.0), floor(fmod(td,3600.0)/60.0), fmod(td,60.0));
    //printf(" doing %i steps!\n", a-1);
	return 0;
}
