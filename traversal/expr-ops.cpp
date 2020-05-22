#include "expr-reader.h"
#include "expr-ops.h"
#include <iostream>

using namespace std;
/*-----------------------------------------------------------------------------
 *  Implement the following functions below.
 *  Processing of each (sub)expression must be recursive (i.e. loops
 *    may only be used to iterate through the child vector of the given node).
 *  You may define recursive helper functions to adapt the function signatures.
 *    However, only exprPrinter likely needs a helper function.
 ----------------------------------------------------------------------------*/
void printHelper(std::ostream& ostr, Node* n){
   if(n->val == "+" || n->val == "-" || n->val == "*" || n->val == "/")
   {
        ostr << "( ";
        for(int i = 0; i < int(n->children.size()); ++i){
            if(n->children[i]->val == "+" || n->children[i]->val == "-" || n->children[i]->val == "*" || n->children[i]->val == "/"){
                printHelper(ostr, n->children[i]);
                if(i != int(n->children.size()) - 1){
                    ostr << n->val << " ";
                }
            }else{
                if(i == int(n->children.size()) - 1){
                    ostr << n->children[i]->val << " ";
                }else{
                    ostr << n->children[i]->val << " " << n->val << " ";
                }
                
            }
        }
        ostr << ") ";
    }
}

void exprPrinter(std::ostream& ostr, Node* n)
{
    if(n->val != "+" && n->val != "-" && n->val != "*" && n->val != "/"){
        ostr << n->val;
    }else{
        printHelper(ostr, n);
        ostr << endl;
    }
}

int solver(Node* n){
    int state = 0;
    if(n->val == "+"){
        state = 0;
    }else if(n->val == "-"){
        state = 1;
    }else if(n->val == "*"){
        state = 2;
    }else if(n->val == "/"){
        state = 3;
    }
    int temp;
    for(int i = 0; i < int(n->children.size()); ++i){
        if(n->children[i]->val == "+" || n->children[i]->val == "-" || n->children[i]->val == "*" || n->children[i]->val == "/"){
            switch (state) {
                case 0:
                    // +
                    if(i == 0){
                        temp = solver(n->children[i]);
                    }else{
                        temp += solver(n->children[i]);
                    }
                    break;
                case 1:
                    // -
                    if(i == 0){
                        temp = solver(n->children[i]);
                    }else{
                        temp -= solver(n->children[i]);
                    }
                    break;
                case 2:
                    // *
                    if(i == 0){
                        temp = solver(n->children[i]);
                    }else{
                        temp *= solver(n->children[i]);
                    }
                    break;
                case 3:
                    // /
                    if(i == 0){
                        temp = solver(n->children[i]);
                    }else{
                        temp /= solver(n->children[i]);
                    }
                    break;
                default:
                    break;
            }
        }else{
            switch (state) {
                case 0:
                    // +
                    if(i == 0){
                        temp = stoi(n->children[i]->val);
                    }else{
                        temp += stoi(n->children[i]->val);
                    }
                    break;
                case 1:
                    // -
                    if(i == 0){
                        temp = stoi(n->children[i]->val);
                    }else{
                        temp -= stoi(n->children[i]->val);
                    }
                    break;
                case 2:
                    // *
                    if(i == 0){
                        temp = stoi(n->children[i]->val);
                    }else{
                        temp *= stoi(n->children[i]->val);
                    }
                    break;
                case 3:
                    // /
                    if(i == 0){
                        temp = stoi(n->children[i]->val);
                    }else{
                        temp /= stoi(n->children[i]->val);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return temp;
}
int exprSolver(Node* n)
{
    /* Should never be called on NULL expression -- Do Not Modify */
    if(n == NULL) {
        throw std::logic_error("Can't solve a NULL expression");
    }else{
        return solver(n);
    }
}

void checkValid(Node* n, bool& output){
    if(n == NULL){
        return;
    }else{
        //test if current node is a proper operation or integer
        if(n->val != "+" && n->val != "-" && n->val != "*" && n->val != "/"){
            try {
                stoi(n->val);
            } catch (const std::invalid_argument& ia) {
                output = false;
            }
        }
        if(n->children.size() == 0){
            return;
        }else{
            for(int i = 0; i < int(n->children.size()); ++i){
                checkValid(n->children[i], output);
            }
        }
    }
}
bool exprIsValid(Node* n)
{
    bool output = true;
    if(n == NULL){
        throw std::logic_error("Node is NULL!");
    }else{
        checkValid(n, output);
        return output;
    }

}
