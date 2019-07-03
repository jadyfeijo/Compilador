//Eduarda Trindade 274709

#include "asmgen.h"

void generateAsm(TAC *first, char *fileName)
{
    FILE *fout;
    TAC *tac;

    if(!(fout = fopen(fileName,"w")))
    {
        fprintf(stderr," ERROR: Cannot opne file %s for writing!\n",fileName);
        exit(5);
    }

    // Print Fixed Beginning
    fprintf(fout, "# START ASM GEN\n"
	                ".section	.rodata\n\n");
    fprintf(fout, "# STRING\n"
                    ".meuString:\n"
                    ".string \"%%d\\n\" \n"
                    ".text\n\n");

    // Print Hash Symbols
    fprintf(fout, "# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)\n"
                    "_I: .long 1\n\n");

    // Print Code
    //fprintf(fout, "");

    for(tac = first; tac; tac = tac->next)
    {
        switch (tac->type)
        {
        case TAC_PRINT:
            fprintf(fout, "# PRINT\n"
	                        "movl	_%s(%%rip), %%eax\n"
	                        "movl	%%eax, %%esi\n"
	                        "leaq	.meuString(%%rip), %%rdi\n"
	                        "movl	$0, %%eax\n"
	                        "call	printf@PLT\n\n",
                            tac->res?tac->res->text:"");
            break;
        case TAC_BEGINFUN:
            fprintf(fout,   "# BEGIN FUN\n"
                            ".globl	main\n" 
                            "main:\n"
	                        ".cfi_startproc\n"
	                        "pushq	%%rbp\n"
	                        "movq	%%rsp, %%rbp\n"
	                        "subq	$16, %%rsp \n\n");
            break;
        case TAC_ENDFUN:
            fprintf(fout, "# END FUN\n"
	                        "movl	$0, %%eax\n"
	                        "leave\n"
	                        "ret\n"
	                        ".cfi_endproc\n\n");
            break;
        case TAC_COPY:
            fprintf(fout, "\n\n");
            break;
        default:
            break;
        }
    }

    fprintf(fout, "# FIXED\n"
                    ".size	main, .-main\n"
	                ".ident	\"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0\"\n"
	                ".section	.note.GNU-stack,\"\",@progbits\n");

}