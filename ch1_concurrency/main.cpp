#include <iostream>
#include <thread>

void hello(){
    std::cout << "hello concurrency:"<< std::this_thread::get_id() << std::endl;
}
int main(){
    std::cout << "hello begin:" << std::this_thread::get_id() << std::endl;
    std::thread t(hello);
    t.join();
    std::cout << "hello end:"<< std::this_thread::get_id() << std::endl;
    return 1;
}