#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s("H\01111");

    cout << s << endl;
    cout << "S size: " << s.size() << endl;
    return 0;
}
