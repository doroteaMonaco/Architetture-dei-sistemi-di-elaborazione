.data
v1: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
v2: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
v3: .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32

v4: .space 256
v5: .space 256
v6: .space 256

m:  .space 64
a:  .space 64
b:  .double 5
.text

MAIN: 
	
	daddi R1, R0, 248
	daddi R2, R0, 3  ;contatore di iterazioni
	daddi R3, R0, 0 ;flag
	daddi R4, R0, 1 ;registro settato a 1
	sd R4, m(R0) ;metto 1 dentro m 
	daddi R8, R0, 8
	
LOOP:
	l.d F1, v1(R1)
	l.d F2, v2(R1)
	l.d F3, v3(R1)
	
	beqz R3, CHECK1
	daddi R2, R2, -1
	beqz R2, MULTIPLY
	
	
NEXT:
	l.d F8, a(R0)
	l.d F9, b(R0)
	mul.d F4, F1, F8
	sub.d F4, F4, F2
	s.d F4, v4(R1)
	
	div.d F5, F4, F3
	sub.d F5, F5, F9
	s.d F5, v5(R1)
	
	sub.d F6, F4, F1
	mul.d F6, F6, F5
	s.d F6, v6(R1)
	
	beqz R1, END
	daddi R1, R1, -8
	j LOOP


CHECK1:
	daddi R3, R3, 1
	beq R2, R4, MULTIPLY
	ld R6, m(R0)
	ddiv R5, R1, R8
	dmul R6, R6, R5
	mtc1 R6, F7
	cvt.d.l F7, F7
	mul.d F8, F1, F7
	cvt.l.d F8, F8
	mfc1 R4, F8
	s.d F8, a(R0)
	sd R4, m(R0)
	j NEXT
	
MULTIPLY:
	daddi R2, R0, 3
	ld R6, m(R0)
	ddiv R5, R1, R8
	dsllv R6, R6, R5
	mtc1 R6, F7
	cvt.d.l F7, F7
	div.d F8, F1, F7
	cvt.l.d F8, F8
	mfc1 R4, F8
	s.d F8, a(R0)
	sd R4, m(R0)
	j NEXT
	
	
END:
	nop
	HALT