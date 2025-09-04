				mov r6, #5
				mov r7, #4
				
				cmp r6, r7
				beq operation
				bhi store
				mov r8, r7
				B fine
				
				
operation		LSR r6, r6, #1
				subs r4, r7, r6
				B fine
				
store 			
				mov r8, r6
				B fine

fine 			LDR     R0, =stop

stop            BX      R0
                ENDP