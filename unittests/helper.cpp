//
//  helper.cpp
//  testing
//
//  Created by Oliver Waldhorst on 15.12.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#include <cstdlib>
#include <string.h>

#include "catch.hpp"
#include "helper.hpp"

void gen_random(char *s, const int len) {
    static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
}

void bdWriteRead(BlockDevice *bd, int noBlocks) {
    char* r= new char[BD_BLOCK_SIZE * noBlocks];
    memset(r, 0, BD_BLOCK_SIZE * noBlocks);

    char* w= new char[BD_BLOCK_SIZE * noBlocks];
    gen_random(w, BD_BLOCK_SIZE * noBlocks);

    // write all blocks
    for(int b= 0; b < noBlocks; b++) {
        REQUIRE(bd->write(b, w + b*BD_BLOCK_SIZE) == 0);
    }

    // read all blocks
    for(int b= 0; b < noBlocks; b++) {
        REQUIRE(bd->read(b, r + b*BD_BLOCK_SIZE) == 0);
    }

    REQUIRE(memcmp(w, r, BD_BLOCK_SIZE * noBlocks) == 0);

    delete [] r;
    delete [] w;
}

// TODO: Implement you helper functions here
