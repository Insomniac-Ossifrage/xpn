/*
 *  Copyright 2020-2023 Felix Garcia Carballeira, Diego Camarmas Alonso, Alejandro Calderon Mateos
 *
 *  This file is part of Expand.
 *
 *  Expand is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Expand is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Expand.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * @file tcp_server_ops.h
 * @brief Header file to 'TODO'.
 *
 * Header file to 'TODO'.
 *
 * @authors Felix Garcia Carballeira, Diego Camarmas Alonso, Alejandro Calderon Mateos
 * @date  Jul 22, 2021
 * @bug No known bugs.
 */


#ifndef _TCP_SERVER_OPS_H_
#define _TCP_SERVER_OPS_H_

/************************************************
 *  ... Includes
 ***********************************************/
#include <libgen.h>
#include "all_system.h"
#include "base/filesystem.h"
#include "base/urlstr.h"
#include "base/utils.h"
#include "base/workers.h"
#include "tcp_server_ops.h"
#include "tcp_server_comm.h"
#include "tcp_server_d2xpn.h"
#include "tcp_server_params.h"

/************************************************
 *  ... Constants
 ***********************************************/
#ifndef TCP_SERVER_ID
#define TCP_SERVER_ID 32
#endif

/************************************************
 *  ... Operations
 ***********************************************/

/************************************************
 *  ... Operations: File operations
 ***********************************************/
#define TCP_SERVER_OPEN_FILE_WS 0
#define TCP_SERVER_CREAT_FILE_WS 1
#define TCP_SERVER_READ_FILE_WS 2
#define TCP_SERVER_WRITE_FILE_WS 3
#define TCP_SERVER_CLOSE_FILE_WS 4
#define TCP_SERVER_RM_FILE 5
#define TCP_SERVER_RM_FILE_ASYNC 6
#define TCP_SERVER_RENAME_FILE 7
#define TCP_SERVER_GETATTR_FILE 8
#define TCP_SERVER_SETATTR_FILE 9

/************************************************
 *  ... Operations: File operations without session
 ***********************************************/
#define TCP_SERVER_OPEN_FILE_WOS 100
#define TCP_SERVER_CREAT_FILE_WOS 101
#define TCP_SERVER_READ_FILE_WOS 102
#define TCP_SERVER_WRITE_FILE_WOS 103

/************************************************
 *  ... Operations: Directory operations
 ***********************************************/
#define TCP_SERVER_MKDIR_DIR 20
#define TCP_SERVER_RMDIR_DIR 21
#define TCP_SERVER_RMDIR_DIR_ASYNC 22
#define TCP_SERVER_OPENDIR_DIR 23
#define TCP_SERVER_READDIR_DIR 24
#define TCP_SERVER_CLOSEDIR_DIR 25

/************************************************
 *  ... Operations: Import / Export operations
 ***********************************************/
#define TCP_SERVER_FLUSH_FILE 40
#define TCP_SERVER_PRELOAD_FILE 41

/************************************************
 *  ... Operations: FS Operations
 ***********************************************/
#define TCP_SERVER_STATFS_DIR 60
#define TCP_SERVER_GETNODENAME 61
#define TCP_SERVER_GETID 62

/************************************************
 *  ... Operations: Connection operatons
 ***********************************************/
#define TCP_SERVER_FINALIZE 80
#define TCP_SERVER_DISCONNECT 81
#define TCP_SERVER_END -1

/************************************************
 *  ... Message struct
 ***********************************************/

/** @struct st_tcp_server_open
 *  This is a struct
 *
 *  @var st_tcp_server_open::path
 *    A 'TODO'.
 */
struct st_tcp_server_open
{
  char path[PATH_MAX]; // TO-DO: Insert FLAGS - O_RDWR etc
};

/** @struct st_tcp_server_open_req
 *  This is a struct
 *
 *  @var st_tcp_server_open_req::fd
 *    A 'TODO'.
 */
struct st_tcp_server_open_req
{
  int fd;
};

/** @struct st_tcp_server_creat
 *  This is a struct
 *
 *  @var st_tcp_server_creat::path
 *    A 'TODO'.
 */
