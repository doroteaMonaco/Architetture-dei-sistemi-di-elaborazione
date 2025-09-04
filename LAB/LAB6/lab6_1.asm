;ESERCIZIO 1
				
				mov r1, #0xFFFFFFFF
				mov r2, #-1
				mov r3, #1
				
				subs r4, r2, r1
				adds r5, r2, r3

fine 			LDR     R0, =stop

stop            BX      R0
                ENDP