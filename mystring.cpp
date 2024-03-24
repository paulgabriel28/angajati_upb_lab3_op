#include <iostream>
#include <cstring>

using namespace std;

class MyString {
    char *buf;
    int l;

    public:
        //constr fara param – initializeaza atrib. cu 0 sau NULL
        MyString();
        
        // constr cu param – un sir de caractere  
        MyString(const char *);

        // constr de copiere
        MyString(const MyString &);
        
        // operator de atribuire
        MyString& operator=(const MyString &);
        
        // destructor
        ~MyString();
        
        // operatorii pentru afisare si citire pentru obiecte MyString
        friend ostream& operator<<(ostream&, const MyString&);
        friend istream& operator>>(istream&, MyString&);
        
        // operator+ concateneaza 2 siruri si salveaza rezultatul intr-un
        // obiect nou de tip MyString pe care il returneaza
        friend const MyString operator+(const MyString &, const MyString &);
        
        // operator+= concateneaza 2 siruri si salveaza rezultatul
        // in primul operand a carui adresa o returneaza
        MyString& operator+=(const MyString &);
        
        //operator de indexare – returneaza referinta catre caracterul 
        //de pe pozitia i din buf
        char& operator[](int);
        
        // cauta caracterul dat ca parametru in sir si
        // returneaza numarul de aparitii
        int lookFor(char) const;
        
        // verifica daca cele 2 siruri sunt identice
        friend bool operator==(const MyString &, const MyString &);
        
        // verifica daca cele 2 siruri sunt diferite, poate folosi ==
        friend bool operator!=(const MyString &, const MyString &);
        
        // Implementati operatorii de relatie: <, <= >, >= ca functii friend
        //ordonare se face alfabetic
        friend bool operator<(const MyString &, const MyString &);
        friend bool operator<=(const MyString &, const MyString &);
        friend bool operator>(const MyString &, const MyString &);
        friend bool operator>=(const MyString &, const MyString &);

        void set_buf(const char *);
};

void MyString::set_buf(const char *new_buf) {
    if (buf != NULL) {
        delete [] buf;
    }

    if (new_buf != NULL) {
        buf = new char[strlen(new_buf) + 1];
        strcpy(buf, new_buf);
    } else {
        buf = NULL;
    }
}

MyString::MyString() {
    buf = NULL;
    l = 0;
}

MyString::MyString(const char *c) {
    buf = NULL;
    l = strlen(c);
    set_buf(c);
}

MyString::MyString(const MyString &str) {
    *this = str;
}

MyString& MyString::operator=(const MyString &str) {
    l = str.l;
    this->set_buf(str.buf);
}

MyString::~MyString() {
    delete [] buf;
    l = 0;
}

ostream& operator<<(ostream &dev, const MyString &str) {
    dev << "\nLungime: " << str.l;
    dev << "\nBuf: " << str.buf;
    dev << "\n---" << endl;
}

istream& operator>>(istream &dev, MyString &str) {
    char temp[100];
    cout<<"Sir: ";
    cin>>temp;

    str.l = strlen(temp);
    str.buf = new char[str.l + 1];
    strcpy(str.buf, temp);
}

const MyString operator+(const MyString &str1, const MyString &str2) {
    int new_dim = str1.l + str2.l;
    char *temp;
    temp = new char[new_dim + 1];
    int poz = 0;
    for(int i = 0; i < str1.l; i++) {
        temp[poz] = str1.buf[i];
        poz++;
    }
    for(int i = 0; i < str2.l; i++) {
        temp[poz] = str2.buf[i];
        poz++;
    }
    temp[poz] = '\0';
    return MyString(temp);    
}

MyString& MyString::operator+=(const MyString &str) {
    *this = *this + str;
    return *this;
}

char& MyString::operator[](int i) {
    return buf[i];
}

int MyString::lookFor(char c) const {
    int nr = 0;
    for(int i = 0; i < strlen(buf); i++) {
        if(buf[i] == c)
            nr++;
    }

    return nr;
}

bool operator==(const MyString &str1, const MyString &str2) {
    return (strcmp(str1.buf, str2.buf) == 0 && str1.l == str2.l) ? 1 : 0;
}

bool operator!=(const MyString &str1, const MyString &str2) {
    return !(str1 == str2);
}

// operatori de relatie:
bool operator<(const MyString &str1, const MyString &str2) {
    return (strcmp(str1.buf, str2.buf) < 0) ? 1 : 0;
}

bool operator<=(const MyString &str1, const MyString &str2) {
    return (strcmp(str1.buf, str2.buf) <= 0) ? 1 : 0;
}

bool operator>(const MyString &str1, const MyString &str2) {
    return !(str1 < str2);
}

bool operator>=(const MyString &str1, const MyString &str2) {
    return !(str1 <= str2);
}


// functii
int count_str(const MyString *vec, const int &dim, const MyString &str) {
    int count = 0;

    for(int i = 0; i < dim; i++) {
        if(vec[i] == str) {
            count++;
        }
    }
    return count;
}

void sort_alpha(MyString *vec, const int dim) {
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            if(vec[i] < vec[j]) {
                MyString temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}




int main()
{
    // 2.
    MyString *vec;
    int dim;
    cout<<"Dimensiune vector: ";
    cin>>dim;

    vec = new MyString[dim];

    for(int i = 0; i < dim; i++) {
        cin>>vec[i];
    }

    // 3.
    cout<<"Sirul concatenat: ";
    MyString concat;
    for(int i = 0; i < dim; i++) {
        concat = concat + vec[i];
    }
    cout<<concat<<endl;

    // 4.
    cout << "Elemente egale cu vec[0]: " << count_str(vec, dim, vec[0]) << endl;

    // 5.
    cout << "Vector sortat alfabetic:\n";
    sort_alpha(vec, dim);
    for(int i = 0; i < dim; i++) {
        cout<<vec[i];
    }

    return 0;
}