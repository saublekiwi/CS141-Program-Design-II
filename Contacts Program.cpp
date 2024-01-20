#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

struct PhoneNumber { //This needs to be moved into the Contact class
  PhoneNumber(char, string);
  char phoneType;
  string number;
};

PhoneNumber::PhoneNumber (char type, string phoneNumber) {
  phoneType = type;
  number = phoneNumber;
}



class Contact {
  public:
    Contact(char, string, string);
    bool operator< (Contact cs);

    string getAddress();
    string getAsString();
    char getContactType();
    string getDateOfBirth();
    string getEmail();
    string getFirstName();
    string getLastName();
    string getName();
    string getState();

    string addPhone(char, string);
    string deletePhone(int);
    void setAddress(int, string, string, string, int);
    void setEmail(string);
    void setContactType(char);
    void setDateOfBirth(string);
    void setFirstName(string);
    void setLastName(string);

    string tester();

  private:
    char contactType;
    string firstName, lastName, streetName, city, state, email, dateOfBirth;
    int streetNumber, postalCode;
    vector<PhoneNumber> phoneNumbers;
};


Contact::Contact (char type, string fn, string ln) {
  contactType = toupper(type);
  firstName = fn;
  lastName = ln;
}


bool Contact::operator< (Contact c2) { //compares the name of the left contact with the contact on the right (the one passed in)
  if (getName() < c2.getName()) {
    return true;
  }

  else {
    return false;
  }
}

string Contact::getAddress () {
  string address = to_string(streetNumber) + " " + streetName + ", " + city + ", " + state + " " + to_string(postalCode);
  return address;
}

string Contact::getAsString() {
  string typeDisplay, phoneTypeDisplay;
  
  if (getContactType() == 'W') {
    typeDisplay = "Work";
  }
  else {
    typeDisplay = "Personal";
  }
  
  string toReturn = getName() + "\n" + typeDisplay + "\n" + getAddress() + "\n" + getDateOfBirth() + "\n" + getEmail() + "\n";
  
  for (int i = 0; i < signed(phoneNumbers.size()); i++) {
    if (toupper(phoneNumbers.at(i).phoneType) == 'H') {
      phoneTypeDisplay = "Home";
    }
    else {
      phoneTypeDisplay = "Cell";
    }
    
    toReturn += phoneTypeDisplay + ": " + phoneNumbers.at(i).number + "\n";
  }
  
  return toReturn;
}

char Contact::getContactType () {
  return contactType;
}

string Contact::getDateOfBirth () {
  return dateOfBirth;
}

string Contact::getEmail () {
  return email;
}

string Contact::getFirstName () {
  return firstName;
}

string Contact::getLastName () {
  return lastName;
}

string Contact::getName() {
  string fullName = lastName + ", " + firstName;
  return fullName;
}

string Contact::getState () {
  return state;
}


string Contact::addPhone (char type, string number) {
  string t, toReturn;

  if (type == 'p' || type == 'P') {
    type = 'h';
  }
  
  t.push_back(toupper(type));
  
  if (t != "W" && t != "H" && t != "C") {
    toReturn = "failure: invalid phone type - " + t;
    return toReturn;
  }

  else {
    phoneNumbers.push_back(PhoneNumber(type, number));
    toReturn = "success: added number " + number + " " + t;
    if (t == "C") {
      toReturn += "ell";
    }
    return toReturn;
  }
}

string Contact::deletePhone(int i) {
  if (i >= signed(phoneNumbers.size())) {
    return "failure: unable to delete phone " + to_string(i);
  }
  
  phoneNumbers.erase(phoneNumbers.begin() + i);
  return "success: deleted phone " + to_string(i);
}

void Contact::setAddress (int num, string street, string cit, string stat, int zip) {
  streetNumber = num;
  streetName = street;
  city = cit;
  state = stat;
  postalCode = zip;
}

void Contact::setContactType (char t) {
  contactType = t;
}

void Contact::setDateOfBirth (string dob) {
  dateOfBirth = dob;
}

