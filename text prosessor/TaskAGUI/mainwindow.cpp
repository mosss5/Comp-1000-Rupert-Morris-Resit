#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    QString fileName = ui->filePathEdit->text();
    QString searchTerm = ui->searchTermEdit->text();
    bool isRegex = ui->regexCheckBox->isChecked();

    if (fileName.isEmpty() || searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please provide both file path and search term.");
        return;
    }

    performSearch(fileName, searchTerm, isRegex);
}

void MainWindow::performSearch(const QString &fileName, const QString &searchTerm, bool isRegex)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Cannot open file: " + fileName);
        return;
    }

    QTextStream in(&file);
    QString results;
    int totalWords = 0;
    int matches = 0;

    QRegularExpression regex;
    if (isRegex) {
        regex = QRegularExpression(searchTerm);
        if (!regex.isValid()) {
            QMessageBox::warning(this, "Regex Error", "Invalid regular expression.");
            return;
        }
    }

    int lineNumber = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        ++lineNumber;
        QStringList words = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        totalWords += words.size();
        int wordNumber = 0;
        for (const QString &word : words) {
            ++wordNumber;
            if ((isRegex && regex.match(word).hasMatch()) || (!isRegex && word.contains(searchTerm, Qt::CaseInsensitive))) {
                results += QString("Line %1, Word %2: %3\n").arg(lineNumber).arg(wordNumber).arg(word);
                ++matches;
            }
        }
    }

    file.close();

    double frequency = totalWords == 0 ? 0 : (static_cast<double>(matches) / totalWords) * 100;
    results += QString("\nTotal Matches: %1\nTotal Words: %2\nFrequency: %3%").arg(matches).arg(totalWords).arg(frequency);

    displayResults(results);
}

void MainWindow::displayResults(const QString &results)
{
    ui->resultsTextEdit->setPlainText(results);
}
