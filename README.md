# NGP1D1
CSCE 315 Project 1 Second delieverable
Relation Database Management System


Group Member

1. Wesley Ng
2. Duy Nguyen
3. Muhammad S Faruqui


How to compile the project: <br />
	There are total 3 tests in the project: Engine Test, Parser Test, and Interpreter Test. <br />
	To chose which test you want to run, open the makefile. You will see 3 tested are listed at the bottom of the makefile. <br />
	Uncomment the test you want to run and comment out the other two. <br />
	From the source folder run the makefile to compile every files. <br />
	After finish compiling, run the main.out to start the test program. <br />
	
	Altenately you can use g++ -std=c++11 to manually compile every single *.cpp file and link them with the tests you want to run. 
	Run the a.out to execute the test program. 
	This can be run on compute.cse.tamu.edu


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
