#include <stdio.h>
#include <dlfcn.h>

void logInFile(char* logevent) {
	FILE* datei;
	datei = fopen("logfile.txt", "a");
	fprintf(datei, "%s\n", logevent);
	fclose(datei);
	printf("%s\n", logevent);
}

char array[255];
char config[50];

void readConfig() {
	FILE* file;
	file = fopen("config.cfg", "r");
	fscanf(file, "%49c", config);
	fclose(file);
}

int main() {
	double a,b,r, erg;
	void* handle, *loghandle;
	void (*logger)(char*);
	double *iptr, (*circle)(double), (*area)(double, double), (*newton)(double);
	typedef void(*func_t)(double a, double b);

	
	loghandle = dlopen("logcalc.so", RTLD_LAZY | RTLD_LOCAL);
	handle = dlopen("libcalc.so", RTLD_LAZY | RTLD_LOCAL);
	a = 3;
	b = 5;
	r = 2.5;
	erg = 0;
	readConfig();

	// Logfunktion auswaehlen
	if(strcmp(config, "console")) {
		*(void **)(&logger) = dlsym(loghandle, "logToConsole");
	} else {
		*(void **)(&logger) = dlsym(loghandle, "logInFile");
	}

	// Circle handler
	*(void **)(&circle) = dlsym(handle, "calcCircleArea");
	erg = (double) circle(r);
	// Ergebnis loggen
	sprintf(array, "Ergebnis Circle: %.2lf", erg);
	(void) logger(array);

	*(void **)(&area) = dlsym(handle, "calcRectArea");
	erg = (double) area(a,b);
	// Ergebnis loggen
	sprintf(array, "Ergebnis Area: %.2lf", erg);
	(void) logger(array);

	// Aufruf newton()
	*(void **)(&newton) = dlsym(handle, "calcNewton");
	erg = (double) newton(r);
	// Ergebnis loggen
	sprintf(array, "Ergebnis Newton: %.2lf", erg);
	(void) logger(array);

	// Zu testzwecken
	logInFile(array);
}
