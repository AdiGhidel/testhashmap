#include <bits/stdc++.h>
using namespace std;
#define ADD 1
#define REMOVE -1
//Node
template <typename K, typename V>
class HashNode
{
  private:
    K key;
    V value;

  public:
    HashNode(K key, V value) : key(key), value(value) {}
    K getKey();
    V getValue();
    pair<K, V> getKeyValue();
    void setKey(K key);
    void setValue(V value);
    void setKeyValue(K key, V value);
};
//compare 2 hashnodes
template <typename K, typename V>
bool operator==(HashNode<K, V> &l, HashNode<K, V> &r)
{
    return l.getKey() == r.getKey() && l.getValue() == r.getValue();
}
//Bucket
template <typename K, typename V>
class Bucket
{
  public:
    vector<HashNode<K, V>> nodes;

    Bucket() {}
    pair<bool, V> findValue(K key);
    HashNode<K, V> findNode(K key);
    bool removeElement(K key);
    bool insertElement(HashNode<K, V> node);
    bool removeElement(HashNode<K, V> node);
};

//HashMap
template <typename K, typename V>
class HashMap
{
  private:
    int bucketSize;
    int occupied;
    vector<Bucket<K, V>> Buckets;
    void resize(bool half);
    void check_size(int delta);
    int hash(K key);

  public:
    HashMap();
    void insert(HashNode<K, V> node);
    bool remove(HashNode<K, V> node);
    bool remove(K key);
    HashNode<K, V> find(K key);
    V getValue(K key);
};