#include <iostream>
#include <string>
#include <map>
using namespace std;

class Book {
    string author;
    string title;
    int year;
public:

    Book(string author = " ", string title = " ", int year = 0)
    {
        this->author = author;
        this->title = title;
        this->year = year;
    }

    string getAuthor() { return author; }


    friend bool operator==(const Book& b1, const Book& b2)
    {
        if (b1.author == b2.author)
            return true;
        else if (b1.title == b2.title)
            return true;
        else if (b1.year == b2.year)
            return true;
        else
            return false;
    }

    friend bool operator<(const Book& b1, const Book& b2)
    {
        if (b1.author == b2.author)
        {
            if (b1.title == b2.title)
            {
                return b1.year < b2.year;
            }
            else
            {
                return b1.title < b2.title;
            }
        }
        else
        {
            return b1.author < b2.author;
        }
    }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << b.author << "  " << b.title << "  " << b.year;
        return os;
    }

    friend istream& operator>>(istream& is, Book& b) {
        is >> b.author >> b.title >> b.year;
        return is;
    }
};
int main()
{
    setlocale(LC_ALL, "Ukrainian");

    multimap<Book, int> Biblio;
    Biblio.emplace(Book("Levitsky I.S.", "Kaydashev family", 2020), 3);
    Biblio.emplace(Book("Tkachenko V.V.", "Siver scrolls", 2011), 4);
    Biblio.emplace(Book("Logvinenko B.A.", "Country from the inside", 2019), 1);
    Biblio.emplace(Book("Grebenyuk V.I.", "Actions of celestial beings", 2011), 2);
    Biblio.emplace(Book("Kotlyarevskyi I.P.", "Natalka Poltavka", 2017), 1);



    cout << "Available books in the registry:" << endl;
    // all books
    for (const auto& book : Biblio) {
        cout << book.first << " (in stock: " << book.second << ")" << endl;
    }

    cout << "\nEnter the author whose books you want to remove from the registry:" << endl;
    // removing books by author
    string authorToDelete;
    getline(cin, authorToDelete);

    auto it = Biblio.begin();
    while (it != Biblio.end()) {

        if (const_cast<Book&>(it->first).getAuthor() == authorToDelete) {
            it = Biblio.erase(it);
        }
        else {
            ++it;
        }
    }


    cout << "\nAfter removing books by " << authorToDelete << endl;
    for (const auto& book : Biblio) {
        cout << book.first << " (in stock: " << book.second << ")" << endl;
    }

    cout << "\nEnter an author to get information about his books::" << endl;
    string authorToSearch;
    getline(cin, authorToSearch);

    for (auto it = Biblio.begin(); it != Biblio.end(); ++it) {
        if (const_cast<Book&>(it->first).getAuthor() == authorToSearch) {
            cout << it->first << ", in stock: " << it->second << endl;
        }
    }




    return 0;
}