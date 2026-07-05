#### （一）插入（递归）

构建树：[20, 10, 30, 5, 15, 25]，观察插入5时的完整递归链：

<TEXT>

```
_insert_recursive(root=20)
  ├─ cmp<0 → left=10
  │   └─ _insert_recursive(node=10)
  │       ├─ cmp<0 → left=5
  │       │   └─ _insert_recursive(node=NULL)  ← 基准！
  │       │       └─ return new_node(5)
  │       │
  │       ├─ node->left = 0x500 (链接5到10)
  │       └─ return 0x300 (返回10节点)
  │
  └─ return 0x200 (返回20节点)
```

每次递归返回后，父节点对应的left或right指针都会被更新，但因为返回的本来就是原指针，所以树结构在逻辑上保持不变（只是新节点被链接）。

#### （二）删除

```
初始树：
      20(del)
     /    \
    10     30
   / \    /  \
  5  15  25  35
    /
   12

调用链：
bst_remove(bst, &20)
└─ _remove_recursive(node=20, key=20)
   ├─ cmp == 0 (找到20)
   ├─ 有两个孩子！
   ├─ successor = _find_min(30的右子树) → 25
   ├─ memcpy(20的位置, 25的数据) → 节点20变成25
   │
   └─ node->right = _remove_recursive(node=30, key=25)  ← 递归1
      ├─ cmp > 0 (25 < 30? 否，25<30，向左)
      ├─ node->left = _remove_recursive(node=25, key=25) ← 递归2
      │   ├─ cmp == 0 (找到25)
      │   ├─ 是叶子节点！(假设25无孩子)
      │   ├─ free(25的数据), free(25的节点)
      │   └─ return NULL
      ├─ node->left = NULL (30的left变为NULL)
      └─ return 30
      
   ├─ node->right = 30 (重新链接)
   └─ return 20 (根节点返回)

内存变化时间线：
T0: 20(0x1000)=20, 30(0x3000)=30, 25(0x7000)=25
T1: 20(0x1000)=25 (数据复制), 25(0x7000)=25 (仍存在)
T2: free(0x7000的数据), free(0x7000节点) ← 25的物理节点被删
T3: 30(0x3000)->left = NULL
T4: 树结构: 25(原20的位置) -> right=30, 30->left=NULL

```

