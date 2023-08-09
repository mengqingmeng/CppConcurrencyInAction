#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include  <queue>

struct data_chunk{

};

std::mutex mut;

std::queue<data_chunk> data_queue; // 共享数据
std::condition_variable data_condi; // 信号量

bool more_data_to_prepare(){
    return false;
}

data_chunk prepare_data(){
    return data_chunk();
}

void process_data(data_chunk& data){

}

bool is_last_chunk(data_chunk&)
{
    return true;
}


void data_preparation_thread(){
    while(more_data_to_prepare()){
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut); // 获取锁；在作用域结束后释放锁。
        data_queue.push(data);
        data_condi.notify_one(); // 通知
    }
}

void data_processing_thread(){
    while(true){
        std::unique_lock<std::mutex> lk(mut);

        // 信号量在此处等待，notify信号。如果有了信号，则判断lambda函数，如果满足则wait返回，此线程持有锁。如果不满足，则释放锁，继续阻塞。
        data_condi.wait(lk,[]{ return !data_queue.empty();}); 
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process_data(data);
        if(is_last_chunk(data)){
            break;
        }
    }
}

int main(){

    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();
    
    return 1;
}