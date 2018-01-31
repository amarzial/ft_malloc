SOURCE_FILES = manager.c \
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

CFLAGS = -Wall -Werror -Wextra
OFLAGS = -O2
NAME = malloc.a

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)	

$(OBJECT_DIR)%.o: %.c $(INCLUDES)
	mkdir -p $(OBJECT_DIR)
	gcc -c -o $@ $(OFLAGS) $(CFLAGS) $< -I$(INCLUDE_DIR) -I$(LIBFT_HEADER)


example: src/ft_malloc.c
	gcc example.c src/ft_malloc.c -I./include
