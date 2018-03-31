/*
    Since Milestone 2, I have converted the program into an OOP format, with the only class being Class Result.
    As we figured out in class, because I have created a completely new project and essentially rewritten most of the code,
    pushing to the same GitHub branch repo does not work. For this Milestone 3, I am going to create yet another branch.
    I realize this is not a good thing to do, but moving forward I will maintain my repo properly and make my commits
    go to the same branch, so you can see the steps I have made in the project. Please consider this as learning from my
    mistakes and do not grade me too negatively because I have once again created a separate branch, it will be corrected.

    I do not believe that using OOP for this program makes it any faster, and at this point I am reconsidering some goals
    I laid out in previous milestones. Here is a new list of goals for the final version:

    1. Generating combinations with digits.
    2. Generating combinations with special characters, such as !@#$.

    I may or may not be able to complete these goals with skills we have learned so far in class, but additional research
    will be necessary and I will at least attempt to make it work.
*/


#include <iostream>
#include <string>

using namespace std;

/*
    Class Result defines data members used by the member function Generate().
*/

class Result{
public:

    /*
        Following two arrays are comprised of uppercase and lowercase characters of the alphabet to be used by Generate()
    */

    const char AlphabetUpper[26] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z'
};

const char AlphabetLower[26] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z'
};

    /*
        These two data members are used by Generate(), finalAnswer only being given a value when a combination match is found,
        and found only being set to true when a combination match is found, but found is also used to tell Generate() to keep
        recursing if a match has not been found.
    */

    string finalAnswer;
    bool found = false;

    /*
        Generate() uses parameters given to it from Main() to recursively create a string and check if it matches the combo
        entered by the user. If this program was put into application, the combo parameter would be replaced by a
        function that provides an encrypted string for the program to guess, or passes the generated string combination
        into a field for another program or system to check for a match.
    */

    void Generate(int length, string s, string combo){

    /*
        The following if condition statement is executed if length has become 0, and every time Generate() recurses, length
        negatively increments by one (length--). If true, it will return to the last place Generate() was called, which
        is either within Generate() because it is recursive, or finally back to Main().
    */

        if(length == 0){
            //cout << s << "\n";
            return;
        }

        /*
            The following 26 step for loop is repeating for every element in the Alphabet arrays.
            string appended is re-initialized and set to the s parameter, along with the next element of the Alphabet array,
            which would actually just be the next letter in the alphabet.
        */

        for(int i = 0; i < 26; i++){
            string appended = s + AlphabetLower[i];

            /*
                This if statement checks to see if the generated combination matches the given combination, inputed by the user.
                If true, data member finalAnswer is set to the current generated combination, and found is set to true,
                preventing Generate() from recursing again. It also courteously tells the user a match has been found.
            */

            if(appended == combo){
                finalAnswer = appended;
                found = true;
                cout<<"MATCH FOUND: "<<finalAnswer<<endl;

            }

            /*
                As stated in previous comments, Generate() will only recurse if found is still false, which also means
                this statement only becomes true if the previous if statement did as well.
            */

            if(found == false){

                /*
                    Generate() recurses, passing length as one increment lower, and appended to become s, which will allow
                    the next run of Generate() to add to the combination string the next letter of the alphabet.
                */

                Generate(length-1,appended,combo);
            }

        }


    }
};

int main()
{
    /*
        Main begins with an introduction and asks for the combination it will try to match.
    */

    cout<<"Welcome to dHashBreaker, Enter a string for the program to guess:"<<endl;
    string combination;
    cin>>combination;

    /*
        minimumChars is inputed and used to tell Generate() how many characters long the combination could be a minimum,
        essentially making it skip all combinations less than this given value.
        For example, if a user knows the minimum length of characters the combination they are trying to find is
        8, they enter 8 here, and Generate starts with 8 characters, and does not waste time checking combinations 1-7.
    */

    cout<<endl<<"Input minimum number of characters the string could be:"<<endl;
    int minimumChars = 0;
    cin>>minimumChars;

    cout<<"...attempting to guess string combination..."<<endl;

    /*
        finalResult object is declared, being of the Result Class, and a loop begins and continues on the condition that
        the object data member found is still false.
        In the loop, object finalResult uses its defined Generate() function, passing previously inputed variables
        minimumChars and combination to the member function, and "" as an empty string to fill the s parameter used by Generate().
        It finally increments minimumChars up by one to tell Generate() to increase the length of the combination it is generating.
    */

    Result finalResult;
    while(finalResult.found == false){
        finalResult.Generate(minimumChars,"",combination);
        minimumChars++;
    }
    return 0;
}
