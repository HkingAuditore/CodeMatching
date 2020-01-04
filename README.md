# CodeMatching
## 哈希表
 哈希表生成文件存储于HashFile，你可以手写.hash文件，也可以调用 `GenerateHashTable_KEYBOARD(int _size)` 方法通过输入的方式生成哈希表。
 ### 哈希表处理
 哈希表头文件的API有：
* `SaveHash(const HashTable *_hash, char *_fileName);`  
  将哈希表*_hash* 以 *_fileName.hash* 的名称存放于哈希表默认存放目录（默认` /HashFile `）。
* `ReadHash(char *_fileName)`  
  读取 *_fileName.hash* 并将之转换为哈希表文件返回。
* `GenerateHashTable_KEYBOARD(int _size)`  
  通过键盘输入 *_size* 数量的关键字，并将之转换为哈希表。
* `WriteHashTable(HashTable *_hash)`  
  读取 *_fileName.hash* 并将之转换为哈希表文件返回。
* `HashSearch(char *_target, HashTable *_hash)`  
  在哈希表 *_hash* 中寻找关键词 *_target* ，若找到返回其在哈希表中的存储编号，否则返回-1。
 ### 哈希表文件.hash格式
形如  
`[Size，NumOfNodes，{position,conflict,_hashKey,_keyWord,_type}，{ position,conflict,_hashKey,_keyWord,_type}，...]`  
#### 字段含义
* Size 表示哈希表节点空间数，
* NumOfNodes表示哈希表有效节点数
* position表示节点存储位置
* conflict表示节点冲突次数
* _hashKey表示关键字的HashKey
* _keyWord表示节点对应的关键字
* _type表示关键字的类型。  
***
## 匹配
 要进行匹配的文件放在`/CodeFile`。默认后缀是`.c`。
 ### 自带关键字
| 英文名 | Data types | Qualifiers | User-defined | Storage Classes | Loop | Decision | Jump | Derived | Function | Others |  
| :-- | :-: | :--: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| 中文名 | 数据类型 | 类型修饰 | 用户自定义类型 | 作用域修饰 | 循环 | 选择 | 跳转 | 派生 | 方法 | 其他 |
| 对应序号 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| 包含关键字 | int<br/>char<br/>float<br/>double |signed<br/>unsigned<br/>short<br/>long |typedef<br/>enum |auto<br/>extern<br/>register<br/>static| for<br/>while<br/>do | if<br/>else<br/>switch<br/>case<br/>default | goto<br/>continue<br/>break | struct<br/>union | void<br/>return | const<br/>volatile<br/>sizeof |
           
### 匹配算法
按照关键字频率生成向量，求两个向量的广义余弦。  
![](http://latex.codecogs.com/gif.latex?\\S(X_i,X_j)=\frac{X^T_iX_j}{|X_i|\cdot|X_j|})  
再求二者的几何距离以提高匹配准确率  
![](http://latex.codecogs.com/gif.latex?\\D(X_i,X_j)=|X_i-X_j|=\sqrt{({X_i-X_j})^T({X_i-X_j})})  


