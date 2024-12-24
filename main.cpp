#include <iostream>
#include <vector>
// #include <conio.h>
#include <fstream>
#include <sstream> // Add this line
#include <string>
#include "operations.h"
using namespace std;
class node;
class td;
bool checknamevalid(string name);
bool checknumvalid(string num);
void updatenode(td &t, int key);
void invalid(string s);
string capitalize(string s);
void insertcontact(td &t);
void search(td &t);
void loadDataFromFile(td &t, const string &fileName) ;
void saveDataToFile(td &t, const string &fileName);
int keycount = 0;
class Group;

class node
{ // this is each contact
public:
    int key;
    string fname;       // first fname
    string lname;       // last fname
    vector<string> num; // contact number
    node *prev;
    node *next;

    node()
    {
    	cout<<"const calledd"<<endl;
        assignkey();
        fname = " ";
        lname = " ";
        num.push_back(" ");
        next = NULL;
        prev = NULL;
    }

    node(string fname, string lname, string num)
    {
    	cout<<"para const calledd"<<endl;
        assignkey();
        this->fname = capitalize(fname);
        this->lname = capitalize(lname);
        this->num.push_back(num);
        next = NULL;
        prev = NULL;
    }
    
    node (node *n)
    {
    	next = NULL;
    	prev = NULL;
    	fname = n->fname;
    	lname = n->lname;
    	num[0] = n->num[0];
    	key = n->key;
	}

    void assignkey()
    {
        key = keycount++;
    }

    void insertnum(string num) // inserting another phone number
    {
        this->num.push_back(num);
    }
    
    void setfname(string s)
    {
    	fname = capitalize(s);
	}
	
	void setlname(string s)
	{
		lname = capitalize(s);
	} 
	
	void setnum(string s)
	{
		num.clear();
		num[0] = s;
	}
};

class Group {
public:
	string name;
    vector<int> contactKeys;
};

class td
{ // td means telephone directory
public:
    node *head;
    node* letterHead[26]; // Array to store addresses for names starting with each letter
	vector<Group> groups;
 
	   td()
	   {
	   
        head = NULL;
        for (int i = 0; i < 26; ++i) 
		{
            letterHead[i] = NULL;
        }
    	}

    td(node *n)
    {
        head = n;
        for (int i = 0; i < 26; ++i) {
            letterHead[i] = NULL;
        }
    }
    
  	void insertSorted(node* new_node) 
	{
	    if (new_node == NULL) 
	    {
	        return;
	    }

   		// Special case: if the list is empty or the new fname comes before the head node alphabetically
		if (head == NULL || new_node->fname < head->fname) 
		{
		    new_node->next = head;
		    if (head) 
		    {
		        head->prev = new_node;
		    }
		    head = new_node;
		}
		else 
		{
		    node* current = head;
		    // Traverse the list to find the correct insertion point
		    while (current->next && current->next->fname <= new_node->fname) 
		    {
		        current = current->next;
		    }
		    new_node->next = current->next;
		    if (current->next) 
		    {
		        current->next->prev = new_node;
		    }
		    current->next = new_node;
		    new_node->prev = current;
		}
		
		// Update the letterHead array
		char firstLetter = new_node->fname[0];
		int index = firstLetter - 'A'; // Calculate the index (0-25) for the first letter
		if (index >= 0 && index < 26) 
		{
		    if (letterHead[index] == NULL || new_node->fname < letterHead[index]->fname) 
		    {
		        letterHead[index] = new_node;
		    }
		}
	}

    void insert(string fname, string lname, string num) //insert with node attributes
	{
        insertSorted( new node(fname, lname, num));
    }

    node *nodeExists(int key)
    {
        node *temp = NULL;
        node *ptr = head;

        while (ptr != NULL)
        {
            if (ptr->key == key)
            {
                temp = ptr;
                break;
            }
            ptr = ptr->next;
        }
        return temp;
    }

