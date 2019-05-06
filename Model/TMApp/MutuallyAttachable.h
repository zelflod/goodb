
#ifndef GOODB_MUTUALLYATTACHABLE_H
#define GOODB_MUTUALLYATTACHABLE_H

#include <vector>

class MutuallyAttachable {
public:
    void Attach(MutuallyAttachable &b);
protected:
    void AttachWithoutReciprocating(MutuallyAttachable &b);
private:
    std::vector<MutuallyAttachable *> Bs;
};


#endif
