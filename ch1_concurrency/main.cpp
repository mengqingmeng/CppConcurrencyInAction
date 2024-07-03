#include <iostream>
#include <thread>

// 入口函数
void hello(){
    std::cout << "hello concurrency,thread id:"<< std::this_thread::get_id() << std::endl;
}

int main(){
    std::cout << "main begin,thread id:" << std::this_thread::get_id() << std::endl;
    
    // 创建新的线程
    std::thread t(hello);
    // 汇入主线程，等待t执行完成，再执行后面的代码
    t.join();

    std::cout << "main end,thread id:"<< std::this_thread::get_id() << std::endl;

    // 使用lambda运行线程
    std::thread t2([]{
        std::cout << "run thread2 in lambda,thread id:" << std::this_thread::get_id() << std::endl;
    });

    t2.join();

    std::cout << "main end,thread id:"<< std::this_thread::get_id() << std::endl;
    
    return 0;
}