//Eduarda Trindade 274709
//Jady Feijó 230210

#include "asmgen.h"

void generateAsm(TAC *first, char *fileName)
{
    FILE *fout;
    TAC *tac;
    int numLabels = 0;

    if(!(fout = fopen(fileName,"w")))
    {
        fprintf(stderr," ERROR: Cannot opne file %s for writing!\n",fileName);
        exit(5);
    }

    // Print Fixed Beginning
    fprintf(fout, "# START ASM GEN\n"
	                "\t.section	.rodata\n\n");

    // Print Hash Symbols
    fprintf(fout, "# FOR EACH SYMBOL IN HASH TABLE (EXCEPT LABELS)\n");
    hashPrintAsm(fout);

    fprintf(fout, "\n# STRING\n"
                    ".meuString:\n"
                    "\t.string \"%%d\\n\" \n"
                    "\t.text\n\n");

    // Print Code
    for(tac = first; tac; tac = tac->next)
    {
        switch (tac->type)
        {
            case TAC_BEGINFUN:
                fprintf(fout,   "# BEGIN FUN\n"
                                "\t.globl	%s\n"
                                "\t.type	%s, @function\n" 
                                "%s:\n"
                                "\t.cfi_startproc\n"
                                "\tpushq	%%rbp\n"
                                "\tmovq	%%rsp, %%rbp\n\n",
                                tac->res->text,tac->res->text,tac->res->text);
                break;
            case TAC_ENDFUN:
                fprintf(fout, "# END FUN\n"
                                "\tpopq	%%rbp\n"
                                "\tret\n"
                                "\t.cfi_endproc\n\n");
                break;
            case TAC_RETURN:
                fprintf(fout, "# RETURN\n"
                                "\tmovl	_%s(%%rip), %%eax\n\n",
                                tac->res?tac->res->text:"O");
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
            case TAC_ADD:
                fprintf(fout,"# ADD\n"
                                "\tmovl	_%s(%%rip), %%edx\n"
                                "\tmovl	_%s(%%rip), %%eax\n"
                                "\taddl	%%edx, %%eax\n"
                                "\tmovl	%%eax, _%s(%%rip)\n\n",
                                tac->op1->text,tac->op2->text,tac->res->text);
                break;
            case TAC_SUB:
                fprintf(fout,"# SUB\n"
                                "\t \n\n");
                break;
            case TAC_LESS:
                fprintf(fout,"# LESS\n"
                                "\t \n\n");
                break;
            case TAC_EQ:
                fprintf(fout,"# EQUAL\n"
                                "\tmovl	_%s(%%rip), %%edx\n"
	                            "\tmovl	_%s(%%rip), %%eax\n"
	                            "\tcmpl	%%eax, %%edx\n"
                                "\tjne ",
                                tac->op1->text,tac->op2->text);
                break;
            case TAC_IFZ:
                fprintf(fout,"%s\n\n",tac->res->text);
                break;
            case TAC_LABEL:
                fprintf(fout,"# LABEL\n"
                                "%s:\n\n",
                                tac->res->text);
                break;
            case TAC_JUMP:
                fprintf(fout,"# JUMP\n"
                                "\tjmp\t%s\n\n",
                                tac->res->text);
                break;
            case TAC_SYMBOL:
                break;
            default:
                fprintf(fout,"# NOT FINISHED TAC %d\n\n",tac->type);
                break;
        }
    }

    fprintf(fout, "# FIXED\n"
                    "\t.size	main, .-main\n"
	                "\t.ident	\"GCC: (Ubuntu 7.2.0-18ubuntu2) 7.2.0\"\n"
	                "\t.section	.note.GNU-stack,\"\",@progbits\n");

}