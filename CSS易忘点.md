# CSS易忘点

## 1.p标签中，英文会将不包含空格、换行的连续文本认为是一个词，所以在默认情况下不换行

解决方法：

```javascript
p{

    word-wrap:break-word
    /*或者是下面一种方法让单词强制换行*/
    /*
    word-break: break-all;
    */
}
```



## 2.css 文本超出就隐藏并且显示省略号

### 在只有一行内容的时候：

```javascript
overflow:hidden; //超出的文本隐藏
text-overflow:ellipsis; //溢出用省略号显示
white-space:nowrap; //溢出不换行
```

### 在多行内容的时候：

```javascript
overflow: hidden;
text-overflow: ellipsis;
display:-webkit-box; //作为弹性伸缩盒子模型显示。
-webkit-box-orient:vertical; //设置伸缩盒子的子元素排列方式--从上到下垂直排列
-webkit-line-clamp:2; //显示的行
```



## 3.==div不生效onBlur( )==

默认情况下的话，div是不生效onBlur的，可以在div中加入tabIndex=-1 即可生效。





## 4.flex横向布局无法换行

在flex布局中，如果是默认横向布局，是无法换行的，因为里面的每个flex项目都会占满整个高度。如果想要换行必须加上

```typescript
flex-wrap:wrap;
```



## 5.弹出div，聚焦于它

首先可以给它一个id

```typescript
<div id={user.id}> </div>
```

利用DOM操作，在执行操作的时候，聚焦于它

```typescript
<button onClick={()=>{
    const DIV = document.getElementById( `${user.id}` )
    DIV.focus()
}}>拔ten</button>
```



## 6.回车事件

```typescript
onKeyDown={(e)=>{
    if(e.key==='Enter'){
        Function()
    }
}}
```



## 7.在 Typescript 中，获得textarea的dom节点，并选中它的文本，复制到剪切板

在JavaScript中，这个不会很难，但是在ts中，需要多一个类型的定义as HTMLInputElement

否则select( ) 选中文本会失败。

```typescript
<textarea id="input">123</textarea>
const copyText = ()=>{
    let input = document.getElementById("input") as HTMLInputElement;
    input.select()
}
```

写到这里发现有点不太对劲。因为接下来的操作是将textarea的文本放入剪贴板中，

```typescript
document.execCommand("copy")
```

但是！！！==execCommand现在被弃用了==。



### 新的方案 使用剪贴板API

```typescript
const copyText = async(text:string)=>{
    await navigator.clipboard.writeText(text)//写入粘贴板
    await navigator.clipboard.readText()//读取粘贴板
}
```















