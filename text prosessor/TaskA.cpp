#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <string>

using namespace std;

class FileHandler {
public:
    FileHandler(const string& fileName) : fileName(fileName) {}
    bool readFile();
    void displayFile() const;
    const vector<string>& getLines() const { return lines; }
private:
    string fileName;
    vector<string> lines;
};

bool FileHandler::readFile() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << fileName << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return true;
}

void FileHandler::displayFile() const {
    cout << "File Contents:" << endl;
    for (const auto& line : lines) {
        cout << line << endl;
    }
}

class Search {
public:
    Search(const vector<string>& lines, const string& searchTerm, bool isRegex)
        : lines(lines), searchTerm(searchTerm), isRegex(isRegex) {}
    void performSearch();
    void displayResults();
    void saveResults(const string& fileName);

private:
    vector<string> lines;
    string searchTerm;
    bool isRegex;
    vector<pair<int, int>> matches;
    int totalWords = 0;

    void searchSimple();
    void searchRegex();
};

void Search::performSearch() {
    if (isRegex) {
        searchRegex();
    }
    else {
        searchSimple();
    }
}

void Search::searchSimple() {
    for (int i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string word;
        int wordNumber = 0;
        while (ss >> word) {
            ++totalWords;
            ++wordNumber;
            if (word.find(searchTerm) != string::npos) {
                matches.push_back({ i, wordNumber });
            }
        }
    }
}

void Search::searchRegex() {
    regex reg(searchTerm);
    for (int i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string word;
        int wordNumber = 0;
        while (ss >> word) {
            ++totalWords;
            ++wordNumber;
            if (regex_search(word, reg)) {
                matches.push_back({ i, wordNumber });
            }
        }
    }
}

void Search::displayResults() {
    cout << "Search Results:" << endl;
    for (const auto& match : matches) {
        cout << "Line " << match.first + 1 << ", Word " << match.second << endl;
    }
    cout << "Total Matches: " << matches.size() << endl;
    cout << "Total Words: " << totalWords << endl;
    cout << "Frequency: " << (static_cast<double>(matches.size()) / totalWords) * 100 << "%" << endl;
}

void Search::saveResults(const string& fileName) {
    ofstream outFile(fileName, ios::app);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open file " << fileName << endl;
        return;
    }

    outFile << searchTerm << "," << matches.size() << "," << (static_cast<double>(matches.size()) / totalWords) * 100 << "%" << endl;
    outFile.close();
}

int findArg(int argc, char* argv[], const string& pattern) {
    for (int n = 1; n < argc; ++n) {
        if (string(argv[n]) == pattern) {
            return n;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Error: Insufficient arguments provided." << endl;
        return EXIT_FAILURE;
    }

    string fileName(argv[1]);
    string searchString(argv[2]);
    bool isRegex = (findArg(argc, argv, "-regex") != 0);

    FileHandler fileHandler(fileName);
    if (!fileHandler.readFile()) {
        return EXIT_FAILURE;
    }

    fileHandler.displayFile();  // Display the file contents

    Search search(fileHandler.getLines(), searchString, isRegex);
    search.performSearch();
    search.displayResults();
    search.saveResults("results.csv");

    return EXIT_SUCCESS;
}