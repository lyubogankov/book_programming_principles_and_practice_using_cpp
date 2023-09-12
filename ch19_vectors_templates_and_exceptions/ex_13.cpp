/*
13. Write a Tracer class where its constructor prints a string and its destructor prints a string. 
    Give the strings as constructor arguments. 
    
    Use it to see where RAII management objects will do their job 
    (i.e., experiment with Tracers as local objects, member objects, global objects, objects allocated by new, etc.). 
    
    Then add a copy constructor and a copy assignment so that you can use Tracer objects to see when copying is done.
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

int main() {
    cout << "\nRunning main()\n";
    fn_stack();
    Tracer* heap_tracer_ptr = fn_heap_creation();
    fn_heap_deletion(heap_tracer_ptr);
    stack_mystruct();
    cout << "Exiting main()\n\n";
    return 0;
}