
#include <iostream>
#include <string>

bool periodic(const std::string& str, int k)
{
    if (k <= 0 && k >= str.length())
    {
        return false;
    }
     int n = str.length();

      for (int i = 0; i < n; ++i)
      {
        if (str[i] != str[i % k])
        {
            return false;
        }
      }
      return true;
}

void show(const std::string& str, int k)
{
    if (str.length() % k == 0) 
    {
        std::cout << "\nline: " << str << "\nmultiplicity = " << k << "\n";
    }
    else
    {
         std::cout << "\nline: " << str << "\nmultiplicity = " << 0;
    }
}

    


int main()
{
    std::string s = {"abcabcabc"};
    std::string s2 = {"abcdeabcdeabcdeabcde"};
    std::string s3 = {"dhfaihgaihalha"};

    periodic(s, 3);
    show(s, 3);

    periodic(s2, 5);
    show(s2, 5);

    periodic(s3, 3);
    show(s3, 3);
    
    return 0;
}
