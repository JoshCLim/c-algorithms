#include <stdio.h>

#include "log.h"

int log_output(char *string) {
    FILE *log = fopen("./logs/log.txt", "a");
    
    fprintf(log, "%s", string);

    fclose(log);

    return 0;
}