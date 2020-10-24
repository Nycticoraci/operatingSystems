//Jaki Giggi
//10/20/2020
//operatingSystems
//asssignment one: part b

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAX_QUEUE_LENGTH    1000

struct Queue
{
    int data[MAX_QUEUE_LENGTH];
    int front;
    int back;
}typedef Queue;

Queue producerQ = {{}, -1, -1};

// create a mutex to be used by producer threads to regulate access to shared resource
pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;

// shared function that writes the random integer produced my producer thread functions to the queue, returns 0 for success, -1 for failure
int produce(int data)
{
    if(producerQ.back == MAX_QUEUE_LENGTH-1)
    {
        printf("Error: Queue full, please consume and come back later\n");
        return -1;
    }
    else
    {
        producerQ.back++; // move back to the next empty index
        producerQ.data[producerQ.back] = data;
        printf("Data written to producer queue: %d, back of queue marker: %d\n", data, producerQ.back);
        //printf("Back of queue marker: %d.\n", producerQ.back);
        return 0;
    }
}

// thread function that is invoked when a thread is created (producer thread)
void* producer_thread(void* args)
{
    int data, val;

    while(1)
    {
        data = rand(); // generate a random number to insert into the queue

        pthread_mutex_lock(&producer_mutex); // acquire the mutex

        val = produce(data); // call the shared function

        pthread_mutex_unlock(&producer_mutex); // release the mutex for other threads once this is done

        if (val == 0)
            printf("I am producer thread %x, data written: %d\n", (int)pthread_self(), data); // print the thread id
        else
            printf("I am thread %x, data writing failed\n", (int)pthread_self());
        // sleep for 10ms
        usleep(10000);
    }
}

int consume()
{
    if(producerQ.back == -1)
    {
        printf("Error: queue empty\n");
        return -1;
    }
    if(producerQ.front > producerQ.back)
    {
        printf("Error: queue empty\n");
        return -1;
    }
    else
    {
        producerQ.front++; // advance front to the first available element
        //printf("Front of queue marker is: %d, data is: %d.\n", producerQ.front, producerQ.data[producerQ.front]);
        return producerQ.data[producerQ.front]; // return the top element
    }
}

// thread function for consumer threads
void* consumer_thread(void* args)
{
    int data;

    while(1)
    {
        pthread_mutex_lock(&producer_mutex); // acquire the same mutex as the shared resource is same for both producer and consumer

        data = consume();

        pthread_mutex_unlock(&producer_mutex); // release the mutex

        if (data != -1)
            printf("I am consumer thread %x, data: %d, queue front marker: %d\n", (int)pthread_self(), data, producerQ.front);

        else
            printf("I am consumer thread %x, queue empty\n", (int)pthread_self());

        //pthread_mutex_unlock(&producer_mutex); // release the mutex

        // sleep for 500ms
        usleep(250000);
    }
}

int main(int argc, char* argv[])
{
    pthread_t producer_thread_id[8]; // array to store producer thread ids

    int i, n;

    // get the number of consumers from the commandline argument
    n = atoi(argv[1]);

    pthread_t consumer_thread_id[n];

    // create and start the producer threads
    //for(i = 0; i < 4; i++)
    //{
    pthread_create(&producer_thread_id[0], NULL, producer_thread, NULL);
    //}

    // create and start the consumer threads
    for(i = 0; i < n; i++)
    {
        pthread_create(&consumer_thread_id[i], NULL, consumer_thread, NULL);
    }

    // wait only for the first thread to return, may do for all using a loop
    pthread_join(producer_thread_id[0], NULL);
    pthread_join(consumer_thread_id[i], NULL);

    return 0;
}
