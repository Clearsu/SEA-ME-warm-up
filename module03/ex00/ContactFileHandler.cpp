#include <QTextStream>
#include <qDebug>

#include "ContactFileHandler.hpp"

ContactFileHandler::ContactFileHandler(const QString& path): contactFile(path) {}

ContactFileHandler::~ContactFileHandler() {
    if (this->contactFile.isOpen()) {
        this->contactFile.close();
    }
}

std::multimap<QString, Contact> ContactFileHandler::loadContactsFromFile() {
    std::multimap<QString, Contact> contacts;

    if (!this->contactFile.open(QIODevice::Text | QIODevice::ReadOnly)) {
        throw OpenFailException();
    }

    QTextStream in(&this->contactFile);
    in.readLine(); // skip header

    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(',');

        if (fields.size() != 4) {
            continue;
        }
        qDebug() << "field3: " << fields[3] << "  isTrue: " << (fields[3].toLower() == "true") << '\n';


        Contact contact(fields[0], fields[1], fields[2],
                        fields[3].toLower() == "true");
        contacts.insert({fields[0], contact});
    }

    this->contactFile.close();

    return contacts;
}

void ContactFileHandler::saveContactsToFile(const std::multimap<QString, Contact> &contacts) {
    if (!this->contactFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate)) {
        throw OpenFailException();
    }

    QTextStream out(&this->contactFile);

    out << "name,phone,email,bookmark\n";

    std::multimap<QString, Contact>::const_iterator it = contacts.begin();
    std::multimap<QString, Contact>::const_iterator end = contacts.end();

    while (it != end) {
        const Contact& contact = it->second;
        out << contact.getName()
            << ',' << contact.getNumber()
            << ',' << contact.getEmail()
            << ',' << contact.getIsBookmarked() << '\n';
        ++it;
    }

    this->contactFile.close();
}

const char* ContactFileHandler::OpenFailException::what() const noexcept {
    return "Failed to open file.";
}
