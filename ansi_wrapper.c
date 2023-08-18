#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define ESCAPE     "\x1B["
#define RESET      "0"
#define ENDLINE    "m"

#define CLOSER     "\x1B[0m"

#define FOREGROUND "3"
#define BACKGROUND "4"

#define BOLD       "1"
#define DIM        "2"
#define ITALIC     "3"
#define UNDERLINE  "4"
#define SLOW_BLINK "5"
#define FAST_BLINK "6"
#define INVERT     "7"

#define RED        "1"
#define GREEN      "2"
#define YELLOW     "3"
#define BLUE       "4"
#define MAGENTA    "5"
#define CYAN       "6"
#define WHITE      "7"

#define USAGE      "This program wraps strings with ansi codes to display them in terminal.\nFLAGS:\n	-b -> background color. requires an argument. example -> ./ansi_wrapper -b red \"SEWy sewy sewY\"\n	-c -> foreground color. requires an argument. example -> ./ansi_wrapper -c red \"SEWy sewy sewY\"\n	-g -> bold. no argument. example -> ./ansi_wrapper -g \"gas gas\"\n"


typedef struct {
	const char* name;
	char* value;
} Color;

char* get_color(int fore_back, char* color) {
	char* buffer = malloc(20);
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
	int  is_bold = 0;
	// char* optarg = "SI";

	while ((opt = getopt(argc, argv, "b:c:g")) != -1) {
		switch (opt) {
			case 'g':
				is_bold = 1;
				break;

			case 'b':
				value_bg_color = optarg;
				break;

			case 'c':
				value_fg_color = optarg;
				break;

			case ':':
				fprintf(stderr, "Usage: %s", argv[0]);
				exit(EXIT_FAILURE);

			case '?':
				fprintf(stderr, "Usage:\n%s", USAGE);
				exit(EXIT_FAILURE);
		}	
	}

	printf("%d", is_bold);

	// printf("%s", argv[argc-1]);

	char* out_buffer = malloc(100);	

	if (value_fg_color) {
		char* color = get_color(0, GREEN);
		printf("%s", value_fg_color);
		sprintf(out_buffer, "%s%s", color, argv[argc-1]);
	}

	if (value_bg_color) {
		char* color = get_color(1, MAGENTA);
		sprintf(out_buffer, "%s%s", color, argv[argc-1]);
	}

	if (is_bold) {
		sprintf(out_buffer, "%s%s%s%s", ESCAPE, BOLD, ENDLINE, out_buffer);
	}

	printf("%s%s%s%s", out_buffer, ESCAPE, RESET, ENDLINE);

	free(out_buffer);

	return 0;

}
