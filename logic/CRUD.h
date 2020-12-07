#ifndef CPP_UNIVERSITY_ASSIGMENT_CRUD_H
#define CPP_UNIVERSITY_ASSIGMENT_CRUD_H

#include "../service/Service.h"

#include "../util/Util.h"

template <typename T>
class CRUD {
protected:
    Service<T> *const service; //saljemo worker service ovde
    void addEntity(const T entity) const;/*1*/
    void deleteEntity(const long index) const;/*3*/
    void replace(const long index,T entity);
public:
    CRUD<T>(Service<T> *service);

//    virtual void createEntity(vector<string> &params) = 0;/*1*/
    virtual void replaceEntity(vector<string> &newParams, int id) = 0;/*2*/
    virtual void removeEntity(const long id) = 0;/*3*/
//    virtual long findIndex(const long &id) = 0;/*2*//*3*/
    void readEntities();
//    virtual long findIndex(long id) const = 0;

    long findIndex(long id) const {
        vector<T> *entities = service->getEntities();
        long index = cuaUtil::findIndex<T>(id,entities);
        return index;
    };

    void createEntity(vector<string> &params){
        T newEntity;
        params[0] = to_string(service->getLastUsedId());
        service->parseEntity(&newEntity, params);
        addEntity(newEntity);
    }
};

/*
 * crud operacija sadrzi promenljivu tipa servis
 * servis se poziva na kraju svake operacije
 * read poziva read servis i to samo prilikom inicilizacije programa gde ucitava sve podatka u vector na koj pokazuje i servis
 * delete brisemo preko id broja smanjujemo ukupan broj elemenata brisem poziciju u arrayu ali pre toga ga izbacujemo iz odeljenja ako je u jednom snimimo fajl preko servicesa
 * replace preko pointera promenimo polja koja se menjaju i snimimo fajl preko servisa
 * create povecam id povecam broj elemenata stavim na kraj vectora i snimim preko servisa*/

#endif //CPP_UNIVERSITY_ASSIGMENT_CRUD_H
