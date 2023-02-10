#ifndef MY_QUEUE_H
#define MY_QUEUE_H
#include <stdbool.h>

typedef struct Cell{
    int x;
    int y;
}my_cell;

typedef struct Queue_node{
    my_cell coord;
    int dist;
}queue_node;

typedef struct Queue_list{
    int front;
    int rear;
    int size;
    int dist;
    queue_node *array;
}queue_list;

queue_list *new_queue(int max_size);
bool is_queue_full(queue_list *queue);
void enqueue(queue_list *queue, queue_node val);
bool is_queue_empty(queue_list *queue);
queue_node dequeue(queue_list *queue);
void free_queue_list(queue_list *q);

#endif