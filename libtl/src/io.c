//
// libtl/src/io.c
//

#include <tl/io.h>
#include <tl/var.h>

static int print_kv(tl_var_t * k, tl_var_t * v, void * f0)
{
	FILE * f = f0;

	fputs("  ", f);
	tl_fprint(k, f);
	fputs(" = ", f);
	tl_fprint(v, f);
	fputs("\n", f);

	return 1;
}

static void fprinth(tl_var_t * v, FILE * f)
{
	int i;

	switch (v->type) {
	case TL_TYPE:
		fputs(tl_type_names[v->v.vtype], f);
		break;
	case TL_INT:
		fprintf(f, "%ld", v->v.vint);
		break;
	case TL_FLOAT:
		fprintf(f, "%g", v->v.vfloat);
		break;
	case TL_STRING:
		for (i = 0; i < v->v.vstring.len; i++)
			fputc(v->v.vstring.str[i], f);
		break;
	case TL_LIST:
		tl_fprint(tl_car(v), f);
		if (tl_cdr(v) != tl_nil) {
			fputc(' ', f);
			fprinth(tl_cdr(v), f);
		}
		break;
	case TL_TABLE:
		fputs("{\n", f);
		tl_traverse(&v->v.vtable, print_kv, f);
		fputs("}", f);
		break;
	default:
		fprintf(f, "[%s]", tl_type_names[v->type]);
		break;
	}
}

void tl_fprint(tl_var_t * v, FILE * f)
{
	if (v->type == TL_LIST) fputs("(", f);
	fprinth(v, f);
	if (v->type == TL_LIST) fputs(")", f);
}
