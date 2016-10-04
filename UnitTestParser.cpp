#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include "Parser.h"
#include <sstream>
#include <fstream>

Parser p;

TEST_CASE(" ")
{
	std::string result, test;
	std::stringstream ss;
	test = "";
	token t = p.parse(test);
	t.print(ss);
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

TEST_CASE("opeN _th1z_1s_atest1 ;")
{
	std::string result, test;
	std::stringstream ss;
	test = "opeN _th1z_1s_atest1 ;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\topen_cmd()\n\t\t\tidentifier(_th1z_1s_atest1)\n\tempty()\n");
}

TEST_CASE("ope _th1z_1s_atest1 ;")
{
	std::string result, test;
	std::stringstream ss;
	test = "ope _th1z_1s_atest1 ;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

TEST_CASE("close close_cmd_test;")
{
	std::string result, test;
	std::stringstream ss;
	test = "close close_cmd_test;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\tclose_cmd()\n\t\t\tidentifier(close_cmd_test)\n\tempty()\n");
}

TEST_CASE("SAVE \t \n save_this;")
{
	std::string result, test;
	std::stringstream ss;
	test = "SAVE save_this;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\tsave_cmd()\n\t\t\tidentifier(save_this)\n\tempty()\n");
}

TEST_CASE("sAVE 2save_this;")
{
	std::string result, test;
	std::stringstream ss;
	test = "cloe close_cmd_test;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

TEST_CASE("exit;")
{
	std::string result, test;
	std::stringstream ss;
	test = "exit;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\texit_cmd()\n\tempty()\n");
}

TEST_CASE("sHOW a1234;")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW a1234;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\tshow_cmd()\n\t\t\tatomic_expr()\n\t\t\t\tidentifier(a1234)\n\tempty()\n");
}

TEST_CASE("sHOW (_testname);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (_testname);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tcommand()\n\t\tshow_cmd()\n\t\t\tatomic_expr()\n\t\t\t\texpr()\n\t\t\t\t\tatomic_expr()\n\t\t\t\t\t\tidentifier(_testname)\n\tempty()\n");
}

//Test 1
TEST_CASE("sHOW (selecT (a > b) test);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test1.txt");
	test = "sHOW (selecT (a > b) test);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (selecT a > b test);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (selecT a > b test);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 2
TEST_CASE("sHOW (selecT (a > b) (Select ((_ != operand)) test));")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test2.txt");
	test = "sHOW (selecT (a > b) (Select ((_ != operand)) test));";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 3
TEST_CASE("sHOW (project (this, is, a , test) test22);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test3.txt");
	test = "sHOW (project (this, is, a , test) test22);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (project () test22);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (project () test22);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

