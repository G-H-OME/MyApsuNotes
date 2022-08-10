# React-force-graph-2d

先建立一个.js(.ts)文件导入`reactForceGraph2d`：

```typescript
import reactForceGraph2d from "react-force-graph-2d"
export default reactForceGraph2d
```

在需要导入的页面中动态引用：

```typescript
const NoSSRForceGraph = dynamic(
    () => import("../../../components/PagePart/NoSSRForceGraph"),
    { ssr: false }
  )
```

```typescript
<NoSSRForceGraph
   width={1920}
   height={500}
   backgroundColor='#ffffff'
   graphData={{ nodes, links }}   //节点和连线 nodes links是重点。
   nodeLabel={"id"}
   linkDirectionalArrowLength={3} //连线上箭头大小
   nodeCanvasObject={(node: newNode, ctx) => { //newNode是自己定的类型type newNode = {...}
   //自定义node节点样式，nodePaint是自己写的节点样式方法 getColor是自己写的选择颜色方法
   nodePaint(ctx, getColor(node.type), node.type, node.x, node.y)
   ctx.fillText(`${node.name}`, node.x, node.y + 10)
   ctx.textAlign = "center"
   ctx.font = "normal 4px sans-serif"
   }}
/>
```

nodePaint：

```typescript
const nodePaint = (
  ctx: CanvasRenderingContext2D,//固定的 上下文
  color: string,
  type?: string,
  x?: number,
  y?: number
) => {
  ctx.fillStyle = color //把节点的颜色赋为传进来的color
  const num = //自定条件，通过type赋予不同数字，用于在下方数组中挑选不同颜色
    type === "operation" || type === "itemSupplier" || type === "distribution"
      ? 0
      : type === "buffer"
      ? 1
      : type === "resource"
      ? 2
      : type === "create"
      ? 3
      : 4
  [
    () => {
      ctx.fillRect(x - 7, y - 3, 14, 7)
    },
    () => {
      ctx.beginPath()
      ctx.moveTo(x, y - 4)
      ctx.lineTo(x - 5, y + 5)
      ctx.lineTo(x + 5, y + 5)
      ctx.fill()
    },
    () => {
      ctx.beginPath()
      ctx.arc(x, y, 5, 0, 2 * Math.PI, false)
      ctx.fill()
    },
    () => {
      ctx.beginPath()
      ctx.moveTo(x, y - 8)
      ctx.lineTo(x - 4, y)
      ctx.lineTo(x, y + 8)
      ctx.lineTo(x + 4, y)
      ctx.fill()
    },
    () => {
      ctx.beginPath()
      ctx.moveTo(x, y - 6)
      ctx.lineTo(x - 7, y + 7)
      ctx.lineTo(x + 7, y + 7)
      ctx.fill()
    },
  ][num]()
}
```

getColor：

```typescript
const getColor = (type: string) => {
  switch (type) {
    case "operation":
      return "#1f77b4"
    case "itemSupplier":
      return "#1f77b4"
    case "distribution":
      return "#1f77b4"
    case "buffer":
      return "#2ca02c"
    case "resource":
      return "#ff7c3f"
    case "create":
      return "#eb37b5"
    case "product":
      return "#FF4C4C"
  }
}
```

自己封装了方法来将nodes和links填满以及它们之间联系。这个的话得根据当下的需求写逻辑了。



# React-quill

React-Quill 是Antd推荐使用的富文本编辑器

引用：

```typescript
const QuillNoSSRWrapper = dynamic(import("react-quill"), {
  ssr: false,
  loading: () => <p>Loading ...</p>,
})
```

用例：（我曾经的代码）

```typescript
<QuillNoSSRWrapper
            style={{ height: "28vw", position: "absolute", top: "2.08vw" }}
            modules={modules}
            formats={formats}
            theme='snow'
            value={
              value || //const [value,setValue] = useState()
              '<h3>二级标题(<span style="color: rgb(230, 0, 0);">使用H3标签</span>)</h3><p>内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容(<span style="color: rgb(230, 0, 0);">内容直接输入不需要标签</span>)</p><p>内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容。(<span style="color: rgb(230, 0, 0);">输入任意字符即可在上方内容显示</span>)</p>'
            }
            onChange={setValue}
          />
```

讲解一下：

**modules**：是对编辑器功能的配置，比如想要有控制字号的功能，加粗的功能等等

