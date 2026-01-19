# Nom de l'exécutable
TARGET = main

# Compilateur
CXX = g++
# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17

# Tous les fichiers .cpp du dossier courant
SRCS = $(wildcard *.cpp)
# Fichiers objets correspondants
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable à partir des fichiers objets
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)

# Règle "phony" pour éviter les conflits avec des fichiers du même nom
.PHONY: all clean
