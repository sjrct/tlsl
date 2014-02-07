//
// include/tl/list.h
//

typedef struct tl_list tl_list_t;

#ifndef _TL_LIST_H_
#define _TL_LIST_H_

typedef struct tl_var tl_var_t;

struct tl_list {
	tl_var_t * car;
	tl_var_t * cdr;
};

tl_var_t * tl_car(tl_var_t *);
tl_var_t * tl_cdr(tl_var_t *);
const tl_var_t * tl_const_car(const tl_var_t *);
const tl_var_t * tl_const_cdr(const tl_var_t *);

tl_var_t * tl_cons(tl_var_t *, tl_var_t *);

#define tl_cadr(X) tl_car(tl_cdr(X))
#define tl_cddr(X) tl_cdr(tl_cdr(X))

#endif
