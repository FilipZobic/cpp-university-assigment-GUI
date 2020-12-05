#include "Service.h"
#include <fstream>
#include <stdexcept>
#include "../util/Util.h"
#include "../model/Department.h"

template <typename T>
Service<T>::Service(const string &filename,vector<T>* entities) : filename(filename),entities(entities),lastUsedId(0),amountOfItems(0) {
}

template <typename T>
ifstream& Service<T>::readFirstLine(ifstream& file){
    string line;
    getline(file,line);

    vector<string> lines;

    cuaUtil::parseStringIntoVector(line, lines, "|*|");

    this->amountOfItems = stol(lines.at(0));
    this->lastUsedId = stol(lines.at(1));

    lines.erase(lines.begin(), lines.end());
    return file;
};

template <typename T>
void Service<T>::readAllLines(vector<string>& lines,ifstream &file){
    string line;
    int i = 0;
    while (i<amountOfItems){
        getline(file,line);
        lines.push_back(line);
        i++;
    }
};

template <typename T>
template<typename Y>
void Service<T>::openFile(Y &file){

    file.open("../database/"+this->filename);
    if (!file.is_open()){ // add error function which opens file
        throw std::runtime_error("Could not open file"); //parse entity function samo redifinisemo sve ostalo moze da bude csv separator
    }

}

// funkcija koja ucitava ta dva parametra
//vrati vector stringova linije

template <typename T> // protected mozda
vector<string> Service<T>::readFromFile(){ // path to file change

    //Opening
    ifstream file;
    openFile<ifstream>(file);

    //Reading
    readFirstLine(file);
    vector<string> lines;
    readAllLines(lines,file);

    //Closing
    file.close();
    return lines;
}

template <typename T>
void Service<T>::writeAllLines(ofstream &file) const{
    string firstLine = to_string(this->amountOfItems) + "|*|" + to_string(this->lastUsedId);
    file << firstLine << "\n";
    for (T entity : (*this->entities)) {
        file << entity->Serialize() << "\n";
    }
};

template <typename T>
void Service<T>::writeToFile() {

    //Opening
    ofstream file;
    openFile<ofstream>(file);

    writeAllLines(file);

    file.close();
}

template<typename T>
const string &Service<T>::getFilename() const {
    return filename;
}

template<typename T>
void Service<T>::setFilename(const string &filename) {
    Service::filename = filename;
}

template<typename T>
int Service<T>::getAmountOfItems() const {
    return amountOfItems;
}

template<typename T>
void Service<T>::setAmountOfItems(int amountOfItems) {
    Service::amountOfItems = amountOfItems;
}

template<typename T>
long Service<T>::getLastUsedId() const {
    return lastUsedId;
}

template<typename T>
void Service<T>::setLastUsedId(long lastUsedId) {
    Service::lastUsedId = lastUsedId;
}

template<typename T>
vector<T> *Service<T>::getEntities() const {
    return entities;
}

template<typename T>
void Service<T>::setEntities(vector<T> *entities) {
    Service::entities = entities;
}

template class Service<Worker*>;
template class Service<Department*>;

