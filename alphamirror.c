#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    int bytes;
    char *buffer;
	// char str[BUFFER_SIZE];
	// // char *line;

    if (buffer == NULL)
		buffer = (char *)malloc(6);

	fd = open("hola", O_RDONLY);
	if (!fd)
	{
		printf("The file could not be opened\nFinishing program\n");
		exit(1);
	}

    bytes = read(fd, buffer, 54145);

    if (bytes == -1)
    {
        printf("ERRORRRR");
        return (0);
    }
    printf("Bytes readed: %i", bytes);
    printf("\n%s", buffer);
    return (0);
}