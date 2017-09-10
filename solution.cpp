#include <iostream>
#include <string>
#include <array>

using namespace std;

typedef array<int, 5> validOption;

class Solution
{
private:
  bool alreadyExists(validOption someOption);
  validOption getFiveNumberOptions();
  int _currentNumberOptions;
  array< validOption, 252> possibleOptions; //check the main function below to see why there is 252 options  
public:
  
  //This function returns a unique list of five numbers between 0 - 9 for all 252 times we call it
  validOption getFiveUniqueNumberOptions(int currentNumberOptions);
  validOption getFiveNumberOptionsDifference(validOption option, string earthMatchingOption,string optionString);
};


class Helpers
{
private:
public:
  static string getUniqueCharacters(string blob);
  static string getStringDiff(string first, string second);
};

string Helpers::getStringDiff(string first, string second)
{
  string temp;
  bool append;
  for(char eachChar : first)
  {
    append = true;
    for( char eachChar2 : second)
    {
      if(eachChar == eachChar2)
      {
        append = false;
        break;
      }
    }
    if(append){
      temp +=eachChar;
    }
  }

  return temp;
}

//This helper function takes a string and returns a new string with no repeating characters
//It is not very optimal but does the job using a brute force algorithm 
string Helpers::getUniqueCharacters(string blob)
{
  string uniqueChars;   
  bool shouldAdd = false;

  //outer for loop goes through all characters of the string
  for(int i=0;i < blob.size();i++)
  {
    //everytime we move allong the concatenated string, we assume we can add the character (we are still to check)
    shouldAdd = true;
    //This goes through the building up string to check if has the character to add
    for(int j=0; j < uniqueChars.size(); j++)
    {
      //If the character is already added to unique chars move on
      if(uniqueChars[j] == blob[i])
      {
        // set this so we do not add to the new string is this character has already been added
        shouldAdd = false;  
        break;
      }
    }
    if(shouldAdd)  
      {
        uniqueChars += blob[i];
      }      
  }
  return uniqueChars;
}

validOption Solution::getFiveUniqueNumberOptions(int currentNumberOptions)
{
  _currentNumberOptions = currentNumberOptions;
  validOption someOption;
  bool isRepeat = false;
  do
  {
    someOption = getFiveNumberOptions();    
    //we do not generate a new set of numbers if this is a unique set
    isRepeat = alreadyExists(someOption);
  }  
  while(isRepeat);
  
  return someOption;;
}

bool Solution::alreadyExists(validOption someOption)
{
  bool similarOptions = false;  

  for(int i = 0; i < _currentNumberOptions;i++)
  {
    similarOptions = true;
    for(int j = 0; j < 5; j++)
    {
      if(someOption[j] != possibleOptions[i][j])
      {
        //break out as soon as you realise some indices are not similar
        similarOptions = false;
        break;
      }
    }
  }
  return similarOptions;
}

validOption Solution::getFiveNumberOptions()
{
  validOption option = {-1, -1, -1, -1, -1};
  bool skip = false;
  int numberOfPickedNumbers = 0;
  //randomly fill these five numbers
  while(numberOfPickedNumbers < 5)
  {
      skip = false;

      //get a random number between 0 to 10
      int candidate = rand() % 10;
            
      for(int i = 0; i < 5; i++)
      {
        //if we've already picked this number, skip it
        if( option[i] != -1 && option[i] == candidate) 
        {
          skip = true;
          break;
        }
      }
      if(!skip) 
      {
        //add the picked number to the list
        numberOfPickedNumbers++;
        option[numberOfPickedNumbers-1] = candidate;;
      }
  }    
  return option;
}

validOption Solution::getFiveNumberOptionsDifference(validOption option, string earthMatchingOption,string optionString)
{
  validOption returnOption;
  bool addOption;
  int currIndex = 0;
  for(int index = 0; index < (optionString.size() + earthMatchingOption.size()); index++)
  {
    addOption = true;
    for(int optionIndex: option)
    {
      if(optionIndex == index)
      {
        addOption = false;
        break;
      }
    }
    if(addOption)
    {
      returnOption[currIndex] = index;
      currIndex++;
    }
  }
  return returnOption;
}

int getNonNegetiveSum(validOption option)
{
  int sum = 0;
  for(int i = 0; i < 5; i++)
  {
    if(option[i] != -1)
      sum += option[i];
  }
  return sum;
}

void printValidOption(validOption option)
{
  for(int i = 0; i < option.size(); i++)
  {
    cout << option[i] << " ";
  }
  cout << endl;
}

array<int, 10> mergeOptions(validOption one, validOption two)
{
  array<int, 10> temp;
  for(int each = 0; each < (one.size() + two.size()); each++)
  {
    if(each < one.size())
      temp[each] = one[each];
    else
      temp[each] = two[each - one.size()];
  }
  return temp;
}

int main()
{
      //just as a note* const optimizes this variable during compile time, telling the c++ compiler that this 
      //variable will not change during the runtime of the program.
      const string NORTH = "NORTH";
      const string EAST = "EAST";
      const string SOUTH = "SOUTH";
      const string WEST = "WEST";
      
      const string EARTH = "EARTH";

      array<string, 4> words = {NORTH, EAST, SOUTH, WEST};

      //Lets start by putting all this strings into on string
      string blob = NORTH + EAST + SOUTH + WEST;

      //Here we get a string with unique characters

      string unique = Helpers::getUniqueCharacters(blob);
      string charsNotInEarth = Helpers::getStringDiff(unique, EARTH);

      //assuming no repeatitions, there are N c R (N combination R) ways to pick r unique objects from N objects
      //There are 10 combination 5 ways to choose individual characters of "earth" from 10 values.
      // Possible Options = 10 C 5 = 252
      //again this is not a very big number so we can run an exhaustive agorithm but be a little clever to break out early

      Solution* solution = new Solution();
      validOption earthOption;      
      validOption tempOption;
      bool currentEarthAnOption;
      int wordsSum;
      int earthOptionSum;      

      for(int instance = 0; instance < 252; instance++)
      {
        earthOption = solution -> getFiveUniqueNumberOptions(instance); //option VALUES for the FIVE LETTER WORD EARTH
        
        earthOptionSum = 0;
        currentEarthAnOption = true;
        wordsSum = 0;

        for(int i = 0; i < 5; i++)
        {
          //calculate the earth sum
          earthOptionSum += earthOption[i];
        }
        for(int wordIndex = 0; wordIndex < words.size() && currentEarthAnOption; wordIndex++)
        {          
          tempOption.fill(-1);              
          
          for(int i = 0; i < EARTH.size(); i++)
          {
            for(int charIndex = 0; charIndex < words[wordIndex].size();charIndex++)
            {
              if(EARTH[i] == words[wordIndex][charIndex])
               {
                 //assign the values on the other words where the characters are the same
                 tempOption[charIndex] = earthOption[i];
               }
            }
          }
          
          int tempOptionSum = getNonNegetiveSum(tempOption);
          wordsSum +=tempOptionSum;
          if(wordsSum > earthOptionSum)
          {
            currentEarthAnOption = false;
            break;
          }

        }
        validOption somePossibleOption = solution -> getFiveNumberOptionsDifference(earthOption, EARTH, charsNotInEarth);

        cout << "EARTH option!" << endl;
        printValidOption(earthOption);

        cout << "Complimentary option for "<< charsNotInEarth << endl;
        printValidOption(somePossibleOption);

        array<int, 10> possibleOptionFinalSolution = mergeOptions(earthOption, somePossibleOption);
      }

      return 0;
}
