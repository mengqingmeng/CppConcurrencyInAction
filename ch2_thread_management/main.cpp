#include <iostream>
#include <thread>

struct func{
    int& i;
    func(int& _i):i(_i){}

    void operator()(){
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
}
int main(){
    std::cout << "start oops" << std::endl;
    // oops();
    std::thread my_thread([](){
        std::cout << "my thread" << std::endl;
    });

    // my_thread.join(); // join: 主线程等待线程执行完后，继续执行。
    my_thread.detach();

    // 线程传递参数
    std::thread param_thread(f,2,"hello");
    param_thread.join();
    
    std::cout << "end oops" << std::endl;
    return 1;
}