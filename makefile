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
engine_test.o: engine_test.cpp
	$(CC) $(DFLAGS) -c $< -o $@
parse_test.o: parse_test.cpp
	$(CC) $(DFLAGS) -c $< -o $@
interp_main.o: interp_main.cpp
	$(CC) $(DFLAGS) -c $< -o $@
UnitTestParser.o: UnitTestParser.cpp
	$(CC) $(DFLAGS) -c $< -o $@
server.o: server.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Application_Server.o: Application_Server.cpp
	$(CC) $(DFLAGS) -c $< -o $@
Application_Client.o: Application_Client.cpp
	$(CC) $(DFLAGS) -c $< -o $@ 
client.o: client.cpp
	$(CC) $(DFLAGS) -c $< -o $@


# ==== MAIN FILE ====
	
main: server.o Application_Server.o interp_main.o parse_test.o engine_test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o Application_Client.o client.o UnitTestParser.o

# ==== Test Engine ====
	$(CC) $(DFLAGS) engine_test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o -o EngineTest.out

# ==== Test Parser ====
	$(CC) $(DFLAGS) parse_test.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o -o ParserTest.out

# ==== Unit Test Parser ====
	$(CC) $(DFLAGS) UnitTestParser.o Parser.o -o UnitParserTest.out

# ==== Test Interperter ====
	$(CC) $(DFLAGS) interp_main.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o -o main.out

# ==== Database Server ====
	$(CC) $(DFLAGS) server.o Application_Server.o Attribute.o Tuple.o Table.o Condition.o Relation_Ops.o DB_Engine.o DB_Set.o Parser.o -o server

# ==== Database Client ====
	$(CC) $(DFLAGS) client.o Application_Client.o -o client

clean:
	rm -f *.o *.out
