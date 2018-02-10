(progn
  (define 'reduca (lambda '(f a l) '(cond (l (@ f (f a (car l)) (cdr l))) (t a))))
  (declare 'reduce (lambda '(f l) '(reduca f (f (car l) (car (cdr l))) (cdr (cdr l)))))
  (declare 'mapcar (lambda '(f l) '(cond (l (cons (f (car l)) (@ f (cdr l)))))))
  (declare 'desc (lambda '(o l) '(cond ((null o) l) ((eq (car o) 'a) (@ (cdr o) (car l))) ((eq (car o) 'd) (@ (cdr o) (cdr l))))))
  (declare 'nth (lambda '(n l) '(cond ((null l) nil) ((eq n 0) (car l)) (t (@ (- n 1) (cdr l))))))
  (declare 'randelt (lambda '(l) '(nth (random (length l)) l)))
  (declare 'range (lambda '(stt stp end) '(cond ((null ((cond ((> stp 0) >) ((< stp 0) <)) stt end)) (cons stt (@ (+ stt stp) stp end))))))
  (declare 'iota (lambda '(n) '(range 1 1 n)))
  (declare '! (lambda '(n) '(cond ((> n 1) (* n (@ (- n 1)))) (t 1))))
  (declare 'equal (lambda '(l1 l2) '(cond ((and (atom l1) (atom l2)) ((cond ((typep l1 'symbol) eq) (t =)) l1 l2))
					  ((and (atom (car l1)) (atom (car l2))) (and (eq (car l1) (car l2)) (@ (cdr l1) (cdr l2))))
					  ((null (or (atom l1) (atom l2))) (and (@ (car l1) (car l2)) (@ (cdr l1) (cdr l2)))))))
  t)
