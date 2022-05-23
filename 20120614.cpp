#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;

//Bai 2
struct Node //cau truc node
{
    float data;
    Node *pNext;
};
struct linkedList //cau truc dslk
{
    Node *pHead;
    Node *pTail;
    int size = 0;
    int maxSize;
};
void Init(linkedList &l) //Khoi tao dslk
{
    l.pHead = l.pTail = NULL;
    l.size = 0;
    l.maxSize = 5;
}
bool IsEmpty(linkedList &l) //kiem tra dslk rong
{
    if (l.size == 0)
    {
        return true;
    }
    return false;
}
bool IsFull(linkedList &l) //kiem tra dslk full
{
    if (l.size == l.maxSize)
    {
        return true;
    }
    return false;
}
Node *createNode(float x) //tao node
{
    Node *newNode = new Node;
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}
void delFront(linkedList &l) //xoa phan tu dung dau
{
    if (IsEmpty(l) == true)
    {
        l.pHead = l.pTail = NULL;
    }
    else
    {
        Node *pDel = l.pHead;
        l.pHead = l.pHead->pNext;
        delete pDel;
        l.size--;
    }
}
void delBack(linkedList &l) //xoa phan tu dung sau
{
    if (IsEmpty(l) == true)
    {
        l.pHead = l.pTail = NULL;
    }
    else
    {
        Node *pDel = l.pTail;
        Node *pCur = l.pHead;
        while (pCur->pNext != pDel)
        {
            pCur = pCur->pNext;
        }
        pCur->pNext = NULL;
        l.pTail = pCur;
        delete pDel;
        l.size--;
    }
}
void delMid(linkedList &l, Node *pDel)
{
    Node *pCur = l.pHead;
    while (pCur->pNext != pDel)
    {
        pCur = pCur->pNext;
    }
    pCur->pNext = pDel->pNext;
    delete pDel;
    l.size--;
}
void delNode(linkedList &l, Node *pDel)
{
    if (pDel == l.pHead)
    {
        delFront(l);
    }
    else if (pDel == l.pTail)
    {
        delBack(l);
    }
    else
    {
        delMid(l, pDel);
    }
}
void addBack(linkedList &l, float x) //Bai2: chuc nang 1
{
    Node *newNode = createNode(x);
    if (IsFull(l) == true) // neu dslk full thi xoa phan tu dau tien
    {
        delFront(l);
    }
    if (IsEmpty(l) == true) //neu dslk rong thi khoi tao dslk sau do gan head=tail=newnode
    {
        Init(l);
        l.pHead = l.pTail = newNode;
    }
    else //them phan tu vao sau dslk
    {
        l.pTail->pNext = newNode;
        l.pTail = newNode;
    }
    l.size++; //tang so phan tu len 1 don vi
}
void displayLinkedList(linkedList l)
{
    for (Node *i = l.pHead; i != NULL; i = i->pNext)
    {
        cout << i->data << " ";
    }
    cout << endl;
}
void sapXepTangDan(linkedList &l)
{
    for (Node *i = l.pHead; i->pNext != NULL; i = i->pNext)
    {
        for (Node *j = i->pNext; j != NULL; j = j->pNext)
        {
            if (i->data > j->data)
            {
                float temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
float tong3PhanTuLonNhat(linkedList &l) //tim 3 phan tu lon nhat trong dslk
{
    linkedList l2;
    l2 = l;
    sapXepTangDan(l2);
    int sum = 0;
    int i = 0;
    Node *pCur = l2.pHead;
    while (i < l2.size - 3)
    {
        pCur = pCur->pNext;
    }
    for (pCur; pCur != NULL; pCur = pCur->pNext)
    {
        sum += pCur->data;
    }
    return sum;
}
void addSum(linkedList &l) //Bai 2: chuc nang 2
{
    float sum = tong3PhanTuLonNhat(l);
    addBack(l, sum);
}
bool isInList(linkedList &l, int val)
{
    for (Node *i = l.pHead; i != NULL; i = i->pNext)
    {
        if (i->data == val)
        {
            return true;
        }
    }
    return false;
}
void delDuplicateElements(linkedList &l) //xoa tat ca cac node trung, chi giu lai 1 gia tri
{
    for (Node *p = l.pHead; p->pNext != NULL; p = p->pNext) //xét lần lượt các giá trị trong dslk
    {
        Node *q = p->pNext;  //gán q là phần tử tiếp theo
        while (q != nullptr) //q chạy từ p->pNext đến hết dslk
        {
            if (p->data == q->data) //nếu q->data = p->data thì gán q cho q->pNext để tiếp tục vòng lặp
            {
                Node *pDel = q;
                q = q->pNext;
                delNode(l, pDel); //xóa node có giá trị bằng với p->data cần xét
            }
            else
            {
                q = q->pNext;
            }
        }
    }
}
void Bai2ChucNang3(linkedList &l) //Bai 2: chuc nang 3
{
    l.maxSize *= 2; // tăng gấp đôi maxSize của dslk ban đầu
    linkedList l2;
    Init(l2);
    srand(time(NULL));
    float x = rand() % 10 + 1;
    addBack(l2, x);
    for (int i = 1; i < 5; ++i)
    {
        float val = (rand() % 10) + 1;
        while (isInList(l, val) == true) // tạo các giá trị ngẫu nhiên khác nhau
        {
            val = (rand() % 10) + 1;
        }
        addBack(l2, val); //Chèn vào dslk 2
    }
    //gộp vào dslk ban đầu
    l.pTail->pNext = l2.pHead;
    l.pTail = l2.pTail;
    sapXepTangDan(l);        //sắp xếp tăng dần
    delDuplicateElements(l); //xóa bớt phần tử trùng
}
void Bai2ChucNang1(linkedList &l)
{
    float x;
    cout << "Nhap phan tu muon them vao: ";
    cin >> x;
    Node *pCur = l.pHead;
    while (pCur != NULL && IsEmpty(l) == false)
    {
        if (pCur->data == x)
        {
            cout << "Da co phan tu nay trong danh sach!" << endl;
            cout << "Danh sach: " << endl;
            displayLinkedList(l);
            return;
        }
        pCur = pCur->pNext;
    }

    addBack(l, x);
    cout << "Danh sach: " << endl;
    displayLinkedList(l);
}
void Bai2ChucNang2(linkedList &l)
{
    if (l.size < 3)
    {
        cout << "Danh sach chi co " << l.size << " phan tu!" << endl;
    }
    else
    {
        addSum(l);
        cout << "Danh sach: " << endl;
        displayLinkedList(l);
    }
}
int MenuChinhBai2()
{
    cout << "=========================MENU 2========================" << endl;
    cout << "0. Thoat menu 2" << endl;
    cout << "1. Them gia tri x vao sau DSLK" << endl;
    cout << "2. Them tong gia tri cua 3 phan tu lon nhat vao DSLK" << endl;
    cout << "3. Ghep DSLK va xoa phan tu trung" << endl;
    return 3;
}
int LuaChonXuLy(int soluong)
{
    int n;
    cout << "-------Lua Chon Xu Ly: ";
    cin >> n;
    cout << endl;
    while (cin.fail() || n < 0 || n > soluong)
    {
        cout << "!!! Nhap sai !!!" << endl;
        cout << "!!! Moi nhap lai !!!" << endl;
        cout << "-------Lua Chon Xu Ly: ";
        cin >> n;
        cout << endl;
    }
    return n;
}
void XuLyMainMenuBai2(linkedList &l, int &lenh, int &kt)
{
    if (lenh == 1)
    {
        kt = 0;
        Bai2ChucNang1(l);
    }
    else if (lenh == 2)
    {
        if (kt == -1)
        {
            cout << "Danh sach rong" << endl;
        }
        else
        {
            kt = 0;
            Bai2ChucNang2(l);
        }
    }
    else if (lenh == 3)
    {
        if (kt == -1)
        {
            cout << "Danh sach rong" << endl;
        }
        else
        {
            kt = 0;
            Bai2ChucNang3(l);
            cout << "Danh sach: " << endl;
            displayLinkedList(l);
        }
    }
    if (lenh == 0)
    {
        char x;
        cout << "Nhap y de thoat: ";
        cin >> x;
        if (x != 'y')
        {
            lenh = -1;
        }
    }
    system("pause");
}
int Cau02() //Chạy bài 2
{
    int lenh = -1;
    int kt = -1;
    linkedList l;
    while (lenh != 0)
    {
        system("cls");
        lenh = LuaChonXuLy(MenuChinhBai2());
        XuLyMainMenuBai2(l, lenh, kt);
    }
    return 0;
}

//Bai 3
struct queue
{
    Node *pHead;
    Node *pTail;
    int size;
    int maxSize;
};
void InitQueue(queue &q) //Khởi tạo queue
{
    q.pHead = q.pTail = NULL;
    q.maxSize = 100;
    q.size = 0;
}
bool IsEmpty(queue &q) // Kiểm tra queue rỗng
{
    if (q.size == 0)
    {
        return true;
    }
    return false;
}
bool IsFull(queue &q) //Kiểm tra queue full
{
    if (q.size == q.maxSize)
    {
        return true;
    }
    return false;
}
void Push(queue &q, int x) //Thêm vào sau queue
{
    if (IsFull(q) == true)
    {
        cout << "Queue day!" << endl;
    }
    else
    {
        Node *newNode = createNode(x);
        if (IsEmpty(q) == true)
        {
            q.pHead = q.pTail = newNode;
        }
        else
        {
            q.pTail->pNext = newNode;
            q.pTail = newNode;
        }
        q.size++;
    }
}
void Pop(queue &q) //Lấy phần tử đầu và xóa
{
    if (IsEmpty(q) == true)
    {
        cout << "Queue rong!" << endl;
    }
    else
    {
        Node *pDel = q.pHead;
        q.pHead = q.pHead->pNext;
        delete pDel;
        if (q.pHead == NULL)
        {
            q.pHead = q.pTail = NULL;
        }
        q.size--;
    }
}
void displayQueue(queue q)
{
    for (Node *i = q.pHead; i != NULL; i = i->pNext)
    {
        cout << i->data << " ";
    }
    cout << endl;
}
void docFile(fstream &filein, queue &q)
{
    filein.open("INPUT.txt", ios::in);
    while (filein.eof() == false)
    {
        int x;
        filein >> x;
        Push(q, x);
    }
    filein.close();
}
void xuatFileBai3ChucNang1(fstream &fileout, int dem)
{
    fileout.open("OUTPUT1.txt", ios::out);
    fileout << dem;
    fileout.close();
}
int demViTri(queue &q, int &k)
{
    int dem = 0;
    for (Node *i = q.pHead; i->pNext != NULL; i = i->pNext)
    {
        if ((i->data < k && k < i->pNext->data))
        {
            dem++;
        }
    }
    if (q.pTail->data < k) //nếu k > giá trị cuối thì vẫn tính là vị trí đúng
    {
        dem++;
    }
    return dem;
}
void Bai3ChucNang1(queue &q)
{
    int k;
    cout << "Nhap gia tri k: ";
    cin >> k;
    cout << "So vi tri co the them " << k << " vao queue la: " << demViTri(q, k) << endl;
    fstream fileout;
    xuatFileBai3ChucNang1(fileout, demViTri(q, k));
    cout << "-----Da xuat ra OUTPUT1.txt" << endl;
}
void sapXepTangDanQueue(queue &q)
{
    for (Node *i = q.pHead; i->pNext != NULL; i = i->pNext)
    {
        for (Node *j = i->pNext; j != NULL; j = j->pNext)
        {
            if (i->data > j->data)
            {
                float temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
queue ganQueue(queue &q, queue &q2)
{
    for (Node *i = q2.pHead; i != NULL; i = i->pNext) //gán lại q2 cho q
    {
        Push(q, i->data);
    }
    return q;
}
void xuatFileBai3ChucNang2(fstream &fileout, queue q)
{
    fileout.open("OUTPUT2.txt", ios::out);
    for (Node *i = q.pHead; i != NULL; i = i->pNext)
    {
        fileout << i->data << " ";
    }
    fileout.close();
}
void Bai3ChucNang2(queue &q)
{
    queue q2;
    InitQueue(q2);
    Node *i = q.pHead;
    int dem = 0;
    int n = q.size;
    while (dem <= n)
    {
        if (i->data < 0) //nếu i->data < 0 thì thêm giá trị đó vào sau q2 sau đó xóa ở q
        {
            Push(q2, i->data);
            Pop(q);
        }
        else
        {
            Push(q, i->data); //i->data>0 thì thêm vào cuối q sau đó xóa đầu. Khi đó q sẽ toàn giá trị dương mà ko thay đổi thứ tự của các giá trị đó
            Pop(q);
        }
        i = q.pHead;
        dem++;
    }
    sapXepTangDanQueue(q2); //sắp xếp tăng dần q2
    q2 = ganQueue(q2, q);   //nối q vào q2
    q = q2;                 //gán q2 cho q
    fstream fileout;
    xuatFileBai3ChucNang2(fileout, q);
    cout << "-----Da xuat ra OUTPUT2.txt" << endl;
}
int MenuChinhBai3()
{
    cout << "=========================MENU 3========================" << endl;
    cout << "0. Thoat menu 3" << endl;
    cout << "1. Dem vi tri co the chen gia tri k" << endl;
    cout << "2. Sap xep cac so am va dua len truoc queue" << endl;
    return 2;
}
void XuLyMainMenuBai3(queue &q, int &lenh)
{
    if (lenh == 1)
    {
        Bai3ChucNang1(q);
        cout << "Hang doi: " << endl;
        displayQueue(q);
    }
    else if (lenh == 2)
    {
        Bai3ChucNang2(q);
        cout << "Hang doi: " << endl;
        displayQueue(q);
    }
    if (lenh == 0)
    {
        char x;
        cout << "Nhap y de thoat: ";
        cin >> x;
        if (x != 'y')
        {
            lenh = -1;
        }
    }
    system("pause");
}
int Cau03()
{
    fstream filein;
    queue q;
    InitQueue(q);
    docFile(filein, q);
    int lenh = -1;

    while (lenh != 0)
    {
        system("cls");
        lenh = LuaChonXuLy(MenuChinhBai3());
        XuLyMainMenuBai3(q, lenh);
    }
    return 0;
}

//Bai 1
struct stack
{
    Node *pHead;
    Node *pTail;
    int size;
    int maxSize;
};
struct node
{
    node *pNext;
    char data;
};
node *TaoNode(char x)
{
    node *newNode = new node;
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}
void InitStack(stack &s)
{
    s.pHead = s.pTail = NULL;
    s.maxSize = 50;
    s.size = 0;
}
bool IsEmptyStack(stack &s)
{
    if (s.size == 0)
    {
        return true;
    }
    return false;
}
bool IsFullStack(stack &s)
{
    if (s.size == s.maxSize)
    {
        return true;
    }
    return false;
}
void PushStack(stack &s, char value)
{
    if (IsFullStack(s) == true)
    {
        cout << "Ngan xep da day!!!" << endl;
    }
    else
    {
        if (IsEmptyStack(s) == true)
        {
            Node *newNode = createNode(value);
            s.pHead = s.pTail = newNode;
        }
        else
        {
            Node *newNode = createNode(value);
            newNode->pNext = s.pHead;
            s.pHead = newNode;
        }
        s.size++;
    }
}
void PopStack(stack &s) // Lay phan tu top va xoa
{
    if (IsEmptyStack(s) == true)
    {
        cout << "Ngan xep rong!!!" << endl;
    }
    else
    {
        Node *pDel = s.pHead;
        s.pHead = s.pHead->pNext;
        delete pDel;
        if (s.pHead == NULL)
        {
            s.pHead = s.pTail = NULL;
        }
    }
}
//42* ; 43+ ; 45- ; 47/
void nhapBieuThuc(string &str)
{
    getline(cin, str);
}
void check(char &x, stack &s, queue &q)
{
    for (char i = 48; i <= 57; i++)
    {
        if (i == x)
        {
            string temp = "";
            temp.push_back(x);
            Push(q, atof(temp.c_str()));
        }
    }
    if (x == 40 || x == 41)
    {
        PushStack(s, x);
    }
    if (x == 42 || x == 43 || x == 45 || x == 47)
    {
        if (IsEmptyStack(s) == true)
        {
            PushStack(s, x);
        }
        if (s.pHead->data = '(')
        {
            PushStack(s, x);
        }
    }
}


int main()
{
    Cau02();
    Cau03();
    return 0;
}
