//
//  test-blockdevice.cpp
//  testing
//
//  Created by Oliver Waldhorst on 15.12.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#include "catch.hpp"

#include <stdio.h>
#include <string.h>

#include "helper.hpp"

#include "blockdevice.h"

#define BD_PATH "/tmp/bd.bin"
#define NUM_TESTBLOCKS 1024

TEST_CASE( "BD_CREATE_WRITE_READ_NEW_FILE", "[blockdevice]" ) {
    
    remove(BD_PATH);

    BlockDevice bd;
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

    BlockDevice bd;
    REQUIRE(bd.create(BD_PATH) == 0);

    bdWriteRead(&bd, NUM_TESTBLOCKS);

    REQUIRE(bd.close() == 0);

    // Open existing file

    BlockDevice bd2;
    REQUIRE(bd2.open(BD_PATH) == 0);

    bdWriteRead(&bd2, NUM_TESTBLOCKS);

    REQUIRE(bd2.close() == 0);

    // Create on existing file
    BlockDevice bd3;
    REQUIRE(bd3.create(BD_PATH) == 0);

    bdWriteRead(&bd3, NUM_TESTBLOCKS);

    REQUIRE(bd3.close() == 0);

}

TEST_CASE( "BD_OPEN_NON-EXISTING_FILE", "[blockdevice]" ) {

    remove(BD_PATH);

    BlockDevice bd;
    REQUIRE(bd.open(BD_PATH) < 0);
}