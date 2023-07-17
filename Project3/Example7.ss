;;; Example 7 - Scheme to C++ translation

(define (main)
	(if (and #t (not #f))
		(display '(#t and (not #f)))
		(newline)
	)
)

(main)
