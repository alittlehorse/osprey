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
import { Upload, message, Button } from 'antd';
import { UploadOutlined } from '@ant-design/icons';
import { Select } from 'antd';
import Codeparameter from './codeparameter';
// const code = 'const a = 0;';
const { Option } = Select;

const SelectTabSize = ({ onChange }) => {
    return (
        <Select style={{ width: 120 }} onChange={onChange} defaultValue="Tab大小">
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

function Editor(props) {
    const [tabSize, setTabSize] = useState('40');
    const [FontSize, setFontSize] = useState('16px')
    const [OutputText, setOutputText] = useState('')
    const onChangeTabSize = (value) => {
        setTabSize(value);
    }
    const onChangeFontSize = (value) => {
        setFontSize(value);
        console.log(value);
    }
    function my_fileReader(e) {
        console.log(e.target.files[0]);
        const reader = new FileReader();
        // 用readAsText读取TXT文件内容
        reader.readAsText(e.target.files[0]);
        reader.onload = function (e) {
            console.log(e.target.result); 　　 //读取结果保存在字符串中
            setOutputText(e.target.result);　　　//直接保存全部数据为一个字符串
        }.bind(this);
    };
    return (
        <div >
            <div className="ToolBar">
                <SelectTabSize value={tabSize} onChange={onChangeTabSize} />
                <SelectFontSize value={FontSize} onChange={onChangeFontSize} />
                <Codeparameter OutputText={OutputText}></Codeparameter>
                <input type="file" className="file" onChange={my_fileReader} id="img-upload" />
            </div>
            <div >
                <CodeMirror
                    value={OutputText}
                    options={{
                        fullScreen: true,
                        tabSize,
                        lineNumbers: true,
                        styleActiveLine: true,
                        theme: "monokai",
                        keyMap: "sublime",
                        mode: "python",
                        matchBrackets: true,
                        extraKeys: { "Ctrl-Space": "autocomplete" }//ctrl-space唤起智能提示
                    }}
                    onBlur={editor => {
                        setOutputText(editor.getValue());
                    }}
                />
            </div>
        </div>
    )
}
export default Editor;