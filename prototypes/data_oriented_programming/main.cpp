#include <string>
#include <iostream> 


class Author{
public:

    Author(std::string firstName, std::string lasName, unsigned int books);
    std::string fullName();
    bool isProlific();

private:
    std::string firstName;
    std::string lastName;
    unsigned int books;
};

Author::Author(std::string firstName, std::string lastName, unsigned int books):
     firstName{firstName}, lastName{lastName}, books{books}{}

std::string Author::fullName(){
    return firstName + " " + lastName;
}

bool Author::isProlific(){
    return books > 10;
}


struct DataAuthor
{
    std::string firstName;
    std::string lastName;
    unsigned int books;
};

struct userData{
    std::string firstName;
    std::string lastName;
    unsigned int books;
};

template <typename T>
class dataManipulator{
    static std::string fullName(const T& data);
    static bool isProlific(const T& data);
};

template <typename T>
std::string dataManipulator<T>::fullName(const T& data){
    return data.firstName + " " + data.lastName;
}

template <typename T>
bool dataManipulator<T>::isProlific(const T& data){
    return data.books > 10;
}


int main(){
    Author author{"Bjarne", "Stroustrup", 20};
    std::cout << author.fullName() << std::endl;
    
   // DataAuthor  dataAuthor{"Bjarne", "Stroustrup", 20};
   // std::cout << dataManipulator<DataAuthor>::fullName(dataAuthor) << std::endl;

   // userData user{"Bjarne", "Stroustrup", 20};
   // std::cout << dataManipulator<userData>::fullName(user) << std::endl;

}
