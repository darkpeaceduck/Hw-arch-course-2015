#define VGA_START_ADDRESS 0xb8000
#define COLUMNS 80
#define LINES 24
#define SCREEN_SIZE COLUMNS * LINES
#define PIXEL_MODE 15

static char * const video = (char *) (VGA_START_ADDRESS);
static int xpos, ypos;

void cls() {
	int i = 0;
	for (i = 0; i < 2 * SCREEN_SIZE; i++) {
		video[i] = 0;
	}
	xpos = 0;
	ypos = 0;
}

void itoa(char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x')
		divisor = 16;

	/* Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

void putchar(int c) {
	if (c == '\n' || c == '\r') {
		newline: xpos = 0;
		ypos++;
		if (ypos >= LINES)
			ypos = 0;
		return;
	}

	*(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = PIXEL_MODE;

	xpos++;
	if (xpos >= COLUMNS)
		goto newline;
}

void printf(const char *format, ...) {
	char **arg = (char **) &format;
	int c;
	char buf[20];

	arg++;
	int i;
	while ((c = *format++) != 0) {
		if (c != '%')
			putchar(c);
		else {
			char *p;

			c = *format++;
			switch (c) {
			case 'd':
			case 'u':
			case 'x':
				itoa(buf, c, *((int *) arg++));
				p = buf;
				goto string;
				break;
			case 'o':
				itoa(buf, 'x', *((int *) (arg+1)));
				int start = 0;
				for(i = 0; i < 16; i++){
					if(buf[i] == 0){
						start = i;
						break;
					}
				}
				itoa(buf + start, 'x', *((int *) arg));
				int end = 0;
				for(i = start; i <= start + 8; i++){
					if(buf[i] == 0){
						end = i;
						break;
					}
				}
				end--;
				buf[start + 8] = '\0';
				for(i = start + 7; i >= start; i--){
					buf[i] = buf[end - (start + 7 - i)];
				}
				for(i = start; i < (start + 8 - end); i++){
					buf[i] = '0';
				}
				arg+= 2;
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";

				string: while (*p)
					putchar(*p++);
				break;

			default:
				putchar(*((int *) arg++));
				break;
			}
		}
	}
}

int strcomp(const char *f, const char *s, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (f[i] != s[i]) {
			return 0;
		}
	}
	return 1;
}
