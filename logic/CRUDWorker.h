#ifndef CPP_UNIVERSITY_ASSIGMENT_CRUDWORKER_H
#define CPP_UNIVERSITY_ASSIGMENT_CRUDWORKER_H
#include "string"
#include "CRUD.h"

using namespace std;


class CRUDWorker : public CRUD<Worker*> {
private:
    long findIndex(const long &id) override;
public:
    CRUDWorker(Service<Worker *> *service);

    void createEntity(vector<string> &params) override;

    void removeEntity(const long id) override;

    void replaceEntity(vector<string> &newParams, int id) override;

};


#endif //CPP_UNIVERSITY_ASSIGMENT_CRUDWORKER_H
