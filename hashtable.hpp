#ifndef HASHTABLE
#define HASHTABLE

#include <string>
#include <iostream>

template<typename T>
struct Node
{
    Node* next;
    std::string key;
    T value;

    Node(const std::string& key, const T& value)
    {
        this->next = nullptr;
        this->key = key;
        this->value = value;
    }

    ~Node()
    {
        delete next;
    }
};

template<typename T>
struct Bucket
{
    Node<T>* root;
    int size;

    Bucket()
    {
        this->root = nullptr;
        this->size = 0;
    }

    ~Bucket()
    {
        delete root;
    }

    void add(Node<T>* node)
    {
        ++this->size;

        if (root == nullptr)
        {
            root = node;
            return;
        }

        Node<T>* current = root;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = node;
    }

    Node<T>* find(std::string key)
    {
        Node<T>* current = root;

        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }
};

template<typename T>
class HashTable
{
    Bucket<T>* _buckets;
    int _numberOfBuckets;

    const int get_hash_value(const std::string& key)
    {
        int index = 0;

        for (auto c : key)
        {
            index += c;
        }

        index %= _numberOfBuckets;

        return index;
    }

public:
    HashTable(const int& numberOfBuckets)
    {
        _numberOfBuckets = numberOfBuckets;
        _buckets = new Bucket<T>[_numberOfBuckets];
    }

    ~HashTable()
    {
        delete[] _buckets;
    }

    void push(const std::string& key, const T& value)
    {
        _buckets[get_hash_value(key)].add(new Node<T>(key, value));
    }

    T* find(const std::string& key)
    {
        Node<T>* value = _buckets[get_hash_value(key)].find(key);

        if (value == nullptr)
        {
            return nullptr;
        }

        return &value->value;
    }

    void print_bucket_counts()
    {
        for (int i = 0; i < _numberOfBuckets; ++i)
        {
            std::cout << "Bucket " << i << ": " << _buckets[i].size << std::endl;
        }
    }
};

#endif