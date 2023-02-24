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

**Approach 1** - handle within `statement()` -- needed to make buffer larger, so that I could buffer `{varname};`, which is two tokens (variable name, and a semicolon).  This was an involved change:



**Approach 2** - handle within `primary()`, within same case as variable lookup.  This is much cleaner!

## Open Questions


## Chapter Review Questions