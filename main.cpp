#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include "Hyena.h"
#include "Lion.h"
#include "Tiger.h"
#include "Bear.h"

using namespace std;

// Constants for file paths and formatting
const string INPUT_FILE = "C:\\cpptxtfiles\\arrivingAnimals.txt";
const string OUTPUT_FILE = "C:\\cpptxtfiles\\newAnimals.txt";
const vector<string> HABITATS = {"hyena", "lion", "tiger", "bear"};

// Parse first line of animal data (age, gender, species)
tuple<int, string, string> parseFirstLine(const string& line) {
    istringstream iss(line);
    string ageStr, temp, gender, species;
    
    iss >> ageStr;
    int age = stoi(ageStr);
    if (age <= 0) throw runtime_error("Invalid age: " + ageStr);
    
    // Skip "year old"
    iss >> temp >> temp;
    iss >> gender >> species;
    if (species.back() == ',') species.pop_back();
    
    return {age, gender, species};
}

// Parse second line of animal data (birth season, color, weight, origin)
tuple<string, string, double, string> parseSecondLine(const string& line1, const string& line2) {
    string birthSeason, color, origin;
    double weight;
    string fullLine = line1 + " " + line2;
    
    // Extract birth season
    if (line1.find("unknown birth season") != string::npos) {
        birthSeason = "unknown";
        // Find the start of the color description after "unknown birth season"
        size_t colorStart = line1.find("unknown birth season");
        // Find the comma after "season"
        colorStart = line1.find(",", colorStart);
        if (colorStart != string::npos) {
            // Skip the comma
            colorStart++;
            // Skip any whitespace
            while (colorStart < line1.length() && isspace(line1[colorStart])) {
                colorStart++;
            }
        }
        
        size_t colorEnd = line1.find(" color,", colorStart);
        if (colorEnd == string::npos) {
            // Color might be split across lines
            string remainingColor = line1.substr(colorStart);
            if (!remainingColor.empty() && remainingColor.back() == ',') {
                remainingColor.pop_back();
            }
            colorEnd = line2.find(" color,");
            if (colorEnd == string::npos) throw runtime_error("Color format not found");
            color = remainingColor + line2.substr(0, colorEnd);
        } else {
            color = line1.substr(colorStart, colorEnd - colorStart);
        }
        
        // Clean up any extra spaces
        while (color.find("  ") != string::npos) {
            color.replace(color.find("  "), 2, " ");
        }
        if (!color.empty() && color[0] == ' ') color = color.substr(1);
        if (!color.empty() && color.back() == ' ') color.pop_back();
    } else {
        size_t seasonStart = line1.find("born in ");
        if (seasonStart == string::npos) throw runtime_error("Birth season not found");
        seasonStart += 8;
        size_t seasonEnd = line1.find(",", seasonStart);
        if (seasonEnd == string::npos) throw runtime_error("Invalid birth season format");
        birthSeason = line1.substr(seasonStart, seasonEnd - seasonStart);
        
        // Extract color
        size_t colorStart = seasonEnd + 1;
        while (colorStart < line1.length() && line1[colorStart] == ' ') colorStart++;
        size_t colorEnd = line1.find(" color,", colorStart);
        if (colorEnd == string::npos) throw runtime_error("Color format not found");
        color = line1.substr(colorStart, colorEnd - colorStart);
    }
    
    // Extract weight - handle line wrapping
    string weightStr;
    size_t weightStart = fullLine.find(" color,");
    if (weightStart == string::npos) throw runtime_error("Weight format not found");
    weightStart += 7;
    while (weightStart < fullLine.length() && fullLine[weightStart] == ' ') weightStart++;
    
    size_t weightEnd = fullLine.find(" pounds", weightStart);
    if (weightEnd == string::npos) throw runtime_error("Weight format not found");
    weightStr = fullLine.substr(weightStart, weightEnd - weightStart);
    
    // Clean up weight string and convert to number
    weightStr.erase(remove_if(weightStr.begin(), weightStr.end(), 
                            [](char c) { return c == ',' || isspace(c); }), 
                   weightStr.end());
    
    try {
        weight = stod(weightStr);
        if (weight <= 0) throw runtime_error("Invalid weight value");
    } catch (const exception&) {
        throw runtime_error("Invalid weight format");
    }
    
    // Extract origin
    size_t originStart = fullLine.find("from ");
    if (originStart == string::npos) throw runtime_error("Origin not found");
    originStart += 5;
    origin = fullLine.substr(originStart);
    if (origin.back() == ',') origin.pop_back();
    
    return {birthSeason, color, weight, origin};
}

