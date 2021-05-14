import styled, { keyframes } from "styled-components";
import { fadeInUp } from "react-animations";
import { Card, Layout, Menu, Row, Col, Divider } from "antd";
import { ArrowLeftOutlined } from "@ant-design/icons";
import "../Select/index.css";
import React from "react";
import { Link, Route } from "react-router-dom";
const { Content } = Layout;
const bounceAnimation = keyframes`${fadeInUp}`;

const BouncyDiv = styled.div`
  animation: 1s ${bounceAnimation};
`;
const { Meta } = Card;
export default function Loading() {
  return (
    <div className="hzr-page" id="hzr-page">
        <div className="hzr-header" id="hzr-header">
          <div className="hzr-brand">
            <ArrowLeftOutlined style={{ margin: 20 }} />
            <Link to="/">返回</Link>
          </div>
          <div className="hzr-nav">
            <ul>
              <li>
                <Link to="/">关于Osprey</Link>
              </li>
              <li>
                <Link to="/">加入我们</Link>
              </li>
            </ul>
          </div>
        </div>
      <div id="hzr-text" className="hzr-text">
        请选择您意向的公司
        <p>以让我们为您提供定制化的服务</p>
      </div>
      <div className="hzr-content" id="hzr-content">
        <div id="cards" className="cards">
          <Row gutter={200}>
            <Col span={70}>
              <BouncyDiv>
                <a href="/code">
                <Card
                  hoverable
                  style={{ width: 240, height: 350 }}
                  cover={
                    <img
                      alt="example"
                      src="https://i04piccdn.sogoucdn.com/cb62cebf7fb927ed"
                    />
                  }
                >
                  <Divider plain></Divider>
                  <Meta title="字节跳动" description="激发创造 丰富生活" />
                </Card>
                </a>
              </BouncyDiv>
            </Col>
            <Col span={70}>
              <BouncyDiv>
              <a href="/code">
                <Card
                  hoverable
                  style={{ width: 240, height: 350 }}
                  cover={
                    <img
                      alt="example"
                      src="https://www.logoids.com/upload/image/201801/15165886089623274.jpg"
                    />
                  }
                >
                  <Divider plain></Divider>
                  <Meta title="阿里巴巴" description="让天下没有难做的生意" />
                </Card>
                </a>
              </BouncyDiv>
            </Col>
            <Col span={70}>
              <BouncyDiv>
              <a href="/code">
                <Card
                  hoverable
                  style={{ width: 240, height: 350 }}
                  cover={
                    <img
                      alt="example"
                      src="https://www.mg21.com/wp-content/uploads/2016/04/Tencent.png"
                    />
                  }
                >
                  {" "}
                  <Divider plain></Divider>
                  <Meta title="腾讯" description="正直，进取，合作，创新" />
                </Card>
                </a>
              </BouncyDiv>
            </Col>
          </Row>
        </div>
      </div>
    </div>
  );
}
