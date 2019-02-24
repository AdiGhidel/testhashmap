#include "Hash.hpp"
using namespace std;
//==================================================================================
//HashNode
template <typename K, typename V>
K HashNode<K, V>::getKey()
{
    return key;
}
template <typename K, typename V>
V HashNode<K, V>::getValue()
{
    return value;
}
template <typename K, typename V>
pair<K, V> HashNode<K, V>::getKeyValue()
{
    pair<K, V> p;
    p.first = key;
    p.second = value;
    return p;
}
template <typename K, typename V>
void HashNode<K, V>::setKey(K key)
{
    this->key = key;
}
template <typename K, typename V>
void HashNode<K, V>::setValue(V value)
{
    this->value = value;
}
template <typename K, typename V>
void HashNode<K, V>::setKeyValue(K key, V value)
{
    this->key = key;
    this->value = value;
}

//==================================================================================
//Buckets
template <typename K, typename V>
bool Bucket<K, V>::insertElement(HashNode<K, V> node)
{
    this->nodes.push_back(node);
    return true;
}
template <typename K, typename V>
bool Bucket<K, V>::removeElement(HashNode<K, V> node)
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        if (this->nodes[i] == node)
        {
            this->nodes.erase(this->nodes.begin() + i);
            return true;
        }
    }
    return false;
}
template <typename K, typename V>
bool Bucket<K, V>::removeElement(K key)
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        if (this->nodes[i].getKey() == key)
        {
            cout << " erasing node" << endl;
            this->nodes.erase(this->nodes.begin() + i);
            return true;
        }
    }
    return false;
}
template <typename K, typename V>
pair<bool, V> Bucket<K, V>::findValue(K key)
{
    pair<bool, V> p;
    for (auto it : this->nodes)
    {
        if (it.getKey() == key)
        {
            p.first = true;
            p.second = it.getValue();
            return p;
        }
    }
    p.first = false;
    p.second = NULL;
    return p;
}
template <typename K, typename V>
HashNode<K, V> Bucket<K, V>::findNode(K key)
{
    pair<bool, V> p;
    for (auto it : this->nodes)
    {
        if (it.getKey() == key)
        {
            return it;
        }
    }
    HashNode<K, V> n(K(0), V(0)); //how to return null?
    return n;
}
//==================================================================================
//Hashmap
template <typename K, typename V>
HashMap<K, V>::HashMap()
{
    bucketSize = 4;
    occupied = 0;
    Buckets.resize(bucketSize);
}
template <typename K, typename V>
void HashMap<K, V>::resize(bool half)
{
    if (half)
    {
        //resize only if you have at least intital size
        if (bucketSize > 4)
        {
            bucketSize >>= 2;
            vector<Bucket<K, V>> oldBuckets = Buckets;

            Buckets.clear();
            Buckets.resize(bucketSize);

            for (int i = 0; i < oldBuckets.size(); i++)
            { //entire size of old vector
                vector<HashNode<K, V>> nodelist = oldBuckets[i].nodes;
                for (int j = 0; j < nodelist.size(); j++)
                {
                    this->insert(nodelist[j]);
                }
            }
        }
        else
        {
            bucketSize <<= 2;
            vector<Bucket<K, V>> oldBuckets = Buckets;

            Buckets.clear();
            Buckets.resize(bucketSize);

            for (int i = 0; i < oldBuckets.size(); i++)
            { //entire size of old vector
                vector<HashNode<K, V>> nodelist = oldBuckets[i].nodes;
                for (int j = 0; j < nodelist.size(); j++)
                {
                    this->insert(nodelist[j]);
                }
            }
        }
    }
}
template <typename K, typename V>
int HashMap<K, V>::hash(K key)
{
    std::hash<K> hashfct;
    return hashfct(key) % bucketSize;
}
template <typename K, typename V>
void HashMap<K, V>::check_size(int delta)
{
    //if add
    if (occupied + delta >= bucketSize / 2)
    {
        //not half
        resize(false);
    }
    //if remove
    if (occupied + delta <= bucketSize / 4)
    {
        //half
        resize(true);
    }
    //do nothing
}
template <typename K, typename V>
void HashMap<K, V>::insert(HashNode<K, V> node)
{
    //will resize if necessary
    check_size(ADD);
    int pos = this->hash(node.getKey());
    Buckets[pos].insertElement(node);
    occupied++;
}
template <typename K, typename V>
bool HashMap<K, V>::remove(HashNode<K, V> node)
{
    K key = node.getKey();
    int pos = this->hash(key);
    Bucket<K, V> b = Buckets[pos];
    //try to find the key in bucket
    if (b.findValue(key).first == false)
    {
        return false;
    }
    else
    { //if found
        //will resize if necessary
        check_size(REMOVE);
        b.removeElement(node);
        occupied--;
    }
    return true;
}

template <typename K, typename V>
bool HashMap<K, V>::remove(K key)
{
    //will resize if necessary
    int pos = this->hash(key);
    Bucket<K, V> b = Buckets[pos];
    //try to find the key in bucket
    if (b.findValue(key).first == false)
    {
        return false;
    }
    else
    {
        //if found
        check_size(REMOVE);
        cout << "try to remove :" << b.removeElement(key) << endl;
        occupied--;
    }
    return true;
}
template <typename K, typename V>
HashNode<K, V> HashMap<K, V>::find(K key)
{
    int pos = this->hash(key);
    Bucket<K, V> b = Buckets[pos];
    return b.findNode(key);
}
template <typename K, typename V>
V HashMap<K, V>::getValue(K key)
{
    int pos = this->hash(key);
    Bucket<K, V> b = Buckets[pos];
    if (b.findValue(key).first == false)
    {
        return V(INT_MIN);
    }
    else
    {
        return b.findValue(key).second;
    }
}


//==================================================================================
int main()
{
    //Hashnode UT
    HashNode<int, int> h = HashNode<int, int>(1, 2);
    cout << h.getValue() << h.getKey() << endl;
    h.setKey(10);
    h.setValue(20);
    cout << h.getKeyValue().first << " " << h.getKeyValue().second << endl;
    //Bucket UT
    Bucket<int, int> b;
    b.insertElement(HashNode<int, int>(12, 13));
    b.insertElement(HashNode<int, int>(23, 24));
    cout << b.findValue(1).first << endl;
    cout << b.findValue(12).first << " " << b.findValue(12).second << endl;
    cout << b.removeElement(100) << endl;
    cout << b.removeElement(12) << endl;
    cout << b.removeElement(HashNode<int, int>(23, 24)) << endl;

    //HashMap ut
    HashMap<string, int> hash;
    hash.insert(HashNode<string, int>("dedu", 10));
    cout << hash.find("dedu").getKey() << " " << hash.find("dedu").getValue() << endl;
    cout << hash.getValue("dedu") << endl;
    cout << hash.getValue("x") << endl;
    hash.remove("dedu");
    cout << hash.getValue("dedu") << endl;
    return 0;
}