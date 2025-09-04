;r0-r3 are the argument and scratch registers; r0-r1 are also the result registers
;r4-r8 are callee-save registers
;r9 might be a callee-save register or not (on some variants of AAPCS it is a special register)
;r10-r11 are callee-save registers
;r12-r15 are special registers




VETT RN r0
dim  RN r1
flag RN r2

media RN r3
i	RN r4
vett_i RN r5
counter RN r6
flag_value RN r8

		AREA functs,CODE,READONLY
avg_vett	PROC
		EXPORT avg_vett
			
		push{r4-r8,r10-r11,lr}
		
		mov media, #0
		mov i, #0
loop_calcolo_media
		ldr vett_i, [VETT, i, lsl #2]

		add media, media, vett_i
	
		add i, i, #1
		cmp i, dim
		bne loop_calcolo_media
		
		udiv media, media, dim
		
		
		mov counter, #0
		mov i, #0
loop_counter
		ldr vett_i, [VETT, i, lsl #2]
		
		cmp vett_i, media
		addhi counter, counter, #1

		add i, i, #1
		cmp i, dim
		bne loop_counter
		
		mov r0, counter			; restituire numero di valori sopra la media
		
		lsrs r10, counter, #1  ; guardo ultimo bit per capire se pari o dispari, vedendo il flag carry
		movcs flag_value, #0   ; uso conditional instruction
		movcc flag_value, #1   ; flag=1 se pari, flag=0 se dispari
		
		strb flag_value, [flag]
		
		pop{r4-r8,r10-r11,pc}
		ENDP
			
		END