#include "../include/my_string.h"
#include <stdlib.h>
#include <unistd.h>

void my_memset(bool *buf, bool b, unsigned long n){
    for(unsigned long i = 0; i < n; i++)
        buf[i] = b;
}

int my_size(const char *string){
    int i = 0;
    while(string[i]) i++;
    return i;
}

int my_atoi(const char *string){
    int ans = 0;
    for(int i = 0; string[i]; i++)
        ans = ans * 10 + string[i] - '0';
    return ans;
}

bool is_number(char c){
    return c >= '0' && c <= '9';
}

char *my_readline(int fd){
    char *line = (char*)malloc(MAX_SIZE * sizeof(char));
    int i = 0;
    char ch;
    while(read(fd, &ch, 1)){
        if(ch != '\n')
            line[i++] = ch;
        else{
            line[i] = '\0';
            return line;
        }
    }
    free(line);
    return NULL;
    
}

int count_line(int fd){
    int count = 0;
    char ch;
    int j;
    do{
        j = read(fd, &ch, 1);
        if(ch == '\n'){
            count++;
        }else{
            if(j == 0) count++;
        }
    }while(j);
    return count;
}