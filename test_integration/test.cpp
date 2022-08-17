#include <cstdio>
#include <string>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
 
using namespace std;
using namespace rocksdb;
 
const std::string PATH = "./data_path";
int main(int argc, char** argv){
    DB* db;
    Options options;
    rocksdb::Env* spdk_env = rocksdb::NewSpdkEnv(rocksdb::Env::Default(), argv[1], argv[2], argv[3], 4096);
    printf("\n");
    if (spdk_env==NULL){
        printf("spdk_env initialization fail\n");
    }
    options.env = spdk_env;
    options.create_if_missing = true;
    Status status = DB::Open(options, PATH, &db);
    assert(status.ok());
    Slice key("foo");
    Slice value("bar");
    std::string get_value;
    status = db->Put(WriteOptions(), key, value);
    printf("put success!\n");
    if(status.ok()){
        status = db->Get(ReadOptions(), key, &get_value);
        if(status.ok()){
            printf("get %s success!!\n", get_value.c_str());
        }else{
            printf("get failed\n");
        }
    }else{
        printf("put failed\n");
    }
    delete db;
    return 0;
}
