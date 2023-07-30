[TOC]

# 《C++并发编程实战第二版》学习代码
[源作者代码库](https://github.com/anthonywilliams/ccia_code_samples.git)
##  第一章
你好，并发世界
## 第二章
线程管理
### 启动线程
- join() 父线程**等待**线程结束后继续执行
- detach() 父线程**不等待**此线程结束（继续执行父线程之后的代码）
    - 线程后台运行
    - 与主线程不能直接交互
### 等待与分离线程
### 传递参数
### 唯一标识符
## 共享数据
> 恶性竞争：多个线程对共享数据的修改。
解决方法：对共享数据采取保护机制。
### 互斥量 
#### std::mutex
- 对mutex的实例，调用lock()进行加锁。
- 多mutex的实例，调用unlock()进行解锁。
#### std::lock_guard<std::mutex>
- 构造时上锁，析构时释放锁。
- c++17中可不提供模板类型: `std::lock_guard guard(some_mutex);`