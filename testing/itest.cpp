//
// Created by Oliver Waldhorst on 20.03.20.
// Copyright © 2017-2020 Oliver Waldhorst. All rights reserved.
//

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#include "catch.hpp"
#include "tools.hpp"

#define FILENAME "file"
#define SMALL_SIZE 1024
#define LARGE_SIZE 20*1024*1024

TEST_CASE("T-1.01", "[Part_1]") {
    printf("Testcase 1.1: Create & remove a single file\n");

    int fd;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    // Open file (must fail)
    REQUIRE(open(FILENAME, O_EXCL | O_RDWR, 0666) < 0);
}

TEST_CASE("T-1.02", "[Part_1]") {
    printf("Testcase 1.2: Write and read a file\n");

    int fd;

    // remove file (just to be sure)
    unlink(FILENAME);

    // set up read & write buffer
    char* r= new char[SMALL_SIZE];
    memset(r, 0, SMALL_SIZE);
    char* w= new char[SMALL_SIZE];
    memset(w, 0, SMALL_SIZE);
    gen_random(w, SMALL_SIZE);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, w, SMALL_SIZE) == SMALL_SIZE);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, r, SMALL_SIZE) == SMALL_SIZE);
    REQUIRE(memcmp(r, w, SMALL_SIZE) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);
}

TEST_CASE("T-1.03", "[Part_1]") {
    printf("Testcase 1.3: Overwrite a part of a file\n");

    const char *buf1= "abcde";
    const char *buf2= "xyz";
    const char *buf3= "axyze";
    char *buf4= new char[strlen(buf3)];

    int fd;
    ssize_t b;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, buf1, strlen(buf1)) == strlen(buf1));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Write to the file at position 1
    REQUIRE(lseek(fd, 1, SEEK_SET) == 1);
    REQUIRE(write(fd, buf2, strlen(buf2)) == strlen(buf2));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, buf4, strlen(buf3)) == strlen(buf3));
    REQUIRE(memcmp(buf3, buf4, strlen(buf3)) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    delete [] buf4;
}

TEST_CASE("T-1.06", "[Part_1]") {
    printf("Testcase 1.6: Append before the end of a file\n");
    const char *buf1= "abcde";
    const char *buf2= "xyz";
    const char *buf3= "abcxyz";
    char *buf4= new char[strlen(buf3)];

    int fd;
    ssize_t b;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, buf1, strlen(buf1)) == strlen(buf1));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Write to the file at position 3
    REQUIRE(lseek(fd, 3, SEEK_SET) == 3);
    REQUIRE(write(fd, buf2, strlen(buf2)) == strlen(buf2));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, buf4, strlen(buf3)) == strlen(buf3));
    REQUIRE(memcmp(buf3, buf4, strlen(buf3)) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    delete [] buf4;
}

TEST_CASE("T-1.04", "[Part_1]") {
    printf("Testcase 1.4: Append at the end of a file\n");

    const char *buf1= "abcde";
    const char *buf2= "xyz";
    const char *buf3= "abcdexyz";
    char *buf4= new char[strlen(buf3)];

    int fd;
    ssize_t b;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, buf1, strlen(buf1)) == strlen(buf1));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Write to the file at position 5
    REQUIRE(lseek(fd, 5, SEEK_SET) == 5);
    REQUIRE(write(fd, buf2, strlen(buf2)) == strlen(buf2));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, buf4, strlen(buf3)) == strlen(buf3));
    REQUIRE(memcmp(buf3, buf4, strlen(buf3)) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    delete [] buf4;
}

TEST_CASE("T-1.05", "[Part_1]") {
    printf("Testcase 1.5: Append beyond the end of a file\n");
    const char *buf1= "abcde";
    const char *buf2= "xyz";
    char *buf4= new char[strlen(buf1)];

    int fd;
    ssize_t b;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, buf1, strlen(buf1)) == strlen(buf1));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Write to the file at position 7
    REQUIRE(lseek(fd, 7, SEEK_SET) == 7);
    REQUIRE(write(fd, buf2, strlen(buf2)) == strlen(buf2));

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, buf4, strlen(buf1)) == strlen(buf1));
    REQUIRE(memcmp(buf1, buf4, strlen(buf1)) == 0);
    REQUIRE(lseek(fd, 7, SEEK_SET) == 7);
    REQUIRE(read(fd, buf4, strlen(buf2)) == strlen(buf2));
    REQUIRE(memcmp(buf2, buf4, strlen(buf2)) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    delete [] buf4;
}

