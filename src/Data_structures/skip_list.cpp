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
    SkipListNode(const T& value, int level, bool empty_node=false): value(value), empty_node(empty_node) {
        if (!empty_node) {
            for (int i = 0; i < level; i++) {
                T def_value;
                forward.emplace_back(new SkipListNode(def_value, 0, true));
            }
        }
    }
    
    std::vector<SkipListNode*> forward;
    T value;
    bool empty_node;
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

    int get_random_level() {
        int level = 1;
        while (coin_flip(gen) <= probablity_of_promotion && level < kMaxLevel) {
            level++;
        }

        return level;
    }

    int count_nodes(const SkipListNode<T>* nodes) {
        return nodes->forward.size();
    }

    //! Modifying functions
    
    void insert(const T& value) {
        std::vector<SkipListNode<T>*> needs_updates(head->forward);
        int cur_max_level = count_nodes(head);
        SkipListNode<T>* current = head;

        for (int i = cur_max_level - 1; i >= 0; i--) {
            while (!current->forward[i]->empty_node && current->forward[i]->value < value) {
                current = current->forward[i];
            }

            needs_updates[i] = current;
        }

        int new_node_level = get_random_level();
        current = new SkipListNode<T>(value, new_node_level);

        for (int i = 0; i < new_node_level; ++i) {
            current->forward[i] = needs_updates[i]->forward[i];
            needs_updates[i]->forward[i] = current;
        }
    }

    SkipListNode<T>* get_head() {
        return head;
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

template<class T>
std::vector<T> vector_from_skip_list(SkipList<T>& list) {
    std::vector<T> answer;
    SkipListNode<T>* current = list.get_head()->forward[0];

    while (!current->empty_node) {
        answer.push_back(current->value);
        current = current->forward[0];
    }

    return answer;
}

#endif