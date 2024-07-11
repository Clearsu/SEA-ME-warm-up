#ifndef CONTACTFILEHANDLER_HPP
#define CONTACTFILEHANDLER_HPP

#include <QFile>
#include <vector>
#include <exception>

#include "Contact.hpp"

class ContactFileHandler {
public:
    ContactFileHandler(const QString& path);
    ~ContactFileHandler();

    std::multimap<QString, Contact>	loadContactsFromFile();
    void	saveContactsToFile(const std::multimap<QString, Contact>& contacts);

private:
    QFile contactFile;

public:
    class OpenFailException : public std::exception {
    public:
        const char* what() const noexcept override;
    };
};

#endif
