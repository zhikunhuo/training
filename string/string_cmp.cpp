#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1;
    string s2;

    cin >> s1 >> s2;

    if ( s1 > s2)
    {
        cout << s1 << " is bigger than " << s2 << endl;
    } else if ( s1 < s2) {
        cout << s2 << " is bigger than " << s1 << endl;
    } else {
        cout << s1 << " is equal to " << s2 << endl;
    }


    return 0;
}
