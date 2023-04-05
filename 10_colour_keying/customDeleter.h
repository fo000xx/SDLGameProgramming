#ifndef CUSTOMDELETER_H
#define CUSTOMDELETER_H

//custom deleter for the unique pointer
template<typename T>
void custom_delete(T* d) {}

template<typename T>
struct custom_deleter
{
    void operator()(T* d) const
    {
        custom_delete(d);
    }
};

#endif