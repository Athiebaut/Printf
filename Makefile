SRC =	ft_print_int_signed.c ft_printf.c \
	ft_print_int_unsigned.c ft_print_ptr.c \
	ft_print_hexadecimal.c
SRCB =	ft_printf_bonus.c ft_printf_parse_bonus.c \
	ft_print_char_bonus.c
SRCS = ${addprefix Src/, ${SRC}}
SRCSB = ${addprefix Srcb/, ${SRCB}}
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = libftprintf.a
NAMEB = libftprintf_bonus.a
LIBC = ar -rcs
CC = cc 
RM = rm -f
FLAGS = -Wall -Werror -Wextra 

.c.o:
	${CC} ${FLAGS} -c $< -o${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}	

all: ${NAME}

bonus: ${OBJSB}
	${LIBC} ${NAMEB} ${OBJSB}	


clean: 
	${RM} ${OBJS}
	${RM} ${OBJSB}

fclean: clean
	${RM} ${NAME}
	${RM} ${NAMEB}

re: fclean all

.PHONY: all clean fclean re 
