#pragma once
#include<iostream>

class tree_exception :
    public std::exception
{
public:
    tree_exception(const std::string& descr)
    {
        description = descr;
    }
    tree_exception() {}
    const char* what() const noexcept
    {
        return description.c_str();
    }
    /*T1 getKey() const
    {
        return key;
    }*/
protected:
    std::string description;
};

class insert_error : public tree_exception
{
public:
    insert_error()
    {
       // this->key = key;
        tree_exception::description = "Insert error: the element with this key doesn't exist";
    }
};

class append_error : public tree_exception
{
public:
    append_error()
    {
        tree_exception::description = "Append error: the element with this key already exist";
    }
};

class errase_error : public tree_exception
{
public:
    errase_error()
    {
        //this->key = key;
        tree_exception::description = "Errase error: the element with this key doesn't exist";
    }
};

class find_error : public tree_exception
{
public:
    find_error()
    {
        //this->key = key;
        tree_exception::description = "Find error: the element with this key doesn't exist";
    }
};

