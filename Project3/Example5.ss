;;; Example 5 - Scheme to C++ translation

(define (test a b)
	(display a) (display " < ")
	(display b) (display " : ")
	(if (< a b)
		#t
		#f
	)
)

(define (main)
	(display (test 7 -5))
	(newline)
	(display (test 3/4 4/5))
	(newline)
)

(main)
