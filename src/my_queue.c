#include "../include/my_queue.h"
#include <stdlib.h>
#include <stdio.h>

queue_list *new_queue(int max_size){
    queue_list *queue = (queue_list*)malloc(sizeof(queue_list));
    queue->size = max_size;
    queue->front = 0;
    queue->rear = 0;
    queue->array = (queue_node*)calloc(max_size , sizeof(queue_node));
    return queue;
}

bool is_queue_full(queue_list *queue){
    if(queue->rear == queue->size - 1)
        return true;
    return false;
}

void enqueue(queue_list *queue, queue_node val){
    if(is_queue_full(queue)){
        printf("Queue is full\n");
    }else {
        queue->array[queue->rear] = val;
        queue->rear++;
    }
}

bool is_queue_empty(queue_list *queue){
    if(queue->front == queue->rear)
        return true;
    return false;
}

queue_node dequeue(queue_list *queue){
    if(is_queue_empty(queue)){
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    queue_node temp = queue->array[queue->front];
    queue->front++;
    return temp;
}

void free_queue_list(queue_list *q){
    free(q->array);
    free(q);
}
