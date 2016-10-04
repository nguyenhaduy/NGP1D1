#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <vector>
#include "DB_Engine.h"
#include "Tuple.h"
#include "Table.h"
#include "Attribute.h"
#include "Relation_Ops.h"
#include "Condition.h"

Attribute name;
Attribute mascot;
Attribute conquests;
vector<Attribute> templ_attr;
Tuple templ, tuple0, tuple1, tuple2;
Table* relation;
Table* relation2;

void make_relation(){
	//Make relation
	name = Attribute("", true, "name", 10);
	mascot = Attribute("", false, "mascot", 10);
	conquests = Attribute (-99, false, "conquests");
	templ_attr.push_back(name);
	templ_attr.push_back(mascot);
	templ_attr.push_back(conquests);
	templ= Tuple(templ_attr);
	relation = new Table("Pirates", templ);
 
	name.set_String_Value("Bob");
	mascot.set_String_Value("parrot");
	conquests.set_Int_Value(29);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;
  
	tuple0 = Tuple(templ_attr);

	relation->insert(tuple0);
  
	name.set_String_Value("Joe");
	mascot.set_String_Value("skull");
	conquests.set_Int_Value(2);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;

	tuple1 = Tuple(templ_attr);

	relation->insert(tuple1);

	name.set_String_Value("Davy");
	mascot.set_String_Value("octopus");
	conquests.set_Int_Value(345);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;

	tuple2 = Tuple(templ_attr);

	relation->insert(tuple2);
}


TEST_CASE( "Test Making Relation")
{
	make_relation();	
	vector<Tuple> check_tuple;
	check_tuple = relation->get_Tuples();
	REQUIRE (relation->get_Name() == "Pirates");
	REQUIRE (relation->get_Template_Tuple() == templ);
	REQUIRE (check_tuple.size() == 3);
	REQUIRE (check_tuple[0] == tuple0);
	REQUIRE (check_tuple[1] == tuple1);
	REQUIRE (check_tuple[2] == tuple2);
}

TEST_CASE( "Test Creating Relation")
{
	relation2 = DB_Engine::create_relation("Pirates2",templ);
	vector<Tuple> check_tuple;
	check_tuple = relation2->get_Tuples();
	REQUIRE (relation2->get_Name() == "Pirates2");
	REQUIRE (relation2->get_Template_Tuple() == templ);
	REQUIRE (check_tuple.size() == 0);
}

TEST_CASE( "Test Insert Relation")
{
	DB_Engine::insert_relation(relation2, *relation);	
	vector<Tuple> check_tuple;
	check_tuple = relation2->get_Tuples();
	REQUIRE (relation2->get_Name() == "Pirates2");
	REQUIRE (relation2->get_Template_Tuple() == templ);
	REQUIRE (check_tuple.size() == 3);
	REQUIRE (check_tuple[0] == tuple0);
	REQUIRE (check_tuple[1] == tuple1);
	REQUIRE (check_tuple[2] == tuple2);
}

TEST_CASE( "Test Select With Small Number of Conquests Condition")
{
	// selecting pirates with conquests less than 30 from relation2
	Condition_Sing few_conquest_sing("conquests", "<=", "30");
	Condition few_conquest(few_conquest_sing);
	Table* query = Relation_Ops::select(few_conquest, *relation2);	
	vector<Tuple> check_tuple;
	check_tuple = query->get_Tuples();
	REQUIRE (query->get_Name() == "select_table");
	REQUIRE (query->get_Template_Tuple() == templ);
	REQUIRE (check_tuple.size() == 2);
	REQUIRE (check_tuple[0] == tuple0);
	REQUIRE (check_tuple[1] == tuple1);
}

TEST_CASE( "Test Remove Tuples Based on Conditions")
{
	// removing pirates with conquests less than 30 from relation2
	Condition_Sing few_conquest_sing("conquests", "<=", "30");
	Condition few_conquest(few_conquest_sing);
	DB_Engine::remove_query(relation2, few_conquest);
	vector<Tuple> check_tuple;
	check_tuple = relation2->get_Tuples();
	REQUIRE (relation2->get_Name() == "Pirates2");
	REQUIRE (relation2->get_Template_Tuple() == templ);
	REQUIRE (check_tuple.size() == 1);
	REQUIRE (check_tuple[0] == tuple2);
}