```typescript
const modules = {
    toolbar: [
      ["bold", "italic", "underline", "strike"],
      ["blockquote", "code-block"],
      [{ header: 1 }, { header: 2 }],
      [{ list: "ordered" }, { list: "bullet" }],
      [{ script: "sub" }, { script: "super" }],
      [{ indent: "-1" }, { indent: "+1" }],
      [{ direction: "rtl" }],
      [{ size: ["small", false, "large", "huge"] }],
      [{ header: [1, 2, 3, 4, 5, 6, false] }],
      [{ color: [] }, { background: [] }],
      [{ font: [] }],
      [{ align: [] }],
      ["clean"],
    ],
    clipboard: {
      matchVisual: false,
    },
  }
```

需要注意的是toolbar（工具栏）toolbar的配置需要和formats属性想匹配：

```typescript
const formats = [
    "header",
    "font",
    "size",
    "bold",
    "code-block",
    "italic",
    "underline",
    "strike",
    "blockquote",
    "list",
    "bullet",
    "indent",
    "link",
    "image",
    "video",
    "color",
    "align",
    "clean",
    "script",
    "direction",
  ]
```

然后在value中，我让编辑器在最开始，文本中就显示有一些提示内容。这里注意，里面写的是html语句。

```typescript
value={
              value ||
              '<h3>二级标题(<span style="color: rgb(230, 0, 0);">使用H3标签</span>)</h3><p>内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容(<span style="color: rgb(230, 0, 0);">内容直接输入不需要标签</span>)</p><p>内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容内容。(<span style="color: rgb(230, 0, 0);">输入任意字符即可在上方内容显示</span>)</p>'
            }
            onChange={setValue}
```

特别说明的一点是：由于React-Quill默认是将图片转换成base64的。但是由于一般情况想生成出来的base64字符串会特别长，所以这个地方我们采用的方式时先将图片上传到服务端，然后用上传成功之后返回的url来替换掉图片的base64。

# React-spring

先简单讲述以下它的API吧。

## useSpring

react-spring 中最基本的 API 就是 useSpring，用于数值间的 transition：

```react
import { animated, useSpring } from 'react-spring';
() => {
  const [open, setOpen] = useState(false);
  const props = useSpring({ width: open ? 240 : 40 });

  return (
    <animated.div
      style={{
        lineHeight: '40px',
        textAlign: 'center',
        height: 40,
        backgroundColor: 'azure',
        border: '1px solid darkslategrey',
        borderRadius: 8,
        cursor: 'pointer',
        ...props,
      }}
      onClick={() => setOpen((prev) => !prev)} //点击取反
    >
      {props.width.to((x) => x.toFixed(0))}
    </animated.div>
  );
};
```

當按下該 div 後就會將 width 從 40px transition 到 240px，children 也会显示对应的數值。

