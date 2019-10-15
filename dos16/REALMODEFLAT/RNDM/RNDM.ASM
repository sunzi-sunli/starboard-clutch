; ############### BEGIN STACK SEGMENT

MyStack         SEGMENT STACK

        DB      64 DUP ('STACK!!!')

MyStack         ENDS

; ############# END STACK SEGMENT

; ############### BEGIN DATA SEGENT

MyData          SEGMENT

numeric         DB      "1234567890",'$'
CRLF            DB      00H,0AH,'$'
success         DB      "program succeeded",13,10,'$'

MyData          ENDS

; ############# END DATA SEGMENT

; ############### BEGIN CODE SEGMENT

MyCode          SEGMENT

                assume CS:MyCode,DS:MyData
Main            PROC

Start:          ; This is where program execution begins
                mov AX,MyData
                mov DS,AX
                ; above is boiler plate

                mov BX,12
                mov CX,131
                call Modulus

                cmp AX,11
                je correct

                mov AH,4CH
                mov AL,1
                int 21H

    correct:
                lea DX,success
                mov AH,09H
                int 21H

                ; below is boiler plate
                mov AH,4CH
                mov AL,0
                int 21H

; ########################## Procedure section


; Procedure: Modulus Load BX with divisor Load CX with figure
; returns in AX

 Modulus        PROC

                mov DX,CX
     mdls:      sub DX,BX
                cmp DX,BX
                ja mdls
                mov AX,DX
                ret

 Modulus        ENDP


; ############# END PROCEDURE SECTION

Main            ENDP

MyCode          ENDS

; ############# END CODE SEGMENT

END Start




