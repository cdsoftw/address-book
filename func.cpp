#include "P3_header.h"

/*
============================================================================
 Citations : Used a portion of code found on cplusplus.com to create the
	     for loop that searches for name duplicates
	     (http://www.cplusplus.com/reference/list/list/begin/)
 	     Used a portion of code found on a forum post on stack over-
	     flow to sort the objects alphabetically by member
	     (http://stackoverflow.com/questions/9423480/alphabetically-
	     sort-a-list-of-objects-by-member-in-c)
		 Used cplusplus.com to figure out how to parse the first and last
		 name from the command line and store separately using substrings
		 and how to erase a string from a certain point to the end.
		 (http://www.cplusplus.com/reference/string/string/substr/ 
		 http://www.cplusplus.com/reference/string/string/npos/)
============================================================================
*/

/*
============================================================================
 Function    : display_info
 Parameters  : none
 Return      : none
 Description : This function outputs a block header to the screen that con-
 	       tains the department, class, name, EUID, and myUNT email add-
	       ress.
============================================================================
*/

void display_info()
{
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << endl
	     << "|         Computer Science and Engineering          |" << endl
	     << "|        CSCE 2100 - Computing Foundations I        |" << endl
	     << "|  Cole Dapprich  cwd0042  coledapprich@my.unt.edu  |" << endl
 	     << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << endl;
}

/*
============================================================================
 Function    : comp_by_name_sort
 Parameters  : Contact a, Contact b
 Return      : none
 Description : This is a free function declaration for a custom STL list
	       sort.
============================================================================
*/

	bool comp_by_name_sort(Contact a, Contact b)
	{
		return a.getNamesort() < b.getNamesort();
	}
	
/*
============================================================================
 Function    : addName
 Parameters  : list<Contact>& address_book, string cmd, int& IDcount
 Return      : none
 Description : This function adds a new Contact to the linked list of con-
	       tacts.
============================================================================
*/

