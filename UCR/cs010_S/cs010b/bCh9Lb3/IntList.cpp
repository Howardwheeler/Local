#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

ostream & operator<<(ostream &out, const IntList &list){
   IntNode *temp = list.head;
   if(temp != nullptr)
   {
      out << temp->value;
      if(temp->next != nullptr)
      {
         out << " ";
         operator<<(out, temp->next);
      }
   }

   return out;
}

bool IntList::exists(int value) const{
   IntNode *temp = head;
   return exists(temp, value);
}

bool IntList::exists(IntNode *temp, int value) const{
   if(temp == nullptr)
   {
      return false;
   }
   if(temp->value == value)
   {
      return true;
   }
   return exists(temp->next, value);
}

ostream & operator<<(ostream &out, IntNode *node1){
   if(node1 != nullptr)
   {
      out << node1->value;
      if(node1->next != nullptr)
      {
         out << " ";
         operator<<(out, node1->next);
      }
   }
   return out;
}