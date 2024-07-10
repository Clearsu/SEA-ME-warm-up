#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "ContactList.hpp"

#define CHECKBOX_COL 0
#define NAME_COL 1
#define NUMBER_COL 2
#define EMAIL_COL 3

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void	onAddContactButtonClicked();
    void	onSaveButtonClicked();
    void	onCancelButtonClicked();
    void	onBookmarkButtonClicked();
    void	onUnbookmarkButtonClicked();
    void	onRemoveButtonClicked();
    void	onCheckBoxClicked(QTableWidgetItem *item);
    void	onShowAllContactsButtonClicked();
    void	onShowBookmarksButtonClicked();
    void	onSearchButtonClicked();

private:
    Ui::MainWindow *ui;
    ContactList		contactList;
    int				checkCount;

    void	clearInputFields() const;
    void	reloadContactWidget(const std::vector<Contact>& contacts);

    void	enableRemoveAndBookmarkButtons();
    void	disableRemoveAndBookmarkButtons();

    void	showWarningDialog(const QString& message);

};
#endif // MAINWINDOW_H
