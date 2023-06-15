SRCS =	ft_print_int_signed.c ft_printf.c \
	ft_print_int_unsigned.c ft_print_ptr.c \
	ft_print_hexadecimal.c

OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
LIBC = ar -rcs
CC = cc 
RM = rm -f
FLAGS = -Wall -Werror -Wextra 

.c.o:
	${CC} ${FLAGS} -c $< -o${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}	

all: ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
