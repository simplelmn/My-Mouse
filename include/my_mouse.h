#ifndef MY_MOUSE_H
#define MY_MOUSE_H
#include "../include/my_queue.h"
#include <stdbool.h>

typedef struct Int_matrix{
    int row_size;
    int col_size;
    int ix;
    int jx;
    int iy;
    int jy;
    int **array;
}my_matrix;

typedef struct Map_info{
    char start;
    char wall;
    char path;
    char end;
    char **arr;
}map_info;

char **memset_char_mtx(int n, int m);
int **memset_int_mtx(int n, int m);
my_matrix *memset_my_mtx(map_info *info);
void free_char_mtx(char **arr, int n);
void free_int_mtx(int **arr, int n);
void free_my_mtx(my_matrix *matrix);
map_info *memset_map_info();
void free_map_info(map_info *info);
bool is_posible(int row, int col, int row_size, int col_size);
bool is_contain(queue_node arr[], int n, int dist);
float calc_distance(int x1, int x2, int y1, int y2);
queue_list *sub_bfs(my_matrix *matrix, my_cell src, my_cell dest);
void init_arr(queue_node *arr, int n);
void cut_size(queue_list *q);
bool drawable(my_cell coord1, my_cell coord2);
void sub_draw_way(queue_list *q, queue_node *arr, int *cnt, my_matrix *matrix);
void draw_way(queue_list *q, my_matrix *matrix, char **char_matrix, map_info *info);
void print_map(my_matrix *matrix, char **char_matrix, map_info *info);
int my_bfs(my_matrix *matrix, char **char_matrix, my_cell src, my_cell dest, map_info *info);
void init_map_info(char *line, map_info *res);
bool is_error(const char *line, map_info *info, int n, int m, int i, int j);
void fill_char_matrix(map_info *info, char **res, int fd);
void fill_int_matrix(map_info *info, my_matrix *matrix, char **char_matrix);
int my_mouse_helper(map_info *info, char *line, int fd);
bool check_map(char *file_name);
int my_mouse(char *file_name);


#endif