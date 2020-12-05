//
// Created by filipz on 12/5/20.
//

#include "Business.h"

Business::Business() {}

Business::Business(const string &name, long registrationNumber, long vat,vector<Department *> *departments)
        : name(name), registrationNumber(registrationNumber), vat(vat), departments(departments) {}

void Business::operator<<(Department *department) {
    this->departments->push_back(department);
}

string Business::Serialize() {

    string departmentsString = "";
    if (!departments->empty()){
        for (Department *ref : (*departments)) {
            departmentsString += to_string(ref->getId()) + ",";
        }
        departmentsString.erase(departmentsString.size()-1,departmentsString.size());
    } else{
        departmentsString += "-1";
    }

    return this->name + sep + to_string(this->registrationNumber) + sep + to_string(this->vat) + sep + departmentsString;
}

void Business::Parse(vector<string> *parameters) {

}
