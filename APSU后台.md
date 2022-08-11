# React全局队列提示弹窗

它像土司一样，一片一片从面包机弹出来，给这个队列叫`ToastList`。

首先写一个组件定义这些“土司”的样式和规则。

`Toast.tsx`:

```react
import { NextPage } from "next"
import React, { useCallback, useEffect, useState } from "react"
import styled from "styled-components"

export const Toast: NextPage<ToastProp> = ({ toastList, setList }) => {
  const [ifDel, setIfDel] = useState(false)
  const deleteToast = useCallback(
    (id: number) => {
      const toastListItem = toastList.filter((e: { id: number }) => e.id !== id)
      setList(toastListItem)
    },
    [toastList, setList]
  )

  useEffect(() => {
    const interval = setInterval(() => {
      if (toastList.length) {
        deleteToast(toastList[0].id)
      }
    }, 2500)
    if (ifDel) {
      clearInterval(interval)
    }
    return () => {
      clearInterval(interval)
    }
  }, [toastList, deleteToast, ifDel])
  return (
    <All>
      {toastList.map((toast, i) => (
        <Box
          onMouseEnter={() => {
            setIfDel(true)
          }}
          onMouseLeave={() => {
            setIfDel(false)
          }}
          key={i}
          style={{ backgroundColor: toast.backgroundColor }}
        >
          <X onClick={() => deleteToast(toast.id)}>X</X>
          <div style={{ position: "fixed" }}>
            <P>{toast.title}</P>
            <PP>{toast.description}</PP>
          </div>
        </Box>
      ))}
    </All>
  )
}

interface ToastProp {
  setList: React.Dispatch<
    React.SetStateAction<
      {
        id: number
        title: string
        description: string
        backgroundColor: string
      }[]
    >
  >
  toastList: {
    id: number
    title: string
    description: string
    backgroundColor: string
  }[]
}
const All = styled.div`
  font-size: 14px;
  position: fixed;
  z-index: 10;
  bottom: 1rem;
  right: 1rem;
`
const Box = styled.div`
  @keyframes toast-in-right {
    0% {
      transform: translateX(100%);
    }
    100% {
      transform: translateX(0%);
    }
  }
  margin-bottom: 1rem;
  border-radius: 4px;
  box-shadow: 0 0 10px #999;
  color: #000;
  opacity: 0.9;
  animation: toast-in-right 1s;
  transition: all 0.3s ease-in-out;
  height: 50px;
  width: 365px;
  color: #fff;
  padding: 20px 15px 10px 10px;

  &:hover {
    box-shadow: 0 0 12px #fff;
    opacity: 1;
  }
`
const X = styled.button`
  float: right;
  background: none;
  border: none;
  color: #fff;
  opacity: 0.8;
  cursor: pointer;
`
const P = styled.p`
  font-weight: 700;
  font-size: 16px;
  text-align: left;
  margin-top: 0;
  margin-bottom: 6px;
  width: 300px;
  height: 18px;
`
const PP = styled.p`
  margin: 0;
  text-align: left;
`

```

这里我接收了两个参数，一个是==存放提示框的信息的数组==，另一个是==更改该数组的方法==，其实就是在一个useState中。该组件用于展示和修改这个数组，所以需要传入。那么应该从哪里传入呢，一般是在一个全局的位置，例如一个我的网站有导航栏是全局的。我的导航栏组件是这样

```react
import dynamic from "next/dynamic"
import { useGlobalContext } from "../../utils/context/globalContext"
import { Toast } from "../Toast/Toast"

const NossrNavBar = dynamic(() => import("./Navbar"), { ssr: false })
//NossrNavBar 导航栏的样式等等就不放出来了

export const Layout = ({ children }) => {//参数传入页面的内容
  const { toastList, setList } = useGlobalContext()//这个位置是从“状态管理文件”拿出来
  return (
    <>
      <NossrNavBar />        //展示页面的导航栏
      <main>{children}</main>//展示每个页面的内容
      <Toast toastList={toastList} setList={setList} />//这里就是我们的消息提示组件
    </>
  )
}
```

欸嘿，那么接下来就是讲到我们的“状态管理文件”，`globalContext.tsx`：

这里使用到的hook是useContext：

- `useContext`就是接收一个`context`对象，并返回该`context`的当前值。当前的`context`的当前值。当前的 `context` 值由上层组件中距离当前组件最近的 `<MyContext.Provider>` 的 `value prop` 决定。
- 当组件上层最近的 `<MyContext.Provider>` 更新时，该`Hook` 会触发重渲染，并使用最新传递给 `provider` 的 `context value` 值。

摘自：https://juejin.cn/post/7028160551079395365

用简单的话总结就是：==爷爷给孙子的东西，没必要一定经过父亲，用到useContext就可以很好的解决这个问题==。

