//
// tlbones/src/bones.c
//

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "bones.h"
#include "arith.h"

static tl_var_t * reqpaths = NULL;

struct {
	char * name;
	tl_cfunction_t func;
} funcs[] = {
	{ "reqpath", tlm_reqpath },
	{ "require", tlm_require },
	{ "typeof",  tlm_typeof  },
	{ "exit",    tlm_exit    },
	{ "+",       tlm_add     },
	{ "-",       tlm_sub     },
	{ "*",       tlm_mul     },
	{ "/",       tlm_div     },
};

void tl_init_module(tl_var_t * env)
{
	int i;
	tl_var_t * key, * val;

	reqpaths = tl_nil;
	assert(env->type == TL_TABLE);

	for (i = 0; i < sizeof(funcs) / sizeof(*funcs); i++) {
		key = tl_create_str_slend(funcs[i].name);
		val = tl_create_cfunction(funcs[i].func);
		tl_store(&env->v.vtable, key, val);
		tl_release(key);
		tl_release(val);
	}

	for (i = 0; i < TL_MAX_TYPES; i++) {
		key = tl_create_str_slend(tl_type_names[i]);
		tl_store(&env->v.vtable, key, tl_types[i]);
		tl_release(key);
	}
}

tl_var_t * tlm_reqpath(tl_var_t * args, tl_var_t * env)
{
	if (args != tl_nil)
		reqpaths = args;
	return tl_assign(reqpaths);
}

tl_var_t * tlm_require(tl_var_t * args, tl_var_t * env)
{
	tl_var_t * paths;
	tl_string_t * r, * l;
	char * buf;

	while (args != tl_nil) {
		paths = reqpaths;
		assert(tl_car(args)->type == TL_STRING); //FIXME
		l = &tl_car(args)->v.vstring;

		while (paths != tl_nil) {
			assert(tl_car(paths)->type == TL_STRING); //FIXME
			r = &tl_car(paths)->v.vstring;

			buf = malloc(l->len + r->len + 1);

			memcpy(buf, l->str, l->len);
			memcpy(buf + l->len, r->str, r->len);
			buf[l->len + r->len] = 0;

			// FIXME
			assert(tl_require(buf, env));
			free(buf);

			paths = tl_cdr(paths);
		}

		args = tl_cdr(args);
	}

	return tl_nil;
}

tl_var_t * tlm_typeof(tl_var_t * args, tl_var_t * env)
{
	tl_var_t * ty;

	if (tl_car(args) == tl_nil) ty = tl_nil;
	else ty = tl_types[tl_car(args)->type];

	if (tl_cdr(args) == tl_nil) return ty;
	return tl_cons(ty, tlm_typeof(tl_cdr(args), env));
}

tl_var_t * tlm_exit(tl_var_t * args, tl_var_t * env)
{
	if (tl_car(args)->type == TL_INT)
		exit(tl_car(args)->v.vint);
	exit(0);
	return tl_nil;
}
