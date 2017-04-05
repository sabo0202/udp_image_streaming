//
//  MyGaze.hpp
//  eyeTest
//
//  Created by SHO on 2016/04/13.
//  Copyright © 2016年 SHO. All rights reserved.
//

#ifndef MyGaze_hpp
#define MyGaze_hpp

#include <stdio.h>
#include "gazeapi.h"
#include <iostream>
#include <iomanip>

// --- MyGaze definition
class MyGaze : public gtl::IGazeListener
{
public:
    MyGaze();
    ~MyGaze();
    float x, y; //added
private:
    // IGazeListener
    void on_gaze_data( gtl::GazeData const & gaze_data );
private:
    gtl::GazeApi m_api;
};



#endif /* MyGaze_hpp */
