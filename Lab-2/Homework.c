/*
$$\   $$\                                                                     $$\               $$\   
$$ |  $$ |                                                                    $$ |            $$$$ |  
$$ |  $$ | $$$$$$\  $$$$$$\$$$$\   $$$$$$\  $$\  $$\  $$\  $$$$$$\   $$$$$$\  $$ |  $$\       \_$$ |  
$$$$$$$$ |$$  __$$\ $$  _$$  _$$\ $$  __$$\ $$ | $$ | $$ |$$  __$$\ $$  __$$\ $$ | $$  |        $$ |  
$$  __$$ |$$ /  $$ |$$ / $$ / $$ |$$$$$$$$ |$$ | $$ | $$ |$$ /  $$ |$$ |  \__|$$$$$$  /         $$ |  
$$ |  $$ |$$ |  $$ |$$ | $$ | $$ |$$   ____|$$ | $$ | $$ |$$ |  $$ |$$ |      $$  _$$<          $$ |  
$$ |  $$ |\$$$$$$  |$$ | $$ | $$ |\$$$$$$$\ \$$$$$\$$$$  |\$$$$$$  |$$ |      $$ | \$$\       $$$$$$\ 
\__|  \__| \______/ \__| \__| \__| \_______| \_____\____/  \______/ \__|      \__|  \__|      \______|
                                                                                                      
  Flips a coin, H = Heads , T = Tails
  Count which result has the longest un-interrupted run
  Input will be a text file

  Read the file from STDIN, report result and stats to STDOUT, report errors to STDERR

  Function - 'longestRun'. Reads characters from STDIN and analyzes them to find longest number of consecutive heads or tails.
  MUST display 2 values:
  - number of max consecutive for winner
  - character (H or T) depending on what won. If tie, print B.

  Program should read file through STDIN:
  - cat myinputfile.txt | myprogram

  feof(stdin) - returns true if reached end of file
  while (!feof(stdin))
  {

  }


_________          _______           _______          _________ _______ 
\__   __/|\     /|(  ___  )|\     /|(  ____ \|\     /|\__   __/(  ____ \
   ) (   | )   ( || (   ) || )   ( || (    \/| )   ( |   ) (   | (    \/
   | |   | (___) || |   | || |   | || |      | (___) |   | |   | (_____ 
   | |   |  ___  || |   | || |   | || | ____ |  ___  |   | |   (_____  )
   | |   | (   ) || |   | || |   | || | \_  )| (   ) |   | |         ) |
   | |   | )   ( || (___) || (___) || (___) || )   ( |   | |   /\____) |
   )_(   |/     \|(_______)(_______)(_______)|/     \|   )_(   \_______)
                                                                        

As long as the file isn't over, check a character.
If that character isn't H or T, ignore it.

Check characters value



   
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
