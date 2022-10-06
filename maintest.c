#include "get_next_line.h"

int main()
{
        int fd;
        char str[200];
        int start = 14;
        int end = 18;
        // // char *line;


        fd = open("texto", O_RDONLY);
        if (!fd)
        {
                printf("The file could not be opened\nFinishing program\n");
                exit(1);
        }
        printf("Read 1 is: %i\n",(int)read(fd, str, 200));
        printf("Str is: %s\n", str);
        printf("Substr from %i to %i is: \"%s\"\n", start, end, ft_substr(str, start, end));
        // printf("Read 2 is: %i\n",(int)read(fd, str, BUFFER_SIZE));
        // printf("Str is: %s\n", str);
        // // if (!read(fd, str, BUFFER_SIZE))
        // // {
        // //   printf("The file could not be read\nFinishing program\n");
        // //   exit(1);
        // // }
        // printf("The content is: \n\"%s\"\n", str);
        // return (0);
        return (0);
}
