.data
v1: .byte 2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2: .byte 4, 2, -13, 3, 9, 9, 7, 16, 4, 7
.data
v1: .byte 2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2: .byte 4, 2, -13, 3, 9, 9, 7, 16, 4, 7
v3: .space 10
flag1: .space 1 ;if v3 is empty
flag2: .space 1 ;if v3 is ascendent
flag3: .space 1 ;if v3 is descendent
.text

MAIN:
	dadd R1, R0, R0  ;i=0
	dadd R3, R0, R0  ;k=0
	dadd R8, R0, R0  ;dimensione v3
	daddi R6, R0, 10 ;dimensione vettori
	sb R0, flag1(R0)
	daddi R10, R0, 1
	sb R10, flag2(R0)
	sb R10, flag3(R0)
	
	
LOOP_EXT:
	beq R1, R6, CHECK
	dadd R2, R0, R0 ;j=0
	lb R4, v1(R1)   ;x=v1[i]
	daddi R1, R1, 1

LOOP_INT:
	beq R2, R6, LOOP_EXT
	lb R5, v2(R2)  ;y=v2[j]
	beq R4, R5, STORE
	daddi R2, R2, 1
	j LOOP_INT

STORE:
	sb R4, v3(R3)
	daddi R2, R2, 1
	daddi R8, R8, 1
	j LOOP_EXT
	
CHECK:
	bnez R8, CHECK2
	sb R10, flag1(R0)
	
CHECK2: 
	dadd R1, R0, R0
	daddi R4, R0, 1
	
LOOP2:
	daddi R5, R8, -1
	beq R2, R5, CHECK3
	lb R6, v3(R2)
	lb R7, v3(R4)
	slt R9, R6, R7
	beqz R9, SETFLAG2
	daddi R2, R2, 1
	daddi R4, R4, 1
	j LOOP2
	
SETFLAG2:
	sb R0, flag2(R0)

CHECK3:
	dadd R2, R0, R0
	daddi R11, R0, 1

LOOP3:
	daddi R12, R8, -1
	beq R2, R12, END
	lb R13, v3(R2)
	lb R14, v3(R11)
	slt R5, R14, R13
	beqz R5, SETFLAG3
	daddi R2, R2, 1
	daddi R11, R11, 1
	j LOOP3
	
SETFLAG3:
	sb R0, flag3(R0)
	
END:
	HALT