#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

struct func{
    int& i;
    func(int& _i):i(_i){
        std::cout << "construct of func" << std::endl;
    }

    void operator()(){
        std::cout << "start of func()" << std::endl;
        for(unsigned j=0;j<1000000;++j){
            std::cout << "j:" << j << std::endl;
        }
    }
};

/// @brief 打印当前时分秒
void print_time(){
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream stream;
    stream << std::put_time(std::localtime(&in_time_t),"%Y-%m-%d %X");
    std::cout << "now is:" << stream.str() << std::endl;
}

void sleep_thread(){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "[thread-" << std::this_thread::get_id() << "] is waking up" << std::endl;
}

void loop_thread() {
    for (int i = 0; i < 10; i++) {
        std::cout << "[thread-" << std::this_thread::get_id() << "] print: " << i << std::endl;
    }
}

void f(int i,std::string const & s){
    std::cout << "i:"<< i << " s:" << s << std::endl;
}

void oops(){
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach(); // 分离父线程运行：父线程不等待此线程结束就结束了。

    std::cout << "joinable:" << my_thread.joinable() << std::endl;
}

class background_task{
    public:
        void operator()() const{ // 函数操作符：可以像使用函数一样，使用对象。
            std::cout << "function operator do task" << std::endl;
        }
};

void init(){
    std::cout << "[thread-" << std::this_thread::get_id() << "] is initing" << std::endl;
}

void worker(std::once_flag* flag){
    std::call_once(*flag,init);
}

int main(){
    // 测试：分离与等待
    //oops();
    print_time();
    std::thread t1(sleep_thread);
    std::thread t2(loop_thread);
    t1.join();  // 阻塞执行
    std::cout << "join finished" << std::endl;
    t2.detach(); // 立马执行，线程有可能在未调用detach之前就执行了
    print_time();

    // 测试：call_once、once_flag
    std::once_flag onceFlag;
    std::thread call_once_t1(worker,&onceFlag);
    std::thread call_once_t2(worker,&onceFlag);
    call_once_t1.join();
    call_once_t2.join();
    return 0;

    /*
    std::thread my_thread([](){
        std::cout << "my thread" << std::endl;
    });

    // my_thread.join(); // join: 主线程等待子线程执行完后，继续执行。
    my_thread.detach();

    // 线程传递参数
    std::thread param_thread(f,2,"hello");
    param_thread.join();
    
    std::cout << "end oops" << std::endl;

    background_task task;
    std::thread task_thread(task);
    task_thread.join();

    std::cout << "main func end" << std::endl;
    return 1;*/
}