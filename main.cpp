#include <iostream>
#include <string>
// The following 2 includes are for increasing CPU utilization to make the program run faster, but I have yet to implement usage.
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

//arrays containing uppercase and lowercase letters for the algorithm to use in finding the password.
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

/*const char AlphabetLower[52] =
{
    'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G',
    'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N',
    'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U',
    'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z'
};*/

//arrays containing digits and special characters, which most passwords are required to have.
const int digit[10] = {0,1,2,3,4,5,6,7,8,9};
// Following line is commented out because the compiler threw the error: "too many initializers for 'const char[10]'"-
//I think it is because of the parenthesis, but it could be that some of these specials aren't considered char type. Or I am missing something completely...
//const char special[10] = {"!","@","#","$","%","^","&","*","(",")"};

string finalAnswer;
int finalFound = 0;

void Start(string pass, int startLength);
void Generate(unsigned int length, string s, string pas);


// Recursive function, keeps clocking characters
// until length is reached
void Generate(unsigned int length, string s,string pas)
{
    // Found and globalFound have been separated so the compiler doesn't have to re-access a global variable every time it asks to recurse.

    if(length == 0) // when length has been reached
    {
        cout << s << "\n"; // print it out... commented out for optimization, but uncomment for testing purposes.
        //attempts++;
        return; //go back to the last place generate() was called.
    }

    for(unsigned int i = 0; i < 26; i++) // iterate through alphabet
    {
        // Create/Recreate String appended to add and attempt the next letter in the alphabet array.
        string appended = s + AlphabetLower[i];

        if(appended == pas)
        {
            finalAnswer = appended;
            cout<<finalAnswer<<endl;
            finalFound = 1;    //globalFound variable matches found, it is used by Crack() to check if the loop should continue.
        }
        // This secondary if statement makes the compiler stop searching for the answer almost immediately after finding the combination.
        if(finalFound != 1){
            // The function calls itself back, passing the updated string combination "appended" as the "string s" parameter
            Generate(length-1, appended,pas);
        }
    }

    //repeat the alphabet loop to find uppercases. IT WORKS!
    for(unsigned int i = 0; i < 26; i++) // iterate through alphabet
    {
        // Create/Recreate String appended to add and attempt the next letter in the alphabet array.
        string appended = s + AlphabetUpper[i];

        if(appended == pas)
        {
            finalAnswer = appended;
            cout<<finalAnswer<<endl;
            finalFound = 1;    //globalFound variable matches found, it is used by Crack() to check if the loop should continue.
        }
        // This secondary if statement makes the compiler stop searching for the answer almost immediately after finding the combination.
        if(finalFound != 1){
            // The function calls itself back, passing the updated string combination "appended" as the "string s" parameter
            Generate(length-1, appended,pas);
        }
    }


}

void Start(string pass, int startLength)
{

    while(finalFound == 0) //loops as long as the password hasn't been found.
    {
        // sets stringlength to startLength, which gets passed as a parameter from int main()
        static unsigned int stringlength = startLength;
        // Calls generate
        Generate(stringlength,"",pass);
        stringlength++;
        cout<<finalFound<<endl;
    }
}

int main()
{
    // Some comments for future development...
    // The current state is for testing the algorithm and making it overall more efficient and fast, secondly more functional.
    // Right now it only can guess lowercase or uppercase passwords with no digits or special characters, and I don't think it would work if there is a space in the string.
    // I have tried doing simple optimizations, but if you see something, comment out current code, make an explanation, and make the change you see fit.
    // DO NOT DELETE ANY CODE! PLEASE FOLLOW THIS COMMENTING FORMAT!

    // Future improvements include but are not limited to this order:
    // 1. guessing passwords with uppercases--DONE...Needs optimization?
    // 2. guessing passwords with digits
    // 3. guessing passwords with special characters
    // 4. making the program skip password combinations that are less than 8 characters, this may be the next thing I try--DONE...Still testing?
    // Alternative to 4: Find way to set CPU threads to testing different stages of password length. example-
                                                    // thread 0 checks combinations up to 4 chars
                                                    // thread 1 checks combinations from 5 to 8 chars
                                                    // thread 3 checks combinations from 9 to 12 chars
                                                    // thread 4 checks combinations from 13 to 16 chars
                                                    //most computers have at least 2 cores and 4 threads, so this should be compatible.

    /*  these commands hopefully will give more resources to this program and make it run faster.
    int getpriority(int which, id_t who);
    int setpriority(int which, id_t who, int prio);
    */
    cout<<"Welcome to dHashBreaker"<<endl;
    cout<<"Enter a password"<<endl;

    // Grabs an input from the user for the program to attempt to guess.
    // Although the program knows the answer in "password", it never cheats and still has to guess the answer through the algorithm.
    string password;
    cin>>password;

    // This input allows the user to tell the program to skip ahead in combinations. For example, if 4, the program will skip all
    // combinations less than 4 characters long, and start with aaaa
    cout<<"Input minimum number of characters to attempt: "<<endl;
    int minChars = 0;
    cin>>minChars;

    // This input would allow the user to tell the program to skip ahead to a specified start letter if they somehow knew only
    // the first letter of the password/hash. This functionality does not work yet but is in the goals of the next milestone.
    cout<<"Do you know what the first letter is? If not, leave blank and hit enter."<<endl;
    string firstChar;
    cin>>firstChar;

    cout<<endl<<"................"<<endl;

    // Call Start(), passing necessary parameters password and minChars.
    Start(password,minChars);

    // This would stay if the program is applied to a real scenario, but there would need to be some following lines to complete the actual functionality of-
    //injecting the found answer into a password field, feeding it to a database, or applying it in a hash decryption.
    cout<<"Found answer: "<<finalAnswer<<endl;
    return 0;
}
