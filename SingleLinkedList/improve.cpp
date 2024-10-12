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
    Node* findPrePos()//找到currentPos的前一个位置  
    {
        if(currentPos!=nullptr&&currentPos!=head)//排除当前位置为头和空的情况
    {
        Node* p=head;
        while(p->next!=currentPos)
        {
            p=p->next;
        }
        return p;
    }
    else
        return nullptr;
    }; 
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

   
    void insert(T _val); /// 在 currentPos 后面插入一个元素，数据为 _val
    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;  
    /// 删除 currentPos 后面的元素
    void remove();  
    void insertbefore(T _val);   //在currentPos前插入，数据为_val                                 
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
        if(size==1)//只有一个元素则清空链表
        {
            emptyList();
        }
        else if(size>1)
        {
            Node* p=findPrePos();
            p->next=currentPos->next;
            delete currentPos;
            currentPos=p->next;//更新currentPos
            --size;
        }
    }
}



template <typename T>
void SingleLinkedList<T>::insertbefore(T _val)
{
    if(size==0)//空链表直接插入
    {
        head=new Node(_val);
        currentPos=head;
    }
    else
    {
        Node* newNode = new Node(_val);
        newNode->next=currentPos;
        Node* p=findPrePos();
        if(p==nullptr)  //在链表的开头插入元素
        {    
            p=newNode;
            head=newNode;
        }
        else//在链表的中间插入元素
            p->next=newNode;
        currentPos=newNode;
    }
    ++size;
}


int main()
{
    SingleLinkedList<char> e;    
    SingleLinkedList<double> c1;    
    SingleLinkedList<double> c2{1.5,2.0,9.0,4.7,8.8};     
    c1.insert(3.0);    
    std::cout << "this is c1:";
    c1.printList();
    std::cout << "this is c2:";    
    c2.printList();
    std::cout << "this is e:";
    e.printList(); 
    std::cout << "test remove" << std::endl;
    e.remove();//空链表    
    c1.remove();//链表只有一个元素
    bool f = c2.find(9.0);    
    c2.remove(); //移除元素9.0   
    e.printList();    
    c1.printList();    
    c2.printList();
    std::cout << "test insertbefore" << std::endl;
    c1.insertbefore(6.6);//在空链表c1中插入6.6
    bool t=c2.find(4.7);
    c2.insertbefore(6.6);//在c2链表中找到4.7（中间元素），在其之前插入6.6
    c1.printList();
    c2.printList();
    t=c2.find(1.5);
    c2.insertbefore(6.6);//在C2链表中找到1.5（头元素），在其之前插入6.6
    c2.printList();

    return 0;
}