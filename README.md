# CodeMatching
## 哈希表
 哈希表生成文件存储于HashFile，你可以手写.hash文件，也可以调用 `GenerateHashTable_KEYBOARD(int _size)` 函数通过输入的方式生成哈希表。
 ### 哈希表文件.hash格式
形如  
`[Size[^哈希表节点空间数]，NumOfNodes[^哈希表有效节点数]，{position[^节点存储位置],conflict[^节点冲突次数],_hashKey[^关键字的HashKey],_keyWord[^节点对应的关键字],_type[^关键字的类型]}，{ position[^节点存储位置],conflict[^节点冲突次数],_hashKey[^关键字的HashKey],_keyWord[^节点对应的关键字],_type[^关键字的类型]}，...]`
***


