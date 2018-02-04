#include "ft_malloc.h"
#include "libft.h"
#include "manager.h"

#include <assert.h>

#define SAMPLES TINY_COUNT + SMALL_COUNT + 1000

void set(unsigned char *ptr, size_t size)
{
    size_t pos;

    pos = 0;
    while (pos < size)
    {
        ptr[pos] = pos % 0xff;
        ++pos;
    }
}

void validate(unsigned char *ptr, size_t size)
{
    while (size--)
    {
        assert(ptr[size] == size % 0xff);
    }
}

int main()
{
    unsigned char *buff[SAMPLES];
    int   cnt;

    cnt = SAMPLES;
    while (--cnt)
        assert(buff[cnt] = (unsigned char *) malloc(cnt));
    cnt = SAMPLES;
    while (--cnt)
        set(buff[cnt], cnt);
    cnt = SAMPLES;
    while (--cnt)
        validate(buff[cnt], cnt);
    cnt = SAMPLES;
    while (--cnt)
        free(buff[cnt]);
    return (0);
}
