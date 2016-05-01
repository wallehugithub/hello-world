#ifndef _MAP_LRU_CACHE_H_
#define _MAP_LRU_CACHE_H_

#include <string.h>

#include <iostream>
#include <list>
#include <map>

using namespace std;

namespace lru_cache {

        static const int DEF_CAPACITY = 100000;

        typedef unsigned long long virtual_time;

        typedef struct _HashKey
        {// key的类型自定义，重要的是要overload <和==

        ｝HashKey;

        typedef struct _HashValue
        {
                string value_;
                virtual_time access_;
        }HashValue;


        class CLRUCache
        {
                public:

                        CLRUCache() : _lru_list(), _hash_table(), _now(0){}
                        virtual ~CLRUCache(){}

                        int set( const HashKey& key, const string &value );
                        HashValue* get( const HashKey& key );


                        unsigned get_lru_list_size(){ return (unsigned)_lru_list.size(); }
                        unsigned get_hash_table_size() { return (unsigned)_hash_table.size(); }
                        virtual_time get_now() { return _now; }

                 private:

                        virtual_time get_virtual_time()
                        {
                                return ++_now;
                        }

                        map<virtual_time, HashKey>    _lru_list;
                        map<HashKey, HashValue> _hash_table;
                        virtual_time _now;
        };

}
#endif