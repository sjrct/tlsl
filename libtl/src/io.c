//
// libtl/src/io.c
//

#include <tl/io.h>
#include <tl/var.h>

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
		if (tl_cdr(v) == tl_nil) {
			fputc(' ', f);
			fprinth(tl_cdr(v), f);
		}
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
