CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I.
# IFLAGS = -L./libft -lft
NAME = libftprintf.a
#LIBFT = libft.a
SRCS = ft_printf.c ft_hex_printf.c ft_printargument.c ft_ptr_printf.c ft_putunsigned.c ft_utils_printf.c ft_calloc.c ft_isdigit.c ft_itoa.c ft_strlen.c ft_toupper.c ft_putchar_fd.c ft_putstr_fd.c
BONUS = ft_printf.c ft_hex_printf.c ft_printargument.c ft_ptr_printf.c ft_putunsigned.c ft_functions2_bonus.c ft_utils_bonus.c ft_calloc.c ft_isdigit.c ft_itoa.c ft_strlen.c ft_toupper.c ft_atoi.c ft_putchar_fd.c ft_putstr_fd.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

# $(LIBFT) :
# 	if [ ! -d "libft" ]; then git clone git@vogsphere.***REMOVED***.de:vogsphere/intra-uuid-1c36f609-e9da-4d0d-aabe-90f7da6596d8-5229704-***REMOVED*** libft; fi
# 	$(MAKE) -C libft all

%.o : %.c
	@$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

all: $(NAME)

bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

#libft/libft.a
# bonus: $(BONUS_OBJS)
# 	make -C libft all
# 	make -C libft clean
# 	@ar rcs $(NAME) $(BONUS_OBJS)

clean:
	@rm -f libft/*.o
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a

re: fclean all
