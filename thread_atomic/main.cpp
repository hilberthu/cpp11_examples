#include <iostream>
#include <atomic>
#include <vector>
#include <functional>
#include <thread>

std::atomic<int> i;
const int count = 100000;
const int n = 10;

void add()
{
    for (int j = 0; j < count; ++j)
        i++;
}

int main()
{
    i.store(0);
    std::vector<std::thread> workers;
    std::cout << "start " << n << " workers, "
              << "every woker inc " << count  << " times" << std::endl;

    for (int j = 0; j < n; ++j)
        workers.push_back(std::move(std::thread(add)));

    for (auto & w : workers)
        w.join();

    std::cout << "workers end "
              << "finally i is " << i << std::endl;

    if (i == n * count)
        std::cout << "i++ test passed!" << std::endl;
    else
        std::cout << "i++ test failed!" << std::endl;

    return 0;
}
