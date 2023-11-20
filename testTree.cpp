#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include "node.h"
#include "testTree.h"

using namespace std;

std::set <string> idList;

string labelNames[] = {
	"PROGRAM", "VARS", "VARLIST", "EXP", "M", "N", "R", "STATS", 
	"MSTAT", "STAT", "BLOCK", "IN", "OUT", "IF", "LOOP", "ASSIGN", "RO"
};

node * createNode(nodeType l){     // initialize all possible tokens and children of node
	node * root = new node;
	root-> label = l;

	Scanner::Token token1;
	Scanner::Token token2;
	Scanner::Token token3;
	Scanner::Token token4;
	Scanner::Token token5;
	root -> tk1 = token1;
	root -> tk2 = token2;
	root -> tk3 = token3;
	root -> tk4 = token4;
	root -> tk5 = token5;

	root -> child1 = NULL;
	root -> child2 = NULL;
	root -> child3 = NULL;
	root -> child4 = NULL;
	return root;

}


void traversePreorder(node *n, int depth){    // Traverse tree preorder, print nodes
	if(n){
		printNode(n, depth); 	
		traversePreorder(n-> child1, depth+1); 	
		traversePreorder(n-> child2, depth+1);	
		traversePreorder(n-> child3, depth+1);  
		traversePreorder(n-> child4, depth+1);  
	}
}


void printNode(node *n, int depth){    // Print nodes, space them out
	string space = "";

	for(int i = 0; i< depth*2; i++)
		space= space + " ";
		
    cout << space << labelNames[n-> label] << ": "; 

	if(n-> tk1.lexeme != "")
		cout << n->tk1.lexeme << " ";
	
	if(n-> tk2.lexeme != "")
		cout << n->tk2.lexeme << " ";
	
	if(n-> tk3.lexeme != "")
   	    cout << n->tk3.lexeme << " ";
	
	if(n-> tk4.lexeme != "")
		cout << n->tk4.lexeme << " ";
	
	if(n-> tk5.lexeme != "")
		cout << n-> tk5.lexeme << " ";
	    
	cout << endl;
}

void staticSemantics(node *n, int depth, std::set<string> idList){
	if(n){
		idList = verifyAndInsert(n->tk1, idList, labelNames[n-> label]);
		idList = verifyAndInsert(n->tk2, idList, labelNames[n-> label]);
		idList = verifyAndInsert(n->tk3, idList, labelNames[n-> label]);
		idList = verifyAndInsert(n->tk4, idList, labelNames[n-> label]);
		idList = verifyAndInsert(n->tk5, idList, labelNames[n-> label]);
		
		staticSemantics(n-> child1, depth+1, idList); 	
		staticSemantics(n-> child2, depth+1, idList);	
		staticSemantics(n-> child3, depth+1, idList);  
		staticSemantics(n-> child4, depth+1, idList);  
	}
}

set<string> verifyAndInsert(Scanner::Token tk, std::set<string> idList, string label){
	if(tk.lexeme != "" && tk.type == "IDENTIFIER" && label == "VARLIST"){
		auto it = idList.find(tk.lexeme);
		if (it != idList.end()) {      	// Found in idList, throw detailed error msg       
        	std::cout << "SEMANTICAL ERROR: redefinition of " << tk.lexeme;
			std::cout << " on line " << tk.line << "\n";
		} else {                       	// Not found in idList, add to idList		
			idList.insert(tk.lexeme);
		}
	}
		
	return idList;
}
