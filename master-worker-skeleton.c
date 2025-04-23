#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>


int item_to_produce, curr_buf_size;
int total_items, items_consumed, max_buf_size, num_workers, num_masters;

int *buffer;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;


void print_produced(int num, int master) {

  printf("Produced %d by master %d\n", num, master);
}

void print_consumed(int num, int worker) {

  printf("Consumed %d by worker %d\n", num, worker);
  
}


//produce items and place in buffer
//modify code below to synchronize correctly
void *generate_requests_loop(void *data)
{
  int thread_id = *((int *)data);

  while(total_items >= items_consumed)
    {
      pthread_mutex_lock(&mutex);

       
      if(item_to_produce >= total_items) {
        pthread_mutex_unlock(&mutex);

	      break;
      }
 
      buffer[curr_buf_size++] = item_to_produce;
      print_produced(item_to_produce, thread_id);
      item_to_produce++;
      pthread_cond_broadcast(&not_empty);
        
      pthread_mutex_unlock(&mutex);
      usleep(1);
    }
  return 0;
}

//write function to be run by worker threads
//ensure that the workers call the function print_consumed when they consume an item
void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < total_items; i++) {
        
        pthread_mutex_lock(&mutex);

        // TODO: Implement the wait condition when the buffer is empty
        while(curr_buf_size <=0 && items_consumed<total_items){
            pthread_cond_wait(&not_empty, &mutex);
        }
        if(items_consumed >= total_items){
          pthread_mutex_unlock(&mutex);
          break;
        }
        // Remove item from buffer
        curr_buf_size --;
        int item = buffer[curr_buf_size];
        print_consumed(item, id);
        items_consumed++;

        // TODO: Signal the producers that buffer is not full
        pthread_cond_broadcast(&not_full);

        pthread_mutex_unlock(&mutex);

        usleep(1); // Simulate processing time
    }
    return NULL;
}

int main(int argc, char *argv[])
{
  int *master_thread_id;
  int *consumer_thread_id;
  pthread_t *master_thread, *consumer_thread;
  item_to_produce = 0;
  curr_buf_size = 0;
  
  int i;
  
   if (argc < 5) {
    printf("./master-worker #total_items #max_buf_size #num_workers #masters e.g. ./exe 10000 1000 4 3\n");
    exit(1);
  }
  else {
    num_masters = atoi(argv[4]);
    num_workers = atoi(argv[3]);
    total_items = atoi(argv[1]);
    max_buf_size = atoi(argv[2]);
  }
    

   buffer = (int *)malloc (sizeof(int) * max_buf_size);

   //create master producer threads
   master_thread_id = (int *)malloc(sizeof(int) * num_masters);
   master_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_masters);
  for (i = 0; i < num_masters; i++)
    master_thread_id[i] = i;

  for (i = 0; i < num_masters; i++)
    pthread_create(&master_thread[i], NULL, generate_requests_loop, (void *)&master_thread_id[i]);
  
  //create worker consumer threads
    consumer_thread_id = (int *)malloc(sizeof(int) * num_workers);
    consumer_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_workers);
    for (i = 0; i < num_workers; i++)
      consumer_thread_id[i] = i+1;

    for (i = 0; i < num_workers; i++)
      pthread_create(&consumer_thread[i], NULL, consumer, (void *)&consumer_thread_id[i]);
    
  
  //wait for all threads to complete
  for (i = 0; i < num_masters; i++)
    {
      pthread_join(master_thread[i], NULL);
      printf("master %d joined\n", i);
    }
  for (i = 0; i < num_workers; i++)
    {
      pthread_join(consumer_thread[i], NULL);
      printf("worker %d joined\n", i);
    }
  
  /*----Deallocating Buffers---------------------*/
  free(buffer);
  free(master_thread_id);
  free(master_thread);
  
  return 0;
}
