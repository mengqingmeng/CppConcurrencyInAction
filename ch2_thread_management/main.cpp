#include <iostream>
#include <thread>

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


int main(){
    // 测试：分离与等待
    oops();

    return 1;
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