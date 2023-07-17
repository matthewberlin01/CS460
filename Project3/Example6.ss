;;; Example 6 - Scheme to C++ translation

(define (average a b)
	b
	(/ (+ a b) 2)
)

(define (main)
	(display "The average of -7/4 and 5/3 is ")
	(display (average -7/4 5/3))
	(newline)
)

(main)
