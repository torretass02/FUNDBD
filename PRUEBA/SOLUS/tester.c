

#include "tester.h"

void checkReplaceExtensionByIdx(const char * tableName, const char * indexName);
void checkCreateIndex(const char * indexName);
void checkCreateTable(const char * tableName);
void checkPrint(const char * indexName);

void createTestIndexFile(const char * indexName);

void checkFindKey(const char * indexName);
void checkAddIndexEntry(const char * indexName);
void checkAddTableEntry(const char * tableName,const char * indexName);


int main() {

    const char *tableName = "myDataBase.dat";
    const char *indexName = "myDataBase.idx";

    /* remove file if exists */
    remove(tableName);
    remove(indexName);

    /*primera parte*/
    checkReplaceExtensionByIdx(tableName, indexName);
    checkCreateTable(tableName);
    checkCreateIndex(indexName);
    checkPrint(indexName);

    /*segunda parte*/
    checkFindKey(indexName);
    checkAddIndexEntry(indexName);
    checkAddTableEntry(tableName,indexName);

#ifdef NEVERDEFINED
#endif
    return (0);
}