    void deletenode(int key)
    {
        node *temp = nodeExists(key);

        if (temp == NULL) // if head is already null
        {
            cout << "Node Does Not Exist" << endl;
            return;
        }
        
        if(temp->next == NULL)
        {
        	letterHead[temp->fname[0]-'A'] = NULL;
		}
		else
		{
			if(temp->fname[0] == temp->next->fname[0])
			{
				letterHead[temp->fname[0]-'A'] = temp->next;
			}
			else
			{
				letterHead[temp->fname[0]-'A'] = NULL;
			}
		}

        if (temp == head) // deleting the head
        {
            head = temp->next;
            if (head != NULL) // if the head has a node attatched to next
            {
                head->prev = NULL;
            }   
        }
        else
        {
            temp->prev->next = temp->next; // deleting at the tail
            if (temp->next != NULL)        // if its not the tail
            {
                temp->next->prev = temp->prev;
            }
        }
        delete temp;
        cout<<"Contact with Key "<<key<<" deleted Successfully"<<endl;
    }
   
    void searchbyname(string name) 
	{
	    name = capitalize(name);
	    bool found = false;
	    node *temp = head;
	    while (temp != NULL ) 
		{
	        if (searchsubstring(temp->fname,name)  || searchsubstring(temp->lname,name)) 
			{
	            cout << "CONTACT FOUND WITH NAME " << name << endl;
	            cout << "First name: " << temp->fname << endl;
	            cout << "Last name: " << temp->lname << endl;
	            cout << "Numbers: ";
	            for (int i = 0; i < temp->num.size(); i++) {
	                cout << temp->num[i] << " ";
	            }
	            cout << endl << endl;
	            found = true;
	        }
	        temp = temp->next;
	    }
	    if (!found) {
	        cout << "Contact not found" << endl;
	    }
	}

    
    void searchbynumber(string number) 
	{
	    bool found = false;
	    node *temp = head;
	
	    while (temp != NULL) {
	        for (int i = 0; i < temp->num.size(); i++) {
	            if (number == temp->num[i]) {
	                cout << "CONTACT FOUND" << endl;
	                cout << "First name: " << temp->fname << endl;
	                cout << "Last name: " << temp->lname << endl;
	                cout << "Number: " << temp->num[i] << endl;
	                found = true;
	                break;
	            }
	        }
	        temp = temp->next;
	    }
	
	    if (!found) {
	        cout << "Contact not found" << endl;
	    }
	}
	
	void viewContactsByLetter(char letter) 
	{
	    letter = toupper(letter);
	    int index = letter - 'A';
	    
	    if (index >= 0 && index < 26 && letterHead[index] != NULL) 
		{
	        node* current = letterHead[index];
	        cout << "Contacts starting with letter '" << letter << "':" << endl;
	        
	        while (current != NULL && current->fname[0] == letter) 
			{
	            cout << "First Name: " << current->fname << endl;
	            cout << "Last Name: " << current->lname << endl;
	            cout << "Numbers: ";
	            for (int i = 0; i < current->num.size(); i++) 
				{
	                cout << current->num[i] << " ";
	            }
	            cout << endl << endl;
	            
	            current = current->next;
	        }
	    } 
		else 
		{
	        cout << "No contacts found starting with letter '" << letter << "'" << endl;
		}
	}



	void update(int key)
	{
		updatenode(*this, key);
		return;
	}
	
    void printlist() {
    node *temp = head;
    while (temp != NULL) {
        cout << temp->key << " " << temp->fname << " " << temp->lname << " ";
        for (int i = 0; i < temp->num.size(); i++) {
            cout << temp->num[i] << " ";
        }
        cout << endl;
        temp = temp->next;
    }
}


    //mergesort starts here
    void mergesort(node **head1, int check1){ 
        node *curr = *head1; //current pointer is pointing at head
        node *first = NULL;
        node *second = NULL;
        if(curr == NULL || curr->next == NULL)  //base case for this mergesort fuction. i.e. if curr becomes null
        return;
        findmiddlelist(curr,&first,&second);
        mergesort(&first,check1); //calling recursively
        mergesort(&second,check1); //calling recursively when curr or curr->next becomes null

         //finding middle part of linklist

        *head1 = merginglists(first,second,check1); //dividing lists into sub-lists
    }

