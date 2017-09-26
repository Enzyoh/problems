import copy

class Solution:
    """A solution class to calculate the positional sum of the strings NORTH, EAST, SOUTH, WEST that equal to EARTH. This is when all numbers are chosen in the range [0 - 9]."""
    __durationInMs = 0;
    def __init__(self):
        #timer create
        print("=====start=====\n")
        
    def replaceOccuranceOfChar(self, words, dictionary, option, value, positionInEarth):
        for i in range(4):
            for j in range(5):
                if(words[i][j] == option):
                    words[i][j] = value
                    dictionary[option] = value
        return words
    
    def isColumnDone(self, words, position):
        for i in range(4):
            if(isinstance(words[i][position], str)):
                return i;
        return -1

    def getNextMissingColumnChar(self, words, position):
        for i in range(4):
            if(isinstance(words[i][position], str)):
                return words[i][position];
        return ""

    def completeCurrentColumn(self, words, carry, earthDigitOption, position):
        columnSum = carry + words[0][position] + words[1][position] + words[2][position] + words[3][position]
        carry = 0
        if(columnSum > 9):
            carry = columnSum // 10
            columnSum = columnSum % 10            
        if(columnSum == earthDigitOption):
            if(position == 0 and carry > 0):
                return []
            newPosition = position - 1
            return [carry, newPosition, position];
        return []
        
    def getPossibleCombinations(self, earth, dictionary, words, position, lastPosition, carry, possibleDigits):
        #print("getPossibleCombinations: position, pozibleOptions, earth: ", position, possibleDigits, earth)
        columnCompleted = self.isColumnDone(words, position) == -1

        #===========Optimizations to break recursion earlier========
        #
        #
        # E can not be 1 (zero + plus any positive number greater one can not give 1
        if(dictionary['E'] == 1 or dictionary['E'] == 0):
           return
        # if H 0 then T must be 5, otherwise can't get a zero sum
        elif(dictionary['H'] == 0 and (isinstance(dictionary['T'], int) and (dictionary['T'] != 5) )):
                return;
        
        elif(position == -1):
            print("N: {0}, O: {1}, R: {2}, T: {3}, H: {4}".format(dictionary['N'], dictionary['O'], dictionary['R'], dictionary['T'], dictionary['H']))
            print("      E: {0}, A: {1}, S: {2}, T: {3}".format(dictionary['E'], dictionary['A'], dictionary['S'], dictionary['T']))
            print("S: {0}, O: {1}, U: {2}, T: {3}, H: {4}".format(dictionary['S'], dictionary['O'], dictionary['U'], dictionary['T'], dictionary['H']))
            print("      W: {0}, E: {1}, S: {2}, T: {3}".format(dictionary['W'], dictionary['E'], dictionary['S'], dictionary['T']))
            print('-----------------------------')
            print("E: {0}, A: {1}, R: {2}, T: {3}, H: {4}".format(earth[0], earth[1], earth[2], earth[3], earth[4]))
            print('-----------------------------\n')
    
        elif (columnCompleted):
            completionItems = self.completeCurrentColumn(words, carry, earth[position], position)
            if(len(completionItems) > 0):
                 self.getPossibleCombinations(earth, dictionary, words, completionItems[1], completionItems[2], completionItems[0], possibleDigits)
            return
        for option in possibleDigits:
            isNewColumn = isinstance(earth[position], str)
            currentCharacter = ""
            if(isNewColumn):
                currentCharacter = earth[position]
            else:
                currentCharacter = self.getNextMissingColumnChar(words, position)
            if(currentCharacter == ""):
                print("error!")
                return
            
            #We need copies of the dictionary and the list since these objects are passed by ref and we need a true copy on each function call
            newDictionary = dictionary.copy()
            newPossibleDigits = possibleDigits.copy()             
            newEarth = earth.copy()
            newWords = copy.deepcopy(words)
            
            potential = -1
            if(isNewColumn):
                potential = dictionary[newEarth[position]]
                if(potential == -1):
                    newEarth[position] = option
                    newPossibleDigits.remove(option)
                else:
                    newEarth[position] = potential
            else:
                newPossibleDigits.remove(option)

                
            #print("words before replace: ", newWords, " earth:, ",earth, "remaining: ", possibleDigits)
            newWModifiedwords = self.replaceOccuranceOfChar(newWords, newDictionary, currentCharacter, option, position)
            #print("words after replace: ", newWModifiedwords, " earth:, ",earth, " remaining: ", newPossibleDigits)

            #print("pos: ", position, "earth at pos: ", earth[position], "char: ", currentCharacter, "words: ", words, "remaining options: ", newPossibleDigits)
            self.getPossibleCombinations(newEarth, newDictionary, newWModifiedwords, position, position, carry, newPossibleDigits)

    
def main():
    #There are (10 combination 5) ways to chose 5 unique numbers from 10 unique numbers
    #There are also 5! ways of re-arranging those numbers in earth since each character is unique
    #There is a total of 10C5 * 5! = 252 * 120 = 30240 possible choices of picking five unique numbers from [0 - 9]
    #====Other constraints
    #The character E can never be 0 because we will be forced to make N and S zero, this would violate uniqueness
    #

    #Initialize variables
    words = [['N','O','R','T','H'],
             [0  ,'E','A','S','T'],
             ['S','O','U','T','H'],
             [0  ,'W','E','S','T']]    

    earth = ['E','A','R','T','H']    
    exclusion = ['N','O','S','U','W']
    initialPossibleDigits = [0,1,2,3,4,5,6,7,8,9]
    initialSolution = {'E':-1,'A':-1,'R':-1,'T':-1,'H':-1,'N':-1,'O':-1,'S':-1,'U':-1,'W':-1}
    LAST_INDEX_IN_EARTH = 4
    LAST_CHECKED_INDEX = 4
    INITIAL_CARRY_OVER = 0;

    #Create solution class object
    solution = Solution()

    #recursive solver
    solution.getPossibleCombinations(earth, initialSolution, words , LAST_INDEX_IN_EARTH, INITIAL_CARRY_OVER, INITIAL_CARRY_OVER, initialPossibleDigits)

    print("\n=====done=====\n")
