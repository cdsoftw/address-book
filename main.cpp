#include "P3_header.h"

/*
=======================================================================================
 Name        : DapC_00_P3_main.cpp
 Author      : Cole Dapprich
 Version     : 2.0
 Copyright   : 2015
 Description : This .cpp file prints the menu, reads in commands, and calls the func-
	       tions for an address book.
 Citations   : Used a cplusplus.com forum post to learn how to clear the screen without
		   using system("CLS"), because it is considered bad practice.
		   (http://www.cplusplus.com/forum/beginner/3304/)
=======================================================================================
*/

int main (void)
{
	// list declaration
	list<Contact> address_book;
	
	// variable declarations
	ifstream f_in;
	string cmd;
	int IDcount = 1;
	
	// print out programmer info
	display_info();
	
	// print out welcome message and menu
	cout << "\n\t\tWelcome to Address Book 2.0!\n"
	     << "\nAVAILABLE COMMANDS:\n"
			 << "\tadd name <name> ==> Add a new name (First Last) to the Address Book\n"
			 << "\tadd spouse <uid> <name> ==> Add spouse of <uid> (First Last) to the Address Book\n"
			 << "\tadd child <uid> <name> ==> Add a child of <uid> (First Last) to the Address Book\n"
			 << "\tadd address1 <uid> <address> ==> Add/change the address for <uid>\n"
			 << "\tadd city <uid> <city> ==> Add/change the city for <uid>\n"
			 << "\tadd state <uid> <state> ==> Add/change the state for <uid>\n"
			 << "\tadd zip <uid> <zipcode> ==> Add/change the zipcode for <uid>\n"
			 << "\tadd date_birth <uid> <ddmmyyyy> ==> Add/change the birthday for <uid>\n"
			 << "\tadd date_wedding <uid> <ddmmyyyy> ==> Add/change the wedding day for <uid>\n"
			 << "\tadd date_death <uid> <ddmmyyyy> ==> Add/change the date of death for <uid>\n"
			 << "\tsearch <name> ==> searches for name (First Last) and returns the <uid>, if found\n"
			 << "\tprint all ==> Prints a list of ALL of the names in the Address Book with their <uid> <name>\n"
			 << "\tprint <uid> ==> Prints all of the fields for <uid>\n"
			 << "\tfile ==> user is prompted for a filename that contains correctly formatted commands\n"
			 << "\t               --- the file must be in CSV format with one full command per line\n"
			 << "\tquit ==> processing complete\n\n"
			 << "cmd> ";
			 
	
	// obtain command, call appropriate function, loop if desired
	do
	{
		getline(cin, cmd);
		
		if (cmd == "commands" || cmd == "COMMANDS")
		{
			// "clear" the screen
			cout << string(50, '\n'); // http://www.cplusplus.com/forum/beginner/3304/
			
			//output list of commands
			cout << "\tadd name <name> ==> Add a new name (First Last) to the Address Book\n"
			 << "\tadd spouse <uid> <name> ==> Add spouse of <uid> (First Last) to the Address Book\n"
			 << "\tadd child <uid> <name> ==> Add a child of <uid> (First Last) to the Address Book\n"
			 << "\tadd address1 <uid> <address> ==> Add/change the address for <uid>\n"
			 << "\tadd city <uid> <city> ==> Add/change the city for <uid>\n"
			 << "\tadd state <uid> <state> ==> Add/change the state for <uid>\n"
			 << "\tadd zip <uid> <zipcode> ==> Add/change the zipcode for <uid>\n"
			 << "\tadd date_birth <uid> <ddmmyyyy> ==> Add/change the birthday for <uid>\n"
			 << "\tadd date_wedding <uid> <ddmmyyyy> ==> Add/change the wedding day for <uid>\n"
			 << "\tadd date_death <uid> <ddmmyyyy> ==> Add/change the date of death for <uid>\n"
			 << "\tsearch <name> ==> searches for name (First Last) and returns the <uid>, if found\n"
			 << "\tprint all ==> Prints a list of ALL of the names in the Address Book with their <uid> <name>\n"
			 << "\tprint <uid> ==> Prints all of the fields for <uid>\n"
			 << "\tfile ==> user is prompted for a filename that contains correctly formatted commands\n"
			 << "\t             --- the file must be in CSV format with one full command per line\n"
			 << "\tquit ==> processing complete\n\n"
			 << "cmd> ";
		}
		
		else if (cmd.compare(0, 9, "add name ") == 0 || cmd.compare(0, 9, "ADD NAME ") == 0)
		{
			addName(address_book, cmd, IDcount);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 11, "add spouse ") == 0 || cmd.compare(0, 11, "ADD SPOUSE ") == 0)
		{
			addSpouse(address_book, cmd, IDcount);
			cout << "\ncmd> ";
		}

		else if (cmd.compare(0, 10, "add child ") == 0 || cmd.compare(0, 10, "ADD CHILD ") == 0)
		{
			add_child(address_book, cmd, IDcount);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 13, "add address1 ") == 0 || cmd.compare(0, 13, "ADD ADDRESS1 ") == 0)
		{
			addStreet(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 9, "add city ") == 0 || cmd.compare(0, 9, "ADD CITY ") == 0)
		{
			addCity(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 10, "add state ") == 0 || cmd.compare(0, 10, "ADD STATE ") == 0)
		{
			addState(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 8, "add zip ") == 0 || cmd.compare(0, 8, "ADD ZIP ") == 0)
		{
			addZip(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 15, "add date_birth ") == 0 || cmd.compare(0, 15, "ADD DATE_BIRTH ") == 0)
		{
			addBirthdate(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 17, "add date_wedding ") == 0 || cmd.compare(0, 17, "ADD DATE_WEDDING ") == 0)
		{
			addWeddingDate(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 15, "add date_death ") == 0 || cmd.compare(0, 15, "ADD DATE_DEATH ") == 0)
		{
			addDeathDate(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 7, "search ") == 0 || cmd.compare(0, 7, "SEARCH ") == 0)
		{
			search(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd == "print all" || cmd == "PRINT ALL")
		{
			printAll(address_book);
			cout << "\ncmd> ";
		}
		
		else if (cmd.compare(0, 6, "print ") == 0 || cmd.compare(0, 6, "PRINT ") == 0)
		{
			print(address_book, cmd);
			cout << "\ncmd> ";
		}
		
		else if (cmd == "file" || cmd == "FILE")
		{
			csv_load(address_book, f_in, IDcount);
			cout << "\ncmd> ";
		}
		
		else if (cmd == "quit" || cmd == "QUIT")
		{
			// close the files
			f_in.close();
			
			cout << "Have a good day and a pleasant tomorrow! Good-bye.\n";
		}
		
		else
		{
			cout << "ERROR: Invalid input. Either you entered an unrecognized command or used an incorrect number of parameters." << endl;
			cout << "\ncmd> ";
		}
		
	} while (cmd != "quit" && cmd != "QUIT");
	
	return 0;
}
