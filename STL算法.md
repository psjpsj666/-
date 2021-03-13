# 算法

STL中的算法大致可以分为七类：

1.  不变序列算法

2.  变值算法

3.  删除算法

4.  变序算法

5.  排序算法

6.  有序区间算法

7.  数值算法

**大多重载的算法都是有两个版本的**

1.  用“==”判断元素是否相等，或用“\<”来比较大小。

2.  多出一个类型参数“Pred”和函数形参“Pred
    op”：通过表达式“op(x,y)”的返回值：true/false，来判断x是否“等于”y，或者x是否“小于”y。

如下面的有两个版本的min\_element：

iterator min_element(iterator first,iterator last); //根据“\<”判断大小

iterator min_element(iterator first,iterator last,Pred op); //根据op来判断

# 不变序列算法

-   该类算法不会修改算法所作用的容器或对象

-   适用于顺序容器和关联容器

-   时间复杂度都是O(n)

| 算法名称                | 功能                                                                           |
|-------------------------|--------------------------------------------------------------------------------|
| min                     | 求两个对象中较小的（可自定义比较器）                                           |
| max                     | 求两个对象中较大的（可自定义比较器）                                           |
| min_element             | 求区间中的最小值（可自定义比较器）                                             |
| max_element             | 求区间中的最大值（可自定义比较器）                                             |
| for_each                | 对区间中的每个元素都做某种操作                                                 |
| count                   | 计算区间中等于某值的元素个数                                                   |
| count_if                | 计算区间中符合某种条件的元素个数                                               |
| find                    | 在区间中查找等于某值的元素                                                     |
| find_if                 | 在区间中查找符合某条件的元素                                                   |
| find_end                | 在区间中查找另一个区间最后一次出现的位置（可自定义比较器）                     |
| find_first_of           | 在区间中查找第一个出现在另一个区间中的元素（可自定义比较器）                   |
| adjacent_find           | 在区间中寻找第一次出现连续两个相等元素的位置（可自定义比较器）                 |
| search                  | 在区间中查找另一个区间第一次出现的位置（可自定义比较器）                       |
| search_n                | 在区间中查找第一次出现等于某值的连续n个元素（可自定义比较器）                  |
| equal                   | 判断两区间是否相等（可自定义比较器）                                           |
| mismatch                | 逐个比较两个区间的元素，返回第一次发生不行的的两个元素的位置（可自定义比较器） |
| lexicographical_compare | 按字典序比较两个区间的大小（可自定义比较器）                                   |

**find:**

templaye\<class InIt,class T\>

InIt(InIt first,InIt last,const T&val);

//返回区间[first,last)中的迭代器i，使得\*i==val

**find\_if:**

template\<class InIt,clsss Pred\>

InIt find_if(InIt first,InIt last,Pred pr);

//返回区间[first,last)中的迭代器i，使得pr(\*i)==true

**for_each:**

template\<class InIt,class Fun\>

Fun for_each(InIt first,InIt last,Fun f);

//对[first,last)中的每个元素e，执行f(e)，要求f(e)不能改变e

**count:**

template\<class InIt,class T\>

size_t count(InIt first,InIt last,const T&val);

//计算[first,last)中等于val元素的个数(x==y为true算等于)

**count_if:**

template\<class InIt,class Pred\>

size_t count_if(InIt first,InIt last,Pred pr);

//计算[first,last)中符合pr(e)==true的元素e的个数

**min_element:**

template\<class FwdIt\>

FwdIt min_element(FwdIt first,FwdIt last);

//返回[first,last)中最小元素的迭代器，以“\<”作比较器

**最小值没有元素比它小，而不是它比别的不同元素都小**

因为即便a!=b,a\<b和b\>a有可能都不成立

**max_element:**

template\<class FwdIt\>

FwdIt max_element(FwdIt first, FwdIt last);

//返回[first,last)中最大元素（不小于任何其他元素）的迭代器，以“\<”作比较器

\#include\<iostream\>

\#include\<algorithm\>

using namespace std;

class A{

public:

int n;

A(int i):n(i){}

};

bool operator\<(const A &a1,const A&a2){

cout\<\<"\<called"\<\<endl;

if(a1.n==3 && a2.n==7){

return true;

}

return false;

}

