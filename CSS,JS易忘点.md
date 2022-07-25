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

默认情况下的话，div是不生效onBlur(失焦事件)的，可以在div中加入tabIndex=-1 即可生效。





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
<input onKeyDown={(e)=>{
    if(e.key==='Enter'){
        Function()
    }
}}>
</input>
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

点击‘复制’，将想要的数据写入剪贴板

```typescript
<button onClick={()=>{
    navigator.clipboard.writeText('写入剪贴板的数据')
    	.then(()=>{alert('已复制到剪贴板')})
    	.catch(err=>{ alert(err) })
}}>
```



## 8.将时间戳转化为时间

```typescript

const timestampToTime = ( timestamp: string | number | Date ) => {
    const date = new Date( timestamp )
    //若时间戳是10位的话，上面需要*1000，否则会跑到1970年 new Date(timesstamp * 1000)
    const Y = date.getFullYear() + '-'
    const M = ( date.getMonth() + 1 < 10 ? '0' + ( date.getMonth() + 1 ) : date.getMonth() + 1 ) + '-'
    const D = date.getDate() + ' '
    const h = date.getHours() + ':'
    const m = date.getMinutes() + ':'
    const s = date.getSeconds()
    return Y + M + D + h + m + s;
  }
const Time = timestampToTime( time )
//但是！这里 如果传入的time是字符串的话，得到的全是Nan 因此需要将其进行转换 
//timestampToTime( parseInt( time ) )
```



## 9.摇摇晃晃框

```typescript
import { useRouter } from "next/router"
import React, { useState } from "react"
import { animated, config, useSpring } from "react-spring"
import styled from "styled-components"
import {
  usePasswordLoginMutation,
  usePhoneLoginMutation,
} from "../../src/generated/graphql"
import { useGlobalContext } from "../../utils/context/globalContext"
import { isPhone } from "../../utils/isPhone_isToken"
import { PasswordToken } from "./PasswordToken"

const RegisterLogin: React.FC<RegisterLoginProps> = ({
  password,
  phone,
  phoneToken,
  setPassword,
  setPhone,
  setPhoneToken,
  setStep,
}) => {
  const [agree, setAgree] = useState(true)
  const { errorsToNotices } = useGlobalContext()
  const [props, set] = useSpring(() => ({
    xys: [0, 0, 1],
    config: config.default,
  }))

  return (
    <All
      onMouseMove={({ clientX: x, clientY: y }) => set({ xys: calc(x, y) })}
      onMouseLeave={() => set({ xys: [0, 0, 1] })}
      style={{
        transform: props.xys.to(trans),
      }}
    >

    </All>
  )
}
export default RegisterLogin

interface RegisterLoginProps {
  setStep: React.Dispatch<React.SetStateAction<number>>
  phone: string
  setPhone: React.Dispatch<React.SetStateAction<string>>
  password: string
  setPassword: React.Dispatch<React.SetStateAction<string>>
  phoneToken: string
  setPhoneToken: React.Dispatch<React.SetStateAction<string>>
}
interface topProps {
  top: string
}
interface bkProps {
  background: string
  border: string
}

const calc = (x: number, y: number) => [
  -(y - window.innerHeight / 2) / 40,
  (x - window.innerWidth / 2) / 40,
  1,
]
const trans = (x: number, y: number, s: number) =>
  `perspective(600px) rotateX(${x}deg) rotateY(${y}deg) scale(${s})`

const All = styled(animated.div)`
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 862px;
  height: 646px;
  border-radius: 40px;
  border: 3px solid rgba(255, 255, 255, 0.4);
  background: rgba(255, 255, 255, 0.4);
  backdrop-filter: blur(25px);
  transform-style: preserve-3d;
  transition: all 0.5s ease-out;
  &:hover {
    box-shadow: 0 50px 80px rgba(0, 0, 0, 0.2);
  }
`
const H1 = styled.h1`
  margin-top: 144px;
  font-style: normal;
  font-weight: normal;
  font-size: 32px;
  line-height: 45px;
  color: #ffffff;
