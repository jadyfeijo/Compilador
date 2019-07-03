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
	                "\t.section	.rodata\n\n");
    fprintf(fout, "# STRING\n"
                    ".meuString:\n"
                    "\t.string \"%%d\\n\" \n"
                    "\t.text\n\n");

    // Print Hash Symbols
    fprintf(fout, "# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)\n"
                    "_I: .long 1\n\n");

    // Print Code
    //fprintf(fout, "");

    for(tac = first; tac; tac = tac->next)
    {
        switch (tac->type)
        {
        case TAC_BEGINFUN:
            fprintf(fout,   "# BEGIN FUN\n"
                            "\t.globl	main\n" 
                            "main:\n"
	                        "\t.cfi_startproc\n"
	                        "\tpushq	%%rbp\n"
	                        "\tmovq	%%rsp, %%rbp\n"
	                        "\tsubq	$16, %%rsp \n\n");
            break;
        case TAC_ENDFUN:
            fprintf(fout, "# END FUN\n"
	                        "\tmovl	$0, %%eax\n"
	                        "\tleave\n"
	                        "\tret\n"
	                        "\t.cfi_endproc\n\n");
            break;
        case TAC_PRINT:
            fprintf(fout, "# PRINT\n"
	                        "\tmovl	_%s(%%rip), %%eax\n"
	                        "\tmovl	%%eax, %%esi\n"
	                        "\tleaq	.meuString(%%rip), %%rdi\n"
	                        "\tmovl	$0, %%eax\n"
	                        "\tcall	printf@PLT\n\n",
                            tac->res?tac->res->text:"");
            break;
        case TAC_COPY:
            fprintf(fout, "# COPY\n"
                            "\tmovl	_%s(%%rip), %%eax\n"
						    "\tmovl	%%eax, _%s(%%rip)\n\n", 
                            tac->op1->text, tac->res->text);
            break;
        default:
            break;
        }
    }

    fprintf(fout, "# FIXED\n"
                    "\t.size	main, .-main\n"
	                "\t.ident	\"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0\"\n"
	                "\t.section	.note.GNU-stack,\"\",@progbits\n");

}