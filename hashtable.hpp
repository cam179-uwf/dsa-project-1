#ifndef HASHTABLE
#define HASHTABLE

#include <string>
#include <iostream>

/**
 * Keeps track of each entry in a bucket.
 */
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

/**
 * Holds singlely linked lists of entries (Nodes).
 */
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

    /**
     * Add an entry to this bucket.
     */
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

    /**
     * Find and entry in this bucket.
     * @returns The entry (Node) if found, otherwise a nullptr.
     */
    Node<T>* find(const std::string& key)
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

/**
 * Used for quick lookups.
 */
template<typename T>
class HashTable
{
    Bucket<T>* _buckets;
    int _numberOfBuckets;

    /**
     * Generates a hash for a given key.
     * @returns The bucket index for this key.
     */
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
        if (numberOfBuckets < 1)
        {
            std::__throw_out_of_range("The number of buckets in a hash table must be more than or equal to one.");
        }

        _numberOfBuckets = numberOfBuckets;
        _buckets = new Bucket<T>[_numberOfBuckets];
    }

    ~HashTable()
    {
        delete[] _buckets;
    }

    HashTable(HashTable<T>& other) = delete;
    HashTable<T>& operator=(HashTable<T>& other) = delete;

    /**
     * Pushes a value into a specific bucket given the values key.
     */
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

    /**
     * Print out all of the buckets and their entry counts.
     */
    void print_bucket_counts()
    {
        for (int i = 0; i < _numberOfBuckets; ++i)
        {
            std::cout << "Bucket " << i << ": " << _buckets[i].size << std::endl;
        }
    }
};

#endif