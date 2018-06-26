SOURCE_FILES = test01_sizes.c \
			   test02_read_write.c \
			   test03_random_allocations.c \
			   test04_huge_mini.c

CC = gcc
CFLAGS = -Wall -Werror -Wextra
OFLAGS = -O2

LIB = libft_malloc.so

NAME = $(SOURCE_FILES:.c=)

all: $(NAME)
	@for executable in $(NAME) ; do \
		echo "Running $$executable" ;\
		DYLD_LIBRARY_PATH=../ ./$$executable ; \
	done

%: %.c
	$(CC) $(DEBUG) -o $@ $< -Wl,-rpath,../ -L../ -lft_malloc -ldl -L../libft -lft  -I../include -I../libft/includes
	
clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
