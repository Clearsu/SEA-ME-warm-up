#include "Contact.hpp"

Contact::Contact() {}

Contact::Contact(const Contact& other)
    : name(other.name), number(other.number),
    email(other.email), isBookmarked(false) {}

Contact::Contact(const QString& name,
                 const QString& number,
                 const QString& email)
    : name(name), number(number),
    email(email), isBookmarked(false) {}

Contact& Contact::operator=(const Contact& other) {
    if (this != &other) {
        this->name = other.name;
        this->number = other.number;
        this->email = other.email;
        this->isBookmarked = other.isBookmarked;
    }
    return *this;
}

Contact::~Contact() {}

const QString&	Contact::getName() const { return this->name; }
const QString&	Contact::getNumber() const { return this->number; }
const QString&	Contact::getEmail() const { return this->email; }
bool			Contact::getIsBookmarked() const { return this->isBookmarked; }

void	Contact::setName(const QString& name) { this->name = name; }
void	Contact::setNumber(const QString& number) { this->number = number; }
void	Contact::setEmail(const QString& email) { this->email = email; }
void	Contact::setIsBookmarked(bool isBookmarked) { this->isBookmarked = isBookmarked; }
