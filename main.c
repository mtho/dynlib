#include <stdio.h>
#include <dlfcn.h>

int main() {
	double a,b,r, erg;
	void* handle;
	double *iptr, (*circle)(double), (*area)(double, double);

	typedef void(*func_t)(double a, double b);

	handle = dlopen("libcalc.so", RTLD_LAZY | RTLD_LOCAL);
	a = 3;
	b = 5;
	r = 2.5;
	erg = 0;

//	func_t fptr;
//	fptr = (func_t) dlsym(handle, "calcRectArea");
//	(*fptr)(a,b);
//	erg = calcRectArea(a,b);

	*(void **)(&circle) = dlsym(handle, "calcCircleArea");
	erg = (double) circle(r);

	*(void **)(&area) = dlsym(handle, "calcRectArea");
	erg = (double) area(a,b);

	*(void **)(&newton) = dlsym(handle, "calcNewton");
//	erg = (double) newton(

	printf("a = %lf\n", a);
	printf("b = %lf\n", b);
	printf("Ergebnis: %lf \n", erg);
}
