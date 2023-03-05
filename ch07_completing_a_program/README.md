## Notes

Testing [Ch06 ex02-03 calculator program](../ch06_writing_a_program/exercise_02-03.cpp):

**Note** - all `errors` cause the program to quit.
| inputs              | result
| -                   | - |
| `1234567890123456;` | `=1.23457e+15`
| `q                ` | Program quits
| `1+2; q           ` | Prints `=3`, then quits
| `1+2+3+4+5+6+7+8  ` | No print char, nothing gets printed
| `1–2–3–4          ` |
| `1/0              ` |
| `!+2              ` | `error: primary expected`
| `(1+);            ` |
| `();              ` |
| `1+;              ` |
| `+1               ` |
| `1++;             ` |
| `1++2;            ` |
| `–2;              ` |
| `–2;;;;           ` |
| `1+q              ` |
| `1/0;             ` | `error: divide by zero`
| `(1+3;            ` | `error: ')' expected`
| `1*2/3%4+5–6;     ` | `error: bad token`
| `'a';             ` |
| `;;;              ` | `=0`  (multi-line output)
|                     | `=0`
|                     | `=0`


### `drill.cpp` -- variable re-assignment

**Approach 1** - handle within `statement()` -- needed to make buffer larger, so that I could buffer `{varname};`, which is two tokens (variable name, and a semicolon).  This was an involved change: touched `statement()`, `Token_stream.buffer`, `Token_stream::get()`, `Token_stream::ignore()`.

**Approach 2** - handle entirely within `primary()`, within same case as variable lookup.  This is much cleaner!

```diff
--- a/ch07_completing_a_program/drill.cpp       // (Approach 1)
+++ b/ch07_completing_a_program/drill.cpp       // (Approach 2)
 
 class Token_stream {
-	vector<Token> buffer;
+	bool full;
+	Token buffer;
 public:
-	Token_stream() :buffer({}) { }
+	Token_stream() :full(0), buffer(0) { }
+
 	Token get();
-	void unget(Token t) { buffer.push_back(t); }
+	void unget(Token t) { buffer = t; full = true; }
+
 	void ignore(char);
 };
 
 
 Token Token_stream::get()
 {
-	if (buffer.size() > 0) {
-       Token t_buffered = buffer.back();   // make copy of last element in buffer
-		buffer.pop_back();                  // delete last element from buffer
-		return t_buffered;
-	}
+	if (full) { full = false; return buffer; }
 	char ch;
 	cin >> ch;
 	switch (ch) {

@@ -224,12 +214,11 @@ Token Token_stream::get()
 
 void Token_stream::ignore(char c)
 {
-	while (buffer.size() > 0) {
-		// Assuming we're trying to ignore a ';' (or other token whose kind is itself)
-		// as opposed to a specific number or letter, which isn't encoded in Token.kind
-		if (buffer.back().kind == c) return;
-		buffer.pop_back();
+	if (full && c == buffer.kind) {
+		full = false;
+		return;
 	}
+	full = false;
 
 	char ch;
 	while (cin >> ch)

@@ -293,8 +282,20 @@ double primary()
         return primary();
 	case number:
 		return t.value;
-	case name:
-		return get_value(t.name);
+	// updated to perform get OR set
+	case name: {
+		string varname = t.name;
+		Token t2 = ts.get();
+		// variable lookup
+		if (t2.kind != '=') {
+			ts.unget(t2);
+			return get_value(varname);
+		}
+		// variable re-assignment
+		double d = expression();
+		set_value(varname, d);
+		return d;
+	}
 	default:
 		cin.unget();
 		error("primary expected");

@@ -367,22 +368,6 @@ double statement()
 	switch (t.kind) {
 	case let:
 		return declaration();
-	// L: new!  The function for setting values exists, but it's never used!
-	case name: {
-		string varname = t.name;
-		if (!is_declared(varname)) error(varname, " not declared");
-		Token t2 = ts.get();
-		if (t2.kind != '=') {
-			ts.unget(t2);           // putting onto stack first, will be processed last (LIFO)
-			ts.unget(t);            // putting onto stack last for first processing
-			return expression();
-		}
-		double d = expression();
-		set_value(varname, d);
-		return d;
-	}
 	default:
 		ts.unget(t);
 		return expression();
```

## Open Questions


## Chapter Review Questions

1. *What is the purpose of working on the program after the first version works? Give a list of reasons.*




2. *Why does 1+2; q typed into the calculator not quit after it receives an error?*




3. *Why did we choose to make a constant character called number?*

	Clearer intent in code - more readable.  '8' does not carry any special meaning, and every time it was used a comment was written to explain what it signified.  The variable 'number' is well named - it explains its purpose and therefore does not require a comment.


4. *We split main() into two separate functions. What does the new function do and why did we split main()?*

	It was doing two things: providing program entry point, try/catch fatal errors; calculator REPL


5. *Why do we split code into multiple functions? State principles.*

	So that each function handles a single logical operation.  This makes it more re-usable and increases the probability the entire function will fit on the screen (easier to read).


6. *What is the purpose of commenting and how should it be done?*

	To express the *intent* of the code.


7. *What does narrow_cast do?*

	From `std_lib_facilities.h`:
	```C++
	template<class R, class A> R narrow_cast(const A& a) {
		R r = R(a);
		if (A(r) != a) error(string("info loss"));
		return r;
	}
	```
	Tries to cast variable of class A to class R, and raises error if conversion lost information.
	Used for double -> int conversion.


8. *What is the use of symbolic constants?*

	If talking about within the program - see #3.
	If talking about within the calculator, to make it more usable.  Shortcuts for common constants, especially irrational ones, save time and can make expressions more readable.


9. *Why do we care about code layout?*




10. *How do we handle % (remainder) of floating-point numbers?*

	We ended up going with `fmod` -- _a % b = a - b*int(a/b)_, instead of casting floats -> int.


11. *What does is_declared() do and how does it work?*

	Checks whether a variable is contained within our symbol table vector.  Loops through all elements within the vector.  If we have a match, returns true (it is contained within the vector, and is therefore a declared variable) else false.


12. *The input representation for let is more than one character. How is it accepted as a single token in the modified code?*

	Within the default case of `Token_stream::get()`, read `cin` and build up a string while certain characters are being input.  We then check whether our built-up string matches any known tokens (ex: "let").

	```C++
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			if (s == "pow") return Token(_pow);
			if (s == "sqrt") return Token(_sqrt);
			if (s == quit_full) return Token(quit);
			if (s == help_full) return Token(help);
			if (s == var_declaration) return Token(let);
			if (s == const_declaration) return Token(constant);
			return Token(name, s);
	```


13. *What are the rules for what names can and cannot be in the calculator program?*

	Expressed as grammar, in (Python) regular-expression syntax:
	```
	Variable
		[a-zA-Z][a-zA-Z0-9]*  // (from drill)
		[a-zA-Z]\w*			  // (#1 -- allow underscores )
	```


14. *Why is it a good idea to build a program incrementally?*




15. *When do you start to test?*




16. *When do you retest?*




17. *How do you decide what should be a separate function?*




18. *How do you choose names for variables and functions? List possible reasons.*




19. *Why do you add comments?*




20. *What should be in comments and what should not?*




21. *When do we consider a program finished?*

