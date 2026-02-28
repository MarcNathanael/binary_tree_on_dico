CC = gcc
CFLAGS = -Wall -Wextra -g
EXEC = dico_tree

SRCS = main.c tree.c
OBJS = $(SRCS:.c=.o)

# --- Règles principales ---

# Règle par défaut 
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c tree.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Règles d'exécution avec arguments ---

run: $(EXEC)
	./$(EXEC) dico.csv "Linux"
	
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC) dico.csv "Linux"

# --- Règles de nettoyage ---

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all

# Déclare les règles qui ne sont pas des fichiers
.PHONY: all run valgrind clean fclean re