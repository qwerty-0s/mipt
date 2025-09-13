#include <iostream>
using namespace std;

bool find(char ch, string str)
{
      long unsigned int i = 0;
      for (i=0; i<str.length(); i++)
      {
            if(str[i]==ch)
            return 1;
      }
      return 0;
}
int main() {

      srand(time(0));
      int number = rand() % 10000;
      string number_str = to_string(number);
      string answer_str;
      int answer;
      int bulls=0;
      int cows=0;
      cout << number << endl;
      cout << find('1', "1000");
      int i=0;
      while (answer != number)
      {
            cin >> answer; 
            answer_str=to_string(answer);
         for(i=0;i<answer_str.length();i++)
         {
            if(answer_str[i]==number_str[i])
            {
                  bulls++;
            }
            else if(find(answer_str[i],number_str))
            {
                  cows++;
            }
         }
         cout << "cows ";
         cout << cows  << endl;
         cout << "bulls ";
         cout << bulls << endl;
         cows = 0;
         bulls = 0;

         
      }
}