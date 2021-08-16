#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>

const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize];

//选择测试案例
#define SINGLES
//#define WAITWAKE

#ifdef SINGLES
//信号量
QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes(0);

class Producer : public QThread
{
public:
    Producer();
    void run();
};

Producer::Producer()
{

}

void Producer::run(){
    for(int i=0;i<DataSize;i++){
        freeBytes.acquire();
        buffer[i%BufferSize] = (i%BufferSize);
        qDebug()<<buffer[i%BufferSize];
        usedBytes.release();
    }
}

class Consumer : public QThread
{
public:
    Consumer();
    void run();
};

Consumer::Consumer()
{

}

void Consumer::run(){
    for(int i =0;i<DataSize;i++){
        usedBytes.acquire();
        fprintf(stderr,"%d",buffer[i%BufferSize]);
        if(i%16==0 && i!=0) fprintf(stderr,"\n");
        freeBytes.release();
    }
    fprintf(stderr,"\n");
}

#endif

#ifdef WAITWAKE
//线程等待与唤醒
QWaitCondition bufferEmpty;
QWaitCondition bufferFull;
QMutex mutex;
int numUsedBytes = 0;
int rIndex = 0;

class Producer : public QThread{
public:
    Producer();
    void run();
};

Producer::Producer(){

}

void Producer::run(){
    for(int i=0; i<DataSize; i++){
        mutex.lock();
        if(numUsedBytes == BufferSize) bufferEmpty.wait(&mutex);
        buffer[i%BufferSize] = numUsedBytes;
        ++numUsedBytes;
        bufferFull.wakeAll();
        mutex.unlock();
    }
}

class Consumer : public QThread{
public:
    Consumer();
    void run();
};

Consumer::Consumer(){

}

void Consumer::run(){
    forever{
        mutex.lock();
        if(numUsedBytes==0) bufferFull.wait(&mutex);
        printf("%ul::[%d]=%d\n",currentThreadId(),rIndex,buffer[rIndex]);
        rIndex = (++rIndex)%BufferSize;
        --numUsedBytes;
        bufferEmpty.wakeAll();
        mutex.unlock();
    }
    printf("\n");
}

#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#ifdef SINGLES
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();
#endif

#ifdef WAITWAKE
    Producer producer;
    Consumer consumerA;
    Consumer consumerB;
    producer.start();
    consumerA.start();
    consumerB.start();
    producer.wait();
    consumerA.wait();
    consumerB.wait();
#endif

    return a.exec();
}