int main(){

A aa[]={3,5,7,2,1};

cout\<\<min_element(aa,aa+5)-\>n\<\<endl;

cout\<\<max_element(aa,aa+5)-\>n\<\<endl;

return 0;

}

**输出：**

\<called

\<called

\<called

\<called

3

\<called

\<called

\<called

\<called

7

# 变值算法

此类算法会修改源区间或目标区间元素的值

**值被修改的那个区间，不可以是属于关联容器的**

| 算法名称        | 功能                                                               |
|-----------------|--------------------------------------------------------------------|
| for\_each       | 对区间中的每个元素都做某种操作                                     |
| **copy**        | **复制一个区间到别处**                                             |
| copy_backward   | 复制一个区间到别处，但目标区间是从后往前被修改的                   |
| transform       | 将一个区间的元素变形后拷贝到另一个区间                             |
| swap_ranges     | 交换两个区间内容                                                   |
| fill            | 用某个值填充区间                                                   |
| fill_n          | 用某个值替换区间中的n个元素                                        |
| generate        | 用某个操作的结果填充区间                                           |
| generate_n      | 用某个操作的结果替换区间中的n个元素                                |
| replace         | 将区间中的某个值替换为另一个值                                     |
| replace_if      | 将区间中符合某种条件的值替换成另一个值                             |
| replace_copy    | 将一个区间拷贝到另一个区间，拷贝时某个值要换成新值拷过去           |
| replace_copy_if | 将一个区间拷贝到另一个区间，拷贝时符合某个条件的值要换成新值拷过去 |

**transform:**

template\<class InIt,class OutIt,class Unop\>

OutIt transform(InIt first,InIt last,OutIt x,Unop uop);

//对[first,last)中的每个迭代器i,

1.  执行uop(\*i);并将结果依次放入从x开始的地方

2.  要求uop(\*i)不得改变\*i的值

本模板返回值是个迭代器，即x+(last-first)，x可以和first相等

\#include\<iostream\>

\#include\<vector\>

\#include\<numeric\>

\#include\<list\>

\#include\<iterator\>

\#include\<algorithm\>

using namespace std;

class CLessThen9{

public:

bool operator()(int n){return n\<9;}

};

void outputSquare(int value){cout\<\<value\*value\<\<" ";}

int calculateCube(int value){return value\*value\*value;}

int main(){

const int Size=10;

int a1[]={1,2,3,4,5,6,7,8,9,10};

int a2[]={100,2,8,1,50,3,8,9,10,2};

vector\<int\> v(a1,a1+Size);

ostream_iterator\<int\> output(cout," ");

random_shuffle(v.begin(),v.end()); //随机打乱数组

cout\<\<endl\<\<"1) ";

copy(v.begin(),v.end(),output);

copy(a2,a2+Size,v.begin()); //把a2的内容拷贝到v里面去，要求目标区间有充足的空间

cout\<\<endl\<\<"2) ";

cout\<\<count(v.begin(),v.end(),8);

cout\<\<endl\<\<"3) ";

cout\<\<count_if(v.begin(),v.end(),CLessThen9());

cout\<\<endl\<\<"4) ";

cout\<\<\*(min_element(v.begin(),v.end()));

cout\<\<endl\<\<"5) ";

cout\<\<\*(max_element(v.begin(),v.end()));

cout\<\<endl\<\<"6) ";

cout\<\<accumulate(v.begin(),v.end(),0); //求和

cout\<\<endl\<\<"7) ";

for_each(v.begin(),v.end(),outputSquare);

vector\<int\> cubes(Size);

transform(a1,a1+Size,cubes.begin(),calculateCube); //a1元素的立方放到cubes里面

cout\<\<endl\<\<"8) ";

copy(cubes.begin(),cubes.end(),output);

return 0;

}

**输出：**

1) 9 2 10 3 1 6 8 4 5 7

2) 2

3) 6

4) 1

5) 100

6) 193

7) 10000 4 64 1 2500 9 64 81 100 4

8) 1 8 27 64 125 216 343 512 729 1000

ostream_iterator\<int\> output(cout," ");

定义了一个ostream_iterator\<int\>对象，可以通过cout输出以“
”（空格）分隔的一个个整数

copy(v.begin(),v.end(),output);

导致v的内容在cout上输出

## copy函数模板（算法）

template\<class InIt,class OutIt\>

OutIt copy(InIt first,InIt last,OutIt x);

