# INTP

## A tiny concatenative programming language

INTP is a very small, minimal programming language. It's stack-based and similar to Forth, though actually heavily influenced by the more mathematically pure language [Joy](https://en.wikipedia.org/wiki/Joy_%28programming_language%29).

I wrote this in 2006 after discovering Joy, thinking it was really cool, and developing a yen to write a tiny programming language interpreter. Sadly I went a bit overboard by defining one-letter abbreviations for many C keywords, as you can see in abbr.h:

```c
#define s static
#define i int
#define v void
#define r return
/* ... etc ... */
```

The abbreviations helped keep my code small (just 12KB of C code) and made writing the interpreter fun because it felt like a different language, but of course they needlessly obfuscate the code. This is not a recommended way to write C!

Here is a short test program in INTP:

```
double
	DUP CONCAT
	%
main
	"Hello" double double PRINT
	%
```

As in Forth, routines in INTP are called “words”. This code defines two words, `double` and `main`. When the program is run, `main` runs. It pushes the string “Hello” onto the stack, calls `double` twice, and then prints the string on top of the stack to standard output. Each time `double` is called, it duplicates the thing on top of the stack, then pops the two strings at the top of the stack, concatenates them and pushes the result back onto the stack. In the end, this example prints “Hello” four times.

INTP has no explicit variables and everything operates directly on the stack. Pretty cool, huh? There's a wiki out there with a great [overview of how concatenative languages work](http://concatenative.org/wiki/view/Concatenative%20language).

You can include another source file as a library by pushing its filename on the stack and calling the `INCL` word, e.g. `"lib.intp" INCL`. See substr.intp for an example using this.

There might be a big honking bug in the interpreter because when I run recursion.intp it's behaving really weird. (I've barely touched this code at all since I wrote it.)

As a language INTP is kind of cool but not original, because everything cool about it came from Joy. It's basically a second-rate Joy clone.