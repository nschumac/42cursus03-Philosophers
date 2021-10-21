NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra

SOURCES =	sources/helper.c				\
			sources/helper2.c				\
			sources/philosophers.c			\
			sources/threads.c				\

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	@$(CC) $(CCFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo $(NAME) built!

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all