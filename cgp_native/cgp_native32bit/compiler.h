//=======================================================================================
//This file was generated by CGP generator (http://www.fit.vutbr.cz/~vasicek/cgp) 
//=======================================================================================

#if !(defined __LP64__ || defined __LLP64__) || defined _WIN32 && !defined _WIN64
 // we are compiling for a 32-bit system
#else
 #error "64-bit architecture is not supported"
#endif

unsigned char* consts;
void cgp_init_consts()
{
    #define B(val)  *(pconst++)=(val)
    unsigned char* pconst;
    pconst = consts = malloc_aligned(1024);
    ///Initialize constants
}


#define MAXCODESIZE 20
typedef void evalfunc(void); 
unsigned char* code[MAX_POPSIZE];

// Native code generation
// -----------------------------------------------------
// The process of CGP genotype compilation contains three sections. 
//
int cgp_compile(unsigned char* pcode, chromosome p_chrom, int* isused) 
{
    #define C(val)  *(pcode++)=(val)
    #define CI(val) {*((uint32_t *)(pcode))= (uint32_t)((__PTRDIFF_TYPE__)val); pcode += sizeof(uint32_t);}

    int pnodeout = 0;
    int in1,in2,fce;
    int out = params.inputs - 1;

    // ### Initialize stack
    // The code that preserves the utilized registers and handles the stack 
    // is generated in the first section.
    C(0x53); //push ebx 
    
    /// Load chromosome ptr to ebx
    C(0xbb);CI(nodeoutput);
    
    // ### Native code generation
    // Then, the CGP chromosome is interpreted and corresponding machine code is generated. The procedure that translates 
    // CGP chromosome to the machine code looks nearly the same as the structure 
    // of linear CGP interpreter. Instead of evaluation of each node, corresponding
    // machine code is generated. 
    //
    for (int i=0; i < params.cols; i++) 
        for (int j=0; j < params.rows; j++) 
        { 
            in1 = *p_chrom++; in2 = *p_chrom++; fce = *p_chrom++; out++;
            #ifdef DONOTEVALUATEUNUSEDNODES
            if (!isused[out]) continue;
            #endif

            // The machine code for the given set of primitive functions was obtained using provided online generator.
            // Register `%ebx` holds the pointer to first item of `nodeoutput` array which stores the node outputs.
            // Variables `in1` and `in2` contain the index of a node that is connected to the first input and second
            // input respectivelly. Variable `out` contains the index of current node.
            switch (fce) 
            {
              case 0: // BUFFER
                 /// data[out] = data[in1];
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 12, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 1: // NOT
                 ///data[out] = ~data[in1];
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0xf7);C(0xd0);                                            //not    %eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 14, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;
                      
              case 2: // AND
                 ///data[out] = data[in1] & data[in2];
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x23);C(0x83);CI(4*in2);                                  //and    in2(%ebx),%eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 18, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 3: // OR
                 ///data[out] = data[in1] | data[in2];
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x0b);C(0x83);CI(4*in2);                                  //or     in2(%ebx),%eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 18, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 4: // XOR
                 ///data[out] = data[in1] ^ data[in2];
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x33);C(0x83);CI(4*in2);                                  //xor    in2(%ebx),%eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 18, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 5: // NAND
                 ///data[out] = ~(data[in1] & data[in2]);
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x23);C(0x83);CI(4*in2);                                  //and    in2(%ebx),%eax
                 C(0xf7);C(0xd0);                                            //not    %eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 20, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 6: // NOR
                 ///data[out] = ~(data[in1] | data[in2]);
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x0b);C(0x83);CI(4*in2);                                  //or     in2(%ebx),%eax
                 C(0xf7);C(0xd0);                                            //not    %eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 20, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              case 7: // XNOR
                 ///data[out] = ~(data[in1] ^ data[in2]);
                 C(0x8b);C(0x83);CI(4*in1);                                  //mov    in1(%ebx),%eax
                 C(0x33);C(0x83);CI(4*in2);                                  //xor    in2(%ebx),%eax
                 C(0xf7);C(0xd0);                                            //not    %eax
                 C(0x89);C(0x83);CI(4*out);                                  //mov    %eax,out(%ebx)
                 ///code size: 20, stack requirements: 0
                 ///registers: %ebx, %eax
                 break;

              default:
                 abort();
            }
    }

    // ### Finalize stack and return
    // Finally, the instructions restoring the values of previously stored registers are generated.  
    C(0x5B); //pop ebx 

    C(0xc3); //ret
}

