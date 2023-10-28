#pragma once

#ifndef SKIP_LIST_NODE_CPP

template<class T>
class SkipListNode {
public:
    SkipListNode(T&& value): value(value), next(nullptr), level_below(nullptr) {}

private:
    T value;
    SkipListNode* next;
    SkipListNode* level_below;
};



#endif