#include<bits/stdc++.h> 
using namespace std;

template <typename K, typename V>
class HashNode {
private:
    K key;
    V value;
public:
    HashNode(K key, V value): key(key), value(value) { }
    K getKey();
    V getValue();
    pair<K, V> getKeyValue();
    void setKey(K key);
    void setValue(V value);
    void setKeyValue(K key, V value);
};

template <typename K, typename V>
class Bucket {
public:
    int hash;
    vector<HashNode<K,V>> nodes;
    Bucket(): hash(0) { }
};
template <typename K, typename V>
class HashMap {
private:
    int bucketSize;
    int occupied;
    vector<Bucket<K,V>> Buckets;
    void resize();
    bool check_size();
public: 
    HashMap();
    void insert();
    void remove();
    void find();
};