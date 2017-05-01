#include <string>
#include <iostream>
using namespace std;
//The InnerList
struct InnerList {
	int innerID;
	struct InnerList *Inext;
};

struct OuterList {
	int outerID;
	InnerList *Ifirst;
	struct OuterList *Onext;
};

/*
-A function that has 2 arguments: a)one interger to set as the ID of the new OuterList we create and b)the first pointer of the OuterList
-It creates a temporary (temp) pointer to navigate in the list and initalizes it with the addres of the first node (*first).
-An if else statment is then needed to check if the list is empty to not only add the new node but also initialize the pointer that
will point at the first node of our list and return it back to our main function, if the lists isn't empty we search for the last node 
and then create a new node and link it with the previous one.
*/

OuterList *Add_OuterList(int ID, OuterList *first) {
	OuterList *temp;
	temp = first;
	if (first != NULL) {
		while (temp->Onext != NULL) {
			temp = temp->Onext;
		}
		temp->Onext = new OuterList;
		temp = temp->Onext;
		temp->Onext = NULL;
		temp->Ifirst = NULL;
		temp->outerID = ID;
	}
	else {
		temp = new OuterList;
		temp->Onext = NULL;
		temp->Ifirst = NULL;
		temp->outerID = ID;
		first = temp;
	}
	return first;
}

/*
-A function that has 1 argument: a)the address of the first node of the list.  
-It scans all the nodes of a list and prints them
(it will include the InnerList later on)
*/

void Print_OuterList(OuterList *first) {
	OuterList *Otemp;
	Otemp = first;
	while (Otemp != NULL) {
		cout << Otemp->outerID << " ";
		Otemp = Otemp->Onext;
	}
	cout << endl;
}

/*
-A function that  has 3 arguments: a)the address we want to assign to the new node in the InnerList
b)the address of the OuterList we want to procceess
c)the first pointer of the OuterList
-It scan the OuterList to find the node we want to proccess and then scans its InnerList 
until the last node to add a new one
*/
void Add_InnerList(int innerID, int outerID , OuterList *Ofirst) {
	OuterList *Otemp;
	InnerList *Itemp;
	Otemp = Ofirst;
	while (Otemp != NULL && Otemp->outerID != outerID) {
		Otemp = Otemp->Onext;
	}
	Itemp = Otemp->Ifirst;
	if (Otemp != NULL && Otemp->Ifirst != NULL) {
		while (Itemp->Inext != NULL) {
			Itemp = Itemp->Inext;
		}
		Itemp->Inext = new InnerList;
		Itemp = Itemp->Inext;
		Itemp->innerID = innerID;
		Itemp->Inext = NULL;
	}
	else {
		Itemp = new InnerList;
		Itemp->Inext = NULL;
		Itemp->innerID = innerID;
		Otemp->Ifirst = Itemp;
	}
}

/*
-A function with 2 arguments: a)the ID of the node we want to do the extraction from
b) the first pointer of the OuterList
-It scans to find the node we want to do the extraction from
-Extracts the first element of the InnerList and save as first pointer the pointer of the previously second element
*/

void Delete_FirstElement(int outerID, OuterList *Ofirst) {
	OuterList *Otemp;
	InnerList *Itemp;
	Otemp = Ofirst;
	while (Otemp != NULL && Otemp->outerID != outerID) {
		Otemp = Otemp->Onext;
	}
	if (Otemp!=NULL && Otemp->Ifirst != NULL) {
		Itemp = Otemp->Ifirst;
		Itemp = Itemp->Inext;
		delete Otemp->Ifirst;
		Otemp->Ifirst = Itemp;
	}
	else
		cout << "Nothing to delete" << endl;
}

/*
-A function that has 2 arguments: a)the ID of the node that contains our desired InnerList to be printed
b)the first pointer of the OuterList
-It scans to find the node that contains our desired InnerList to be printed
-Print all the nodes of the InnerList
*/

void Print_InnerList(int outerID, OuterList *Ofirst) {
	OuterList *Otemp;
	InnerList *Itemp;
	Otemp = Ofirst;
	while (Otemp != NULL && Otemp->outerID != outerID) {
		Otemp = Otemp->Onext;
	}
	if (Otemp != NULL) {
		Itemp = Otemp->Ifirst;
		while (Itemp != NULL) {
			cout << Itemp->innerID << " ";
			Itemp = Itemp->Inext;
		}
		cout << endl;
	}
}

/*

*/

int main()
{
	int Inner_choice = 0,Outer_choice = 0, counter_of_outer_nodes = 0;
	OuterList *first;
	first = NULL;
	while (true) {
		cout << "Give an ID to create a new node for the OuterList(ID > 0)[ID <= 0 breaks the loop and prints the OuterList you created]" << endl;
		cin >> Outer_choice;
		if (Outer_choice > 0) {
			first = Add_OuterList(Outer_choice, first);
			counter_of_outer_nodes++;
		}
		else {
			Print_OuterList(first);
			break;
		}
	}
	while (true) {
		cout << "Give the ID of the node you want to add elements at its InnerList(ID > 0)[ID <= 0 breaks the loop and prints the OuterList you created]" << endl;
		cin >> Outer_choice;
		if (Outer_choice > 0) {
			cout << "Give an ID to create a new node for the InnerList(ID > 0)[ID <= 0 breaks the loop and prints the OuterList you created]" << endl;
			cin >> Inner_choice;
			if (Inner_choice > 0)
				Add_InnerList(Inner_choice, Outer_choice, first);
			else
				break;
		}
		else {
			Print_InnerList(Outer_choice, first);
			break;
		}
	}
	while(true) {
		cout << "Give the ID of the node you want to delete its InnerList's first element(ID>0)[ID <=0 break the loop]" << endl;
		cin >> Outer_choice;
		if (Outer_choice > 0) {
			Delete_FirstElement(Outer_choice, first);
			Print_InnerList(Outer_choice, first);
		}
		else
			break;
	}
	system("pause");
    return 0;
}

