import CodeMirror from '@uiw/react-codemirror';
import React, { useRef, useEffect, useImperativeHandle, useState, useMemo } from 'react';
import 'codemirror/addon/display/autorefresh';
import 'codemirror/addon/comment/comment';
import 'codemirror/addon/edit/matchbrackets';
import 'codemirror/keymap/sublime';
import 'codemirror/addon/hint/show-hint.css';
import 'codemirror/addon/hint/show-hint.js';
import 'codemirror/theme/monokai.css';
import 'codemirror/theme/ambiance.css';
import "./codeeditor.css";
import { Upload, message, Button, Select, BackTop } from 'antd';
import { UploadOutlined } from '@ant-design/icons';
import { Divider } from 'antd';
import Codeparameter from './codeparameter';
import { notification } from 'antd';
import { SmileOutlined, ItalicOutlined } from '@ant-design/icons';
import 'codemirror/theme/3024-day.css';
import 'codemirror/theme/3024-night.css';
import 'codemirror/theme/abcdef.css';
import 'codemirror/theme/ambiance-mobile.css';
import 'codemirror/theme/ambiance.css';
import 'codemirror/theme/base16-dark.css';
import 'codemirror/theme/base16-light.css';
import 'codemirror/theme/bespin.css';
import 'codemirror/theme/blackboard.css';
import 'codemirror/theme/cobalt.css';
import 'codemirror/theme/colorforth.css';
import 'codemirror/theme/darcula.css';
import 'codemirror/theme/dracula.css';
import 'codemirror/theme/duotone-dark.css';
import 'codemirror/theme/duotone-light.css';
import 'codemirror/theme/eclipse.css';
import 'codemirror/theme/elegant.css';
import 'codemirror/theme/erlang-dark.css';
import 'codemirror/theme/gruvbox-dark.css';
import 'codemirror/theme/hopscotch.css';
import 'codemirror/theme/icecoder.css';
import 'codemirror/theme/idea.css';
import 'codemirror/theme/isotope.css';
import 'codemirror/theme/lesser-dark.css';
import 'codemirror/theme/liquibyte.css';
import 'codemirror/theme/lucario.css';
import 'codemirror/theme/material.css';
import 'codemirror/theme/mbo.css';
import 'codemirror/theme/mdn-like.css';
import 'codemirror/theme/midnight.css';
import 'codemirror/theme/monokai.css';
import 'codemirror/theme/neat.css';
import 'codemirror/theme/neo.css';
import 'codemirror/theme/night.css';
import 'codemirror/theme/oceanic-next.css';
import 'codemirror/theme/panda-syntax.css';
import 'codemirror/theme/paraiso-dark.css';
import 'codemirror/theme/paraiso-light.css';
import 'codemirror/theme/pastel-on-dark.css';
import 'codemirror/theme/railscasts.css';
import 'codemirror/theme/rubyblue.css';
import 'codemirror/theme/seti.css';
import 'codemirror/theme/shadowfox.css';
import 'codemirror/theme/solarized.css';
import 'codemirror/theme/ssms.css';
import 'codemirror/theme/the-matrix.css';
import 'codemirror/theme/tomorrow-night-bright.css';
import 'codemirror/theme/tomorrow-night-eighties.css';
import 'codemirror/theme/ttcn.css';
import 'codemirror/theme/twilight.css';
import 'codemirror/theme/vibrant-ink.css';
import 'codemirror/theme/xq-dark.css';
import 'codemirror/theme/xq-light.css';
import 'codemirror/theme/yeti.css';
import 'codemirror/theme/zenburn.css';
const { Option } = Select;


const setFontSizeByClassName = (value) => {
    var obj = document.getElementsByClassName("CodeMirror");
    if (value == '12px')
        obj[0].setAttribute('style', 'font-size:12px;');
    else if (value == '9px')
        obj[0].setAttribute('style', 'font-size:9px;');
    else if (value == '14px')
        obj[0].setAttribute('style', 'font-size:14px;');
    else if (value == '16px')
        obj[0].setAttribute('style', 'font-size:16px;');
    else if (value == '18px')
        obj[0].setAttribute('style', 'font-size:18px;');
    else
        obj[0].setAttribute('style', 'font-size:22px;');
}

const setFontThemeByClassName = (value) => {
    var obj = document.getElementsByClassName("CodeMirror");
    if (value == 'FangSong')
        obj[0].setAttribute('style', 'font-family:FangSong;');
    else if (value == 'KaiTi')
        obj[0].setAttribute('style', 'font-family:KaiTi;');
    else if (value == 'PMingLiU')
        obj[0].setAttribute('style', 'font-family:PMingLiU;');
    else if (value == 'Microsoft YaHei')
        obj[0].setAttribute('style', 'font-family:Microsoft YaHei;');
    else if (value == 'YouYuan')
        obj[0].setAttribute('style', 'font-family:YouYuan;');
    else
        obj[0].setAttribute('style', 'font-family:Arial;');
}


const SelectTabSize = ({ onChange }) => {
    return (
        <Select style={{ width: 120 }} onChange={onChange} defaultValue="Tab大小" >
            <Option value="2">2</Option>
            <Option value="10">10</Option>
            <Option value="40">40</Option>
        </Select>
    );
};

