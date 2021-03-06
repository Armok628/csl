#include "rpn.h"
obj_t *rpn(obj_t *form)
{
	if (form->type!=CELL)
		return cons(form,NIL);
	if (car(form)==QUOTE)
		return form;
	if (car(form)==PROGN)
		return t_progn(form);
	if (car(form)==COND)
		return t_cond(form);
	push(NULL);
	push(cons(&ARGS,NIL));
	for (obj_t *o=cdr(form);o!=NIL;o=cdr(o))
		push(rpn(car(o)));
	push(rpn(car(form)));
	push(cons(&CALL,NIL));
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop(); // Drop NULL
	r->refs--;
	return r;
}
obj_t *rpnd(obj_t *form)
{
	obj_t *r=rpn(form);
	dec_rc(form);
	return r;
}
obj_t *t_progn(obj_t *form) // "Translate progn"
{
	push(NULL);
	for (obj_t *f=cdr(form);f!=NIL;f=cdr(f)) {
		push(rpn(car(f)));
		if (cdr(f)!=NIL)
			push(cons(&DROP,NIL));
	}
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop();
	r->refs--;
	return r;
}
obj_t *t_cond(obj_t *form) // "Translate cond"
{
	push(NULL);
	push(cons(&COND_BEGIN,NIL));
	for (obj_t *f=cdr(form);f!=NIL;f=cdr(f)) {
		push(rpn(car(car(f))));
		push(cons(&COND_DO,NIL));
		push(rpn(car(cdr(car(f)))));
		push(cons(&COND_DONE,NIL));
	}
	push(cons(&COND_END,NIL));
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop();
	r->refs--;
	return r;
}