struct st_tcp_server_creat
{
  char path[PATH_MAX];
};

/** @struct st_tcp_server_read
 *  This is a struct
 *
 *  @var st_tcp_server_read::fd
 *    A 'TODO'.
 *  @var st_tcp_server_read::path
 *    A 'TODO'.
 *  @var st_tcp_server_read::offset
 *    A 'TODO'.
 *  @var st_tcp_server_read::size
 *    A 'TODO'.
 */
struct st_tcp_server_read
{
  int fd;
  char path[PATH_MAX];
  offset_t offset;
  size_t size;
};

/** @struct st_tcp_server_read_req
 *  This is a struct
 *
 *  @var st_tcp_server_read_req::size
 *    A 'TODO'.
 *  @var st_tcp_server_read_req::last
 *    A 'TODO'.
 */
struct st_tcp_server_read_req
{
  ssize_t size;
  char last;
};

/** @struct st_tcp_server_write
 *  This is a struct
 *
 *  @var st_tcp_server_write::fd
 *    A 'TODO'.
 *  @var st_tcp_server_write::path
 *    A 'TODO'.
 *  @var st_tcp_server_write::offset
 *    A 'TODO'.
 *  @var st_tcp_server_write::size
 *    A 'TODO'.
 */
struct st_tcp_server_write
{
  int fd;
  char path[PATH_MAX];
  offset_t offset;
  size_t size;
};

/** @struct st_tcp_server_write_req
 *  This is a struct
 *
 *  @var st_tcp_server_write_req::size
 *    A 'TODO'.
 */
struct st_tcp_server_write_req
{
  ssize_t size;
};

/** @struct st_tcp_server_close
 *  This is a struct
 *
 *  @var st_tcp_server_close::fd
 *    A 'TODO'.
 *  @var st_tcp_server_close::path
 *    A 'TODO'.
 */
struct st_tcp_server_close
{
  int fd;
  char path[PATH_MAX];
};

/** @struct st_tcp_server_rename
 *  This is a struct
 *
 *  @var st_tcp_server_rename::old_url
 *    A 'TODO'.
 *  @var st_tcp_server_rename::new_url
 *    A 'TODO'.
 */
struct st_tcp_server_rename
{
  char old_url[PATH_MAX];
  char new_url[PATH_MAX];
};

/** @struct st_tcp_server_rm
 *  This is a struct
 *
 *  @var st_tcp_server_rm::path
 *    A 'TODO'.
 */
struct st_tcp_server_rm
{
  char path[PATH_MAX];
};

/** @struct st_tcp_server_getattr
 *  This is a struct
 *
 *  @var st_tcp_server_getattr::path
 *    A 'TODO'.
 */
struct st_tcp_server_getattr
{
  char path[PATH_MAX];
};

/** @struct st_tcp_server_setattr
 *  This is a struct
 *
 *  @var st_tcp_server_setattr::path
 *    A 'TODO'.
 *  @var st_tcp_server_setattr::attr
 *    A 'TODO'.
 */
struct st_tcp_server_setattr
{
  char path[PATH_MAX];
  struct stat attr;
};

/** @struct st_tcp_server_attr_req
 *  This is a struct
 *
 *  @var st_tcp_server_attr_req::status
 *    A 'TODO'.
 *  @var st_tcp_server_attr_req::attr
 *    A 'TODO'.
 */
struct st_tcp_server_attr_req
{
  char status;
  struct stat attr;
};

/** @struct st_tcp_server_mkdir
 *  This is a struct
 *
 *  @var st_tcp_server_mkdir::path
 *    A 'TODO'.
 */
struct st_tcp_server_mkdir
{
  char path[PATH_MAX];
};

/** @struct st_tcp_server_opendir
 *  This is a struct
 *
 *  @var st_tcp_server_opendir::path
 *    A 'TODO'.
 */
struct st_tcp_server_opendir
{ // NEW
  char path[PATH_MAX];
};

/** @struct st_tcp_server_readdir
 *  This is a struct
 *
 *  @var st_tcp_server_readdir::dir
 *    A 'TODO'.
 */
struct st_tcp_server_readdir
{ // NEW
  DIR *dir;
};

