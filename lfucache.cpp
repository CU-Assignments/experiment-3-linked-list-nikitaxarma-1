class LFUCache {
public:
    struct Node {
        int key, value;
        int freq;
        Node(int k, int v) {
            key = k;
            value = v;
            freq = 1;
        }
    };

    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        auto node = cache[key];
        update(node);
        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (cache.find(key) != cache.end()) {
            auto node = cache[key];
            node->value = value;
            update(node);
        } else {
            if (cache.size() == capacity) {
                auto evict = freq[minFreq].back();
                cache.erase(evict->key);
                freq[minFreq].pop_back();
                if (freq[minFreq].empty()) {
                    freq.erase(minFreq);
                }
                delete evict;
            }
            auto newNode = new Node(key, value);
            cache[key] = newNode;
            freq[1].push_front(newNode);
            minFreq = 1;
        }
    }

private:
    int capacity, minFreq;
    unordered_map<int, Node*> cache;
    unordered_map<int, list<Node*>> freq;

    void update(Node* node) {
        int frequency = node->freq;
        freq[frequency].remove(node);
        if (freq[frequency].empty()) {
            freq.erase(frequency);
            if (minFreq == frequency) {
                minFreq++;
            }
        }
        node->freq++;
        freq[node->freq].push_front(node);
    }
};
