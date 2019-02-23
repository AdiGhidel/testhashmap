#include "hash.hpp"
using namespace std;

//HashNode
template <typename K, typename V>
K HashNode<K,V>::getKey() {
    return key;
}
template <typename K, typename V>
V HashNode<K,V>::getValue() {
    return value;
}
template <typename K, typename V>
pair<K,V> HashNode<K,V>::getKeyValue() {
    pair<K,V> p;
    p.first = key;
    p.second = value;
    return p;
}
template <typename K, typename V>
void HashNode<K,V>::setKey(K key) {
    this->key = key;
}
template <typename K, typename V>
void HashNode<K,V>::setValue(V value) {
    this->value = value;
}
template <typename K, typename V>
void HashNode<K,V>::setKeyValue(K key, V value) {
    this->key = key;
    this->value = value;
}

//Buckets
template <typename K, typename V>
bool Bucket<K,V>::insertElement(HashNode<K,V> node) {
    if (!node) 
        return false;
    this->nodes.push_back(node);
    return true;
}
template <typename K, typename V>
bool Bucket<K,V>::removeElement(HashNode<K,V> node) {
    if (!node) 
        return false;
    for (auto it : this->nodes) {
        if (*it == node) {
            nodes.erase(it);
            return true;
        }
    }
    return false;
}
template <typename K, typename V>
pair <bool, V> Bucket<K,V>::findValue(K key) {
    pair<bool, V> p;
    for (auto it : this->nodes) {
        if (*it.getKey() == key) {
            p.first = true;
            p.value = *it.getValue();
            return p;
        }
    }
    p.first = false; p.second = NULL;
    return p;
}

int main() {
    //Hashnode UT
    HashNode<int,int> h = HashNode<int,int>(1,2);
    cout << h.getValue() << h.getKey() << endl;
    h.setKey(10); h.setValue(20);
    cout << h.getKeyValue().first <<" "<<h.getKeyValue().second << endl;

    return 0;
}