; Ejemplo sintaxis del ensamblador

      li r3, 23
      li r2, -8
      add r1, r2, r3
test: neg r1, r1
      jeqz 100
      li r2, 15
      add r1, r1, r2
      jeqz tag
loop: j loop

tag: jneqzr r2, loop