const SelectFontSize = ({ onChange }) => {
    return (
        <Select style={{ width: 120 }} onChange={onChange} defaultValue="字体大小">
            <Option value="9px">9px</Option>
            <Option value="12px">12px</Option>
            <Option value="14px">14px</Option>
            <Option value="16px">16px</Option>
            <Option value="18px">18px</Option>
            <Option value="22px">22px</Option>
        </Select>
    );
};

const themes = ['3024-day', '3024-night', 'abcdef', 'ambiance-mobile', 'ambiance', 'base16-dark', 'base16-light', 'bespin', 'blackboard', 'cobalt', 'colorforth', 'darcula', 'dracula', 'duotone-dark', 'duotone-light', 'eclipse', 'elegant', 'erlang-dark', 'gruvbox-dark', 'hopscotch', 'icecoder', 'idea', 'isotope', 'lesser-dark', 'liquibyte', 'lucario', 'material', 'mbo', 'mdn-like', 'midnight', 'monokai', 'neat', 'neo', 'night', 'oceanic-next', 'panda-syntax', 'paraiso-dark', 'paraiso-light', 'pastel-on-dark', 'railscasts', 'rubyblue', 'seti', 'shadowfox', 'solarized', 'ssms', 'the-matrix', 'tomorrow-night-bright', 'tomorrow-night-eighties', 'ttcn', 'twilight', 'vibrant-ink', 'xq-dark', 'xq-light', 'yeti', 'zenburn'];
// const codethemeoptions = themes.forEach(function (element) {
//     console.log("jiijiji" + element);
//     <Option value={element}>{element}</Option>;
// });
// const codethemeoptions = themes.map(d => <Option value={d.value + ""}>{d.text}</Option>);
const SelectFontTheme = ({ onChange }) => {
    return (
        <Select style={{ width: 120 }} onChange={onChange} defaultValue="字体">
            <Option value="PMingLiU">新細明體</Option>
            <Option value="SimHei">SimHei</Option>
            <Option value="Microsoft YaHei">Microsoft YaHei</Option>
            <Option value="KaiTi">KaiTi</Option>
            <Option value="FangSong">FangSong</Option>
            <Option value="YouYuan">YouYuan</Option>
        </Select>
    );
};


function Editor(props) {
    const [tabSize, setTabSize] = useState('40');
    const [FontSize, setFontSize] = useState('16px')
    const [FontTheme, setFontTheme] = useState('FangSong')
    const [verify_program, setVerify_program] = useState('')
    const [theme, setTheme] = useState('monokai')

    const SelectTheme = ({ onChange }) => {
        return (
            <Select style={{ width: 120 }} onChange={onChange} defaultValue="代码风格" >
                <Option value="3024-day">3024-day</Option>
                <Option value="3024-night">3024-night</Option>
                <Option value="abcdef">abcdef</Option>
                <Option value="ambiance">ambiance</Option>
                <Option value="ambiance-mobile">ambiance-mobile</Option>
                <Option value="base16-dark">base16-dark</Option>
                <Option value="base16-light">base16-light</Option>
                <Option value="lucario">lucario</Option>
                <Option value="neo">neo</Option>
            </Select>
        );
    };
    const onChangeTabSize = (value) => {
        setTabSize(value);
    }
    const onChangeFontSize = (value) => {
        setFontSize(value);
        console.log(value);
        setFontSizeByClassName(value);
    };
    const onChangeFontTheme = (value) => {
        setFontTheme(value);
        console.log(value);
        setFontThemeByClassName(value);
    }
    const onChangeCodeTheme = (value) => {
        setTheme(value);
        console.log("huhu" + value)
    }
    function my_fileReader(e) {
        console.log(e.target.files[0]);
        const reader = new FileReader();
        // 用readAsText读取TXT文件内容
        reader.readAsText(e.target.files[0]);
        reader.onload = function (e) {
            console.log(e.target.result); 　　 //读取结果保存在字符串中
            setVerify_program(e.target.result);　　　//直接保存全部数据为一个字符串
        }.bind(this);
    };
    return (
        <div >
            <div className="ToolBar">
                <SelectTabSize value={tabSize} onChange={onChangeTabSize} />
                <SelectTheme value={theme} onChange={onChangeCodeTheme} />
                <SelectFontSize value={FontSize} onChange={onChangeFontSize} />
                <SelectFontTheme value={FontTheme} onChange={onChangeFontTheme} />
                <Codeparameter verify_program={verify_program}></Codeparameter>
                <input type="file" className="file" onChange={my_fileReader} id="img-upload" />
                <Divider />
            </div>
            <div >
                <CodeMirror
                    value={verify_program}
                    options={{
                        fullScreen: true,
                        tabSize,
                        theme,
                        lineNumbers: true,
                        styleActiveLine: true,
                        keyMap: "sublime",
                        mode: "c",
                        matchBrackets: true,
                        extraKeys: { "Ctrl-Space": "autocomplete" }//ctrl-space唤起智能提示
                    }}
                    onBlur={editor => {
                        setVerify_program(editor.getValue());
                    }}

                />
            </div>
        </div>
    )
}
export default Editor;