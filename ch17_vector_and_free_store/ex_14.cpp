/*
14. Could the “list of gods” example from §17.10.1 have been written using a singly-linked list; 
    that is, could we have left the prev member out of Link?

    Operations used in 17.10.1:
    insert()
    find()
    next()
    erase()


    Why might we want to do that? For what kind of examples would it make sense to use a singly-linked list? 
    
    Re-implement that example using only a singly-linked list.

    **Big change: each operation returns the (new) *front* of the linked list.
        Otherwise, it's impossible to traverse backwards and I can't implement some of the member functions!

        This also means that each function assumes that it is being called from the front of the linked list
        (or that the user intended a subset of the singly linked list to be used).
*/

#include <iostream>
#include <string>
using std::cout;
using std::string;

// from 17.10:
class Link {
public:
    string value;
    // constructor
    Link(const string& v, Link* s = nullptr) : value{v}, succ{s} { }
    // operations
    Link* insert(Link* n, Link* target=nullptr);    // insert `n` before `target` or current object
    Link* add(Link* n);                             // insert `n` after current object
    Link* erase();                                  // remove current object from linked list
    Link* find(const string& s);                    // find Link containing string `s`
    const Link* find(const string& s) const;        // find Link containing string `s` within const list
    Link* advance(int n) /*const*/;                 // advance pointer `n` positions in linked list
    Link* next() const { return succ; }             // advance pointer +1 position in linked list
private:
    Link* succ;
};

Link* Link::insert(Link* n, Link* target)
// If target == nullptr, then insert `n` in front of current object.
//      This should only be used when `this` is the front of the list, otherwise the list will splinter.
// If target != nullptr, then insert `n` in front of target.
//      Assumption is that operation is called from front of linked list, and list will be traversed until `target` is found.
{
    // error checking
    if (n == nullptr) return this;

    // insert `n` in front of `this`, making it the new front-of-list
    if (target == nullptr || target == this) {
        n->succ = this;
        return n;
    }
    // otherwise, search the list and insert `n` in front of target.
    // need to return front of list, which is `this`.
    Link* prev = this;
    Link* curr = this->next();
    while(curr) {
        // we've found our match!  insert `n` between `prev` / `curr`
        if (curr == target) {
            prev->succ = n;
            n->succ = curr;
            break;
        }
        // advance along list
        prev = curr;
        curr = curr->next();
    }
    return this;
}

Link* Link::add(Link* n)
// Insert `n` after current object and return n
// This function doesn't /need/ to be called from front of list since it appends *after*
// current node (follows singly-linked direction).  Therefore, we don't need to worry about
// a `target` parameter or always returning front of list.
{
    if (n == nullptr) return this;
    // append the new link!
    n->succ = succ;
    succ = n;
    return n;
}

Link* Link::erase()
// remove current object from linked list (and return "successor")
//      - if there are any `Link`s after current, return next `Link`
//      - if no `Link`s after current, return current end `Link`
//      - if the list is now empty, return `nullptr`
{
    // if (prev != nullptr)
    //     prev->succ = succ;
    // if (succ != nullptr) {
    //     succ->prev = prev;
    //     return succ;
    // } else
    //     return prev;
    return this;
}


Link* Link::find(const string& s)
// find Link containing string `s` if any;
// otherwise return `nullptr`
{
    cout << "    ... this is the non-const version of ::find()\n";

    // // Can no longer do this, because we can only move in one direction!
    // // search from current position to front
    // Link* curr = this;
    // while(curr != nullptr) {
    //     if (curr->value == s) return curr;
    //     curr = curr->prev;
    // }

    // if we get here, we should search current position to back
    Link* curr = this;
    while(curr != nullptr) {
        if (curr -> value == s) return curr;
        curr = curr->succ;
    }

    // if we get here, we did not find the desired string.
    return nullptr;
}
const Link* Link::find(const string& s) const
// find Link containing string `s` if any;
// otherwise return `nullptr`
{
    cout << "    ... this is the const version of ::find()\n";

    if (s == value)
        return this;

    Link curr_link = *this; // make a copy
    Link* curr = &curr_link;

    // // Can only search front -> back, backwards
    // // search from current position to front
    // while(curr != nullptr) {
    //     if (curr->value == s) return curr;
    //     curr = curr->prev;
    // }
    // curr = &curr_link; // reset to curr_link

    // if we get here, we should search current position to back
    while(curr != nullptr) {
        if (curr -> value == s) return curr;
        curr = curr->succ;
    }

    // if we get here, we did not find the desired string.
    return nullptr;
}

