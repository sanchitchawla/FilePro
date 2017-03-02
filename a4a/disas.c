# include <stdio.h>

#define mask 0x03


enum name {RAX, RCX, RDX, RBX, RSP,RBP,RSI,RDI};

void diassemble(const unsigned char* raw_instr){

	if (raw_instr[0]== 0x68){

		for (int i = 0;i < 5; i++){
			printf("%0x", raw_instr[i]);
		}
		printf("pushq %0x\n", *((int*)) &raw_instr[1]);

	}
	else if (raw_instr[0]<=0x57){

	}

}

void print(){

}