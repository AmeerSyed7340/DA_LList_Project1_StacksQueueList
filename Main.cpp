
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class listNode {
public:
	int data;
	listNode* next;

	listNode(int Data) {
		data = Data;
		next = NULL;
	}
	
	void printNode(listNode* node, ofstream& outFile3) {
		
		while (node != NULL) {	
			outFile3 << "(";
			outFile3 << node->data << ", ";
			//outFile3 << node->next->data << " ";
			node = node->next;	
			if (node->next == NULL) {
				break;
			}
			outFile3 << node->data << ") -> ";
		}
		
	}
}; // listNode (node class)


class LLStack {
public:
	listNode* top;
	LLStack() {
		listNode* dummy = new listNode(-99999);
		dummy->next = NULL;
		top = dummy;
	}
	void push(listNode* newNode) {
		
		newNode->next = top->next;
		top->next = newNode;
	}
	bool isEmpty() {
		if (top->next == NULL) {
			return true;
		}
		return false;
	}
	listNode* pop(ofstream& outFile1) {
		if (!isEmpty()) {
			listNode* deleteNode = top;
			top = top->next;
			delete(deleteNode);
		}
		else
			outFile1 << "Stack is empty" << endl;
		return top;
	}
	void buildStack(ifstream& inFile) {
		int data;
		while (!inFile.eof()) {
			inFile >> data;
			listNode* newNode = new listNode(data);
			push(newNode);
		}
	}
}; //LLStack

class LLQueue {
public:
	listNode* head;
	listNode* tail;
	listNode* dummy;
	LLQueue() {
		dummy = new listNode(-99999);
		dummy->next = NULL;
		head = dummy;
		tail = dummy;
	}
	void insertQ(LLQueue* Q, listNode* newNode) {		
		newNode->next = Q->tail->next;
		Q->tail->next = newNode;
		Q->tail = newNode;
	}
	listNode* deleteQ(LLQueue* Q, ofstream& outFile2) {
		if (isEmpty(Q)) {
			outFile2 << "Q is empty";
			return NULL;
		}
		else {
			listNode* temp = Q->head->next;
			Q->head->next = temp->next;
			temp->next = NULL;
			return temp;
		}
	}
	bool isEmpty(LLQueue* Q) {
		if (Q->tail == Q->dummy) {
			return true;
		}
		return false;
	}
	void buildQueue(LLStack S, LLQueue* Q, ofstream& outFile1) {
		listNode* newNode;
		while (S.top->next != NULL) {
			newNode = S.pop(outFile1);			
			outFile1 << newNode->data << endl;
			listNode* temp = new listNode(newNode->data);			
			insertQ(Q, temp); 
			
		}
	}
};//LLQueue

class LList {
public:
	listNode* listHead;
	LList() {
		listNode* dummy = new listNode(-99999);
		dummy->next = NULL;
		listHead = dummy;
	}

	
	listNode* findSpot(listNode* listHead, listNode* newNode) {
		listNode* Spot = listHead;
		while (Spot->next != NULL && Spot->next->data < newNode->data) {
			  Spot = Spot->next;
		}
		return Spot;
	}
	void insertOneNode(listNode* spot, listNode* newNode) {
		newNode->next = spot->next;
		spot->next = newNode;
	}
	void buildList(LLQueue* Q, ofstream& outFile2) {
		listNode* newNode;
		while (Q->head->next != NULL) {
			newNode = Q->deleteQ(Q, outFile2);
			outFile2 << newNode->data << endl;			
			listNode* Spot = findSpot(listHead, newNode);
			insertOneNode(Spot, newNode);
		}
	}
	void printList(listNode* listHead, ofstream& outFile3 ) {
		outFile3 << "listHead -> ";
		listHead->printNode(listHead, outFile3);
	}
}; //LList



int main(int argc, char** argv) {
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	ofstream outFile3;

	if (argc != 5) {
		cout << "Need one inFile and three outfiles";

	}
	else {
		inFile.open(argv[1]);
		outFile1.open(argv[2]);
		outFile2.open(argv[3]);
		outFile3.open(argv[4]);
	}


	LLStack* S = new LLStack();
	S->buildStack(inFile);
	
	LLQueue* Q = new LLQueue();
	Q->buildQueue(*S, Q, outFile1);

	LList* LL = new LList();
	LL->buildList(Q, outFile2);
	LL->printList(LL->listHead, outFile3);

	inFile.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();

	return 0;
}