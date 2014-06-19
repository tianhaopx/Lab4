
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               syscall.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

%include "sconst.inc"

_NR_get_ticks       equ 0 ; 要跟 global.c 中 sys_call_table 的定义相对应！
_NR_prog_sleep		equ 1
_NR_disp_str		equ 2
_NR_sem_p			equ 3
_NR_sem_v			equ 4

INT_VECTOR_SYS_CALL equ 0x90
INT_VECTOR_PROG_SLEEP	equ 0x91
INT_VECTOR_DISP_STR	equ 0x92
INT_VECTOR_SEM_P	equ 0x93
INT_VECTOR_SEM_V	equ 0x94

; 导出符号
global	get_ticks
global 	progress_sleep
global	sys_disp_str
global	sem_p
global	sem_v

bits 32
[section .text]

; ====================================================================
;                              get_ticks
; ====================================================================
get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret

progress_sleep:
	mov eax, _NR_prog_sleep
	int INT_VECTOR_PROG_SLEEP
	ret

sys_disp_str:
	mov eax, _NR_disp_str
	int INT_VECTOR_DISP_STR
	ret

sem_p:
	mov eax, _NR_sem_p
	int INT_VECTOR_SEM_P
	ret

sem_v:
	mov eax, _NR_sem_v
	int INT_VECTOR_SEM_V
	ret