Link* Link::advance(int n) /*const*/
// advance pointer `n` positions in linked list and return new `Link` if possible;
// otherwise return `nullptr
{

    // Link* curr = this;
        
    // // wasn't sure how to get around `const` in function!  that means it's not supposed to
    // // mess with internal state of current object, so we're making a copy.

    // // move forward
    // if (n > 0) {
    //     while(curr != nullptr && n > 0) {
    //         curr = curr->succ;
    //         n--;
    //     }
    //     // if n > 0, that means we hit end of list before reaching nth `Link`.
    //     if (n > 0)
    //         return nullptr;
    //     // otherwise, we hit the `Link` we wanted!
    //     return curr;
    // } 
    // // move backwards
    // else {
    //     while(curr != nullptr && n < 0) {
    //         curr = curr->prev;
    //         n++;
    //     }
    //     if (n < 0)
    //         return nullptr;
    //     return curr;
    // }
    return this;
}

void print_all(Link* p) {
    cout << "{";
    while (p) {
        cout << p->value;
        if (p->next())
            cout << ", ";
        p = p->next();
    }
    cout << "}";
}

// ------------------------------------------------------------------------------------------------
// Testing the Link class

bool test_construction() {

    // testing single link
    string v = "value";
    Link l = Link(v);
    if (l.value != v) {
        cout << "    ... did not correctly initialize `l`'s value\n";
        return false;
    }
    if (l.next() != nullptr) {
        cout << "    ... did not correctly initialize `l`'s succ pointer\n";
        return false;
    }

    string v2 = "second value";
    Link l2 = Link(v2, &l);
    if (l2.next() != &l || l2.next() != &l) {
        cout << "    ... did not correctly initialize `l2`'s prev/succ pointers to `&l`\n";
        return false;
    }

    return true;
}
bool test_add() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    Link* list = &a;

    cout << "    Original list: ";
    print_all(list);
    cout << '\n';

    Link* ret1 = a.add(&b);  // A <-> B
    if (a.next() != &b || ret1 != &b) {
        cout << "    ... a.add(&b) failed.\n";
        return false;
    }
    cout << "    After add(&b): ";
    print_all(list);
    cout << '\n';

    Link* ret2 = b.add(&c);  // A <-> B <-> C
    if (b.next() != &c || ret2 != &c) {
        cout << "    ... b.add(&c) failed.\n";
        return false;
    }
    cout << "    After add(&c): ";
    print_all(list);
    cout << '\n';

    Link* ret3 = b.add(nullptr);
    if (ret3 != &b || b.next() != &c) {
        cout << "    ... b.add(nullptr) failed.\n";
        return false;
    }

    return true;
}
bool test_insert() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    Link* list = &a;

    cout << "    Original list: ";
    print_all(list);
    cout << "\n";

    list = list->insert(nullptr, &b);
    if (list != &a || b.next() != &c) {
        cout << "    ... list->insert(nullptr, &b) failed\n";
        return false;
    }

    Link x {"X"};
    list = list->insert(&x, &b);
    if(list != &a || x.next() != &b || b.next() != &c) {
        cout << "    ... list->insert(&x, &b) failed\n";
        return false;
    }
    cout << "    After insert X ";
    print_all(&a);
    cout << "\n";

    Link y {"Y"};
    list = list->insert(&y);
    if (list != &y || y.next() != &a || a.next() != &x) {
        cout << "    ... list->insert(&y) failed\n";
        return false;
    }
    cout << "    After insert Y ";
    print_all(list);
    cout << "\n";

    return true;
}
bool test_erase() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    // case 1: erase middle node, get `&c` back
    Link* ret = b.erase();
    if(ret != &c || a.next() != &c) {
        cout << "    ... b.erase() failed\n";
        return false;
    }

    // case 2: erase `c`, get `&a` back
    ret = c.erase();
    if(ret != &a || a.next() != nullptr) {
        cout << "    ... c.erase() failed\n";
        return false;
    }

    // case 3: erasing last `Link` in the list, get `nullptr` back
    ret = a.erase();
    if(ret != nullptr) {
        cout << "    ... a.erase() failed\n";
        return false;
    }

    return true;
}
bool test_advance() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    Link* ret;
    // case 1: advance by 0, should get same obj back
    ret = b.advance(0);
    if(ret != &b) {
        cout << "    ... b.advance(0) failed\n";
        return false;
    }   
    // case 2: advance by positive integer within list bounds, should get Link* back
    ret = b.advance(1);
    if(ret != &c) {
        cout << "    ... b.advance(1) failed\n";
        return false;
    }
    // case 3: advance by positive integer outside list bounds, should get nullptr back
    ret = b.advance(2);
    if(ret != nullptr) {
        cout << "    ... b.advance(2) failed\n";
        return false;
    }
    // case 4: advance by negative integer within list bounds, should get Link* back
    ret = b.advance(-1);
    if(ret != &a) {
        cout << "    ... a.advance(-1) failed\n";
        return false;
    }
    // case 5: advance by negative integer outside list bounds, should get nullptr back
    ret = b.advance(-2);
    if(ret != nullptr) {
        cout << "    ... b.advance(-2) failed\n";
        return false;
    }

    return true;
}
bool test_find() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    Link* ret;
    // case 1: can't find string
    ret = b.find("meme");
    if (ret != nullptr) {
        cout << "    ... b.find(\"meme\") failed\n";
        return false;
    }
    // case 2: string belongs to current link
    ret = b.find("B");
    if (ret != &b) {
        cout << "    ... b.find(\"B\") failed\n";
        return false;
    }
    // case 3: string is ahead of current link
    ret = b.find("C");
    if (ret != &c) {
        cout << "    ... b.find(\"C\") failed\n";
        return false;
    }
    // case 4: string is behind current link
    ret = b.find("A");
    if (ret != &a) {
        cout << "    ... b.find(\"A\") failed\n";
        return false;
    }

    return true;
}

