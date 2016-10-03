#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include<iostream>
#include<vector>
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
Tuple templ;
Table* relation;

void make_relation(){
	//Make relation
	name = Attribute("", true, "name", 10);
	mascot = Attribute("", false, "mascot", 10);
	conquests = Attribute (-99, false, "conquests");
	templ_attr.push_back(name);
	templ_attr.push_back(mascot);
	templ_attr.push_back(conquests);
	relation = new Table("Pirates", templ);
 
	name.set_String_Value("Bob");
	mascot.set_String_Value("parrot");
	conquests.set_Int_Value(29);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;
  
	templ = Tuple(templ_attr);

	relation->insert(templ);
  
	name.set_String_Value("Joe");
	mascot.set_String_Value("skull");
	conquests.set_Int_Value(2);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;

	templ = Tuple(templ_attr);

	relation->insert(templ);

	name.set_String_Value("Davy");
	mascot.set_String_Value("octopus");
	conquests.set_Int_Value(345);

	templ_attr[0] = name;
	templ_attr[1] = mascot;
	templ_attr[2] = conquests;

	templ = Tuple(templ_attr);

	relation->insert(templ);
}


TEST_CASE( "Test Making Relation")
{
	make_relation();
	REQUIRE (relation->get_Name() == "Pirates");
	REQUIRE (relation->get_Template_Tuple().get_Attribute == 3);
}

TEST_CASE( "Test Creating Table")
{
	make_relation();
	Table* relation2 = DB_Engine::create_relation("Pirates2",templ);
	DB_Engine::show(*relation2);
	REQUIRE (relation2->get_Name() == "Pirates2");
}