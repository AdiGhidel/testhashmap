#include<bits/stdc++.h> 
using namespace std;

//Node
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
//compare 2 hashnodes
template <typename K, typename V>
bool operator ==(const HashNode<K,V> &l, const HashNode<K,V> &r) {
    return l.key == r.key && l.value == r.value;
}
//Bucket
template <typename K, typename V>
class Bucket {
public:
    vector<HashNode<K,V>> nodes;
    Bucket() {}
    pair<bool, V> findValue(K key);
    bool insertElement(HashNode<K,V> node);
    bool removeElement(HashNode<K,V> node);
};

//HashMap
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