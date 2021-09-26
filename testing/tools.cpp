//
//  Created by Oliver Waldhorst on 15.12.17.
//  Copyright © 2017-2020 Oliver Waldhorst. All rights reserved.
//

#include <cstdlib>
#include <string.h>

#include "../catch/catch.hpp"

#include "tools.hpp"

void gen_random(char *s, const int len) {
    static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}

// TODO: Implement you helper functions here
