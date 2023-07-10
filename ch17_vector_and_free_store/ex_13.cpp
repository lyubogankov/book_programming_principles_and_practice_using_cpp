/*
13. x Modify the Link class from §17.10.1 to hold a value of a `struct God`. 
    `struct God` should have members of type `string`: name, mythology, vehicle, and weapon. 
    For example, 
        `God{"Zeus", "Greek", "", "lightning"}`
    and 
        `God{"Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir"}` 
    
    x Write a print_all() function that lists gods with their attributes one per line. 
    
    Add a member function add_ordered() that places its new element in its correct lexicographical position. 
    
    Using the Links with the values of type God, 
        x make a list of gods from three mythologies; 
        then move the elements (gods) from that list to three lexicographically ordered lists — one for each mythology.
*/

#include <iomanip>
#include <iostream>
#include <string>
using std::cout;
using std::ostream;
using std::string;
using std::setw;

// for ex 13
struct God {
    // member variables
    string name;
    string mythology;
    string vehicle;
    string weapon;
    //
    God(const string& n, const string& m, const string& v, const string& w)
        : name {n}, mythology {m}, vehicle {v}, weapon {w} {}
};
bool operator==(const God& a, const God& b) {
    return (a.name == b.name && a.mythology == b.mythology 
         && a.vehicle == b.vehicle && a.weapon == b.weapon);
};
bool operator!=(const God& a, const God& b) { return !(a == b); }
ostream& operator<<(ostream& os, const God& g) {
    os << "[name] " << setw(8) << g.name 
     << "  [mythology] " << setw(5) << g.mythology 
     << "  [vehicle] " << setw(1) << g.vehicle 
     << "  [weapon] " << g.weapon;
    return os;
}

