#include <iostream>
#include <string>

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

// 2 dimension array test. I don't think this would work.
/*const char AlphabetLower[26][26] =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z'
};*/

//arrays containing digits and special characters, which most passwords are required to have.
const int digit[10] = {0,1,2,3,4,5,6,7,8,9};
// Following line is commented out because the compiler threw the error: "too many initializers for 'const char[10]'"-
//I think it is because of the parenthesis, but it could be that some of these specials aren't considered char type. Or I am missing something completely...
//const char special[10] = {"!","@","#","$","%","^","&","*","(",")"};

//global string variable to allow Generate() to check if it has found the correct password.
//if this program were to be applied, this variable would be replaced with a function, attempting to inject password into a field.
string finalAnswer;
int found = 0;
void Crack(string pass);
void Generate(unsigned int length, string s, string pas);


// Recursive function, keeps clocking characters
// until length is reached

void Generate(unsigned int length, string s,string pas)
{

    if(length == 0) // when length has been reached
    {
        //cout << s << "\n"; // print it out... commented out for optimization, but uncomment for testing purposes.

        //I have a hard time understanding this part, please comment an explanation below if you know...
        //By just reading syntax, it checks if length has become 0, which it does every other time Generate() is called from Crack(), because of Generate(length-1,,)
        //Somehow, this Generate() function run through each of the lowercase array elements and tests if the password is the current combination, what confuses me-
        //is that when the password does not match any single character combination of the lowercase array, it adds a character length and starts checking to see if the-
        //combination is aa,ab,ac,ad... so on. After it checks az, it moves onto ba,bb,bc,bd... so on. Not sure how it nows to run through all characters on the right-
        //before changing the character on the left. If you have a better explanation please comment below.

        //

        return;
    }

    //string p = pas;

    for(unsigned int i = 0; i < 26; i++) // iterate through alphabet
    {
        // Create new string with next character
        // Call generate again until string has reached it's length
        string appended = s + AlphabetLower[i];
        if(appended == pas)
        {
            finalAnswer = appended;
            cout<<finalAnswer<<endl;
            //cin.get();    //debugging
            found = 1;
            //cout<<"FOUND HAS BEEN SET TO 1"<<endl;    //debugging
        }
        if(found != 1){
            //The function calls itself back, passing the updated string combination "appended" as the "string s" parameter
            Generate(length-1, appended,pas);
        }



    }
}

void Crack(string pass)
{
    //cout<<"CRACK HAS BEEN CALLED"<<endl;      //debugging

    while(found == 0)
    {
        //Keeps growing till it gets it right
        static unsigned int stringlength = 1;
        Generate(stringlength,"",pass);
        stringlength++;
    }
    //cout<<"LEAVING CRACK()"<<endl; debugging
}

int main()
{
    // Some comments for future development...
    // The current state is for testing the algorithm and making it overall more efficient and fast, secondly more functional.
    // Right now it only can guess lowercase passwords with no digits or special characters, and I don't think it would work if there is a space in the string.
    // I have tried doing simple optimizations, but if you see something, comment out current code, make an explanation, and make the change you see fit.
    // DO NOT DELETE ANY CODE! PLEASE FOLLOW THIS COMMENTING FORMAT!

    // Future improvements include but are not limited to this order:
    // 1. guessing passwords with uppercases
    // 2. guessing passwords with digits
    // 3. guessing passwords with special characters
    // 4. making the program skip password combinations that are less than 8 characters, this may be the next thing I try.
    // 5. converting everything to integers so the algorithm runs faster.

    cout<<"Enter a password"<<endl;

    // Grabs an input from the user for the program to attempt to guess.
    // Although the program knows the answer in "password", it never cheats and still has to guess the answer through the algorithm.
    string password;
    cin>>password;
    cout<<endl<<".........."<<endl;
    Crack(password);

    // This would stay if the program is applied to a real scenario, but there would need to be some following lines to complete the actual functionality of-
    //injecting the password into a password field or feeding it to a database. More research and information is needed on how these password systems work.
    cout<<"Attempting to inject password: "<<finalAnswer;
    return 0;
}
