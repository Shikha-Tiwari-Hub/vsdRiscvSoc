# Instruction Decoding – factorial.c

| Instruction       | Type | Opcode  | rd   | rs1  | rs2  | funct3 | funct7  | Binary (hex) | Description                      |
|-------------------|------|---------|------|------|------|--------|---------|---------------|---------------------------------|
| addi sp, sp, -32  | C    | 01      | x2   | x2   | —    | —      | —       | 1101          | sp = sp - 32 (compressed)       |
| sd ra, 24(sp)     | S    | 0100011 | —    | x2   | x1   | 011    | —       | ec06          | store x1 (ra) at sp + 24        |
| addi a0, a5, 1952 | I    | 0010011 | x10  | x15  | —    | 000    | —       | 7a078513      | a0 = a5 + 1952                  |
| jal a0, 1054c<printf>| J | 1101111 | x10  | —    | —    | —      | —       | 1ac000ef      | jump to printf, save next in a0 |
| ret               | I    | 1100111 | x0   | x1   | —    | 000    | —       | 8082          | return to address in ra (x1)    |
# Instruction Decoding – max_array.c

| Instruction         | Type | Opcode  | rd   | rs1  | rs2  | funct3 | funct7  | Binary (hex) | Description                         |
|---------------------|------|---------|------|------|------|--------|---------|---------------|--------------------------------------|
| addi sp, sp, -48    | I    | 0010011 | x2   | x2   | —    | 000    | —       | 7179          | Decrease stack pointer by 48 bytes  |
| sd ra, 40(sp)       | S    | 0100011 | —    | x2   | x1   | 011    | —       | f406          | Store return address to stack       |
| addi a5, a5, -16    | I    | 0010011 | x15  | x15  | —    | 000    | —       | ff040713      | a5 = a5 - 16                         |
| bge a5, a4, <target>| B    | 1100011 | —    | x15  | x14  | 101    | —       | 00e7dc63      | Branch if a5 ≥ a4                    |
| lw a4, 0(a5)        | I    | 0000011 | x14  | x15  | —    | 010    | —       | fe842783      | Load word from memory to a4         |