//本函数对每个在区间[0,last-first)中的N执行一次\*(x+N)=\*(first+N),返回x+N

//对于copy(v.begin(),v.end(),output);

//first和last的类型是vector\<int\>::const_iterator

//output的类型是ostream_iterator\<int\>

//copy的源代码

template\<class InputIterator, class OutputIterator\>

OutputIterator copy (InputIterator first, InputIterator last, OutputIterator
result)

{

while (first!=last) {

\*result = \*first;

\++result; ++first;

}

return result;

}

# 删除算法

删除一个容器里的某些元素

删除不会使容器里的元素减少

1.  将所有应该被删除的元素看作空位子

2.  用留下的元素从后往前移，一次去填空位子

3.  元素往前移后，它原来的位置也就算是空位子

4.  也应由后面的留下的元素来填上

5.  最后，没有被填上的空位子，维持其原来的值不变

6.  **删除算法不应作用于关联容器**

| 算法名称       | 功能                                                                           |
|----------------|--------------------------------------------------------------------------------|
| remove         | 删除区间中等于某个值的元素                                                     |
| remove_if      | 删除区间中满足某种条件的元素                                                   |
| remove_copy    | 拷贝区间到另一个区间，等于某个值的元素不拷贝                                   |
| remove_copy_if | 拷贝区间到另一个区间，符合某种条件的元素不拷贝                                 |
| unique         | 删除区间中连续相等的元素，只留下一个（可自定义比较器）                         |
| unique_copy    | 拷贝区间到另一个区间，连续相等的元素，只拷贝第一个到目标区间（可自定义比较器） |

算法复杂度都是O(n)的

**unique:**

template\<class Fwdlt\>

Fwdlt unique(Fwdlt first,Fwdlt last);

//用==比较是否相等

template\<class Fwdlt,class Pred\>

Fwdlt unique(Fwdlt first,Fwdlt last,Pred pr);

//用pr(x,y)=true说明x=y

//对[first,last)这个序列中连续相等的元素，只留下第一个

//返回值是迭代器，指向元素删除后的区间的最后一个元素的后面

int main(){

int a[5]={1,2,3,2,5};

int b[6]={1,2,3,2,5,6};

ostream_iterator\<int\> oit(cout,",");

int \*p=remove(a,a+5,2);

cout\<\<"1) ";copy(a,a+5,oit);

cout\<\<endl;

cout\<\<"2) "\<\<p-a\<\<endl;

vector\<int\> v(b,b+6);

remove(v.begin(),v.end(),2);

cout\<\<"3) ";copy(v.begin(),v.end(),oit);

cout\<\<endl;

cout\<\<"4) "\<\<v.size()\<\<endl;

return 0;

}

**输出：**

1) 1,3,5,2,5,

2) 3

3) 1,3,5,6,5,6,

4) 6

# 变序算法

1.  变序算法改变容器中元素的顺序

2.  但是不改变元素的值

3.  **变序算法不适用于关联容器**

4.  算法复杂度都是O(n)

| 算法名称          | 功能                                                               |
|-------------------|--------------------------------------------------------------------|
| reverse           | 颠倒区间的前后次序                                                 |
| reverse_copy      | 把一个区间颠倒后的结果拷贝到另一个区间，源区间不变                 |
| rotate            | 将区间进行循环左移                                                 |
| rotate_copy       | 将区间以首尾相接的形式进行旋转后的结果拷贝到另一个区间，源区间不变 |
| next\_permutation | 将区间改为下一个排列（可自定义比较器）                             |
| prev_permutation  | 将区间改为上一个排列（可自定义比较器）                             |
| random_shuffle    | 随机打乱区间内的元素的顺序                                         |
| partition         | 把区间内满足某个条件的元素移到前面，不满足该条件的移到后面         |

**stable_patition:**

1.  把区间内满足某个条件的元素移到前面，不满足该条件的移到后面

2.  对这两部分元素，分别保持它们原来的先后次序不变

**random_shuffle:**

template\<class Ranlt\>

void random_shuffle(Ranlt first,Ranlt last);

//随机打乱[first,last)中的元素，适用于**能随机访问的容器**

**reverse:**

template\<class Bidlt\>

void reverse(Bidlt first,Bidlt last);

//颠倒区间[first,last)顺序

**next_permutation:**

