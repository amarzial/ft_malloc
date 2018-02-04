#include "ft_malloc.h"
#include "manager.h"
#include "libft.h"

#include <assert.h>

int main ()
{
    char *buff;

    assert(!(buff = (char*)malloc(0)));
    free(buff);
    assert(buff = (char*)malloc(TINY_SIZE));
    free(buff);
    assert(buff = (char*)malloc(SMALL_SIZE));
    free(buff);
    assert(buff = (char*)malloc(SMALL_SIZE * 10));
    free(buff);
    return (0);
}
