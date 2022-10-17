
#ifndef BLOCKRPG_TYPEIDGENERATOR_H
#define BLOCKRPG_TYPEIDGENERATOR_H


namespace util{

    template<typename Type>
    class TypeIDGenerator {
    public:
        TypeIDGenerator() = default;
        ~TypeIDGenerator() = default;

        static unsigned int GenNewID(){return ++count;}

    private:
        inline static unsigned int count{0};
    };

};

#endif //BLOCKRPG_TYPEIDGENERATOR_H

