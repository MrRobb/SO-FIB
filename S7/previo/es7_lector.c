#include <unistd.h>
#include <stdio.h>

int main(){
    int num;
    read(0, &num, sizeof(int));
    printf("%d\n", num);
}
