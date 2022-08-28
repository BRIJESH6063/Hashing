#include<bits/stdc++.h>
using namespace std ;

int main()
{
    unordered_map<string, int> m ;
    m["abc"]  = 1 ;
    m["abc1"] = 2 ;
    m["abc2"] = 3 ;
    unordered_map<string, int>::iterator it = m.begin() ;
    for(it = m.begin(); it != m.end(); it++){
        cout << it->first << " " << it->second << endl ;
    }
    cout << "----------------------------------------------------" << endl ;
    for(auto x : m) cout << x.first << " " << x.second << endl ;
    m.erase("abc") ;
    cout << "----------------------------------------------------" << endl ;
    for(auto x : m) cout << x.first << " " << x.second << endl ;
    if(m.find("abcd") == m.end()) cout << "string 'abcd' is not present." << endl ;
    // erase elements in map 
    m.erase(m.begin(), m.end()) ;
    cout << "----------------------------------------------------" << endl ;
    for(auto x : m) cout << x.first << " " << x.second << endl ;
    return 0 ;
}