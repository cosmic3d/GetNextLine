#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char    *line;
    int     i;
    int     fd;

    i = 0;
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open file\nFinishing program\n");
        return (0);
    }
    while (i < 1)
    {
        line = get_next_line(fd);
        printf("Line %i is %s", i++, line);
        if (line)
        {
            free(line);
            line = NULL;
        }
    }
}