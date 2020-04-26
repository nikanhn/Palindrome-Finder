#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h> //for punctuation
//struct for add in order function which uses string
struct nodes{
nodes* next;
std:: string data;
std:: string cleanData;
};
//struct for add at end and remove from start function which use characters
struct nodec
{
	nodec *next;
	char data;
};
	 
const  int MAXSIZE = 500;
bool isPalyndrome(char* str,int size);
int countPalyndrome(std:: string ); //count how many palyndromes
void push_stack(char [],int , char );//stack
char pop_stack(char [],int );//stack
void add_at_end(nodec*& h,nodec*& t, char d); //Queue
char remove_from_start(nodec*& h,nodec*& t);//Queue
void add_in_order(nodes*& h,nodes*& t, std::string d, std::string cleanD); //to sort alphabetically
int lineCleaner(std::string line, char*& cleanLine);
bool isAlphaNumeric(char c); // check to see if the character is number or alphabet
void traverse(nodes*& h); //for printing the function
void traverse_delete(nodes*& h);
void traverse_delete2(nodec*& h);
std:: string convertToString(char* a, int size); //change  array of characters to strings

int main()
{
	nodes* head = NULL;
	nodes* tail =NULL;
	std::string fileName;
	std::ifstream in_file;
	std::string textfile;
	std::string line;
	std::string sCleanLine;
	int size=0;
	char* cleanLine; //pointer to character
	int countPolyndromes=0;
	std::cout<<"Which text file do you want to use?"<<std::endl;
	std::cout << "Enter 1 for the first text file and 2 for the second text file: "<<std::endl; 
	std::cin>> textfile;
	if(textfile == "1")
	{
		fileName="PalindromeTest1.txt";
	}
	else if(textfile == "2")
	{
		fileName="PalindromeTest2.txt";
	}
	in_file.open(fileName);
	if(in_file.is_open())
	{
		

		while(std::getline(in_file,line))
		{
			std::cout<<"checking the line: "<<line <<std::endl;
			std::string temp = line; //assing line to temp
			size=lineCleaner(temp,cleanLine);
			sCleanLine=convertToString(cleanLine,size);
			if(size>MAXSIZE)
			{
			std::cout<<"this line has more than 500 characters."<<std::endl;
			continue; //opposite of break, continue the loop
			}		
			if(isPalyndrome(cleanLine,size))
			{
				add_in_order(head,tail,line,sCleanLine); //fill linked list
				//with punctuations
				countPolyndromes++;
				
			}
			
		}	
	}	
		
	else if(in_file.fail())
	{
		std::cout <<"Error opening file: "<<std::endl;
	}
	in_file.close();
	
	//print total number of palindromes
	std::cout<<"total numbers are: "<< countPolyndromes<< std::endl;
	traverse(head); //print
	
	traverse_delete(head);
	return 0;
}

