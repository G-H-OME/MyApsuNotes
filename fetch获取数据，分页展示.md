# 前言

记录：从网址获取json数据，将数据展示在页面，实现分页(封装的组件就不写出来了)

（我这里好像写得有点小麻烦）

# fetch

首先定义三个量：(数据很多，不能一口气全部展示出来，所以使用分页)

==allDataRef 获取的总数据==

==article 展示数组==

==nowDataRef 每次添加到展示数组的数据==

由于分页，接下来定义 每一页有多少条数据（const itemsNum = 10）表示每页10条。

页数（let page = useRef( 0 )）。

以及nowDataRef的范围（let offSet = useRef( page.current * itemsNum )

  let last = useRef( ( page.current + 1 ) * itemsNum )）

```typescript
let allDataRef = useRef( [] )
useEffect( () => {
    async function get() {
      let url = 'https://my-json-server.typicode.com/G-H-OME/test_json/posts'
      let response = JSON.parse( await ( await fetch( url ) ).text() )//基操
      allDataRef.current = response
        //在页面初始化的时候，从网址获取总数据（allDataRef）
      nowDataRef.current = allDataRef.current.filter( ( item, index ) => {
        if ( offSet.current <= index && index < last.current ) {
            return item
        }
      } )
      setArticle( [...article, ...nowDataRef.current] )
    }
    get()
  }, [] )
```

# JSONPlaceholder

使用JSONPlaceholder来创建一个测试API：我的大概是这样子

```json
[
  {
    "albumId": 1,
    "id": 1,
    "title": "accusamus beatae ad facilis cum similique qui sunt",
    "url": "https://via.placeholder.com/600/92c952",
    "thumbnailUrl": "https://via.placeholder.com/150/92c952"
  },
  {
    "albumId": 1,
    "id": 2,
    "title": "reprehenderit est deserunt velit ipsam",
    "url": "https://via.placeholder.com/600/771796",
    "thumbnailUrl": "https://via.placeholder.com/150/771796"
  }
  .....
]
```

# 展示

用styled-components定义一些需要的元素

```typescript
const Post = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  column-gap: 24px;
  row-gap: 10px;
`
const More = styled.button`
  width: 100px;
  height: 50px;
  background-color: #FFFFFF;
  border: #FFFFFF;
`
```

接下来看逻辑

```typescript
<Post>
  {!article ? 'nothing' : (
     <Post>
       {article.map( ( item: { path: string, thumbnailUrl: string; id: string; title: string; } ) => {//对展示数组article进行遍历
        return (
           <Service onClick={() => {//Service是自己定义的组件，展示文章，可点击跳转
              router.push( item.path )
           }} key={item.id} img={item.thumbnailUrl} title={item.id} content={item.title}></Service>
                )
              } )}
            </Post>
          )}
       <More onClick={() => {//点击“查看更多”后，
         page.current = page.current + 1//page+1
         offSet.current = page.current * itemsNum//范围从0-9变成10-19（数组下标从
         last.current = ( page.current + 1 ) * itemsNum              //0开始）
         nowDataRef.current = allDataRef.current.filter( ( item, index ) => {
         if ( offSet.current <= index && index < last.current ) {
            return item
           }
         } )
          setArticle( [...article, ...nowDataRef.current] )
         }}>加载更多 {'>'}</More>
        </Post>
```

==注意useRef和useState的使用区别==，useRef可以在拿到新数据的同时**不会**去刷新页面。

（第二天）突然记起来，在没有更多数据了的时候，“加载更多”应该消失掉，所以再给个条件

```typescript
{article.length === allDataRef.current.length ? '' : (//如果展示长度与总长度一样
            <More onClick={() => {
              page.current = page.current + 1
              offSet.current = page.current * itemsNum
              last.current = ( page.current + 1 ) * itemsNum
              nowDataRef.current = allDataRef.current.filter( ( item, index ) => {
                if ( offSet.current <= index && index < last.current ) {
                  return item
                }
              } )
              setArticle( [...article, ...nowDataRef.current] )
            }}>加载更多 {'>'}</More>
          )}
```

