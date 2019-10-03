; source name           : EAT.ASM
; executable name       : EAT.COM
; Code model:           : real mode flat model
; version               : 1.0
; Created date          : 6/4/1999
; Last update           : 9/10/1999
; Author                : Jeff Duntemann
; Description           : A simple example of a DOS .COM file
;			  nasm -f bin EAT.ASM -o EAT.COM
[BITS 16]
[ORG 0100h]

[SECTION .text]
START:

        mov dx, eatmsg
        mov ah,9
        int 21H

        mov ah, 01H
        int 21H

        mov [input], byte al
        cmp [input], byte 59H
        je ans
        mov dx, answerno
        mov ah,9
        int 21H
        jmp end
ans:
        mov dx, answer
        mov ah,9
        int 21H

end:
        mov ax, 04C00H
        int 21H

[SECTION .data]

eatmsg  db "Eat at Joe's!", 13, 10, "$"
answer  db "Yes I did.", 13, 10, "$"
answerno db "No I did not.", 13, 10, "$"

[SECTION .BSS]

input RESB     1



