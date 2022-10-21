#include <unistd.h>

void  ft_simple(char *input)
{
    char    *output;
    input = "modificado";
    return ;
}

void  ft_doble(char **input2)
{
    
    char    *output4 = "123456";

    *input2 = output4;
       
    return ;
}

void ft_editcontent(int *number)
{
  int b = 42;
  
  *number = 0;
  number = &b;
  *number = 11111;
  return ;
}

int main(void)
{
    char *str;
    int a = 9999999;

    str = "HOLA";
    ft_editcontent(&a);
    ft_simple(str);
    ft_doble(&str);
    
   

    return (0);
}