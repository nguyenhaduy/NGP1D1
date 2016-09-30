CC     = g++     # the c compiler to use
DFLAGS = -std=c++11        # common defines

all: main


# ==== FDATA ENGINE ====
Attribute.o: Attribute.cpp
	$(CC) $(DFLAGS) -c $< -o $@ 
Tuple.o: Tuple.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Condition.o: Condition.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Table.o: Table.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Relation_Ops.o: Relation_Ops.cpp
	$(CC) $(DFLAGS) -c $< -o $@
DB_Engine.o: DB_Engine.cpp
	$(CC) $(DFLAGS) -c $< -o $@
test.o: test.cpp
	$(CC) $(DFLAGS) -c $< -o $@
# ==== MAIN FILE ====
	
main: Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o test.o
	$(CC) $(DFLAGS) test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o -o main.out


clean:
	rm -f *.o
