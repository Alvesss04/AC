/*
CPU-Mem architecture
AC 2023/24  LEI FCT/UNL

256 8-bit data words
256 16-bit data words
8 bit addresses (max memory 2^8)
1 acumulator
flags: zero, carry, overflow

16 bit instruction
    4 bits 15-12 opcode
    4 bits 11-8 specification of ALU operaation ALU 00 ADD 01 SUB
    8 bits signed value or address
*/
#include <stdio.h>


extern unsigned char Mem[];
extern unsigned short int Code[];
extern char ac;
extern unsigned char flagZero;
extern unsigned char flagCarry;
extern unsigned char flagOverflow;





void dorun(){
    unsigned short int pc;  // program counter or intruction pointer
    unsigned short int ir;  // instruction register
    unsigned char opcode;
	unsigned char opALU;
	short addressOrValue;
    flagCarry = 0;
    flagOverflow = 0;
	
    pc = 0;
    while( 1 ) {
        ir = Code[pc++];                  // FETCH
        opcode = (unsigned char)(ir >> 12);             // DECODE
		opALU = (unsigned char)((ir & 0x0f00) >> 8);	
        addressOrValue =  ir & 0x00ff;
        char sigBit = ac >> 7;
        char sigBitV = addressOrValue >> 7;
        char sigBitA = (signed)Mem[addressOrValue] >> 7;
        unsigned char unAC;

    
        
        
        switch( opcode ){              // EXECUTE
            case 0x0F:   /* HALT */
                printf("HALT instruction executed\n");
                return;

            case 0x00: /* NOOP */
            
                break;
     
            
            case 0x01: /* ADDI SUBI*/
		        
                //ADDI
                if(opALU == 0){
                    unAC = (unsigned)ac + (unsigned)addressOrValue;
                    if	(unAC < ac){
                    	flagCarry = 1;
                    }else{
                        flagCarry = 0;
                    }
                    		
                    ac += addressOrValue;
                    if(sigBit == 0 && sigBitV == 0 ){
                        if (ac < 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }else if(sigBit == 1 && sigBitV == 1){
                        if (ac > 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }
				
                
                }
                //SUBI
                else {
		            unAC = (unsigned)ac - (unsigned) addressOrValue;	
		            if	(unAC > ac){
		            flagCarry = 1;
		            }else{
                        flagCarry = 0;
                    }
		    
                    ac -= addressOrValue;

                    if(sigBit == 0  && sigBitV == 1){
                        if (ac < 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }else if(sigBit == 1 && sigBitV == 0){
                        if (ac > 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }
                


                }

                break;
            
            case 0x02: /* ADD, SUB */
                //ADD
                if(opALU == 0){
                    unAC = (unsigned)ac + (unsigned)Mem[addressOrValue];
                    if	(unAC < ac){
                    	flagCarry = 1;
                    }else{
                        flagCarry = 0;
                    }
                  
                    		
                    ac += Mem[addressOrValue];
                    if(sigBit == 0 && sigBitA == 0){
                        if (ac < 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }else if(sigBit == 1 && sigBitA == 1){
                        if (ac >0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }
                
				
                
                }
                //SUB
                else {
		            unAC = (unsigned)ac - (unsigned)Mem[addressOrValue];	
		            if	(unAC > ac){
		            flagCarry = 1;
		            }else{
                        flagCarry = 0;
                    }
		    
                    ac -= Mem[addressOrValue];
                    if(sigBit == 0  && sigBitA == 1){
                        if (ac < 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }else if(sigBit == 1 && sigBitA == 0){
                        if (ac > 0){
                            flagOverflow = 1;
                        }else{
                            flagOverflow = 0;
                        }
                    }
                }

                              
                
                break;
            
            case 0x03: /* CLAC */
                ac = 0;
                flagZero = 1;
                break;
            
            case 0x04: /* STORE */

                Mem[addressOrValue] = ac;
   
                break;
			
	      case 0x05: /* BEQZ */

            if(ac == 0){
                pc = addressOrValue;
            }
 
                break;
	     
            default:
                printf("Invalid instruction!\n");
                return;
        }
    }
}
