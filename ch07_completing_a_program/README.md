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
--- a/ch07_completing_a_program/drill.cpp       // (approach 1)
+++ b/ch07_completing_a_program/drill.cpp       // (approach 2)
 
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