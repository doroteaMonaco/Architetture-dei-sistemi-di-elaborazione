				
				
				AREA asm_functions, CODE, READONLY				
				EXPORT check_square
				EXPORT my_division
					
check_square
								
				STMFD sp!,{r4-r8,r10-r11,lr}

				MUL R4, R0, R0
				MUL R5, R1, R1
				MUL R6, R2, R2
				
				ADD R7, R4, R5
				CMP R7, R6
				MOVLE R0, #1
				MOVGT R0, #0
				
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
				B fine
				
my_division
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}
				
				LDR R0, [R0]
				LDR R1, [R1]
				IMPORT __aeabi_fdiv
				BL __aeabi_fdiv
				
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
fine 
                END