TEST_CASE( "Test Project From Relation1")
{
	// removing pirates with conquests less than 30 from relation2
	vector<string> attributes;
	attributes.push_back("name");
	attributes.push_back("mascot");
	Table* query = Relation_Ops::project(attributes, *relation);

	vector<Tuple> check_tuple;

	Attribute name, mascot;
	vector<Attribute> templ_attr;

	name = Attribute("", true, "name", 10);
	mascot = Attribute("", false, "mascot", 10);
	templ_attr.push_back(name);
	templ_attr.push_back(mascot);
	Tuple templ_check(templ_attr);

	name.set_String_Value("Bob");
	mascot.set_String_Value("parrot");
	templ_attr[0] = name;
	templ_attr[1] = mascot;  
	Tuple tuple_check0 (templ_attr);
  
	name.set_String_Value("Joe");
	mascot.set_String_Value("skull");
	templ_attr[0] = name;
	templ_attr[1] = mascot;
	Tuple tuple_check1 (templ_attr);

	name.set_String_Value("Davy");
	mascot.set_String_Value("octopus");
	templ_attr[0] = name;
	templ_attr[1] = mascot;
	Tuple tuple_check2 (templ_attr);

	check_tuple = query->get_Tuples();
	REQUIRE (query->get_Name() == "project_table");
	// REQUIRE (query->get_Template_Tuple() == templ_check);
	REQUIRE (check_tuple.size() == 3);
	REQUIRE (check_tuple[0] == tuple_check0);
	REQUIRE (check_tuple[1] == tuple_check1);
	REQUIRE (check_tuple[2] == tuple_check2);
}

TEST_CASE( "Test Project From Relation2")
{
	// removing pirates with conquests less than 30 from relation2
	vector<string> attributes;
	attributes.push_back("name");
	attributes.push_back("mascot");
	Table* query = Relation_Ops::project(attributes, *relation2);

	vector<Tuple> check_tuple;

	Attribute name, mascot;
	vector<Attribute> templ_attr;

	name = Attribute("", true, "name", 10);
	mascot = Attribute("", false, "mascot", 10);
	templ_attr.push_back(name);
	templ_attr.push_back(mascot);
	Tuple templ_check(templ_attr);

	name.set_String_Value("Davy");
	mascot.set_String_Value("octopus");
	templ_attr[0] = name;
	templ_attr[1] = mascot;
	Tuple tuple_check (templ_attr);

	check_tuple = query->get_Tuples();
	REQUIRE (query->get_Name() == "project_table");
	// REQUIRE (query->get_Template_Tuple() == templ_check);
	REQUIRE (check_tuple.size() == 1);
	REQUIRE (check_tuple[0] == tuple_check);
}

TEST_CASE( "Test Rename Attributes")
{
	// renaming name and mascot in relation
	vector<string> attributes;
  	attributes.push_back("name");
  	attributes.push_back("mascot");
	vector<string> new_names;
  	new_names.push_back("Pirate Name");
  	new_names.push_back("Flag");
  	Relation_Ops::rename(attributes, new_names, relation);

  	Attribute name, mascot, conquests;
	vector<Attribute> templ_attr;

	name = Attribute("", true, "name", 10);
	mascot = Attribute("", false, "mascot", 10);
  	conquests = Attribute(-99, false, "conquests");
	templ_attr.push_back(name);
	templ_attr.push_back(mascot);
  	templ_attr.push_back(conquests);
	Tuple templ_check(templ_attr);
	vector<Tuple> check_tuple;
	check_tuple = relation->get_Tuples();

	REQUIRE (relation->get_Name() == "Pirates");
	REQUIRE (relation->get_Template_Tuple() == templ_check);
	REQUIRE (check_tuple.size() == 3);
	REQUIRE (check_tuple[0] == tuple0);
	REQUIRE (check_tuple[1] == tuple1);
	REQUIRE (check_tuple[2] == tuple2);
}