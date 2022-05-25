; In this code, I printed the ascii character using the hex address
; (which I stored using a variable). I then printed a space char using a
; variable. Then, I set a counter up to print the hex values. I then
; looped the code until every hex value was printed. Then I printed
; a new line similar to how I printed the ascii character and the
; space character. A challenge I faced was running out of registers, 
; so I used temp registers, and periodically cleared registers as I needed. 

; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
; R0 = temp variable
; R1 = current ascii char 
; R2 = current address 
; R3 = current value 
; R4 = counter for the printing loop for ascii char and space 
; R5 = counter for the hex loop 
; R6 = counter for the value increment loop 

			LD R0, CLEAR ;init
			LD R1, CLEAR 
			LD R2, CLEAR 
			LD R3, CLEAR
			LD R4, CLEAR
			LD R5, CLEAR
			LD R6, CLEAR

			LD R1, CHAR ;loads the first char address
			LD R3, HIST_ADDR ;loads the histogram initial address
			ADD R4, R4, #15 ;holds 27(we will decrement this to count down)
			ADD R4, R4, #12
			

PRINTCHSP	LD R0, CLEAR
			ADD R0, R0, R1
			OUT				;print ascii char															
			LD R0, SPACE
			OUT				;print space
			LD R0, CLEAR
			LDR R2, R3, #0	;load the current ascii address
			LD R5, CLEAR
			LD R5, FOUR	;set the counter for the ascii to 4

HEXC		LD R6, CLEAR
			LD R6, FOUR ;set the counter for the hex value to 4
			BR VALINC ;branch to value incrementer

NOINC		ADD R2, R2, R2  ;left shift 
			ADD R6, R6, #-1 ;decrement
			BRnz SKIPVALINC	;if value is positive, increment value

VALINC		ADD R0, R0, R0	;left shift
			ADD R2, R2, #0	
			BRzp NOINC		;if the current hex value is positive, increment R0
			ADD R0, R0, #1
			BR NOINC		;branch to no increment

SKIPVALINC	LD R6, VAL ;VAL holds -57 to determine char
			ADD R0, R0, #15 ;offset of 48 is added to R0
			ADD R0, R0, #15
			ADD R0, R0, #15
			ADD R0, R0, #3
			ADD R6, R6, R0 ;ADD R6 and R0 with the 48 offset to figure out type of char
			BRnz PRINTHXNL 
			ADD R0, R0, #7 ;if the previous value is positive, add offset of 7 to get type of char

PRINTHXNL	OUT	; prints the hex value(one digit at a time)
			LD R0, CLEAR
			ADD R5, R5, #-1 ;decrements the hex loop char
			BRp HEXC ;if there are still more hex values to print, loop to HEXC
			LD R0, NEWLINE ;prints new line
			OUT
			ADD R4, R4, #-1 ;decrements counter to one less character
			BRz DONE ;if there are no more ascii values left to print, halt program
			ADD R1, R1, #1 ;increment the char address
			ADD R3, R3, #1 ;increment the current value
			BR PRINTCHSP
		
DONE	HALT			; done

CLEAR		.FILL x00
CHAR 		.FILL x40
SPACE 		.FILL x20
FOUR		.FILL x04
NEWLINE 	.FILL x0A
VAL 		.FILL xFFC7


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
