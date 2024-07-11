#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <QString>

class Contact {
public:
    Contact();
    Contact(const Contact& other);
    Contact(const QString& name,
            const QString& number,
            const QString& email,
            bool isBookmarked);
    Contact& operator=(const Contact& other);
    ~Contact();

    const QString&	getName() const;
    const QString&	getNumber() const;
    const QString&	getEmail() const;
    bool			getIsBookmarked() const;

    void	setName(const QString& name);
    void	setNumber(const QString& phone);
    void	setEmail(const QString& email);
    void	setIsBookmarked(bool isBookmarked);

private:
    QString	name;
    QString	number;
    QString email;
    bool	isBookmarked;
};

#endif