    node *merginglists(node *first, node *second,int check1){ //this function will merge two different link lists
        node *answer = NULL;
        if(first == NULL) //if first linklist ends, data of second linklist will be stored in new list.
        return second;
        else if(second == NULL) //if second linklist ends, data of first linklist will be stored in new list.
        return first;

        if(check1==1){//sort by first name
            if(first->fname <= second->fname){
                answer = first;
                answer->next = merginglists(first->next,second,check1);
            }
            else{
                answer = second;
                answer->next = merginglists(first,second->next,check1);
            }
        }
        else if(check1 == 2){//sort by number
            if(first->num <= second->num){
                answer = first;
                answer->next = merginglists(first->next,second,check1);
            }
            else{
                answer = second;
                answer->next = merginglists(first,second->next,check1);
            }
        }
        else if(check1 == 3){//sort by key
            if(first->key <= second->key){
                answer = first;
                answer->next = merginglists(first->next,second,check1);
            }
            else{
                answer = second;
                answer->next = merginglists(first,second->next,check1);
            }
        }
        return answer;
    }
    void findmiddlelist(node *curr, node** first, node** second)
	{
        node *fast = NULL;
        node *slow = NULL;
        slow = curr;
        fast = curr->next;
        
        while(fast!=NULL){
            fast = fast->next;
            if(fast!=NULL){
                slow = slow->next;
                fast = fast->next;
            }
        }

        *first = curr;
        *second = slow->next;
        slow->next = NULL;
    }


    td tosort(td t1,int check1){ //base function for sorting using mergesort
        t1.mergesort(&t1.head,check1);
        return t1;
    }
    
	void display() 
	{
        node* current = head;
        while (current) {
            cout << current->fname << " ";
            current = current->next;
        }
        cout << endl;
    }
     
    node* findContact(string fname, string lname) 
	{
	    fname = capitalize(fname);
	    lname = capitalize(lname);
	    node *temp = head;
	    while (temp != NULL) {
	        if (temp->fname == fname && temp->lname == lname) {
	            return temp;
	        }
	        temp = temp->next;
	    }
	    return NULL;
	}


	void createGroup() 
	{
	    cout << "Creating a new contact group." << endl;
	    printlist(); // Display all contacts
	
	    int num, key;
	    cout << "Enter the number of contacts in the group: ";
	    cin >> num;
	
	    Group newGroup;
	    cout << "Enter the keys of the contacts to add to the group:" << endl;
	    for (int i = 0; i < num; i++) {
	        cin >> key;
	        newGroup.contactKeys.push_back(key);
	    }
	
	    cout << "Enter a name for this group: ";
	    cin >> newGroup.name;
	
	    groups.push_back(newGroup); // Add the new group to the vector
	    cout << "Group created successfully." << endl;
	}
	
	void displayGroups() {
	    if (groups.empty()) {
	        cout << "No groups available." << endl;
	        return;
	    }
	
	    for (const auto& group : groups) {
	        cout << "Group Name: " << group.name << endl;
	        cout << "Contacts in the group:" << endl;
	        for (int key : group.contactKeys) {
	            node* contact = nodeExists(key);
	            if (contact) {
	                // Display the contact details
	                cout << "Key: " << contact->key << ", Name: " << contact->fname << " " << contact->lname << endl;
	            } else {
	                cout << "Contact with key " << key << " not found." << endl;
	            }
	        }
	        cout << endl;
	    }
	}



};
  

