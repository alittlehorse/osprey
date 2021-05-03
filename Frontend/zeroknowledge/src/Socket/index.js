/**
 * 参数：[socketOpen|socketClose|socketMessage|socketError] = func，[socket连接成功时触发|连接关闭|发送消息|连接错误]
 * timeout：连接超时时间
 * @type {module.webSocket}
 */
module.exports = class webSocket {
  constructor(param = {}) {
    this.param = param;
    this.reconnectCount = 0;
    this.socket = null;
    this.taskRemindInterval = null;
    this.isSuccess = true;
  }
  connection = () => {
    let { socketUrl, timeout = 0 } = this.param;
    const Stomp = require('stompjs')
    var SockJS = require('sockjs-client')
    SockJS = new SockJS('/ws')
    // 检测当前浏览器是什么浏览器来决定用什么socket
    if ("WebSocket" in window) {
      console.log("WebSocket");
      this.socket = new WebSocket(socketUrl);
    }else {
      console.log("SockJS");
      this.socket = new SockJS(socketUrl);
    }
    this.socket.onopen = this.onopen;
    this.socket.onmessage = this.onmessage;
    this.socket.onclose = this.onclose;
    this.socket.onerror = this.onerror;
    this.socket.sendMessage = this.sendMessage;
    this.socket.closeSocket = this.closeSocket;
  };
  // 连接成功触发
  onopen = () => {
    let { socketOpen } = this.param;
    this.isSuccess = false; //连接成功将标识符改为false
    socketOpen && socketOpen();
  };
  // 后端向前端推的数据
  onmessage = (msg) => {
    let { socketMessage } = this.param;
    socketMessage && socketMessage(msg);
  };
  // 关闭连接触发
  onclose = (e) => {
    this.isSuccess = true; //关闭将标识符改为true
    this.socket.close();
    let { socketClose } = this.param;
    socketClose && socketClose(e);
  };
  onerror = (e) => {
    // socket连接报错触发
    let { socketError } = this.param;
    this.socket = null;
    socketError && socketError(e);
  };
  sendMessage = (value) => {
    // 向后端发送数据
    if (this.socket) {
      this.socket.send(JSON.stringify(value));
    }
  };
  closeSocket = () => {
    this.socket.close();
  };
  //获得状态
  readyState = () => {
    return this.socket.readyState;
  };
};
