; Programa de verificación de operaciones con pseudoinstrucciones

      li r1, 10       ; Cargar 10 en r1
      li r2, -5       ; Cargar -5 en r2
      add r3, r1, r2  ; r3 = r1 + r2 = 10 + (-5) = 5
      sub r4, r3, r1  ; r4 = r3 - r1 = 5 - 10 = -5
      neg r4, r4      ; r4 = -(-5) = 5 (debería ser igual a r3)
      sub r5, r4, r3  ; r5 = r4 - r3, debería ser 0
      jneqz error     ; Si r5 no es 0, hay error

; Prueba de operaciones lógicas
      li r6, 3        ; Cargar 3 (0b11) en r6
      li r7, 5        ; Cargar 5 (0b101) en r7
      and r8, r6, r7  ; r8 = 3 AND 5 = 1
      li r9, 1        ; Cargar valor esperado en r9
      sub r10, r8, r9 ; r10 = r8 - r9, debería ser 0
      jneqz error     ; Si r10 no es 0, hay error

      or r11, r6, r7  ; r11 = 3 OR 5 = 7
      li r12, 7       ; Cargar valor esperado en r12
      sub r13, r11, r12 ; r13 = r11 - r12, debería ser 0
      jneqz error     ; Si r13 no es 0, hay error

; Bucle anidado de prueba
      li r14, 3       ; Contador externo
outer_loop:
      li r15, 2       ; Contador interno
inner_loop:
      sub r15, r15, r9 ; r15 -= 1
      jneqzr r15, inner_loop ; Repite mientras r15 != 0
      sub r14, r14, r9 ; r14 -= 1
      jneqzr r14, outer_loop ; Repite mientras r14 != 0

; Si llegamos aquí, todas las pruebas pasaron
      j success

error:
      li r16, -1      ; Indicar error
      j error         ; Bucle infinito en caso de fallo

success:
      j success       ; Bucle infinito indicando éxito