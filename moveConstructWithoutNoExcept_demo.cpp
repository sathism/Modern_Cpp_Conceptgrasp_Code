#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class Test
{
   private :
    size_t len;
    int *data;

  public :
    Test(Test && ref)  : len(std::exchange(ref.len, 0)),
                                 data(std::exchange(ref.data, nullptr))
    {
       std::cout << "Test :: move constructor\n";
       std::cout << "Len = " << len <<"\n";
    }

    Test& operator=(Test && ref) 
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
        delete [] data;
    }

    Test() : Test(10)
    {
        std::cout <<" Default constructor\n";
    }
    Test(const Test &ref) : len(ref.len),
                            data(ref.len ? new int[len] : nullptr)
    {
        std::copy(ref.data, ref.data + len, data);
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
   std::vector<Test> v;
   v.emplace_back();
   v.emplace_back();

}

