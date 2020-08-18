INCLUDE macros2.asm
INCLUDE number.asm
.MODEL LARGE
.386
.STACK 200h
	.DATA
	TRUE equ 1
	FALSE equ 0
	MAXTEXTSIZE equ 200
_Ingrese_un_valor_entero_positivo__	db	"Ingrese un valor entero positivo: ",'$', 34 dup (?)
X                               	dd	?

.CODE

START:
MOV AX,@DATA
MOV DS,AX
MOV es,ax
FINIT
FFREE

displayString _Ingrese_un_valor_entero_positivo__
GetInteger X

liberar:
	ffree
	mov ax, 4c00h
	int 21h
	jmp fin
fin:
	End START
