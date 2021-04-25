import React, { useState, useEffect } from 'react'
import { useHistory } from "react-router-dom";
import { Drawer, Form, Button, Col, Row, Input, Select, DatePicker } from 'antd';
import { PlusOutlined } from '@ant-design/icons';
const { Option } = Select;



function Codeparameter(props) {
    const [visible, setVisible] = useState(false);
    // const [register_count, setregister_count] = useState("20");
    // const [word_size, setword_size] = useState("8");
    // const [tinyram_input_size_bound, settinyram_input_size_bound] = useState("25");
    // const [program, setprogram] = useState("20");
    // const [time_bound, settime_bound] = useState("64");
    const { OutputText } = props;
    const showDrawer = () => {
        setVisible(true);
    };

    const onClose = () => {
        setVisible(false);
    };
    const [values, setValues] = useState({
        register_count: "",
        word_size: "",
        tinyram_input_size_bound: "",
        program: "",
        time_bound: "",
    });

    const onChange = event => {
        console.log("1", event.target.value)
        console.log("3", event.target.name)
        console.log("2", values.word_size)
        setTimeout(() => {
            setValues({ ...values, [event.target.name]: event.target.value })
        }, 0);
        console.log("4", values.word_size)
        // setValues();
    };



    // const onChangeRegister = (value) => {
    //     setregister_count(value);
    // }
    // const onChangeWordSize = (value) => {
    //     setword_size(value);
    //     console.log(value);
    // }
    // const onChangeTinyram = (value) => {
    //     settinyram_input_size_bound(value);
    // }
    // const onChangeProgram = (value) => {
    //     setprogram(value);
    // }
    // const onChangeTimebound = (value) => {
    //     settime_bound(value);
    // }
    const onSubmit = (e) => {
        // 把表单用的最终数据从state中提取出来,传入请求
        e.preventDefault();
        console.log("sze", values);
        console.log("aaa", OutputText);
        fetch('http://localhost:8080/thirdParty/buyer?values=' + values.program)
            .then(res => res.text())
            .catch(e => console.log('错误:', e))
        handleClick();
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
                                <Input placeholder="Please enter Register count" value={values.register_count}
                                    onChange={onChange} name="register_count" />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="word_size"
                                label="Word_size"
                                rules={[{ required: true, message: 'Please enter Word size(bit)' }]}
                            >
                                <Input placeholder="Please enter Word size(bit)" value={values.word_size}
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
                                <Input placeholder="Please enter Tinyram input size bound" onChange={onChange} name="tinyram_input_size_bound" />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="program"
                                label="Program"
                                rules={[{ required: true, message: 'Please enter Program' }]}
                            >
                                <Input placeholder="Please enter Program" onChange={onChange} name="program" />
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
                                <Input placeholder="Please enter Time bound" onChange={onChange} name="time_bound" />
                            </Form.Item>
                        </Col>
                        <Col span={12}>
                            <Form.Item
                                name="dateTime"
                                label="DateTime"
                                rules={[{ required: true, message: 'Please choose the dateTime' }]}
                            >
                                <DatePicker.RangePicker
                                    style={{ width: '100%' }}
                                    getPopupContainer={trigger => trigger.parentElement}
                                />
                            </Form.Item>
                        </Col>
                    </Row>
                    <Row gutter={30}>
                        <Col span={24}>
                            <Form.Item
                                name="OutputText"
                                label="OutputText"
                                initialValue={OutputText.toString()}
                                rules={[
                                    {
                                        required: true,
                                        message: 'please enter OutputText',
                                    },
                                ]
                                }
                            >
                                <Input.TextArea rows={30} placeholder={OutputText.toString()} onChange={onChange} name="OutputText" />
                            </Form.Item>
                        </Col>
                    </Row>
                </Form>
            </Drawer>
        </>
    );
}
export default Codeparameter;