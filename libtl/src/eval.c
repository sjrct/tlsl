//
// libtl/src/eval.c
//

#include <assert.h>
#include <tl/tl.h>

static tl_var_t * value(tl_var_t * v, tl_var_t * env)
{
	if (v->flags & TL_SYMBOL) {
		assert(env->type == TL_TABLE);
		return tl_select(&env->v.vtable, v);
	} else {
		return v;
	}
}

static tl_var_t * statement(tl_var_t * st, tl_var_t * env)
{
	tl_var_t * v;
	tl_var_t * nxt;
	tl_var_t * lft;

	if (st->type == TL_LIST) {
		v = value(tl_car(st), env);

		if (v->type == TL_FUNCTION) {
			nxt = tl_cadr(st);

			if (nxt->type == TL_LIST || (nxt == tl_nil && tl_car(st) != tl_nil)) {
				nxt = statement(nxt, env);
				v = tl_call(&v->v.vfunction, nxt, env);
				tl_release(nxt);
				st = tl_cdr(st);
			}
		} else {
			v = statement(tl_car(st), env);
		}

		lft = statement(tl_cdr(st), env);
		return (lft == tl_nil) ? v : tl_cons(v, lft);
	} else {
		return tl_assign(value(st, env));
	}
}

tl_var_t * tl_eval(tl_var_t * code, tl_var_t * env)
{
	tl_var_t * ret;

	if (code->flags & TL_BLOCK) {
		assert(code != tl_nil);
		ret = tl_nil;

		do {
			tl_release(ret);
			ret = statement(tl_car(code), env);
			code = tl_cdr(code);
		} while (code != tl_nil);
	} else {
		ret = statement(code, env);
	}

	return ret;
}
