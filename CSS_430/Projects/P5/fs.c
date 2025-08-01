// ============================================================================
// fs.c - user FileSytem API
// ============================================================================

#include "bfs.h"
#include "fs.h"

// ============================================================================
// Close the file currently open on file descriptor 'fd'.
// ============================================================================
i32 fsClose(i32 fd) { 
  i32 inum = bfsFdToInum(fd);
  bfsDerefOFT(inum);
  return 0; 
}



// ============================================================================
// Create the file called 'fname'.  Overwrite, if it already exsists.
// On success, return its file descriptor.  On failure, EFNF
// ============================================================================
i32 fsCreate(str fname) {
  i32 inum = bfsCreateFile(fname);
  if (inum == EFNF) return EFNF;
  return bfsInumToFd(inum);
}



// ============================================================================
// Format the BFS disk by initializing the SuperBlock, Inodes, Directory and 
// Freelist.  On succes, return 0.  On failure, abort
// ============================================================================
i32 fsFormat() {
  FILE* fp = fopen(BFSDISK, "w+b");
  if (fp == NULL) FATAL(EDISKCREATE);

  i32 ret = bfsInitSuper(fp);               // initialize Super block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitInodes(fp);                  // initialize Inodes block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitDir(fp);                     // initialize Dir block
  if (ret != 0) { fclose(fp); FATAL(ret); }

  ret = bfsInitFreeList();                  // initialize Freelist
  if (ret != 0) { fclose(fp); FATAL(ret); }

  fclose(fp);
  return 0;
}


// ============================================================================
// Mount the BFS disk.  It must already exist
// ============================================================================
i32 fsMount() {
  FILE* fp = fopen(BFSDISK, "rb");
  if (fp == NULL) FATAL(ENODISK);           // BFSDISK not found
  fclose(fp);
  return 0;
}



// ============================================================================
// Open the existing file called 'fname'.  On success, return its file 
// descriptor.  On failure, return EFNF
// ============================================================================
i32 fsOpen(str fname) {
  i32 inum = bfsLookupFile(fname);        // lookup 'fname' in Directory
  if (inum == EFNF) return EFNF;
  return bfsInumToFd(inum);
}



// ============================================================================
// Read 'numb' bytes of data from the cursor in the file currently fsOpen'd on
// File Descriptor 'fd' into 'buf'.  On success, return actual number of bytes
// read (may be less than 'numb' if we hit EOF).  On failure, abort
// ============================================================================
i32 fsRead(i32 fd, i32 numb, void* buf) {
  if (fd < 0 || fd >= BLOCKSPERDISK || g_oft[fd].inum == -1)
  {
    FATAL(EBADCURS);
  } 
  u8* ret = (u8*)buf;
  i32 fileSize = fsSize(fd);
  i32 cursor = fsTell(fd);
  i32 byteToRead;
  
  //clamp bites to read to be within file size
  if (cursor + numb > fileSize){
    byteToRead = fileSize - cursor;
  } else{
    byteToRead = numb;
  }

  i32 index = 0;
  i32 inum = bfsFdToInum(fd);

  while (index < byteToRead){
    i32 offset = cursor + index;
    i32 fileBlockNo = offset / BYTESPERBLOCK;
    i32 blockOffset = offset % BYTESPERBLOCK;

    // FBN to DBN
    i32 diskBlockNo = bfsFbnToDbn(inum, fileBlockNo);
    if (diskBlockNo == ENODBN) {
      break; // Hit unallocated block / EOF
    }
    
    u8 block[512];
    bioRead(diskBlockNo, block);

    i32 bytesInThisBlock = 512 - blockOffset;
    if (bytesInThisBlock > (byteToRead - index)) {
      bytesInThisBlock = byteToRead - index;
    }

    memcpy(ret + index, block + blockOffset, bytesInThisBlock);
    index += bytesInThisBlock;
  }

  i32 newCursor = cursor + index;
  bfsSetCursor(inum, newCursor);
  return index;
}


// ============================================================================
// Move the cursor for the file currently open on File Descriptor 'fd' to the
// byte-offset 'offset'.  'whence' can be any of:
//
//  SEEK_SET : set cursor to 'offset'
//  SEEK_CUR : add 'offset' to the current cursor
//  SEEK_END : add 'offset' to the size of the file
//
// On success, return 0.  On failure, abort
// ============================================================================
i32 fsSeek(i32 fd, i32 offset, i32 whence) {

  if (offset < 0) FATAL(EBADCURS);
 
  i32 inum = bfsFdToInum(fd);
  i32 ofte = bfsFindOFTE(inum);
  
  switch(whence) {
    case SEEK_SET:
      g_oft[ofte].curs = offset;
      break;
    case SEEK_CUR:
      g_oft[ofte].curs += offset;
      break;
    case SEEK_END: {
        i32 end = fsSize(fd);
        g_oft[ofte].curs = end + offset;
        break;
      }
    default:
        FATAL(EBADWHENCE);
  }
  return 0;
}



// ============================================================================
// Return the cursor position for the file open on File Descriptor 'fd'
// ============================================================================
i32 fsTell(i32 fd) {
  return bfsTell(fd);
}



// ============================================================================
// Retrieve the current file size in bytes.  This depends on the highest offset
// written to the file, or the highest offset set with the fsSeek function.  On
// success, return the file size.  On failure, abort
// ============================================================================
i32 fsSize(i32 fd) {
  i32 inum = bfsFdToInum(fd);
  return bfsGetSize(inum);
}



// ============================================================================
// Write 'numb' bytes of data from 'buf' into the file currently fsOpen'd on
// filedescriptor 'fd'.  The write starts at the current file offset for the
// destination file.  On success, return 0.  On failure, abort
// ============================================================================
i32 fsWrite(i32 fd, i32 numb, void* buf) {

  if (fd < 0 || fd >= BLOCKSPERDISK || g_oft[fd].inum == -1)
  {
    FATAL(EBADCURS);
  } 

  if (numb <= 0){ //if no space in numb
    return 0;
  }

  ///OpenFile* file = &g_oft[fd];
  u8* ret = (u8*)buf;
  i32 inum = bfsFdToInum(fd);
  i32 cursor = fsTell(fd);

  i32 index = 0;

  while (index < numb) {
    i32 offset = cursor + index;
    i32 fileBlockNo = offset / BYTESPERBLOCK;
    i32 blockOffset = offset % BYTESPERBLOCK;

    // FBN to DBN
    i32 diskBlockNo = bfsFbnToDbn(inum, fileBlockNo);
    if (diskBlockNo == ENODBN) {
      bfsExtend(inum, fileBlockNo);
      diskBlockNo = bfsFbnToDbn(inum, fileBlockNo);
    }

    // Read existing block
    u8 block[512];
    bioRead(diskBlockNo, block);

    // Compute how much to write in this block
    i32 bytesLeft = numb - index;
    i32 chunk = 512 - blockOffset;
    if (chunk > bytesLeft) {
        chunk = bytesLeft;
    }

    // Copy data into block and write back
    memcpy(block + blockOffset, ret + index, chunk);
    bioWrite(diskBlockNo, block);

    index += chunk;
  }

  i32 newCursor = cursor + index;
  bfsSetCursor(inum, newCursor);

  //update file size
  Inode inode;
  bfsReadInode(inum, &inode);
  if (newCursor > inode.size) {
      inode.size = newCursor;
      bfsWriteInode(inum, &inode);
  }


  return 0;
}
