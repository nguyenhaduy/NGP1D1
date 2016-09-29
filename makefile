CC     = g++     # the c compiler to use
DFLAGS = -std=c++11        # common defines

all: main


# ==== FDATA ENGINE ====
Attribute.o: Attribute.cpp
	$(CC) $(DFLAGS) -c $< -o $@ 
Tuple.o: Tuple.cpp Attribute.o
	$(CC) $(DFLAGS) -c $< -o $@
Condition.o: Condition.cpp Tuple.o Attribute.o
	$(CC) $(DFLAGS) -c $< -o $@
Table.o: Table.cpp Tuple.o Condition.o
	$(CC) $(DFLAGS) -c $< -o $@
Relation_Ops.o: Relation_Ops.cpp Table.cpp Attribute.o Condition.o
	$(CC) $(DFLAGS) -c $< -o $@
DB_Engine.o: DB_Engine.cpp Table.o Attribute.o Condition.o
	$(CC) $(DFLAGS) -c $< -o $@
main.o: main.cpp
	$(CC) $(DFLAGS) -c $< -o $@
# ==== MAIN FILE ====
	
main: main.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o
	$(CC) $(DFLAGS) main.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o -o main.out


clean:
	rm -f *.o
