CFLAGS= -Wall -g
LDFLAGS= -lMLV -lm
CC= gcc
OPT=-O2
OBJ= $(BIN)Main.o $(BIN)Graphique.o $(BIN)Vaisseau.o $(BIN)Missile.o $(BIN)Ennemi.o $(BIN)Allié.o  $(BIN)Collision.o $(BIN)Menu.o $(BIN)Evenement.o $(BIN)Highscore.o $(BIN)Sound.o $(BIN)Déplacement.o $(BIN)Tir.o $(BIN)Explosion.o $(BIN)Ressource.o
SRC=src/
BIN=bin/
INCLUDE=include/

$(BIN)Shoot’em_up: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
 
$(BIN)Main.o: $(SRC)Main.c $(INCLUDE)Graphique.h $(INCLUDE)Vaisseau.h $(INCLUDE)Missile.h $(INCLUDE)Ennemi.h $(INCLUDE)Allié.h $(INCLUDE)Collision.h $(INCLUDE)Menu.h $(INCLUDE)Evenement.h $(INCLUDE)Highscore.h $(INCLUDE)Sound.h $(INCLUDE)Explosion.h $(INCLUDE)Ressource.h

$(BIN)Graphique.o: $(SRC)Graphique.c $(INCLUDE)Graphique.h $(INCLUDE)Vaisseau.h $(INCLUDE)Missile.h $(INCLUDE)Ennemi.h $(INCLUDE)Allié.h $(INCLUDE)Menu.h $(INCLUDE)Explosion.h $(INCLUDE)Ressource.h

$(BIN)Vaisseau.o: $(SRC)Vaisseau.c $(INCLUDE)Vaisseau.h 

$(BIN)Missile.o: $(SRC)Missile.c $(INCLUDE)Missile.h $(INCLUDE)Tir.h

$(BIN)Ennemi.o: $(SRC)Ennemi.c $(INCLUDE)Ennemi.h $(INCLUDE)Vaisseau.h $(INCLUDE)Missile.h $(INCLUDE)Déplacement.h $(INCLUDE)Explosion.h

$(BIN)Allié.o: $(SRC)Allié.c $(INCLUDE)Allié.h $(INCLUDE)Vaisseau.h $(INCLUDE)Missile.h $(INCLUDE)Evenement.h

$(BIN)Collision.o: $(SRC)Collision.c $(INCLUDE)Collision.h $(INCLUDE)Ennemi.h $(INCLUDE)Allié.h  $(INCLUDE)Missile.h $(INCLUDE)Explosion.h

$(BIN)Menu.o: $(SRC)Menu.c $(INCLUDE)Menu.h

$(BIN)Evenement.o: $(SRC)Evenement.c $(INCLUDE)Evenement.h 

$(BIN)Highscore.o: $(SRC)Highscore.c $(INCLUDE)Highscore.h $(INCLUDE)Ressource.h

$(BIN)Sound.o: $(SRC)Sound.c $(INCLUDE)Sound.h $(INCLUDE)Ressource.h

$(BIN)Ressource.o: $(SRC)Ressource.c $(INCLUDE)Ressource.h

$(BIN)Déplacement.o: $(SRC)Déplacement.c $(INCLUDE)Déplacement.h $(INCLUDE)Vaisseau.h 

$(BIN)Tir.o: $(SRC)Tir.c $(INCLUDE)Tir.h $(INCLUDE)Vaisseau.h $(INCLUDE)Missile.h

$(BIN)Explosion.o: $(SRC)Explosion.c $(INCLUDE)Explosion.h $(INCLUDE)Sound.h

$(BIN)%.o: $(SRC)%.c
	$(CC) -c $< $(CFLAGS) $(OPT) -o $@

clean:
	rm -f $(BIN)*.o

mrproper: clean
	rm -f $(BIN)Shoot’em_up
	

