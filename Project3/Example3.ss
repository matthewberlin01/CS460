;;; Example 3 - Scheme to C++ translation

(define (sum L)
	(if (null? L)
		0
		(+ (car L) (sum (cdr L)))
	)
)

(define (count L)
	(if (null? L)
		0
		(+ 1 (count (cdr L)))
	)
)

(define (average L)
	(let ((total (sum L)) (num (count L)))
		(if (= 0 num)
			"Average cannot be calculated"
			(/ total num)
		)
	)
)

(define (main)
	(display "The average of '(1 5 6) is ")
	(display (average '(1 5 6)))
	(newline)
	(display "The average of '() is ")
	(display (average '()))
	(newline)
	(display "The average of '(5 -1 3 7 10) is ")
	(display (average '(5 -1 3 7 10)))
	(newline)
)

(main)
