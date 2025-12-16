#pragma once

#include <QMainWindow>
#include "core.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();


    void handleLoginSuccess(User* loggedInUser);
    void handleLoginFailure(const QString& reason);
    void handleRegistrationSuccess(const QString& msg);
    void handleRegistrationFailure(const QString& reason);



   // void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    App* m_app;
    User* m_currentUser = nullptr;

    void setStatusMessage(const QString& message, bool isError = false);
    void switchToUserMenu();
};
