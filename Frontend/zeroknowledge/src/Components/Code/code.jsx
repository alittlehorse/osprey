import React, { useEffect, useState } from "react";
import { Select, Table } from "antd";
import Editor from "./codeeditor";
import CodeContent from "./codecontent";

const { Option } = Select;

function Code() {
  return (
    <div>
      <CodeContent></CodeContent>
    </div>
  );
}
export default Code;

