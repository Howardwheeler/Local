#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string& expression) : infixExpression(expression), root(nullptr) {}
//constructs a tree using the expression given

void arithmeticExpression::buildTree() {    //builds the tree using the expression that is converted from infix to postfix
    string postFix = infix_to_postfix();
    stack<TreeNode*> node;

    int key = 'a';
    for(unsigned i = 0; i < postFix.size(); i++){  //iterates through postfix expression
        char character = postFix[i];
        TreeNode* newNode = new TreeNode(character, key++);
        if(isalnum(character)){ //makes new node of the operand and pushes onto the stack
            node.push(newNode);
        } else{ //otherwise, pops the 2 operands from the stack and set them as children nodes and make their parent an operator
            newNode->right = node.top();
            node.pop();
            newNode->left = node.top();
            node.pop();
            node.push(newNode);
        }
    }
    root = node.top(); //then set root to the top element of the stack
}

void arithmeticExpression::infix() { //recursive calls for infix, prefix, and postfix
  infix(root);
}

void arithmeticExpression::prefix() {
  prefix(root);
}

void arithmeticExpression::postfix() {
  postfix(root);
}

void arithmeticExpression::infix(TreeNode* root){ //prints the infix expression by recursively iterating through the tree
    if(root == nullptr){
        return;
    }
    if (root->left || root->right){
        cout << "(";
    }
    infix(root->left);
    cout << root->data;
    infix(root->right);
    if (root->left || root->right){
        cout << ")";
    }
}

void arithmeticExpression::prefix(TreeNode* root){ //prints the prefix expression by recursively iterating through the tree
    if(root == nullptr){
        return;
    }
    cout << root->data;
    prefix(root->left);
    prefix(root->right);
}

void arithmeticExpression::postfix(TreeNode* root){ //prints the postfix expression by recursively iterating through the tree
    if(root == nullptr){
        return;
    }
    postfix(root->left);
    postfix(root->right);
    cout << root->data;
}

int arithmeticExpression::priority(char op){ //helper function that determines the priority listings of the operators
    int priority = 0; //its basically like PEMDAS kinda
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){ //helper function that converts the given infix expression to postfix expression
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){ //if white space, continue
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){ //pushes ( onto stack initially)
                s.push(c);
            }
            else if(c == ')'){  //otherwise, if ), then you pop all the operators and (
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{ //otherwise, pop the operators depending on their priority then push the given operator on the stack
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    } //then output the remaining stack to oss
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){ //test cases and a recursive call to visualize the tree to terminal
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode* root){ //prints out the tree to out
    if(!root){
        return;
    }
    if(root->left){
        out << "\"" << root->data << "(" << root->key << ")\"" << "-> " << "\"" << root->left->data << "(" << root->left->key << ")\"" << endl;
        visualizeTree(out, root->left);
    }
    if(root->right){
        out << "\"" << root->data << "(" << root->key << ")\"" << "-> " << "\"" << root->right->data << "(" << root->right->key << ")\"" << endl;
        visualizeTree(out, root->right);
    }
}