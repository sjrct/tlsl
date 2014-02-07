//
// libtl/src/list.c
//

#include <tl/var.h>

tl_var_t * tl_car(tl_var_t * ls)
{
	if (ls->type != TL_LIST) return ls;
	return ls->v.vlist.car;
}

tl_var_t * tl_cdr(tl_var_t * ls)
{
	if (ls->type != TL_LIST) return tl_nil;
	return ls->v.vlist.cdr;
}

const tl_var_t * tl_const_car(const tl_var_t * ls)
{
	if (ls->type != TL_LIST) return ls;
	return ls->v.vlist.car;
}

const tl_var_t * tl_const_cdr(const tl_var_t * ls)
{
	if (ls->type != TL_LIST) return tl_nil;
	return ls->v.vlist.cdr;
}

tl_var_t * tl_cons(tl_var_t * head, tl_var_t * tail)
{
	tl_var_t * ls = tl__create(TL_LIST);

	ls->v.vlist.car = head;
	ls->v.vlist.cdr = tail;

	return ls;
}
