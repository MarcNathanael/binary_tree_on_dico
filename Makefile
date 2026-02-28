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

# Lance le programme avec les arguments par défaut
run: $(EXEC)
	./$(EXEC) dico.csv "Linux"

# Lance Valgrind avec les arguments par défaut pour vérifier les fuites
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC) dico.csv "Linux"

# --- Règles de nettoyage ---

# Supprime les fichiers objets (.o)
clean:
	rm -f $(OBJS)

# Supprime les objets et l'exécutable
fclean: clean
	rm -f $(EXEC)

re: fclean all

# Déclare les règles qui ne sont pas des fichiers
.PHONY: all run valgrind clean fclean re