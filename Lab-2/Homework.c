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

int main() {

  int Longest_H = 0;
  int Longest_T = 0;
  int CurrentRun = 0;
  char Winner;
  
  while (!feof(stdin)) //Runs while loop while not end of file
    {
      char CurrentChar = getchar(); // Gets current Char
      char PrevChar;
      if (CurrentChar !='T' && CurrentChar !='H')
	{continue;} // Skips character if neither H nor T


      if (CurrentChar == PreviousChar && CurrentChar == 'H')
	{
	  CurrentRun++;
	  if (CurrentRun>Longest_H)
	    {Longest_H = CurrentRun}
	} //Checks if we have repetition, and whether its an H. If its repeated, increase the current run length. Checks whether the current run is longer than the longest run, and resets longest H run if so.
      if (CurrentChar == PreviousChar && CurrentChar == 'T')
	{
	  CurrentRun++;
	  if (CurrentRun>Longest_T)
	    {Longest_T = CurrentRun}
	} //Checks if we have repetition, and whether its an T. If its repeated, increase the current run length. Checks whether the current run is longer than the longest run, and resets longest T run if so.

      
      if (CurrentChar != PreviousChar)
	{
	  CurrentRun = 1;
	} //Checks if we have ended the run, and sets the current length to 1. 

      PreviousChar = CurrentChar; // Sets the previous character before incrementing. 
    } // End of while loop






  if (Longest_H == Longest_T) {print B, length}
  if (Longest_T > Longest_H) {print T, length}
  if (Longest_H > Longest_T) {print H, length}
  
  return(0);
}
