ITEMS = Item.o Bag.o
ABILITIES = Ability.o Attack.o Decompile.o Delete.o Dereference.o Exception.o GarbageCollection.o TrialAndError.o
RACES = Race.o Haxxor.o Memory.o Noob.o Pointer.o Template.o
CLASSES = Class.o Bruteforcer.o Guard.o Guru.o JavaDeveloper.o Magician.o
CHARACTERS = Character.o NPC.o Boss.o Player.o
ENVIRONMENTS = Environment.o Area.o World.o
UTILS = Utils.o SelectionListUtils.o
MODERATORS = Arena.o MovementModerator.o

OBJECTS = $(ITEMS) $(ABILITIES) $(RACES) $(CLASSES) $(CHARACTERS) $(ENVIRONMENTS) $(UTILS) $(MODERATORS) Main.o
EXEC = Fingolfin.out
FLAGS = -std=c++0x
CC = g++

all: compile clean

compile: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXEC)
	
%.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
