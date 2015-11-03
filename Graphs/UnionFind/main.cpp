#include "UF.h"

#include <iostream>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    UF *uf = new UF(100);

    cout<<uf->Find(10)<<endl;
    cout<<uf->Find(11)<<endl;

    if(!uf->connected(10, 11))
       cout<<"Not Connected!"<<endl;

    uf->Union(10, 11);
    cout<<"here"<<endl;

    cout<<uf->Find(10)<<endl;
    cout<<uf->Find(11)<<endl;

    if(uf->connected(10, 11))
       cout<<"Connected!"<<endl;

    return 0;
}
