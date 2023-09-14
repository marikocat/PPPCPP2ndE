/*
Binary-Inclusive-OR:
	Binary-Exclusive-OR
	Binary-Inclusive- OR "|" Binary-Exclusive-OR

Binary-Exclusive-OR:
	Binary-AND
	Binary-Exclusive-OR "^" Binary-AND

Binary-AND:
	Unary
	Binary-AND "&" Unary

Unary:
	Primary
	"!" Unary
	"~" Unary

Primary
	Number
	"(" Binary-Inclusive-OR ")" // grouping

Number
	integer
*/