template\<class InIt\>

bool next_permutation(InIt first,InIt last);

//求下一个排列

\#include\<iostream\>

\#include\<string\>

\#include\<algorithm\>

using namespace std;

int main(){

string str="231";

char szStr[]="324";

while(next_permutation(str.begin(),str.end())){

cout\<\<str\<\<endl;

}

cout\<\<"\*\*\*\*"\<\<endl;

while(next_permutation(szStr,szStr+3)){

cout\<\<szStr\<\<endl;

}

sort(str.begin(),str.end());

cout\<\<"\*\*\*\*"\<\<endl;

while(next_permutation(str.begin(),str.end()))

{

cout\<\<str\<\<endl;

}

return 0;

}

**输出：**

312

321

\*\*\*\*

342

423

432

\*\*\*\*

132

213

231

312

321

# 排序算法

1.  比前面的变序算法复杂度更高，一般是O(nlog(n))

2.  排序算法需要随机访问迭代器的支持

3.  **不适用于关联容器和list**

| 算法名称          | 功能                                                                                                            |
|-------------------|-----------------------------------------------------------------------------------------------------------------|
| sort              | 将区间从小到大排序（可自定义比较器）                                                                            |
| stable_sort       | 将区间从小到大排序，并保持相等元素间的相对次序（可自定义比较器）                                                |
| partial_sort      | 将区间部分排序，直到最小的n个元素就位（可自定义比较器）                                                         |
| partial_sort_copy | 将区间前n个元素的排序结果拷贝到别处，源区间不变（可自定义比较器）                                               |
| nth_element       | 对区间部分排序，使得第n小的元素（n从0开始算）就位，而且比它小的都在它前面，比它大的都在它后面（可自定义比较器） |
| make\_heap        | 是区间成为一个“堆”（可自定义比较器）                                                                            |
| push_heap         | 将元素加入一个是“堆”区间（可自定义比较器）                                                                      |
| pop_heap          | 从“堆”区间删除堆顶元素（可自定义比较器）                                                                        |
| sort_heap         | 将一个“堆”区间进行排序，排序结束后，该区间就是普通的有序区间，不再是“堆”了（可自定义比较器）                    |

**sort(快速排序)：**

template\<class Ranlt\>

void sort(Ranlt first,Ranlt last);

//按升序排序

//判断x是否应比y靠前，就看x\<y是否为true

template\<class Ranlt,class Pred\>

coid sort(Ranlt first,Ranlt last,Pred pr);

//按升序排序

//判断x是否应比y靠前，就看pr(x,y)是否为true

1.  sort实际上是快速排序，时间复杂度O(nlog(n))

    (平均性能最优，但是最坏的情况下，性能可能非常差)

2.  如果要保证“最坏情况下”的性能，那么可以使用stable_sort

3.  stable_sort实际上是归并排序，特点是能保持相等元素之间的先后次序

4.  在有足够存储空间的情况下，复杂度为nlog(n)，否则复杂度为n\*log(n)\*log(n)

5.  stable_sort和sort用法一样

list不能使用排序算法，要使用list::sort

# 有序区间算法

-   需要所操作的区间是已经从小到大排好序的

-   需要随机访问迭代器的支持

-   **有序区间算法不能用于关联容器和list**

| 算法名称                 | 功能                                         |
|--------------------------|----------------------------------------------|
| binary_search            | 判断区间中是否包含某个元素                   |
| includes                 | 判断是否一个区间的每个元素，都在另一个区间内 |
| lower_bound              | 查找最后一个不小于某值的元素的位置           |
| upper_bound              | 查找第一个大于某值元素的位置                 |
| equal_range              | 同时获取lower_bound和upper_bound             |
| merge                    | 合并有序区间到第三个区间                     |
| set\_union               | 将两个有序区间的并拷贝到第三个区间           |
| set_intersection         | 将两个有序区间的交拷贝到第三个区间           |
| set_difference           | 将两个有序区间的差拷贝到第三个区间           |
| set_symmetric_difference | 将两个有序区间的对称差拷贝到第三个区间       |
| inplace_merge            | 将两个连续的有序区间原地合并为一个有序区间   |

**binary\_search:**

折半查找，要求容器已经有序且支持随机访问迭代器，返回是否找到

template\<class Fwdlt,class T\>