特別要注意的是，所有 react-spring 給的 props 都是 [SpringValue](https://react-spring.io/classes/spring-value)，若要让其作为 style 使用，就要放到 react-spring 提供的 `animated.x` 元件。

## useSprings

与 useSpring 类似，差別在 useSprings 操作的是一個 array 的 spring：

```react
const fn = (order: number[], active = false, originalIndex = 0, curIndex = 0, y = 0)=>{...}
const [springs, api] = useSprings(items.length, fn(order.current))
api.start( fn(newOrder, active, originalIndex, curIndex, y))
                                                                                       {springs.map(({ zIndex, shadow, y, scale }, i) => (
        <animated.div
          {...bind(i)}
          key={i}
          style={{
            zIndex,
            boxShadow: shadow.to(s => `rgba(0, 0, 0, 0.15) 0px ${s}px ${2 * s}px 0px`),
            y,
            scale,
          }}
          children={items[i]}
        />
      ))}
```



## useTransition

useTransition 應該是最常用的 hooks，用於實作單一元件或列表 mount／unmount 的動畫效果，避免僵直的元件切換

```react
() => {
  const [toggle, setToggle] = useState(false);
  const transitions = useTransition(toggle, {
    from: { opacity: 0 },
    enter: { opacity: 1 },
    leave: { opacity: 0 },
  });

  return (
    <div style={{ display: 'flex', height: 40 }}>
      <button
        style={{ marginRight: 16 }}
        onClick={() => setToggle((prev) => !prev)}
      >
        {toggle ? 'Hide' : 'Show'}
      </button>
      {transitions(
        (props, item) =>
          item && (
            <animated.div
              style={{
                fontSize: 40,
                lineHeight: 1,
                ...props,
              }}
            >
              😄
            </animated.div>
          )
      )}
    </div>
  );
};
```

## useTrial

與 useSprings 類似，差別在每一個 spring 會跟在前一個後面，不會同時觸發。

```jsx
const trail = useTrail(amount, { opacity: 1 });
return trail.map((styles) => <animated.div style={styles} />);
```

## useChain

用於連結不同 spring hooks 的動畫效果，讓下個動畫的作動時間會接在前一個完成後接續執行。

也可以設定 delay 時間在前一動畫完成時，經過指定時間後再執行下個動畫。以下節錄官方範例：

```typescript
const springRef = useSpringRef();
const props = useSpring({ ...values, ref: springRef });
const transitionRef = useSpringRef();
const transitions = useTransition({ ...values, ref: transitionRef });
// 先執行前個 spring 完成動畫後執行 transitionuseChain([springRef, transitionRef]);
return (  
    <animated.div style={props}>    
    {transitions((styles) => (      
     <animated.div style={styles} />
    ))}
     </animated.div>
);
```



我做的第一个效果是当滚动轴到达某一位置时，做一个信息由一点炸开展示的特效。

那么首先先要监听window。在react中，要监听到window对象的话，可以在useEffect中，我是这么选择的。

```typescript
useEffect(() => {
    window.addEventListener("scroll", () => {
      console.log({ e: document.documentElement.scrollTop })
    })
  })
```

这样可以拿到滚动轴距离顶部的距离。就有了触发动效的点了，接下来只要写好动效就可以了。这边我用的是useTransition。

```react
const [items, setItems] = useState<{ x: number, y: number, delay: number, label: string }[]>( [] )

  const transition = useTransition( items, {
    from: { x: widthRef.current / 2 - 25, y: heightRef.current / 2 - 25, opacity: 0 },
    enter: ( item ) => ( next ) => (
      next( { x: item.x, y: item.y, opacity: 1, delay: item.delay } )
    ),
    leave: { x: widthRef.current / 2 - 25, y: heightRef.current / 2 - 25, opacity: 0 }
  } )
```

```react
<div>
      {transition( ( style, item ) =>
        item ? (
     	<animated.div style={{ ...style, height: 151, width: 323.35, position: 'absolute', backdropFilter: 'blur(4px)', backgroundRepeat: 'no-repeat', margin: '4px', background: 'rgba(255, 255, 255, 0.4)', border: '0.4px solid rgba(255, 255, 255, 0.8)', borderRadius: '4px', fontSize: '24px', justifyContent: 'center', alignItems: 'center', display: 'flex', wordWrap: 'break-word', wordBreak: 'break-all' }} ><P>{item.label}</P>							</animated.div>
		): ''
      )}
</div>
```

这里写个我们设置item的例子，是这样，只要修改了item，那么animated.div里的数据就会变化了

```react
if ( scrollRef.current > 1650 && scrollRef.current < 2550 ) {//监听的滚动轴的位移
          if ( state === false ) {//默认是false，关闭状态 在这个if中会把他设置为true 打开状态
            widthRef.current = Ref.current?.offsetWidth
            heightRef.current = Ref.current?.offsetHeight
            setItems( v => v.length ? [] : [
              { x: 20, y: 15, delay: 200, label: '标题1' },
              { x: widthRef.current / 2 - 161, y: 15, delay: 300, label: '标题2' },
              { x: widthRef.current - 365, y: 15, delay: 400, label: '标题3' },
              { x: 20, y: heightRef.current / 2 - 80, delay: 200, label: '标题4' },
              { x: widthRef.current / 2 - 161, y: heightRef.current / 2 - 80, delay: 100, label: '标题5' },
              { x: widthRef.current - 365, y: heightRef.current / 2 - 80, delay: 400, label: '标题6' },
              { x: 20, y: heightRef.current - 170, delay: 400, label: '标题7' },
              { x: widthRef.current / 2 - 161, y: heightRef.current - 170, delay: 500, label: '标题8' },
              { x: widthRef.current - 365, y: heightRef.current - 170, delay: 400, label: '标题9' },
            ] )
            state = true  //这里将状态设置为打开状态，这样离开这个范围的时候就会触发else
          }
        } else {
          if ( state === true ) {//离开范围时执行，将item设置为[]
            setItems( [] )
            state = false
          }
        }
```

