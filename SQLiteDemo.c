#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
//#include <sqlite3.h>

void dealCMCCOSGIInfoTable(sqlite3 *db);
void dealCMCCBundleInfoTable(sqlite3 *db);
void dealCMCCDuPermissionTable(sqlite3 *db);
void dealCMCCApiRightTable(sqlite3 *db);
int showTableInfo(void *para,int n_column,char **column_value,char **column_name);
int showCount(void *para,int n_column,char **column_value,char **column_name);
int dealCMCCOSGIInfoData(void *para, int n_column, char **column_value, char **column_name);
int dealCMCCApiRightData(void *para, int n_column, char **column_value, char **column_name);


// CMCCOSGIInfo表结构体
typedef struct
{
    int     iEnable;
    char    szStatus[32];
    int     iReset;
    char    szName[32];
    char    szVendor[128];
    char    szVersion[32];
    char    szType[32];
    int     iAccDefult;
} T_CMCCOSGIInfo;

// CMCCApiRight表结构体
typedef struct
{
    char    szBundleName[256];
    char    szAPIName[256];
    int     iAPIRight;
} T_CMCCApiRightInfo;
T_CMCCApiRightInfo g_tCMCCApiRightInfo = {0};


int main ( int argc, char **argv ) 
{
    sqlite3 *db = NULL;
    int      rc = 0;

    // 打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
    rc = sqlite3_open ("IGD.db", &db);

    if (rc == SQLITE_OK)    // 打开成功
    {
        printf ("打开数据库成功！\n");
        
        dealCMCCOSGIInfoTable(db);        // CMCCOSGIInfo表
        dealCMCCBundleInfoTable(db);      // CMCCBundleInfo表
        dealCMCCDuPermissionTable(db);    // CMCCDuPermission表
        dealCMCCApiRightTable(db);        // CMCCApiRight表

        sqlite3_close(db);    // 关闭数据库 
    }
    else
    {
        printf ("打开数据库失败！\n");
    }

    return 0;
}


// 操作CMCCOSGIInfo表
void dealCMCCOSGIInfoTable(sqlite3 *db) 
{
    char    *errMsg         = NULL;
    int      rc             = 0;
    int      iDataNum       = 0;
    char     szContent[128] = {0};
    
    if (db == NULL)
    {
        printf("dealCMCCOSGIInfoTable:db is NULL!\n");
        return;
    }

    // 先删除表数据
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "delete from CMCCOSGIInfo where Type='2G'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // delete data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCOSGIInfoTable:CMCCOSGIInfo表删除数据失败!\n");
        return;
    }

    // 插入数据
    for (iDataNum=0; iDataNum<3; iDataNum++)
    {
        memset(szContent, 0x00, sizeof(szContent));
        snprintf(szContent, sizeof(szContent)-1, "insert into CMCCOSGIInfo values(1, 'OK', 0, 'osgi', 'zxic', '1.0.1', '%dG', 1)", iDataNum+1);

        rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // insert data
        if (rc != SQLITE_OK) 
        {
            printf("dealCMCCOSGIInfoTable:CMCCOSGIInfo表插入第%d条数据失败, errMsg=%s!\n", iDataNum+1, errMsg);
        }
    }

    // 非空字段不插入值
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "insert into CMCCOSGIInfo(Enable,Status,Reset,Name,Vendor,Version,Type) values(2, 'OK', 0, 'osgi', 'zxic', '1.0.1', '4G')");

    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // insert data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCOSGIInfoTable:CMCCOSGIInfo表插入单条数据失败, errMsg=%s!\n", errMsg);
    }
    // 更改数据字段值
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "update CMCCOSGIInfo set Version='1.0.2' where Type='3G'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // update data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCOSGIInfoTable:CMCCOSGIInfo表更改数据失败!\n");
        return;
    }

    // 查询数据详细信息
    rc = sqlite3_exec(db, "select * from CMCCOSGIInfo", dealCMCCOSGIInfoData, NULL, &errMsg);   // select data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCOSGIInfoTable:查询CMCCOSGIInfo表数据详细信息失败!\n");
        return;
    }

    // 查询数据条数
    rc = sqlite3_exec(db, "select count(*) from CMCCOSGIInfo", showCount, NULL, &errMsg);    // select count(*)
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCOSGIInfoTable:查询CMCCOSGIInfo表数据条数失败!\n");
    }
}


