/*
13. Write a Tracer class where its constructor prints a string and its destructor prints a string. 
    Give the strings as constructor arguments. 
    
    Use it to see where RAII management objects will do their job 
    (i.e., experiment with Tracers as local objects, member objects, global objects, objects allocated by new, etc.). 
    
    Then add a copy constructor and a copy assignment so that you can use Tracer objects to see when copying is done.
*/

/*
Did a little extra, also tested move assignment/construction.
For some reason, only the assignment worked, move construction did not work?  See very bottom for printout.
*/

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Tracer {
private:
    string constructor_string, destructor_string;
public:
    Tracer(string constructor_str, string destructor_str)
        : constructor_string {constructor_str}, destructor_string {destructor_str} {
            cout << constructor_string << '\n';
        }
    ~Tracer() {
        cout << destructor_string << '\n';
    }
    // copy initialization / construction
    Tracer(const Tracer& other) 
    : constructor_string {other.constructor_string}, destructor_string {other.destructor_string + "* this is the new one"} {
        cout << "--- Currently within Tracer's copy constructor!\n";
    }
    // copy assignment
    Tracer& operator=(const Tracer& other) {
        cout << "--- Currently within Tracer's copy assignment operator overload!\n";
        constructor_string = other.constructor_string;
        destructor_string = other.destructor_string + "* this is the new one";
        return *this;
    }
    // move constructor
    Tracer(Tracer&& other)
    : constructor_string {other.constructor_string}, destructor_string {other.destructor_string + "* this is the new one"} {
        cout << "--- Currently within Tracer's move constructor!\n";
    }
    // move assignment
    Tracer& operator=(Tracer&& other) {
        cout << "--- Currently within Tracer's move assignment operator overload!\n";
        constructor_string = other.constructor_string;
        destructor_string = other.destructor_string + "* this is the new one";
        return *this;
    }
};

struct MyStruct {
private:
    Tracer t;
public:
    MyStruct(string constructor_str, string destructor_str)
        : t {Tracer(constructor_str, destructor_str)} {
            cout << "- Just made a MyStruct.\n";
        }
    ~MyStruct() {
        cout << "- Just destroyed a MyStruct.\n";
    }
};

Tracer global_tracer {"--- global tracer constructor", "--- global tracer destructor"};

// local objects on stack, on heap
void fn_stack() {
    cout << "\nRunning fn_stack()\n";
    Tracer stack_tracer {"--- stack tracer constructor", "--- stack tracer destructor"};
    cout << "Exiting fn_stack()\n\n";
}
Tracer* fn_heap_creation() {
    cout << "\nRunning fn_heap_creation()\n";
    Tracer* heap_tracer_ptr = new Tracer("--- heap tracer constructor", "--- heap tracer destructor");
    cout << "Exiting fn_heap_creation()\n\n";
    return heap_tracer_ptr;
}
void fn_heap_deletion(Tracer* heap_tracer_ptr) {
    cout << "\nRunning fn_heap_deletion()\n";
    delete heap_tracer_ptr;
    cout << "Exiting fn_heap_deletion()\n\n";
}
void stack_mystruct() {
    cout << "\nRunning stack_mystruct()\n";
    MyStruct ms {"--- MyStruct member constructor", "--- MyStruct member destructor"};
    cout << "Exiting stack_mystruct()\n\n";
}
void test_copy_construction() {
    cout << "\nRunning test_copy_construction()...\n";
    Tracer original {"--- original construction (stack)", "--- original destruction (stack)"};
    Tracer cc = original;
    cout << "Exiting test_copy_construction()...\n\n";
}
void test_copy_assignment() {
    cout << "\nRunning test_copy_assignment()...\n";
    Tracer original {"--- original construction (stack)", "--- original destruction (stack)"};
    Tracer ca {"--- will-be-copy-assigned-over construction (stack)", "--- will-be-copy-assigned-over destruction (stack)"};
    ca = original;
    cout << "Exiting test_copy_assignment()...\n\n";
}

Tracer return_tracer() {
    cout << "\nRunning return_tracer()...\n";
    return Tracer("created in return_tracer on stack, construction", "created in return_tracer on stack, destruction");
    cout << "Exiting return_tracer()...\n\n";
}
void test_move_construction() {
    cout << "\nRunning test_move_construction()...\n";
    Tracer t = return_tracer();
    cout << "Exiting test_move_construction()...\n\n";
}
void test_move_assignment() {
    cout << "\nRunning test_move_assignment()...\n";
    Tracer t {"test_move_assignment original, construction", "test_move_assignment original, destruction"};
    t = return_tracer();
    cout << "Exiting test_move_assignment()...\n\n";
}

int main() {
    cout << "\nRunning main()\n";
    fn_stack();
    Tracer* heap_tracer_ptr = fn_heap_creation();
    fn_heap_deletion(heap_tracer_ptr);
    stack_mystruct();
    test_copy_construction();
    test_copy_assignment();
    test_move_construction();
    test_move_assignment();
    cout << "Exiting main()\n\n";
    return 0;
}

/*
PRINTOUT

--- global tracer constructor

Running main()

Running fn_stack()
--- stack tracer constructor
Exiting fn_stack()

--- stack tracer destructor

Running fn_heap_creation()
--- heap tracer constructor
Exiting fn_heap_creation()


Running fn_heap_deletion()
--- heap tracer destructor
Exiting fn_heap_deletion()


Running stack_mystruct()
--- MyStruct member constructor
- Just made a MyStruct.
Exiting stack_mystruct()

- Just destroyed a MyStruct.
--- MyStruct member destructor

Running test_copy_construction()...
--- original construction (stack)
--- Currently within Tracer's copy constructor!
Exiting test_copy_construction()...

--- original destruction (stack)* this is the new one
--- original destruction (stack)

Running test_copy_assignment()...
--- original construction (stack)
--- will-be-copy-assigned-over construction (stack)
--- Currently within Tracer's copy assignment operator overload!
Exiting test_copy_assignment()...

--- original destruction (stack)* this is the new one
--- original destruction (stack)

Running test_move_construction()...                                             ***
                                                                                ***
Running return_tracer()...                                                      ***
created in return_tracer on stack, construction                                 ***
Exiting test_move_construction()...                                             ***
                                                                                ***
created in return_tracer on stack, destruction                                  ***

Running test_move_assignment()...
test_move_assignment original, construction

Running return_tracer()...
created in return_tracer on stack, construction
--- Currently within Tracer's move assignment operator overload!
created in return_tracer on stack, destruction
Exiting test_move_assignment()...

created in return_tracer on stack, destruction* this is the new one
Exiting main()

--- global tracer destructor
*/