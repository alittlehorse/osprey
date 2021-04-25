import { Result, Button } from 'antd';
import React from 'react'
function MyResult() {
    return (
        <div className = "result">
            <Result
                status="success"
                title="Successfully Purchased Cloud Server on Osprey!"
                subTitle="Order number: 2021424 Cloud server configuration takes 1-5 minutes, please wait."
                extra={[
                    <Button type="primary" key="console" href="/">
                        Go Console
      </Button>,
                    <Button key="buy">Buy Again</Button>,
                ]}
            />
        </div>
    )
}

export default MyResult