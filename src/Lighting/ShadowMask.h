//
// Created by tibov on 03/05/23.
//

#ifndef ENGINE_SHADOWMASK_H
#define ENGINE_SHADOWMASK_H


#include <vector>
using namespace std;
class ShadowMask: public vector<vector<double>> {
public:
    ShadowMask(unsigned int width, unsigned int height);
    ShadowMask();

private:
    unsigned int width;
    unsigned int height;
};



#endif //ENGINE_SHADOWMASK_H
