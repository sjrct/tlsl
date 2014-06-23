//
// tli/src/main.c
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <tl/io.h>
#include <tl/tl.h>

#define MAX_LINE 256

static int parse_only = 0;

static void interactive(tl_var_t * env)
{
	char line[MAX_LINE];
	tl_var_t * pls;
	tl_var_t * ret;

	for (;;) {
		fputs("> ", stdout);
		fgets(line, MAX_LINE, stdin);

		pls = tl_parse(line);
		ret = parse_only ? pls : tl_eval(pls, env);

		tl_fprint(ret, stdout);
		puts("");

		if (!parse_only) tl_release(pls);
		tl_release(ret);
	}
}

static void print_help(void)
{
	puts(
		"\n"
		"tli [options]\n"
		"\n"
		"Options:\n"
		"    -h\n"
		"        Print this helpful information.\n"
		"    -p\n"
		"        Enable parse only mode (typically for debugging purposes).\n"
	);
}

int main(int argc, char ** argv)
{
	int i;
	tl_var_t * env;

	tl_init();
	env = tl_create_table();

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
				print_help();
				return 0;
			case 'p':
				parse_only = 1;
				break;
			default:
				fprintf(stderr, "Error: Unknown switch '%s'.\n", argv[i]);
				fputs("Use 'tli -h' for help.\n", stderr);
				return EXIT_FAILURE;
			}
		} else {
			fprintf(stderr, "Error: Stray argument '%s'.\n", argv[i]);
			fputs("Use 'tli -h' for help.\n", stderr);
			return EXIT_FAILURE;
		}
	}

	assert(tl_require("../tlbones/tlbones.so", env)); // FIXME

	interactive(env);

	return 0;
}
