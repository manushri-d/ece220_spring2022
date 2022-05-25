;In this program, we computed an LC-3 program that evaluates postfix
;expressions using a stack. We first echoed the input to the screen
;and then directly went into the EVALUATE subroutine. In the
;subroutine, if the char typed was a "=", then the program would
;end, and print its result after storing it in R5(if the stack only
;had one value. If not, "Invalid Expression" would be printed, and
;the program would end. The program ignores spaces. The program 
;checks if the character typed is a digit or an operator. If the
;char is a digit, the value would be pushed. If the char is an
;operator, 2 values would be popped and the designated operator
;would be applied(through other subroutines). The value would then
;be pushed. If the character typed is invalid, "Invalid Expression"
;would be printed.
;partners: ssrir5, jatint2
;
.ORIG x3000

;your code goes here

START
	;read next input
	;echo it to screen (register R0)
	GETC
	OUT
	JSR EVALUATE
	BR START

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - char to be printed
;R1 - digit counter
;R2 - bit counter
;R3 - value to print in hexadecimal
;R4 - address to get print char
PRINT_HEX
	AND R1, R1, #0	;init R1
	ADD R1, R1, #4	;load for 4 since we have 4 outer loops
PRINTDIGIT
	AND R0, R0, #0	;init R0
	ADD R2, R0, #4	;init bit counter to 4

READBIT
	ADD R0, R0, R0	;left shift
	ADD R3, R3, #0	;referencing R3 for branch statement
	BRzp SHIFT
	ADD R0, R0, #1	;adding 1 and shift

SHIFT
	ADD R3, R3, R3	;left shift
	ADD R2, R2, #-1	;decrement bit counter
	BRp READBIT
	ADD R0, R0, #-10 ;check if number of letter
	BRn NUMBER 		; if negative, it is a number
	ADD R0, R0, #7

NUMBER
	LD R4, ALPHABET
	ADD R0, R0, R4	;adds 48 for alphabet
	OUT
	ADD R1, R1, #-1	;decrements digit counteeer
	BRp PRINTDIGIT	;branch until 0
	AND R4, R4, #0	;clear R4, since only R5 can be modified
	HALT

ALPHABET		.FILL #58
OFFSVAL			.FILL #65
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ADD R0, R3, R4 ;R0 = R3 + R4
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;computes R3 - R4
MIN	
	ST R4, MIN_SAVER4	;save R2
	NOT R4, R4		
	ADD R4, R4, #1		;-R4
	ADD R0, R3, R4		;R0 = R3-R4
	LD R4, MIN_SAVER4
	RET
MIN_SAVER4	.BLKW #1	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
	ST R3, MUL_SAVER3
	ST R4, MUL_SAVER4
	AND R0, R0, #0		
	ADD R3, R3, #0
	BRn ONENEGATIVE		;checks if R3 is negative
	BRz MULEND			;go to MULEND if there is a 0
	ADD R4, R4, #0
	BRn OTHERNEGATIVE	;checks if R4 is negative
	BRz MULEND			;go to MULEND if there is a 0
TWOPOS
	ADD R0, R0, R3		; R0 = R0 + R3
	ADD R4, R4, #-1		;decrements R4
	BRp TWOPOS			;loops
	BRz MULEND			;finished mult
ONENEGATIVE
	NOT R3, R3			
	ADD R3, R3, #1		;-R3
	ADD R4, R4, #0		;checks for a second negative
	BRp ONENEGCONV		;two numbers are pos
	NOT R4, R4
	ADD R4, R4, #1		;-R4
	BR TWOPOS			;result is positive
OTHERNEGATIVE
	NOT R4, R4
	ADD R4, R4, #1		;-R4
ONENEGCONV
	ADD R0, R0, R3		;R0 = R0 + R3
	ADD R4, R4, #-1
	BRp ONENEGCONV
	ADD R0, R0, #-1		
	NOT R0, R0			;-R0
MULEND
	LD R3, MUL_SAVER3
	LD R4, MUL_SAVER4
	RET

MUL_SAVER3	.BLKW #1
MUL_SAVER4	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
	ST R4, DIV_SAVER4
	ST R3, DIV_SAVER3
	AND R0, R0, #0		;init R0
	ADD R4, R4, #-1		
	NOT R4, R4			;-R4
KEEPON
	ADD R0, R0, #1		;add 1 to quotient
	ADD R3, R3, R4		;subtract R4 - R3
	BRzp KEEPON			;loop if remainder is not negative
	ADD R0, R0, #-1		;subtract 1 from quotient if the remainder is negative
NEGATIVE
	NOT R4, R4			
	ADD R4, R4, #1		;R4
	ADD R1, R3, R4		;R1= R3+R
	LD R4, DIV_SAVER4
	LD R3, DIV_SAVER3
	RET

DIV_SAVER4	.BLKW #1
DIV_SAVER3	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	ST R7, EXP_SAVER7
	AND R0, R0, #0	;init R0
	AND R1, R4, R4	;R1 is counter
	ADD R1, R1, #-1	;decrement counter(depending on how many times we mult)
	BRn EXPZERO		;if value is negative, exp is 0, so branch
	BRz EXPONE		;if value is 0, exp is 1, so branch
	AND R2, R3, R3	;if not, set R4 = R3 to mult
EXPL
	AND R4, R4, #0	;init R4
	ADD R4, R2, #0	;setting val of R3 in R4
	JSR MUL			;jump to MUL subroutine to multiply
	AND R3, R3, #0	;init R3
	ADD R3, R0, #0	;store ans in R3
	ADD R1, R1, #-1	;decrement R1
	BRz EXPDONE		;exponent is done
	BRp EXPL		;if not, keep multiplying
EXPZERO
	ADD R0, R0, #1	;R0 = 1 since the exp of a value to 0 is 1
	BR EXPDONE
EXPONE
	ADD R0, R3, #0	;R0 = R3 since exp of a value to 1 is the value
EXPDONE
	LD R7, EXP_SAVER7
	RET

EXP_SAVER7	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R0, R1
;output R1
SUBTRACT
	NOT R1, R1
	ADD R1, R1, #1 ; gets the negative value of R1
	ADD R1, R1, R0 ; subtracts R1 and R0
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R1 - LABEL for hex values of diff chars
;R2 - stores STACK_TOP, also holds R0
;R3 - stores STACK_START, also holds R0
;R4 - temp register to store value of R3-R2
;R5 - final value stored in R5

EVALUATE
	;check if value == "="
	ST R7, EVAL_SAVER7
	ST R0, EVAL_SAVER0
	LD R1, EQUALSIGN		;loads hex value of = to R0
	JSR SUBTRACT
	BRz CHKONEVAL			;if 0, check if stack has only one value
	BR CHKSPINP				;check space input, meaning check if the input is a space char

CHKONEVAL
	;if stack has only one value
	LD R2, STACK_TOP		;loads the value of stack top
	NOT R2, R2
	ADD R2, R2, #1			;gets -R2
	LD R3, STACK_START		;loads the value of stack start
	ADD R4, R2, R3			;compares them to check if stack has only 1 value
	ADD R4, R4, #-1			;decrement
	BRnp NOTONEVALUE		;if not, print "Invalid Expression"
	BR PRH
	
NOTONEVALUE
	LEA R0, INVALIDSTATE	;loads string value
	PUTS 					;prints it out
	BR STOP

PRH	
	JSR POP					;pop value to print
	ADD R5, R0, #0			;store value in R5
	ADD R3, R0, #0			;store value in R3 to print
	BR PRINT_HEX			;go to PRINT_HEX
	BR STOP

CHKSPINP ;checks if there is a space
	LD R1, SPACECHAR
	JSR SUBTRACT
	BRz ENDSUBROUTINE		;if char is a space char, go to start

	;check if input character is valid
	;first, check each number
	LD R1, ZERO
	JSR SUBTRACT			;subtracting results in 0 if the value is the value loaded
	BRz OPERAND				;if the value is 0, branch to operand

	LD R1, ONE		;repeat with every digit 0-9
	JSR SUBTRACT
	BRz OPERAND

	LD R1, TWO
	JSR SUBTRACT
	BRz OPERAND

	LD R1, THREE
	JSR SUBTRACT
	BRz OPERAND

	LD R1, FOUR
	JSR SUBTRACT
	BRz OPERAND

	LD R1, FIVE
	JSR SUBTRACT
	BRz OPERAND

	LD R1, SIX
	JSR SUBTRACT
	BRz OPERAND

	LD R1, SEVEN
	JSR SUBTRACT
	BRz OPERAND

	LD R1, EIGHT
	JSR SUBTRACT
	BRz OPERAND

	LD R1, NINE
	JSR SUBTRACT
	BRz OPERAND
	
	;check if operator

	LD R1, PLUSSIGN 
	JSR SUBTRACT ;subtracting results in 0 if the value is the value loaded
	BRz PLUSF ;if char is + in this case, branch to PLUSF(since val is 0)

	LD R1, MINUSSIGN	;repeat with every operator
	JSR SUBTRACT
	BRz MINUSF

	LD R1, MULTSIGN
	JSR SUBTRACT
	BRz MULTF

	LD R1, DIVIDESIGN
	JSR SUBTRACT
	BRz DIVIDEF

	LD R1, EXPSIGN
	JSR SUBTRACT
	BRz EXPF

	BR NOTVALID			;skip if not a valid character

PLUSF
	JSR POP				;pop value
	ADD R4, R0, #0		;set R4 = R0
	JSR POP				;pop value
	ADD R3, R0, #0		;set R3 = R0
	ADD R5, R5, #0
	BRp NOTVALID		;if R5 is positive, it is not valid
	JSR PLUS			;if it is, jump to PLUS subroutine
	JSR PUSH			;push this value
	BR ENDSUBROUTINE	;branch after

MINUSF
	JSR POP				;pop value
	ADD R4, R0, #0		;set R4 = R0
	JSR POP				;pop value
	ADD R3, R0, #0		;set R3 = R0
	ADD R5, R5, #0
	BRp NOTVALID		;if R5 is positive, it is not valid
	JSR MIN				;if it is, jump to MINUS subroutine
	JSR PUSH			;push this value
	BR ENDSUBROUTINE	;branch after

MULTF
	JSR POP
	ADD R4, R0, #0
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp NOTVALID		;if R5 is positive, it is not valid
	JSR MUL				;if it is, jump to MUL subroutine
	JSR PUSH			;push this value
	BR ENDSUBROUTINE	;branch after

DIVIDEF
	JSR POP
	ADD R4, R0, #0
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp NOTVALID		;if R5 is positive, it is not valid
	JSR DIV				;if it is, jump to DIV subroutine
	JSR PUSH			;push this value
	BR ENDSUBROUTINE	;branch after

EXPF
	JSR POP
	ADD R4, R0, #0
	JSR POP
	ADD R3, R0, #0
	ADD R5, R5, #0
	BRp NOTVALID		;if R5 is positive, it is not valid
	JSR EXP				;if it is, jump to EXP subroutine
	JSR PUSH			;push this value
	BR ENDSUBROUTINE	;branch after

OPERAND
	LD R1, ZERO
	NOT R1, R1
	ADD R1, R1, #1
	ADD R0, R0, R1 ;convert to decimal
	JSR PUSH
	BR ENDSUBROUTINE

NOTVALID ;print "Invalid Expression"
	LDR R0, R1, #0
	LEA R0, INVALIDSTATE
	PUTS
	BR STOP

ENDSUBROUTINE
	LD R7, EVAL_SAVER7 ;have to load original value for R7 since PC was changed
	LD R0, EVAL_SAVER0
	RET

EQUALSIGN	.FILL x3D; ascii hex value for =
INVALIDSTATE .STRINGZ "Invalid Expression"
EVAL_SAVER7	.BLKW #1
EVAL_SAVER0 .BLKW #1
SPACECHAR	.FILL x20; ascii hex value for space
ZERO		.FILL x30; ascii hex value for 0
ONE			.FILL x31; ascii hex value for 1
TWO			.FILL x32; ascii hex value for 2
THREE		.FILL x33; ascii hex value for 3
FOUR		.FILL x34; ascii hex value for 4
FIVE		.FILL x35; ascii hex value for 5
SIX			.FILL x36; ascii hex value for 6
SEVEN		.FILL x37; ascii hex value for 7
EIGHT		.FILL x38; ascii hex value for 8
NINE		.FILL x39; ascii hex value for 9
PLUSSIGN	.FILL x2B; ascii hex value for +
MINUSSIGN	.FILL x2D; ascii hex value for -
DIVIDESIGN	.FILL x2F; ascii hex value for /
MULTSIGN	.FILL x2A; ascii hex value for *
EXPSIGN		.FILL x5E; ascii hex value for ^
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

STOP HALT ;ends the program





.END
