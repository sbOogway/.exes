#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ESCAPE     "\x1B["
#define RESET      "0"
#define ENDLINE    "m"

#define CLOSER     "\x1B[0m"

#define FOREGROUND "3"
#define BACKGROUND "4"

#define RED        "1"
#define GREEN      "2"
#define YELLOW     "3"
#define BLUE       "4"
#define MAGENTA    "5"
#define CYAN       "6"
#define WHITE      "7"


typedef struct {
	const char* name;
	char* value;
} Color;

char* get_color(int fore_back, char* color) {
	char* buffer;
	// 0 fore, 1 back
	if (fore_back == 0) {
		sprintf(buffer, "%s%s%s%s", ESCAPE, FOREGROUND, color, ENDLINE);
	}
	if (fore_back == 1) {
		sprintf(buffer, "%s%s%s%s", ESCAPE, BACKGROUND, color, ENDLINE);
	}
	return buffer;

}


int main(int argc, char *argv[]) {
	int  opt;
	char *value_fg_color = NULL;
	char *value_bg_color = NULL;
	char* optarg = "SI";

	while ((opt = getopt(argc, argv, "b:c:")) != -1) {
		switch (opt) {
			case 'b':
				value_bg_color = optarg;
				break;
			case 'c':
				value_fg_color = optarg;
				break;
			case '?':
				fprintf(stderr, "Usage: %s", argv[0]);
				exit(EXIT_FAILURE);
		}	
	}

	char* out_buffer;

	if (value_fg_color) {
		char* color = get_color(0, RED);
		sprintf(out_buffer, "%s%s", color, argv[argc-1]);
	}

	if (value_bg_color) {
		char* color = get_color(1, GREEN);
		sprintf(out_buffer, "%s%s", color, argv[argc-1]);
	}

	printf("%s", out_buffer);
	return 0;

}
