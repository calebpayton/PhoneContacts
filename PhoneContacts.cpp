/*
 *	Author: Caleb Payton
 *
 *	Phonebook
 *
 *	A set of two classes that maintains phone contacts.
 *	phoneContact takes three string parameters (first name, last name, and phone number),
 *	with methods to get/set each of them.
 *	contactCollection stores the contacts into a singly linked list with methods to add,
 *	remove, and view contacts. The sortAlphabetically method uses a selection sort algorithm
 *	and makes a call to the private function swap.
 *	The main function for this program has a simple but clean look, giving the user options
 *	to add, view, delete, and sort their contacts. An entry of 0 will exit the program.
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

class phoneContact
{
	public:
		phoneContact()
		{
			setFirstName("");
			setLastName("");
			setPhoneNum("");
		}
		phoneContact(string firstName, string lastName, string phoneNum)
		{
			setFirstName(firstName);
			setLastName(lastName);
			setPhoneNum(phoneNum);
		}
		string getFirstName()
		{
			return _firstName;
		}
		void setFirstName(string firstName)
		{
			_firstName = firstName;
		}
		string getLastName()
		{
			return _lastName;
		}
		void setLastName(string lastName)
		{
			_lastName = lastName;
		}
		string getPhoneNum()
		{
			return _phoneNum;
		}
		void setPhoneNum(string phoneNum)
		{
			_phoneNum = phoneNum;
		}
		void printContact()
		{
			cout << getFirstName() << " " << getLastName() << ": " << getPhoneNum() << endl;
		}
	private:
		string _firstName;
		string _lastName;
		string _phoneNum;
};

class contactCollection
{
	private:
		struct contactNode
		{
			phoneContact contactInfo;
			contactNode * next;
		};
	public:
		contactCollection()
		{
			listHead = NULL;
		}
		~contactCollection()
		{
			deleteContacts(listHead);
		}
		contactCollection(const contactCollection &original)
		{
			listHead = copiedList(original.listHead);
		}
		contactCollection& operator=(const contactCollection &rhs)
		{
			if (this != &rhs)
			{
				deleteContacts(listHead);
				listHead = copiedList(rhs.listHead);
			}
			return *this;
		}
		void addContact(phoneContact newContact)
		{
			contactNode * newNode = new contactNode;
			newNode->contactInfo = newContact;
			newNode->next = listHead;
			listHead = newNode;			
		}
		void removeContact(string contactNum)
		{
			contactNode * loopPtr = listHead;
			contactNode * trailing = NULL;
			while ((loopPtr != NULL) && (loopPtr->contactInfo.getPhoneNum() != contactNum))
			{
				trailing = loopPtr;
				loopPtr = loopPtr->next;
			}
			if (loopPtr == NULL)
			{
				return;
			}
			if (trailing == NULL)
			{
				listHead = listHead->next;
			}
			else
			{
				trailing->next = loopPtr->next;
			}
			delete loopPtr;
		}		
		void sortAlphabetically()
		{
			contactNode * start = listHead;
			contactNode * traverse;
			contactNode * min;
			while (start->next != NULL)
			{
				min = start;
				traverse = start->next;
				while (traverse != NULL)
				{
					if (strcmp(min->contactInfo.getFirstName().c_str(), traverse->contactInfo.getFirstName().c_str()) > 0)
					{
						min = traverse;
					}
					traverse = traverse->next;
				}
				swap(start, min);
				start = start->next;				
			}
		}
		void printContactCollection()
		{
			contactNode * loopPtr = listHead;
			cout << "Contacts:" << endl;
			if (loopPtr == NULL)
			{
				cout << "You have no contacts at this time." << endl;
			}
			while (loopPtr != NULL)
			{
				cout << loopPtr->contactInfo.getFirstName() << " " << loopPtr->contactInfo.getLastName()
					<< ": " << loopPtr->contactInfo.getPhoneNum() << endl;
				loopPtr = loopPtr->next; 
			}
		}
				
	private:
		typedef contactNode * contactList;
		contactList listHead;
		void deleteContacts(contactList& listPtr)
		{
			while (listPtr != NULL)
			{
				contactNode * temp = listPtr;
				listPtr = listPtr->next;
				delete temp;
			}
		}
		void swap(contactList& listPtr1, contactList& listPtr2)
		{
			phoneContact temp = listPtr1->contactInfo;
			listPtr1->contactInfo = listPtr2->contactInfo;
			listPtr2->contactInfo = temp;
		}
		contactList copiedList(const contactList original)
		{
			if (original == NULL)
			{
				return NULL;
			}
			contactList newList = new contactNode;
			newList->contactInfo = original->contactInfo;
			contactNode * oldLoopPtr = original->next;
			contactNode * newLoopPtr = newList;
			while (oldLoopPtr != NULL)
			{
				newLoopPtr->next = new contactNode;
				newLoopPtr = newLoopPtr->next;
				newLoopPtr->contactInfo = oldLoopPtr->contactInfo;
				oldLoopPtr = oldLoopPtr->next;
			}
			newLoopPtr->next = NULL;
			return newList;
		}
};

int main()
{	
	contactCollection contacts;
	int userOption = 0;
	string first, last, number;	
	cout << "\t\tPhonebook\n\t\t---------\n\n";
	cout << "\t(1)\tAdd Contact\n\t(2)\tView Contacts\n\t(3)\tDelete Contact\n\t(4)\tSort Contacts\n\n";
	do
	{
		cout << "\tWhat would you like to do? (0 to exit): ";
		cin >> userOption;
		if (userOption == 1)
		{
			cout << "Enter first name: ";
			cin >> first;
			cout << "Enter last name: ";
			cin >> last;
			cout << "Enter phone number: ";
			cin >> number;
			phoneContact newEntry(first, last, number);
			contacts.addContact(newEntry);
			cout << endl;
		}
		if (userOption == 2)
		{
			contacts.printContactCollection();
			cout << endl;
		}
		if (userOption == 3)
		{
			cout << "Enter phone number to delete: ";
			cin >> number;
			contacts.removeContact(number);
			cout << endl;
		}
		if (userOption == 4)
		{
			contacts.sortAlphabetically();
			contacts.printContactCollection();
			cout << endl;
		}
	}	while (userOption != 0);
}
