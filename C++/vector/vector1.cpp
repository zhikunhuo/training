#include <iostream>
#include <vector>

using namespace::std;

int main(){
    vector<int> ivec1;
    int ivalue;
    vector<int>::size_type index = 0;
    int ibefore;
    int iafter;

    while(cin >> ivalue) {
        ivec1.push_back(ivalue);
	cout << ivalue << endl;
    }

    for(vector<int>::size_type loop = 0; loop < ivec1.size() / 2; ++loop)
    {    
        ibefore = ivec1[index];
	iafter = ivec1[++index];
        ++index;
        cout << "The sum of " << ibefore << " and " << iafter << " is " << ibefore + iafter << endl;
    }

    return 0;
}

