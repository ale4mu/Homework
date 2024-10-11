#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find (const T &_val);
    SingleLinkedList(){};
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val); 
    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;  
    /// 删除 currentPos 后面的元素
    void remove();                                        
};

template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;    
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}

template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if(currentPos!=nullptr)
    {
        return currentPos->data;
    }
    else
    {
        std::cerr << "Empty current position!Can't get value!" << std::endl;
        throw std::runtime_error("Empty current position! Can't get value!");
    }
}

template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if(currentPos!=nullptr)
    {
        currentPos->data=_val;
    }
    else
    {   
        std::cerr << "Empty current position!Can't set value!" << std::endl;
    }
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return size==0;
}

template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    if(size==0)
    {
        head=new Node(_val);
        currentPos=head;
    }
    else
    {
        Node* newNode = new Node(_val);
        newNode->next=currentPos->next;
        currentPos->next=newNode;
        currentPos=newNode;
    }
    ++size;
}


template <typename T>
void SingleLinkedList<T>::remove()
{
    if(currentPos!=nullptr)
    {
        if(size==1)
        {
            emptyList();
        }
        else if(size>1&&(currentPos->next!=nullptr))
        {
            Node* p=currentPos->next;
            currentPos->next=p->next;
            delete p;
            currentPos=currentPos->next;//更新currentPos
            --size;
        }
    }
}



int main()
{
    SingleLinkedList<int> a{1,2,3,4,5};
    int a_get = a.getCurrentVal();    
    std::cout << a_get << std::endl;
    
    SingleLinkedList<char> b{'a','c','e'};    
    b.setCurrentVal('g');    
    b.printList();
    
    SingleLinkedList<char> e;    
    std::cout << b.isEmpty() << " "<< e.isEmpty() << std::endl;

    SingleLinkedList<double> c1;    
    SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};   
    SingleLinkedList<double> c3;    
    c3 = c2;
    //std::cout << "c3" << std::endl;
    //c3.printList();
    c1.insert(3.0);    
    c2.insert(8.8);
    bool f_c3 = c3.find(2.0);    
    c3.insert(8.8);  
    c1.printList();    
    c2.printList();     
    c3.printList();

    e.remove();    
    c1.remove();
    bool f = c2.find(9.0);    
    c2.remove();    
    e.printList();    
    c1.printList();    
    c2.printList();

    return 0;
}