import React, { useEffect, useState } from "react";
import { Layout, Menu, Breadcrumb, Switch, Divider, message, Image } from 'antd';
import { HomeOutlined } from '@ant-design/icons';
import tsIcon from '../../logo4.png';
import { useGesture } from 'react-use-gesture'
import {
    UserOutlined, LaptopOutlined, NotificationOutlined, MailOutlined,
    SmileOutlined
} from '@ant-design/icons';
import Editor from './codeeditor';
import "./codecontent.css";
import Codeparameter from './codeparameter';
import PropTypes from 'prop-types';
import TweenOne from 'rc-tween-one';
import PathPlugin from 'rc-tween-one/lib/plugin/PathPlugin';
TweenOne.plugins.push(PathPlugin);
const { SubMenu } = Menu;
const { Header, Content, Sider } = Layout;
const CodeContent = () => {
    const [mode, setMode] = React.useState('inline');
    const [theme, setTheme] = React.useState('light');
    const [CurIndex, setCurIndex] = useState('1');

    const changeMode = value => {
        setMode(value ? 'vertical' : 'inline');
    };

    const changeTheme = value => {
        setTheme(value ? 'dark' : 'light');
    };
    const scrollToAnchor = (anchorName) => {
        if (anchorName) {
            // 找到锚点
            let anchorElement = document.getElementById(anchorName);
            if (anchorElement) { anchorElement.scrollIntoView({ block: 'start', behavior: 'smooth' }); }
        }
    }
    const changeCurIndex = (value) => {
        setCurIndex(value)
        console.log('program' + value)
        scrollToAnchor('program' + value)
    }

    const menu = (
        <Menu>
            <Menu.Item>
                <a target="_blank" rel="noopener noreferrer" onClick={() => changeCurIndex("1")} >
                    Program
            </a>
            </Menu.Item>
            <Menu.Item>
                <a target="_blank" rel="noopener noreferrer" onClick={() => changeCurIndex("2")} >
                    Verify Program
            </a>
            </Menu.Item>
        </Menu>
    );
    return (
        <Layout>

            <Header className="header">
                <div className="logo" />
                <Menu theme="dark" mode="horizontal" defaultSelectedKeys={['2']}>
                    <Menu.Item key="1"><a href="./">首页</a></Menu.Item>
                    <Menu.Item key="2">控制台</Menu.Item>
                    <Menu.Item key="3">使用帮助</Menu.Item>
                </Menu>
            </Header>
            <Layout>
                <Sider width={250} className="site-layout-background">
                    <Switch onChange={changeTheme} style={{ margin: 30 }} /> 切换风格
                        <Menu
                        mode="inline"
                        defaultSelectedKeys={['1']}
                        defaultOpenKeys={['sub1', 'sub2', 'sub3']}
                        style={{ height: '100%', borderRight: 0 }}
                        theme={theme}
                    >
                        <SubMenu key="sub1" icon={<UserOutlined />} title="个人信息">
                            <Menu.Item key="1">控制台</Menu.Item>
                            <Menu.Item key="2">用户信息</Menu.Item>
                            <Menu.Item key="3">实名认证</Menu.Item>
                            <Menu.Item key="4">邀请好友</Menu.Item>
                        </SubMenu>
                        <SubMenu key="sub2" icon={<LaptopOutlined />} title="账号设置">
                            <Menu.Item key="5">通知设置</Menu.Item>
                            <Menu.Item key="6">账户等级</Menu.Item>
                            <Menu.Item key="7">充值记录</Menu.Item>
                            <Menu.Item key="8">消费记录</Menu.Item>
                        </SubMenu>
                        <SubMenu key="sub3" icon={<NotificationOutlined />} title="消费记录">
                            <Menu.Item key="9">我的工单</Menu.Item>
                            <Menu.Item key="10">消息中心</Menu.Item>
                            <Menu.Item key="11">积分商城</Menu.Item>
                            <Menu.Item key="12">操作记录</Menu.Item>
                        </SubMenu>
                        <div id="menu-logo">
                            <Image
                                width={200}
                                src={tsIcon} />
                        </div>
                    </Menu>
                </Sider>
                <Layout style={{ padding: '0 24px 24px' }}>
                    <Breadcrumb style={{ margin: '16px 0' }}>
                        <Breadcrumb.Item >
                            <HomeOutlined /><span>Home</span>
                        </Breadcrumb.Item>
                        <Breadcrumb.Item >
                            <UserOutlined />
                            <span>Code List</span>
                        </Breadcrumb.Item>
                        <Breadcrumb.Item overlay={menu}>Program</Breadcrumb.Item>
                    </Breadcrumb>
                    <Content
                        className="site-layout-background"
                        style={{
                            padding: 24,
                            margin: 0,
                            minHeight: 280,
                        }}
                    >
                        <Editor ></Editor>
                    </Content>
                </Layout>
            </Layout>
        </Layout>
    );
};

export default CodeContent;