// Parses animal data and creates appropriate animal object
unique_ptr<Animal> parseAnimalData(const string& line1, const string& line2) {
    try {
        // Parse first line
        auto [age, gender, species] = parseFirstLine(line1);
        
        // Parse second line
        auto [birthSeason, color, weight, origin] = parseSecondLine(line1, line2);
        
        // Create appropriate animal type based on species
        // Transform species to lowercase for comparison
        string lowerSpecies = species;
        transform(lowerSpecies.begin(), lowerSpecies.end(), lowerSpecies.begin(), ::tolower);
        
        if (lowerSpecies == "hyena") {
            return make_unique<Hyena>(age, gender, birthSeason, color, weight, origin);
        }
        if (lowerSpecies == "lion") {
            return make_unique<Lion>(age, gender, birthSeason, color, weight, origin);
        }
        if (lowerSpecies == "tiger") {
            return make_unique<Tiger>(age, gender, birthSeason, color, weight, origin);
        }
        if (lowerSpecies == "bear") {
            return make_unique<Bear>(age, gender, birthSeason, color, weight, origin);
        }
        
        throw runtime_error("Unknown species: " + species);
    }
    catch (const exception& e) {
        cerr << "Error parsing animal data: " << e.what() << "\nLine 1: " << line1 << "\nLine 2: " << line2 << endl;
        return nullptr;
    }
}

// Returns current date in "MMM DD, YYYY" format
string getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%b %d, %Y");
    return ss.str();
}

// Generates animal ID in format [Species prefix]## (e.g., HY01)
string generateId(const string& species, int count) {
    // Convert species prefix to uppercase
    string prefix = species.substr(0, 2);
    transform(prefix.begin(), prefix.end(), prefix.begin(), ::toupper);
    return prefix + (count < 10 ? "0" : "") + to_string(count);
}

// Process animals from input file and return vector of parsed animals
vector<unique_ptr<Animal>> processInputFile() {
    vector<unique_ptr<Animal>> animals;
    ifstream inFile(INPUT_FILE);
    
    if (!inFile) {
        throw runtime_error("Could not open input file '" + INPUT_FILE + "'");
    }

    string line1, line2;
    int lineCount = 0;
    
    while (getline(inFile, line1)) {
        lineCount++;
        if (!getline(inFile, line2)) {
            throw runtime_error("Incomplete animal record at line " + to_string(lineCount));
        }
        
        cout << "Processing animal record at lines " << lineCount << "-" << (lineCount + 1) << "...\n";
        if (auto animal = parseAnimalData(line1, line2)) {
            string species = animal->getSpecies();
            transform(species.begin(), species.end(), species.begin(), ::tolower);
            animals.push_back(move(animal));
            cout << "Successfully processed " << species << "\n";
        }
        
        lineCount++;
    }
    
    inFile.close();
    return animals;
}

// Write animals to output file grouped by habitat
void writeOutputFile(const vector<unique_ptr<Animal>>& animals) {
    ofstream outFile(OUTPUT_FILE);
    if (!outFile) {
        throw runtime_error("Could not create output file '" + OUTPUT_FILE + "'");
    }

    string currentDate = getCurrentDate();
    map<string, int> idCounter;
    
    for (const auto& habitat : HABITATS) {
        string title = habitat;
        title[0] = toupper(title[0]);
        outFile << title << " Habitat:\n";
        cout << "Writing " << title << " habitat information...\n";
        
        for (const auto& animal : animals) {
            string species = animal->getSpecies();
            transform(species.begin(), species.end(), species.begin(), ::tolower);
            
            if (species == habitat) {
                idCounter[species]++;
                string id = generateId(species, idCounter[species]);
                outFile << id << "; " << animal->getDescription()
                       << "; arrived " << currentDate << "\n";
            }
        }
        outFile << "\n";
    }
    
    outFile.close();
}

int main() {
    cout << "Zoo Management System\n--------------------\n";
    
    try {
        // Process input file
        cout << "Reading input file...\n";
        auto animals = processInputFile();
        cout << "\nProcessed " << animals.size() << " animals successfully.\n\n";

        // Generate output report
        cout << "Generating report...\n";
        writeOutputFile(animals);
        cout << "\nReport generated successfully in '" << OUTPUT_FILE << "'\n";
        cout << "Program completed successfully!\n";
        return 0;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
