; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt
;ʵ������0fffh��BCD�����

code segment
assume cs:code, ds:data
start:
mov ds, ax
mov dx,0000h
mov ax,0FFFFH
mov cx,10000
div cx 
mov result,al
mov ax,dx	;����Ϊ8λ,���֮�����������dx
mov dx,0000h
mov cx,1000
div cx
mov result+1,al
mov ax,dx
mov dx,0000h
mov cx,100
div cx
mov result+2,al
mov ax,dx
mov dx,0000h
mov cx,100
div cx
mov result+3,al 
mov result+4,dl
jmp $ 
code ends
data segment
    result db 5 dup(0)
    data ends
end start