void Contact::setEmail (string emailInput) {
  email = emailInput;
}

void Contact::setFirstName (string fn) {
  firstName = fn;
}

void Contact::setLastName (string ln) {
  lastName = ln;
}



class ContactList {
  public:
    int getCount();

    bool addContact(Contact);
    bool deleteContact(int);
    vector<int> findContactsByName(string);
    string loadContactsFromFile(const string&);
    void printContacts();
    void printContacts(vector<int>);
    bool sortContacts();

    string tester();

  private:
    vector<Contact> contacts;
};


int ContactList::getCount () {
  int count = signed(contacts.size());
  
  return count;
}


bool ContactList::addContact (Contact c) {
  contacts.push_back(c);
  return true;
}

bool ContactList::deleteContact (int d) {
  contacts.erase(contacts.begin() + d);
  return true;
}

vector<int> ContactList::findContactsByName (string nameToFind) {
  vector<int> positions;

  transform(nameToFind.begin(), nameToFind.end(), nameToFind.begin(), ::toupper);

  for (int i = 0; i < signed(contacts.size()); i++) {
    string contactName = contacts.at(i).getName();
    
    transform(contactName.begin(), contactName.end(), contactName.begin(), ::toupper);

    if (contactName.find(nameToFind) != string::npos) {
      positions.push_back(i);
    }
  }

  return positions;
}

string ContactList::loadContactsFromFile (const string& f) {
  ifstream file{f};
  
  if (!file.is_open()) {
    return "failure: " + f + " not found";
  }

  else {
    bool firstLine = true;
    int countAdded = 0;
    
    while (!file.eof()) {
      
      string type, firstName, lastName, streetNumber, streetName, city, state, postalCode, email, dob, age, phone, cell;

      getline(file, type, ',');
      //makes sure the type is not blank (preventing the last line from casing an error)
      if (signed(type.size()) == 0) {
        break;
      }
      getline(file, firstName, ',');
      getline(file, lastName, ',');
      getline(file, streetNumber, ',');
      getline(file, streetName, ',');
      getline(file, city, ',');
      getline(file, state, ',');
      getline(file, postalCode, ',');
      getline(file, email, ',');
      getline(file, dob, ',');
      getline(file, age, ','); //Currently this is unused??
      getline(file, phone, ','); //Currently this is unused?? the vector of phone numbers needs to be used
      getline(file, cell, '\n'); //Currently this is unused??

      if (firstLine) {
        firstLine = false;
        continue;
      }

      Contact c (type.at(0), firstName, lastName);

      c.setAddress(stoi(streetNumber), streetName, city, state, stoi(postalCode));
      c.setEmail(email);
      c.setDateOfBirth(dob);
      c.addPhone('H', phone);
      c.addPhone('C', cell);

      contacts.push_back(c);
      countAdded++;
    }
    
    return "success: " + to_string(countAdded) + " contacts added\n";
  }
}

void ContactList::printContacts() {
  for (Contact c: contacts) {
    cout << "--------------------" << endl  << endl << c.getAsString() << endl;
  }
}

void ContactList::printContacts(vector<int> positions) {
  for (int i = 0; i < signed(positions.size()); i++) {
    cout << "--------------------" << endl << endl << contacts.at(positions.at(i)).getAsString() << endl;
  }
}

bool ContactList::sortContacts() { //Needs to return success or failure
  sort(contacts.begin(), contacts.end());
  return true;
}



int main() {
    ContactList myContacts;
  
    myContacts.loadContactsFromFile("contacts.csv");
  
    myContacts.sortContacts();
  
    vector<int> v = myContacts.findContactsByName("ra");
    
    myContacts.printContacts(v);
    
    return 0;

}

int main_testing() {
  ContactList cv;
  
  cout << cv.loadContactsFromFile("contacts.csv") << endl;
  cout << cv.sortContacts() << endl;
  //cv.printContacts();
  //cv.printContacts({0, 3});
  vector<int> positions = cv.findContactsByName("Allen");
  for (int i: positions) {
    cout << i << endl;
  }

  return 0;
}   