/** @struct st_tcp_server_direntry
 *  This is a struct
 *
 *  @var st_tcp_server_direntry::end
 *    A 'TODO'.
 *  @var st_tcp_server_direntry::ret
 *    A 'TODO'.
 */
struct st_tcp_server_direntry
{          // NEW
  int end; // If end = 1 exist entry; 0 not exist
  struct dirent ret;
};

/** @struct st_tcp_server_closedir
 *  This is a struct
 *
 *  @var st_tcp_server_closedir::dir
 *    A 'TODO'.
 */
struct st_tcp_server_closedir
{ // NEW
  DIR *dir;
};

/** @struct st_tcp_server_rmdir
 *  This is a struct
 *
 *  @var st_tcp_server_rmdir::path
 *    A 'TODO'.
 */
struct st_tcp_server_rmdir
{
  char path[PATH_MAX];
};

// TODO: define TCP_SERVER_OPENDIR_DIR, TCP_SERVER_READDIR_DIR, TCP_SERVER_CLOSEDIR_DIR

/** @struct st_tcp_server_flush
 *  This is a struct
 *
 *  @var st_tcp_server_flush::storage_path
 *    A 'TODO'.
 *  @var st_tcp_server_flush::virtual_path
 *    A 'TODO'.
 *  @var st_tcp_server_flush::block_size
 *    A 'TODO'.
 *  @var st_tcp_server_flush::opt
 *    A 'TODO'.
 */
struct st_tcp_server_flush
{
  char storage_path[PATH_MAX];
  char virtual_path[PATH_MAX];
  int block_size;
  char opt;
};

/** @struct st_tcp_server_preload
 *  This is a struct
 *
 *  @var st_tcp_server_preload::storage_path
 *    A 'TODO'.
 *  @var st_tcp_server_preload::virtual_path
 *    A 'TODO'.
 *  @var st_tcp_server_preload::block_size
 *    A 'TODO'.
 *  @var st_tcp_server_preload::opt
 *    A 'TODO'.
 */
struct st_tcp_server_preload
{
  char storage_path[PATH_MAX];
  char virtual_path[PATH_MAX];
  int block_size;
  char opt;
};

/** @struct st_tcp_server_end
 *  This is a struct
 *
 *  @var st_tcp_server_end::status
 *    A 'TODO'.
 */
struct st_tcp_server_end
{
  char status;
};

/** @struct st_tcp_server_msg
 *  This is a struct
 *
 *  @var st_tcp_server_msg::type
 *    A 'TODO'.
 *  @var st_tcp_server_msg::id
 *    A 'TODO'.
 */
struct st_tcp_server_msg
{
  int type;
  char id[TCP_SERVER_ID];
  union
  {
    struct st_tcp_server_open op_open;
    struct st_tcp_server_creat op_creat;
    struct st_tcp_server_close op_close;
    struct st_tcp_server_read op_read;
    struct st_tcp_server_write op_write;
    struct st_tcp_server_rm op_rm;
    struct st_tcp_server_rename op_rename;
    struct st_tcp_server_mkdir op_mkdir;
    struct st_tcp_server_opendir op_opendir;
    struct st_tcp_server_readdir op_readdir;
    struct st_tcp_server_closedir op_closedir;
    struct st_tcp_server_rmdir op_rmdir;
    struct st_tcp_server_getattr op_getattr;
    struct st_tcp_server_setattr op_setattr;

    struct st_tcp_server_flush op_flush;
    struct st_tcp_server_preload op_preload;
    struct st_tcp_server_end op_end;
  } u_st_tcp_server_msg;
};

/************************************************
 *  ... Functions
 ***********************************************/

/**
 * @brief 'TODO'.
 *
 * 'TODO'
 *
 * @param op_code 'TODO'.
 * @return 'TODO'.
 */
char *tcp_server_op2string(int op_code);

/**
 * @brief 'TODO'.
 *
 * 'TODO'
 *
 * @param th 'TODO'.
 * @param the_end 'TODO'.
 * @return 'TODO'.
 */
int tcp_server_do_operation(struct st_th *th, int *the_end);

#endif
