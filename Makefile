NAME	:= fractol
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code

LIBMLX	:= ./libs/MLX42
LIBPRINTF := ./printf
HEADERS	:= -I $(LIBMLX)/include/MLX42 -I $(LIBPRINTF)
LIBS	:= $(LIBPRINTF)/libftprintf.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:= fract_ol.c color_tools.c ft_atod.c julia.c \
libft_utils.c mandelbrot.c mlx_hooks.c parse_arg.c

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		mkdir -p libs && \
		git clone --depth 1 --branch v2.3.2 https://github.com/codam-coding-college/MLX42 $(LIBMLX) && \
		cmake -S $(LIBMLX) -B $(LIBMLX)/build && \
		make -C $(LIBMLX)/build -j4; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBPRINTF) bonus
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBPRINTF) clean
	@rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBPRINTF) fclean
	@rm -rf libs
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
