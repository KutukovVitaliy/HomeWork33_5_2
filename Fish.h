//
// Created by kvit on 31.03.2022.
//

#ifndef HOMEWORK33_5_2_FISH_H
#define HOMEWORK33_5_2_FISH_H

#include <exception>
#include <string>

enum class FieldType{
    empty,
    boot,
    fish
};
class NewException : public std::exception{
    FieldType type;
public:
    NewException(): type(FieldType::empty){}
    NewException(FieldType inType) : type(inType){}

    FieldType GetType(){
        return type;
    }


};
class EmptyException: public NewException{

public:
    EmptyException() : NewException(FieldType::empty){}
    const char* what() const noexcept override{
        return "Empty casting.";
    }

};

class BootException: public NewException{

public:
    BootException() : NewException(FieldType::boot){}
    const char* what() const noexcept override{
        return "You have caught a boot.";
    }

};

class FishException: public NewException{

public:
    FishException() : NewException(FieldType::fish){}
    const char* what() const noexcept override{
        return "You have caught a fish.";
    }

};

class Empty{
    FieldType type;
    std::string name;
public:
    Empty(){
        type = FieldType::empty;
        name = "Empty";
    }
    Empty(FieldType inType, std::string inName): type(inType), name(inName){}
    virtual void cast() const {
        throw EmptyException();
    }
    FieldType GetType(){
        return  type;
    }
    void SetType(FieldType inType){
        type = inType;
    }
    std::string GetName(){
        return name;
    }
};

class Boot : public Empty{

public:
    Boot(): Empty(FieldType::boot, "Boot"){}
    void cast() const override {
        throw BootException();
    }
};

class Fish : public Empty{

public:
    Fish(): Empty(FieldType::fish, "Fish"){}
    void cast() const override {
        throw FishException();
    }
};


#endif //HOMEWORK33_5_2_FISH_H
