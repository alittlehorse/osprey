import React from "react";

export const Nav01DataSource = {
  wrapper: { className: "header0 home-page-wrapper" },
  page: { className: "home-page" },
  logo: {
    className: "header0-logo",
    // children: 'https://os.alipayobjects.com/rmsportal/mlcYmsRilwraoAe.svg',
  },
  Menu: {
    className: "header0-menu",
    children: [
      {
        name: "item0",
        className: "header0-item",
        children: {
          href: "#",
          children: [
            {
              children: (
                <span>
                  <span>
                    <p>首页</p>
                  </span>
                </span>
              ),
              name: "text",
            },
          ],
        },
      },
      {
        name: "item1",
        className: "header0-item",
        children: {
          href: "/load",
          children: [
            {
              children: (
                <span>
                  <p>开始使用</p>
                </span>
              ),
              name: "text",
            },
          ],
        },
      },
      {
        name: "item2",
        className: "header0-item",
        children: {
          href: "#",
          children: [
            {
              children: (
                <span>
                  <span>
                    <p>使用说明</p>
                  </span>
                </span>
              ),
              name: "text",
            },
          ],
        },
      },
      {
        name: "item3",
        className: "header0-item",
        children: {
          href: "#",
          children: [{ children: "关于我们", name: "text" }],
        },
      },
    ],
  },
  mobileMenu: { className: "header0-mobile-menu" },
};
export const Banner51DataSource = {
  wrapper: { className: "home-page-wrapper banner5" },
  page: { className: "home-page banner5-page" },
  childWrapper: {
    className: "banner5-title-wrapper",
    children: [
      {
        name: "title",
        children: (
          <span>
            <p>OSPrey</p>
          </span>
        ),
        className: "banner5-title",
      },
      {
        name: "explain",
        className: "banner5-explain",
        children: (
          <span>
            <p>PaaS零知识证明平台</p>
          </span>
        ),
      },
      {
        name: "button",
        className: "banner5-button-wrapper",
        children: {
          href: "/load",
          className: "banner5-button",
          type: "primary",
          children: "开始使用",
        },
      },
    ],
  },
  image: {
    className: "banner5-image",
    children:
      "https://gw.alipayobjects.com/mdn/rms_ae7ad9/afts/img/A*-wAhRYnWQscAAAAAAAAAAABkARQnAQ",
  },
};
export const Content00DataSource = {
  wrapper: { className: "home-page-wrapper content0-wrapper" },
  page: { className: "home-page content0" },
  OverPack: { playScale: 0.3, className: "" },
  titleWrapper: {
    className: "title-wrapper",
    children: [{ name: "title", children: "产品与服务" }],
  },
  childWrapper: {
    className: "content0-block-wrapper",
    children: [
      {
        name: "block0",
        className: "content0-block",
        md: 8,
        xs: 24,
        children: {
          className: "content0-block-item",
          children: [
            {
              name: "image",
              className: "content0-block-icon",
              children:
                "https://zos.alipayobjects.com/rmsportal/WBnVOjtIlGWbzyQivuyq.png",
            },
            {
              name: "title",
              className: "content0-block-title",
              children: "数据隐私保护",
            },
            { name: "content", children: "保护您珍贵的隐私信息" },
          ],
        },
      },
      {
        name: "block1",
        className: "content0-block",
        md: 8,
        xs: 24,
        children: {
          className: "content0-block-item",
          children: [
            {
              name: "image",
              className: "content0-block-icon",
              children:
                "https://zos.alipayobjects.com/rmsportal/YPMsLQuCEXtuEkmXTTdk.png",
            },
            {
              name: "title",
              className: "content0-block-title",
              children: "一站式事中风险监控",
            },
            {
              name: "content",
              children: "区块链保证公平交易",
            },
          ],
        },
      },
      {
        name: "block2",
        className: "content0-block",
        md: 8,
        xs: 24,
        children: {
          className: "content0-block-item",
          children: [
            {
              name: "image",
              className: "content0-block-icon",
              children:
                "https://zos.alipayobjects.com/rmsportal/EkXWVvAaFJKCzhMmQYiX.png",
            },
            {
              name: "title",
              className: "content0-block-title",
              children: "一站式数据运营",
            },
            {
              name: "content",
              children: "沉淀产品接入效率和数据运营",
            },
          ],
        },
      },
    ],
  },
};
export const Content10DataSource = {
  wrapper: { className: "home-page-wrapper content1-wrapper" },
  OverPack: { className: "home-page content1", playScale: 0.3 },
  imgWrapper: { className: "content1-img", md: 10, xs: 24 },
  img: {
    children: "https://zos.alipayobjects.com/rmsportal/nLzbeGQLPyBJoli.png",
  },
  textWrapper: { className: "content1-text", md: 14, xs: 24 },
  title: { className: "content1-title", children: "企业资源管理" },
  content: {
    className: "content1-content",
    children:
      "云资源集中编排、弹性伸缩、持续发布和部署，高可用及容灾。云资源集中编排、弹性伸缩、持续发布和部署，高可用及容灾。云资源集中编排、弹性伸缩、持续发布和部署，高可用及容灾。",
  },
};
export const Teams10DataSource = {
  wrapper: { className: "home-page-wrapper teams1-wrapper" },
  page: { className: "home-page teams1" },
  OverPack: { playScale: 0.3, className: "" },
  titleWrapper: {
    className: "title-wrapper",
    children: [{ name: "title", children: "团队成员" }],
  },
  block: {
    className: "block-wrapper",
    children: [
      {
        name: "block0",
        className: "block",
        md: 8,
        xs: 24,
        titleWrapper: {
          children: [
            {
              name: "image",
              className: "teams1-image",
              children:
                "http://5b0988e595225.cdn.sohucs.com/images/20190805/38fd5ea8dcce4e28806005114ec2c315.png",
            },
            {
              name: "title",
              className: "teams1-title",
              children: (
                <span>
                  <p>马越</p>
                </span>
              ),
            },
            {
              name: "content",
              className: "teams1-job",
              children: (
                <span>
                  <p>华东师范大学-17-数据科学</p>
                </span>
              ),
            },
            {
              name: "content1",
              className: "teams1-content",
              children: "Osprey -- 软件开发工程师",
            },
          ],
        },
      },
      {
        name: "block1",
        className: "block",
        md: 8,
        xs: 24,
        titleWrapper: {
          children: [
            {
              name: "image",
              className: "teams1-image",
              children:
                "https://p9.pstatp.com/large/pgc-image/21e87df44309434187294b907b015b77",
            },
            {
              name: "title",
              className: "teams1-title",
              children: (
                <span>
                  <p>张子涵</p>
                </span>
              ),
            },
            {
              name: "content",
              className: "teams1-job",
              children: (
                <span>
                  <p>华东师范大学-18-卓越班</p>
                </span>
              ),
            },
            {
              name: "content1",
              className: "teams1-content",
              children: "Osprey -- 软件开发工程师",
            },
          ],
        },
      },
      {
        name: "block2",
        className: "block",
        md: 8,
        xs: 24,
        titleWrapper: {
          children: [
            {
              name: "image",
              className: "teams1-image",
              children:
                "https://gw.alipayobjects.com/mdn/rms_ae7ad9/afts/img/A*njqxS5Ky7CQAAAAAAAAAAABjARQnAQ",
            },
            {
              name: "title",
              className: "teams1-title",
              children: (
                <span>
                  <p>胡梓锐</p>
                </span>
              ),
            },
            {
              name: "content",
              className: "teams1-job",
              children: (
                <span>
                  <p>华东师范大学-18-软件科学</p>
                </span>
              ),
            },
            {
              name: "content1",
              className: "teams1-content",
              children: "Osprey -- 软件开发工程师",
            },
          ],
        },
      },
    ],
  },
};
export const Content30DataSource = {
  wrapper: { className: "home-page-wrapper content3-wrapper" },
  page: { className: "home-page content3" },
  OverPack: { playScale: 0.3 },
  titleWrapper: {
    className: "title-wrapper",
    children: [
      {
        name: "title",
        children: (
          <span>
            <p>OSPrey提供专业的第三方平台服务</p>
          </span>
        ),
        className: "title-h1",
      },
      {
        name: "content",
        className: "title-content",
        children: (
          <span>
            <p>基于华东师范大学强大的基础资源</p>
          </span>
        ),
      },
    ],
  },
  block: {
    className: "content3-block-wrapper",
    children: [
      {
        name: "block0",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/ScHBSdwpTkAHZkJ.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "企业资源管理" },
          content: {
            className: "content3-content",
            children:
              "云资源集中编排、弹性伸缩、持续发布和部署，高可用及容灾。",
          },
        },
      },
      {
        name: "block1",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/NKBELAOuuKbofDD.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "云安全" },
          content: {
            className: "content3-content",
            children:
              "按金融企业安全要求打造的完整云上安全体系，全方位保障金融应用及数据安全。",
          },
        },
      },
      {
        name: "block2",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/xMSBjgxBhKfyMWX.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "云监控" },
          content: {
            className: "content3-content",
            children:
              "分布式云环境集中监控，统一资源及应用状态视图，智能分析及故障定位。",
          },
        },
      },
      {
        name: "block3",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/MNdlBNhmDBLuzqp.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "移动" },
          content: {
            className: "content3-content",
            children:
              "一站式移动金融APP开发及全面监控；丰富可用组件，动态发布和故障热修复。",
          },
        },
      },
      {
        name: "block4",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/UsUmoBRyLvkIQeO.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "分布式中间件" },
          content: {
            className: "content3-content",
            children:
              "金融级联机交易处理中间件，大规模分布式计算机，数万笔/秒级并发能力，严格保证交易数据统一性。",
          },
        },
      },
      {
        name: "block5",
        className: "content3-block",
        md: 8,
        xs: 24,
        children: {
          icon: {
            className: "content3-icon",
            children:
              "https://zos.alipayobjects.com/rmsportal/ipwaQLBLflRfUrg.png",
          },
          textWrapper: { className: "content3-text" },
          title: { className: "content3-title", children: "大数据" },
          content: {
            className: "content3-content",
            children:
              "一站式、全周期大数据协同工作平台，PB级数据处理、毫秒级数据分析工具。",
          },
        },
      },
    ],
  },
};
export const Feature50DataSource = {
  wrapper: { className: "home-page-wrapper content7-wrapper" },
  page: { className: "home-page content7" },
  OverPack: {},
  titleWrapper: {
    className: "title-wrapper",
    children: [
      {
        name: "title",
        children: "Osprey提供定制化的数据交易服务",
        className: "title-h1",
      },
      {
        name: "content",
        children: "基于华东师范大学数据科学学院强大的基础资源",
      },
    ],
  },
  tabsWrapper: { className: "content7-tabs-wrapper" },
  block: {
    children: [
      {
        name: "block0",
        tag: {
          className: "content7-tag",
          text: { children: "PHONE", className: "content7-tag-name" },
          icon: { children: "mobile" },
        },
        content: {
          className: "content7-content",
          text: {
            className: "content7-text",
            md: 14,
            xs: 24,
            children: (
              <span>
                <h3>创新</h3>
                <p>
                  将通用零知识证明技术应用于大数据PaaS交易系统。SDTE提出的大数据PaaS交易系统是使用SGX和智能合约来保证数据隐私和执行过可信的特性的，这样会对硬件有限制条件。而本文是使用零知识证明技术来保证上述特性的，对于参与方的硬件没有要求。同时，应用零知识证明保证“谁卖谁计算“，解决了SDTE中多个节点对同一个分析程序进行计算，从而浪费算力的缺点。
                </p>
                <br />
                <h3>融合</h3>
                <p>
                  在大数据PaaS系统中加入函数隐私特性。Osprey首次将函数隐私引入大数据交易系统。已有的大数据交易系统方案没有考虑到买方的分析函数不想透露的情况，基于这种情况，Osprey用程序混淆和IO的方法提供了一定程度上的函数隐私。
                </p>
                <br />
                <h3>安全</h3>
                同时保证公平交易、数据隐私和函数隐私。分析以前的方案，SDTE主要解决的问题是数据隐私，没有考虑函数隐私。而fair-swap等方案主要关注公平交易。Osprey同时实现了公平交易，数据隐私和函数隐私
              </span>
            ),
          },
          img: {
            className: "content7-img",
            children:
              "https://zos.alipayobjects.com/rmsportal/xBrUaDROgtFBRRL.png",
            md: 10,
            xs: 24,
          },
        },
      },
      {
        name: "block1",
        tag: {
          className: "content7-tag",
          icon: { children: "tablet" },
          text: { className: "content7-tag-name", children: "TABLET" },
        },
        content: {
          className: "content7-content",
          text: {
            className: "content7-text",
            md: 14,
            xs: 24,
            children: (
              <span>
                <h3>创新</h3>
                <p>
                  将通用零知识证明技术应用于大数据PaaS交易系统。SDTE提出的大数据PaaS交易系统是使用SGX和智能合约来保证数据隐私和执行过可信的特性的，这样会对硬件有限制条件。而本文是使用零知识证明技术来保证上述特性的，对于参与方的硬件没有要求。同时，应用零知识证明保证“谁卖谁计算“，解决了SDTE中多个节点对同一个分析程序进行计算，从而浪费算力的缺点。
                </p>
                <br />
                <h3>融合</h3>
                <p>
                  在大数据PaaS系统中加入函数隐私特性。Osprey首次将函数隐私引入大数据交易系统。已有的大数据交易系统方案没有考虑到买方的分析函数不想透露的情况，基于这种情况，Osprey用程序混淆和IO的方法提供了一定程度上的函数隐私。
                </p>
                <br />
                <h3>安全</h3>
                同时保证公平交易、数据隐私和函数隐私。分析以前的方案，SDTE主要解决的问题是数据隐私，没有考虑函数隐私。而fair-swap等方案主要关注公平交易。Osprey同时实现了公平交易，数据隐私和函数隐私
              </span>
            ),
          },
          img: {
            className: "content7-img",
            md: 10,
            xs: 24,
            children:
              "https://zos.alipayobjects.com/rmsportal/xBrUaDROgtFBRRL.png",
          },
        },
      },
      {
        name: "block2",
        tag: {
          className: "content7-tag",
          text: { children: "DESKTOP", className: "content7-tag-name" },
          icon: { children: "laptop" },
        },
        content: {
          className: "content7-content",
          text: {
            className: "content7-text",
            md: 14,
            xs: 24,
            children: (
              <span>
                <h3>创新</h3>
                <p>
                  将通用零知识证明技术应用于大数据PaaS交易系统。SDTE提出的大数据PaaS交易系统是使用SGX和智能合约来保证数据隐私和执行过可信的特性的，这样会对硬件有限制条件。而本文是使用零知识证明技术来保证上述特性的，对于参与方的硬件没有要求。同时，应用零知识证明保证“谁卖谁计算“，解决了SDTE中多个节点对同一个分析程序进行计算，从而浪费算力的缺点。
                </p>
                <br />
                <h3>融合</h3>
                <p>
                  在大数据PaaS系统中加入函数隐私特性。Osprey首次将函数隐私引入大数据交易系统。已有的大数据交易系统方案没有考虑到买方的分析函数不想透露的情况，基于这种情况，Osprey用程序混淆和IO的方法提供了一定程度上的函数隐私。
                </p>
                <br />
                <h3>安全</h3>
                同时保证公平交易、数据隐私和函数隐私。分析以前的方案，SDTE主要解决的问题是数据隐私，没有考虑函数隐私。而fair-swap等方案主要关注公平交易。Osprey同时实现了公平交易，数据隐私和函数隐私
              </span>
            ),
          },
          img: {
            className: "content7-img",
            md: 10,
            xs: 24,
            children:
              "https://zos.alipayobjects.com/rmsportal/xBrUaDROgtFBRRL.png",
          },
        },
      },
    ],
  },
};
export const Content40DataSource = {
  wrapper: { className: "home-page-wrapper content4-wrapper" },
  page: { className: "home-page content4" },
  OverPack: { playScale: 0.3, className: "" },
  titleWrapper: {
    className: "title-wrapper",
    children: [
      {
        name: "title",
        children: "Osprey提供专业的服务",
        className: "title-h1",
      },
      {
        name: "content",
        className: "title-content content4-title-content",
        children: "大数据时代，数据交易",
      },
    ],
  },
  video: {
    className: "content4-video",
    children: {
      video: "https://os.alipayobjects.com/rmsportal/EejaUGsyExkXyXr.mp4",
      image: "https://zos.alipayobjects.com/rmsportal/HZgzhugQZkqUwBVeNyfz.jpg",
    },
  },
};

