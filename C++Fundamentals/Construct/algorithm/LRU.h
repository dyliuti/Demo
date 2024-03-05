#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <assert.h>
using namespace::std;

struct Node{
    Node() = default;
    Node(Node& n):key(n.key), val(n.val), prev(n.prev), next(n.next){}
    Node(int k, int v, Node* p = nullptr, Node* n = nullptr):key(k), val(v), prev(p), next(n){}
    int key{}, val{};
    Node* prev = nullptr;
    Node* next = nullptr;

    unique_ptr<Node> clone(){ // 这里用unique_ptr居然会出错？
        return make_unique<Node>(key, val, prev, next);
    }
};
// 尾部的数据是最近使用的
class DoubleList{
public:
    DoubleList(){
        head = make_unique<Node>(0, 0);
        tail = make_unique<Node>(0, 0);
        head->next = tail.get();
        tail->prev = head.get();
        m_size = 0;
    }
    // 或者用node传进来key、val值，也要new
    void addLast(Node* node){
        node->next = tail.get();
        node->prev = tail->prev;
        tail->prev->next = node;
        tail->prev = node; // 前面用到tail->prev所以放最后更改
        m_size++;
    }

    void remove(Node* node){
        if(node == nullptr){
            assert(false);
        }

        node->prev = node->next;
        node->next->prev = node->prev;
        delete node; // 删除资源 也该特有函数 去管理资源
        m_size--;
    }

    // 删除链表中第一个节点，并返回该节点，时间复杂度o(1)
    // 不该用Node* 把类里创建资源的指针暴露给外面
    // 这里用返回shared_ptr替换了std中的itertor
    unique_ptr<Node> removeFirst(){
        if(head->next == tail.get() || head->next == nullptr){
            return nullptr;
        }
        // 右值引用
        unique_ptr<Node> copyNode = head->next->clone();
        remove(head->next);
        return copyNode;
    }

    int size(){return m_size;}
private:
    unique_ptr<Node> head;
    unique_ptr<Node> tail;
    // 链表个数
    int m_size = 0;
};

// makeRecently(k)  addRecently(k, v) deleteKey(k) removeLeastRecently() 成对出现的
class LRUCache{
public:
    LRUCache() = default;
    LRUCache(int c):cap(c){
        cache = make_unique<DoubleList>();
    }

    void makeRecently(int key){
        if(m_map.count(key) == 0)
            assert(false);
        Node* node = m_map[key];
//        unique_ptr<Node> nodeCopy = node->clone();
        Node* copyNode = new Node(*node);
        cache->remove(node);
        cout << "111 makeRecently: " << node->key << node->val;
        cache->addLast(copyNode);  // 感觉这里有问题
    }

    void addRecently(int key, int val){
        Node* node = new Node(key, val);
        cache->addLast(node);
        m_map[key] = node;
    }

    void removeLeastRecently(){
        unique_ptr<Node> node = cache->removeFirst();
        m_map.erase(node->key);
    }

    int get(int key){
        if(m_map.count(key) == 0)
            return -1;
        std::cout << "test: " << m_map[key]->val << endl;
        makeRecently(key);
        return m_map[key]->val;
    }

    void put(int key, int val){
        // 如果已经存在了
        if(m_map.count(key) != 0){
            m_map[key]->val = val; // 多余
            makeRecently(key);
            // 或者先从map和cache中delete key，再addRecently
            return;
        }
        // 没存在但容量已经满了
        std::cout << "put: " << cap << " " << cache->size();
        if(cap == cache->size()){
            removeLeastRecently(); // 移除最久没使用的
        }

        // 问题出在这 只是指针 指针指向的已经删除了！
        addRecently(key, val);
    }

protected:
    // key->node(key, val)
    unordered_map<int, Node*> m_map;
    // Node(k1, v1)<->Node(k2, v2)
    unique_ptr<DoubleList> cache;
    // 最大容量
    int cap{};
};

class LRUTest {
    static void run() {
        std::cout << "1111111111";
        auto lruCache = make_shared<LRUCache>(2);
        lruCache->put(1, 1);
        lruCache->put(2, 2);
        std::cout << lruCache->get(1) << endl;
        lruCache->put(3, 3);
        std::cout << lruCache->get(2) << endl;
        lruCache->put(4, 4);
        std::cout << lruCache->get(1) << endl;
        std::cout << lruCache->get(3) << endl;
        std::cout << lruCache->get(4) << endl;
        std::cout << "2222222222";
    }
};

