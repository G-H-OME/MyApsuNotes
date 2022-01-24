# 树梅派制作无线wifi（桥接模式）

所谓的==桥接模式==，也就是将eth0和wlan0通过一座虚拟的桥连接起来，树莓派==通过eth0上网==，然后==将wlan0分享出来==，供给其他设备连接上网。

==**内置以太网接口 (eth0)**==

## 1.安装必备程序

```
sudo apt-get install hostapd udhcpd bridge-utils
```

这三种工具中hostapd能使无线网卡工作在软AP模式，udhcpd用来分配ip地址，bridge-utils是网桥工具。

## 2、配置网卡

输入sudo vim /etc/network/interfaces 

注释掉所有关于无线网卡的配置部分，但lo和eth0的部分可以保留，如图：

![img](https://img-blog.csdn.net/201804051534118)

添加的部分就是关于桥接的配置：

auto br0

iface br0 inet dhcp

bridge_ports eth0 wlan0

## 3、配置hostapd

输入  sudo vim /etc/hostapd/hostapd.conf

在其中添加如下内容：

```
interface=wlan0
driver=nl80211
bridge=br0
ssid=Raspberry_AP
channel=1
wmm_enabled=0
wpa=1
wpa_passphrase=12345678
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
auth_algs=1
macaddr_acl=0
```

添加完后保存退出。

参数的具体含义请参考我的上一篇文章，ssid名字和wpa_passphrase密码可以自行更改，但密码要在八位以上。（上一篇文章搬过来了👇）

```
# 这是我们上配置的WiFi接口的名称
interface=wlan0
 
# 使用 nl80211 驱动程序和 brcmfmac 驱动程序
driver=nl80211
 
# 这是网络名称
ssid=Pi3-AP
 
# 使用 2.4GHz 频段
hw_mode=g
 
# 使用频道 6
channel=6
 
# 启用 802.11n
ieee80211n=1
 
# 启用 WMM
wmm_enabled=1
 
# 启用具有 20ns 保护间隔的 40MHz 信道
ht_capab=[HT40][SHORT-GI-20][DSSS_CCK-40]
 
#接受所有MAC地址
macaddr_acl=0
 
# 使用WPA认证
auth_algs=1
 
# 要求客户端知道网络名称
ignore_broadcast_ssid=0
 
# 使用 WPA2
wpa=2
 
# 使用预共享密钥
wpa_key_mgmt=WPA-PSK
 
# 网络密码
wpa_passphrase=raspberry
 
# 使用 AES，而不是 TKIP
rsn_pairwise=CCMP
```



## 4、重启并测试hostapd

输入sudo reboot

之后我们测试hostapd是否正常：sudo hostapd -dd /etc/hostapd/hostapd.conf

![img](https://img-blog.csdn.net/20180405154229533)

如果测试一次不正常请尝试两遍，如果失败请查看以上的配置是否出差错。

如果成功，那么就可以看到我们的Raspberry_AP了，但还无法连接，按ctrl+c退出测试。

## 5、配置文件路径

输入 sudo vim /etc/default/hostapd

找到#DAEMON_CONF=这一行，去掉#号，并改为我们的配置文件路径：
DAEMON_CONF="/etc/hostapd/hostapd.conf"，

并将hostapd加入开机自启动：

输入sudo update-rc.d hostapd enable

## 6、重启hostapd

输入sudo service hostapd restart

这下可以通过手机或者电脑连接我们Raspberry_AP的wifi了









额外收获：

学习到了Linux里有个cowsay。。。哈哈哈(牛说)