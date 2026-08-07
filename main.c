/* main.c */

/* CPU starts in 16-bit real mode after reset. We need to tell the assembler to interpret the following code in 16-bit
** mode
*/

 asm(
    //".code16gcc\n" 
    "call main\n"
    "call exit\n"
);

#include <gui.h>


void main(){

}
