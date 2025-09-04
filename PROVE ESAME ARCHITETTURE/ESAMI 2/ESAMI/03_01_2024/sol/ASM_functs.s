				
				
				AREA |.text|, CODE, READONLY
				EXPORT ExtractVal
		
ExtractVal 		PROC
					
				PUSH {r4-r8,r10-r11,lr}		
						
				LSR R0, R0, #3 ;prendo bit 3
				
				AND R0, R0, #255 ;prendo primi 8 bit				
				

				POP {r4-r8,r10-r11,pc}
				
                ENDP
					
				EXPORT fill_fibonacci

fill_fibonacci	PROC
	
				PUSH {r4-r8,r10-r11,lr}	
				
				LDR R5, =fib ;ottengo indirizzo vettore
				MOV R12, #12 ;loop 12 volte


loop			
				LDR R7, [R5]
				LDR R8, [R5, #4]
				ADD R9, R7, R8
				
				STR R9, [R5, #8]
				
				ADD R5, R5, #4


				SUBS R12, R12, #1
				BNE loop

				POP {r4-r8,r10-r11,pc}
				
				ENDP
					
					
				EXPORT check_fibonacci
		
		
check_fibonacci PROC
					
				MOV R12, sp	
					
				PUSH {r4-r8,r10-r11,lr}	
				
				LDR R4, [R12] ;prendo boundary
				
				LDR R6, =fib				 
				

				
				
				MOV R12, #14
				MOV R8, #2
				
				
loop1			LDR R5, [R6]
				SUBS R5, R3, R5
				MULLT R7, R5, R8
				ADDLT R5, R5, R7
				
				CMP R5, R4
				BLE fail
				
				ADD R6, R6, #4												
				
				SUBS R12, R12, #1
				BNE loop1
						
				STR R3, [R0]
				MOV R0, #1
				B fine

			
			
fail			MOV R0, #0

				

fine			POP {r4-r8,r10-r11,pc}
				
                ENDP
					
					
					
	
					


;				EXPORT call_svc ;uso EXPORT perchè voglio usare la variabile in un file esterno .C
;				
;				;chiamo SVC function
;call_svc		PROC
;					
;				SVC	#0x15 ;chiamo SVC con numero arbitrario in base alle esigenze	
;				BX lr
;				
;				ENDP ;fine singola procedura
;					
;				EXPORT  check_square
;					
;check_square
;				PUSH {r4-r8,r10-r11,lr}				
;				
;				MUL R4, R0, R0  ;R4=x^2
;				MUL R5, R1, R1	;R5=y^2
;				MUL R6, R2, R2	;R6=r^2
;				
;				ADD R7, R4, R5	;R7=x^2+y^2
;				
;				CMP R7, R6		;confronto
;				MOVLE R0, #1	;se x^2+y^2 <= r^2 torna 1
;				MOVGT R0, #0	;altrimenti 0
;				
;				

;				POP {r4-r8,r10-r11,pc}
;				
;                ENDP
;					
;				
;				EXPORT  my_division

;					
;my_division

;				
;				; save current SP for a faster access 
;				; to parameters in the stack
;				MOV   r12, sp
;				; save volatile registers
;				PUSH {r4-r8,r10-r11,lr}
;								
;				
;				LDR R0, [R0]	;R0=*(&area_f)
;				LDR R1, [R1] 	;R1=*(&r_quadrato)
;				IMPORT __aeabi_fdiv ;ci vuole IMPORT per usarla
;				BL __aeabi_fdiv
;				
;				
;				
;			
;				POP {r4-r8,r10-r11,pc}
;				
;				ENDP

;				EXPORT  next_state
;					
;					
;next_state		PUSH {r4-r8,r10-r11,lr}
;				
;				AND R4, R0, #1 ;current state AND 1
;				STR R4, [R2]
;				
;				MOV R5, #8 ;indice loop
;				MOV R8, #8 ;8 fisso
;				MOV R3, #1 ;flag prima iterazione
;				
;				;R8-R5 è il numero di shift

;loop			TST R1, #1
;				
;				
;				
;				BEQ skip
;				

;tap				SUB R6, R8, R5 ;calcolo numero di shift
;				SUBS R3, R3, #1
;				
;				BEQ first ; prima iterazione
;				
;				LSR R9, R0, R6
;				
;				
;				
;				EOR R4, R4, R9
;				
;				
;				

;				B skip
;				
;first			LSR R4, R0, R6

;				
;skip			SUBS R5, R5, #1
;				LSR R1, R1, #1

;				BNE loop
;				
;				AND R4, R4, #1
;				LSL R4, R4, #7
;				
;				LSR R0, R0, #1
;				
;				ORR R0, R0, R4



;				LDMFD POP {r4-r8,r10-r11,pc}
;				
;				ENDP

				AREA |.data|, DATA, READWRITE
		
fib 			DCD 0,1,0,0,0,0,0,0,0,0,0,0,0,0
				
				END

				
