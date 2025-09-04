				mov r10, #2_00000101
				mov r11, #2
				mov r12, #5
				mov r8, #0
				mov r9, #2_10000000
				
loop1			
				tst r9, r10
				bne fine
				adds r8, r8, #1
				lsr r9, r9, #1
				cmp r9, #0
				bne loop1
				
fine_loop1
				tst r8, #1
				it eq
				addeq r3, r11, r12
				subne r3, r11, r12
				

fine 			LDR     R0, =stop

stop            BX      R0
                ENDP