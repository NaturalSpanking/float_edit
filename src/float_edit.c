/*
 ============================================================================
 Name        : float_edit.c
 Author      : cma
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
	float value;
	uint32_t qw;
	struct {
		uint32_t fraction :23;
		uint32_t exponent :8; // Ёффективный пор€док (2 в этой степени) определ€етс€ как E-127
		uint32_t sign :1;
	};
} TFloatFields;

static void print_cursor(int cp);
static void update_float(float* fl, int cp, int direction);

int main(void) {
	float f = 1.23406e1;
	int curpos = 0;
	_set_output_format(1); // 2 символа дл€ пор€дка
	fflush(stdin);
	printf("%+-.3E\n", f);
	print_cursor(curpos);
	for (;;) {
		fflush(stdout);
		char c = getchar();
		if (c == 'q')
			break;
		switch (c) {
		case 'l':
			curpos++;
			break;
		case 'r':
			curpos--;
			break;
		case 'u':
			update_float(&f, curpos, 1);
			break;
		case 'd':
			update_float(&f, curpos, -1);
			break;
		case '\n':
			continue;
		}
		printf("%+-.3E\n", f);
		print_cursor(curpos);
	}
	//system("cls"); не работает
	return EXIT_SUCCESS;
}

void update_float(float* fl, int cp, int direction) {
//	*fl += direction * 5.0;
//	TFloatFields tmp_f;
//	tmp_f.value = *fl;
//	int temp_e = tmp_f.exponent - 127;
	switch (cp) {
	case 0:
		//temp_e += direction * 3;
		*fl *= direction==1?10:0.1;
		break;
	case 1:
//		temp_e += direction * 10;
		*fl *= direction==1?10000000000:0.0000000001;
		break;

	}
//	tmp_f.exponent = temp_e +127;
//	*fl = tmp_f.value;
}

void print_cursor(int cp) {
	int i;
	for (i = 0; i < 9 - cp; i++) {
		putchar(' ');
	}
	putchar('^');
	putchar('\n');
}
