#include "map_lru_cache.h"

using namespace lru_cache;

int CLRUCache::set( const HashKey& key, const string &value )
{
        HashValue hash_value;
        hash_value.value_ = value;
        hash_value.access_ = get_virtual_time();

        pair< map<HashKey, HashValue>::iterator, bool > ret = _hash_table.insert(make_pair(key, hash_value));

        if ( !ret.second )
        {
                // key already exist
                virtual_time old_access = _hash_table[key].access_;
                map<virtual_time, HashKey>::iterator iter = _lru_list.find(old_access);
                if(iter != _lru_list.end())
                {
                        _lru_list.erase(iter);
                }

                _lru_list.insert(make_pair(hash_value.access_, key));
                _hash_table[key] = hash_value;


        }

        else
        {
                _lru_list.insert(make_pair(hash_value.access_, key));

                if ( _hash_table.size() > DEF_CAPACITY ) //ÌÔÌ­
                {
                        // get the least recently used key
                        map<virtual_time, HashKey>::iterator iter = _lru_list.begin();


                        _hash_table.erase( iter->second );
                        // remove last key from list
                        _lru_list.erase(iter);
                }
        }
        return 0;
}

HashValue* CLRUCache::get( const HashKey& key )
{
        map<HashKey, HashValue>::iterator iter = _hash_table.find(key);
        if ( iter != _hash_table.end() )
        {
                virtual_time old_access = iter->second.access_;
                iter->second.access_ = get_virtual_time();

                map<virtual_time, HashKey>::iterator it = _lru_list.find(old_access);
                if(it != _lru_list.end())
                {
                        _lru_list.erase(it);
                }

                _lru_list.insert(make_pair(iter->second.access_, key));

                return &(iter->second);
        }

        else
                return NULL;
}