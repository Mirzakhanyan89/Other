/*	pdf_to_txt.cpp	
	to compile this file You must have in your computer poppler pdf reader
	and You must compile in this way
	g++ -std=c++20 pdf_to_txt.cpp -lpoppler-cpp
*/ 

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <fstream>

std::string readPDF(const std::string& filePath);
std::string processString(const std::string& input);
void saveToTxtFile(const std::string& input, const std::string& fileName);

int main() {
    std::string filePath = "LeetCode.pdf";
    std::string pdfContent = readPDF(filePath);
    std::cout << pdfContent << std::endl;

	std::string processed = processString(pdfContent);
    std::cout << "Processed string: " << processed << std::endl;

    std::string fileName = "to_txt.txt";
    saveToTxtFile(processed, fileName);


return 0;
}

std::string readPDF(const std::string& filePath) {
    std::string result;

    try {
        poppler::document* pdfDoc = poppler::document::load_from_file(filePath);
        if (!pdfDoc || pdfDoc->is_locked()) {
            throw std::runtime_error("Failed to load PDF document");
        }

        for (int i = 0; i < pdfDoc->pages(); ++i) {
            poppler::page* pdfPage = pdfDoc->create_page(i);
            if (!pdfPage) {
                throw std::runtime_error("Failed to create PDF page");
            }

            result += pdfPage->text().to_latin1();
            delete pdfPage;
        }

        delete pdfDoc;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return result;
}

std::string processString(const std::string& input) {
    // Step 1: Convert the string to lowercase
    std::string lowercase = input;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    // Step 2: Remove extra characters and convert to words
    std::string word;
    std::stringstream ss(lowercase);
    std::unordered_set<std::string> uniqueWords;
    while (ss >> word) {
        // Remove non-alphanumeric characters
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
            return !std::isalnum(c);
        }), word.end());

        // Step 3: Add the processed word to the set of unique words
        uniqueWords.insert(word);
    }

    // Step 4: Create the final string by joining unique words with spaces
    std::string result;
    for (const std::string& uniqueWord : uniqueWords) {
        result += uniqueWord + "\n";
    }

    // Remove the trailing space, if any
    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}


void saveToTxtFile(const std::string& input, const std::string& fileName) {
    std::ofstream outputFile(fileName);

    if (outputFile.is_open()) {
        outputFile << input;
        outputFile.close();
        std::cout << "File saved successfully." << std::endl;
    } else {
        std::cerr << "Error opening the file." << std::endl;
    }
}




