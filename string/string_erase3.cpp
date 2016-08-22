#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string s1;
    string::iterator first, last;

    while (cin >> s1)
    {
        for (string::size_type index=0; index < s1.size(); ++index)
	{
	    if(ispunct(s1[index])) {
	        first = s1.begin() + index;
	        last = s1.begin() + index+1;
	        s1.erase(first, last);
		cout << s1<< endl;
		return 0;
	    }
	}
    }


    return 0;
}
