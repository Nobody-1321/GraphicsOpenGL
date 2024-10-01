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
    std::string first;
    std::string last;
    unsigned int books;
};



class dataAuthor{
    static std::string fullName(const DataAuthor& author);
    static bool isProlific(const DataAuthor& author);
};


std::string dataAuthor::fullName(const DataAuthor& author){
    return author.first + " " + author.last;
}

bool dataAuthor::isProlific(const DataAuthor& author){
    return author.books > 10;
}

int main(){
    Author author{"Bjarne", "Stroustrup", 20};
    std::cout << author.fullName() << " is prolific: " << author.isProlific() << std::endl;


    return 0;
}