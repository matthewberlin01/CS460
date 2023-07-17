;;; Example 2 - Scheme to C++ translation

(define (sum L)
	(if (null? L)
		0
		(+ (car L) (sum (cdr L)))
	)
)

(define (main)
	(display "The sum of '(1 5 6) is ")
	(display (sum '(1 5 6)))
	(newline)
	(display "The sum of '() is ")
	(display (sum '()))
	(newline)
	(display "The sum of '(5 -1 3 7 10) is ")
	(display (sum '(5 -1 3 7 10)))
	(newline)
)

(main)
