//
//  myfs.h
//  myfs
//
//  Created by Oliver Waldhorst on 02.08.17.
//  Copyright © 2017-2020 Oliver Waldhorst. All rights reserved.
//

#ifndef myfs_h
#define myfs_h

#include <fuse.h>
#include <cmath>

#include "blockdevice.h"
#include "myfs-structs.h"

class MyFS {
protected:
    static MyFS *_instance;
    FILE *logFile;

    BlockDevice *blockDevice;
    
public:
    static MyFS *Instance();
    
    // TODO: [PART 2] You may add attributes of your file system here
    
    MyFS();
    ~MyFS();
    
    // --- Methods called by FUSE ---
    // For Documentation see https://libfuse.github.io/doxygen/structfuse__operations.html
    virtual int fuseGetattr(const char *path, struct stat *statbuf);
    virtual int fuseReadlink(const char *path, char *link, size_t size);
    virtual int fuseMknod(const char *path, mode_t mode, dev_t dev);
    virtual int fuseMkdir(const char *path, mode_t mode);
    virtual int fuseUnlink(const char *path);
    virtual int fuseRmdir(const char *path);
    virtual int fuseSymlink(const char *path, const char *link);
    virtual int fuseRename(const char *path, const char *newpath);
    virtual int fuseLink(const char *path, const char *newpath);
    virtual int fuseChmod(const char *path, mode_t mode);
    virtual int fuseChown(const char *path, uid_t uid, gid_t gid);
    virtual int fuseTruncate(const char *path, off_t newSize);
    virtual int fuseUtime(const char *path, struct utimbuf *ubuf);
    virtual int fuseOpen(const char *path, struct fuse_file_info *fileInfo);
    virtual int fuseRead(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo);
    virtual int fuseWrite(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo);
    virtual int fuseStatfs(const char *path, struct statvfs *statInfo);
    virtual int fuseFlush(const char *path, struct fuse_file_info *fileInfo);
    virtual int fuseRelease(const char *path, struct fuse_file_info *fileInfo);
    virtual int fuseFsync(const char *path, int datasync, struct fuse_file_info *fi);
#ifdef __APPLE__
    virtual int fuseSetxattr(const char *path, const char *name, const char *value, size_t size, int flags, uint32_t x);
    virtual int fuseGetxattr(const char *path, const char *name, char *value, size_t size, uint x);
#else
    virtual int fuseSetxattr(const char *path, const char *name, const char *value, size_t size, int flags);
    virtual int fuseGetxattr(const char *path, const char *name, char *value, size_t size);
#endif
    virtual void* fuseInit(struct fuse_conn_info *conn);
    virtual int fuseListxattr(const char *path, char *list, size_t size);
    virtual int fuseRemovexattr(const char *path, const char *name);
    virtual int fuseOpendir(const char *path, struct fuse_file_info *fileInfo);
    virtual int fuseReaddir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo);
    virtual int fuseReleasedir(const char *path, struct fuse_file_info *fileInfo);
    virtual int fuseFsyncdir(const char *path, int datasync, struct fuse_file_info *fileInfo);
    virtual int fuseTruncate(const char *path, off_t offset, struct fuse_file_info *fileInfo);
    virtual int fuseCreate(const char *, mode_t, struct fuse_file_info *);
    virtual void fuseDestroy();
    
    // TODO: [PART 2] You may add methods of your file system here
    
};

#endif /* myfs_h */
