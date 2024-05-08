#include "Node.h"

ostream &operator<<(ostream &out, const nodePtr &rhs){
    out << rhs.item << "(" << rhs.count << ")";
    return out;
}