#!/bin/bash
##############################
# @file create_db_sqlite.sh
# @brief create database and tables in sqlite
# @author zzx
# @version 0.1
# @date 2018-03-26
##############################
sqlite3 IGD.db << EOF 2>/dev/null
drop table CMCCOSGIInfo;
create table CMCCOSGIInfo 
(
    Enable    int,
    Status    varchar(32),
    Reset     int,
    Name      varchar(32),
    Vendor    varchar(128),
    Version   varchar(32),
    Type      varchar(32),
    AccDefult int  not null
);
create unique index idx_CMCCOSGIInfo on CMCCOSGIInfo(Type);
drop table CMCCBundleInfo;
create table CMCCBundleInfo 
(
    BundleName             varchar(256),
    EUID                   varchar(64),
    Name                   varchar(256),
    Status                 varchar(32),
    InstallFirst           int,
    JarStatus              varchar(32),
    ExecutionFaultCode     varchar(32),
    ExecutionFaultMessage  varchar(256),
    AutoStart              int,
    Vendor                 varchar(128),
    Version                varchar(32),
    Description            varchar(256),
    URL                    varchar(1024),
    UUID                   varchar(64),
    DUID                   varchar(64),
    Resolved               int,
    Visable                int,
    ID                     int,
    AppType                int
);
create unique index idx1_CMCCBundleInfo on CMCCBundleInfo(EUID);
create        index idx2_CMCCBundleInfo on CMCCBundleInfo(BundleName);
drop table CMCCDuPermission;
create table CMCCDuPermission 
(
    DUName  varchar(256)
);
create unique index idx_CMCCDuPermission on CMCCDuPermission(DUName);
drop table CMCCApiRight;
create table CMCCApiRight 
(
    BundleName  varchar(256),
    APIName     varchar(256),
    APIRight    int  default 1 not null
);
create unique index idx1_CMCCApiRight on CMCCApiRight(BundleName,APIName);
create        index idx2_CMCCApiRight on CMCCApiRight(APIRight);
.quit
EOF
