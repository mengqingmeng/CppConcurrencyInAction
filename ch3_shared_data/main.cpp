#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <list>

std::list<int> some_list;
std::mutex some_mutex; // 必须确保是同一把锁。否则无效

/// @brief 向list中加入数据
/// @param new_value int型数值
void add_to_list(int new_value){
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

/// @brief list中是否包含待查找数值
/// @param value_to_find 待查找数值
/// @return 是否包含
bool list_contains(int value_to_find){
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}

int main(){
    return 1;
}