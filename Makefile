SRC =	ft_printf.c \
	ft_print_parse.c \
	ft_print_char.c \
	ft_print_str.c \
	ft_print_nbrs.c \
	ft_print_ptr.c \
	ft_print_hexa.c

SRCS = ${addprefix Srcb/, ${SRC}}
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
LIBC = ar rcs
CC = cc 
RM = rm -f
FLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${FLAGS} -c $< -o${<:.c=.o}

${NAME}: ${OBJS}
	make -C Libft
	${LIBC} ${NAME} Libft/*.o ${OBJS} 

all: ${NAME}
	

clean: 
	${RM} ${OBJS}
	${RM} ${OBJSB}
	make clean -C Libft

fclean: clean
	${RM} ${NAME}
	${RM} ${NAMEB}
	make fclean -C Libft

re: fclean all

.PHONY: all clean fclean re 
