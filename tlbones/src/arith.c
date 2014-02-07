//
// tlbones/src/arith.c
//

#include <assert.h>
#include <tl/tl.h>
#include "arith.h"

typedef struct {
	tl_type_t type;
	union {
		tl_int_t i;
		tl_float_t f;
	} n;
} num_t;


#define ARITH_OP(NAME, OP, IDENT, ONE) \
static num_t NAME##h(tl_var_t * ls, int * one) \
{ \
	num_t a, b; \
	\
	if (ls->type == TL_LIST) { \
		one = 0; \
		a = NAME##h(tl_car(ls), one); \
		b = NAME##h(tl_cdr(ls), one); \
		assert(a.type == b.type); \
		\
		if (a.type == TL_INT) \
			a.n.i OP b.n.i; \
		else \
			a.n.f OP b.n.f; \
	} else { \
		a.type = ls->type; \
		\
		if (a.type == TL_INT) \
			a.n.i = ls->v.vint; \
		else if (a.type == TL_FLOAT) \
			a.n.f = ls->v.vfloat; \
		else \
			assert(0); \
	} \
	\
	return a; \
} \
\
tl_var_t * tlm_##NAME(tl_var_t * args, tl_var_t * env) \
{ \
	int one = 1; \
	num_t n; \
	\
	if (args == tl_nil) { \
		return tl_create_int(IDENT); \
	} else { \
		n = NAME##h(args, &one); \
		if (n.type == TL_INT) { \
			if (one) n.n.i = ONE n.n.i; \
			return tl_create_int(n.n.i); \
		} else { \
			if (one) n.n.f = ONE n.n.f; \
			return tl_create_float(n.n.f); \
		} \
	} \
}

ARITH_OP(add, +=, 0, +);
ARITH_OP(sub, -=, 0, -);
ARITH_OP(mul, *=, 1, +);
ARITH_OP(div, /=, 1, 1/);
