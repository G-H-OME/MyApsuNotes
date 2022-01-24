# 前言

记录：==在页面中滚动到某处有新元素出现，离开时消失== 的实现

# React-spring

## Hooks

useChain

useSpring

useSprings

useTrail

useTransition

------------

这里我使用useTransition，通过传入items，以及定义三个状态(from,enter,leave)来达到多个对象的动效。

```typescript
const [items, setItems] = useState<{ x: number, y: number, delay: number }[]>( [] )//定义要传入的属性类型
const transition = useTransition( items, {
    from: { x: 200, y: 200, opacity: 0 },//opacity：透明度
    enter: ( item ) => ( next ) => (
      next( { x: item.x, y: item.y, opacity: 1, delay: item.delay } )
    ),
    leave: { x: 200, y: 200, opacity: 0 }
  } )

===============修改items👇===============
      setItems( item => item.length ? [] : [//暂时写的固定位置，可以灵活更改
            { x: 50, y: 50, delay: 200 },
            { x: 200, y: 50, delay: 300 },
            { x: 350, y: 50, delay: 400 },
            { x: 50, y: 200, delay: 500 },
            { x: 200, y: 200, delay: 100 },
            { x: 350, y: 200, delay: 700 },
            { x: 50, y: 350, delay: 800 },
            { x: 200, y: 350, delay: 700 },
            { x: 350, y: 350, delay: 600 },
          ] )
========================================
      
return(
	<>
    	<Box>//用styled-components写的div名为Box，主要让它 position:relative
    		{transition( ( style, item ) =>
          		item ? <animated.div style={{ ...style, height: 100, width: 				100, position: 'absolute', backgroundImage: 'url(xxx.svg)', 				 backgroundColor: 'black' }} /> : '' //如果没items输出空
        )}
    	</Box>
    </>
)
```

这样实现的效果是：触发setItems时，这9个对象从from的位置(x:200,y:200)发散出来到各自的位置。

# ScrollTop

往常我们知道，可以通过window.onscroll,window.addEventListener('scroll',()=>{})来实现滚动事件。但window 对象仅存在于浏览器中，因此，需要确保代码在 componentDidMount 的 useEffect 中运行，否则会报错 ==ReferenceError: window is not defined== 。

下面是自己根据节流(throttle)写的：

```typescript
let state = false //定义state表示动效状态
const scrollRef = useRef(0)

useEffect( () => {
    window.addEventListener( 'scroll', () => {
      scrollRef.current = document.documentElement.scrollTop
      console.log( scrollRef.current );//可以看到滚动条高度
      if ( scrollRef.current > 1630 && scrollRef.current < 2330 ) {
      //上面根据具体情况定高度范围
        if ( state === false ) {//如果state为false，表示动效未被执行
          setItems(...)         //那么执行动效
          state = true          //并将state改为true，防止重复执行
        }
      } else { //如果在范围外的话，有两种情况：1.刚进入页面，还为到达动效区域 2.离开区域
        if ( state === true ) {//如果state为true 说明刚离开动效区域
          setItems( [] )       //那么将items设置为空数组，即可让出现的元素消失
          state = false		   //将state设置为false，这样再回来时可以再次触发事件
        }
      }
    } )
  }, [] )
```

