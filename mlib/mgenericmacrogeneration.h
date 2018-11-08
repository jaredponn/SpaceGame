// clang-format on

// -----------------------------------------
//    GENERATING GENERIC FUNCTIONS FROM XMACROS
// -----------------------------------------

/* This section serves to be a short guide on how to generate generic functions
 * with the _Generic keyword of C11 with macros


 * Let's say we have the following:

#define XMACRO  \
	X_g(int)  \
	X_g(char) \
	X_g(deffed)
// notice we need to postfix the X() macro with a unique identifier

// we define the X macro to convert the expression to a list. Note: when
converting the x xmacro to generic expressions, it's important to DO THIS LAST
AFTER DEFINING EVERYTHING because from this point forward in the program, the X
macro must expand into a list of arguements

#define X_g(val) val,

// this is the function that will be mapped over the X macro list
#define F(val)val : val##func,

// this creatse the function
#define genericFunction(val) _Generic((val),REMOVE_EXTRA_COMMA(DEFER1(MAP)(F,
XMACRO))) (val)

typedef struct deffed {
	int a;
} deffed;

void intfunc(int a) { printf("INT FUNC %i\n", a); }

void charfunc(char a) { printf("CHAR FUNC %c\n", a); }

void deffedfunc(deffed a) { printf("deffed FUNC %i\n", a.a); }

void defaultfunc(float a) { printf("DEFAULT FUNC %f\n", a); }


int main() {
	int a = 1;
	char b = 'a';
	deffed c = {2};
	float d = 1.2f;
	genericFunction(a);
	genericFunction(b);
	genericFunction((deffed){2});
	// genericFunction(d); will cause compiel error
}

 * Notes: with this method, if it is fed a type not accounted for in the Xmacro,
the program will fail to compile
*/
