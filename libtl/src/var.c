//
// libtl/src/var.c
//

#include <assert.h>
#include <stdlib.h>
#include <tl/var.h>

tl_var_t * tl_nil;
tl_var_t * tl_types[TL_MAX_TYPES];

char * tl_nil_name;
char * tl_type_names[TL_MAX_TYPES] = {
	"nil",
	"type",
	"int",
	"float",
	"string",
	"list",
	"function",
	"table",
};

tl_var_t * tl__create(tl_type_t type)
{
	tl_var_t * v = malloc(sizeof(tl_var_t));
	v->refs = 1;
	v->flags = 0;
	v->type = type;
	return v;
}

void tl_init(void)
{
	int i;

	for (i = 0; i < TL_MAX_TYPES; i++) {
		tl_types[i] = tl__create(TL_TYPE);
		tl_types[i]->v.vtype = i;
		tl_types[i]->flags |= TL_STATIC;
	}

	tl_nil = tl_types[TL_NIL];
	tl_nil_name = tl_type_names[TL_NIL];
}

tl_var_t * tl_create_int(tl_int_t x)
{
	tl_var_t * t = tl__create(TL_INT);
	t->v.vint = x;
	return t;
}

tl_var_t * tl_create_string(void)
{
	tl_var_t * t = tl__create(TL_STRING);
	t->v.vstring.size = 0;
	t->v.vstring.len = 0;
	t->v.vstring.str = NULL;
	return t;
}

tl_var_t * tl_create_cfunction(tl_cfunction_t f)
{
	tl_var_t * t = tl__create(TL_FUNCTION);
	t->v.vfunction.isuser = 0;
	t->v.vfunction.u.builtin = f;
	return t;
}

tl_var_t * tl_create_table(void)
{
	tl_var_t * t = tl__create(TL_TABLE);
	t->v.vtable.root = NULL;
	return t;
}

tl_var_t * tl_create_str_xset(const char * str, size_t len)
{
	tl_var_t * v = tl_create_string();
	tl_str_xset(&v->v.vstring, str, len);
	return v;
}

tl_var_t * tl_create_str_lend(char * str, size_t len)
{
	tl_var_t * v = tl_create_string();
	tl_str_lend(&v->v.vstring, str, len);
	return v;
}

tl_var_t * tl_create_str_give(char * str, size_t len)
{
	tl_var_t * v = tl_create_string();
	tl_str_give(&v->v.vstring, str, len);
	return v;
}

tl_var_t * tl_assign(tl_var_t * v)
{
	v->refs++;
	return v;
}

static int release_entry(tl_var_t * k, tl_var_t * v, void * d)
{
	tl_release(k);
	tl_release(v);
	return 1;
}

void tl_release(tl_var_t * v)
{
	if (!--v->refs && ~v->flags & TL_STATIC) {
		switch (v->type) {
		case TL_STRING:
			tl_str_release(&v->v.vstring);
			break;
		case TL_LIST:
			tl_release(tl_car(v));
			tl_release(tl_cdr(v));
			break;
		case TL_TABLE:
			tl_traverse(&v->v.vtable, release_entry, NULL);
			break;
		case TL_FUNCTION:
			if (v->v.vfunction.isuser) {
				tl_release(v->v.vfunction.u.user.code);
				tl_release(v->v.vfunction.u.user.argls);
				tl_release(v->v.vfunction.u.user.env);
			}
			break;
		}

		free(v);
	}
}
