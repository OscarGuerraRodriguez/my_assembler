# Custom assembler

## Syntax
### Basic mnemonics
- **id** dest_reg op_reg1 op_reg2: identity ALU operation
- **not** dest_reg op_reg1 op_reg2: not ALU operation
- **add** dest_reg op_reg1 op_reg2: sum ALU operation
- **sub** dest_reg op_reg1 op_reg2: substraction ALUM operation
- **and** dest_reg op_reg1 op_reg2: and ALU  operation
- **or** dest_reg op_reg1 op_reg2: or ALU operation
- **nega** dest_reg op_reg1 op_reg2: negates op_reg1
- **negb** dest_reg op_reg1 op_reg2: negates op_reg2
- **li** dest_reg inm: loads inm into dest_reg
- **j** dir: inconditional jump to dir
- **jeqz** dir: jumps to dir if last ALU operation enabled the zero flag
- **jneqz** dir: jumps to dir if last ALU operation didn't enable the zero flag
### Pseudoisntructions
- **ident** dest_reg op_reg, : stores op_reg in dest_reg
- **neg** dest_reg op_reg: stores -op_reg in dest_reg
- **jeqzr**: conditional jump, that compares a given register to 0
- **jneqzr** reg dir: conditional jump, that compares a given register to 0

