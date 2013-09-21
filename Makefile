NAME=		libmy_malloc_$(HOSTTYPE).so

FINAL_NAME=	libmy_malloc.so

RM=		rm -f

CC=		gcc

CFLAGS=		-fPIC -g -lpthread

MALLOC_LIB_SRC=         malloc.c \
                        realloc.c \
			free.c

MALLOC_LIB_OBJ=		$(MALLOC_LIB_SRC:.c=.o)

all:			$(NAME)

$(NAME):		$(MALLOC_LIB_OBJ)
			gcc -shared -Wl,-soname,$(NAME) -o $(NAME) $(MALLOC_LIB_OBJ) $(CFLAGS)
			ln -s $(NAME) $(FINAL_NAME)
clean:
			$(RM) $(MALLOC_LIB_OBJ)

fclean:			clean
			$(RM) $(NAME) $(FINAL_NAME)

re:			fclean clean all