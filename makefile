CC     = g++     # the c compiler to use
DFLAGS = -std=c++11        # common defines

all: main


# ==== FDATA ENGINE ====
Attribute.o: Attribute.cpp
	$(CC) $(DFLAGS) -c $< -o $@ 
Tuple.o: Tuple.cpp Attribute.o
	$(CC) $(DFLAGS) -c $< -o $@
Condition.o: Condition.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Table.o: Table.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Relation_Ops.o: Relation_Ops.cpp
	$(CC) $(DFLAGS) -c $< -o $@
DB_Engine.o: DB_Engine.cpp
	$(CC) $(DFLAGS) -c $< -o $@
DB_Set.o: DB_Set.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Parser.o: Parser.cpp
	$(CC) $(DFLAGS) -c $< -o $@
parse_test.o: parse_test.cpp
	$(CC) $(DFLAGS) -c $< -o $@
#main.o: main.cpp
#	$(CC) $(DFLAGS) -c $< -o $@

# ==== MAIN FILE ====
	
main: parse_test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o
	$(CC) $(DFLAGS) parse_test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o -o main.out


clean:
	rm -f *.o
