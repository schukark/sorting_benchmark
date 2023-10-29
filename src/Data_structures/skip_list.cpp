#pragma once

#ifndef SKIP_LIST_NODE_CPP
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> coin_flip(0.0, 1.0);

template<class T>
class SkipListNode {
public:
    SkipListNode(T&& value, int level, bool empty_node=false): value(value), empty_node(empty_node) {
        for (int i = 0; i < level; i++) {
            forward.emplace_back(nullptr);
        }
    }

private:
    T value;
    bool empty_node;
    std::vector<SkipListNode*> forward;
};

template<class T>
class SkipList {
public:
    SkipList(): probablity_of_promotion(0.5), kMaxLevel(16) {
        T default_value;
        head = new SkipListNode<T>(default_value, kMaxLevel);
        null_node = new SkipListNode<T>(default_value, kMaxLevel, true);

        for (size_t i = 0; i < head->forward.size(); ++i) {
            head->forward[i] = null_node;
        }
    }

    ~SkipList() {
        delete head;
        delete null_node;
    }

    //! HELPERS

    size_t get_random_level() {
        int level = 1;
        while (coin_flip(gen) <= probablity_of_promotion && level < kMaxLevel) {
            level++;
        }

        return level;
    }

    size_t count_nodes(const std::vector<SkipListNode<T>>& nodes) {
        int cur_level = 1;
        if (nodes[0]->empty_node) {
            return cur_level;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] != nullptr && !nodes[i]->empty_node) {
                cur_level++;
            }
        }

        return cur_level;
    }

    //! Modifying functions
    
    void insert(T&& value) {
        std::vector<SkipListNode<T>*> needs_updates(head->forward);
        uint8_t cur_max_level = count_nodes(head->forward);
        SkipListNode<T>* current = head;

        for (int i = cur_max_level - 1; i >= 0; i--) {
            while (!current->forward[i]->empty_node && current->forward[i]->value < value) {
                current = current->forward[i];
            }

            needs_updates[i] = current;
        }

        current = current->forward[0];

        int new_node_level = get_random_level();
        int cur_node_level = count_nodes(needs_updates);

        if (new_node_level > cur_node_level) {
            for (int i = cur_node_level + 1; i < new_node_level; ++i) {
                needs_updates[i] = head;
            }   
        }

        current = new SkipListNode<T>(value, new_node_level);

        for (int i = 0; i < new_node_level; ++i) {
            current->forward[i] = needs_updates[i]->forward[i];
            needs_updates[i]->forward[i] = current;
        }
    }

private:
    SkipListNode<T>* head;
    SkipListNode<T>* null_node;

    double probablity_of_promotion;
    const int kMaxLevel;
};


template<class T>
SkipList<T> list_from_vector(std::vector<T>& data) {
    SkipList<T> result;

    for (const auto& it : data) {
        result.insert(it);
    }

    return result;
}

#endif