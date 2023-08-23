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

#define USAGE      "This program wraps strings with ansi codes to display them in terminal.\nFlags:\n	-b -> background color. requires an argument. example -> ./ansi_wrapper -b red \"SEWy sewy sewY\"\n	-c -> foreground color. requires an argument. example -> ./ansi_wrapper -c red \"SEWy sewy sewY\"\n	-g -> bold. no argument. example -> ./ansi_wrapper -g \"gas gas\"\n	-n -> newline. no argument. example -> ./ansi_wrapper -n \"gas gas\"\n"

typedef struct {
	const char* name;
	char* value;
} Color;

char* get_color(const Color* color_map, int fore_back, char* color) {
	char* color_value = malloc(2);
	for (int i = 0; color_map[i].name != NULL; i++) {
		if (strcmp(color_map[i].name, color) == 0) {
			color_value = color_map[i].value;
		}
	}
	char* buffer = malloc(20);
	// 0 fore, 1 back
	if (fore_back == 0) {
		sprintf(buffer, "%s%s%s%s", ESCAPE, FOREGROUND, color_value, ENDLINE);
	}
	if (fore_back == 1) {
		sprintf(buffer, "%s%s%s%s", ESCAPE, BACKGROUND, color_value, ENDLINE);
	}
	return buffer;
}

int main(int argc, char *argv[]) {
	const Color color_map[] = {
		{"red",     RED},
		{"green",   GREEN},
		{"yellow",  YELLOW},
		{"blue",    BLUE},
		{"magenta", MAGENTA},
		{"cyan",    CYAN}, 
		{"white",   WHITE}, 
		{NULL, NULL}
	}; 

	// printf("%s\n", color_map[0].name);
	// printf("%s\n", color_map[0].value);

	int  opt;
	char *value_fg_color = NULL;
	char *value_bg_color = NULL;
	int  is_bold   = 0;
	int  newline   = 0;
	int  underline = 0;
	// char* optarg = "SI";

	while ((opt = getopt(argc, argv, "b:c:gnu")) != -1) {
		switch (opt) {
			case 'u':
				underline = 1;
				break;
				
			case 'g':
				is_bold = 1;
				break;
			
			case 'n':
				newline = 1;
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

	// printf("%d", is_bold);
	// printf("%s", argv[argc-1]);

	char* out_buffer = malloc(100);	

	if (value_fg_color) {
		char* color = get_color(color_map, 0, value_fg_color);
		// printf("%s", value_fg_color);
		strcat(out_buffer, color);
		free(color);
	}

	if (value_bg_color) {
		char* color = get_color(color_map, 1, value_bg_color);
		strcat(out_buffer, color);
		free(color);
	}

	if (is_bold) {
		char* bold = malloc(20);
		sprintf(bold, "%s%s%s", ESCAPE, BOLD, ENDLINE);
		strcat(out_buffer,  bold);
		free(bold);
	}

	if (underline) {
		char* _underline = malloc(20);
		sprintf(_underline, "%s%s%s", ESCAPE, UNDERLINE, ENDLINE);
		strcat(out_buffer,  _underline);
		free(_underline);

	}

	if (newline) {
		printf("%s%s%s\n", out_buffer, argv[argc-1], CLOSER);
		free(out_buffer);
		return 0;
		
	}

	printf("%s%s%s", out_buffer, argv[argc-1], CLOSER);
	free(out_buffer);
	return 0;

}
