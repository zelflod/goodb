
#include "MutuallyAttachable.h"

void MutuallyAttachable::Attach(MutuallyAttachable &b){
    Bs.push_back(&b);
    b.AttachWithoutReciprocating(*this);
}

void MutuallyAttachable::AttachWithoutReciprocating(MutuallyAttachable &b){
    Bs.push_back(&b);
}
