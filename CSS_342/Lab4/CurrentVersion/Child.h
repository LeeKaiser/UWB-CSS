#include <iostream> 
using namespace std;

class Child
{
    friend ostream& operator<< (ostream &, const Child &);
    friend istream& operator>> (istream &, Child&);
    
    public:
    Child();
    Child(string fName, string lName, int Age);
    Child(Child const &obj);
    ~Child();

    int getAge() const;
    string getName() const;
    string getFirst() const;
    string getLast() const;
    

    bool operator<(const Child&) const;
    bool operator<=(const Child&) const;
    bool operator>(const Child&) const;
    bool operator>=(const Child&) const;
    bool operator==(const Child&) const;
    bool operator!=(const Child&) const;

    private:
    int age;
    string firstName;
    string lastName;
};