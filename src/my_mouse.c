#include "../include/my_mouse.h"
#include "../include/my_queue.h"
#include "../include/my_math.h"
#include "../include/my_string.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **memset_char_mtx(int n, int m){
    char **arr = (char**)malloc(n * sizeof(char*));
    for(int i = 0; i < n ; i++)
        arr[i] = (char*)malloc(m * sizeof(char));
    return arr;
}

int **memset_int_mtx(int n, int m){
    int **arr = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++)
        arr[i] = (int*)malloc(m * sizeof(int));
    return arr;
}

my_matrix *memset_my_mtx(map_info *info){
    my_matrix *matrix = (my_matrix*)malloc(sizeof(my_matrix));
    int n = my_atoi(info->arr[0]);
    int m = my_atoi(info->arr[1]);
    matrix->array = memset_int_mtx(n , m);
    matrix->row_size = n;
    matrix->col_size = m;
    return matrix;
}

void free_char_mtx(char **arr, int n){
    for(int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

void free_int_mtx(int **arr, int n){
    for(int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

void free_my_mtx(my_matrix *matrix){
    free_int_mtx(matrix->array, matrix->row_size);
    free(matrix);
}

map_info *memset_map_info(){
    map_info *info = (map_info*)malloc(sizeof(map_info));
    info->arr = memset_char_mtx(2, 11);
    return info;
}

void free_map_info(map_info *info){
    free_char_mtx(info->arr, 2);
    free(info);
}

bool is_posible(int row, int col, int row_size, int col_size){
    return ((row >= 0) && (row < row_size) && (col >= 0) && (col < col_size));
}

bool is_contain(queue_node arr[], int n, int dist){
    for(int i = 0; i < n; i++)
        if(arr[i].dist == dist)
            return true;
    return false;
}

float calc_distance(int x1, int x2, int y1, int y2){
    return my_square(my_pow(x2 - x1, 2) + my_pow(y2 - y1, 2));
}

queue_list *sub_bfs(my_matrix *matrix, my_cell src, my_cell dest){
    int row_num[] = {-1, 0, 0, 1};
    int col_num[] = {0, -1, 1, 0};
    bool visited[matrix->row_size][matrix->col_size];
    visited[src.x][src.y] = true;
    queue_list *q = new_queue(matrix->row_size * matrix->col_size);
    queue_node s = {src, 0};
    enqueue(q, s);
    while(!is_queue_empty(q)){
        queue_node curr = dequeue(q);
        my_cell coord = curr.coord;
        if(coord.x == dest.x && coord.y == dest.y){
            q->dist = curr.dist;
            return q;
        }
        for(int i = 0; i < 4; i++){
            int row = coord.x + row_num[i], col = coord.y + col_num[i];
            if(is_posible(row, col, matrix->row_size, matrix->col_size) && matrix->array[row][col] && !visited[row][col]){
                visited[row][col] = true;
                queue_node adjc = {{row, col}, curr.dist + 1};
                enqueue(q, adjc);
            }
        }
    }
    free_queue_list(q);
    return NULL;
}

void init_arr(queue_node *arr, int n){
    my_cell temp = {0 , 0};
    for(int i = 0; i < n; i++){
        arr[i].coord = temp;
        arr[i].dist = 0;
    }
}

void cut_size(queue_list *q){
    int cnt = 1;
    for(int i = 1; i < q->size; i++)
        if(q->array[i].coord.x != 0 && q->array[i].coord.y != 0 && q->array[i].dist <= q->dist)
            cnt++;
    q->size = cnt;
}

bool drawable(my_cell coord1, my_cell coord2){
    float dist = calc_distance(coord1.x, coord2.x, coord1.y, coord2.y);
    if(dist >= 2)
        return false;
    return true;
}



void sub_draw_way(queue_list *q, queue_node *arr, int *cnt, my_matrix *matrix){
    cut_size(q);
    queue_node temp = {{matrix->iy, matrix->jy}, q->dist};
    for(int i = q->size - 1; i >= 0; i--){
        if(!is_contain(arr, q->dist + 1, q->array[i].dist)){
            if(drawable(temp.coord, q->array[i].coord))
            {
                arr[(*cnt)++] = q->array[i];
                temp = q->array[i];
            }
        }
    }
}


void draw_way(queue_list *q, my_matrix *matrix, char **char_matrix, map_info *info){
    queue_node *arr = (queue_node*)malloc((q->dist + 1) * sizeof(queue_node));
    init_arr(arr, q->dist + 1);
    int cnt = 0;
    sub_draw_way(q, arr, &cnt, matrix);
    for(int i = 0; i < cnt; i++)
        char_matrix[arr[i].coord.x][arr[i].coord.y] = info->path;
    char_matrix[matrix->ix][matrix->jx] = info->start;
    char_matrix[matrix->iy][matrix->jy] = info->end;
    free(arr);
}

void print_map(my_matrix *matrix, char **char_matrix, map_info *info){
    int p = 0;
    printf("%dx%d%c %c%c%c\n", matrix->row_size, matrix->col_size, info->wall, info->path, info->start, info->end);
    fflush(stdout);
    for(int i = 0; i < matrix->row_size; i++){
        for(int j = 0; j < matrix->col_size; j++){
            if(char_matrix[i][j] == info->path)
                p++;
            printf("%c", char_matrix[i][j]);
        }
        printf("\n");
    }
    printf("%d STEPS!\n", p);
    fflush(stdout);
}

int my_bfs(my_matrix *matrix, char **char_matrix, my_cell src, my_cell dest, map_info *info){
    if(!matrix->array[src.x][src.y] && !matrix->array[dest.x][dest.y])
        return -1;
    if(char_matrix && info){}
    queue_list *q = sub_bfs(matrix, src, dest);
    if(q == NULL){
       return -1;
    }
    draw_way(q, matrix, char_matrix, info);
    free_queue_list(q);
    return 1;
}

void init_map_info(char *line, map_info *res){
    int c = 0, r = 0;
    while(*line != ' '){
        if(is_number(*line))
            res->arr[r][c++] = *line;
        else{
            res->arr[r][c] = '\0';
            r++;
            c = 0;
        }
        if(*line != 'x' && !is_number(*line))
            res->wall = *line;
        line++;
    }
    line++;
    res->path = *line++;
    res->start = *line++;
    res->end = *line;
}

bool is_error(const char *line, map_info *info, int n, int m, int i, int j){
    if((j - 2) != n) return true;
    if(my_size(line) > m) return true;
    if(i == 0){
        for(int j = 0; line[j]; j++)
            if(line[j] == info->start)
                return false;
    }else
    if(i == n - 1){
        for(int j = 0; line[j]; j++)
            if(line[j] == info->end)
                return false;
    }else{
        int f = 0;
        for(int j = 0; line[j]; j++)
            if(line[j] == info->wall || line[j] == ' ')
                f++;
        if(f == my_size(line)) return false;
    }
    return true;
}

void fill_char_matrix(map_info *info, char **res, int fd){
    int i = 0, r = 0;
    char *line;
    while((line = my_readline(fd))){
        for(i = 0; line[i]; i++){
            if(line[i] == info->wall)
                res[r][i] = info->wall;
            else if(line[i] == info->start)
                res[r][i] = info->start;
            else if(line[i] == info->end)
                res[r][i] = info->end;
            else
                res[r][i] = ' ';
        }
        res[r++][i] = '\0';
        free(line);
    }
}

void fill_int_matrix(map_info *info, my_matrix *matrix, char **char_matrix){
    int n = my_atoi(info->arr[0]), m = my_atoi(info->arr[1]);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(char_matrix[i][j] == info->start){
                matrix->array[i][j] = 1;
                matrix->ix = i;
                matrix->jx = j;
            }else if(char_matrix[i][j] == info->end){
                matrix->array[i][j] = 1;
                matrix->iy = i;
                matrix->jy = j;
            }else if(char_matrix[i][j] == ' '){
                matrix->array[i][j] = 1;
            }else{
                matrix->array[i][j] = 0;
            }
        }
    }
}

int my_mouse_helper(map_info *info, char *line, int fd){
    init_map_info(line, info);
    char **char_matrix = memset_char_mtx(my_atoi(info->arr[0]), my_atoi(info->arr[1]) + 1);
    fill_char_matrix(info, char_matrix, fd);
    my_matrix *matrix = memset_my_mtx(info);
    fill_int_matrix(info, matrix, char_matrix);
    my_cell src = {matrix->ix, matrix->jx};
    my_cell dest = {matrix->iy, matrix->jy};
    int j = my_bfs(matrix, char_matrix, src, dest, info);
    if(j == -1){
        free_my_mtx(matrix);
        free_char_mtx(char_matrix, my_atoi(info->arr[0]));
        return -1;
    }
    print_map(matrix, char_matrix, info);
    fflush(stdout);
    free_my_mtx(matrix);
    free_char_mtx(char_matrix, my_atoi(info->arr[0]));
    return 0;
}

bool check_map(char *file_name){
    int fd = open(file_name, O_RDONLY), i = 0;
    int j = count_line(fd);
    close(fd);
    fd = open(file_name, O_RDONLY);
    char *line = my_readline(fd);
    map_info *info = memset_map_info();
    init_map_info(line, info);
    int n = my_atoi(info->arr[0]), m = my_atoi(info->arr[1]);
    free(line);
    while((line = my_readline(fd))){
        if(is_error(line, info, n, m, i, j)){
            free(line);
            free_map_info(info);
            return false;
        }
        free(line);
        i++;
    }
    close(fd);
    free_map_info(info);
    return true;
}

int my_mouse(char *file_name){
    if(!check_map(file_name)){
        return -1;
    }
    int fd = open(file_name, O_RDONLY);
    char *line = my_readline(fd);
    map_info *info = memset_map_info();
    int j = my_mouse_helper(info, line, fd);
    if(j == -1){
        free(line);
        free_map_info(info);
        return -1;
    }    
    free(line);
    free_map_info(info);
    return 1;
}