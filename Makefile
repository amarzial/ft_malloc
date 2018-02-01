SOURCE_FILES = manager.c \
			   utils.c \
			   ft_malloc.c \
			   #ft_free.h
SOURCE_DIR = src/
SOURCES = $(addprefix $(SOURCE_DIR), $(SOURCE_FILES))


OBJECT_FILES = $(SOURCE_FILES:.c=.o)
OBJECT_DIR = obj/
OBJECTS = $(addprefix $(OBJECT_DIR), $(OBJECT_FILES))

INCLUDE_FILES = ft_memory.h \
				manager.h
INCLUDE_DIR = include/
INCLUDES = $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

LIBFT_PATH = libft/
LIBFT_HEADER = $(LIBFT_PATH)includes/

vpath %.c $(SOURCE_DIR)

CFLAGS = -Wall -Werror -Wextra -fpic
OFLAGS = -O2

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

ifeq ($(HOSTTYPE), )
$(eval HOSTTYPE := $(shell uname -m)_$(shell uname -s))
endif

.PHONY: all clean fclean re link

all: $(NAME) $(LINK)

$(NAME): $(OBJECTS)
	gcc -shared -o $(NAME) $(LIBFT_PATH)libft.a
	
$(OBJECT_DIR)%.o: %.c $(INCLUDES)
	mkdir -p $(OBJECT_DIR)
	gcc -c -o $@ $(OFLAGS) $(CFLAGS) $< -I$(INCLUDE_DIR) -I$(LIBFT_HEADER)

clean:
	rm -f $(OBJECTS)
	rm -rf $(OBJECT_DIR)

fclean: clean
	rm -f $(LINK)
	rm -f $(NAME)

re: fclean all

$(LINK): $(NAME)
	rm -f $(LINK)
	ln -s $(NAME) $(LINK)

example: $(LINK)
	gcc -o sample example.c -L. -L./$(LIBFT_PATH) -lft_malloc -lft -I./include -I./$(LIBFT_HEADER)
