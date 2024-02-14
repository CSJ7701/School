#include <stdio.h>

int main(int argc, char ** argv) {

  //Your code goes here

int T_Counter = 0;
int H_Counter = 0;
char Current;

while(!feof(stdin)) // While not end of file, read stdin
{
  Current = getchar(); // Read the current character through while loop, save to variable.
if(Current == 'T') {T_Counter++;} // If current char t, add 1 to T_Counter

else if(Current == 'H') {H_Counter++;} // If current char h, add 1 to H_Counter

 else {printf("Unrecognized Char\n");} // Print error message for unrecognized character. 
}
printf("\nT's count is : %d\n", T_Counter);
printf("\nH's count is : %d\n", H_Counter);
}
