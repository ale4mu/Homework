#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        if( isEmpty( ) )
            throw UnderflowException{ };
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}


    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height;
        /**
         * @brief 构造函数，接受常量引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt,int h=0)
            : element{ theElement }, left{ lt }, right{ rt },height{h} {}

        /**
         * @brief 构造函数，接受右值引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt,int h=0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt },height{h} {}
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针                
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode * &t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr, 
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } 
        else if (x < t->element) {
            insert(x, t->left);
        } 
        else if (x > t->element) {
            insert(x, t->right);
        } 
        else 
        {
            /// 如果元素已存在，则不进行插入
          /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
       balance(t);
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
        balance(t);
    }

  

    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

   

    /// @brief 找子树的最小节点并删除，如果该节点有right child则parent->left=right child
    /// @param t 
    /// @return 最小节点
    BinaryNode *detachMin(BinaryNode *&t)
    {
        if(t==nullptr)
            return nullptr;
        if(t->left == nullptr)//t没有left child的情况下t就是最小节点
        {
            BinaryNode *minNode = t;
            t=t->right; 
            balance(t);
            minNode->right = nullptr;
            return minNode;
        }
        else//t存在left child
        {   
            BinaryNode *minNode=t->left;
            if(t->left->left == nullptr)
            {
            t->left = minNode->right;//parent->left=最小节点->right，最小节点只可能存在right child，若不存在则都为nullptr
            minNode->left=nullptr;//清空minNode
            minNode->right=nullptr;
            }
            else
            {
              minNode=detachMin(t->left);
            }
            balance(t->left);
            return minNode;
        }
    }
    
    /// @brief 删除指定元素x
    /// @param x 
    /// @param t 
    void remove(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            return;  
        }
        if (x < t->element) {
            remove(x, t->left);
        } 
        else if (x > t->element) {
            remove(x, t->right);
        } 
        else if (t->left != nullptr && t->right != nullptr) //待删除节点有两个子节点
        {  
            BinaryNode *minNode = detachMin(t->right); //右子树的最小元素节点
            minNode->left = t->left;
            minNode->right = t->right;
            delete t;
            t = minNode;
        } 
        else //待删除节点有一个或没有子节点
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }
        
    static const int ALLOWED_IMBALANCE = 1;
    int height( BinaryNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    
    void balance( BinaryNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};
