#include <string>
#include <regex>
#include <iostream>
using namespace std;

int main()
{
  
  regex pat("\".+\"");
  smatch res;  
  string str = "012\"asdfghjkl;a\"210" ;  
  regex_search(str, res, pat, regex_constants::match_default);
  cout << res.str().substr(1, res.str().size()-2) << endl;
  
  str = "\n" ;
  cout << str << endl;
  
  return 0;
  
}
