; ############### BEGIN STACK SEGMENT

MyStack         SEGMENT STACK

        DB      64 DUP ('STACK!!!')

MyStack         ENDS

; ############# END STACK SEGMENT

; ############### BEGIN DATA SEGENT

MyData          SEGMENT

OUTPUT          DB      ?
inputcount      DW      5
numeric         DB      "0123456789ABCDEF",'$'
CRLF            DB      00H,0AH,'$'
success         DB      "program succeeded",13,10,'$'
seed            DW      0
loopcount       DW      0
ones            DW      1
tens            DW      10
hundreds        DW      100
thousands       DW      1000
tenthousands    DW      10000
collect         DW      0
jran            DW      0

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

                mov [inputcount],5
       input:
                mov AH,01H
                int 21H
                call ProcessInput
                mov CX,AX
                mov BX,[inputcount]
                call SumColumn
                add [collect],AX
                dec [inputcount]
                cmp [inputcount],0
                jnz input

                mov AX,[collect]
                mov [seed],AX
                call FirstTerm
                mov CX,[seed]
                call Modulus
                mov [seed],AX
                
                mov AH,BYTE PTR OUTPUT
                mov [SI],AH
                mov AX,[seed]
                call Word2Str

                mov DL,[OUTPUT]
                mov AH,06H
                int 21H

                mov DL,[OUTPUT+1]
                mov AH,06H
                int 21H

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

 FirstTerm      PROC

                mov BX,31104
                mov CX,625
                mov DX,6571
                mov AX,CX
                pop CX
                mov [loopcount],CX
     mult:      add [seed],CX
                dec [loopcount]
                cmp [loopcount],0
                jnz mult
                add [seed],DX
                ret

 FirstTerm      ENDP

 ProcessInput   PROC

                cmp AL,'0'
                jmp zero
                cmp AL,'1'
                jmp one
                cmp AL,'2'
                jmp two
                cmp AL,'3'
                jmp three
                cmp AL,'4'
                jmp four
                cmp AL,'5'
                jmp five
                cmp AL,'6'
                jmp six
                cmp AL,'7'
                jmp seven
                cmp AL,'8'
                jmp eight
                cmp AL,'9'
                jmp nine

        zero:   mov AX,0
                ret
        one:    mov AX,1
                ret
        two:    mov AX,2
                ret
        three:  mov AX,3
                ret
        four:   mov AX,4
                ret
        five:   mov AX,5
                ret
        six:    mov AX,6
                ret
        seven:  mov AX,7
                ret
        eight:  mov AX,8
                ret
        nine:   mov AX,9
                ret

                
 ProcessInput   ENDP
                ; set BX to the column number of input
                ; set CX to the ascii byte actual value
 SumColumn      PROC

                mov AX,0
                cmp BX,5
                je tagone
                cmp BX,4
                je tagtwo
                cmp BX,3
                je tagthree
                cmp BX,2
                je tagfour
                cmp BX,1
                je tagfive


    tagone:     mov [loopcount],CX
    tenthous:   add AX,[tenthousands]
                dec [loopcount]
                cmp [loopcount],0
                ja tenthous
                ret

    tagtwo:     mov [loopcount],CX
    thous:      add AX,[thousands]
                dec [loopcount]
                cmp [loopcount],0
                ja thous
                ret

    tagthree:   mov [loopcount],CX
    hund:       add AX,[hundreds]
                dec [loopcount]
                cmp [loopcount],0
                ja hund
                ret

    tagfour:    mov [loopcount],CX
    tns:        add AX,[tens]
                dec [loopcount]
                cmp [loopcount],0
                ja tns
                ret

    tagfive:    mov [loopcount],CX
    units:      add AX,[ones]
                dec [loopcount]
                cmp [loopcount],0
                ja units
                ret

 SumColumn      ENDP

 Byte2Str       PROC
                mov DI,AX
                and DI,000FH
                mov BX,OFFSET numeric
                mov AH,BYTE PTR [BX+DI]
                mov [SI+1],AH
                xor AH,AH
                mov DI,AX
                shr DI,1
                shr DI,1
                shr DI,1
                shr DI,1
                mov AH,BYTE PTR [BX+DI]
                mov [SI],AH
                RET
 Byte2Str       ENDP


 Word2Str       PROC
                mov CX,AX
                xchg AH,AL
                call Byte2Str
                add SI,2
                mov AX,CX
                call Byte2Str
                ret
 Word2Str       ENDP

; ############# END PROCEDURE SECTION

Main            ENDP

MyCode          ENDS

; ############# END CODE SEGMENT

END Start




