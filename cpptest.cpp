//
// Created by vipl on 2022/9/10.
//

#include <iostream>
#include <fstream>

int main()
{
    std::ifstream ifs;
    ifs.open("/home/vipl/VIPL2021-CJ/codes/github/tandem/tandem/results/tracking/dense/euroc/V1_01_easy/camera.txt");
    std::string firstline;
    std::getline(ifs, firstline);
    ifs.close();
    float ic[5];
    std::cout<<firstline;
    std::sscanf(firstline.c_str(),"%f %f %f %f %f", &ic[0],&ic[1],&ic[2],&ic[3],&ic[4]);
    return 0;
}




