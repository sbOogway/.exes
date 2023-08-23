#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "/home/uomosucco/c_headers/utils.c"

int main(int argc, char *argv[], char *envp[]) {
    int i;
    char* test = capture_stdout("echo -n $FORMAT", 10);
    printf("%s", test);
    return 0;
}