# NGP1D1
CSCE 315 Project 1 Second delieverable
Relation Database Management System


Group Member

1. Wesley Ng
2. Duy Nguyen
3. Muhammad S Faruqui


<b/><u>How to compile the project:</u></b> <br />
	The project can be run on compute.cs.tamu.edu <br />
	There are total 6program in the project: Engine Test, Parser Test, Unit Parser Test, Interpreter Test, application client, and application server. <br />
	To compile the test, simply just run the makefile.<br />
	To start the Engine Test, run EngineTest.out. <br />
	To start the Parser Test, run ParserTest.out. <br />
	To start the Parser Unit Test, run UnitTestParser.out. <br />
	To start the Interperter Test, run main.out. <br />
	To start the application server, run server <br />
	To start the application client, run client <br />
	
	Altenately you can use g++ -std=c++11 to manually compile every single *.cpp file and link them with the tests you want to run. 
	Run the a.out to execute the test program. 
	
<b/><u>Application:</b></u> <br />
	This application is a simple banking application that allow adimistrator to modify user's info, user's accout, and user's transatrions. <br />
	This application can do the following function: Create New User, Create New Bank Account for User (Debit or Credit), Make Transaction (Deposit or Withdraw), Delete User, Delete User's Account, Delete User's Transaction History, View User's Basic Information, View User's Account Information, View User's Transaction History. <br />
	The application contain the server and the client. Server and client communicate with each other by socket.<br />
	The client takes care of gathering user input and send it to the server. <br />
	the server will use the input, directly work with the RDBMS, and return the result to client. <br />
	<b/>To run the application, open 2 console terminal. <br />
	Run the server first, type in the port you want to use when the program ask. <br />
	After that, run the client and type in the same port when the program sak. <br />
	Follow the instruction on the client console to manipulate the database. </b><br />
	

<b/><u>Unit tests:</b></u> <br />
	Test some dummy data to check how the engine function. <br />
	The dummy data is about the information of pirates. <br />
	The attributes are name, mascot, and conquest. <br />
	The tested operators are: <br />
		- 6 relational algebra operations: selection, projection, renaming, set union, set difference, cross product <br />
		- Natural join <br />
		- Creating and dropping tables (relations) <br />
		- Inserting, updating, and deleting records in a table <br />
		- Show content of a table <br />
		
<b/><u>Parser Unit Tests:</b></u><br />
	- We are taking multiple test cases to check to see if parsing works. <br />
	- We parse certain commands one by one and have the unit test check to see if the output is equivilent to what we expect <br />
	- If not, Catch will tell us which one has errors <br />
	- Each command needs to have a semicolon at the end <br />
	- We saved some commands in text file so it will make it easier for us to test instead of typing out all the commands. <br />
