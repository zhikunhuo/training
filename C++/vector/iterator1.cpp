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

    vector<int>::iterator iter = ivec1.begin();

    for(vector<int>::size_type loop = 0; loop < ivec1.size() / 2; ++loop)
    {    
        ibefore = *iter;
	iafter = *++iter;
        ++iter;
        cout << "The sum of " << ibefore << " and " << iafter << " is " << ibefore + iafter << endl;
    }

    return 0;
}

