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
    this->nodes.push_back(node);
    return true;
}
template <typename K, typename V>
bool Bucket<K,V>::removeElement(HashNode<K,V> node) {
    for (int i = 0; i < this->nodes.size(); i++) {
        if (this->nodes[i] == node) {
            this->nodes.erase(this->nodes.begin() + i);
            return true;
        }
    }
    return false;
}
template <typename K, typename V>
bool Bucket<K,V>::removeElement(K key) {
    for (int i = 0; i < this->nodes.size(); i++) {
        if (this->nodes[i].getKey() == key) {
           this->nodes.erase(this->nodes.begin() + i);
        return true;
        }
    }
    return false;
}
template <typename K, typename V>
pair <bool, V> Bucket<K,V>::findValue(K key) {
    pair<bool, V> p;
    for (auto it : this->nodes) {
        if (it.getKey() == key) {
            p.first = true;
            p.second = it.getValue();
            return p;
        }
    }
    p.first = false; p.second = NULL;
    return p;
}
//Hashmap
int main() {
    //Hashnode UT
    HashNode<int,int> h = HashNode<int,int>(1,2);
    cout << h.getValue() << h.getKey() << endl;
    h.setKey(10); h.setValue(20);
    cout << h.getKeyValue().first <<" "<<h.getKeyValue().second << endl;
    //Bucket UT
    Bucket<int,int> b;
    b.insertElement(HashNode<int,int>(12,13));
    b.insertElement(HashNode<int,int>(23,24));
    cout << b.findValue(1).first << endl;
    cout << b.findValue(12).first<<" "<<b.findValue(12).second << endl;
    cout << b.removeElement(100) << endl;
    cout << b.removeElement(12) << endl;
    cout << b.removeElement(HashNode<int,int>(23,24)) << endl;
    return 0;
}