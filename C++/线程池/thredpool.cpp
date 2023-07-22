#include<queue>
#include<pthread.h>
#include<string.h>
#include<string>
#include<unistd.h>
#include<iostream>
using namespace std;
using callback=void(*)(void*arg);

//任务结构体
struct Task
{
    Task()
    {
        function=nullptr;
        arg=nullptr;
    }
    Task(callback f,void* arg)
    {
        this->arg=arg;
        function=f;
    }
    callback function;
    void* arg;
};

class TaskQueue
{
    public:
    TaskQueue();
    ~TaskQueue();

    //添加任务
    void addTask(Task task);
    void addTask(callback f,void* arg);
    //取出一个任务
    Task takeTask();
    //获取当前任务的个数
    inline size_t taskNumber()
    {
        return m_taskQ.size();
    }

    private:
    pthread_mutex_t m_mutex;
    std::queue<Task>m_taskQ;
};

TaskQueue::TaskQueue()
{
    //初始化互斥锁
    pthread_mutex_init(&m_mutex,NULL);

}
TaskQueue::~TaskQueue()
{
    //销毁互斥锁
    pthread_mutex_destroy(&m_mutex);
}
void TaskQueue::addTask(Task task)
{
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push(task);
    pthread_mutex_unlock(&m_mutex);
}
void TaskQueue::addTask(callback f,void* arg)
{
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push(Task(f,arg));
    pthread_mutex_unlock(&m_mutex);
}
Task TaskQueue::takeTask()
{
    Task t;
    pthread_mutex_lock(&m_mutex);
    //判断任务队列是不是空的
    if(m_taskQ.size()>0)
    {
        t=m_taskQ.front();
        m_taskQ.pop();
    }
    pthread_mutex_unlock(&m_mutex);
    return t;
}


class ThreadPool
{
    public:
    //创建线程池并初始化就是构造函数
    ThreadPool(int min,int max);
    //销毁线程池就是析构函数
    ~ThreadPool();
    //给线程池添加任务
    void addTask(Task task);
    //获取线程池中工作的线程个数
    int getBusyNum();
    //获取线程池中活着的线程的个数
    int getAliveNum();
    //工作的线程（消费者线程）任务函数
    static void* worker(void* arg);
    //管理者线程任务函数
    static void* manager(void* arg);
    //单个线程退出
    void threadExit();

    private:
    // 任务队列
    TaskQueue *taskQ;
   
    int minNum;        // 最小线程数
    int maxNum;        // 最大线程数
    int busyNum;       // 忙的线程个数
    int liveNum;       // 存活的线程个数
    int exitNum;       // 要杀死的线程个数

    pthread_t *threadIDs; // 工作的线程ID
    pthread_t managerID;  // 管理者线程ID

    pthread_cond_t notEmpty; // 任务队列是不是空了

    pthread_mutex_t mutexPool; // 锁整个的线程池
    static const  int NUMBER=2;

    bool shutdown; // 是不是要销毁线程池，销毁为1,不销毁为0
};

//创建线程池
ThreadPool::ThreadPool(int min, int max)
{
    //实例化任务队列

    do 
    {
        taskQ=new TaskQueue;
        if (taskQ == nullptr)
        {
            cout<<"malloc taskQ fail...\n"<<endl;
            break;
        }
        threadIDs = new pthread_t[max];
        if (threadIDs == nullptr)
        {
            cout<<"malloc threadIDs fail...\n"<<endl;
            break;
        }
        memset(threadIDs, 0, sizeof(pthread_t) * max);
        minNum = min;
        maxNum = max;
        busyNum = 0;
        liveNum = min;    // 和最小个数相等
        exitNum = 0;

        if (pthread_mutex_init(&mutexPool, NULL) != 0 ||
            pthread_cond_init(&notEmpty, NULL) != 0 )
        {
            cout<<"mutex or condition init fail...\n"<<endl;
            break;
        }


        shutdown = false;

        // 创建线程
        pthread_create(&managerID, NULL, manager, this);
        for (int i = 0; i < min; ++i)
        {
            pthread_create(&threadIDs[i], NULL, worker, this);
        }
        return;
    } while (0);

    // 释放资源
    if (threadIDs) delete[]threadIDs;
    if (taskQ) delete taskQ;
}

