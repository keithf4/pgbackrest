/***********************************************************************************************************************************
Test Ini
***********************************************************************************************************************************/
#include "storage/driver/posix/storage.h"

/***********************************************************************************************************************************
Test Run
***********************************************************************************************************************************/
void
testRun(void)
{
    FUNCTION_HARNESS_VOID();

    Storage *storageTest = storageDriverPosixNew(
        strNew(testPath()), STORAGE_MODE_FILE_DEFAULT, STORAGE_MODE_PATH_DEFAULT, true, NULL);

    // *****************************************************************************************************************************
    if (testBegin("iniNew() and iniFree()"))
    {
        Ini *ini = NULL;

        TEST_ASSIGN(ini, iniNew(), "new ini");
        TEST_RESULT_PTR_NE(ini->memContext, NULL, "mem context is set");
        TEST_RESULT_PTR_NE(ini->store, NULL, "store is set");
        TEST_RESULT_VOID(iniFree(ini), "free ini");
        TEST_RESULT_VOID(iniFree(NULL), "free null ini");
    }

    // *****************************************************************************************************************************
    if (testBegin("iniSet(), iniGet(), iniGetDefault(), iniSectionList(), and iniSectionKeyList()"))
    {
        Ini *ini = NULL;

        MEM_CONTEXT_TEMP_BEGIN()
        {
            TEST_ASSIGN(ini, iniNew(), "new ini");

            TEST_RESULT_VOID(iniSet(ini, strNew("section1"), strNew("key1"), strNew("11")), "set section, key");
            TEST_RESULT_VOID(iniSet(ini, strNew("section1"), strNew("key2"), strNew("1.234")), "set section, key");

            TEST_RESULT_VOID(iniMove(ini, MEM_CONTEXT_OLD()), "move ini");
            TEST_RESULT_VOID(iniMove(NULL, MEM_CONTEXT_OLD()), "move null ini");
        }
        MEM_CONTEXT_TEMP_END();

        TEST_RESULT_STR(strPtr(iniGet(ini, strNew("section1"), strNew("key1"))), "11", "get section, key");
        TEST_RESULT_STR(strPtr(iniGet(ini, strNew("section1"), strNew("key2"))), "1.234", "get section, key");

        TEST_ERROR(iniGet(ini, strNew("section2"), strNew("key2")), FormatError, "section 'section2', key 'key2' does not exist");

        TEST_RESULT_STR(strPtr(iniGetDefault(ini, strNew("section1"), strNew("key1"), NULL)), "11", "get section, key, int");
        TEST_RESULT_PTR(iniGetDefault(ini, strNew("section2"), strNew("key2"), NULL), NULL, "get section, key, NULL");
        TEST_RESULT_STR(
                strPtr(iniGetDefault(ini, strNew("section3"), strNew("key3"), strNew("true"))), "true", "get section, key, bool");

        TEST_RESULT_INT(strLstSize(iniSectionKeyList(ini, strNew("bogus"))), 0, "get keys for missing section");
        TEST_RESULT_STR(strPtr(strLstJoin(iniSectionKeyList(ini, strNew("section1")), "|")), "key1|key2", "get keys for section");

        TEST_RESULT_VOID(iniSet(ini, strNew("section2"), strNew("key2"), strNew("2")), "set section2, key");
        TEST_RESULT_INT(strLstSize(iniSectionList(ini)), 2, "number of sections");
        TEST_RESULT_STR(strPtr(strLstJoin(iniSectionList(ini), "|")), "section1|section2", "get sections");

        TEST_RESULT_BOOL(iniSectionKeyIsList(ini, strNew("section1"), strNew("key1")), false, "single value is not list");
        TEST_RESULT_VOID(iniSet(ini, strNew("section2"), strNew("key2"), strNew("7")), "set section2, key");
        TEST_RESULT_BOOL(iniSectionKeyIsList(ini, strNew("section2"), strNew("key2")), true, "section2, key2 is a list");
        TEST_RESULT_STR(strPtr(strLstJoin(iniGetList(ini, strNew("section2"), strNew("key2")), "|")), "2|7", "get list");

        TEST_RESULT_VOID(iniFree(ini), "free ini");
    }

    // *****************************************************************************************************************************
    if (testBegin("iniParse()"))
    {
        Ini *ini = NULL;
        String *content = NULL;

        // -------------------------------------------------------------------------------------------------------------------------
        TEST_RESULT_VOID(iniParse(iniNew(), NULL), "no content");
        TEST_ERROR(
            iniParse(iniNew(), strNew("compress=y\n")), FormatError, "key/value found outside of section at line 1: compress=y");
        TEST_ERROR(iniParse(iniNew(), strNew("[section\n")), FormatError, "ini section should end with ] at line 1: [section");
        TEST_ERROR(iniParse(iniNew(), strNew("[section]\nkey")), FormatError, "missing '=' in key/value at line 2: key");
        TEST_ERROR(iniParse(iniNew(), strNew("[section]\n =value")), FormatError, "key is zero-length at line 1: =value");

        // -------------------------------------------------------------------------------------------------------------------------
        TEST_ASSIGN(ini, iniNew(), "new ini");

        content = strNew
        (
            "# Comment\n"
            "[global] \n"
            "compress=y \n"
            "\n"
            " [db]\n"
            "pg1-path = /path/to/pg"
        );

        TEST_RESULT_VOID(iniParse(ini, content), "load ini");

        TEST_RESULT_STR(strPtr(iniGet(ini, strNew("global"), strNew("compress"))), "y", "get compress");
        TEST_RESULT_STR(strPtr(iniGet(ini, strNew("db"), strNew("pg1-path"))), "/path/to/pg", "get pg1-path");
    }

    // *****************************************************************************************************************************
    if (testBegin("iniSave()"))
    {
        Ini *ini = iniNew();
        iniSet(ini, strNew("section2"), strNew("key1"), strNew("value1"));
        iniSet(ini, strNew("section1"), strNew("key2"), strNew("value2"));
        iniSet(ini, strNew("section1"), strNew("key1"), strNew("value1"));

        StorageFileWrite *write = storageNewWriteNP(storageTest, strNew("test.ini"));
        TEST_RESULT_VOID(iniSave(ini, storageFileWriteIo(write)), "save ini");

        TEST_RESULT_STR(
            strPtr(strNewBuf(storageGetNP(storageNewReadNP(storageTest, strNew("test.ini"))))),
            "[section1]\n"
                "key1=value1\n"
                "key2=value2\n"
                "\n"
                "[section2]\n"
                "key1=value1\n",
            "check ini");
    }

    FUNCTION_HARNESS_RESULT_VOID();
}
