#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>

#define NUMBER_LIMIT 300
int arr[NUMBER_LIMIT];
static size_t firstThreadCounter = 0, secondThreadCounter = 0;
std::mutex mtx;

void firstThread()
{

    for (size_t i = 0; i < 60; i++)
    {
        for (size_t i = 0; i < 5; i++)
        {
            //timer
            std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();

            mtx.lock();
            arr[firstThreadCounter] = rand();
            firstThreadCounter++;
            mtx.unlock();

            //timer
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            std::chrono::milliseconds md = std::chrono::milliseconds(200) - std::chrono::duration_cast<std::chrono::milliseconds>(duration);
            std::this_thread::sleep_for(md);
        }
    }

}


void secondThread()
{

    for (size_t i = 0; i < NUMBER_LIMIT; i++)
    {
        //timer
        auto start = std::chrono::high_resolution_clock::now();

        mtx.lock();
        std::cout << arr[secondThreadCounter] << '\t';
        secondThreadCounter++;
        mtx.unlock();

        //timer
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        std::chrono::milliseconds md = std::chrono::milliseconds(1000) - std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        std::this_thread::sleep_for(md);
    }

}

int main()
{

    srand(9);

    std::thread th(firstThread);
    std::thread th2(secondThread);

    th.join();
    th2.join();

    std::cout << '\n';
    for (size_t i = 0; i < 30; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            std::cout << arr[i * 10 + j] << '\t';
        }
        std::cout << '\n';
    }


    return 0;
}