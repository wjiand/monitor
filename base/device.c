#include <stdio.h>
#include "monitor.h"

char main_path[128] = {0};

int sigint_pipe[2] = {-1, -1};