// 操作CMCCBundleInfo表
void dealCMCCBundleInfoTable(sqlite3 *db) 
{
    char    *errMsg         = NULL;
    int      rc             = 0;
    int      iDataNum       = 0;
    char     szContent[256] = {0};
    
    if (db == NULL)
    {
        printf("dealCMCCBundleInfoTable:db is NULL!\n");
        return;
    }

    // 先删除表数据
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "delete from CMCCBundleInfo where EUID='12303'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // delete data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCBundleInfoTable:CMCCBundleInfo表删除数据失败!\n");
        return;
    }

    // 插入数据
    for (iDataNum=0; iDataNum<3; iDataNum++)
    {
        memset(szContent, 0x00, sizeof(szContent));
        snprintf(szContent, sizeof(szContent)-1, "insert into CMCCBundleInfo values('test_api', '123%02d', 'CMIOT', 'active', 0, 'inactive', '100', 'fail', 1, 'ZXIC', '1.0.1', 'very good', '192.168.1.1', '1234', '4567', 0 , 1, 23, 2)", iDataNum+1);

        rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // insert data
        if (rc != SQLITE_OK) 
        {
            printf("dealCMCCBundleInfoTable:CMCCBundleInfo表插入第%d条数据失败, errMsg=%s!\n", iDataNum+1, errMsg);
        }
    }

    // 更改数据字段值
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "update CMCCBundleInfo set Version='1.0.2' where EUID='12302'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // update data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCBundleInfoTable:CMCCBundleInfo表更改数据失败!\n");
        return;
    }

    // 查询数据详细信息
    // rc = sqlite3_exec(db, "select EUID, Name from CMCCBundleInfo where EUID='12303'", showTableInfo, NULL, &errMsg);   // select data
    // rc = sqlite3_exec(db, "select * from CMCCBundleInfo where EUID='12303'", showTableInfo, NULL, &errMsg);   // select data
    rc = sqlite3_exec(db, "select * from CMCCBundleInfo", showTableInfo, NULL, &errMsg);   // select data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCBundleInfoTable:查询CMCCBundleInfo表数据详细信息失败!\n");
        return;
    }

    // 查询数据条数
    rc = sqlite3_exec(db, "select count(*) from CMCCBundleInfo", showCount, NULL, &errMsg);    // select count(*)
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCBundleInfoTable:查询CMCCBundleInfo表数据条数失败!\n");
    }
}


// 操作CMCCDuPermission表
void dealCMCCDuPermissionTable(sqlite3 *db) 
{
    char    *errMsg         = NULL;
    int      rc             = 0;
    int      iDataNum       = 0;
    char     szContent[128] = {0};
    
    if (db == NULL)
    {
        printf("dealCMCCDuPermissionTable:db is NULL!\n");
        return;
    }

    // 先删除表数据
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "delete from CMCCDuPermission where DUName='CMIOT01'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // delete data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCDuPermissionTable:CMCCDuPermission表删除数据失败!\n");
        return;
    }

    // 插入数据
    for (iDataNum=0; iDataNum<3; iDataNum++)
    {
        memset(szContent, 0x00, sizeof(szContent));
        snprintf(szContent, sizeof(szContent)-1, "insert into CMCCDuPermission(DUName) values('CMIOT%02d')", iDataNum+1);

        rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // insert data
        if (rc != SQLITE_OK) 
        {
            printf("dealCMCCDuPermissionTable:CMCCDuPermission表插入第%d条数据失败, errMsg=%s!\n", iDataNum+1, errMsg);
        }
    }

    // 更改数据字段值
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "update CMCCDuPermission set DUName='hello' where DUName='CMIOT02'");
    rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // update data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCDuPermissionTable:CMCCDuPermission表更改数据失败!\n");
        return;
    }

    // 查询数据详细信息
    rc = sqlite3_exec(db, "select * from CMCCDuPermission", showTableInfo, NULL, &errMsg);   // select data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCDuPermissionTable:查询CMCCDuPermission表数据详细信息失败!\n");
        return;
    }

    // 查询数据条数
    rc = sqlite3_exec(db, "select count(*) from CMCCDuPermission", showCount, NULL, &errMsg);    // select count(*)
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCDuPermissionTable:查询CMCCDuPermission表数据条数失败!\n");
    }
}


