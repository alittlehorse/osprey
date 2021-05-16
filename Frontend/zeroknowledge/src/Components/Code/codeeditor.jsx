import CodeMirror from '@uiw/react-codemirror';
import { useState } from 'react';
import 'codemirror/addon/display/autorefresh';
import 'codemirror/addon/comment/comment';
import 'codemirror/addon/edit/matchbrackets';
import 'codemirror/keymap/sublime';
import 'codemirror/addon/hint/show-hint.css';
import 'codemirror/addon/hint/show-hint.js';
import 'codemirror/theme/monokai.css';
import 'codemirror/theme/ambiance.css';
import "./codeeditor.css";
import { Select, BackTop } from 'antd';
import { Divider } from 'antd';
import Codeparameter from './codeparameter';
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
import TextArea from 'antd/lib/input/TextArea';
import { Upload, message, Button } from 'antd';
import { UploadOutlined, VerticalAlignTopOutlined } from '@ant-design/icons';
const { Option } = Select;

const setFontSizeByClassName = (value) => {
    var obj = document.getElementsByClassName("CodeMirror");
    if (value == '12px') {
        obj[0].setAttribute('style', 'font-size:12px;');
        obj[1].setAttribute('style', 'font-size:12px;');
    }
    else if (value == '9px') {
        obj[0].setAttribute('style', 'font-size:9px;');
        obj[1].setAttribute('style', 'font-size:9px;');
    }
    else if (value == '14px') {
        obj[0].setAttribute('style', 'font-size:14px;');
        obj[1].setAttribute('style', 'font-size:14px;');
    }
    else if (value == '16px') {
        obj[0].setAttribute('style', 'font-size:16px;');
        obj[1].setAttribute('style', 'font-size:16px;');
    }
    else if (value == '18px') {
        obj[0].setAttribute('style', 'font-size:18px;');
        obj[1].setAttribute('style', 'font-size:18px;');
    }
    else {
        obj[0].setAttribute('style', 'font-size:22px;');
        obj[1].setAttribute('style', 'font-size:22px;');
    }
}

