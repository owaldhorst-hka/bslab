//
//  test-blockdevice.cpp
//  testing
//
//  Created by Oliver Waldhorst on 15.12.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#include "../catch/catch.hpp"

#include <stdio.h>
#include <string.h>

#include "tools.hpp"

#include "blockdevice.h"

#define BD_PATH "/tmp/bd.bin"
#define NUM_TESTBLOCKS 1024
#define BLOCK_SIZE 512

// Declarations of helper functions
void bdWriteRead(BlockDevice *bd, int noBlocks= 1);

TEST_CASE( "BD_CREATE_WRITE_READ_NEW_FILE", "[blockdevice]" ) {
    
    remove(BD_PATH);

    BlockDevice bd(BLOCK_SIZE);
    REQUIRE(bd.create(BD_PATH) == 0);

    SECTION("write single block") {
        bdWriteRead(&bd);
    }
    
    SECTION("write multiple blocks") {
        bdWriteRead(&bd, NUM_TESTBLOCKS);
    }
    
    REQUIRE(bd.close() == 0);
    remove(BD_PATH);
    
}

TEST_CASE( "BD_CREATE_WRITE_READ_EXISTING_FILE", "[blockdevice]" ) {

    // Write to new file

    remove(BD_PATH);

    BlockDevice bd(BLOCK_SIZE);
    REQUIRE(bd.create(BD_PATH) == 0);

    bdWriteRead(&bd, NUM_TESTBLOCKS);

    REQUIRE(bd.close() == 0);

    // Open existing file

    BlockDevice bd2(BLOCK_SIZE);
    REQUIRE(bd2.open(BD_PATH) == 0);

    bdWriteRead(&bd2, NUM_TESTBLOCKS);

    REQUIRE(bd2.close() == 0);

    // Create on existing file
    BlockDevice bd3(BLOCK_SIZE);
    REQUIRE(bd3.create(BD_PATH) == 0);

    bdWriteRead(&bd3, NUM_TESTBLOCKS);

    REQUIRE(bd3.close() == 0);

}

TEST_CASE( "BD_OPEN_NON-EXISTING_FILE", "[blockdevice]" ) {

    remove(BD_PATH);

    BlockDevice bd(BLOCK_SIZE);
    REQUIRE(bd.open(BD_PATH) < 0);
}

// ***
// *** Helper functions
// ***

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