/**
generates a charachter array of clean charachters 
inside the line and returns the size of this charachters.
@param - string, pointer which is passed by reference
@return - integer
*/
int lineCleaner(std::string line, char*& cleanLine) 
{ 
	std::string word = "";
	int i=0; 
	for (i=0; i < line.length(); i++) 
	{ 
   
	if (isAlphaNumeric(line[i]))  //pass line[i] to isAlphaNumeric function 
	//to check if it's alpha numeric or not
	{ 
		word=word+std::tolower(line[i],std::locale()); //converting the character to lower so it can be checked equally through all the line.
	}  
	}
	int size = word.length();
	cleanLine=new char[size+1]; // dynamic allocation to create an array of characters with the size of the line and then fit the line into it
	for(i=0;i<size;i++)
	{
		cleanLine[i]=word[i]; //copy character by character
	}
	return size; // size of the array minus one because the last character is null.
	
} 
/**
function to push to the stack
@param - array of character, pointer to integer, character
@return - none
*/
void push_stack(char myStack[],int* sp, char value) 
// we should have used sp as a pointer so if we used to pop or push again, the stack pointer know where to point correctly.
{ 
//sp=-1 ,newest element
	if(*sp > 500)
	{
		std:: cout << "Out of array"<<std::endl;
	}
	else
	{	
		*sp=*sp+1;
		myStack[*sp] = value;
	}
	return;
}
/**
function to pop from the stack
@param - array of character, pointer to integer,
@return - character
*/
char pop_stack(char* myStack,int* sp)
{ //sp=-1 ,newest element
	char value;
	if(*sp == -1)
	{
		std:: cout << "Out of array"<<std::endl;
	}
	else
	{
		value =myStack[*sp];
		*sp=*sp-1;
	}
	return value;	
}
/**
function to check if it's palindrome or not
@param - pointer to character, integer
@return - boolean expression
*/
bool isPalyndrome(char* str,int size)
{ //if it's palyndrom then call pop function
//dynamic allocation of size of the stack
	char* stack = new char[size];
	nodec* h=NULL;
	nodec* t=NULL;
	int sp=-1;
	for(int i =0; i < size; i++)
	{
		push_stack(stack,&sp,str[i]);
		add_at_end(h,t,str[i]);
	};
	char result_stack =pop_stack(stack, &sp) ; //initialize
	char result_queue = remove_from_start(h,t) ; //initialize
	while(result_stack == result_queue && sp!=-1)
//when the results from both stack and queue are equal then
//since first element of one of them is equal to last element of the other one
//that means words are palindrome
//when sp is -1 it means every letters is popped
{
		result_stack =pop_stack(stack, &sp) ;
		result_queue = remove_from_start(h,t) ;		
}
if(sp == -1)
{
	
	//delete [] stack; 
	//traverse_delete2(h);
	return true;  
}	
else
{
	//traverse_delete2(h);
	//delete [] stack; 
	
	return false;
}

	

}
/**
function to push to the queue
@param - pointers to nodec passed by reference, character
@return - none
*/
void add_at_end(nodec*& h,nodec*& t, char d)
{
nodec* new_node = new nodec;
new_node -> data = d;
if(h== NULL)
{
	h = new_node;
	t= new_node;
}
else
{
	t ->next = new_node;
	t = new_node;
}

}
/**
function to pop from the queue
@param - pointers to nodec passed by reference
@return - character
*/
char remove_from_start(nodec*& h,nodec*& t)
{
char d;
if(h==NULL) //list is empty
{
}
else if(h->next == NULL) //list has one element
{
	d= h->data;
	delete h;
	h = NULL;
	t = NULL;
}
else
{
	d= h->data; //assigning value of head next to char d 
	nodec * temp = h;
	h = h->next;
	delete temp;
}
return d;
}
/**
function for sort alphabetically
@param - pointers to nodes passed by reference, string
@return - none
*/
void add_in_order(nodes*& h,nodes*& t, std::string d,std::string cleanD)
{
	nodes * new_node = new nodes;
	new_node -> data = d;
	new_node ->cleanData=cleanD;
	nodes * temp = h;
	if(h==NULL)
	{	 
		h = new_node;
		t = NULL;
	
	}
	else if( strcmp(new_node -> cleanData.c_str() ,temp->cleanData.c_str())<0) //string comparison
	// if the result is less than 0 then it means left string is less than right string
	{
		new_node->next=h;
		h=new_node;
	}
	else
	{
		while(temp->next != t)
		{
			if(strcmp( new_node->cleanData.c_str(),temp->next->cleanData.c_str())<0) //string comparison
			{
				new_node->next = temp->next;
				temp->next=new_node;
				return;
			}
		temp = temp -> next;	
	}
	
		new_node->next = t;
		temp->next=new_node;
	}
}
				
/**
function to check if the character is alphabet or number
@param - character
@return - boolean expression
*/
bool isAlphaNumeric(char c)
{
if((c>='A' & c<='Z') || (c>='a' & c<='z') || (c>='0' & c<='9')) //not including punctuations
{
  return true;
}
else
{
  return false;
} 
}
/**
function for converting characters to strings
@param - pointer to character, integer
@return - string
*/

std:: string convertToString(char* a, int size) 
{ 
   
    std:: string s = ""; 
    for ( int i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

/**
function to traverse and print
@param - pointers to nodes passed by reference
@return - none
*/
void traverse(nodes*& h)
{
	nodes* ptr;
	int i=1;
	for(ptr = h; ptr != NULL; ptr = ptr->next)
	{
		std::cout << i <<". "<<ptr->data << std::endl;
		i++;
	}
}
/**
function to traverse and delete
@param - pointer to nodes passed by reference
@return - none
*/
void traverse_delete(nodes*& h)
{
	nodes* ptr = h;
	while ( ptr != NULL)
	{
		ptr= ptr -> next;
		delete h;
		h = ptr;
	}
}
/**
function to traverse and delete
@param - pointer to nodes passed by reference
@return - none
*/
void traverse_delete2(nodec*& h)
{
	nodec* ptr = h;
	while ( ptr != NULL)
	{
		ptr= ptr -> next;
		delete h;
		h = ptr;
	}
}









