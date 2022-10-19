#include <unistd.h>
#include <stdio.h>

void print_bits(unsigned char octet)
{
	int	i;
	unsigned char bit;

	i = 8;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

int main(void)
{
	char	*hola = "hola";

	printf("Index 0 is: %c", hola[0]);
	hola++;
	hola++;
	printf("Index 0 is: %c", hola[0]);
    //print_bits(' ');
    return (0);
}