#include "ContactList.hpp"
#include <QDebug>

ContactList::ContactList() {}
ContactList::ContactList(const std::multimap<QString, Contact>& contacts): contacts(contacts) {
    this->initializeNumbers();
}
ContactList::~ContactList() {}

void ContactList::add(const QString& name, const QString& number,
                      const QString& email) {
    if (this->isNumberUnique(number)) {
        this->contacts.insert({name,
                               Contact(name, number, email, false)});
        this->numbers.insert(number);
    } else {
        throw NumberDuplicateException();
    }
}

void ContactList::remove(const QString& name, const QString& number) {
    std::pair<std::multimap<QString, Contact>::iterator,
              std::multimap<QString, Contact>::iterator> range
        = this->contacts.equal_range(name);
    std::multimap<QString, Contact>::iterator it = range.first;

    while (it != range.second) {
        if (it->second.getNumber() == number) {
            this->contacts.erase(it);
            this->numbers.erase(number);
            return;
        }
        ++it;
    }
}

std::vector<Contact> ContactList::searchByName(const QString& name) {
    std::multimap<QString, Contact>::iterator it = this->contacts.begin();
    std::multimap<QString, Contact>::iterator end = this->contacts.end();
    std::vector<Contact> matchingContacts;

    while (it != end) {
        if (it->first.toLower().contains(name)) {
            matchingContacts.push_back(it->second);
        }
        ++it;
    }
    return matchingContacts;
}

std::vector<Contact> ContactList::searchByNumber(const QString &number) {
    std::multimap<QString, Contact>::iterator it = this->contacts.begin();
    std::multimap<QString, Contact>::iterator end = this->contacts.end();
    std::vector<Contact> matchingContacts;

    while (it != end) {
        if (it->second.getNumber().contains(number)) {
            matchingContacts.push_back(it->second);
        }
        ++it;
    }
    return matchingContacts;
}

std::vector<Contact> ContactList::getAllContacts() const {
    std::multimap<QString, Contact>::const_iterator it = this->contacts.begin();
    std::multimap<QString, Contact>::const_iterator end = this->contacts.end();
    std::vector<Contact> ret;

    while (it != end) {
        ret.push_back(it++->second);
    }
    return ret;
}

std::vector<Contact> ContactList::getBookmarkedContacts() const {
    std::multimap<QString, Contact>::const_iterator it = this->contacts.begin();
    std::multimap<QString, Contact>::const_iterator end = this->contacts.end();
    std::vector<Contact> ret;

    while (it != end) {
        if (it->second.getIsBookmarked() == true) {
            ret.push_back(it->second);
        }
        ++it;
    }
    return ret;
}

void ContactList::bookmarkContact(const QString &name, const QString &number) {
    std::pair<std::multimap<QString, Contact>::iterator,
              std::multimap<QString, Contact>::iterator> range
        = this->contacts.equal_range(name);
    std::multimap<QString, Contact>::iterator it = range.first;

    while (it != range.second) {
        if (it->second.getNumber() == number) {
            it->second.setIsBookmarked(true);
            return;
        }
        ++it;
    }
    throw ContactNotExistException();
}

void ContactList::unbookmarkContact(const QString &name, const QString &number) {
    std::pair<std::multimap<QString, Contact>::iterator,
              std::multimap<QString, Contact>::iterator> range
        = this->contacts.equal_range(name);
    std::multimap<QString, Contact>::iterator it = range.first;

    while (it != range.second) {
        if (it->second.getNumber() == number) {
            it->second.setIsBookmarked(false);
            return;
        }
        ++it;
    }
    throw ContactNotExistException();
}

const std::multimap<QString, Contact>&	ContactList::getContacts() const {
    return this->contacts;
}

void ContactList::setContacts(const std::multimap<QString, Contact>& contacts) {
    this->contacts = contacts;
    this->initializeNumbers();
}

bool ContactList::isNumberUnique(const QString &number) {
    return this->numbers.find(number) == this->numbers.end();
}

void ContactList::initializeNumbers() {
    auto it = this->contacts.begin();
    auto end = this->contacts.end();

    while (it != end) {
        const QString& number = it->second.getNumber();
        if (this->isNumberUnique(number)) {
            this->numbers.insert(number);
        } else {
            throw NumberDuplicateException();
        }
        ++it;
    }
}

const char* ContactList::NumberDuplicateException::what() const noexcept {
    return "Warning: number already exists.";
}

const char* ContactList::ContactNotExistException::what() const noexcept {
    return "Warning: contact does not exist.";
}
