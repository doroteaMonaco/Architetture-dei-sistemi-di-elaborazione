				
				
				AREA |.text|, CODE, READONLY
				EXPORT find_best_3
find_best_3		PROC	
				PUSH {r4-r8,r10-r11,lr}	
				
				MOV R3, #3
				MOV R4, #-101 ;MASSIMO CORRENTE
				MOV R5, #0 ;OFFSET
				MOV R8, R1
				
loop_ext			

loop_int		LDR R6, [R0, R5]
				
				CMP R6, R4
				MOVGT R4, R6
				MOVGT R7, R5 ;MEMORIZZO OFFSET MASSIMO
				
				ADD R5, R5, #4

				SUBS R1, R1, #1
				BNE loop_int
				MOV R1, R8
				STR R4, [R2]
				ADD R2, R2, #4
				
				MOV R4, #-101 ;MASSIMO CORRENTE
				MOV R5, #0 ;OFFSET
				
				STR R4, [R0, R7] ;ANNULLO MASSIMO 
				
	
				SUBS R3, R3, #1
				BNE loop_ext
					
				MOV R0, R1
				POP {r4-r8,r10-r11,pc}
				
                ENDP	
;				EXPORT ExtractVal
;		
;ExtractVal 		PROC
;					
;				PUSH {r4-r8,r10-r11,lr}		
;						
;				LSR R0, R0, #3 ;prendo bit 3
;				
;				AND R0, R0, #255 ;prendo primi 8 bit				
;				

;				POP {r4-r8,r10-r11,pc}
;				
;                ENDP
;					
;				EXPORT fill_fibonacci

;fill_fibonacci	PROC
;	
;				PUSH {r4-r8,r10-r11,lr}	
;				
;				LDR R5, =fib ;ottengo indirizzo vettore
;				MOV R12, #12 ;loop 12 volte


