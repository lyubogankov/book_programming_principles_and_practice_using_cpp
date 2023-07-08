/*
9. Split the binary I/O program from §11.3.2 into two: 
    one program that converts an ordinary text file into binary 
    and one program that reads binary and converts it to text.
    
   Test these programs by comparing a text file with what you get by converting it to binary and back.
*/

#include <fstream>
#include <string>
#include <vector>
using namespace std;

// ------------------------------------------------------------------------------------------------
//      From std_lib_facilities.h
// ------------------------------------------------------------------------------------------------
template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
	// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}
// ------------------------------------------------------------------------------------------------

vector<int> text_to_binary(const string& input_txtfile) {
    ifstream ifs {input_txtfile, ios_base::binary};
    if (!ifs) throw runtime_error("Could not open file for input: " + input_txtfile);

    vector<int> v;
    for (int x; ifs.read(as_bytes(x), sizeof(int)); )
        v.push_back(x);

    return v; 
}

void binary_to_text(const vector<int>& bin, const string& output_binfile) {
    ofstream ofs {output_binfile, ios_base::binary}; // open in binary "stream mode"
    if (!ofs) throw runtime_error("Could not open file for output: " + output_binfile);

    for (int x : bin)
        ofs.write(as_bytes(x), sizeof(int));
}

int main() {
    vector<int> bin = text_to_binary("ex_09_input.txt");
    binary_to_text(bin, "ex_09_output.txt");
    return 0;
}