int main()
{
    td t;
    loadDataFromFile(t, "contacts.txt");
   
    
	t.display();
	t.printlist();
	
    system("pause");

    char choice;

menu:
    system("cls");
    cout << "What action do you want to perform? " << endl;

    cout << "A. Add a New Contact" << endl;
    cout << "B. Remove a Contact" << endl;
    cout << "C. Update the contact" << endl;
    cout << "D. View contacts" << endl;
    cout << "E. Search a contact" << endl;
    cout << "F. Sort Numbers" << endl;
    cout << "H. Group Contacts" << endl;
    cout << "G. Exit" << endl;
     
    cin >> choice;

    switch (choice)
    {
	    case 'a':
	    case 'A':
	    {
	        system("cls");
	     	insertcontact(t);
            saveDataToFile(t, "contacts.txt");
	        goto menu;
	    }
	
	    case 'b':
	    case 'B':
	    {
	        system("cls");
	        t.printlist();
	        int key;
	        cout << endl
	             << "Enter the key to be deleted:";
	        cin >> key;
	        t.deletenode(key);
	        saveDataToFile(t, "contacts.txt");
	        system("pause");
	        goto menu;
	    }
	    case 'c':
	    case 'C':
	    {
	        system("cls");
	        t.printlist();
	        int ch;
	        int key;
	        cout << "Enter key of which you want to update:";
	        cin >> key;
	        updatenode(t,key);
            saveDataToFile(t, "contacts.txt");
	        system("pause");
	        goto menu;
	    }
	    case 'd':
        case 'D':
        {
        	char subchoice;
            system("cls");
            cout << "View Contacts" << endl;
            cout << "1. View all contacts" << endl;
            cout << "2. View Contacts Starting With Letter" << endl;
            cout << "3. View Group of Contacts" << endl;            
            cin >> subchoice;                                   

            switch (subchoice)
            {
                case '1':
                    t.printlist();
                    break;
                case '2':
                {
                    char letter;
                    cout << "Enter the starting letter: ";
                    cin >> letter;
                    t.viewContactsByLetter(letter);
                    break;
                }
            		case '3': // New sub-option to view groups
                {                                         
                	t.displayGroups();
				    break;  
				}				
				default:
				{
					cout << "Invalid choice." << endl;
				}
     			
            }
            system("pause");
            goto menu;
        }
	    case 'e':
	    case 'E':
	    {
	    	search(t);
	   		goto menu;
	    }
        case 'f': //Exit Case
	    case 'F':
	    {
            cout<<"Sorting by Number"<<endl;
            cout<<"Sort by: \nPress:\n\t1.By Name\n\t2.By Phone Numbers\n\t3.By Keys"<<endl;
            int check1;
            cin>>check1;
            t = t.tosort(t,check1);
            if(check1 == 1){
                cout<<"Numbers Sorted in Ascending Order by First name"<<endl;
            }
            else if(check1 == 2){
                cout<<"Numbers Sorted in Ascending Order by Phone Number"<<endl;
            }
            else if(check1 == 3){
                cout<<"Numbers Sorted in Ascending Order by Key Values"<<endl;
            }
            
            system("pause");
            goto menu;
            
	    }
        case 'g':
        case 'G':
        {
            saveDataToFile(t, "contacts.txt");
            break;
        }
        case 'h': // New case for grouping contacts
		case 'H':
		{			
		    t.createGroup();
		    system("pause");
		    goto menu;
		}
		default: //to handle exceptions.
        {
            cout<<"Invalid Input"<<endl;
            cout<<"Press: \n1. Return to main menu\n2. Exit"<<endl;
            int inp;
            cin>>inp;
            if(inp == 1){
                goto menu;
            }
            else if(inp == 2){
                system("cls");
                break;
            }
        }
	
    }
}



void updatenode(td &t, int key)
{
upmenu:
    int ch;
    cout << "What do you want to update:" << endl;
    cout << "1.First name " << endl;
    cout << "2.Last name" << endl;
    cout << "3.Number" << endl;
    cout << "4.Previous menu" << endl;
    cin >> ch;
    cin.ignore();
    string fname, lname, num;
    node *temp = t.nodeExists(key);

    if (temp == NULL) // Check if the node exists
    {
        cout << "Node Does Not Exist" << endl;
        return;
    }

    // Creating a new node and copying contents
    node *newnode = new node(*temp);

    switch (ch)
    {
        case 1:
        {
            cout << "Enter the new First Name (limit 15):";
            cin >> fname;
            if (!checknamevalid(fname))
            {
                invalid("Name");
                system("pause");
                delete newnode; // Cleanup
                goto upmenu;
            }
            newnode->setfname(fname); // Update first name
            break;
        }
        case 2:
        {
            cout << "Enter the new Last Name (limit 15): ";
            cin >> lname;
            if (!checknamevalid(lname))
            {
                invalid("Name");
                system("pause");
                delete newnode; // Cleanup
                goto upmenu;
            }
            newnode->setlname(lname); // Update last name
            break;
        }
        case 3:
        {
            cout << "Enter the new contact Number (limit 15):";
            cin >> num;
            if (!checknumvalid(num))
            {
                invalid("Number");
                system("pause");
                delete newnode; // Cleanup
                goto upmenu;
            }
            newnode->num.clear();
            newnode->num.push_back(num); // Update number
            break;
        }
        case 4:
        {
            delete newnode; // Cleanup
            return;
        }
        default:
        {
            invalid("CHOICE");
            system("pause");
            delete newnode; // Cleanup
            goto upmenu;
        }
    }

    t.deletenode(key); // Delete the old node
    t.insertSorted(newnode); // Insert the updated node into the list
}


