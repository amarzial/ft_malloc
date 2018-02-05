SOURCE_FILES = test01_sizes.c \
			   test02_read_write.c \

CC = gcc
CFLAGS = -Wall -Werror -Wextra
OFLAGS = -O2

LIB = libft_malloc.so

NAME = $(SOURCE_FILES:.c=)

all: $(NAME)
	@for executable in $(NAME) ; do \
		echo "Running $$executable" ;\
		LD_PRELOAD=../libft_malloc.so ./$$executable ; \
	done

%: %.c
	$(CC) $(DEBUG) -o $@ $< -L../libft -lft  -I../include -I../libft/includes
	
clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
