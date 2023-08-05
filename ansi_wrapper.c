#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	int  opt;
	char *value_color = NULL;
	char *value_bg_color = NULL;

	char *escape = "\x1b";

	while ((opt = getopt(argc, argv, "b:c:")) != -1) {
		switch (opt) {
			case 'b':
				value_bg_color = optarg;
				break;
			case 'c':
				value_color = optarg;
				break;
			case '?':
				fprintf(stderr, "Usage: %s", argv[0]);
				exit(EXIT_FAILURE);

		}	
	}

	if (value_color) {
		printf("\v%s\n", value_color);
	}

	return 0;

}
