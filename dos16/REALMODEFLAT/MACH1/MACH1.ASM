[BITS 16]
[ORG 0100h]

[SECTION .text]
START:
            ; create file new each time under the name
        mov cx, 2
        mov dx,filename
        mov ah,0x3C
        int 0x21

                ; open file after creating it
        mov al, 2        ; must be a system file (ax register lower half)
        mov dx,filename
        mov ah,0x3D                         ; (upper half of ax)
        int 0x21

        push ax                  ; keeping this returned handle
        mov dx,title
	mov ah,9
        int 0x21
        pop bx

newline:
        mov dl,0x0D
        mov ah, 0x06
        int 0x21
        mov cx, 1
        mov [mybyte], byte 0x0D
        mov dx, mybyte
        mov ah, 0x40
        int 0x21
        mov dl,0x0A
        mov ah, 0x06
        int 0x21
        mov [mybyte], byte 0x0A
        mov dx, mybyte
        mov ah, 0x40
        int 0x21
proc:
        mov dl,0xFF
        mov ah,0x06
        int 0x21
        jz proc
        mov [mybyte], byte al
        mov dl,[mybyte]
        mov ah, 0x02
        int 0x21
        cmp [mybyte], byte 0x0D
        je newline
        mov dx,mybyte
        mov cx, 1
        mov ah, 0x40
        int 0x21
        cmp [mybyte], byte 0x1b
        jne proc
                                ; close file
        mov ah,0x3E             ; bx is already set
        int 0x21
        mov ax,0x4c00
        int 0x21

[segment .data]

title db       "MACH1 -minimal text editor-",13,10,'$'
filename db     "MACH1.TXT",0,'$'

[segment .bss]
mybyte RESB 1

