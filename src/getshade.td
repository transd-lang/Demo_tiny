#lang transd

public module Export: {
	x: Double(),
	y: Double()
}

tst: {
	import: "Export",
	getShade: (λ (with t (- (pow x 2) y) 
							(if (and (<= t 1.0)(> t -1.0))
								1 0)))
}
