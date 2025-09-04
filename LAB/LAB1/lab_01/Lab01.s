.data
v1: .byte 2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2: .byte 4, 2, -13, 3, 9, 9, 7, 16, 4, 7
v3: .space 10
flag1: .space 1 ;if v3 is empty
flag2: .space 1 ;if v3 is ascendent
flag3: .space 1 ;if v3 is descendent
.text

MAIN:
	dadd R1, R0, R0 ;i=0
	dadd R2, R0, R0 ;k=0
	dadd R8, R0, R0
	daddi R6, R0, 10
	sb R0, flag1(R0)
	daddi R20, R0, 1
	sb R20, flag2(R0)
	sb R20, flag3(R0)
	
	
LOOP_EXT:
	beq R1, R6, CHECK
	dadd R4, R0, R0 ;j=0
	lb R3, v1(R1)   ;x=v1[i]
	daddi R1, R1, 1

LOOP_INT:
	beq R4, R6, LOOP_EXT
	lb R5, v2(R4)  ;y=v2[j]
	beq R3, R5, STORE
	daddi R4, R4, 1
	j LOOP_INT

STORE:
	sb R3, v3(R2)
	daddi R2, R2, 1
	daddi R8, R8, 1
	j LOOP_EXT
	
CHECK:
	bnez R8, CHECK2
	daddi R9, R0, 1
	sb R9, flag1(R0)
	
CHECK2: 
	dadd R1, R0, R0
	dadd R2, R0, R0
	daddi R10, R0, 1
	
LOOP2:
	daddi R15, R8, -1
	beq R2, R15, CHECK3
	lb R11, v3(R2)
	lb R12, v3(R10)
	slt R13, R11, R12
	beqz R13, SETFLAG2
	daddi R2, R2, 1
	daddi R10, R10, 1
	j LOOP2
	
SETFLAG2:
	sb R0, flag2(R0)

CHECK3:
	dadd R2, R0, R0
	daddi R14, R0, 1

LOOP3:
	daddi R16, R8, -1
	beq R2, R16, END
	lb R17, v3(R2)
	lb R18, v3(R14)
	slt R19, R18, R17
	beqz R19, SETFLAG3
	daddi R2, R2, 1
	daddi R14, R14, 1
	j LOOP3
	
SETFLAG3:
	sb R0, flag3(R0)
	
END:
	HALT