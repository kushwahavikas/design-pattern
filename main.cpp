//
//  main.cpp
//  abc
//
//  Created by Vikas on 05/03/23.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;
//using namespace boost;

enum class Color{green,red,blue};
enum class Size{small,medium,large};

struct Product{
    string name;
    Color color;
    Size size;
};

template <typename T> struct Specification
{
    virtual bool is_satisfied(T* item) const = 0;
};
template <typename T> struct Filter
{
    virtual vector<T*> ProductFilter(vector<T*> items, const Specification<T>& spec) = 0;
    // The reason & is used because specification struct has become abstract class with virtual function becuase of that we can't 
    // instantiate an object of it.  And also by using & it now has become an lvalue reference we can only reference to created 
    // already object.
    // if we want to send ColorSpecification {Color::green} then we have to make lvalue refrence to be constant and the function
    //which is using the lvalue reference needs to be constant.
    // before 
    //bool is_satisfied(T*) override , 
    //vector<Product *> ProductFilter(vector<Product *> items, Specification<Product> &spec) override
    //vector<Product*> result = bf.ProductFilter(items, color);
    //after 
    //bool is_satisfied(T*)const override , 
    //vector<Product *> ProductFilter(vector<Product *> items, const Specification<Product> &spec) override
    //vector<Product*> result = bf.ProductFilter(items, ColorSpecification {Color::green};
    // all of this change is because of this  -- ColorSpecification {Color::green} -- which is an rvalue.

};

struct ColorSpecification: Specification<Product>
{
    Color color;
    ColorSpecification (Color color):color{color}{};
    
    
    bool is_satisfied(Product *item) const override
    {
        return item->color == color;
    };
    
};
struct SizeSpecification: Specification<Product>
{
    Size size;
    SizeSpecification (Size size):size{size}{};
    
    
    bool is_satisfied(Product *item) const override
    {
        return item->size == size;
    }
    
};

struct BetterFilter:Filter<Product>
{
    
    vector<Product *> ProductFilter(vector<Product *> items, const Specification<Product> &spec) override
    {
        vector<Product*> result;
        
        for(auto &item:items)
        {
            if (spec.is_satisfied(item))
                result.push_back(item);
        }
        return result;
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Product p1{"Shree",Color::green,Size::small};
    Product p2{"Shree2",Color::blue,Size::medium};
    Product p3{"Shree3",Color::green,Size::small};
    
    vector<Product*> items {&p1,&p2,&p3};
    ColorSpecification color{Color::blue};
    BetterFilter bf;
    vector<Product*> result = bf.ProductFilter(items, ColorSpecification {Color::green});
    for(auto &item:result)
    {
        cout<< item->name<<endl;
    }
    return 0;
}
