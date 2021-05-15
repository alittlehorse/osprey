import React, { useState, useEffect } from 'react'
import { useHistory } from "react-router-dom";
import { Drawer, Form, Button, Col, Row, Input, Select, DatePicker } from 'antd';
import { PlusOutlined } from '@ant-design/icons';
import io from 'socket.io-client'
const { Option } = Select;

var stompClient = null; // 设置 STOMP 客户端
var SOCKET_ENDPOINT = "/osprey"; // 设置 WebSocket 进入端点
var SUBSCRIBE_PREFIX = "/topic/public" // 设置订阅消息的请求前缀
var SUBSCRIBE = ""; // 设置订阅消息的请求地址
var SEND_ENDPOINT = "/app/test"; // 设置服务器端点，访问服务器中哪个接口
var message2 = "";
var wsUrl = "ws://106.13.125.83:3498/compute_query";//必须以ws开头
//wsUrl = "ws://localhost:3498/compute_query";//必须以ws开头
let ws;

function Codeparameter(props) {
    const [visible, setVisible] = useState(false);
    const [error, seterror] = useState("");
    const [channelConnected, setchannelConnected] = useState(false)
    const { compile_info, changeInfo } = props;
    const connect = () => {
        ws = new WebSocket(wsUrl);
        ws.onopen = function (evt) {
            console.log("连接开始")
            sendMessage();
        }
        onMessageReceived();
        ws.onclose = function () {
            console.log("连接已关闭...");
            handleClick()
        }
    }
    
    const onMessageReceived = () => {
        ws.onmessage = function (payload) {
            console.log('有消息过来');
            console.log(payload.data);
            message2 += payload.data;
            changeInfo(compile_info + message2);
        }
    }
    const sendMessage = () => {
        // 设置待发送的消息内容
        var message3 = {
            "register_count": parseInt(values.register_count),
            "tinyram_input_size_bound": Number(values.tinyram_input_size_bound),
            "word_size": Number(values.word_size),
            "verify_program": verify_program,
            "tinyram_program_size_bound": Number(values.tinyram_program_size_bound),
            "program": program,
            "time_bound": 64,
            "destination": SUBSCRIBE_PREFIX
        }
        console.log("aaaa", message3);
        console.log("bbbb", JSON.stringify(message3))
        ws.send(JSON.stringify(message3));
    }

    const { program } = props;
    const { verify_program } = props;
    const showDrawer = () => {
        setVisible(true);
    };

    const onClose = () => {
        setVisible(false);
    };
    const [values, setValues] = useState({
        register_count: 16,
        word_size: 16,
        tinyram_input_size_bound: 25,
        program: 16,
        time_bound: 64,
        tinyram_program_size_bound: 20
    });

    const onChange = event => {
        console.log("1", event.target.value)
        console.log("3", event.target.name)
        console.log("2", values.word_size)
        setTimeout(() => {
            setValues({ ...values, [event.target.name]: event.target.value })
        }, 0);
        console.log("4", values.word_size)
        console.log("5", values.register_count)
        console.log("6", values.tinyram_program_size_bound)
        console.log("hzr", JSON.stringify(values))
    };
    const onSubmit = (e) => {
        connect();
        onClose();
        scrollToAnchor('result');
    };
    const scrollToAnchor = (anchorName) => {
        if (anchorName) {
            // 找到锚点
            let anchorElement = document.getElementById(anchorName);
            if (anchorElement) { anchorElement.scrollIntoView({ block: 'start', behavior: 'smooth' }); }
        }
    }
    let history = useHistory();
    function handleClick() {
        history.push("/result");
    }
    return (
        <>
            <Button type="primary" onClick={showDrawer}>
                <PlusOutlined /> 输入运行参数
          </Button>
            <Drawer
                title="请输入即将运行的模拟参数"
                width={720}
                onClose={onClose}
                visible={visible}
                bodyStyle={{ paddingBottom: 80 }}
                footer={
                    <div
                        style={{
                            textAlign: 'right',
                        }}
                    >
                        <Button onClick={onClose} style={{ marginRight: 8 }}>
                            Cancel
                </Button>
                        <Button type="primary" htmlType="submit" onClick={onSubmit} >
                            Submit
                </Button>
                    </div>
                }
            >
                <Form layout="vertical" noValidate >
                    <Row gutter={16}>
                        <Col span={12}>
                            <Form.Item
                                name="register_count"
                                label="Register_count"
                                rules={[{ required: true, message: 'Please enter Register count' }]}
                            >
                                <Input placeholder={values.register_count} value={values.register_count}
                                    onChange={onChange} name="register_count" />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="word_size"
                                label="Word_size"
                                rules={[{ required: true, message: 'Please enter Word size(bit)' }]}
                            >
                                <Input placeholder={values.word_size} value={values.word_size}
                                    onChange={onChange} name="word_size" />
                            </Form.Item>
                        </Col>
                    </Row>
                    <Row gutter={16}>
                        <Col span={12}>
                            <Form.Item
                                name="tinyram_input_size_bound"
                                label="Tinyram_input_size_bound"
                                rules={[{ required: true, message: 'Please enter Tinyram input size bound' }]}
                            >
                                <Input placeholder={values.tinyram_input_size_bound} onChange={onChange} name="tinyram_input_size_bound" value={values.tinyram_input_size_bound} />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="program"
                                label="Program"
                                rules={[{ required: true, message: 'Please enter Program' }]}
                            >
                                <Input placeholder={values.program} onChange={onChange} name="program" value={values.program} />
                            </Form.Item>
                        </Col>
                    </Row>
                    <Row gutter={16}>
                        <Col span={12}>
                            <Form.Item
                                name="time_bound"
                                label="Time_bound"
                                rules={[{ required: true, message: 'Please enter Time bound' }]}
                            >
                                <Input placeholder={values.time_bound} onChange={onChange} name="time_bound" value={values.time_bound} />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="tinyram_program_size_bound"
                                label="Tinyram_program_size_bound"
                                rules={[{ required: true, message: 'Please enter Tinyram_program_size_bound' }]}
                            >
                                <Input placeholder={values.tinyram_program_size_bound} onChange={onChange} name="tinyram_program_size_bound" value={values.tinyram_program_size_bound} />
                            </Form.Item>
                        </Col>
                    </Row>
                    <Row gutter={30}>
                        <Col span={24}>
                            <Form.Item
                                name="verify_program"
                                label="verify_program"
                                initialValue={program.toString()}
                                rules={[
                                    {
                                        required: true,
                                        message: 'please enter verify_program',
                                    },
                                ]
                                }
                            >
                                <Input.TextArea rows={25} placeholder={program.toString()} onChange={onChange} name="verify_program" value={program} />
                            </Form.Item>
                        </Col>
                    </Row>
                    <Row gutter={30}>
                        <Col span={24}>
                            <Form.Item
                                name="userProgram"
                                label="userProgram"
                                initialValue={verify_program.toString()}
                                rules={[
                                    {
                                        required: true,
                                        message: 'please enter userProgram',
                                    },
                                ]
                                }
                            >
                                <Input.TextArea rows={25} placeholder={verify_program.toString()} onChange={onChange} name="userProgram" value={verify_program}/>
                            </Form.Item>
                        </Col>
                    </Row>
                </Form>
            </Drawer>
        </>
    );
}
export default Codeparameter;