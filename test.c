#include "ft_malloc.h"
#include "libft.h"

int main ()
{
    char *buff;

    if ((buff = (char*)malloc(10)) == NULL) return 1;
    ft_printf("Allocation: %p\n", buff);
    free(buff);
    if ((buff = (char*)malloc(1000)) == NULL) return 2;
    ft_printf("Allocation: %p\n", buff);
    free(buff);
    if ((buff = (char*)malloc(10000)) == NULL) return 3;
    ft_printf("Allocation: %p\n", buff);
    free(buff);
    return (0);
}