// 操作CMCCApiRight表
void dealCMCCApiRightTable(sqlite3 *db) 
{
    char    *errMsg         = NULL;
    int      rc             = 0;
    int      iDataNum       = 0;
    char     szContent[128] = {0};
    
    if (db == NULL)
    {
        printf("dealCMCCApiRightTable:db is NULL!\n");
        return;
    }

    // 先删除表数据
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "delete from CMCCApiRight where BundleName='CMIOT01'");
    rc = sqlite3_exec(db, szContent, NULL, NULL,&errMsg);  // delete data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:CMCCApiRight表删除数据失败!\n");
        return;
    }

    // 插入数据
    for (iDataNum=0; iDataNum<3; iDataNum++)
    {
        memset(szContent, 0x00, sizeof(szContent));
        snprintf(szContent, sizeof(szContent)-1, "insert into CMCCApiRight(BundleName,APIName) values('CMIOT%02d','bundle%02d')", iDataNum+1, iDataNum+1);

        rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // insert data
        if (rc != SQLITE_OK) 
        {
            printf("dealCMCCApiRightTable:CMCCApiRight表插入第%d条数据失败, errMsg=%s!\n", iDataNum+1, errMsg);
        }
    }

    // 继续插入数据
    // 唯一索引
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "insert into CMCCApiRight(BundleName,APIName) values('CMIOT03','bundle03')");

    rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // insert data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:CMCCApiRight表插入数据失败1, errMsg=%s!\n", errMsg);
    }
    // 非唯一索引
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "insert into CMCCApiRight(BundleName,APIName) values('CMIOT03','bundle04')");

    rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // insert data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:CMCCApiRight表插入数据失败2, errMsg=%s!\n", errMsg);
    }

    // 更改数据字段值
    memset(szContent, 0x00, sizeof(szContent));
    snprintf(szContent, sizeof(szContent)-1, "update CMCCApiRight set APIName='test_api' where BundleName='CMIOT02'");
    rc = sqlite3_exec(db, szContent, NULL, NULL, &errMsg);  // update data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:CMCCApiRight表更改数据失败, errMsg=%s!\n", errMsg);
        return;
    }

    // 查询单条数据信息
    rc = sqlite3_exec(db, "select APIName,APIRight from CMCCApiRight where BundleName='CMIOT01'", dealCMCCApiRightData, NULL, &errMsg);   // select data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:查询CMCCApiRight表单条数据信息失败!\n");
        return;
    }
    // 打印结构体变量值
    printf("dealCMCCApiRightTable: APIName=%s, APIRight=%d\n", g_tCMCCApiRightInfo.szAPIName, g_tCMCCApiRightInfo.iAPIRight);

    // 查询数据详细信息
    rc = sqlite3_exec(db, "select * from CMCCApiRight where 1=1", showTableInfo, NULL, &errMsg);   // select data
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:查询CMCCApiRight表数据详细信息失败!\n");
        return;
    }

    // 查询数据条数
    rc = sqlite3_exec(db, "select count(*) from CMCCApiRight", showCount, NULL, &errMsg);    // select count(*)
    if (rc != SQLITE_OK) 
    {
        printf("dealCMCCApiRightTable:查询CMCCApiRight表数据条数失败!\n");
    }
}