`
export const Input = styled.input<topProps>`
  margin-top: ${({ top }) => top};
  width: 400px;
  height: 40px;
  background: #ffffff;
  border: 1px solid #ffffff;
  box-sizing: border-box;
  border-radius: 4px;
  padding-left: 8px;
  outline: none;
`

const Accept = styled.div<topProps>`
  display: flex;
  align-items: center;
  column-gap: 8px;
  margin-top: ${({ top }) => top};
  width: 400px;
  height: 17px;
  font-size: 12px;
  line-height: 17px;
  color: #ffffff;
  p {
    color: #2e32f9;
  }
`
const Choice = styled.div<bkProps>`
  cursor: pointer;
  background: ${({ background }) => background};
  z-index: 2;
  width: 14px;
  height: 14px;
  border: ${({ border }) => border};
  box-sizing: border-box;
  border-radius: 2px;
  transition: all 0.1s ease-out;
  &:active {
    border: 7px solid #bbbbbb;
  }
`
const Btn = styled.div`
  margin-top: 64px;
  width: 200px;
  height: 48px;
  background: #ffffff;
  border-radius: 4px;
  display: flex;
  cursor: pointer;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  transition: all 0.5s ease-out;
  p {
    font-size: 20px;
    color: #2e32f9;
  }
  &:hover {
    box-shadow: 4px 4px 6px rgba(0, 0, 0, 0.25);
  }
  &:active {
    background: #9c9c9c;
    transition: all 0.1s ease-out;
  }
`
const Way = styled.p`
  cursor: pointer;
  margin-top: 16px;
  font-size: 14px;
  color: #ffffff;
`
const Alert = styled.p`
  position: absolute;
  color: #ec3710;
  font-size: 12px;
  right: 8px;
  bottom: 9px;
  line-height: 22px;
  transition: all 0.3s ease-in-out;
`

```



## 10.获取当前和24小时前的时间戳

```typescript
const nowTime = new Date().getTime().toString()//当前时间戳
const beforeTime = (new Date().getTime() - 60*60*1000*24).toString()//24小时前时间戳
                                           //由1毫秒算到24小时
```



## 11.可拉伸表格

首先通常的table格式

```typescript
<table>
	<thead>
    	<tr>
    		<th>列首</th>
    	</tr>
    </thead> 
	<tbody>
    	<tr>
    		<td>内容</td>
    	</tr>
    </tbody>
</table>
```

写一个<TH>组件，其中主要功能为：读取鼠标的横坐标，拉动到的位置。这样就可以算出拉了多少距离，再与原宽度相加减就可以得到新的宽度，由于th改变也会随之改变td，因此做到一个可拉伸的表格。

主要用的  ==拖拽事件==

```typescript
import React, { useState } from "react"
import styled from "styled-components"

export const TH: React.FC<THProps> = ({ title, index }) => {
  const [w, setW] = useState(title.length > 4 ? 200 : 100)
  return (
    <Th width={w}>
      {title}
      <SP
        id={`sp${index}`}
        draggable
        onDragEnd={(e) => {
          const Span = document.getElementById(`sp${index}`)
          const Left = Span.getBoundingClientRect().left /* 拿到span的x坐标 */
          /* e.clientX：鼠标到达的x坐标 Left会比正常是大1，所以减1 */
          setW(w + e.clientX - (Left - 1))
        }}
      >
        &nbsp;
      </SP>
    </Th>
  )
}
interface THProps {
  title: string
  index: number
}

const Th = styled.th<{ width?: number }>`
  position: relative;
  border-right: 1px solid #ccc;
  padding: 2px;
  width: ${({ width }) => (width ? width : "100px")};
  user-select: none;
  color: #333;
  font-size: 13px;
`
const SP = styled.span`
  position: absolute;
  cursor: ew-resize;
  height: 100%;
  right: 0px;
  top: 0px;
  width: 5px;
  &:active {
    width: 3px;
    background-color: #464545;
    height: 880px;
    box-sizing: border-box;
  }
`
export const TD = styled.td`
  border: 1px solid #ccc;
  width: 100px;
`
```

只设置表格的右边框，并在右边框处放置一个占位span，主要通过拉动span，来确定新的位置。



## 12.将时间戳格式化（“YYYY-MM-DD HH:mm:ss”）