export const Footer10DataSource = {
  wrapper: { className: "home-page-wrapper footer1-wrapper" },
  OverPack: {
    className: "footer1 kntq1dmeq0k-editor_css",
    playScale: 0.2,
    appear: true,
  },
  block: {
    className: "home-page",
    gutter: 0,
    children: [
      {
        name: "block0",
        xs: 24,
        md: 6,
        className: "block",
        title: {
          className: "logo",
          children:
            "https://zos.alipayobjects.com/rmsportal/qqaimmXZVSwAhpL.svg",
        },
        childWrapper: {
          className: "slogan",
          children: [
            {
              name: "content0",
              children: "基于AntDesign+AntMotion的前端开发",
            },
          ],
        },
      },
      {
        name: "block1",
        xs: 24,
        md: 6,
        className: "block",
        title: { children: "产品" },
        childWrapper: {
          children: [
            { name: "link0", href: "#", children: "产品更新记录" },
            { name: "link1", href: "#", children: "API文档" },
            { name: "link2", href: "#", children: "快速入门" },
            { name: "link3", href: "#", children: "参考指南" },
          ],
        },
      },
      {
        name: "block2",
        xs: 24,
        md: 6,
        className: "block",
        title: { children: "关于" },
        childWrapper: {
          children: [
            { href: "#", name: "link0", children: "FAQ" },
            {
              href: "https://github.com/alittlehorse/osprey#",
              name: "link1",
              children: "联系我们",
            },
          ],
        },
      },
      {
        name: "block3",
        xs: 24,
        md: 6,
        className: "block",
        title: { children: "组件库" },
        childWrapper: {
          children: [
            {
              href: "https://ant.design/components/overview-cn/",
              name: "link0",
              children: "Ant Design",
            },
            {
              href: "https://motion.ant.design/index-cn",
              name: "link1",
              children: "Ant Motion",
            },
          ],
        },
      },
    ],
  },
  copyrightWrapper: { className: "copyright-wrapper" },
  copyrightPage: { className: "home-page" },
  copyright: {
    className: "copyright",
    children: (
      <span>
        <span>
          <span>©2021 by ECNU Osprey&nbsp;All Rights Reserved</span>
        </span>
      </span>
    ),
  },
};
