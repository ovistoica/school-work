#include<stdio.h>
#include<stdlib.h>

void modify_copy(int to_modify) {
    to_modify = 6;
}

void modify_var_pointer(int* pointer_to_modify) {
    *pointer_to_modify = 6;
}

int main() {
    int b[100];
    int i = 0;

    for (i = 0; i < 100; i++) {
        b[i] = i;
    }
    modify_var_pointer(&i);

    printf("%d\n", b + 1);
    printf("%d\n", *(b+1));
    printf("%d\n", b[1]);

    return 0;
}