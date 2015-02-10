#ifndef INC_RANDOM_OP
#define INC_RANDOM_OP

class Random_operation
{
public:
    Random_operation( unsigned int seed = 1, int range = 100000 );

    void Set_seed( unsigned int seed );

    void Randomize_next_op();

    char Get_op();
    int  Get_key();
    int* Get_data();
private:
    char current_operation;
    int  current_key;
    int  current_range;
    int current_data;
};

#endif /* INC_RANDOM_OP */