```typescript
export const timeStampFormat = (timestamp: string) => {
  let timeStamp: number
  if (timestamp.length === 13) {
    timeStamp = new Date(parseInt(timestamp)).getTime()
  } else {
    timeStamp = new Date(timestamp).getTime()
  }
  const date = new Date(timeStamp)
  const Y = date.getFullYear() + "-"
  const M = (date.getMonth() + 1).toString().padStart(2, "0") + "-"
  const D = date.getDate().toString().padStart(2, "0") + " "
  const h = date.getHours().toString().padStart(2, "0") + ":"
  const m = date.getMinutes().toString().padStart(2, "0") + ":"
  const s = date.getSeconds().toString().padStart(2, "0")
  return Y + M + D + h + m + s
}

```



## 13.得到某年某月的天数

```typescript
const getDays = (year: number, month: number) => {
    const start = new Date(year, month - 1, 1)
    const end = new Date(year, month, 1)
    const days = timeDay.count(start, end)
    return days
  }
```



## 14.封装一个时间戳推算时间方法

```typescript
export const timeStampFormat = (timestamp: string) => {
  let timeStamp: number
  if (timestamp.length === 13) {
    timeStamp = new Date(parseInt(timestamp)).getTime()
  } else {
    timeStamp = new Date(timestamp).getTime()
  }
  const date = new Date(timeStamp)
  const Y = date.getFullYear() + "-"
  const M = (date.getMonth() + 1).toString().padStart(2, "0") + "-"
  const D = date.getDate().toString().padStart(2, "0") + " "
  const h = date.getHours().toString().padStart(2, "0") + ":"
  const m = date.getMinutes().toString().padStart(2, "0") + ":"
  const s = date.getSeconds().toString().padStart(2, "0")
  return Y + M + D + h + m + s
}
```



## 15.JS打开新的tab

```typescript
window.open(strUrl,strWindowName,[strWindowFeatures]);
```

- strUrl: 新窗口需要载入的url地址。
- strWindowName：新窗口的名字，通过这个名字我们可以获得新窗口的引用，容易重复，==如果我们希望每次打开新窗口都是一个全新的窗口，可以设置成关键字 “_blank”。==
- strWindowFeatures：新窗口的一些设置，比如是否显示菜单栏，是否可以滚动和缩放窗口大小等。

除了将窗口的名字设置为关键字 “_blank”，还可以在窗口设置中（即第三个位置）加入==location=no==，也可以达到打开全新窗口的目的。

**特殊**：当将窗口名字设置为关键字“_blank”时，需要有输入窗口设置，否则还是不会弹出全新独立窗口



## 16.使用console.time进行时间计算

这种方法在需要测试的开始位置写上`console.time`，并且括号内传一个字符串。在结束的位置使用`console.timeEnd`方法，并再次把字符串传入。

```typescript
console.time("funTime")
fun()
console.timeEnd("funTime")
```

## 17.手动useQuery

常见的useQuery是这样

```typescript
const [{data:moumouData,fetching}] = useMoumouQuery()
```

在进入页面的时候进行查询。而想要实现 在特定条件触发下来执行的话需要给他赋予一个方法名，在需要的时候调用它。

```typescript
const [{data:moumouData},execute] = useMoumouQuery({pause:true})
```

其中`execute`就是给它起的方法名。`pause:true`可以让它刚进入页面时的自动查询关闭，这样刚进入页面就不会进行查询。

## 18.上传文件

两种方法，

一种使用原生的input标签自带type：

```typescript
<input type='file' />
//可以通过使用label，将其和其他元素包在一起，将input隐藏，这样就能做到点击其他元素来上传文件
<label>
	<div>hallo</div>
	<input type='file' style={{display:'none'}} />
</label>
```

另一种使用react-dropzone：

```typescript
yarn add react-dropzone
import {useDropzone} from 'react-dropzone'
const {getRootProps, getInputProps, isDragActive} = useDropzone({onDrop})
<div {...getRootProps()}>
  <input {...getInputProps()} />
  {
    isDragActive ?
      <p>Drop the files here ...</p> :
      <p>Drag 'n' drop some files here, or click to select files</p>
  }
</div>
```