ThreadPool::~ThreadPool()
{
    // 关闭线程池
    shutdown = true;
    // 阻塞回收管理者线程
    pthread_join(managerID, NULL);
    // 唤醒阻塞的消费者线程
    for (int i = 0; i < liveNum; ++i)
    {
        pthread_cond_signal(&notEmpty);
    }
    // 释放堆内存
    if (taskQ)
    {
        delete taskQ;
    }
    if (threadIDs)
    {
        delete threadIDs;
    }

    pthread_mutex_destroy(&mutexPool);
    pthread_cond_destroy(&notEmpty);
}



//添加工作的线程的任务函数
void* ThreadPool::worker(void* arg)
{
    ThreadPool* pool = static_cast<ThreadPool*>(arg);//强制类型转换
//静态成员函数要想访问非静态成员变量，必须通过实例化对象
    while (true)
    {
        pthread_mutex_lock(&pool->mutexPool);
        // 当前任务队列是否为空
        while (pool->taskQ->taskNumber() == 0 && !pool->shutdown)
        {
            // 阻塞工作线程
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            // 判断是不是要销毁线程
            if (pool->exitNum > 0)
            {
                pool->exitNum--;
                if (pool->liveNum > pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    pool->threadExit();
                }
            }
        }

        // 判断线程池是否被关闭了
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }

        // 从任务队列中取出一个任务
        Task task=pool->taskQ->takeTask();
       
        pool->busyNum++;
        // 解锁
        pthread_mutex_unlock(&pool->mutexPool);

        cout<<"thread "<<to_string( pthread_self())<<"start working..."<<endl;
        //通过函数指针调用函数，传递的实参堆内存
        task.function(task.arg);
        delete task.arg;
        task.arg = nullptr;

        cout<<"thread "<<to_string( pthread_self())<<"end working..."<<endl;

        pthread_mutex_lock(&pool->mutexPool);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexPool);
    }
    return NULL;
}

void ThreadPool::threadExit()
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < maxNum; ++i)
    {
        if (threadIDs[i] == tid)
        {
            threadIDs[i] = 0;
            cout<<"threadExit() called," <<to_string(tid)<< "exiting..."<<endl;
            break;
        }
    }
    pthread_exit(NULL);
}

void*ThreadPool::manager(void* arg)
{
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while (!pool->shutdown)
    {
        // 每隔3s检测一次
        sleep(3);

        // 取出线程池中任务的数量和当前线程的数量
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->taskQ->taskNumber();
        int liveNum = pool->liveNum;
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);


        // 添加线程
        // 任务的个数>存活的线程个数 && 存活的线程数<最大线程数
        if (queueSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            //限制创建的线程数量
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUMBER
                && pool->liveNum < pool->maxNum; ++i)
            {
                if (pool->threadIDs[i] == 0)
                {
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }
        // 销毁线程
        // 忙的线程*2 < 存活的线程数 && 存活的线程>最小线程数
        if (busyNum * 2 < liveNum && liveNum > pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            // 让工作的线程自杀
            for (int i = 0; i < NUMBER; ++i)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return NULL;
}



void ThreadPool::addTask(Task task)
{
    if (shutdown)
    {
        return;
    }
    // 添加任务 
    taskQ->addTask(task);

    pthread_cond_signal(&notEmpty);
}

int ThreadPool::getBusyNum()
{
    pthread_mutex_lock(&mutexPool);
    int busyNum =this->busyNum;
    pthread_mutex_unlock(&mutexPool);
    return busyNum;
}

int ThreadPool::getAliveNum()
{
    pthread_mutex_lock(&mutexPool);
    int aliveNum = this->liveNum;
    pthread_mutex_unlock(&mutexPool);
    return aliveNum;
}