void addName(list<Contact>& address_book, string cmd, int& IDcount)
{
	// variable declarations
	string f_name, l_name, nm;
	bool duplicate = false;
	list<Contact>::iterator it;
	
	if (cmd.length() > 9) // ensure that there is another parameter after "add name "
	{
		cmd.erase(0, 9); // erase the command portion of the line input by the user, leaving only the name
		// http://www.cplusplus.com/reference/string/string/substr/
		size_t pos = cmd.find(" "); // find the position of the space between the first and last name
		l_name = cmd.substr(pos + 1); // get the last name and assign it to the variable
				
		cmd.erase(pos, -1); // erase the last name (http://www.cplusplus.com/reference/string/string/npos/)
		f_name = cmd; // assign the first name to the variable
		nm = l_name + " " + f_name; // assign last name, first name to a variable for sorting
				
		// search for duplicates if the list is not empty
		if (!address_book.empty())
		{
			for (it = address_book.begin(); it != address_book.end(); ++it)
			{
				if (it->getNamesort() == nm) // if duplicate is found, output error message and update the bool so that it will not be added to the list
				{
					cout << "DUPLICATE: " << it->getName() << " UID: " << it->getUid() << endl;
					duplicate = true;
				}
			}
		}
		
		if (duplicate == false) // no duplicates found
		{
			address_book.push_front(Contact(nm, f_name, l_name, IDcount)); // create a new object in Contact class and add to the beginning of the list
			IDcount++;
			it = address_book.begin();
			it->setSpouse(it); // sets the spouse to itself to avoid a seg fault when printing an unmarried person's info
			cout << "ADDED: " << it->getName() << " UID: " << it->getUid() << endl;
			address_book.sort(comp_by_name_sort); // sort the entries in the list alphabetically by last name, then first name
		}
	}
	
	else // no input after "add name "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

/*
============================================================================
 Function    : addSpouse
 Parameters  : list<Contact>& address_book, string cmd, int& IDcount
 Return      : none
 Description : This function adds a new Contact to the linked list and links
			   it to the indicated spouse Contact with pointers.
============================================================================
*/

void addSpouse(list<Contact>& address_book, string cmd, int& IDcount)
{
	// variable declarations
	string f_name, l_name, nm, uid;
	bool duplicate = false;
	list<Contact>::iterator it1, it2;
	
	if (cmd.length() > 11) // ensure that there is another parameter after "add spouse "
			{
				cmd.erase(0, 11); // erase the command portion of the line input by the user, leaving only the uid and name
				
				uid = cmd.substr(0, 5); // parse uid from command line
				cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the name
				
				size_t pos = cmd.find(" "); // find the position of the space between the first and last name
				l_name = cmd.substr(pos + 1); // get the last name and assign it to the variable
				
				cmd.erase(pos, -1); // erase the last name
				f_name = cmd; // assign the first name to the variable
				nm = l_name + " " + f_name; // assign last name, first name to a variable for sorting
				
				// search for duplicates if the list is not empty
				if (!address_book.empty())
				{
					for (it1 = address_book.begin(); it1 != address_book.end(); ++it1)
					{
						if (it1->getNamesort() == nm) // if duplicate is found, output error message and update the bool so that it will not be added to the list
						{
							cout << "ALREADY IN LIST: " << it1->getName() << " UID: " << it1->getUid() << endl;
							duplicate = true;
						}
					}
				}
				
				if (duplicate == false) // no duplicates found
				{
					address_book.push_front(Contact(nm, f_name, l_name, IDcount)); // create a new object in Contact class and add to the beginning of the list
					IDcount++;
					it1 = address_book.begin();
					cout << "ADDED: " << it1->getName() << " UID: " << it1->getUid() << endl;
					
					for (it2 = address_book.begin(); it2 != address_book.end(); ++it2)
					{
						if (it2->getUid() == uid)
						{
							it2->setSpouse(it1);
							it1->setSpouse(it2);
						}
					}
					
					address_book.sort(comp_by_name_sort); // sort the entries in the list alphabetically by last name, then first name
				}
			}
	
	else // no input after "add spouse "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

/*
============================================================================
 Function    : addChild
 Parameters  : list<Contact>& address_book, string cmd, int& IDcount
 Return      : none
 Description : This function adds a new Contact to the linked list and links
			   it to the indicated parent Contact with a list of pointers.
============================================================================
*/

void add_child(list<Contact>& address_book, string cmd, int& IDcount)
{
	// variable declarations
	string f_name, l_name, nm, uid;
	bool duplicate = false;
	list<Contact>::iterator it;
	
	if (cmd.length() > 10) // ensure that there is another parameter after "add child "
			{
				cmd.erase(0, 10); // erase the command portion of the line input by the user, leaving only the uid and name
				
				uid = cmd.substr(0, 5); // parse uid from command line
				cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the name
				
				size_t pos = cmd.find(" "); // find the position of the space between the first and last name
				l_name = cmd.substr(pos + 1); // get the last name and assign it to the variable
				
				cmd.erase(pos, -1); // erase the last name
				f_name = cmd; // assign the first name to the variable
				nm = l_name + " " + f_name; // assign last name, first name to a variable for sorting
				
				// search for duplicates if the list is not empty
				if (!address_book.empty())
				{
					for (it = address_book.begin(); it != address_book.end(); ++it)
					{
						if (it->getNamesort() == nm) // if duplicate is found, output error message and update the bool so that it will not be added to the list
						{
							cout << "ALREADY IN LIST: " << it->getName() << " UID: " << it->getUid() << endl;
							duplicate = true;
						}
					}
				}
				
				if (duplicate == false) // no duplicates found
				{
					Contact kid = Contact(nm, f_name, l_name, IDcount);
					address_book.push_front(kid); // create a new object in Contact class and add to the beginning of the list
					IDcount++;
					Contact *pKid = new Contact(nm, f_name, l_name, IDcount);
					it = address_book.begin();
					it->setSpouse(it); // sets the spouse to itself to avoid a seg fault when printing an unmarried person's info
					cout << "ADDED: " << it->getName() << " UID: " << it->getUid() << endl;
					
					for (it = address_book.begin(); it != address_book.end(); ++it)
					{
						if (it->getUid() == uid) // executes only when the correct entry is found
						{
							it->addChild(pKid);
						}
					}
					
					address_book.sort(comp_by_name_sort); // sort the entries in the list alphabetically by last name, then first name
				}
			}
	
	else // no input after "add child "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addStreet(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 13)
	{
		cmd.erase(0, 13); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setAddress(cmd);
				cout << "ADDED ADDRESS1: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add address1 "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addCity(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 9)
	{
		cmd.erase(0, 9); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setCity(cmd);
				cout << "ADDED CITY: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add city "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addState(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 10)
	{
		cmd.erase(0, 10); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setState(cmd);
				cout << "ADDED STATE: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add state "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addZip(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 8)
	{
		cmd.erase(0, 8); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setZip(cmd);
				cout << "ADDED ZIP: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add zip "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addBirthdate(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 15)
	{
		cmd.erase(0, 15); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setBirthdate(cmd);
				cout << "ADDED BIRTHDAY: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add date_birth "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addWeddingDate(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 17)
	{
		cmd.erase(0, 17); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setWeddingDate(cmd);
				cout << "ADDED WEDDING-DAY: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add date_wedding "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

void addDeathDate(list<Contact>& address_book, string cmd)
{
	string uid;
	list<Contact>::iterator it;
	
	if (cmd.length() > 11)
	{
		cmd.erase(0, 11); // remove the command portion, leaving only the uid and address
		
		uid = cmd.substr(0, 5); // parse uid from command line
		cmd.erase(0, 6); // erase uid ("IDxxx ") from command line, leaving only the address
		
		// find the requested user
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == uid)
			{
				it->setDeathDate(cmd);
				cout << "ADDED DATE of DEATH: " << cmd << " UID: " << uid << endl;
			}
		}
	}
	
	else // no input after "add date_death "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

/*
============================================================================
 Function    : search
 Parameters  : list<Contact> address_book, string cmd
 Return      : none
 Description : This function searches for a entry in the list with a name
	       input by the user, then outputs the results.
============================================================================
*/

void search(list<Contact> address_book, string cmd)
{
	// variable declarations
	list<Contact>::iterator it;
	bool found = false;
	
	if (cmd.length() > 7) // ensure that there is another parameter after "search "
	{
		cmd.erase(0, 7); // erase the command portion of the line input by the user, leaving only the name
		
		// loop through the list until the search term is found or the end of the list is reached, and output the results
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getName() == cmd)
			{
				found = true;
				cout << "FOUND: " << cmd << " UID: " << it->getUid() << endl;
			}
		}
		
		if (found == false)
		{
			cout << "NOT FOUND: " << cmd << endl;
		}
	}
	
	else // no input after "search "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}

/*
============================================================================
 Function    : printAll
 Parameters  : list<Contact> address_book
 Return      : none
 Description : This function prints the formatted and sorted list, but first
	       makes sure the list isn't empty.
============================================================================
*/

void printAll(list<Contact> address_book)
{
	// variable declaration
	list<Contact>::iterator it;
	
	if (address_book.empty() == true) // print out an error message if the list is empty
	{
		cout << "NO NAMES IN LIST" << endl;
	}
	
	else // the list is not empty
	{
		// print out the contents of the list
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			it->show_info();
		}
	}
}

/*
============================================================================
 Function    : print
 Parameters  : list<Contact> address_book, string cmd
 Return      : none
 Description : This function searches for a entry in the list with a name
	       input by the user. If found, it prints out all the fields the
		   entry contains.
============================================================================
*/

void print(list<Contact> address_book, string cmd)
{
	// variable declarations
	list<Contact>::iterator it;
	bool found = false;
	
	if (cmd.length() > 6) // ensure that there is another parameter after "print "
	{
		cmd.erase(0, 6); // erase the command portion of the line input by the user, leaving only the uid
		
		// search for the uid given, if found, print info; if not, print error
		for (it = address_book.begin(); it != address_book.end(); ++it)
		{
			if (it->getUid() == cmd) // uid found
			{
				it->show_all_info();
				found = true;
			}
		}
	
		if (found == false) // uid not found
		{
			cout << "ERROR: No user with UID: " << cmd << endl;
		}
	}
	
	else // no input after "print "
	{
		cout << "ERROR: Not enough command parameters." << endl;
	}
}


/*
============================================================================
 Function    : csv_load
 Parameters  : list<Contact>& address_book, string f_name, ifstream& f_in,
			int& IDcount
 Return      : none
 Description : This function opens a .csv file and reads and executes
	       commands from it.
============================================================================
*/

void csv_load(list<Contact>& address_book, ifstream& f_in, int& IDcount)
{
	// variable declaration
	string f_name, cmd;
	
	cout << ">FILENAME? " << endl;
	getline(cin, f_name);
		
	const char* c_f_name = f_name.c_str(); // convert f_name to a c-string
			
	// open the input file and error check
	f_in.open(c_f_name);
	if (f_in.fail())
	{
		cout << "ERROR: CANNOT OPEN INPUT FILE" << endl;
		return;
	}
		
	// loop through the entire file
	while (! f_in.eof())
	{
		getline(f_in, cmd); // read in one line at a time and call appropriate function
			
		if (cmd == "commands," || cmd == "COMMANDS,")
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
		
		else if (cmd.compare(0, 9, "add,name,") == 0 || cmd.compare(0, 9, "ADD,NAME,") == 0)
		{
			addName(address_book, cmd, IDcount);
			cout << endl;
		}
		
		else if (cmd.compare(0, 11, "add,spouse,") == 0 || cmd.compare(0, 11, "ADD,SPOUSE,") == 0)
		{
			addSpouse(address_book, cmd, IDcount);
			cout << endl;
		}

		else if (cmd.compare(0, 10, "add,child,") == 0 || cmd.compare(0, 10, "ADD,CHILD,") == 0)
		{
			add_child(address_book, cmd, IDcount);
			cout << endl;
		}
		
		else if (cmd.compare(0, 13, "add,address1,") == 0 || cmd.compare(0, 13, "ADD,ADDRESS1,") == 0)
		{
			addStreet(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 9, "add,city,") == 0 || cmd.compare(0, 9, "ADD,CITY,") == 0)
		{
			addCity(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 10, "add,state,") == 0 || cmd.compare(0, 10, "ADD,STATE,") == 0)
		{
			addState(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 8, "add,zip,") == 0 || cmd.compare(0, 8, "ADD,ZIP,") == 0)
		{
			addZip(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 15, "add,date_birth,") == 0 || cmd.compare(0, 15, "ADD,DATE_BIRTH,") == 0)
		{
			addBirthdate(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 17, "add,date_wedding,") == 0 || cmd.compare(0, 17, "ADD,DATE_WEDDING,") == 0)
		{
			addWeddingDate(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 15, "add,date_death,") == 0 || cmd.compare(0, 15, "ADD,DATE_DEATH,") == 0)
		{
			addDeathDate(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd.compare(0, 7, "search,") == 0 || cmd.compare(0, 7, "SEARCH,") == 0)
		{
			cmd.erase(cmd.size() - 2, 2);
			search(address_book, cmd);
			cout << endl;
		}
		
		else if (cmd == "print,all,," || cmd == "PRINT,ALL,,")
		{
			printAll(address_book);
			cout << endl;
		}
		
		else if (cmd.compare(0, 6, "print,") == 0 || cmd.compare(0, 6, "PRINT,") == 0)
		{
			cmd.erase(cmd.size() - 2, 2);
			print(address_book, cmd);
			cout << endl;
		}
		
		else
		{
			cout << "ERROR: Invalid input. Either you entered an unrecognized command or used an incorrect number of parameters." << endl;
			cout << endl;
		}
		
	}
}