bool test_find_const() {
    // setup
    Link a {"A"};
    Link b {"B"};
    Link c {"C"};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C
    const Link* bp = &b;

    const Link* retc0 = bp->find("B");
    if (retc0 != &b) {
        cout << "    ... b.find(\"B\") failed (const version)\n";
        return false;
    }
    const Link* retc1 = bp->find("meme");
    if (retc1 != nullptr) {
        cout << "    ... b.find(\"meme\") failed (const version)\n";
        return false;
    }
    const Link* retc2 = bp->find("A");
    if (retc2 != &a) {
        cout << "    ... b.find(\"A\") failed (const version)\n";
        return false;
    }

    Link* ret = a.find("B");
    if (ret != &b) {
        cout << "    ... a.find(\"B\") failed (non-const version)\n";
        return false;
    }
    
    return true;
}


void run_tests() {
    cout << "... testing construction:                                 \n" << test_construction() << '\n';
    cout << "... testing Link* Link::add():                            \n" << test_add() << '\n';
    cout << "... testing Link* Link::insert():                         \n" << test_insert() << '\n';
    // cout << "... testing Link* Link::erase():                          \n" << test_insert() << '\n';
    // cout << "... testing Link* Link::advance(int n):                   \n" << test_advance() << '\n';
    // cout << "... testing Link* Link::find(const string& s):            \n" << test_find() << '\n';
    // cout << "... testing const Link* Link::find(const string& s) const:\n" << test_find_const() << '\n';
}

void book_17_10_1() {
    Link* norse_gods = new Link{"Thor"};
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freia"});

    Link* greek_gods = new Link{"Hera"};
    greek_gods = greek_gods->insert(new Link{"Athena"});
    greek_gods = greek_gods->insert(new Link{"Mars"});
    greek_gods = greek_gods->insert(new Link{"Poseidon"});

    // Mars (Roman) -> Ares (Greek)
    Link* p = greek_gods->find("Mars");
    if (p)
        p->value = "Ares";

    // Move Zeus from norse -> greek pantheon
    Link* p2 = norse_gods->find("Zeus");
    if (p2) {
        if (p2 == norse_gods) norse_gods = p2->next();
        p2->erase();
        greek_gods = greek_gods->insert(p2);
    }

    cout << "Norse:\n";
    print_all(norse_gods);
    cout << "\n";

    cout << "Greek:\n";
    print_all(greek_gods);
    cout << "\n";
}


int main() {
    run_tests();
    return 0;
}