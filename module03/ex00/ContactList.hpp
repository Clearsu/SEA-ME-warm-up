#ifndef CONTACTLIST_HPP
#define CONTACTLIST_HPP

#include <map>
#include <set>
#include <exception>

#include "Contact.hpp"

class ContactList {
public:
    ContactList();
    ~ContactList();

    void	add(const QString& name,
             const QString& number,
             const QString& email);
    void					remove(const QString& name, const QString& number);
    std::vector<Contact>	searchByName(const QString& name);
    std::vector<Contact>	searchByNumber(const QString& number);
    std::vector<Contact>	getAllContacts() const;
    std::vector<Contact>	getBookmarkedContacts() const;
    void					bookmarkContact(const QString& name, const QString& number);
    void					unbookmarkContact(const QString& name, const QString& number);

private:
    std::multimap<QString, Contact>	contacts;
    std::set<QString>				numbers;

    bool isNumberUnique(const QString& number);

    class NumberDuplicateException: public std::exception {
    public:
        const char*	what() const noexcept;
    };

    class ContactNotExistException: public std::exception {
    public:
        const char* what() const noexcept;
    };
};

#endif
