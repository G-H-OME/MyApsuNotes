# APSU后台

1.创建用户，加入公司

2.在公司下，创建型号 和 产品

3.在产品下，创建固件（选择型号，选择产品，就会展示出产品的功能，一个固件相当于产品的一个功能，选择相应功能填写详细代码）

一个型号本身带有功能，相当于再从产品中定制专属的功能出来 成为一个 固件。







### 更改了Topic的字段

```typescript
@Field( { nullable: true } )
  @Property()
  access: string //pub,sub,pubsub

  @Field()
  @Property()
  name: string

  @Field()
  @Property()
  FunName: string

  @Field()
  @Property()
  ExampleValue: string

  @Field()
  @Property()
  FunDescription: string

  @Field()
  @Property()
  icon: string

  @ManyToOne( () => Company, { nullable: true } )
  company: IdentifiedReference<Company>

  @ManyToOne( () => Product, { nullable: true } )
  product?: IdentifiedReference<Product>

  @ManyToOne( () => Device, { nullable: true } )
  device?: IdentifiedReference<Device>
```



​				产品ID: "182px,48px",

​                产品名称: "193px,48px",

​                创建时间: "152px,48px",

​                固件版本: "56px,48px",

​                产品详情图: "70px,48px",