// from 17.10:
class Link {
public:
    God value;
    // constructor
    Link(const God& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} { }
    // operations
    Link* insert(Link* n);                      // insert `n` before current object
    Link* add(Link* n);                         // insert `n` after  current object
    Link* add_ordered(Link* n);                 // insert link in "correct lexographical position"
    Link* erase();                              // remove current object from linked list
    Link* find(const God& s);                   // find Link containing string `s`
    const Link* find(const God& s) const;       // find Link containing string `s` within const list
    Link* advance(int n) /*const*/;             // advance pointer `n` positions in linked list
    Link* next() const { return succ; }         // advance pointer +1 position in linked list
    Link* previous() const { return prev; }     // advance pointer -1 position in linked lis
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

Link* Link::find(const God& s)
// find Link containing God `s` if any;
// otherwise return `nullptr`
{
    cout << "    ... this is the non-const version of ::find()\n";
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
const Link* Link::find(const God& s) const
// find Link containing string `s` if any;
// otherwise return `nullptr`
{
    cout << "    ... this is the const version of ::find()\n";

    if (s == value)
        return this;

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

Link* Link::add_ordered(Link* n)
// Places new element in correct lexicographical position and return `n`;
// For `Link`s with value of type `God`, comparisons will just be based on first name.
{
    if (n == nullptr) return this;

    // first, let's get to the first `Link` in the list (not checking for cycles, though.)
    Link* l = this;
    while (l->previous())
        l = l->previous();

    // now, go from front to back and see where new Link* belongs.
    while(l) {
        // if `n`'s value comes before current node, insert `n` before current node!
        if (n->value.name < l->value.name) {
            l->insert(n);
            return n;
        }
        l = l->next();
    }
    // if we haven't returned, that means we went through the whole list
    // and `n` doesn't belong in front of any node, which means it belongs
    // at the back.
    l->add(n);
    return n;
}

void print_all(Link* l) {
    // first, let's get to the first `Link` in the list (not checking for cycles, though.)
    while (l->previous())
        l = l->previous();
    // then, print each God from front to back!
    cout << "{" << '\n';
    while (l) {
        cout << "    " << l->value << '\n';
        l = l->next();
    }
    cout << "}" << '\n';
}

// ------------------------------------------------------------------------------------------------
// Testing the Link class

bool test_construction() {

    God g {"Zeus", "Greek", "", "lightning"};

    // testing single link
    Link l {g};
    if (l.value != g) {
        cout << "    ... did not correctly initialize `l`'s value\n";
        return false;
    }
    if (l.next() != nullptr || l.previous() != nullptr) {
        cout << "    ... did not correctly initialize `l`'s prev/succ pointers\n";
        return false;
    }

    God g2 {"Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir"};
    Link l2 = Link(g2, &l, &l);
    if (l2.next() != &l || l2.next() != &l) {
        cout << "    ... did not correctly initialize `l2`'s prev/succ pointers to `&l`\n";
        return false;
    }

    return true;
}
bool test_add() {
    // setup
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
    
    Link* ret1 = a.add(&b);  // A <-> B
    if (a.previous() != nullptr || a.next() != &b || b.previous() != &a || ret1 != &b) {
        cout << "    ... a.add(&b) failed.\n";
        return false;
    }

    Link* ret2 = b.add(&c);  // A <-> B <-> C
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
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    Link* ret = b.insert(nullptr);
    if (ret != &b || b.previous() != &a || b.next() != &c) {
        cout << "    ... b.insert(nullptr) failed\n";
        return false;
    }

    God gn = {"N", "N", "N", "N"};
    Link n {gn};
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
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
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
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
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
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C

    Link* ret;
    // case 1: can't find string
    God fakegod {"memester", "", "", ""};
    ret = b.find(fakegod);
    if (ret != nullptr) {
        cout << "    ... b.find(\"meme\") failed\n";
        return false;
    }
    // case 2: string belongs to current link
    ret = b.find(gb);
    if (ret != &b) {
        cout << "    ... b.find(\"B\") failed\n";
        return false;
    }
    // case 3: string is ahead of current link
    ret = b.find(gc);
    if (ret != &c) {
        cout << "    ... b.find(\"C\") failed\n";
        return false;
    }
    // case 4: string is behind current link
    ret = b.find(ga);
    if (ret != &a) {
        cout << "    ... b.find(\"A\") failed\n";
        return false;
    }

    return true;
}
bool test_find_const() {
    // setup
    God ga {"A", "A", "A", "A"};
    God gb {"B", "B", "B", "B"};
    God gc {"C", "C", "C", "C"};
    Link a {ga};
    Link b {gb};
    Link c {gc};
    a.add(&b);  // A <-> B
    b.add(&c);  // A <-> B <-> C
    const Link* bp = &b;

    const Link* retc0 = bp->find(gb);
    if (retc0 != &b) {
        cout << "    ... b.find(\"B\") failed (const version)\n";
        return false;
    }
    God fakegod {"memester", "", "", ""};
    const Link* retc1 = bp->find(fakegod);
    if (retc1 != nullptr) {
        cout << "    ... b.find(\"meme\") failed (const version)\n";
        return false;
    }
    const Link* retc2 = bp->find(ga);
    if (retc2 != &a) {
        cout << "    ... b.find(\"A\") failed (const version)\n";
        return false;
    }

    Link* ret = a.find(gb);
    if (ret != &b) {
        cout << "    ... a.find(\"B\") failed (non-const version)\n";
        return false;
    }
    
    return true;
}
bool test_add_ordered() {
    // setup
    God ga {"A", "A", "A", "A"};
    God gc {"C", "C", "C", "C"};
    God ge {"E", "E", "E", "E"};
    Link a {ga};
    Link c {gc};
    Link e {ge};
    a.add(&c);  // A <-> C
    c.add(&e);  // A <-> C <-> E

    God gfront {"a", "", "", ""};
    Link newfront {gfront};
    God gb {"B", "B", "B", "B"};
    Link b {gb};
    God gd {"D", "D", "D", "D"};
    Link d {gd};
    God gz {"Z", "Z", "Z", "Z"};
    Link z {gz};

    Link* ret;
    cout << "Before any operations:\n";
    print_all(&c);
    // Case 0: add nullptr
    ret = c.add_ordered(nullptr);
    if (ret != &c) {
        cout << "   ... c.add_ordered(nullptr) failed\n";
        return false;
    }
    // Case 1: add something after current link, but not end of list
    ret = c.add_ordered(&d);
    if (ret != &d || c.next() != &d || d.previous() != &c || d.next() != &e || e.previous() != &d) {
        cout << "   ... c.add_ordered(&d) failed\n";
        return false;
    }
    cout << "After c.add_ordered(&d):\n";
    print_all(&c);
    // case 2: add something before current link
    ret = c.add_ordered(&b);
    if (ret != &b || c.previous() != &b || b.next() != &c || a.next() != &b || b.previous() != &a) {
        cout << "   ... c.add_ordered(&b) failed\n";
        return false;
    }
    cout << "After c.add_ordered(&b):\n";
    print_all(&c);

    // // case 2b: add something to front of list
    // ret = c.add_ordered(&newfront);
    // if (ret != &newfront || newfront.previous() != nullptr || newfront.next() != &a || a.previous() != &newfront) {
    //     cout << "   ... c.add_ordered(&newfront) failed\n";
    //     return false;
    // }
    // cout << "After c.add_ordered(&newfront):\n";
    // print_all(&c);

    // // case 3: add something to end of entire list
    // ret = c.add_ordered(&z);
    // if (ret != &z || z.previous() != &e || e.next() != &z || z.next() != nullptr) {
    //     cout << "   ... c.add_ordered(&z) failed\n";
    //     return false;
    // }
    // cout << "After c.add_ordered(&z):\n";
    // print_all(&c);

    return true;
}
void run_tests() {
    cout << "... testing construction:                                 \n" << test_construction() << '\n';
    cout << "... testing Link* Link::add():                            \n" << test_add() << '\n';
    cout << "... testing Link* Link::insert():                         \n" << test_insert() << '\n';
    cout << "... testing Link* Link::erase():                          \n" << test_insert() << '\n';
    cout << "... testing Link* Link::advance(int n):                   \n" << test_advance() << '\n';
    cout << "... testing Link* Link::find(const string& s):            \n" << test_find() << '\n';
    cout << "... testing const Link* Link::find(const string& s) const:\n" << test_find_const() << '\n';
    cout << "... testing Link* Link::add_ordered(...):                 \n" << test_add_ordered() << '\n';
}

// ---
// code for completing ex13
void ex13() {
    // instantiate the gods
    God zeus {"zeus", "greek", "", "lightning"};
    God poseidon {"poseidon", "greek", "", "trident"};
    God ares {"ares", "greek", "", ""};
    God jupiter {"jupiter", "roman", "", "lightning"};
    God neptune {"neptune", "roman", "", "trident"};
    God mars {"mars", "roman", "", ""};
    God odin {"odin", "norse", "", ""};
    God thor {"thor", "norse", "", "hammer"};
    God freia {"freia", "norse", "", ""};

    cout << "Test print: " << zeus << '\n';

    // make the individual links
    Link gz {zeus};
    Link gp {poseidon};
    Link ga {ares};
    Link rj {jupiter};
    Link rn {neptune};
    Link rm {mars};
    Link no {odin};
    Link nt {thor};
    Link nf {freia};
    // construct the doubly linked list
    gz.add(&gp);
    gp.add(&ga);
    ga.add(&rj);
    rj.add(&rn);
    rn.add(&rm);
    rm.add(&no);
    no.add(&nt);
    nt.add(&nf);

    print_all(&gz);
}

int main() {
    run_tests();
    ex13();
    return 0;
}