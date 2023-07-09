/*
11. Complete the “list of gods” example from §17.10.1 and run it.

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

#include <string>
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
    Link* advance(int n) const;                 // advance pointer `n` positions in linked list
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

Link* Link::advance(int n) const
// advance pointer `n` positions in linked list and return new `Link` if possible;
// otherwise return `nullptr
{
    // wasn't sure how to get around `const` in function!  that means it's not supposed to
    // mess with internal state of current object, so we're making a copy.
    Link curr_val = *this;
    Link* curr = &curr_val;

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