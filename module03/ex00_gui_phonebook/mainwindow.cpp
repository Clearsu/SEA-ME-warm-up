#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QComboBox>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

/**********     public     **********/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileHandler(QCoreApplication::applicationDirPath() + "/../../../../../contacts.csv")
    , checkCount(0) {
    this->ui->setupUi(this);

    QWidget::setWindowTitle("My Phonebook");

    connect(this->ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddContactButtonClicked);
    connect(this->ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(this->ui->cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelButtonClicked);
    connect(this->ui->bookmarkButton, &QPushButton::clicked, this, &MainWindow::onBookmarkButtonClicked);
    connect(this->ui->removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);
    connect(this->ui->showAllContactsButton, &QPushButton::clicked, this, &MainWindow::onShowAllContactsButtonClicked);
    connect(this->ui->showBookmarkButton, &QPushButton::clicked, this, &MainWindow::onShowBookmarksButtonClicked);
    connect(this->ui->contactTableWidget, &QTableWidget::itemChanged, this, &MainWindow::onCheckBoxClicked);
    connect(this->ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);

    try {
        this->contactList.setContacts(this->fileHandler.loadContactsFromFile());
    } catch (const std::exception& e) {
        this->showWarningDialog(e.what());
        this->deleteWindowAndExit();
    }

    this->reloadContactWidget(this->contactList.getAllContacts());
}

MainWindow::~MainWindow() {
    delete this->ui;
}



/**********     private slots     **********/

void MainWindow::onAddContactButtonClicked() {
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onSaveButtonClicked() {
    QString name(this->ui->nameInput->text().trimmed());
    QString phone(this->ui->phoneInput->text().trimmed());
    QString email(this->ui->emailInput->text().trimmed());

    if (name.isEmpty() || phone.isEmpty() || email.isEmpty()) {
        this->showWarningDialog("Warning: One or more inputs are empty.");
        return;
    }

    try {
        this->contactList.add(name, phone, email);
    } catch (const std::exception& e) {
        showWarningDialog(e.what());
        return;
    }

    this->updateContactFile();
    this->reloadContactWidget(this->contactList.getAllContacts());
    this->clearInputFields();
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onCancelButtonClicked() {
    this->clearInputFields();
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onBookmarkButtonClicked() {
    QTableWidget& tableWidget = *this->ui->contactTableWidget;
    int rowCount = tableWidget.rowCount();

    for (int row = 0; row < rowCount; row++) {
        if (tableWidget.item(row, CHECKBOX_COL)->checkState() == Qt::Checked) {
            this->contactList.bookmarkContact(
                tableWidget.item(row, NAME_COL)->text(),
                tableWidget.item(row, NUMBER_COL)->text());
        }
    }
    this->updateContactFile();
    this->reloadContactWidget(this->contactList.getAllContacts());
}

void MainWindow::onUnbookmarkButtonClicked() {
    QTableWidget& tableWidget = *this->ui->contactTableWidget;
    int rowCount = tableWidget.rowCount();

    for (int row = 0; row < rowCount; row++) {
        if (tableWidget.item(row, CHECKBOX_COL)->checkState() == Qt::Checked) {
            this->contactList.unbookmarkContact(
                tableWidget.item(row, NAME_COL)->text(),
                tableWidget.item(row, NUMBER_COL)->text());
        }
    }
    this->updateContactFile();
    this->reloadContactWidget(this->contactList.getBookmarkedContacts());
}

void MainWindow::onRemoveButtonClicked() {
    QTableWidget& tableWidget = *this->ui->contactTableWidget;
    int rowCount = tableWidget.rowCount();

    for (int row = 0; row < rowCount; row++) {
        if (tableWidget.item(row, CHECKBOX_COL)->checkState() == Qt::Checked) {
            this->contactList.remove(
                tableWidget.item(row, NAME_COL)->text(),
                tableWidget.item(row, NUMBER_COL)->text());
        }
    }
    this->updateContactFile();
    this->reloadContactWidget(this->contactList.getAllContacts());
}

void MainWindow::onCheckBoxClicked(QTableWidgetItem* item) {
    if (item->column() != 0) {
        return;
    }

    if (item->checkState() == Qt::Checked) {
        ++this->checkCount;
    } else if (this->checkCount > 0){
        --this->checkCount;
    }

    if (this->checkCount > 0) {
        this->enableRemoveAndBookmarkButtons();
    } else {
        this->disableRemoveAndBookmarkButtons();
    }
}

void MainWindow::onShowAllContactsButtonClicked() {
    this->ui->bookmarkButton->setText("Bookmark");
    disconnect(this->ui->bookmarkButton, &QPushButton::clicked, this, &MainWindow::onUnbookmarkButtonClicked);
    connect(this->ui->bookmarkButton, &QPushButton::clicked, this, &MainWindow::onBookmarkButtonClicked);
    this->reloadContactWidget(this->contactList.getAllContacts());
}

void MainWindow::onShowBookmarksButtonClicked() {
    this->ui->bookmarkButton->setText("Unbookmark");
    disconnect(this->ui->bookmarkButton, &QPushButton::clicked, this, &MainWindow::onBookmarkButtonClicked);
    connect(this->ui->bookmarkButton, &QPushButton::clicked, this, &MainWindow::onUnbookmarkButtonClicked);
    this->reloadContactWidget(this->contactList.getBookmarkedContacts());
}

void MainWindow::onSearchButtonClicked() {
    const QString& textInput = this->ui->searchInput->text().trimmed();

    if (textInput.isEmpty()) {
        this->reloadContactWidget(this->contactList.getAllContacts());
        return;
    }

    if (this->ui->searchOptionComboBox->currentText() == "Search by name") {
        this->reloadContactWidget(this->contactList.searchByName(textInput.toLower()));
    } else {
        this->reloadContactWidget(this->contactList.searchByNumber(textInput.toLower()));
    }
}


/**********     private     **********/

void MainWindow::clearInputFields() const {
    this->ui->nameInput->clear();
    this->ui->phoneInput->clear();
    this->ui->emailInput->clear();
}

void MainWindow::reloadContactWidget(const std::vector<Contact>& contacts) {
    size_t size = contacts.size();
    QTableWidget& tableWidget = *this->ui->contactTableWidget;

    tableWidget.clearContents();
    tableWidget.setRowCount(size);
    tableWidget.setColumnWidth(CHECKBOX_COL, 25);

    for (size_t i = 0; i < size; i++) {
        const Contact& contact = contacts[i];

        QTableWidgetItem* checkBoxItem = new QTableWidgetItem();
        QTableWidgetItem* nameItem = new QTableWidgetItem(contact.getName());
        QTableWidgetItem* numberItem = new QTableWidgetItem(contact.getNumber());
        QTableWidgetItem* emailItem = new QTableWidgetItem(contact.getEmail());

        checkBoxItem->setCheckState(Qt::Unchecked);

        checkBoxItem->setFlags(checkBoxItem->flags() & ~Qt::ItemIsEditable);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        numberItem->setFlags(numberItem->flags() & ~Qt::ItemIsEditable);
        emailItem->setFlags(emailItem->flags() & ~Qt::ItemIsEditable);

        tableWidget.setItem(i, CHECKBOX_COL, checkBoxItem);
        tableWidget.setItem(i, NAME_COL, nameItem);
        tableWidget.setItem(i, NUMBER_COL, numberItem);
        tableWidget.setItem(i, EMAIL_COL, emailItem);
    }
}

void MainWindow::enableRemoveAndBookmarkButtons() {
    this->ui->removeButton->setEnabled(true);
    this->ui->bookmarkButton->setEnabled(true);
}

void MainWindow::disableRemoveAndBookmarkButtons() {
    this->ui->removeButton->setEnabled(false);
    this->ui->bookmarkButton->setEnabled(false);
}

void MainWindow::showWarningDialog(const QString &message) {
    QMessageBox::warning(this, "Warning: ", message);
}

void MainWindow::deleteWindowAndExit() {
    this->deleteLater();
    QCoreApplication::exit(1);
}

void MainWindow::updateContactFile() {
        try {
        this->fileHandler.saveContactsToFile(this->contactList.getContacts());
    } catch (const std::exception& e) {
        this->showWarningDialog(e.what());
        this->deleteWindowAndExit();
    }
}







