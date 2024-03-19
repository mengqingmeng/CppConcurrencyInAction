#include <iostream>
#include <thread>

void hello(){
    std::cout << "hello concurrency,thread id:"<< std::this_thread::get_id() << std::endl;
}
int main(){
    std::cout << "main begin,thread id:" << std::this_thread::get_id() << std::endl;
    
    std::thread t(hello);
    t.join();

    std::cout << "main end,thread id:"<< std::this_thread::get_id() << std::endl;
    return 1;
}