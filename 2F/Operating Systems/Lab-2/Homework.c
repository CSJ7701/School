/*
$$\   $$\                                                                     $$\               $$\   
$$ |  $$ |                                                                    $$ |            $$$$ |  
$$ |  $$ | $$$$$$\  $$$$$$\$$$$\   $$$$$$\  $$\  $$\  $$\  $$$$$$\   $$$$$$\  $$ |  $$\       \_$$ |  
$$$$$$$$ |$$  __$$\ $$  _$$  _$$\ $$  __$$\ $$ | $$ | $$ |$$  __$$\ $$  __$$\ $$ | $$  |        $$ |  
$$  __$$ |$$ /  $$ |$$ / $$ / $$ |$$$$$$$$ |$$ | $$ | $$ |$$ /  $$ |$$ |  \__|$$$$$$  /         $$ |  
$$ |  $$ |$$ |  $$ |$$ | $$ | $$ |$$   ____|$$ | $$ | $$ |$$ |  $$ |$$ |      $$  _$$<          $$ |  
$$ |  $$ |\$$$$$$  |$$ | $$ | $$ |\$$$$$$$\ \$$$$$\$$$$  |\$$$$$$  |$$ |      $$ | \$$\       $$$$$$\ 
\__|  \__| \______/ \__| \__| \__| \_______| \_____\____/  \______/ \__|      \__|  \__|      \______|
                                                                                                      
A simple c script meant to process a string of characters through STDIN, searching for the longest string of either H or T.
Script will return H if the longest string consists of H's, T if T's, and B if there are two strings of H's and T's of equal length.
Script will also return the length of the longest string.

This program requires only C and a C compiler. In order to run, the code must first be compiled, then the output file should function.

In order for this program to run properly, input must be send to the script via STDIN (using a pipe)
e.g. =cat inputfile | program_executable=

Results:
When run with the small text file: "T, 7"
When run with the large text file: "B, 14"
*/



#include <stdio.h>

int main() {

  int Longest_H = 0;
  int Longest_T = 0;
  int CurrentRun = 0;
  char CurrentChar;
  char PreviousChar = '\0'; // Initialize PreviousChar to a default value

  //printf("Begin\n"); // Present for debugging. Uncomment to check beginning. 
  
  while (!feof(stdin)) // 
    {
      CurrentChar = getchar();
      if (CurrentChar != 'T' && CurrentChar != 'H')
	{
	  //printf("Char Not Recognized\n"); // Present for Debugging. Uncomment to check each character individually. 
	  continue;
	} // Skips character if neither H nor T

      if (CurrentChar == PreviousChar && CurrentChar == 'H')
	{
	  CurrentRun++;
	  if (CurrentRun > Longest_H)
	    {
	      Longest_H = CurrentRun;
	    }
	  //printf("H, %d\n", CurrentRun); // Present for Debugging. Uncomment to check each character individually. 
	} // Checks if we have repetition and whether it's an H. If it's repeated, increase the current run length. Checks whether the current run is longer than the longest run and resets the longest H run if so.

      if (CurrentChar == PreviousChar && CurrentChar == 'T')
	{
	  CurrentRun++;
	  if (CurrentRun > Longest_T)
	    {
	      Longest_T = CurrentRun;
	    }
	  //printf("T, %d\n", CurrentRun); // Present for Debugging. Uncomment to check each character individually.
	} // Checks if we have repetition and whether it's a T. If it's repeated, increase the current run length. Checks whether the current run is longer than the longest run and resets the longest T run if so.

      if (CurrentChar != PreviousChar)
	{
	  CurrentRun = 1;
	  //printf("Switch\n"); // Present for Debugging. Uncomment to check each character individually.
	} // Checks if we have ended the run and sets the current length to 1.

      PreviousChar = CurrentChar; // Sets the previous character before incrementing.
    } // End of while loop

  if (Longest_H == Longest_T) {printf("B, %d\n", Longest_H);}
  if (Longest_T > Longest_H) {printf("T, %d\n", Longest_T);}
  if (Longest_H > Longest_T) {printf("H, %d\n", Longest_H);}

  return 0;
}
