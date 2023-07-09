/*
11. Complete the “list of gods” example from §17.10.1 and run it.

    **I changed `Link* advance(int n)` so that `this` non-const qualified.
    I couldn't figure out a way to return pointer to current Link if n == 0 :(

    Two options were...
    - remove const-qualification for `this`                                 <- chose this option
    - make the function return a const Link* instead of a mutable Link*

12. Why did we define two versions of find()?

13. Modify the Link class from §17.10.1 to hold a value of a `struct God`. 
    `struct God` should have members of type `string`: name, mythology, vehicle, and weapon. 
    For example, 
        `God{"Zeus", "Greek", "", "lightning"}`
    and 
        `God{"Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir"}` 
    
    Write a print_all() function that lists gods with their attributes one per line. 
    
    Add a member function add_ordered() that places its new element in its correct lexicographical position. 
    
    Using the Links with the values of type God, make a list of gods from three mythologies; 
    then move the elements (gods) from that list to three lexicographically ordered lists — one for each mythology.


14. Could the “list of gods” example from §17.10.1 have been written using a singly-linked list; 
    that is, could we have left the prev member out of Link? 
    Why might we want to do that? For what kind of examples would it make sense to use a singly-linked list? 
    
    Re-implement that example using only a singly-linked list.
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
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
    // operations
    Link* insert(Link* n);                      // insert `n` before current object
    Link* add(Link* n);                         // insert `n` after  current object
    Link* erase();                              // remove current object from linked list
    Link* find(const string& s);                // find Link containing string `s`
    const Link* find(const string& s) const;    // find Link containing string `s` within const list
    Link* advance(int n) /*const*/;                 // advance pointer `n` positions in linked list
    Link* next() const { return succ; }         // advance pointer +1 position in linked list
    Link* previous() const { return prev; }     // advance pointer -1 position in linked list
private:
    Link* prev;
    Link* succ;
};

Link* Link::insert(Link* n)
// insert `n` before current object and return n
{
    // error checking
    if (n == nullptr) return this;
    // insert the new link!
    n->succ = this;
    n->prev = prev;             // prev is implicitly this->prev
    if (prev != nullptr)
        prev->succ = n;
    prev = n;
    return n;
}

Link* Link::add(Link* n)
// insert `n` after current object and return n
{
    if (n == nullptr) return this;
    // append the new link!
    n->succ = succ;
    if (succ != nullptr)
        succ->prev = n;
    n->prev = this;
    succ = n;
    return n;
}

Link* Link::erase()
// remove current object from linked list (and return "successor")
//      - if there are any `Link`s after current, return next `Link`
//      - if no `Link`s after current, return current end `Link`
//      - if the list is now empty, return `nullptr`
{
    if (prev != nullptr)
        prev->succ = succ;
    if (succ != nullptr) {
        succ->prev = prev;
        return succ;
    } else
        return prev;
}


Link* Link::find(const string& s)
// find Link containing string `s` if any;
// otherwise return `nullptr`
{
    // search from current position to front
    Link* curr = this;
    while(curr != nullptr) {
        if (curr->value == s) return curr;
        curr = curr->prev;
    }

    // if we get here, we should search current position to back
    curr = this;
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
    Link curr_link = *this; // make a copy
    Link* curr = &curr_link;

    // search from current position to front
    while(curr != nullptr) {
        if (curr->value == s) return curr;
        curr = curr->prev;
    }

    // if we get here, we should search current position to back
    curr = &curr_link; // reset to curr_link
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

    Link* curr = this;
        

    // wasn't sure how to get around `const` in function!  that means it's not supposed to
    // mess with internal state of current object, so we're making a copy.

    // move forward
    if (n > 0) {
        while(curr != nullptr && n > 0) {
            curr = curr->succ;
            n--;
        }
        // if n > 0, that means we hit end of list before reaching nth `Link`.
        if (n > 0)
            return nullptr;
        // otherwise, we hit the `Link` we wanted!
        return curr;
    } 
    // move backwards
    else {
        while(curr != nullptr && n < 0) {
            curr = curr->prev;
            n++;
        }
        if (n < 0)
            return nullptr;
        return curr;
    }
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
    if (l.next() != nullptr || l.previous() != nullptr) {
        cout << "    ... did not correctly initialize `l`'s prev/succ pointers\n";
        return false;
    }

    string v2 = "second value";
    Link l2 = Link(v2, &l, &l);
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
    Link* ret1 = a.add(&b);  // A <-> B
    Link* ret2 = b.add(&c);  // A <-> B <-> C
    
    if (a.previous() != nullptr || a.next() != &b || b.previous() != &a || ret1 != &b) {
        cout << "    ... a.add(&b) failed.\n";
        return false;
    }
    if (b.next() != &c || c.previous() != &b || ret2 != &c) {
        cout << "    ... b.add(&c) failed.\n";
        return false;
    }

    Link* ret3 = b.add(nullptr);
    if (ret3 != &b || b.previous() != &a || b.next() != &c) {
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

    Link* ret = b.insert(nullptr);
    if (ret != &b || b.previous() != &a || b.next() != &c) {
        cout << "    ... b.insert(nullptr) failed\n";
        return false;
    }

    Link n {"N"};
    ret = b.insert(&n);
    if(ret != &n || n.previous() != &a || n.next() != &b 
                 || b.previous() != &n || b.next() != &c) {
        cout << "    ... b.insert(&n) failed\n";
        return false;
    }

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
    if(ret != &c || a.next() != &c || c.previous() != &a) {
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
    
    return true;
}

void run_tests() {
    cout << "... testing construction:               \n" << test_construction() << '\n';
    cout << "... testing Link::add():                \n" << test_add() << '\n';
    cout << "... testing Link::insert():             \n" << test_insert() << '\n';
    cout << "... testing Link::erase():              \n" << test_insert() << '\n';
    cout << "... testing Link::advance(int n):       \n" << test_advance() << '\n';
    cout << "... testing Link::find(const string& s):\n" << test_find() << '\n';
}




int main() {
    run_tests();
    return 0;
}