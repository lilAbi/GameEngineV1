
#ifndef BLOCKRPG_COMPONENTARRAY_H
#define BLOCKRPG_COMPONENTARRAY_H
#include <array>



namespace ECS {

    class IComponentArray{};

    //Construct an array of data of type Component
    template<typename ComponentType>
    class ComponentArray: public IComponentArray{
    public:
        using CompType = ComponentType;

        explicit ComponentArray(int size): compSize{size} {dataArr = new CompType[size]{};}
        ~ComponentArray() {delete dataArr;}

        //returns ptr to the data location by index
        CompType* GetDataAt(int index) { return (index > compSize) ? nullptr : &(dataArr[index]); }

    public:
        int compSize;
        CompType* dataArr;
    };



}

#endif //BLOCKRPG_COMPONENTARRAY_H