TEST_CASE("sHOW (project (this,) test22);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (project (this,) test22);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 4
TEST_CASE("sHOW (rename (this, is, a , test) test1);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test4.txt");
	test = "sHOW (rename (this, is, a , test) test1);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (rename (this, is, a ,) test1);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (project (this,) test22);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 5
TEST_CASE("sHOW ((rename (this, is, a , test) test1)+(project (this, too, is , test2) test22));")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test5.txt");
	test = "sHOW ((rename (this, is, a , test) test1)+(project (this, too, is , test2) test22));";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (+(project (this, too, is , test2) test22));")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (+(project (this, too, is , test2) test22));";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 6
TEST_CASE("sHOW (name-(project (this, too, is , test2) test22));")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test6.txt");
	test = "sHOW (name-(project (this, too, is , test2) test22));";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (name-();")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (name-();";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 7
TEST_CASE("sHOW (name1*name2);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test7.txt");
	test = "sHOW (name1*name2);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("sHOW (*);")
{
	std::string result, test;
	std::stringstream ss;
	test = "sHOW (*);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 8
TEST_CASE("CREATE TABLE animals(test1 integer, name VARCHAR(20), kind VARCHAR(8), years INTEGER, test2 varchar(9001)) PRIMARY KEY(name, kind);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test8.txt");
	test = "CREATE TABLE animals(test1 integer, name VARCHAR(20), kind VARCHAR(8), years INTEGER, test2 varchar(9001)) PRIMARY KEY(name, kind);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("CREATE TABLE animals(test1 integer, name VARCHAR(20), kind VARCHAR(8), years INTEGER,) PRIMARY KEY(name, kind);")
{
	std::string result, test;
	std::stringstream ss;
	test = "CREATE TABLE animals(test1 integer, name VARCHAR(20), kind VARCHAR(8), years INTEGER,) PRIMARY KEY(name, kind);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 9
TEST_CASE("update pirates set booty = \"a_lot\", rum = 0 where abc == abc && b != b || c >= c;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test9.txt");
	test = "update pirates set booty = \"a_lot\", rum = 0 where abc == abc && b != b || c >= c;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("update pirates set booty = \"a_lot\", where abc == abc && b != b || c >= c;")
{
	std::string result, test;
	std::stringstream ss;
	test = "update pirates set booty = \"a_lot\", where abc == abc && b != b || c >= c;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 10
TEST_CASE("INSERT INTO species VALUES FROM RELATION project (kind) animals;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test10.txt");
	test = "INSERT INTO species VALUES FROM RELATION project (kind) animals;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("INSERT INTO species VALUES FROM RELATION project kind animals;")
{
	std::string result, test;
	std::stringstream ss;
	test = "INSERT INTO species VALUES FROM RELATION project kind animals;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 11
TEST_CASE("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1, 44, \"_testing56\");")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test11.txt");
	test = "INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1, 44, \"_testing56\");";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("INSERT INTO animals VALUES FROM (Tweety, \"bird\", 1, 44, \"_testing56\");")
{
	std::string result, test;
	std::stringstream ss;
	test = "INSERT INTO animals VALUES FROM (Tweety, \"bird\", 1, 44, \"_testing56\");";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 12
TEST_CASE("deleTe FROM relation_name where 1 >= 2;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test12.txt");
	test = "deleTe FROM relation_name where 1 >= 2;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("deleTe FROM 3relation_name where 1 >= 2;")
{
	std::string result, test;
	std::stringstream ss;
	test = "deleTe FROM 3relation_name where 1 >= 2;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

TEST_CASE("fgyuewagbujc72szwP8C FW 798 2qgj7u;")
{
	std::string result, test;
	std::stringstream ss;
	test = "fgyuewagbujc72szwP8C FW 798 2qgj7u;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 13
TEST_CASE("quesry_test1<-select(1 == 2 || 3 == \"4\")test_over;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test13.txt");
	test = "quesry_test1<-select(1 == 2 || 3 == \"4\")test_over;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 14
TEST_CASE("SAVE save_this;this is invalid;EXIT;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test14.txt");
	test = "SAVE save_this;this is invalid;EXIT;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 15
TEST_CASE("SAVE save_this;this is invalid EXIT;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test15.txt");
	test = "SAVE save_this;this is invalid EXIT;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 16
TEST_CASE("failure;SAVE save_this;this is invalid; exit<- _a*_b;")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;
	ifs.open("./ParserTestCases/Test16.txt");
	test = "failure;SAVE save_this;this is invalid; exit<- _a*_b;";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 17
TEST_CASE("exit; fail with no semicolon")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test17.txt");
	test = "exit; fail with no semicolon";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 18
TEST_CASE("show (select ((5 > 2)||((1 == 2 || \"a\" != \"b\") && (\"4\" != 4))) testing_condition);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test18.txt");
	test = "show (select ((5 > 2)||((1 == 2 || \"a\" != \"b\") && (\"4\" != 4))) testing_condition);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 19
TEST_CASE("show (select ((5 > 2)||((1 == 2 || \"a\" != \"b\") && \"4\" != 4)) testing_condition);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test19.txt");
	test = "show (select ((5 > 2)||((1 == 2 || \"a\" != \"b\") && \"4\" != 4)) testing_condition);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 20
TEST_CASE("show (select (5 > 2||((1 == 2 || \"a\" != \"b\") && \"4\" != 4)) testing_condition);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test20.txt");
	test = "show (select (5 > 2||((1 == 2 || \"a\" != \"b\") && \"4\" != 4)) testing_condition);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

//Test 21
TEST_CASE("show (select (5 > 2||1 == 2 || \"a\" != \"b\" && \"4\" != 4 || 4 < 3) testing_condition);")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test21.txt");
	test = "show (select (5 > 2||1 == 2 || \"a\" != \"b\" && \"4\" != 4 || 4 < 3) testing_condition);";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}

TEST_CASE("^%$")
{
	std::string result, test;
	std::stringstream ss;
	test = "^%$";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	REQUIRE (result == "program()\n\tfail()\n\tempty()\n");
}

//Test 22
TEST_CASE("query1<-test;update treble set a = 1, b = 2, c = 3, d = \"d\" where 1==2||3==4&&5!=6||7>=8;fail;exit;query2<-computer+science")
{
	std::ifstream ifs;
	std::string result, test;
	std::stringstream ss;	
	ifs.open("./ParserTestCases/Test22.txt");
	test = "query1<-test;update treble set a = 1, b = 2, c = 3, d = \"d\" where 1==2||3==4&&5!=6||7>=8;fail;exit;query2<-computer+science";
	token t = p.parse(test);
	t.print(ss);	
	result = ss.str();
	std::string check { istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	REQUIRE (result == check);
}