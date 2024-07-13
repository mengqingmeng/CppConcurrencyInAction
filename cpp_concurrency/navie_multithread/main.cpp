#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

static const int MAX = 10e8;
static double sum = 0;
static std::mutex lock;

void worker(int min,int max){
    double temp_sum = 0.0;
    for(int i=min;i<=max;++i){
        temp_sum += sqrt(i); // 临界区，访问/修改共享数据的代码片段
    }

    lock.try_lock();
    sum += temp_sum;
    lock.unlock();
}

// 串行执行
void serial_task(){
    auto start_time = std::chrono::steady_clock::now();
    sum = 0;
    worker(0,MAX);
    auto end_time = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();
    std::cout << "serial task finish," << ms << " ms consumed,Result:" << sum << std::endl;
}

void concurrent_task(){
    auto start_time = std::chrono::steady_clock::now();

    unsigned concurrent_count = std::thread::hardware_concurrency();
    std::cout << "hardware_concurrency:" << concurrent_count << std::endl;

    int min = 0;
    sum = 0;

    std::vector<std::thread> threads;

    for(int i=0; i< concurrent_count;++i){
        int range = MAX / concurrent_count * (i + 1);
        threads.push_back(std::thread(worker,min,range));
        min = range + 1;
    }

    for(auto& t: threads){
        t.join();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count();
    std::cout << "concurrent task finish," << ms << " ms consumed,Result:" << sum << std::endl;
}

int main(){
    // 耗时：3439ms，sum=2.10819e+13
    //serial_task();

    // 耗时：930 ms，sum = 3.71081e+12（每次结果不同）；
    // 使用mutex后，耗时：611ms，sum = 2.10819e+13
    concurrent_task(); 

    return 0;
}