#Fichiers sources (.cpp)
SOURCES= Position/annulus.cpp Position/free2d.cpp Position/free3d.cpp Position/square.cpp Vec/Vec.cpp Birds/Flock.cpp Birds/main_flock.cpp #test.cpp 

# Compilateur
CXX=g++

# Arguments pour l'étape d'édition de liens
LDFLAGS=-Wall -Wextra

# Arguments pour l'etape de compilation : tous les avertissements (et même plus) sauf "ignored-attributes" (présence d'un bug dans GCC version 6 et plus)
CPPFLAGS=-Wall -Wextra -Wno-unused-parameter

# Librairies :
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Liste des fichier objet (*.o), générés automagiquement
OBJETS=$(subst .cpp,.o,$(SOURCES))

all: build

mytarget:
	(rm -f Birds/*.o )

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