```tsx
import {
  createContext,
  Dispatch,
  ReactElement,
  SetStateAction,
  useContext,
  useState,
} from "react"
import { FieldError } from "../../src/generated/graphql"

type Props = {
  children: ReactElement | ReactElement[]
}
interface globalContextType {  //定义我需要的类型
  leftMarkPoint: number
  changeLeftMarkPoint: (args: number) => void
  toastList: {
    id: number
    title: string
    description: string
    backgroundColor: string
  }[]
  setList: Dispatch<
    SetStateAction<
      {
        id: number
        title: string
        description: string
        backgroundColor: string
      }[]
    >
  >
  addNotice: (
    type: "success" | "danger" | "info" | "warning",
    title: string,
    content: string
  ) => void
  errorsToNotices: (errors: FieldError[]) => void
}

export const globalContextDefaultValues: globalContextType = {//初始化状态
  leftMarkPoint: 0,
  changeLeftMarkPoint: (args: number) => {},
  toastList: [],
  setList: () => {},
  addNotice: (
    type: "success" | "danger" | "info" | "warning",
    title: string,
    content: string
  ) => {},
  errorsToNotices: (errors: FieldError[]) => {},
}

const GlobalContext = createContext<globalContextType>(
  globalContextDefaultValues
)//建立一个context对象，类型为上方定义的类型，内容为上方定义的初始化状态

export const useGlobalContext = () => {//export供给页面调用useGlobalContext就可以拿到context的值
  return useContext(GlobalContext)
}//将我们的context对象交给useContext

export const GlobalProvider = ({ children }: Props) => { //定义Context.Provider，在下面讲解
  const [leftMarkPoint, setLeftMarkPoint] = useState<number>(0)
  const changeLeftMarkPoint = (args: number) => setLeftMarkPoint(args)
  const [toastList, setList] = useState<
    {
      id: number
      title: string
      description: string
      backgroundColor: string
    }[]
  >([])

  let toastProperties = {
    id: 0,
    title: "",
    description: "",
    backgroundColor: "",
  }

  const addNotice = (
    type: "success" | "danger" | "info" | "warning",
    title: string,
    content: string
  ) => {  //定义我们自己想要的方法
    switch (type) {
      case "success":
        toastProperties = {
          id: toastList.length + 1,
          title,
          description: content,
          backgroundColor: "#5cb85c",
        }
        break
      case "danger":
        toastProperties = {
          id: toastList.length + 1,
          title,
          description: content,
          backgroundColor: "#d9534f",
        }
        break
      case "info":
        toastProperties = {
          id: toastList.length + 1,
          title,
          description: content,
          backgroundColor: "#5bc0de",
        }
        break
      case "warning":
        toastProperties = {
          id: toastList.length + 1,
          title,
          description: content,
          backgroundColor: "#f0ad4e",
        }
        break
      default:
        toastProperties = {
          id: 0,
          title: "",
          description: "",
          backgroundColor: "",
        }
    }
    setList([...toastList, toastProperties]) //改变toastList
  }
  const errorsToNotices = (errors: FieldError[]) => {//定义我们自己想要的方法
    if (errors[0].message === "goReg") {
      addNotice("danger", errors[0].field, errors[0].message)
    } else {
      addNotice("danger", errors[0].field, errors[0].message)
    }
  }

  const value = {
    leftMarkPoint,
    changeLeftMarkPoint,
    toastList,
    setList,//操作toastList的方法  也就是会改变下方value
    addNotice,//供其他页面调用的 方法
    errorsToNotices,//供其他页面调用的 方法
  }
  return (
    <>
      <GlobalContext.Provider value={value}>{children}</GlobalContext.Provider>
    </>
  )
}

```

React文档中介绍：

`<MyContext.Provider value={/* 某个值 */}>`

每个 **Context **对象都会返回一个 **Provider React** 组件，它允许消费组件订阅 context 的变化。

**Provider**接收一个 `value` 属性，==传递给消费组件==。一个**Provider**可以和多个消费组件有对应关系。多个 Provider 也可以嵌套使用，里层的会覆盖外层的数据。

当 **Provider**的 `value` 值发生变化时，它内部的所有消费组件都会重新渲染。从 Provider 到其内部 consumer（消费者） 组件（包括 [.contextType](https://zh-hans.reactjs.org/docs/context.html#classcontexttype) 和 [useContext](https://zh-hans.reactjs.org/docs/hooks-reference.html#usecontext)）的传播不受制于 `shouldComponentUpdate` 函数，因此当消费者组件在其祖先组件跳过更新的情况下也能更新。



所以在上部分代码中，定义的Provider React组件，我们需要把它放到全局中去。app.tsx中:

```react
const MyApp = ({ Component, pageProps }: AppProps)=>{
    <GlobalProvider>
        <Head>...</Head>
        <Layout> //这里就是我第二个代码块的导航栏组件了，里面引用了context对象的toastList和setList
        	<Component {...pageProps} />
        </Layout>
    </GlobalProvider>
}
```

然后在其他页面调用context中的我们写的方法，就会最终改变我们toastList的值，那么根据上面的描述，==当 **Provider**的 `value` 值发生变化时，它内部的所有消费组件都会重新渲染==。例：

```react
import { useGlobalContext } from "...../globalContext"
const { addNotice, errorsToNotices } = useGlobalContext()//就可以使用了
addNotice("success", "创建成功", "创建成功")
errorsToNotices(errors)
```

