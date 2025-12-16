#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermenu.h"
#include "core.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_app(new App(this))
{

    ui->setupUi(this);
    setWindowTitle("Saraha Login / Register");

    QObject::connect(m_app, &App::loginSuccessful,
                     this, &MainWindow::handleLoginSuccess);

    QObject::connect(m_app, &App::loginFailed,
                     this, &MainWindow::handleLoginFailure);

    QObject::connect(m_app, &App::registrationSuccess,
                     this, &MainWindow::handleRegistrationSuccess);

    QObject::connect(m_app, &App::registrationFailed,
                     this, &MainWindow::handleRegistrationFailure);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    // 1. Get data from the View
    std::string uname = ui->usernameLineEdit->text().toStdString();
    std::string pass = ui->lineEdit_2->text().toStdString();

    // 2. Call the Model's logic method. The Model will emit a signal when done.
    m_app->login(uname, pass);

    // Clear password field after attempt
    ui->lineEdit_2->clear();
    ui->usernameLineEdit->clear();
}

void MainWindow::on_registerButton_clicked()
{
    std::string uname = ui->usernameLineEdit->text().toStdString();
    std::string pass = ui->lineEdit_2->text().toStdString();

    m_app->registerUser(uname, pass);
    ui->lineEdit_2->clear();
}

void MainWindow::handleLoginSuccess(User* loggedInUser)
{
    // Pass the loggedInUser and the m_app to the new window
    UserMenu *menu = new UserMenu(loggedInUser, m_app);
    menu->show();

    // Close the login window
    this->close();
}


void MainWindow::handleLoginFailure(const QString& reason)
{
    setStatusMessage(reason, true);
}


void MainWindow::handleRegistrationSuccess(const QString& msg)
{
    setStatusMessage(msg, false);
    ui->statusLabel->setText(msg);

}

void MainWindow::handleRegistrationFailure(const QString& reason)
{
    setStatusMessage(reason, true);
    ui->statusLabel->setText(reason);
}

void MainWindow::setStatusMessage(const QString& message, bool isError)
{
    // Set the text and change the color to indicate success (green) or error (red)
    QString style = isError ? "color: red;" : "color: green;";
    ui->statusLabel->setText(message);
    ui->statusLabel->setStyleSheet(style);
}

void MainWindow::switchToUserMenu()
{
    // For a simple app, you might hide the login widgets and show the user widgets.
    // For a complex app, you use a QStackedWidget (recommended).
    // ui->stackedWidget->setCurrentIndex(1);
}


