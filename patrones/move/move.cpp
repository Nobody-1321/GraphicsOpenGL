#include <iostream>
#include <string>
#include <memory>
#include <utility>

using namespace std;
int main() {
    
    {
    std::string str1 = "Hello, World!";
    std::cout << "str1: " << &str1 << std::endl;
    std::string str2 = std::move(str1);
    std::cout << "str1: " << &str2 << std::endl;
    }

    cout<< endl << " punteros crudos " << endl;

    string *strAux;
{
    string *str3 = new string("Hello, Worldssss!");
    std::cout << "str3: " << str3 << std::endl;
    //string *str4 = std::move(str3);
    string *str4 = str3;
    strAux = str4;
    std::cout << "str3: " << str4 << std::endl;
    //delete str3;
    //delete str4;
}
    cout << "strAux: " << *strAux << std::endl;


    cout<< endl << " punteros inteligentes " << endl;
{
    unique_ptr<string> str5(new string("Hello, World!"));
    std::cout << "str5: " << str5.get() << std::endl;
    unique_ptr<string> str6 = std::move(str5);
    std::cout << "str5: " << str6.get() << std::endl;
}


    return 0;
}