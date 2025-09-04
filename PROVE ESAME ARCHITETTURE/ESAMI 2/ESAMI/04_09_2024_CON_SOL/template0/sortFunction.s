		
			;r0 addr vect
			;r1 N
			;r2 dest vett
			AREA data,DATA,READWRITE
N			EQU 12
tempvect 	SPACE 4*N
;resultvect	SPACE 4*N

			AREA sort,CODE,READONLY
sortfunct	PROC
			EXPORT sortfunct
			push{r4-r8,r10-r11,lr}
			mov r4,r1
			mov r6,#0
			ldr r7,=tempvect
			;ldr r8,=resultvect
			mov r8,r2
loop1
			ldr r5,[r0,r6,lsl #2]
			str r5,[r7,r6,lsl #2]
			add r6,r6,#1
			adds r4,r4,#-1
			bne loop1
		
		;r4 index for loop
		;r6 index for vector final
			mov r4,r1
			mov r6,#0
loop2	
			;r9 index for vector temp
			;r10 index for loop2
			;r0 index max
			;r1 value max
			;r5 current value
			;r7 temp vect
			;r8 final vect
			mov r9,#0
			mov r10,r1
			mov r0,#-1
			mov r12,#0x80000000
			; CRESC 0x7FFFFFFF
loop3
			ldr r5,[r7,r9,lsl #2]
			cmp r12,r5
			;cresc gt
			movlt r12,r5
			movlt r0,r9
			add r9,r9,#1
			adds r10,r10,#-1
			bne loop3
		
			str r12,[r8,r6,lsl #2]
			mov r12,#0x80000000
			; CRESC 0x7FFFFFFF
			str r12,[r7,r0,lsl #2]
		
			add r6,r6,#1
			adds r4,r4,#-1
			bne loop2
		
		
			pop{r4-r8,r10-r11,pc}
			ENDP
			
			END