bool binary_search(Fwdlt first,Fwdlt last,const T&val);

//比较两个元素x,y大小时，看x\<y

template\<class Fwdlt,class T,class Pred\>

bool binary_search(Fwdlt first,Fwdlt last,const T&val,Pred pr);

//比较两个元素x,y大小时，若pr(x,y)为true，则认为x\<y

**lower_bound:**

template\<class Fwdlt,class T\>

Fwdlt lower_bound(Fwdlt first,Fwdlt last,const T&val);

//要求[first,last)是有序的

//查找[first,last)中的，最大的位置Fwdlt,使得[first,Fwdlt)中所有的元素都比val小

**upper_bound:**

template\<class Fwdlt,class T\>

Fwdlt upper_bound(Fwdlt first,Fwdlt last,const T&val);

//要求[first,last)是有序的

//查找[first,last)中的，最大的位置Fwdlt,使得[Fwdlt,last)中所有的元素都比val大

**equal_range:**

template\<class Fwdlt,class T\>

pair\<Fwdlt,Fwdlt\> equal_range(Fwdlt first,Fwdlt last,const T&val);

//要求[first,last)是有序的

//返回值是一个pair，假设为p,则：

/\*[first,p.first)中的元素都比val小

[p.second,last)中的元素都比val大

p.first就是lower_bound的结果

p.second就是upper_bound的结果

\*/

**merge:**

template\<class InIt1,class InIt2,class Outlt\>

Outlt merge(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt x);

//用\<作比较器

template\<class InIt1,class InIt2,class Outlt,class Pred\>

Outlt merge(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt x,Pred pr);

//用pr作比较器

//把[first1,last1),[first2,last2)两个升序序列合并，形成第三个升序序列，第三个升序序列以x开头

**inlcudes:**

template\<class InIt1,class InIt2\>

bool includes(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2);

//用\<作比较器

template\<class InIt1,class InIt2,class Pred\>

bool includes(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Pred pr);

//判断[first2,last2)中的每一个元素，是否都在[first1,last1)中

//用pr作比较器，p(x,y)==true说明x,y相等

**set_difference:**

template\<class InIt1,class InIt2,class Outlt\>

Outlt set_difference(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt x);

template\<class InIt1,class InIt2,class Outlt,class Pred\>

Outlt set_difference(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt
x,Pred pr);

//求出[first1,last1)中，不在[first2,last2)中的元素，放到从x开始的地方

//如果[first1,last1)里有多个相等元素不在[first2,last2)中，则这多个元素也都会被放入x代表的目标区间里

**set_intersection:**

template\<class InIt1,class InIt2,class Outlt\>

Outlt set_intersection(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt
x);

template\<class InIt1,class InIt2,class Outlt,class Pred\>

Outlt set_intersection(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt
x,Pred pr);

//求出[first1,last1)和[first2,last2)中共有的元素，放到从x开始的地方

//如果某个元素e在[first1,last1)里出现n1次，在[first2,last2)中出现n2次，则该元素在目标区间里出现min(n1,n2)次

**set_symmetric_difference:**

template\<class InIt1,class InIt2,class Outlt\>

Outlt set_symmetric_difference(InIt1 first1,InIt1 last1,InIt2 first2,InIt2
last2,Outlt x);

template\<class InIt1,class InIt2,class Outlt,class Pred\>

Outlt set_symmetric_difference(InIt1 first1,InIt1 last1,InIt2 first2,InIt2
last2,Outlt x,Pred pr);

//把两个区间里相互不在两一个区间里的元素放入x开始的地方

**set_union:**

template\<class InIt1,class InIt2,class Outlt\>

Outlt set_union(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt x);

//用\<比较大小

template\<class InIt1,class InIt2,class Outlt,class Pred\>

Outlt set_union(InIt1 first1,InIt1 last1,InIt2 first2,InIt2 last2,Outlt x,Pred
pr);

//用pr比较大小

//求两个区间的并，放到以x开始的位置

//如果某个元素e在[first1,last1)里出现n1次，在[first2,last2)中出现n2次，则该元素在目标区间里出现max(n1,n2)次

**bitset**

template\<size_t N\>

class bitset

{

.....

};

实际使用的时候，N是个整型常数

如：bitset\<40\>bst;

bst是一个由40为组成的对象

用bitset函数可以方便地访问任何一位
