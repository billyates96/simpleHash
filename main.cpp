#include <iostream>
#include <string>

using namespace std;

class Result{
public:
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

    string finalAnswer;
    bool found = false;

    void Generate(int length, string s, string combo){

        if(length == 0){
            cout << s << "\n";
            return;
        }

        for(int i = 0; i < 26; i++){
            string appended = s + AlphabetLower[i];

            if(appended == combo){
                finalAnswer = appended;
                found = true;
                cout<<"MATCH FOUND: "<<finalAnswer<<endl;

            }

            if(found == false){
                Generate(length-1,appended,combo);
            }

        }


    }
};

int main()
{
    cout<<"Welcome to dHashBreaker, Enter a string for the program to guess:"<<endl;
    string combination;
    cin>>combination;

    cout<<endl<<"Input minimum number of characters the string could be:"<<endl;
    int minimumChars = 0;
    cin>>minimumChars;

    cout<<"...attempting to guess string combination..."<<endl;

    Result finalResult;
    while(finalResult.found == false){
        finalResult.Generate(minimumChars,"",combination);
        minimumChars++;
    }
    return 0;
}
