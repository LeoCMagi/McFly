#PARTIE A MODIFIER : Liste des fichiers .cpp (et uniquement les .cpp) à compiler
SOURCES= Position/position.h Position/annulus.cpp Position/free2d.cpp Position/free3d.cpp Position/square.cpp Vec/Vec.cpp Birds/Flock.cpp     Birds/main_flock.cpp #test.cpp 
#FIN DE LA PARTIE A MODIFIER

# Nom du compilateur
CXX=g++
# Arguments pour l'étape d'édition de liens : tous les avertissements
LDFLAGS=-Wall -Wextra
# Arguments pour l'etape de compilation : tous les avertissements (et même plus) sauf "ignored-attributes" (présence d'un bug dans GCC version 6 et plus)
CPPFLAGS=-Wall -Wextra
# Librairies : none
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Liste des fichier objet (*.o), générée automagiquement
OBJETS=$(subst .cpp,.o,$(SOURCES))

all: build

build: $(OBJETS)
	$(CXX) $(LDFLAGS) -o run $(OBJETS) $(LDLIBS) 

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	rm $(OBJETS)
	rm -f *~ .depend

include .depend
