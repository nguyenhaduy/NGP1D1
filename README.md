# NGP1D1
CSCE 315 Project 1 Second delieverable
Relation Database Management System


Group Member

1. Wesley Ng
2. Duy Nguyen
3. Muhammad S Faruqui


How to compile the project: <br />
	The project can be run on compute.cs.tamu.edu <br />
	There are total 4 tests in the project: Engine Test, Parser Test, Unit Parser Test, and Interpreter Test. <br />
	To compile the test, simply just run the makefile.<br />
	To start the Engine Test, run EngineTest.out. <br />
	To start the Parser Test, run ParserTest.out. <br />
	To start the Parser Unit Test, run UnitTestParser.out. <br />
	To start the Interperter Test, run main.out. <br />
	
	Altenately you can use g++ -std=c++11 to manually compile every single *.cpp file and link them with the tests you want to run. 
	Run the a.out to execute the test program. 
	

Unit tests: <br />
	Test some dummy data to check how the engine function. <br />
	The dummy data is about the information of pirates. <br />
	The attributes are name, mascot, and conquest. <br />
	The tested operators are: <br />
		- 6 relational algebra operations: selection, projection, renaming, set union, set difference, cross product <br />
		- Natural join <br />
		- Creating and dropping tables (relations) <br />
		- Inserting, updating, and deleting records in a table <br />
		- Show content of a table <br />
		
Parser Unit Tests: <br />
	- We are taking multiple test cases to check to see if parsing works. <br />
	- We parse certain commands one by one and have the unit test check to see if the output is equivilent to what we expect <br />
	- If not, Catch will tell us which one has errors <br />
	- Each command needs to have a semicolon at the end <br />
	- We saved some commands in text file so it will make it easier for us to test instead of typing out all the commands. <br />
