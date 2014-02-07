//
// tli/src/main.c
//

#include <stdio.h>
#include <assert.h>
#include <tl/io.h>
#include <tl/tl.h>

#define MAX_LINE 256
/*
static void dump(tl_var_t *);

static void dump_str(tl_string_t * str)
{
	int i;
	for (i = 0; i < str->len; i++)
		putchar(str->str[i]);
}

static void dump_h(tl_var_t * v)
{
	switch (v->type) {
	case TL_NIL:
		printf("!nil!");
		break;
	case TL_TYPE:
		printf("<%s>", tl_type_names[v->v.vtype]);
		break;
	case TL_INT:
		printf("%ld", v->v.vint);
		break;
	case TL_FLOAT:
		printf("%g", v->v.vfloat);
		break;
	case TL_STRING:
		dump_str(&v->v.vstring);
		break;
	case TL_LIST:
		dump(tl_car(v));
		if (tl_cdr(v) != tl_nil) {
			fputs(" ", stdout);
			dump_h(tl_cdr(v));
		}
		break;
	case TL_FUNCTION:
		printf("[function]");
		break;
	default:
		printf("????");
	}
}

static void dump(tl_var_t * v)
{
	if (v->type == TL_LIST) fputs("(", stdout);
	dump_h(v);
	if (v->type == TL_LIST) fputs(")", stdout);
}
*/
static void interactive(tl_var_t * env)
{
	char line[MAX_LINE];
	tl_var_t * pls;
	tl_var_t * ret;

	for (;;) {
		fputs("> ", stdout);
		fgets(line, MAX_LINE, stdin);

		pls = tl_parse(line);
		ret = tl_eval(pls, env);

		tl_fprint(ret, stdout);
		puts("");

		tl_release(pls);
		tl_release(ret);
	}
}

int main(int argc, char ** argv)
{
	tl_init();

	tl_var_t * env = tl_create_table();
	assert(tl_require("../tlbones/tlbones.so", env)); // FIXME

	interactive(env);

	return 0;
}