// 查询表数据详细信息
int showTableInfo(void *para, int n_column, char **column_value, char **column_name) 
{
    int i = 0;

    printf("记录包含%d个字段\n", n_column);
    for (i=0; i<n_column; i++) 
    {
        printf("字段名：%s  >> 字段值：%s\n", column_name[i], column_value[i]);
    }
    printf("--------------------------------------\n");
    return 0;
}


// 查询表数据条数
int showCount(void *para, int n_column, char **column_value, char **column_name) 
{
    // printf("一共%s条记录%s\n", column_value[0], column_name[0]);
    printf("一共%s条记录!\n", column_value[0]);
    return 0;
}


// CMCCOSGIInfo表数据处理
int dealCMCCOSGIInfoData(void *para, int n_column, char **column_value, char **column_name) 
{
    int i = 0;
    T_CMCCOSGIInfo tCMCCOSGIInfo = {0};

    printf("记录包含%d个字段\n", n_column);
    for (i=0; i<n_column; i++) 
    {
        printf("字段名：%s  >> 字段值：%s\n", column_name[i], column_value[i]);
    }
    printf("--------------------------------------\n");

    // 将获取到的每个字段值放到结构体中
    tCMCCOSGIInfo.iEnable = atoi(column_value[0]);
    memcpy(tCMCCOSGIInfo.szStatus, column_value[1], sizeof(tCMCCOSGIInfo.szStatus)-1);
    tCMCCOSGIInfo.iReset = atoi(column_value[2]);
    memcpy(tCMCCOSGIInfo.szName, column_value[3], sizeof(tCMCCOSGIInfo.szName)-1);
    memcpy(tCMCCOSGIInfo.szVendor, column_value[4], sizeof(tCMCCOSGIInfo.szVendor)-1);
    memcpy(tCMCCOSGIInfo.szVersion, column_value[5], sizeof(tCMCCOSGIInfo.szVersion)-1);
    memcpy(tCMCCOSGIInfo.szType, column_value[6], sizeof(tCMCCOSGIInfo.szType)-1);
    tCMCCOSGIInfo.iAccDefult = atoi(column_value[7]);

    // 打印结构体变量值
    printf("dealCMCCOSGIInfoData: iEnable=%d, szStatus=%s, iReset=%d, szName=%s, szVendor=%s, szVersion=%s, szType=%s, iAccDefult=%d\n", tCMCCOSGIInfo.iEnable, tCMCCOSGIInfo.szStatus, tCMCCOSGIInfo.iReset, tCMCCOSGIInfo.szName, tCMCCOSGIInfo.szVendor, tCMCCOSGIInfo.szVersion, tCMCCOSGIInfo.szType, tCMCCOSGIInfo.iAccDefult);
	
    return 0;
}

// CMCCApiRight表数据处理
int dealCMCCApiRightData(void *para, int n_column, char **column_value, char **column_name) 
{
    int i = 0;

    memset(&g_tCMCCApiRightInfo, 0x00, sizeof(g_tCMCCApiRightInfo));

    printf("记录包含%d个字段\n", n_column);
    for (i=0; i<n_column; i++) 
    {
        printf("字段名：%s  >> 字段值：%s\n", column_name[i], column_value[i]);
    }
    printf("--------------------------------------\n");

    // 将获取到的每个字段值放到结构体中
    memcpy(g_tCMCCApiRightInfo.szAPIName, column_value[0], sizeof(g_tCMCCApiRightInfo.szAPIName)-1);
    g_tCMCCApiRightInfo.iAPIRight = atoi(column_value[1]);
	
    return 0;
}

