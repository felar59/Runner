# Nom de l'exécutable final
TARGET = run

# Fichiers source
SRC = src/Main.cpp \
	  src/Loop.cpp \
	  src/Player.cpp \
	  src/Enemy.cpp \
	  src/Tile.cpp \
	  src/Tiles.cpp \
	  src/PauseMenu.cpp \
	  src/ParalaxBG.cpp \
	  src/Collision.cpp \
	  src/gameStates/ManageState.cpp \
	  src/gameStates/GameState.cpp \
	  src/gameStates/MenuState.cpp \

# Compilateur
CXX = g++

# SFML
SFML = -lsfml-graphics -lsfml-window -lsfml-system

# Options de compilation
CXXFLAGS = -Wall -std=c++17 -Iinclude -Iinclude/gameStates

# Règle par défaut
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(SFML)

# Nettoyer les fichiers générés
clean:
	rm -f $(TARGET)