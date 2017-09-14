/*
=======================================================================================
 Name        : P3_header.h
 Author      : Cole Dapprich
 Version     : 2.0
 Copyright   : 2015
 Description : This header file includes the necessary directories and function proto-
	       types and creates a class used to create an address book.
 Citations   : Used a stack overflow forum post to learn how to concatenate a string
               and an int in order to make the 'IDxxx' identifiers
	       (http://stackoverflow.com/questions/191757/c-concatenate-string-and-int)
=======================================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
using namespace std;

// class declaration
class Contact
{
	private:
		// member declarations
		string firstname, lastname, name, name_sort, uid, address, city, state, zip, birthdate, wedding_date, death_date;
		list<Contact>::iterator spouse;
		list<Contact*> children;
	public:
		// member declaration
		// constructor
		Contact(string nm, string f_nm, string l_nm, int IDcount)
		{
			// stream declaration for concatenation
			stringstream s_strm;
			
			firstname = f_nm;
			lastname = l_nm;
			name = f_nm + " " + l_nm;
			name_sort = nm;
			address = "NONE_LISTED";
			city = "NONE_LISTED";
			state = "NONE_LISTED";
			zip = "NONE_LISTED";
			birthdate = "NONE_LISTED";
			wedding_date = "NONE_LISTED";
			death_date = "NONE_LISTED";
			
			if (IDcount < 10)
			{
				string ID = "ID00";
				s_strm << ID << IDcount;
				uid = s_strm.str(); 
			}
			else if (IDcount < 100)
			{
				string ID = "ID0";
				s_strm << ID << IDcount;
				uid = s_strm.str();
			}
			else
			{
				string ID = "ID";
				s_strm << ID << IDcount;
				uid = s_strm.str();
			}
		}
		
		// get functions
		string getFirstname() { return firstname; }
		string getLastname() { return lastname; }
		string getName() { return name; }
		string getNamesort() { return name_sort; }
		string getUid() { return uid; }
		
		// set functions
		void setSpouse(list<Contact>::iterator spse) { spouse = spse; }
		void addChild(Contact* pKid)
		{
			children.push_back(pKid);
		}
		void setAddress(string add) { address = add; }
		void setCity(string cty) { city = cty; }
		void setState(string st) { state = st; }
		void setZip(string zp) { zip = zp; }
		void setBirthdate(string bd) { birthdate = bd; }
		void setWeddingDate(string wd) { wedding_date = wd; }
		void setDeathDate(string dd) { death_date = dd; }
		
		// member functions
		void show_info()
		{
			cout << setw(13) << name;
			cout << " UID: " << uid << endl;
		}
		
		void show_all_info()
		{
			cout << "         UID: " << uid << endl
			     << "        NAME: " << name << endl
			     << "    ADDRESS1: " << address << endl
			     << "        CITY: " << city << endl
			     << "       STATE: " << state << endl
			     << "         ZIP: " << zip << endl
			     << "  DATE_BIRTH: " << birthdate << endl
			     << "  DATE_DEATH: " << death_date << endl
				 << "DATE_WEDDING: " << wedding_date << endl
				 << "      SPOUSE: " << spouse->name << endl;
				 
			if (children.empty() == true) // print out an error message if the list is empty
			{
				cout << "NO CHILDREN LISTED" << endl;
			}
	
			else // the list is not empty
			{
				int child_count = 1;
				
				// print out the contents of the list
				for (list<Contact*>::iterator it = children.begin(); it != children.end(); ++it) //   <--- INFINITE LOOP HAPPENS HERE
				{
					cout << "      CHILD" << child_count << ": " << (*it)->name << endl;
					child_count++;
				}
				
			}
			
		}
};

// function prototypes
void display_info();
void addName(list<Contact>& address_book, string cmd, int& IDcount);
void addSpouse(list<Contact>& address_book, string cmd, int& IDcount);
void add_child(list<Contact>& address_book, string cmd, int& IDcount);
void addStreet(list<Contact>& address_book, string cmd);
void addCity(list<Contact>& address_book, string cmd);
void addState(list<Contact>& address_book, string cmd);
void addZip(list<Contact>& address_book, string cmd);
void addBirthdate(list<Contact>& address_book, string cmd);
void addWeddingDate(list<Contact>& address_book, string cmd);
void addDeathDate(list<Contact>& address_book, string cmd);
void search(list<Contact> address_book, string cmd);
void printAll(list<Contact> address_book);
void print(list<Contact> address_book, string cmd);
void csv_load(list<Contact>& address_book, ifstream& f_in, int& IDcount);