;loop			
;				LDR R7, [R5]
;				LDR R8, [R5, #4]
;				ADD R9, R7, R8
;				
;				STR R9, [R5, #8]
;				
;				ADD R5, R5, #4


;				SUBS R12, R12, #1
;				BNE loop

;				POP {r4-r8,r10-r11,pc}
;				
;				ENDP
;					
;					
;				EXPORT check_fibonacci
;		
;		
;check_fibonacci PROC
;					
;				MOV R12, sp	
;					
;				PUSH {r4-r8,r10-r11,lr}	
;				
;				LDR R4, [R12] ;prendo boundary
;				
;				LDR R6, =fib				 
;				

;				
;				
;				MOV R12, #14
;				MOV R8, #2
;				
;				
;loop1			LDR R5, [R6]
;				SUBS R5, R3, R5
;				MULLT R7, R5, R8
;				ADDLT R5, R5, R7
;				
;				CMP R5, R4
;				BLE fail
;				
;				ADD R6, R6, #4												
;				
;				SUBS R12, R12, #1
;				BNE loop1
;						
;				STR R3, [R0]
;				MOV R0, #1
;				B fine

;			
;			
;fail			MOV R0, #0

;				

;fine			POP {r4-r8,r10-r11,pc}
;				
;                ENDP
;					
					
					
	
					


;				EXPORT call_svc ;uso EXPORT perch� voglio usare la variabile in un file esterno .C
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
;				;R8-R5 � il numero di shift

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

;				AREA |.data|, DATA, READWRITE
;		
;fib 			DCD 0,1,0,0,0,0,0,0,0,0,0,0,0,0
;				


;ALGORITMO SORTING DECRESCENTE
;get_and_sort	PROC
;					
;				PUSH {r4-r8,r10-r11,lr}	
;				
;				MOV R7, #0 ;offset per primo elemento
;				MOV R3, #0;offset corrente
;				MOV R6, #0 ;massimo	(mettere NUMERO GRANDE per il minimo in caso di SORTING CRESCENTE)
;				MOV R11, R2
;						
;loopext		SUB R4, R11, R7 ;lunghezza vettore interno
;				ADD R8, R0, R7 ;indirizzo vettore interno
;
;loopint
;				LDRB R5, [R8, R3] ;prendo elemento vettore interno
;				
;				CMP R5, R6 ;confronto con il massimo (minimo)
;				MOVGT R6, R5 ;se è più grande (piccolo --> MOVLT) aggiorno il massimo (minimo)
;				MOVGT R9, R3 ;prendo indice del massimo (minimo)
				
				
;				ADD R3, R3, #1 ;vado a prossimo elemento
				
;				SUBS R4, R4, #1
;				BNE loopint
				
;				LDRB R10, [R8] ;prendo elemento in prima posizione vettore interno
				
;				STRB R6, [R8] ;stampo massimo nella prima posizione del vettore interno
;				MOV R6, #0 ;metto massimo a 0
				
;				STRB R10, [R8, R9] ;stampo elemento in prima posizione al posto del posto precedente del massimo
				

;				ADD R7, R7, #1 ;accorcio vettore interno
;				MOV R3, #0 ;azzero offset
;				
;				SUBS R2, R2, #1
;				BNE loopext
				

;				POP {r4-r8,r10-r11,pc}
				
;               ENDP

				END










				
;ISTRUZIONI CONDIZIONALI CHE SUPPORTANO SUFFISSI
;1. Istruzioni di Aritmetica
;Queste istruzioni aggiornano i flag opzionalmente (se accompagnate dal suffisso S) e supportano i suffissi condizionali:

;ADD: Somma.
;ADC: Somma con Carry.
;SUB: Sottrazione.
;SBC: Sottrazione con Carry.
;RSB: Sottrazione inversa.
;RSC: Sottrazione inversa con Carry.
;MUL: Moltiplicazione.
;MLA: Moltiplicazione con Accumulo.

;2. Istruzioni di Confronto
;Queste istruzioni aggiornano esclusivamente i flag e non producono un risultato esplicito:

;CMP: Confronto (sottrazione).
;CMN: Confronto con Carry (addizione).
;TST: Test (AND bit a bit).
;TEQ: Test di uguaglianza (XOR bit a bit).

;3. Istruzioni Logiche
;Queste istruzioni eseguono operazioni logiche bit a bit e possono aggiornare i flag:

;AND: AND logico.
;ORR: OR logico.
;EOR: XOR logico.
;BIC: AND con maschera invertita.
;MOV: Caricamento di un valore.
;MVN: NOT bit a bit.

;4. Istruzioni di Caricamento e Memorizzazione
;Queste istruzioni accedono alla memoria e supportano condizioni:

;LDR: Carica un dato da memoria.
;STR: Memorizza un dato in memoria.
;LDM: Carica pi� registri da memoria.
;STM: Memorizza pi� registri in memoria.
;LDRB: Carica un byte da memoria.
;STRB: Memorizza un byte in memoria.
;LDRH: Carica una mezza parola (16 bit) da memoria.
;STRH: Memorizza una mezza parola (16 bit) in memoria.

;5. Istruzioni di Branching
;Queste istruzioni saltano condizionatamente:

;B: Salto incondizionato.
;BL: Salto con link (per subroutine).
;BX: Salto a un indirizzo specifico (cambio di stato ARM/Thumb opzionale).
;BLX: Salto con link e cambio stato (ARM/Thumb).
;	
;6. Istruzioni di Shift e Rotazione
;Queste istruzioni manipolano i bit nei registri:

;ASR: Arithmetic Shift Right.
;LSR: Logical Shift Right.
;LSL: Logical Shift Left.
;ROR: Rotate Right.
;RRX: Rotate Right con Carry.

;7. Istruzioni Multiply-Accumulate
;Queste istruzioni eseguono moltiplicazioni avanzate:

;MUL: Moltiplicazione.
;MLA: Moltiplicazione con Accumulo.
;MLS: Moltiplicazione con Sottrazione.

;8. Istruzioni Condizionali Speciali
;Alcune istruzioni sono intrinsecamente condizionali:

;SWI: Software Interrupt.
;SVC: Supervisor Call.
;BKPT: Breakpoint.

;9. Istruzioni Multiple
;Queste istruzioni per operazioni su pi� registri supportano suffissi:

;POP: Carica pi� registri dalla stack.
;PUSH: Salva pi� registri nello stack.















;# Instruction Set Architecture (ISA) per ARM Cortex



;## 1. Direttive Assembler

;### **.data**
;**Descrizione:** Indica l'inizio della sezione dati.

;```assembly
;.data
;```

;### **.text / .code**
;**Descrizione:** Indica l'inizio della sezione codice.

;```assembly
;.text  ; oppure .code
;```

;### **.org**
;**Descrizione:** Imposta l'indirizzo iniziale.

;```assembly
;.org 0x1000
;```

;### **.space**
;**Descrizione:** Riserva un numero specifico di byte.

;```assembly
;.space 16  ; Riserva 16 byte
;```

;### **.ascii / .asciiz**
;**Descrizione:** Inserisce una stringa ASCII. `.asciiz` aggiunge automaticamente il terminatore null.

;```assembly
;.ascii "Hello"
;.asciiz "Hello\0"
;```

;### **.align**
;**Descrizione:** Allinea alla specifica boundary di byte.

;```assembly
;.align 4  ; Allinea a un multiplo di 4 byte
;```

;### **.word / .byte / .double**
;**Descrizione:** Inserisce valori di diverse dimensioni.

;```assembly
;.word 0x1234, 0x5678
;.byte 0x12, 0x34
;.double 3.14159
;```

;---

;## 2. Istruzioni Aritmetiche

;### **ADD** - Somma
;**Descrizione:** Somma due operandi e salva il risultato in un registro.
;**Sintassi:**

;```assembly
;ADD{cond}{S} Rd, Rn, Operand2
;```

;- `Rd`: Registro di destinazione.
;- `Rn`: Primo operando.
;- `Operand2`: Secondo operando (registro, valore immediato o risultato di uno shift).
;- `cond`: (Opzionale) Condizione per eseguire l'istruzione.
;- `S`: (Opzionale) Aggiorna i flag CPSR.

;**Esempio:**

;```assembly
;ADD R0, R1, R2   ; R0 = R1 + R2
;ADDS R0, R1, #5  ; R0 = R1 + 5, aggiorna i flag
;```

;### **ADC** - Somma con Carry
;**Descrizione:** Somma due operandi e il valore del carry.

;```assembly
;ADC R0, R1, R2   ; R0 = R1 + R2 + Carry
;```

;### **SUB / SBC** - Sottrazione (con Carry)
;**Descrizione:** Sottrae il secondo operando dal primo.

;```assembly
;SUB R0, R1, R2   ; R0 = R1 - R2
;SBC R0, R1, R2   ; R0 = R1 - R2 - Carry
;```

;### **MUL / MLA** - Moltiplicazione
;**Descrizione:** Moltiplica due operandi, opzionalmente aggiungendo un accumulatore.

;```assembly
;MUL R0, R1, R2   ; R0 = R1 * R2
;MLA R0, R1, R2, R3 ; R0 = (R1 * R2) + R3
;```

;---

;## 3. Istruzioni Logiche

;### **AND / ORR / EOR**
;**Descrizione:** Operazioni logiche bit a bit.

;```assembly
;AND R0, R1, R2   ; R0 = R1 AND R2
;ORR R0, R1, R2   ; R0 = R1 OR R2
;EOR R0, R1, R2   ; R0 = R1 XOR R2
;```

;### **BIC / MVN**
;**Descrizione:** AND con maschera invertita e NOT bit a bit.

;```assembly
;BIC R0, R1, #0xFF ; R0 = R1 AND NOT 0xFF
;MVN R0, R1        ; R0 = NOT R1
;```

;---

;## 4. Istruzioni di Movimento

;### **MOV / MOVT**
;**Descrizione:** Sposta un valore in un registro, opzionalmente nei bit alti.

;```assembly
;MOV R0, #10      ; R0 = 10
;MOVT R0, #0x1234 ; Imposta i 16 bit alti di R0
;```

;---

;## 5. Istruzioni di Confronto

;### **CMP / TST**
;**Descrizione:** Confronta valori o testa bit.

;```assembly
;CMP R0, #0       ; Confronta R0 con 0
;TST R0, #1       ; Testa se il bit 0 di R0 � impostato
;```

;---

;## 6. Istruzioni di Rotazione e Shift

;### **LSL / LSR / ASR / ROR**
;**Descrizione:** Shift logici, aritmetici e rotazioni.

;```assembly
;LSL R0, R1, #2   ; Shift logico sinistra di 2 bit
;LSR R0, R1, #2   ; Shift logico destra di 2 bit
;ASR R0, R1, #2   ; Shift aritmetico destra di 2 bit
;ROR R0, R1, #2   ; Rotazione destra di 2 bit
;```

;---

;## 7. Istruzioni di Caricamento e Memorizzazione

;### **LDR / STR**
;**Descrizione:** Caricamento e memorizzazione da/verso memoria.

;```assembly
;LDR R0, [R1]    ; Carica il valore puntato da R1 in R0
;STR R0, [R1]    ; Memorizza il valore di R0 all'indirizzo puntato da R1
;```

;### **LDM / STM**
;**Descrizione:** Carica o memorizza pi� registri.

;```assembly
;LDMIA R0!, {R1-R3} ; Carica R1, R2, R3 dalla memoria partendo da R0
;STMDB R0!, {R1-R3} ; Memorizza R1, R2, R3 in memoria partendo da R0
;```

;---

;## 8. Istruzioni di Branching

;### **B / BL / BX**
;**Descrizione:** Salti condizionati e non.

;```assembly
;B Label          ; Salta a Label
;BL Subroutine    ; Salta a Subroutine salvando il ritorno in LR
;BX LR            ; Ritorna da una subroutine
;```

;---

;## 9. Istruzioni Floating Point

;### **VCVT**
;**Descrizione:** Conversioni tra interi e floating-point.

;```assembly
;VCVT.F32.S32 S0, S1 ; Converte un intero in float
;VCVT.S32.F32 S1, S0 ; Converte un float in intero
;```

;### **VADD / VSUB / VMUL / VDIV**
;**Descrizione:** Operazioni aritmetiche su numeri floating-point.

;```assembly
;VADD.F32 S0, S1, S2 ; S0 = S1 + S2
;VSUB.F32 S0, S1, S2 ; S0 = S1 - S2
;VMUL.F32 S0, S1, S2 ; S0 = S1 * S2
;VDIV.F32 S0, S1, S2 ; S0 = S1 / S2
;```

;---

;## 10. Pseudo-Istruzioni

;### **NOP**
;**Descrizione:** Nessuna operazione.

;```assembly
;NOP
;```

;### **ADR**
;**Descrizione:** Calcola l'indirizzo di un'etichetta.

;```assembly
;ADR R0, Label
;```












;1. Unit� FPU e Registri Floating Point
;Registri Floating Point
;L'FPU ARM utilizza due set di registri per il calcolo in virgola mobile:

;S0-S31: Registri a precisione singola (32-bit).
;D0-D15: Registri a precisione doppia (64-bit), che sovrappongono coppie di registri a precisione singola (es. D0 = {S0, S1}).
;2. Istruzioni Floating Point
;Caricamento e Memorizzazione
;VLD: Carica un dato floating-point dalla memoria.
;assembly
;Copia codice
;VLD1.32 {S0}, [R0]    ; Carica un valore float da memoria
;VST: Memorizza un dato floating-point in memoria.
;assembly
;Copia codice
;VST1.32 {S0}, [R0]    ; Salva un valore float in memoria
;Operazioni Aritmetiche
;VADD: Somma.
;assembly
;Copia codice
;VADD.F32 S0, S1, S2   ; S0 = S1 + S2 (precisione singola)
;VSUB: Sottrazione.
;assembly
;Copia codice
;VSUB.F32 S0, S1, S2   ; S0 = S1 - S2
;VMUL: Moltiplicazione.
;assembly
;Copia codice
;VMUL.F32 S0, S1, S2   ; S0 = S1 * S2
;VDIV: Divisione.
;assembly
;Copia codice
;VDIV.F32 S0, S1, S2   ; S0 = S1 / S2
;Conversioni
;VCVT: Converte tra interi e floating-point.
;assembly
;Copia codice
;VCVT.F32.S32 S0, S1   ; Converte da intero a float
;VCVT.S32.F32 S0, S1   ; Converte da float a intero
;Confronto
;VCMP: Confronta due valori floating-point.
;assembly
;Copia codice
;VCMP.F32 S0, S1       ; Confronta S0 con S1
;VMRS APSR_nzcv, FPSCR ; Trasferisce i flag di confronto nel registro APSR
;3. Esempio di Programma
;Un esempio completo che mostra come sommare due numeri floating-point e salvare il risultato.

;assembly
;Copia codice
;    AREA .text, CODE, READONLY
;    ENTRY
;    LDR R0, =val1       ; Carica indirizzo di val1
;    LDR R1, =val2       ; Carica indirizzo di val2
;    LDR R2, =result     ; Carica indirizzo per salvare il risultato

;    VLDR.F32 S0, [R0]   ; Carica val1 in S0
;    VLDR.F32 S1, [R1]   ; Carica val2 in S1
;    VADD.F32 S2, S0, S1 ; S2 = S0 + S1
;    VSTR.F32 S2, [R2]   ; Salva S2 in memoria

;    END

;    AREA .data, DATA, READWRITE
;val1    DCD 3.14         ; Valore float
;val2    DCD 1.59
;result  DCD 0.0          ; Risultato





;SUFFISSI




;Ecco i principali suffissi condizionali utilizzabili per valutare questi flag:

;1. Suffissi per il Flag Z (Zero):
;EQ (Equal): Z = 1 (uguale a zero)
;NE (Not Equal): Z = 0 (non uguale a zero)
;2. Suffissi per il Flag N (Negative):
;MI (Minus): N = 1 (negativo)
;PL (Plus): N = 0 (positivo o zero)
;3. Suffissi per il Flag C (Carry):
;CS (Carry Set): C = 1 (carry generato)
;CC (Carry Clear): C = 0 (carry non generato)
;4. Suffissi per il Flag V (Overflow):
;VS (Overflow Set): V = 1 (overflow)
;VC (Overflow Clear): V = 0 (nessun overflow)
;5. Combinazioni di Flag:
;HI (Higher): C = 1 e Z = 0 (unsigned higher)
;LS (Lower or Same): C = 0 o Z = 1 (unsigned lower or same)
;GE (Greater or Equal): N = V (signed greater or equal)
;LT (Less Than): N ≠ V (signed less than)
;GT (Greater Than): Z = 0 e N = V (signed greater than)
;LE (Less or Equal): Z = 1 o N ≠ V (signed less or equal)
;AL (Always): Ignora i flag, esegue sempre l'istruzione
;NV (Never): Non esegue mai l'istruzione (non usato comunemente)