void insertcontact(td &t) 
{
    cout << "Enter the new contact First Name (limit 15): ";
    string fname;
    cin >> fname;
    if (!checknamevalid(fname)) {
        invalid("Name");
        system("pause");
        return;
    }

    cout << "Enter the new contact Last Name (limit 15): ";
    string lname;
    cin >> lname;
    if (!checknamevalid(lname)) {
        invalid("Name");
        system("pause");
        return;
    }

    cout << "Enter the new contact Number (limit 15): ";
    string num;
    cin >> num;
    if (!checknumvalid(num)) {
        invalid("Number");
        system("pause");
        return;
    }

    node *existingContact = t.findContact(fname, lname);
    if (existingContact != NULL) {
        // Check if the number already exists for this contact
        for (int i = 0; i < existingContact->num.size(); i++) {
            if (existingContact->num[i] == num) {
                cout << "This number already exists for the contact." << endl;
                system("pause");
                return;
            }
        }
        existingContact->insertnum(num);
        cout << "Number added to existing contact." << endl;
    } else {
        t.insert(fname, lname, num);
        cout << "New contact inserted." << endl;
    }

    system("pause");
}



void search(td &t)
{
     int ch;
        cout << "How do you want to search?" << endl;
        cout << " 1. By name " << endl;
        cout << " 2. By number" << endl;
        cin >> ch;
        
        switch(ch)
        {
	        case 1:
	        {
	            string name;
	            cout << "Enter name for you want to search:";
	            cin >> name;
	            name = capitalize(name);
	            t.searchbyname(name);
	            system("pause");
	            return;
	        }
			case 2:
	        {	
	            string n;
	            cout << "Enter number for you want to search:";
	            cin >> n;
	            t.searchbynumber(n);
	            system("pause");
	            return;
	        }	
	        default:
	        {  	 
	        	invalid("CHOICE");
	        	system("pause");
	        	return;
			}
		}
    return;
}


// Function to save contacts and groups data to a file
void saveDataToFile(td &t, const string &fileName) {
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        cout << "Failed to open file for writing." << endl;
        return;
    }

    // Save contacts data
    node *temp = t.head;
    while (temp != NULL) {
        outFile << temp->key << " " << temp->fname << " " << temp->lname << " ";
        for (int i = 0; i < temp->num.size(); i++) {
            outFile << temp->num[i] << " ";
        }
        outFile << endl;
        temp = temp->next;
    }

    // Save groups data
    for (const auto &group : t.groups) {
        outFile << "Group " << group.name << endl;
        for (int key : group.contactKeys) {
            outFile << key << " ";
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Data saved to " << fileName << " successfully." << endl;
}

// Function to load contacts and groups data from a file
void loadDataFromFile(td &t, const string &fileName) {
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cout << "Failed to open file for reading." << endl;
        return;
    }

    // Clear existing data
    t.head = NULL;
    t.groups.clear();

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        ss >> token;
        if (token == "Group") {
            string groupName;
            ss >> groupName;
            Group newGroup;
            while (ss >> token) {
                int key = stoi(token);
                newGroup.contactKeys.push_back(key);
            }
            newGroup.name = groupName;
            t.groups.push_back(newGroup);
        } else {
            int key = stoi(token);
            string fname, lname, num;
            ss >> fname >> lname;
            node *newNode = new node(fname, lname, "");
            newNode->key = key;

            while (ss >> num) {
                newNode->num.push_back(num);
            }
            t.insertSorted(newNode);
        }
    }

    inFile.close();
    cout << "Data loaded from " << fileName << " successfully." << endl;
}
