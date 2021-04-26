import React, { useEffect, useState } from "react";
import { Layout, Menu, Breadcrumb, Switch, Divider } from 'antd';
import {
    UserOutlined, LaptopOutlined, NotificationOutlined, MailOutlined,
    SmileOutlined 
} from '@ant-design/icons';
import Editor from './codeeditor';
import "./codecontent.css";
import Codeparameter from './codeparameter';
import Tool from './Tool';

const { SubMenu } = Menu;
const { Header, Content, Sider } = Layout;

const CodeContent = () => {
    const [mode, setMode] = React.useState('inline');
    const [theme, setTheme] = React.useState('light');

    const changeMode = value => {
        setMode(value ? 'vertical' : 'inline');
    };

    const changeTheme = value => {
        setTheme(value ? 'dark' : 'light');
    };
    return (
        <Layout>
            <Header className="header">
                <div className="logo" />
                <Menu theme="dark" mode="horizontal" defaultSelectedKeys={['2']}>
                    <Menu.Item key="1">首页</Menu.Item>
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
                            defaultOpenKeys={['sub1']}
                            style={{ height: '100%', borderRight: 0 }}
                            theme={theme}
                        >
                            <SubMenu key="sub1" icon={<UserOutlined />} title="subnav 1">
                                <Menu.Item key="1">用户中心</Menu.Item>
                                <Menu.Item key="2">用户信息</Menu.Item>
                                <Menu.Item key="3">实名认证</Menu.Item>
                                <Menu.Item key="4">邀请好友</Menu.Item>
                            </SubMenu>
                            <SubMenu key="sub2" icon={<LaptopOutlined />} title="subnav 2">
                                <Menu.Item key="5">通知设置</Menu.Item>
                                <Menu.Item key="6">账户等级</Menu.Item>
                                <Menu.Item key="7">充值记录</Menu.Item>
                                <Menu.Item key="8">消费记录</Menu.Item>
                            </SubMenu>
                            <SubMenu key="sub3" icon={<NotificationOutlined />} title="subnav 3">
                                <Menu.Item key="9">我的工单</Menu.Item>
                                <Menu.Item key="10">消息中心</Menu.Item>
                                <Menu.Item key="11">积分商城</Menu.Item>
                                <Menu.Item key="12">操作记录</Menu.Item>
                            </SubMenu>
                        </Menu>
                </Sider>
                    <Layout style={{ padding: '0 24px 24px' }}>
                        <Breadcrumb style={{ margin: '16px 0' }}>
                            <Breadcrumb.Item>Home</Breadcrumb.Item>
                            <Breadcrumb.Item>Service</Breadcrumb.Item>
                            <Breadcrumb.Item>App</Breadcrumb.Item>
                        </Breadcrumb>
                        <Content
                            className="site-layout-background"
                            style={{
                                padding: 24,
                                margin: 0,
                                minHeight: 280,
                            }}
                        >
                            <Editor></Editor>
                        </Content>
                    </Layout>
            </Layout>
            </Layout>
    );
};

export default CodeContent;