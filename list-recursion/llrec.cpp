#include "llrec.h"

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    if (head == NULL){
        smaller = NULL;
        larger = NULL;
        head = NULL;
        return;
    }
    if (head->val > pivot){
        larger = head;
        Node* temp = head->next;
        llpivot(temp, smaller, larger->next, pivot);
    }else{
        smaller = head;
        Node* temp = head->next;
        llpivot(temp, smaller->next, larger, pivot);
    }
}
