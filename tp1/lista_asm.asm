;; PALABRA
global palabraLongitud
global palabraMenor
global palabraFormatear
global palabraImprimir
global palabraCopiar
	
;; LISTA y NODO
global nodoCrear
global nodoBorrar
global oracionCrear
global oracionBorrar
global oracionImprimir

;; AVANZADAS
global longitudMedia
global insertarOrdenado
global filtrarPalabra
global descifrarMensajeDiabolico

;; YA IMPLEMENTADAS EN C
extern palabraIgual
extern insertarAtras

;; STDIO
extern fputs
extern malloc
extern free
extern fopen
extern fclose
	
;; DEFINES
%define NULL 		0
%define TRUE 		1
%define FALSE 	0

%define LISTA_SIZE 	    	 8 ;un puntero
%define OFFSET_PRIMERO 		 0 ;el único elemento
	
%define NODO_SIZE     		 16 ; dos punteros
%define OFFSET_SIGUIENTE 	 0  ; el primer elemento (tamaño: 8)
%define OFFSET_PALABRA 		 8  ; el segundo elemento (tamaño: 8)


section .rodata
file_mode:	db "a", 0
line_feed:	db 10, 0
oracion_vacia:	db "<oracionVacia>", 10, 0
mensaje_vacio:	db "<sinMensajeDiabolico>", 10, 0
	
section .data
	
section .text
	
	
;; unsigned char palabraLongitud( char *p );
;;      RAX      palabraLongitud(   RDI   );
palabraLongitud:
  xor rax, rax
  .loop:
	  mov cl, [rdi]
	  inc rdi
	  inc rax
	  cmp cl, 0
	  jne .loop
	dec rax
	ret
	
;; bool palabraMenor( char *p1, char *p2 );
;;        RAX       (   RDI   ,   RSI    );
palabraMenor:
  .loop:
	  mov cl, [rdi]
	  mov dl, [rsi]
    ;; si hasta aquí son los dos iguales y dl es 0, entonces cl nunca es menor
	  cmp dl, 0
	  je .false
	  inc rdi
	  inc rsi
	  cmp cl, dl
	  je .loop
	  jl .true
	  jg .false
.true:
 	mov rax, TRUE
  ret
.false:
  mov rax, FALSE
  ret

;; void palabraFormatear( char *p, void (*funcModificarString)(char*) );
;;                      (   RDI  ,                RSI                 )
palabraFormatear:
	push rbp
	mov rbp, rsp
	call rsi		; +++ si hago sólo jump pierdo el ip. cómo lo hago a mano? +++
	pop rbp
	ret

;; void palabraImprimir( char *p, FILE *file );
;;                     (   RDI  ,    RSI     );
palabraImprimir:
	push rbp
	mov rbp, rsp
	push rsi
	call fputs	; +++ puedo usar fputs? o tengo que interrumpir al kernel? [es una tontería igual]
	pop rsi
	mov rdi, line_feed						; jaja fputs no pone linefeed
	call fputs
	pop rbp
	ret

;; char *palabraCopiar( char *p );
;;         RAX       (   RDI   );
palabraCopiar:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	mov r12, rdi
	call palabraLongitud
	add rax, 1 	; agregamos uno para el null termination
	mov r13, rax	; porque malloc no preserva rax

	mov rdi, rax
	call malloc
	mov rcx, r13
	mov r13, rax	; pCop tiene que devolver el rax de malloc: no lo toco
  .loop:				; while rcx != 0
  	cmp rcx, 0
  	je .break
  	dec rcx
  	mov dl, [r12]
  	mov [r13], dl
  	inc r12
  	inc r13
  	jmp .loop
  .break:
 	pop r13
 	pop r12
 	pop rbp
 	ret

;; nodo *nodoCrear( char *palabra );
;;      RAX       (      RDI      ); 
nodoCrear:
	push rbp
	mov rbp, rsp
	push r12
	mov r12, rdi
	mov rdi, NODO_SIZE
	call malloc
	xor rdi, rdi
	mov [rax + OFFSET_SIGUIENTE], rdi
	mov [rax + OFFSET_PALABRA], r12
	pop r12
	pop rbp
	ret

;; void nodoBorrar( nodo *n );
;;                (   RDI   );
nodoBorrar:
	push rbp
	mov rbp, rsp
	push r12
	mov r12, rdi
	mov rdi, [rdi + OFFSET_PALABRA] ; +++ OK, yo esto lo hago así, pero
																	; +++ no me gusta. Libero el char
																	; +++ alocado? y si tengo varios
																	; +++ punteros al mismo char?
	call free
	mov rdi, r12
	call free
	pop r12
	pop rbp
	ret

;; lista *oracionCrear( void );
;;  RAX               (      );
oracionCrear:
	push rbp
	mov rbp, rsp
	mov rdi, LISTA_SIZE
	call malloc
	mov qword [rax], 0
	pop rbp
	ret

;; void oracionBorrar( lista *l );
;;                   (   RDI    );
oracionBorrar:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	mov r12, rdi
	mov rdi, [rdi + OFFSET_PRIMERO]
  .loop:
   	cmp rdi, 0x0
  	je .break
  	mov r13, [rdi + OFFSET_SIGUIENTE]
  	call nodoBorrar
   	mov rdi, r13
	  jmp .loop
  .break:
	mov rdi, r12
	call free
	pop r12
	pop r13
	pop rbp
	ret

