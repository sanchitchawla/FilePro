# include <stdio.h>

#define mask 0x07
#define mask2 0x38
#define mask3 0xc0


enum name {RAX, RCX, RDX, RBX, RSP,RBP,RSI,RDI};

char* sca[] = {"1","2","4","8"}; 

void print(char raw_instr){

	switch(raw_instr & mask){
	case RAX:
		printf("%%rax");
		break;
	case RCX:
		printf("%%rcx");
		break;
	case RDX:
		printf("%%rdx");
		break;
	case RBX:
		printf("%%rbx");
		break;
	case RSP:
		printf("%%rsp");
		break;
	case RBP:
		printf("%%rbp");
		break;
	case RSI:
		printf("%%rsi");
		break;
	case RDI:
		printf("%%rdi");
		break;

	}
}


void disassemble(const unsigned char* raw_instr){

	if (raw_instr[0]== 0x68){

		for (int i = 0;i < 5; i++){
			printf("%.2x ", raw_instr[i]);
		}
		printf("\tpushq $%#x\n", *(int*)&raw_instr[1]);

	}
	else if (raw_instr[0]<=0x57){
		printf("%.2x\t", raw_instr[0]);
		printf("pushq ");
		print(raw_instr[0]);
		printf("\n");
	}

	else if (raw_instr[0]<=0xff && raw_instr[1]<= 0x37){
		printf("%.2x %.2x \t", raw_instr[0], raw_instr[1]);
		printf("pushq (");
		print(raw_instr[1]);
		printf(")\n");

	}
	else if (raw_instr[3]==0x00){
		printf("%.2x %.2x %.2x \t", raw_instr[0], raw_instr[1], 
												raw_instr[2]);
		printf("pushq %#x(", raw_instr[2]);
		print(raw_instr[1]);
		printf(")\n");
	}
	else{
		printf("%.2x %.2x %.2x %.2x\t", raw_instr[0], raw_instr[1],
		 								raw_instr[2], raw_instr[3]);
		printf("pushq %#x(", raw_instr[3]);
		print(raw_instr[2]);
		printf(",");
		print(raw_instr[2]>>3);
		char t = (raw_instr[2] & mask3)>>6;
		printf(",%s)\n", sca[t]);

	}


}
