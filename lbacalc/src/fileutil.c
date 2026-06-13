#include "fileutil.h"
#include <sys/stat.h>

long fsize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0)
        return -1;
    return (long)st.st_size;
}
