SOURCE_FILES = manager.c \
			   allocator.c \
			   utils.c \
			   malloc.c \
			   stat.c \
			   chunk.c \
			   big.c

SOURCE_DIR = src/
SOURCES = $(addprefix $(SOURCE_DIR), $(SOURCE_FILES))


OBJECT_FILES = $(SOURCE_FILES:.c=.o)
OBJECT_DIR = obj/
OBJECTS = $(addprefix $(OBJECT_DIR), $(OBJECT_FILES))

INCLUDE_FILES = ft_malloc.h \
				manager.h
INCLUDE_DIR = include/
INCLUDES = $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

LIBFT_PATH = ./libft/
LIBFT_HEADER = $(LIBFT_PATH)includes/

vpath %.c $(SOURCE_DIR)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
OFLAGS = -O2

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

ifeq ($(HOSTTYPE), )
$(eval HOSTTYPE := $(shell uname -m)_$(shell uname -s))
endif

.PHONY: all clean fclean re link

all: $(NAME) $(LINK)

$(NAME): $(OBJECTS)
	make -C $(LIBFT_PATH)
	$(CC) $(DEBUG) -shared -o $(NAME) $(OBJECTS) $(LIBFT_PATH)libft.a
	
$(OBJECT_DIR)%.o: %.c $(INCLUDES)
	mkdir -p $(OBJECT_DIR)
	$(CC) $(DEBUG) -c -fPIC -o $@ $(OFLAGS) $(CFLAGS) $< -I$(INCLUDE_DIR) -I$(LIBFT_HEADER)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)
	rm -rf $(OBJECT_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(LINK)
	rm -f $(NAME)

re: fclean all

$(LINK): $(NAME)
	rm -f $(LINK)
	ln -s $(NAME) $(LINK)