;; void oracionImprimir( lista *l, char *archivo, void (*funcImprimirPalabra)(char*,FILE*) );
;;                     (   RDI   ,      RSI     ,                  RDX                     );
oracionImprimir:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	mov r12, [rdi + OFFSET_PRIMERO]
	mov rdi, rsi
	mov r14, rdx
	mov rsi, file_mode ; +++ esto no puede evitarse? es feito
	call fopen
	mov r13, rax
	cmp r12, 0x0
	je .empty
  .loop:
  	cmp r12, 0x0
  	je .break
  	mov rdi, [r12 + OFFSET_PALABRA]
   	mov rsi, r13
 	
  	call r14
  	mov r12, [r12 + OFFSET_SIGUIENTE]
  	jmp .loop

  .empty:
  	mov rsi, r13
  	mov rdi, oracion_vacia
  	call fputs

  .break:
	mov rdi, r13
	call fclose
	pop r14
	pop r13
	pop r12
	pop rbp
	ret


;; float longitudMedia( lista *l );
;; XMM0               (   RDI    );
longitudMedia:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	xor r13, r13
	xor r14, r14
	mov r12, [rdi + OFFSET_PRIMERO]
  .loop:
  	cmp r12, 0x0
  	je .break
  	mov rdi, [r12 + OFFSET_PALABRA]
  	call palabraLongitud
  	add r14, rax
  	inc r13
  	mov r12, [r12 + OFFSET_SIGUIENTE]
  	jmp .loop
  .break:
	cvtsi2ss xmm0, r14 						; +++ esto fue al tuntún
	cvtsi2ss xmm1, r13
	cmp r13, 0
	je .finish
	divss xmm0, xmm1 ; sólo divido si xmm1 no es 0 [o sea, si tengo una palabra]
  .finish:
	pop r14
	pop r13
	pop r12
	pop rbp
	ret


;; void insertarOrdenado( lista *l, char *palabra, bool (*funcCompararPalabra)(char*,char*) );
;;                      (   RDI   ,      RSI     ,                  RDX                     );
insertarOrdenado:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15
	mov r12, rdi
	mov r13, rsi
	mov r15, rdx
	; si el primero es nulo, agrego aquí. no es necesario, pero queda más limpio
	mov r14, [r12 + OFFSET_PRIMERO]  
	cmp r14, 0x0
	je .append
  .loop:
    ;; if next is NULL or GT we append
	  mov r14, [r12 + OFFSET_SIGUIENTE]  
	  cmp r14, 0
	  je .append
	  mov rdi, [r14 + OFFSET_PALABRA]
	  mov rsi, r13
	  call r15
	  cmp rax, 0
	  je .append
    ;; else GOTO next 
  	mov r12, r14
  	jmp .loop
  .append:
	mov rdi, r13
	call nodoCrear
	mov [r12 + OFFSET_SIGUIENTE], rax
	mov [rax + OFFSET_SIGUIENTE], r14
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret

;; void filtrarAltaLista( lista *l, bool (*funcCompararPalabra)(char*,char*), char *palabraCmp );
;;                      (   RDI   ,                   RSI                   ,        RDX       );
filtrarPalabra:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	push r14
	push r15
 	mov rbx, rsi
	mov r12, rdi
	mov r13, rdx
	;; si el primero es nulo, me voy aquí. no es necesario, pero queda más limpio
	mov r14, [r12 + OFFSET_PRIMERO]  
	cmp r14, 0x0
	je .break

  .loop:
    ;; if next is NULL
	  mov r14, [r12 + OFFSET_SIGUIENTE]
	  cmp r14, 0x0
	  je .break
    ;; if next is GT
	  mov rdi, [r14 + OFFSET_PALABRA]
   	mov rsi, r13 
  	call rbx
  	cmp rax, 1
  	je .next
    mov r15, [r14 + OFFSET_SIGUIENTE]
  	mov rdi, r14
  	call nodoBorrar
  	mov [r12 + OFFSET_SIGUIENTE], r15
  	jmp .loop
    ;; GOTO next 
    .next:
  	mov r12, r14
  	jmp .loop
  .break:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret

;; void descifrarMensajeDiabolico( lista *l, char *archivo, void (*funcImpPbr)(char*,FILE* ) );
;;                               (   RDI   ,      RSI     ,             RDX                  );
descifrarMensajeDiabolico:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15
	mov r12, [rdi + OFFSET_PRIMERO]
	mov rdi, rsi
	mov r14, rdx
	mov rsi, file_mode
	call fopen
	mov r13, rax
	cmp r12, 0x0
	je .empty
	xor r15, r15
  .loop:
  	cmp r12, 0x0
  	je .break
  	mov rdi, [r12 + OFFSET_PALABRA]
  	push rdi
  	mov r12, [r12 + OFFSET_SIGUIENTE]
  	inc r15
  	jmp .loop

  .empty:
  mov rsi, r13
  mov rdi, mensaje_vacio
  call fputs
  jmp .exit
	
  .break:
  .loop1:
	  cmp r15, 0x0
	  je .exit
	  dec r15
	  pop rdi
	  mov rsi, r13
	  call r14
	  jmp .loop1
  
  .exit:
	mov rdi, r13
	call fclose
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
	ret
