#include <iostream>
#include <thread>
#include <chrono>

const int n = 100;
const int k = 50;
const int t = 20;
int buffer[n];
int next_in = 0;
int next_out = 0;


void producer()
{
    while (1) {
        int k1 = rand() % k;
        for (int i = 0; i < k1; i++) {
            buffer[(next_in + i) % n] += 1;
        }
        next_in = (next_in + k1) % n;
        int t1 = rand() % t;
        std::this_thread::sleep_for(std::chrono::seconds(t1));
    }
}

void consumer()
{
    while (1)
    {
        bool race = false;
        int t2 = rand() % t;
        std::this_thread::sleep_for(std::chrono::seconds(t2));
        int k2 = rand() % k;
        int data;
        for (int i = 0; i < k2; i++) {
            data = buffer[(next_out) % n];
            if (data > 1 || data == 0) {
                std::cout << "Race condition meet, Data: " << data << std::endl;
                race = true;
                break;
            }
            buffer[(next_out) % n] = 0;
            next_out = (next_out + 1) % n;
        }
        if (race)
            break;
    }
}


int main()
{
    std::cout << "N: " << n << " K: " << k << " T: " << t << std::endl;

    for (int i = 0; i < n; i++) {
        buffer[i] = 0;
    }

    std::thread p = std::thread(producer);
    std::thread c = std::thread(consumer);

    std::cout << "executing\n";

    p.join();
    c.join();

    return 0;
}