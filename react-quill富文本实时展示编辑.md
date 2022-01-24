# 前言

做一个==本地富文本编辑器==，可以实时查看编写的数据。

# React-Quill

## 安装：

```typescript
yarn add -D react-quill
```

## 基本结构：

```typescript
import React, { useState } from "react";
import ReactQuill from 'react-quill';
import 'react-quill/dist/quill.snow.css';//一定要有，否则没有样式，会炸掉

function MyComponent() {
  const [value, setValue] = useState('');//用于读取输入的文本

  return (
    <ReactQuill theme="snow" value={value} onChange={setValue}/>
  );
}
```

这个ReactQuill可以这样代替：

```typescript
import dynamic from 'next/dynamic'

const QuillNoSSRWrapper = dynamic( import( "react-quill" ), {
  ssr: false,
  loading: () => <p>Loading ...</p>,
} )

return (
    <QuillNoSSRWrapper theme="snow" value={value} onChange={setValue}/>
  );
```

以上会获得一个输入框，富文本还需要上面的样式控制板，如下：

```typescript
const modules = { //定义样式控制板的内容
    toolbar: [
      ["bold", "italic", "underline", "strike", "image"],
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
    }
  }

const formats = [ //定义格式
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

<QuillNoSSRWrapper
        style={{ height: '500px' }}
        modules={modules}//传入模板
        formats={formats}//传入格式
        theme='snow'
        value={value || '这里可以输入默认内容'}
        onChange={setValue} />//获得的是Html格式的数据
```

# dangerouslySetInnerHTML

## React中接收Html格式数据

react中有一个属性可以用来接受html格式的数据并展示出来，这里我们可以使用到:dangerouslySetInnerHTML   用法很简单：

```typescript
<div dangerouslySetInnerHTML={{ __html: value}}></div> //value:html格式的数据
```

但这里由于使用的是react-quill  因此我们需要引用它的css

```typescript
<div className='ql-editor' dangerouslySetInnerHTML={{ __html: value}}></div> 
```

这样就可以做到实时查看自己编辑的效果。



## OSS上传图片，将图片插入content









