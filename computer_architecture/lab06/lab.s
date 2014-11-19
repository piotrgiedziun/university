.MODEL SMALL
.386P
.DATA
EXECUT EQU 10011010b
RDWRDATA EQU 10010010b
STACKSEG EQU 10010110b
SEGVIDEO EQU 00100000b

STATUS_PORT EQU 64h
A20_PORT EQU 0d1h
A20_ON EQU 0dfh
A20_OFF EQU 0ddh
KBD_PORT_A EQU 60h

GblDT   DW 0, 0, 0, 0
        DW 0, 0, 0, 0
        DW 0, 0, 0, 0
        DW 0, 0, 0, 0
        DW 0, 0, 0, 0 ; segment g

GblDscTbl DW 5 * 8 - 1
          DD 0
        .CODE
        
Start   PROC
        mov ax, SEG _DATA
        mov ds, ax
        mov si, OFFSET GblDT

        add si, 8
        mov bx, 0FFFFh
        mov cx, RDWRDATA
        call SetDscrpt
        
        mov ax, SEG _TEXT
        add si, 8
        mov bx, 0FFFFh
        mov cx, EXECUT 
        call SetDscrpt

        mov ax, SEG SSEG
        add si, 8
        mov bx, 0FFFFh
        mov cx, RDWRDATA
        call SetDscrpt
	
        ; add segment g (dodatkowy segment)
        call GoProtect
        
        ; zadania w trybie chrnionionym
        call GoReal
        mov ah, 4Ch ; rozkaz zakonczenia programu
        int 21h
Start ENDP

SetDscrpt PROC
        mov dl, ah
        shl ax, 4
        shr dl, 4
        mov WORD PTR [si], bx
        mov WORD PTR [si+2], ax
        mov BYTE PTR [si+4], dl
        mov WORD PTR [si+5], cx
        mov BYTE PTR [si+7], 0
        ret
SetDscrpt ENDP

PrintText PROC
	; get cursor pos
	mov     ah, 03h
	mov     bh, 00h
	int     10h
	mov [bp - 4], dx

	; print b
	mov    ax, 0962h
	mov    bx, 001ah
	mov    cx, 0001h
	int    10h

	; move cursor
	INC		DL
	MOV     AH, 2
	INT     10H

	;print y
	mov    ax, 0979h
	int    10h

	; move cursor
	INC		DL
	MOV     AH, 2
	INT     10H

	;print e
	mov    ax, 0965h
	int    10h

	; move cunrsor
	INC		DL
	MOV     AH, 2
	INT     10H

	;print !
	mov    ax, 0921h
int    10h
PrintText ENDP

GoProtect PROC
        call enable_a20
        mov ax, SEG _DATA
        mov dl, ah
        shl ax, 4
        shr dl, 4
        sub dh, dh
        add ax, OFFSET GblDT
        adc dl, 0
        mov GblDscTbl+2, ax
        mov GblDscTbl+4, dx
        lgdt PWORD PTR GblDscTbl
        cli
        smsw ax
        and ax, 1Fh
        or ax, 1
        lmsw ax
        DB 0EAh
        DW ClearPF
        DW 10h
ClearPF:
        mov ax, 8
        mov ds, ax
        mov ax, 18h
        mov ss, ax
        ret
GoProtect ENDP

GoReal  PROC
        mov eax, CR0
        and eax, 07FFFFFFEh
        mov CR0, eax
        DB 0EAh
        DW ClearPF2
        DW _TEXT
ClearPF2:
        mov ax, SEG DGROUP
        mov ds, ax
        mov ax, SEG SSEG
        mov ss, ax
        sti
        call disable_a20
        ret
GoReal  ENDP
enable_a20 PROC NEAR
        mov al, A20_PORT
        out STATUS_PORT, al
        mov al, A20_ON
        out KBD_PORT_A, al
        ret
ENDP    enable_a20
disable_a20 PROC NEAR
        mov al, A20_PORT
        out STATUS_PORT, al
        mov al, A20_OFF
        out KBD_PORT_A, al
        ret
ENDP    disable_a20

SSEG SEGMENT WORD STACK USE16 'STACK'
        DB 1024 DUP (?)
SSEG ENDS
END