TEST_CASE("T-1.07", "[Part_1]") {
    printf("Testcase 1.7: Truncate a file\n");

    int fd;

    // remove file (just to be sure)
    unlink(FILENAME);

    // set up read & write buffer
    char* r= new char[SMALL_SIZE];
    memset(r, 0, SMALL_SIZE);
    char* w= new char[SMALL_SIZE];
    memset(w, 0, SMALL_SIZE);
    gen_random(w, SMALL_SIZE);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, w, SMALL_SIZE) == SMALL_SIZE);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Truncate open file
    REQUIRE(ftruncate(fd, SMALL_SIZE/2) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Check file size
    struct stat s;
    REQUIRE(stat(FILENAME, &s) == 0);
    REQUIRE(s.st_size == SMALL_SIZE/2);

    // Truncate closed file
    REQUIRE(truncate(FILENAME, SMALL_SIZE/4) == 0);

    // Check file size
    REQUIRE(stat(FILENAME, &s) == 0);
    REQUIRE(s.st_size == SMALL_SIZE/4);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);

    delete [] r;
    delete [] w;
}

TEST_CASE("T-1.08", "[Part_1]") {
    printf("Testcase 1.8: Change mode of a file\n");

    int fd;

    // remove file (just to be sure)
    unlink(FILENAME);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Get file attributes
    struct stat s;
    REQUIRE(stat(FILENAME, &s) == 0);

    // Change mode
    REQUIRE(chmod(FILENAME, s.st_mode | S_IRWXG | S_IRWXO ) == 0);

    struct stat s2;
    REQUIRE(stat(FILENAME, &s2) == 0);
    REQUIRE(s2.st_mode == (s.st_mode | S_IRWXG | S_IRWXO));

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);
}

TEST_CASE("T-1.09", "[Part_1]") {
    printf("Testcase 1.9: Write to multiple files\n");

    int fileSize= SMALL_SIZE;
    int writeSize= 16;
    const char *filename = "file";
    int noFiles= 64;

    off_t bufferSize= (fileSize/writeSize)*writeSize;

    char* w= new char[bufferSize];
    memset(w, 0, bufferSize);
    gen_random(w, (int) bufferSize);

    char* r= new char[bufferSize];
    memset(r, 0, bufferSize);

    int ret;
    size_t b;

    int fd[noFiles];

    // open all files
    for(int f= 0; f < noFiles; f++) {
        char nFilename[strlen(filename)+10];
        sprintf(nFilename, "%s_%d", filename, f);
        unlink(nFilename);
        fd[f]= open(nFilename, O_EXCL | O_RDWR | O_CREAT, 0666);
        REQUIRE(fd[f] >= 0);
    }

    // write incrementally to all files
    for(off_t offset= 0; offset < bufferSize; offset+= writeSize) {
        off_t toWrite= offset + writeSize < bufferSize ? writeSize : bufferSize - offset;

        for(int f= 0; f < noFiles; f++) {
            b= lseek(fd[f], offset, SEEK_SET);
            REQUIRE(b == offset);

            b= write(fd[f], w+offset, toWrite);
            REQUIRE(b == toWrite);
        }
    }

    // close all files
    for(int f= 0; f < noFiles; f++) {
        ret= close(fd[f]);
        REQUIRE(ret >= 0);
    }

    // check all files
    for(int f= 0; f < noFiles; f++) {
        char nFilename[strlen(filename)+10];
        sprintf(nFilename, "%s_%d", filename, f);

        int fd= open(nFilename, O_RDONLY);
        REQUIRE(fd >= 0);

        b= read(fd, r, bufferSize);
        REQUIRE(b == bufferSize);
        REQUIRE(memcmp(r, w, bufferSize) == 0);

        ret= close(fd);
        REQUIRE(ret >= 0);

        ret= unlink(nFilename);
        REQUIRE(ret >= 0);
    }

    delete [] r;
    delete [] w;
}

TEST_CASE("T-1.10", "[Part_1]") {
    printf("Testcase 1.10: Write a very large file\n");
    int fd;

    // remove file (just to be sure)
    unlink(FILENAME);

    // set up read & write buffer
    char* r= new char[LARGE_SIZE];
    memset(r, 0, LARGE_SIZE);
    char* w= new char[LARGE_SIZE];
    memset(w, 0, LARGE_SIZE);
    gen_random(w, LARGE_SIZE);

    // Create file
    fd = open(FILENAME, O_EXCL | O_RDWR | O_CREAT, 0666);
    REQUIRE(fd >= 0);

    // Write to the file
    REQUIRE(write(fd, w, LARGE_SIZE) == LARGE_SIZE);

    // Close file
    REQUIRE(close(fd) >= 0);

    // Open file again
    fd = open(FILENAME, O_EXCL | O_RDWR, 0666);
    REQUIRE(fd >= 0);

    // Read from the file
    REQUIRE(read(fd, r, LARGE_SIZE) == LARGE_SIZE);
    REQUIRE(memcmp(r, w, LARGE_SIZE) == 0);

    // Close file
    REQUIRE(close(fd) >= 0);

    // remove file
    REQUIRE(unlink(FILENAME) >= 0);
}