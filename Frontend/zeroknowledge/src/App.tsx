import React, { Component } from "react";
import { BrowserRouter as Router, Route, Link, Switch, Redirect} from "react-router-dom";
import Header from "./Home/Nav0";
import Footer from "./Home/Footer1";
import Home from "./Home";

import { Nav01DataSource, Footer10DataSource } from "./Home/data.source.js";
import Code from "./Components/Code/code";
import MyResult from "./Components/Result/result";
import Loading from "./Components/Select/Loading";

class App extends Component {
  constructor(props: {} | Readonly<{}>) {
    super(props);
  }
  render() {
    return (
      <Router>
        <div>
          <Switch>
            <Route exact path="/" component={Home} />
            <Route path="/code" component={Code} />
            <Route path="/result" component={MyResult} />
            <Route path="/load" component={Loading} />
            {/* <Redirect exact to="/" from="/" /> */}
          </Switch>
        </div>
      </Router>
    );
  }
}

export default App;