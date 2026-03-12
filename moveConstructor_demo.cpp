#include <iostream>
#include <utility>

class Test
{
   private :
    size_t len;
    int *data;

  public :
    Test(Test && ref) noexcept : len(std::exchange(ref.len, 0)),
                                 data(std::exchange(ref.data, nullptr))
    {
       std::cout << "Test :: move constructor\n";
       std::cout << "Len = " << len <<"\n";
    }

    Test& operator=(Test && ref) noexcept
    {
        if(this != &ref)
        {
           std::cout << "Test :: move assignment\n";
           delete [] data;
           this->data = (std::exchange(ref.data, nullptr));
           this->len = (std::exchange(ref.len,0));
           
        }
       return *this;
    }

    Test(int size_)
    {
         len = size_;
         data = new int[size_];
         for(int i = 0; i < len ; i++)
         {
            data[i] = i * size_;
            //std::cout << data[i] <<"\n";
         }

    }

    ~Test()
    {
         if(data)
            delete [] data;
    }

    Test(const Test &ref)
    {
         len = ref.len;
         data = new int[len];
         if(data)
         {
            for(int i = 0 ; i < len; i++)
               data[i] = ref.data[i] ;
         }
        std::cout << "Test :: Copy Constructor \n";
    }
    void print()
    {
       std::cout << "Test::print \n";
       for( int i = 0 ; i < len ; i++)
            std::cout << data[i] <<"\n";
    }
  
};

int main()
{
   Test x(10);
   Test y = x;
   const Test z(30);
   std::cout << "printing y\n";
   y.print();
   Test x1 = std::move(Test(20));
   x1.print();
   y = std::move(x1);
   Test y1 = std::move(z); //This invokes copy constructor
   return 0;
}

