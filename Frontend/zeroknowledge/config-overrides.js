// const { override, fixBabelImports, addLessLoader } = require("customize-cra");

// module.exports = override(
//   // 按需加载 antd
//   fixBabelImports("import", {
//     libraryName: "antd",
//     libraryDirectory: "es",
//     style: true,
//   }),
//   // 添加加载 less 的 javascriptEnabled 和 antd 的主题配置。
//   // addLessLoader({
//   //   lessOptions: {
//   //     javascriptEnabled: true,
//   //     modifyVars: { '@primary-color': '#1DA57A' },
//   //   }
//   // }),
//   addLessLoader({
//     lessOptions: {
//       modifyVars: {
//         "@primary-color": "#1DA57A",
//         "@link-color": "#1DA57A",
//       },
//       javascriptEnabled: true,
//       math: "always", // 此处指定为兼容 less-loader 3.x 的默认选项
//     },
//   }),
// );

const { override, fixBabelImports, addLessLoader } = require('customize-cra');

module.exports = override(
    fixBabelImports('import', {
        libraryName: 'antd',
        libraryDirectory: 'es',
        style: true,
    }),    
    addLessLoader({
        javascriptEnabled: true,
        modifyVars: { '@primary-color': '#1DA57A' },
        localIdentName: '[local]--[hash:base64:5]' // 自定义 CSS Modules 的 localIdentName
    }),
);