const setFontThemeByClassName = (value) => {
    var obj = document.getElementsByClassName("CodeMirror");
    if (value == 'FangSong') {
        obj[0].setAttribute('style', 'font-family:FangSong;');
        obj[1].setAttribute('style', 'font-family:FangSong;');
    }
    else if (value == 'KaiTi') {
        obj[0].setAttribute('style', 'font-family:KaiTi;');
        obj[1].setAttribute('style', 'font-family:KaiTi;');
    }
    else if (value == 'PMingLiU') {
        obj[0].setAttribute('style', 'font-family:PMingLiU;');
        obj[1].setAttribute('style', 'font-family:PMingLiU;');
    }
    else if (value == 'Microsoft YaHei') {
        obj[0].setAttribute('style', 'font-family:Microsoft YaHei;');
        obj[1].setAttribute('style', 'font-family:Microsoft YaHei;');
    }
    else if (value == 'YouYuan') {
        obj[0].setAttribute('style', 'font-family:YouYuan;');
        obj[1].setAttribute('style', 'font-family:YouYuan;');
    }
    else {
        obj[0].setAttribute('style', 'font-family:Arial;');
        obj[1].setAttribute('style', 'font-family:Arial;');
    }
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

const SelectLanguage = ({ onChange }) => {
    return (
        <Select style={{ width: 120 }} onChange={onChange} defaultValue="语言">
            <Option value="c">c</Option>
            <Option value="c++">c++</Option>
            <Option value="java">java</Option>
            <Option value="python">python</Option>
            <Option value="csharp">c#</Option>
        </Select>
    );
};


const themes = ['3024-day', '3024-night', 'abcdef', 'ambiance-mobile', 'ambiance', 'base16-dark', 'base16-light', 'bespin', 'blackboard', 'cobalt', 'colorforth', 'darcula', 'dracula', 'duotone-dark', 'duotone-light', 'eclipse', 'elegant', 'erlang-dark', 'gruvbox-dark', 'hopscotch', 'icecoder', 'idea', 'isotope', 'lesser-dark', 'liquibyte', 'lucario', 'material', 'mbo', 'mdn-like', 'midnight', 'monokai', 'neat', 'neo', 'night', 'oceanic-next', 'panda-syntax', 'paraiso-dark', 'paraiso-light', 'pastel-on-dark', 'railscasts', 'rubyblue', 'seti', 'shadowfox', 'solarized', 'ssms', 'the-matrix', 'tomorrow-night-bright', 'tomorrow-night-eighties', 'ttcn', 'twilight', 'vibrant-ink', 'xq-dark', 'xq-light', 'yeti', 'zenburn'];
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
    const [verify_program, setVerify_program] = useState('import sys; .....')
    const [theme, setTheme] = useState('monokai')
    const [mode, setmode] = useState('c++')
    const [compile_info, setcompile_info] = useState("")
    const [userProgram, setuserProgram] = useState("; TinyRAM V=2.000 M=vn W=16 K=16\n;;; avarage\n;;; primary input: DATA_HASH\n;;; aux input: DATA\n;;; suppose the aux input is a array which length is 20\n;;; compute the avarage of data,which hash is DATA_HASH\n;;; 1. hash aux input and compare with the DATA_HASH\n;;; 2. avarage the aux inpute and out the result\n\n;;;we just complete the step2 firstly, and the hash function is hard.\nstore.w 0, r0                    ; 0:\nmov r0, 32768                    ; 4:\nread r1, 0                       ; 8: read the first word in the primary word\ncjmp 28                          ; 12: if the flag is 1 ,jump 28\nadd r0, r0, 2                    ; 16:\nstore.w r0, r1                   ; 20:\njmp 8                            ; 24:this prelude can store the primary input in the momery\nstore.w 32768, r0                ; 28: end of prelude. put the data end index in the  32768\nmov r3, 0                        ; 44:r3 is the count index of auxiliary input\nmov r4, 0                        ; 48:r4 is the sum of r2\n_loop:read r2, 1                 ; 36: read auxiliary input in r2 (note that pairs are processed in reverse order)\ncjmp _bail                       ; 40\nadd r3,r3,1                      ; 52:r3 += 1\nadd r4, r4, r2                   ; 56:r4 = r4 + r2\njmp _loop                        ; 60\n_bail: udiv r4,r4,r3             ; 64:r4 = r4/r3\nload.w r1,r0\nsub r4,r4,r1\nanswer r4")

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
    const onChangeLanguage = (value) => {
        setmode(value);
        console.log(value);
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
    function my_fileReader2(e) {
        console.log(e.target.files[0]);
        const reader = new FileReader();
        // 用readAsText读取TXT文件内容
        reader.readAsText(e.target.files[0]);
        reader.onload = function (e) {
            console.log(e.target.result); 　　 //读取结果保存在字符串中
            setuserProgram(e.target.result);　　　//直接保存全部数据为一个字符串
        }.bind(this);
        scrollToAnchor('program2')
    };
    function setFileVisible() {
        var fileInput = document.getElementById("file-upload");
        fileInput.click();
    }
    function setFileVisible2() {
        var fileInput = document.getElementById("file-upload2");
        fileInput.click();
    }
    const scrollToAnchor = (anchorName) => {
        if (anchorName) {
            // 找到锚点
            let anchorElement = document.getElementById(anchorName);
            if (anchorElement) { anchorElement.scrollIntoView({ block: 'start', behavior: 'smooth' }); }
        }
    }

    return (
        <div >
            <BackTop >
                <Button type="Link" icon={<VerticalAlignTopOutlined />} />
            </BackTop>
            <div className="ToolBar">
                <SelectTabSize value={tabSize} onChange={onChangeTabSize} />
                <SelectTheme value={theme} onChange={onChangeCodeTheme} />
                <SelectFontSize value={FontSize} onChange={onChangeFontSize} />
                <SelectFontTheme value={FontTheme} onChange={onChangeFontTheme} />
                <SelectLanguage value={mode} onChange={onChangeLanguage} />
                <Button icon={<UploadOutlined />} onClick={setFileVisible} >上传程序</Button>
                <Button icon={<UploadOutlined />} onClick={setFileVisible2} >上传验证程序</Button>
                <Codeparameter program={verify_program} verify_program={userProgram} compile_info={compile_info} changeInfo={(compile_info) => setcompile_info(compile_info)}></Codeparameter>
                <input type="file" className="file" onChange={my_fileReader} id="file-upload" style={{ display: 'none' }} />
                <input type="file" className="file" onChange={my_fileReader2} id="file-upload2" style={{ display: 'none' }} />
                <Divider />
            </div>
            <div id='program1' >
                <CodeMirror
                    value={verify_program}
                    options={{
                        fullScreen: true,
                        tabSize,
                        theme,
                        lineNumbers: true,
                        styleActiveLine: true,
                        keyMap: "sublime",
                        mode,
                        matchBrackets: true,
                        extraKeys: { "Ctrl-Space": "autocomplete" }//ctrl-space唤起智能提示
                    }}
                    onBlur={editor => {
                        setVerify_program(editor.getValue());
                    }}
                />
            </div>
            <div id='program2'>
                <CodeMirror
                    value={userProgram}
                    options={{
                        fullScreen: true,
                        tabSize,
                        theme,
                        lineNumbers: true,
                        styleActiveLine: true,
                        keyMap: "sublime",
                        mode,
                        matchBrackets: true,
                        extraKeys: { "Ctrl-Space": "autocomplete" }//ctrl-space唤起智能提示
                    }}
                    onBlur={editor => {
                        setuserProgram(editor.getValue());
                    }}
                />
            </div>
            <div>
                <TextArea rows={10} value={compile_info} id='result'></TextArea>
            </div>
        </div>
    )
}
export default Editor;