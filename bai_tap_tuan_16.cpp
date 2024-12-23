#include <iostream>
using namespace std;

// Cấu trúc của một nút trong cây AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};
// Hàm trả về chiều cao của một nút
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Hàm tính hệ số cân bằng của một nút
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}
// Hàm xoay phải
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Trả về nút mới sau khi xoay
    return x;
}

// Hàm xoay trái
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Trả về nút mới sau khi xoay
    return y;
}
// Hàm chèn một nút mới vào cây AVL và duy trì cân bằng
Node* insert(Node* node, int key) {
    // 1. Chèn như cây nhị phân tìm kiếm
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else { // Trường hợp key đã tồn tại, chúng ta không chèn trùng
        cout << "Key " << key << " đã tồn tại trong cây. Không chèn trùng.\n";
        return node;
    }

    // 2. Cập nhật chiều cao của cây
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Tính hệ số cân bằng để kiểm tra xem cây có bị mất cân bằng không
    int balance = getBalance(node);

    // Nếu nút này mất cân bằng, có 4 trường hợp

    // Trường hợp Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Trả về nút không thay đổi
    return node;
}
// Hàm duyệt cây theo thứ tự in-order
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}
int main() {
    Node* root = nullptr;

    // Dãy số cần chèn vào cây AVL
    int keys[] = { 17, 23, 201, 98, 67, 83, 13, 23, 10, 198, 84, 58 };
    int n = sizeof(keys) / sizeof(keys[0]);

    // Chèn các phần tử vào cây AVL
    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    // In cây theo thứ tự in-order
    cout << "Duyet in-order cua cay AVL: ";
    inOrder(root);
    cout << endl;

    return 0;
}
