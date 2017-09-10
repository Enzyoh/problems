#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

typedef array<int, 5> validOption;
struct OptionPair{
  char optionChar;
  int value;
};

typedef vector<OptionPair> possiblePairs;

class Solution
{
private:
  bool alreadyExists(validOption someOption);
  int _currentNumberOptions;
  array< validOption, 1000000> _possibleOptions; //check the main function below to see why there is 100 000 options  
public:  
  //This function returns a unique list of five numbers between 0 - 9 for all 100 000 times we call it, making sure they have not be recorded before
  validOption getFiveUniqueNumberOptions(int currentNumberOptions);

  //This function returns a unique list of five numbers between 0 - 9 which are not in <option>
  validOption getFiveNumberOptionsDifference(validOption option, string earthMatchingOption,string optionString);
  
  //This function returns a unique list of five numbers between 0 - 9  
  validOption getFiveNumberOptions();  

  //This function returns a list of five numbers between 0 - 9 allowing repeats
  validOption getFiveNumberOptionsWithReapeats();  

  //record
  void recordOption(validOption option)
  {
    _possibleOptions[_currentNumberOptions] = option;
  };
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
    someOption = getFiveNumberOptionsWithReapeats();    
    isRepeat = alreadyExists(someOption);
  }  
  while(isRepeat);
  
  return someOption;;
}

bool Solution::alreadyExists(validOption someOption)
{
  bool similar;
  for(int i = 0; i < _currentNumberOptions; i++)
  {
    similar = true;
    for(int j = 0; j < someOption.size(); j++)
    {
      if(someOption[j] != _possibleOptions[i][j])
      {
        similar = false;
        break;
      }
    }
    if(similar) return true;
  }
  return similar;
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

validOption Solution::getFiveNumberOptionsWithReapeats()
{
  validOption option;
  //randomly fill these five numbers
            
  for(int i = 0; i < 5; i++)
  {
    option[i] = rand() % 10;
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

void printOptionPairs(possiblePairs pairs)
{
  for(OptionPair each: pairs)
  {
    cout << each.optionChar << " : " << each.value << ", ";
  }
  cout << endl;
}

int getNumberOccurancesOfChar(char seekedChar, string testString)
{
  int count = 0;
  for(int i = 0; i < testString.size(); i++)
  {
    if(testString[i] == seekedChar) count++;
  }
  return count;
}

void getOptionsForTheOtherChars(int earthSum, int wordsSum, string blobMinusEarthChars, string missingChars, possiblePairs options)
{  
  int missingCharSize = missingChars.size();
  if(missingCharSize == 0)
  {
    if(earthSum == wordsSum)
    {
      printOptionPairs(options);
      cout << "Earth Sum: " << earthSum << "   Other words Sum: " << wordsSum << "\n \n" << endl;
      return; //stopping point for the recursion. Finally we have a solution
    }
  }

  for(int index = 0; index < missingCharSize; index++)
  {    
    OptionPair temp;
    temp.optionChar = missingChars[index];
    int occurances = getNumberOccurancesOfChar(temp.optionChar, blobMinusEarthChars);
    
    for(int option = 0; option < 10; option++)
    {    
      wordsSum += (option * occurances);      
      if(wordsSum > earthSum)
      {
        break;
      }

      temp.value = option;
      options.push_back(temp);

      //some crappy code to convert c++ chars to strings, I'm sure this can be done better
      stringstream ss;
      ss << temp.optionChar;
      string s;
      ss >> s;
      //end of crappy code

      missingChars = Helpers::getStringDiff(missingChars, s);
      return getOptionsForTheOtherChars(earthSum, wordsSum, blobMinusEarthChars, missingChars, options);
    }
  }
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

possiblePairs ConvertToPairs(string fiveLetterWord, validOption option)
{
  possiblePairs temp;

  for(int i = 0; i < option.size(); i++)
  {
    OptionPair optionPair;    

    optionPair.optionChar = fiveLetterWord[i];
    optionPair.value = option[i];

    temp.push_back(optionPair);
  }
  return temp;
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

  //Lets start by putting all these strings into one string
  string blob = NORTH + EAST + SOUTH + WEST;

  //Here we get a string with unique characters
  string unique = Helpers::getUniqueCharacters(blob);
  string charsNotInEarth = Helpers::getStringDiff(unique, EARTH);

  Solution* solution = new Solution();
  validOption earthOption;      
  validOption tempOption;
  bool currentEarthAnOption;
  int wordsSum;
  int earthOptionSum;      
  // Picking five numbers with repeatition
  // there are 10^5 = 100 000 ways we can pick 5 numbers from 10 numbers with repeatition
  for(int instance = 0; instance < 100000; instance++)
  {
    earthOption = solution -> getFiveUniqueNumberOptions(instance); //option VALUES for the FIVE LETTER WORD EARTH
    solution -> recordOption(earthOption);
    wordsSum = 0;
    currentEarthAnOption = true;
    earthOptionSum = getNonNegetiveSum(earthOption);

    for(int wordIndex = 0; wordIndex < words.size() ; wordIndex++)
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
      wordsSum += tempOptionSum;
      if(wordsSum > earthOptionSum)
      {
        currentEarthAnOption = false;
        break;
      }
    }
    if(currentEarthAnOption)
    {
      printValidOption(earthOption);
      string blobMinusEarthChars = Helpers::getStringDiff(blob, EARTH);
      possiblePairs earthPairs = ConvertToPairs(EARTH, earthOption);
      getOptionsForTheOtherChars(earthOptionSum, wordsSum,  blobMinusEarthChars, charsNotInEarth, earthPairs);
    }
}
return 0;
}
