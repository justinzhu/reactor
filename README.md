reactor
=======
一个简单的reactor模式的实现。目前只支持select和epoll两种多路复用的实现。
如果要使用select，则可使用编译参数
make select
如果要实现epoll，则使用编译参数
make epoll

代码中用这个reactor实现了一个反射服务器。
由于项目是练手项目，在socket异常处理部分做得比较简单，有兴趣得同学自行完善下
