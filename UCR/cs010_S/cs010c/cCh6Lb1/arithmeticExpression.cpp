#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string& expression) : infixExpression(expression), root(nullptr) {}

void arithmeticExpression::buildTree() {
    string postFix = infix_to_postfix();
    stack<TreeNode*> node;

    int key = 'a';
    for(unsigned i = 0; i < postFix.size(); i++){
        char character = postFix[i];
        TreeNode* newNode = new TreeNode(character, key++);
        if(isalnum(character)){
            node.push(newNode);
        } else{
            newNode->right = node.top();
            node.pop();
            newNode->left = node.top();
            node.pop();
            node.push(newNode);
        }
    }
    root = node.top();
}

void arithmeticExpression::infix() {
  infix(root);
}

void arithmeticExpression::prefix() {
  prefix(root);
}

void arithmeticExpression::postfix() {
  postfix(root);
}

void arithmeticExpression::infix(TreeNode* root){
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

void arithmeticExpression::prefix(TreeNode* root){
    if(root == nullptr){
        return;
    }
    cout << root->data;
    prefix(root->left);
    prefix(root->right);
}

void arithmeticExpression::postfix(TreeNode* root){
    if(root == nullptr){
        return;
    }
    postfix(root->left);
    postfix(root->right);
    cout << root->data;
}

int arithmeticExpression::priority(char op){
    int priority = 0;
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

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
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
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
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

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode* root){
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